/*
 * AUTO-GENERATED _componentMain.c for the read_data_send_packageComponent component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char* _read_data_send_packageComponent_le_posCtrl_ServiceInstanceName;
const char** le_posCtrl_ServiceInstanceNamePtr = &_read_data_send_packageComponent_le_posCtrl_ServiceInstanceName;
void le_posCtrl_ConnectService(void);
extern const char* _read_data_send_packageComponent_le_pos_ServiceInstanceName;
const char** le_pos_ServiceInstanceNamePtr = &_read_data_send_packageComponent_le_pos_ServiceInstanceName;
void le_pos_ConnectService(void);
extern const char* _read_data_send_packageComponent_le_mdc_ServiceInstanceName;
const char** le_mdc_ServiceInstanceNamePtr = &_read_data_send_packageComponent_le_mdc_ServiceInstanceName;
void le_mdc_ConnectService(void);
extern const char* _read_data_send_packageComponent_le_data_ServiceInstanceName;
const char** le_data_ServiceInstanceNamePtr = &_read_data_send_packageComponent_le_data_ServiceInstanceName;
void le_data_ConnectService(void);
// Component log session variables.
le_log_SessionRef_t read_data_send_packageComponent_LogSession;
le_log_Level_t* read_data_send_packageComponent_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _read_data_send_packageComponent_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _read_data_send_packageComponent_Init(void)
{
    LE_DEBUG("Initializing read_data_send_packageComponent component library.");

    // Connect client-side IPC interfaces.
    le_posCtrl_ConnectService();
    le_pos_ConnectService();
    le_mdc_ConnectService();
    le_data_ConnectService();

    // Register the component with the Log Daemon.
    read_data_send_packageComponent_LogSession = log_RegComponent("read_data_send_packageComponent", &read_data_send_packageComponent_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_read_data_send_packageComponent_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
