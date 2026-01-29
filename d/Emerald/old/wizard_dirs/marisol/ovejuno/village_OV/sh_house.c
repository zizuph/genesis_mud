/* Shepherd house in the village of Re Albi
 * Coded by Marisol (05/21/98)
 * Modified by Marisol (08/04/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

inherit "/d/Emerald/std/room";
#include "/d/Emerald/sys/macros.h";
#include <stdproperties.h>
#include "defs.h"
#define SHDOOR DOORS + "sh_out"

object shdoor;


nomask void
create_emerald_room()
{

    set_short("A shepherd's house");
    set_long("There is no one in the house right now, but "+
        "seems that the owner is not too far away because the house "+
        "is open and a fire is burning in the hearth. This seems "+
        "like the permanent home of a shepherd in Ovejuno, when "+
        "using the communal pastures. A wooden table is at the "+
        "center of the room, surround by straw chairs. To the far "+
        "end of the room, there is a small kitchen with a sink. To "+
        "the opposite side of the kitchen, resting in the floor is "+
        "a small pallet. This is a poor house but clean and "+
        "neat.\n");

    add_item("hearth",
        "Is just a hole in the floor of the house. It is burning "+
        "now. The fire was made with wooden coals and sheep dugs. "+
        "Two iron forks hold a metal rod over the hole. In the "+
        "rod, two metal hooks hangs on it holding a cooking pot "+
        "over the fire. The smoke escape from a hole in the "+
        "thatch celling.\n");

    add_item("table", 
        "This is a roughly made wooden table.\n");

    add_item(({"straw chairs", "chairs"}),
        "These are very ordinary straw chairs, with a wooden "+
        "frame and dry straw for padding.\n");

    add_item("pallet",
        "This is a small bed filled with straw that rest in the "+
        "floor. Doesn't seem like a soft place to sleep.\n");

    add_item(({"kitchen", "sink"}),
        "This is a very small kitchen, with a wooden counter to "+
        "cut vegetables and meat and a smaller sink to soak dirty "+
        "dishes.\n");

    add_item(({"thatch celling", "celling"}),
        "A rustic thatch celling. It seems to need some repairs, "+
        "you can see the daylight through the many small holes in "+
        "it. A big hole is over the hearth where the smoke from the "+
        "fire escapes.\n");

    add_item("floor",
        "The floor is hard-packed earth.\n");

    shdoor= clone_object(SHDOOR);
    shdoor->move(TO);

}
