/* A village fountain in the village of Ovejuno in Emerald 
 * Coded by Marisol (08/18/98) Copyright (c) Marisol Ramos 1998 */

#pragma save_binary

inherit "/d/Emerald/std/room.c";
#include "/sys/macros.h";
#include "/d/Emerald/sys/macros.h"
#include "/d/Emerald/lib/room_tell.c"
#include "defs.h"
#include <stdproperties.h>
#include "/d/Emerald/marisol/ovejuno/village_OV/vtells.h"

nomask void
create_emerald_room()
{
    int i;

    set_short("A village fountain");
    set_long("This is the village's fountain that serves both "+
        "human and sheep in Ovejuno. The fountain is a little "+
        "apart from the main dwellings, so the sheep can water "+
        "without disturbing the villagers and viceverce. Two "+
        "well-beaten trails go to the south and to the northwest "+
        "of the fountain.\n");

    add_item("fountain",
        "The fountain is quite simple but with a efective design. "+
        "Grey stone was carved to create a round basin where "+
        "water is poured from a center tower in the form of a "+
        "young shepherd carrying a jug. The water pours down "+
        "from the jub to fill the basin.\n");

    add_item(({"trail", "trails"}),
        "Well-beaten earth trails go to the village and the pastures "+
        "from here. They seem to be used a lot.\n");


    add_item("basin",
        "A grey stone round basin. It is carved into the ground. "+
        "It is full of cool water that comes from a jug that is hold "+
        "by a statue of a young shepherd.\n");

    add_item(({"statue", "young shepherd", "shepherd"}),
        "This is a statue of a young shepherd carrying a jug full of "+
        "water, that is poured down to the round stone basin. The "+
        "statue features are rough and without any special art as "+
        "elvish mind will like, but is pretty in a primitive way "+
        "as human art is in this world.\n");

    add_prop(OBJ_I_CONTAIN_WATER,1);

    set_tell_time(90);
    for (i = 0; i < 4; i++)
    {
     add_tell(VTELLS[random(sizeof(VTELLS))]);
    }

add_exit("/d/Emerald/marisol/ovejuno/village_OV/village_ov06.c", "south");
add_exit("/d/Emerald/marisol/ovejuno/village_OV/pastures/pastures02", "northwest");



}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
     start_room_tells();
    }
}

int

drink_it(string str)
{
    if ((str == "water") || (str == "water from basin"))
    {

    if(!this_player()->drink_soft(500))
    {
        write("You are too full to drink any more water.\n");
        return 1;
    }

        write("You take a drink of the earthy-tasting water. "+
       "You feel refreshed.\n");

        say(QCTNAME(TP) + "drink some water from the basin.\n");
       return 1;
    }

        notify_fail("Drink what?\n");
        return 0;
}

void
init()
{

    ::init();          
    add_action(drink_it, "drink");

}
     
