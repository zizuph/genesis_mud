/*
 *	/d/Gondor/lebennin/sroad/sroad.c
 *
 *	The master for the road in south Lebennin from
 *	Pelargir upon Anduin to Linhir upon Gilrain
 *
 *	Olorin, June 1995
 */
#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";

#include <macros.h>

#include "/d/Gondor/defs.h"

#define CROPS	({ "wheat", "barley", "oats", })

void
create_road()
{
}

void
create_area_room()
{
    set_area("southern");
    set_areaname("Lebennin");
    set_land("Gondor");
    set_areatype(8);
    set_areadesc("field");
    set_grass("long green");

    create_road();

    remove_item("road");
    remove_item("ground");
    add_item(({"road", "ancient road", "ground", }), BSN(ONE_OF_LIST(
        ({ "This is an ancient road running from Pelargir upon "
      + "Anduin to Linhir upon Gilrain and Dol Amroth.",
        "The road is made from large flat stones. The handiwork "
      + "of the men of old can be seen in its level course and "
      + "sure flight.", 
        "The road is running across the fields of southern Lebennin "
      + "from Pelargir to Linhir in the east.", })) ));

    remove_item("field");
    add_item(({"field","fields"}), BSN( ONE_OF_LIST( ({
        "The fields on both sides of the road look as if they are "
      + "used for farming, but you cannot see any cattle.",
        VBFC_ME("exa_field"), })) ));
}

varargs void
add_anduin(string extra)
{
    string desc =
        "The road is running along the west bank of the river "
      + "Anduin. The Anduin is here close to its end and several "
      + "miles wide. Not far from here, it will reach the Mouths of "
      + "the Anduin, or the Ethir Anduin, where it divides into "
      + "many smaller river courses before it finally reaches "
      + "the Sea in the Bay of Belfalas.";

    if (strlen(extra))
        desc += (" " + extra);

    add_item(({"river", "stream", "river anduin", "anduin"}),
        BSN(desc));
}

string
exa_field()
{
    object  clock = find_object(CLOCK);
    string  desc = "",
            crop;

    switch (clock->query_season())
    {
        case "spring":
            desc += "The fields have been tilled recently and are "
                 +  "obviously newly sown.";
            break;
        case "summer":
            crop = ONE_OF_LIST(CROPS);
            desc += "The fields are used to grow different crops. "
                 +  "On the field next to the road, one can see "
                 +  crop+".";
            break;
        case "autumn":
            crop = ONE_OF_LIST(CROPS);
            desc += "The fields are full with ripe crops. Right next to "
                 +  "the road, there can be seen "+crop+" bending under "
                 +  "the weight of full ears.";
            break;
        case "winter":
            desc += "All the fields are harvested and lie barren for the "
                 +  "winter.";
            break;
        default:
            break;
    }
    return desc;
}

