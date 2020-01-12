/*
 * AUTO-GENERATED _componentMain.c for the test_iot_connComponent component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char* _test_iot_connComponent_le_mrc_ServiceInstanceName;
const char** le_mrc_ServiceInstanceNamePtr = &_test_iot_connComponent_le_mrc_ServiceInstanceName;
void le_mrc_ConnectService(void);
// Component log session variables.
le_log_SessionRef_t test_iot_connComponent_LogSession;
le_log_Level_t* test_iot_connComponent_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _test_iot_connComponent_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _test_iot_connComponent_Init(void)
{
    LE_DEBUG("Initializing test_iot_connComponent component library.");

    // Connect client-side IPC interfaces.
    le_mrc_ConnectService();

    // Register the component with the Log Daemon.
    test_iot_connComponent_LogSession = log_RegComponent("test_iot_connComponent", &test_iot_connComponent_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_test_iot_connComponent_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
