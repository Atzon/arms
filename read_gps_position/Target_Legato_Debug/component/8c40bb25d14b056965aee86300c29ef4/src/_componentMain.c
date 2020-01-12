/*
 * AUTO-GENERATED _componentMain.c for the read_gps_positionComponent component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char* _read_gps_positionComponent_le_posCtrl_ServiceInstanceName;
const char** le_posCtrl_ServiceInstanceNamePtr = &_read_gps_positionComponent_le_posCtrl_ServiceInstanceName;
void le_posCtrl_ConnectService(void);
extern const char* _read_gps_positionComponent_le_pos_ServiceInstanceName;
const char** le_pos_ServiceInstanceNamePtr = &_read_gps_positionComponent_le_pos_ServiceInstanceName;
void le_pos_ConnectService(void);
// Component log session variables.
le_log_SessionRef_t read_gps_positionComponent_LogSession;
le_log_Level_t* read_gps_positionComponent_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _read_gps_positionComponent_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _read_gps_positionComponent_Init(void)
{
    LE_DEBUG("Initializing read_gps_positionComponent component library.");

    // Connect client-side IPC interfaces.
    le_posCtrl_ConnectService();
    le_pos_ConnectService();

    // Register the component with the Log Daemon.
    read_gps_positionComponent_LogSession = log_RegComponent("read_gps_positionComponent", &read_gps_positionComponent_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_read_gps_positionComponent_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
