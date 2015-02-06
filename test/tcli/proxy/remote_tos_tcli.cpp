/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Original file: remote_tos_tcli.sidl
 */
 

#define LOG_TAG     "remote_tos_tcli"

#include <string.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

#include "tos_tcli.h"


#define SERVICE_DESCRIPTOR                      "e1ba72ba-ade3-11e4-9426-7831c1c50d90"
#define SERVICE_NAME                            "remote_tos_tcli"

#define FIRST_CALL_TRANSACTION                  (1)
#define TRANSACTION_tos_tcli_init FIRST_CALL_TRANSACTION + 1
#define TRANSACTION_tos_tcli_destroy FIRST_CALL_TRANSACTION + 2
#define TRANSACTION_tos_tcli_printf FIRST_CALL_TRANSACTION + 3
#define TRANSACTION_tos_tcli_execute FIRST_CALL_TRANSACTION + 4
#define TRANSACTION_tos_tcli_executeByargs FIRST_CALL_TRANSACTION + 5

#define TRANSACTION_CALLBACK_outputcallback FIRST_CALL_TRANSACTION + 100

using namespace android;

#if defined(BINDER_SERVICE)

#include <stdlib.h>
#include "remote_tos_tcli.h"

class remote_tos_tcli_service : public BBinder  
{  
private:
    static remote_tos_tcli_service* _instance;

    remote_tos_tcli_service(){
        ALOGI(SERVICE_NAME"_service create\n");
    }
    
    virtual ~remote_tos_tcli_service() {
        ALOGI(SERVICE_NAME"_service destory\n");
    }

    static void tcli_output(const char* prompt,void* userdata) {
        IBinder* binder = (IBinder*)userdata;
        if(binder != NULL && binder->isBinderAlive()) {
            Parcel data, reply;
            data.writeInterfaceToken(String16(SERVICE_NAME"_OutputCallback"));
            data.writeCString(prompt);
            binder->transact(TRANSACTION_CALLBACK_outputcallback, data, &reply, 0);

            if(reply.readExceptionCode() == 0) {//fix check
            }
            else {
                ALOGW(SERVICE_NAME"_servce tos_tcli_onOutput exception");
            }
        }
        else {
            ALOGW(SERVICE_NAME"_servce tos_tcli_onOutput error");
        }
    }

public:  
    static int Instance() {
        if(_instance == NULL) {
            _instance = new remote_tos_tcli_service();
            int ret = defaultServiceManager()->addService(  
                String16(SERVICE_NAME), _instance );  
            ALOGI(SERVICE_NAME"_service Instance %d\n",ret);
            return ret;  
        }

        return -1;
    }
    
    virtual status_t onTransact(uint32_t code , const Parcel& data , Parcel* reply, uint32_t flags) {
        ALOGD(SERVICE_NAME"_service - onTransact code=%d",code);

        switch(code)  {

            case TRANSACTION_tos_tcli_init:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for tos_tcli_init here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                int _result = tos_tcli_init(  );

                reply->writeInt32(_result); //int as return value

                //-- end code for tos_tcli_init here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_tos_tcli_destroy:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for tos_tcli_destroy here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                int _result = tos_tcli_destroy(  );

                reply->writeInt32(_result); //int as return value

                //-- end code for tos_tcli_destroy here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_tos_tcli_printf:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for tos_tcli_printf here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                const char* buf = data.readCString();

                tos_tcli_printf( buf );

                //-- end code for tos_tcli_printf here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_tos_tcli_execute:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for tos_tcli_execute here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                const char* cmd = data.readCString();

                sp<IBinder> binder = data.readStrongBinder();

                int _result = tos_tcli_execute( cmd, remote_tos_tcli_service::tcli_output, binder.get() );

                reply->writeInt32(_result); //int as return value

                //-- end code for tos_tcli_execute here --
                return NO_ERROR;
            } break;
            
            case TRANSACTION_tos_tcli_executeByargs:
            {
                data.enforceInterface(String16(SERVICE_NAME));  //fixed check

                //-- begin code for tos_tcli_executeByargs here, will auoto generated but may change yourself if need --

                //skip Exception and result first to write output paramters
                reply->writeNoException();
                //skip Exception and result first end

                //begin paramters list
                int argc = (int)data.readInt32();  //int as input paramter

                const char* argv[16];//max 16 is OK
                memset(argv,0,sizeof(argv));
                for(int i=0;i<argc;i++) {
                    if(data.readInt32() > 0) {
                        argv[i] = data.readCString();
                    }
                    else {
                        argv[i] = NULL;
                    }
                }

                sp<IBinder> binder = data.readStrongBinder();

                int _result = tos_tcli_executeByargs( argc, argv, remote_tos_tcli_service::tcli_output, binder.get() );

                reply->writeInt32(_result); //int as return value

                //-- end code for tos_tcli_executeByargs here --
                return NO_ERROR;
            } break;
            
            default:  
                return BBinder::onTransact(code, data, reply, flags);
        
        }

        ALOGD(SERVICE_NAME"_service end");
    }
}; 

int remote_tos_tcli_service_add() {
    remote_tos_tcli_service::Instance();
    return 0;
}

remote_tos_tcli_service* remote_tos_tcli_service::_instance = NULL;

#elif defined(BINDER_CLIENT)
#include <stdarg.h>
#include <sbinder/ICallbackList.h>

class remote_tos_tcli_client  
{  
private:
    static remote_tos_tcli_client* _instance;
    sp<IBinder> _binder;

    class OutputCallback : public ICallbackList::ICallback {
    public:
        OutputCallback(void* cb,void* cookie)
            :ICallback(cb,cookie) {
            _descriptor = String16(SERVICE_NAME"_OutputCallback");
        }

        ~OutputCallback() {
        }

        virtual status_t onTransact( uint32_t code,
                const Parcel& data,Parcel* reply,uint32_t flags = 0) {
            ALOGV(SERVICE_NAME"_client onTransact code=%d\n",code);

            switch (code){
            case TRANSACTION_CALLBACK_outputcallback:
            {
                if (!data.checkInterface(this)) {
                    ALOGW(SERVICE_NAME"_client onTransact Interface error\n");
                    return -1;
                }

                if(_callback != NULL) {
                    const char* prompt = data.readCString();

                    ((tos_tcli_onOutput)_callback)(prompt,_cookie);

                    reply->writeNoException();
                }
                else {
                    reply->writeInt32(-1);//Exception
                }
                break;
            }

            default:
                return BBinder::onTransact(code, data, reply, flags);
            }

            return NO_ERROR;
        }
    };

    remote_tos_tcli_client()
        :_binder(NULL) {
        ALOGI(SERVICE_NAME"_client create\n");
        getService();
    }
    
    virtual ~remote_tos_tcli_client() {
        ALOGI(SERVICE_NAME"_client destory\n");
    }

    inline bool getService(void) {
        if(_binder == NULL) {
            sp<IServiceManager> sm = defaultServiceManager();
            _binder = sm->getService(String16(SERVICE_NAME));
        }

        if(_binder == NULL) {
            ALOGW(SERVICE_NAME"_client getFailed!\n");
        }

        return (_binder != NULL);
    }

public:  
    static remote_tos_tcli_client* Instance() {
        if(_instance == NULL) {
            ALOGI(SERVICE_NAME"_client Instance");
            _instance = new remote_tos_tcli_client();
        }

        return _instance;
    }

    int tos_tcli_init(  ) {
        Parcel data, reply;

        /*-- add you code for tos_tcli_init here --*/
        int _result = -1;
        if(!getService()) {
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            _binder->transact(TRANSACTION_tos_tcli_init,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = (typeof(_result))reply.readInt32();//int as return value

            } else {
                ALOGW(SERVICE_NAME"_client tos_tcli_init error");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client tos_tcli_init error");
        }

        return _result;
        /*-- add you code for tos_tcli_init here --*/
    }

    int tos_tcli_destroy(  ) {
        Parcel data, reply;

        /*-- add you code for tos_tcli_destroy here --*/
        int _result = -1;
        if(!getService()) {
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            _binder->transact(TRANSACTION_tos_tcli_destroy,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = (typeof(_result))reply.readInt32();//int as return value

            } else {
                ALOGW(SERVICE_NAME"_client tos_tcli_destroy error");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client tos_tcli_destroy error");
        }

        return _result;
        /*-- add you code for tos_tcli_destroy here --*/
    }

    void tos_tcli_printf( const char* buf ) {
        Parcel data, reply;

        /*-- add you code for tos_tcli_printf here --*/
        if(!getService()) {
            return;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeCString(buf);

            _binder->transact(TRANSACTION_tos_tcli_printf,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

            } else {
                ALOGW(SERVICE_NAME"_client tos_tcli_printf error");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client tos_tcli_printf error");
        }

        
        /*-- add you code for tos_tcli_printf here --*/
    }

    int tos_tcli_execute( const char* cmd, tos_tcli_onOutput out, void* userdata ) {
        Parcel data, reply;

        /*-- add you code for tos_tcli_execute here --*/
        int _result = -1;
        if(cmd == NULL || !getService()) {
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeCString(cmd);

            sp<OutputCallback> cout = new OutputCallback((void*)out,userdata);
            data.writeStrongBinder(cout);

            _binder->transact(TRANSACTION_tos_tcli_execute,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = (typeof(_result))reply.readInt32();//int as return value

            } else {
                ALOGW(SERVICE_NAME"_client tos_tcli_execute error");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client tos_tcli_execute error");
        }

        return _result;
        /*-- add you code for tos_tcli_execute here --*/
    }

    int tos_tcli_executeByargs( int argc, const char* argv[], tos_tcli_onOutput out, void* userdata ) {
        Parcel data, reply;

        /*-- add you code for tos_tcli_executeByargs here --*/
        int _result;
        if(argc <= 0 || argv == NULL || !getService()) {
            return _result;
        }

        try {
            data.writeInterfaceToken(String16(SERVICE_NAME));//fixed check

            data.writeInt32(argc);
            for(int i=0;i<argc;i++) {
                if(argv[i] != NULL) {
                    data.writeInt32(1);
                    data.writeCString(argv[i]);
                }
                else {
                    data.writeInt32(-1);
                }
            }

            sp<OutputCallback> cout = new OutputCallback((void*)out,userdata);
            data.writeStrongBinder(cout);

            _binder->transact(TRANSACTION_tos_tcli_executeByargs,data, &reply,0);

            if(reply.readExceptionCode() == 0) {//fix check

                _result = (typeof(_result))reply.readInt32();//int as return value

            } else {
                ALOGW(SERVICE_NAME"_client tos_tcli_executeByargs error");
            }
        }catch(...) {
            ALOGW(SERVICE_NAME"_client tos_tcli_executeByargs error");
        }

        return _result;
        /*-- add you code for tos_tcli_executeByargs here --*/
    }
};

remote_tos_tcli_client* remote_tos_tcli_client::_instance = NULL;

int tos_tcli_init(  ) {
    return remote_tos_tcli_client::Instance()->tos_tcli_init();
}
int tos_tcli_destroy(  ) {
    return remote_tos_tcli_client::Instance()->tos_tcli_destroy();
}
void tos_tcli_printf(const char* fmt,...) {
    char buf[1024];
    va_list arg;
    va_start(arg,fmt);
    vsnprintf(buf,sizeof(buf),fmt,arg);
    va_end(arg);
    buf[sizeof(buf)-1]=0;
    return remote_tos_tcli_client::Instance()->tos_tcli_printf(buf);
}
int tos_tcli_execute( const char* cmd, tos_tcli_onOutput out, void* userdata ) {
    return remote_tos_tcli_client::Instance()->tos_tcli_execute(cmd, out, userdata);
}
int tos_tcli_executeByargs( int argc, const char* argv[], tos_tcli_onOutput out, void* userdata ) {
    return remote_tos_tcli_client::Instance()->tos_tcli_executeByargs(argc, argv, out, userdata);
}

#else
 #error Must define BINDER_SERVICE or BINDER_CLIENT
#endif