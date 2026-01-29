/*
 * This is a boulder that will occasionally fall into the bottom of the
 * ravine for ogres to use to make knives.
 * 
 * Created August 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Shire/common/obj/rock";

#include <stdproperties.h>
#include <language.h>

#include "/d/Emerald/blackwall/delrimmon/defs.h"

public void
create_rock()
{
    int weight, il, rnd;

    rnd = random(10) + 1;
    weight = random(200) + 800;
    weight *= rnd;

    il = weight / 1000;

    set_name("_del_rimmon_stone");

    set_name("boulder");
    add_name( ({ "stone", "rock", "boulder" }) );

    set_long(BSN("This is " + short() + ", often"
      + " found in rocky areas."));

    add_prop(OBJ_I_WEIGHT, weight);
    add_prop(OBJ_I_VOLUME, weight * 1000 / (3600 + random(1800)));
    add_prop(OBJ_I_VALUE, 0);
}
