/*
 * AUTO-GENERATED _componentMain.c for the test_gnssComponent component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char* _test_gnssComponent_le_posCtrl_ServiceInstanceName;
const char** le_posCtrl_ServiceInstanceNamePtr = &_test_gnssComponent_le_posCtrl_ServiceInstanceName;
void le_posCtrl_ConnectService(void);
extern const char* _test_gnssComponent_le_pos_ServiceInstanceName;
const char** le_pos_ServiceInstanceNamePtr = &_test_gnssComponent_le_pos_ServiceInstanceName;
void le_pos_ConnectService(void);
// Component log session variables.
le_log_SessionRef_t test_gnssComponent_LogSession;
le_log_Level_t* test_gnssComponent_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _test_gnssComponent_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _test_gnssComponent_Init(void)
{
    LE_DEBUG("Initializing test_gnssComponent component library.");

    // Connect client-side IPC interfaces.
    le_posCtrl_ConnectService();
    le_pos_ConnectService();

    // Register the component with the Log Daemon.
    test_gnssComponent_LogSession = log_RegComponent("test_gnssComponent", &test_gnssComponent_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_test_gnssComponent_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
