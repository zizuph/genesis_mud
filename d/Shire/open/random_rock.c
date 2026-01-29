inherit "/d/Shire/common/obj/rock";

#include "defs.h"
#include <stdproperties.h>
#include <language.h>

#define SIZES ({ "small", "fairly big", "big", "very big", "heavy", \
		 "very heavy" })

create_rock()
{
    int weight, il, rnd;

    weight = 0;
    rnd = random(12) + 1;
    for (il = 0; il < rnd; il ++)
	weight += random(1000);

    il = weight / 1000;
    switch (il) {
    case 0..5:
	set_name("rock");
	set_adj(SIZES[il]);
	set_short(SIZES[il] + " rock");
	break;
    case 6..11:
	set_name("slab");
	set_adj("rock");
	add_adj(SIZES[il - 6]);
	set_short(SIZES[il - 6] + " slab of rock");
	break;
    }
    add_name("rock");
    set_long("This is " + LANG_ADDART(short()) + ", often " +
	     "found in rocky areas, and totaly useless.\n");

    add_prop(OBJ_I_WEIGHT, weight);
    add_prop(OBJ_I_VOLUME, weight * 1000 / (1600 + random(800)));
    add_prop(OBJ_I_VALUE, 0);
}
