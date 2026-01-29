/*
 * Base file for Orc Tents
 * By Finwe, July 2000
 */

inherit "/d/Shire/std/room/room_tell";
inherit "/d/Shire/std/room.c";

#include "/d/Shire/sys/defs.h"
#include "local.h"
//#include "/d/Shire/common/bree/orc_camp/camp.h"
//#include "/d/Shire/orcmaker/orcmaker.h"

#include <stdproperties.h>
#include <macros.h>
#include <language.h>

void
create_tent_room()
{
}

create_shire_room()
{
    set_short("Inside an orc tent");
    set_long("This tent is even dirtier than the camp outside " +
        "and full of smelly things. It is dark even though some " +
        "light filters in through the seems and through the open " +
        "tent flap. ");
    add_item(({"tent","floor","ground","walls","wall"}),
        "This tent is made of some type of skin, and knowing orcs, " +
        "it could be anything. The floor is dirt and the " +
        "walls are notched with small holes, the size and shape of "+
        "arrowheads.\n");
    add_item(({"camp","outside"}), 
        "The camp is outside, but you can't see it from in here.\n");
    add_item(({"debris", "piles of debris"}),
        "Nothing of interest is in the piles of debris. It consists " +
        "of garbage and other smelly sundry items.\n");
    add_item(({"bones","bone","pile"}), 
        "These bones have been gnawed beyond recognition. They are " +
        "white and pitted with teeth marks.\n");


    add_prop(ROOM_I_INSIDE,1);

    // no horsies in the tent. The tents are messy enough without them.
    add_prop(ROOM_I_ALLOW_STEED, 0);
    enable_reset();
    add_stuff();
    reset_shire_room();
    create_tent_room();

}


void slavebed()
{
    add_item(({"bed","slave bed","beds"}),
        "The beds of the slaves who live here are the only things " +
        "kept meticulously clean and tidy. They are hollowed-out " +
        "places in the ground and don't look too comfortable.\n");
}

void guardbed()
{   
     add_item(({"bed","guard bed","beds","cots"}),
        "The guard's cots are in some disarray. Some are neat and " +
        "tidy, others are dirty.\n");
}

void warriorbed() 
{
    add_item(({"bed","warrior bed","beds"}),
        "These are actual, real-live beds. They are sprinkled with " +
        "dust as though they were just moved here, and probably on " +
        "the backs of their slaves. They are quite beat up, but " +
        "they look comfortable.\n");
}

void scoutbed()
{
     add_item(({"bed","scout bed","beds"}),
        "These are the beds for the scouts of the army. They are in " +
        "close order formation and look hardly slept in, as a scout " +
        "must be ready at all hours.\n");
}

void kingbed()
{
     add_item(({"bed","king bed", "large bed"}),
        "This is a bed fit for a king, an orc king, that is. It is " +
        "large as if it was built for someone, or something, large. " +
        "The quality is too good to be made by the orcs as it is " +
        "heavy and solid looking.\n");
}

void kitchen()
{
    add_item(({"pots","pans","pot","pan","utensils"}),
        "There are several dirty pots and pans scattered over the " +
        "floor, some of the utensils are red from rust, and a few " +
        "pots have spiderwebs or fungi growing out of them.\n");
}

void furniture()
{
    add_item(({"furniture"}),
        "The furniture is is poor condition. Some of it looks like " +
        "it was once nicely constructed but now it is banged up and " +
        "looks pretty bad. Other pieces look like they were crudely " +
        "constructed and barely stay together.\n");
}

void chairs()
{
    add_item("chairs",
        "They are all scattered about and some overturned in a corner " +
        "of the tent. Some are crudely constructed, and others look " +
        "like they were stolen during one of many orc raids.\n");
}

void table()
{
    add_item("table",
        "The table is long and made of planks. It is stained with " +
        "what looks like blood and who knows what else. Claw marks " +
        "scuff the surface and the edges are splintered, broken, and " +
        "jagged. Small holes dot the surface, like those made from " +
        "knifes or arrows.\n");
}


void bedroll()
{
    add_item(({"bedroll","bedrolls","bed roll"}),
        "The bedrolls are dirty and lie in a pile in one corner. " +
        "They smell and look disgusting.\n");
}

void camp()
{
    add_item(({"camp","outside"}), 
        "The camp is outside, but you can't see it from in here.\n");
}

void
add_stuff()
{
//   object orcleader, orc1, orc2;
}
