#import <substitute.h>
#import <xpc/xpc.h>

static void setDict(xpc_object_t dict){
	if (xpc_dictionary_get_string(dict, "interfaceAddress") == NULL || xpc_dictionary_get_string(dict, "interfaceMask") == NULL){
		xpc_dictionary_set_string(dict, "interfaceAddress", "172.20.10.1");
		xpc_dictionary_set_string(dict, "interfaceMask", "255.255.255.0");
		xpc_dictionary_set_string(dict, "networkMask", "255.255.255.0");
		xpc_dictionary_set_string(dict, "startAddress", "172.20.10.2");
		xpc_dictionary_set_string(dict, "endAddress", "172.20.10.253");
	}
}

extern void *_NETRBClientStartService(char *, void *, void *, void *, xpc_object_t);

static void * (*old__NETRBClientStartService)(char *, void *, void *, void *, xpc_object_t);

static void *new__NETRBClientStartService(char *arg0, void *arg1, void *arg2, void *arg3, xpc_object_t dict){
	setDict(dict);
	return old__NETRBClientStartService(arg0, arg1, arg2, arg3, dict);
}

static void * (*old__NETRBClientStartService2)(char *, void *, void *, void *, xpc_object_t);

static void *new__NETRBClientStartService2(char *arg0, void *arg1, void *arg2, void *arg3, xpc_object_t dict){
	setDict(dict);
	return old__NETRBClientStartService2(arg0, arg1, arg2, arg3, dict);
}

__attribute__((constructor)) static void EntryPoint(){
	int sym_count = 1;

	void *wifid_syms[1];

	struct substitute_image *wifid = substitute_open_image("/usr/sbin/wifid");
	if (wifid){
		const char *wifid_names[1] = {
			"__NETRBClientStartService"
		};
		substitute_find_private_syms(wifid, wifid_names, wifid_syms, 1);
		sym_count++;
	}

	struct substitute_function_hook hook[2] = {
		{(void *)&_NETRBClientStartService, (void **)&new__NETRBClientStartService, (void **)&old__NETRBClientStartService},
		{(void *)wifid_syms[0], (void **)&new__NETRBClientStartService2, (void **)&old__NETRBClientStartService2}
	};
	substitute_hook_functions(hook, sym_count, NULL, SUBSTITUTE_NO_THREAD_SAFETY);
}