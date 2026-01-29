#include "../defs.h"

#ifndef __RHOVANION_MIRKWOOD_DEFINES__
#define __RHOVANION_MIRKWOOD_DEFINES__

#define MIRKWOOD_DIR            (RHOVANION_DIR + "mirkwood/")
#define MIRKWOOD_STD_DIR        (MIRKWOOD_DIR + "std/")
#define MIRKWOOD_OLDROAD_DIR    (MIRKWOOD_DIR + "oldroad/")

#define LIGHT_NIGHT             0
#define LIGHT_DUSKDAWN          1
#define LIGHT_MIDDAY            2
#define LIGHT_BRIGHT            3

#define LIGHT_ALL               ({ LIGHT_DUSKDAWN, LIGHT_MIDDAY, LIGHT_BRIGHT })

#endif