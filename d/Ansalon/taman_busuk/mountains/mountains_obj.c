inherit "/d/Krynn/common/area/area_handler";

#include <stdproperties.h>
#include "local.h"
#include "describe.h"

create_area()
{
	set_map(MAP);

	add_desc("v", ({ VALLEY_TYPE,
    	({ V1_S, V1_L1 }),
	    ({ VALLEY_ITEMS }),
	    ({ }) }));

	add_desc("w", ({ VALLEY_TYPE,
	    ({ V1_S, V1_L2 }),
	    ({ VALLEY_ITEMS,
		    ({ "cliff", "cliffs", "steep cliffs" }),
		    "The steep cliffs form a natural barrier, " +
		    "enclosing the valley on all sides."
	    }),
	    ({ }) }));

	add_desc("1", ({ ROAD_TYPE,
	    ({ R1_S, R1_L1 }),
	    ({ MOUNTAIN_ITEMS,
	       ROAD1_ITEMS,
	    }),
	    ({ }) }));

	add_desc("2", ({ ROAD_TYPE,
    	({ R1_S, R1_L1 }),
	    ({ MOUNTAIN_ITEMS,
	       ROAD1_ITEMS,
	    }),
    	({ }) }));

	add_desc("3", ({ ROAD_TYPE,
	    ({ R2_S, R2_L1 }),
    	({ VALLEY_ITEMS,
    	   ROAD2_ITEMS,
    	}),
	    ({ }) }));

	add_desc("4", ({ ROAD_TYPE,
    	({ R1_S, R1_L2 }),
	    ({ MOUNTAIN_ITEMS,
		    "road", "The road leads down into a " +
    		"valley.",
    		"valley","The valley looks peaceful from up " +
    		"here.",
	    }),
    	({ }) }));

	add_desc("5", ({ ROAD_TYPE,
	    ({ "road outside Neraka",
	       "This is a long dusty road outside Neraka. It points like " +
	       "an arrow across the plains from the city in the south to " +
	       "the mountains in the north.",
	    }),
	    ({ "road","The road leads north into the mountains and south " +
		"into the city of Neraka.",
           ({"city","neraka"}),"Neraka lies to the south, lost in a " +
           "dusty haze.",
		"mountains", "The mountains are to the north.",
           "plains","The plains of Neraka stretch out on both sides of " +
           "the road.",
	    }),
	    ({ }) }));

	add_desc("6", ({ ROAD_TYPE,
	    ({ "road outside Sanction",
			"This is a road just east of Sanction. The " +
			"road heads into the mountains to the east, " +
			"and to the west down to the city, past an encampment.",
	    }),
		({ "road", "The road leads east into the mountains " +
		    "and west into the city of Sanction.",
		    ({"city","sanction"}),"Sanction lies to the west, " +
		    "barely discernible through a layer of fog and " +
		    "clouds.",
		    "mountains", "The mountains are to the east, the tall " +
		    "Taman Busuk mountain range. A road leads through the " +
		    "mountains.",
		    "encampment", "It would seem the encampment to the west " +
		    "belongs to the Blue Dragonarmy.",
		}),
	    ({ }) }));

	add_bound("S", SANCTION_LINK);
	add_bound("N", NERAKA_LINK);
	add_bound("C", CAVE_LINK);

	add_linev("S661");
	add_linev("N551");
	add_linev("12");
	add_linev("1433");
}
