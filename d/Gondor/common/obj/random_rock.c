/*
 *	/d/Gondor/common/obj/random_rock.c
 *
 *	Copied from /d/Shire/common/obj/random_rock.c.
 *
 *	Some slight modifications.
 */
#pragma strict_types

inherit "/d/Shire/common/obj/rock";

#include <stdproperties.h>
#include <language.h>

#include "/d/Gondor/defs.h"

#define SIZES ({ "small", "ordinary", "fairly big", "big", "very big", })

public void
create_rock()
{
    int weight, il, rnd;

    rnd = random(10) + 1;
    weight = random(1000) + 1;
    weight *= rnd;

    il = weight / 1000;
    switch (il)
    {
    case 0..4:
	set_name("stone");
        add_name("rock");
	set_adj(SIZES[il]);
	set_short(SIZES[il] + " stone");
	break;
    case 5..9:
	set_name("rock");
        add_name("stone");
	add_adj(SIZES[il - 5]);
	set_short(SIZES[il - 5] + " rock");
	break;
    }
/*  Why write this? Let the player decide if it is useless.
 *  -Gorboth
    set_long("This is " + LANG_ADDART(short()) + ", often " +
	     "found in rocky areas, and totaly useless.\n");
*/
    set_long(BSN("This is " + LANG_ADDART(short()) + ", often"
      + " found in rocky areas."));

    add_prop(OBJ_I_WEIGHT, weight);
    add_prop(OBJ_I_VOLUME, weight * 1000 / (3600 + random(1800)));
    add_prop(OBJ_I_VALUE, 0);
}
