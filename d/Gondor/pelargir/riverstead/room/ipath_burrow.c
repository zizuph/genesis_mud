/*
 *  NCAMP_ROOM + "ipath_burrow.c"
 *
 *  A burrow. Only newbies and wizards should ever see this place.
 *
 *  Last modified by Alto, 28 September 2002
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include <math.h>
#include "/d/Gondor/defs.h"
#include "../ncamp_defs.h"

inherit NCAMP_LIB + "ncamp_funcs.c";

public void        	create_gondor();
public string      	long_desc();
string			gem_types();

public void
create_gondor()
{
    set_short("inside a small burrow");
    set_long(&long_desc());

    add_item(({"room", "area", "surroundings", "place", "burrow", "den"}), 	long_desc);
    add_item(({"bed", "leaves", "old leaves"}), "A bed of old leaves rests "
        + "upon the floor. It must have kept a litter of fox cubs dry "
        + "and warm at one time.\n");
    add_item(({"floor", "ground"}), "The floor of the burrow is covered "
        + "with a bed of old leaves.\n");
    add_item(({"old bones", "bones", "bone", "old bone"}), "The old bones "
        + "are hollow and "
        + "pneumatized, suggesting they once belonged to various species "
        + "of small bird. Most likely their former owners fell prey to "
        + "the foxes inhabiting this den.\n");
    add_item(({"fur", "red fur"}), "Scattered throughout the leaves are "
        + "remnants of fur. The red colour suggests it once was attached "
        + "to a fox.\n");
    add_item(({"wall", "walls", "ceiling"}), "The walls and ceiling of the "
        + "burrow are made from the earth from which it was hollowed.\n");
    add_item(({"earth", "dirt"}), "As the burrow was dug into the earth, "
        + "you are unsurprised to see dirt everywhere.\n");
        
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_NO_TELEPORT,"That is not possible here.\n");

    add_exit(NCAMP_ROOM + "ipath2.c", "out");

    clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);

    reset_room();
}

string
gem_types() 
{
    string *gemtypes =
                 ({"agate", "amber", "amethyst", "beryl_red",
                   "chalcedony", "coral", "diamond", "emerald", "garnet", 
                   "jade", "opal", "pearl_black", "pearl", "peridot", 
                   "ruby", "sapphire", "topaz_yellow", "topaz", "moonstone"});
    return ONE_OF_LIST(gemtypes);
}

void
reset_room()
{
    switch (random(3))
    {
        case 0:
        case 1:
            break;
        case 2:
            setuid();
            seteuid(getuid());

            clone_object("/d/Genesis/gems/obj/" + gem_types())->move(TO);
            break;
        default:
            break;
    }
}

string
long_desc()
{
    return "Although it is cramped and dark, the little burrow is dry, "
        + "with a soft bed of old leaves upon the floor. Old bones and "
        + "red fur suggest this was once the den of a fox. The former "
        + "resident and her kin, however, are nowhere to be seen.\n";
}
