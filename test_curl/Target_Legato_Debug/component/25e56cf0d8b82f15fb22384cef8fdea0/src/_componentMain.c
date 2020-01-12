/*
 * AUTO-GENERATED _componentMain.c for the test_curlComponent component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component log session variables.
le_log_SessionRef_t test_curlComponent_LogSession;
le_log_Level_t* test_curlComponent_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _test_curlComponent_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _test_curlComponent_Init(void)
{
    LE_DEBUG("Initializing test_curlComponent component library.");

    // Register the component with the Log Daemon.
    test_curlComponent_LogSession = log_RegComponent("test_curlComponent", &test_curlComponent_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_test_curlComponent_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
