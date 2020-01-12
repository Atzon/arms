/*
 * AUTO-GENERATED _componentMain.c for the test_read_sds011Component component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component log session variables.
le_log_SessionRef_t test_read_sds011Component_LogSession;
le_log_Level_t* test_read_sds011Component_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _test_read_sds011Component_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _test_read_sds011Component_Init(void)
{
    LE_DEBUG("Initializing test_read_sds011Component component library.");

    // Register the component with the Log Daemon.
    test_read_sds011Component_LogSession = log_RegComponent("test_read_sds011Component", &test_read_sds011Component_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_test_read_sds011Component_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
