/*
 * AUTO-GENERATED _componentMain.c for the test_mainComponent component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const char* _test_mainComponent_le_mdc_ServiceInstanceName;
const char** le_mdc_ServiceInstanceNamePtr = &_test_mainComponent_le_mdc_ServiceInstanceName;
void le_mdc_ConnectService(void);
extern const char* _test_mainComponent_le_data_ServiceInstanceName;
const char** le_data_ServiceInstanceNamePtr = &_test_mainComponent_le_data_ServiceInstanceName;
void le_data_ConnectService(void);
// Component log session variables.
le_log_SessionRef_t test_mainComponent_LogSession;
le_log_Level_t* test_mainComponent_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _test_mainComponent_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _test_mainComponent_Init(void)
{
    LE_DEBUG("Initializing test_mainComponent component library.");

    // Connect client-side IPC interfaces.
    le_mdc_ConnectService();
    le_data_ConnectService();

    // Register the component with the Log Daemon.
    test_mainComponent_LogSession = log_RegComponent("test_mainComponent", &test_mainComponent_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_test_mainComponent_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
