/*
 * AUTO-GENERATED _componentMain.c for the read_sensor_dataComponent component.

 * Don't bother hand-editing this file.
 */

#include "legato.h"
#include "../liblegato/eventLoop.h"
#include "../liblegato/log.h"

#ifdef __cplusplus
extern "C" {
#endif

// Component log session variables.
le_log_SessionRef_t read_sensor_dataComponent_LogSession;
le_log_Level_t* read_sensor_dataComponent_LogLevelFilterPtr;

// Component initialization function (COMPONENT_INIT).
void _read_sensor_dataComponent_COMPONENT_INIT(void);

// Library initialization function.
// Will be called by the dynamic linker loader when the library is loaded.
__attribute__((constructor)) void _read_sensor_dataComponent_Init(void)
{
    LE_DEBUG("Initializing read_sensor_dataComponent component library.");

    // Register the component with the Log Daemon.
    read_sensor_dataComponent_LogSession = log_RegComponent("read_sensor_dataComponent", &read_sensor_dataComponent_LogLevelFilterPtr);

    //Queue the COMPONENT_INIT function to be called by the event loop
    event_QueueComponentInit(_read_sensor_dataComponent_COMPONENT_INIT);
}


#ifdef __cplusplus
}
#endif
