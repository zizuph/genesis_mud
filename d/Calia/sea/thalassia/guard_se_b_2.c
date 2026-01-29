
/* 	Thalassian Guard Barracks

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";


void
create_water_room()
{
    set_short("Guard tower armoury");
    set_long("You have entered the armoury of the guard "+
        "tower. This is where the guards of this place "+
        "store all of the armour and weapons they have "+
        "when they are not using them. In various racks "+
        "and cages around the room you see suits of armour "+
        "and weapons. To the north you see the entrance to "+
        "the stables.\n");
    add_item("stables","The stables are north from here. "+
        "Normally you could smell something or hear something "+
        "but since you are underwater, you can do neither here.\n");
    add_item(({"rack","racks","various racks"}),"The racks around "+
        "the room contain many weapons for use by the guards of "+
        "this guard house.\n");
    add_item("weapons","Upon closer inspection, the weapons in "+
        "the racks appear to be rusted and/or broken, apparently "+
        "not used for some time. They would be useless to anyone.\n");
    add_item(({"armours","suits of armour"}),"Upon closer inspection, "+
        "the suits of armour in the cages appear to be rusted "+
        "and/or broken, apparently not used for some time. They "+
        "would be useless to anyone.\n");
    add_item(({"cage","cages"}),"The cages around the room contain "+
        "many suits of armour for use by the guards of this guard "+
        "house.\n");

    add_swim_exit(THAL+"guard_se_b_4","north",0,1);
    add_swim_exit(THAL+"guard_se_b_1","east",0,1);
}
