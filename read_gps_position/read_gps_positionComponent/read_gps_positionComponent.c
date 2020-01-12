#include "legato.h"
#include "interfaces.h"

COMPONENT_INIT
{
	LE_INFO("Fetching 2D location \n");

	le_posCtrl_ActivationRef_t posCtrlRef = le_posCtrl_Request();
	if (!posCtrlRef)
	{
		LE_ERROR("Can't activate the Positioning service");
//		return LE_UNAVAILABLE;
	}


	le_result_t res;
	int32_t latitude = 0;
	int32_t longitude = 0;
	int32_t hAccuracy = 0;

	while(1) {
		res = le_pos_Get2DLocation(&latitude, &longitude, &hAccuracy);

		if (res == LE_OK)
		{
			LE_INFO("Location: latitude=%.6f, longitude=%.6f, hAccuracy=%.6f", latitude/10e5, longitude/10e5, hAccuracy/10e5);
		}
		else if (res == LE_FAULT)
		{
			LE_INFO("Failed to get the 2D location's data");
		}
		else if (res == LE_OUT_OF_RANGE)
		{
			LE_INFO("One of the retrieved parameter is invalid (set to INT32_MAX)");
		}
		else
		{
			LE_INFO("unknown location error (%d)", res);
		}

		sleep(1);
	}


    le_posCtrl_Release(posCtrlRef);
}
