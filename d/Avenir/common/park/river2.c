// file name: river2.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do: change the sille go_s function


inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"

/* Room 243 */

init()
{
        ::init();
        add_action("go_n","north");
        add_action("go_n","n");
        add_action("go_s","south");
        add_action("go_s","s");
        add_action("go_s","enter river");
        add_action("go_s","step into river");
}

create_room()
{
set_short("Near the river");
set_long("You stand on a tiny strip of dry land on the"
        +" bank of a rapidly flowing river. Tall stone cliffs rise"
        +" up all around you. The bank on which you stand continues to the"
        +" north. It may be possible to go further southward"
        +" by stepping into the shallows of the river.\n"
        +"There are two obvious exits: north, south.\n");

add_prop(ROOM_I_LIGHT,1); IN


add_item(({"water","river"}), "The river rushes"
        +" rapidly on, flowing from north to south.\n");
add_item(({"rock","stone","cliff","cliffs"}), "The sheer"
        +" faces of rocky cliffs rise up high into the sky. Only dim light"
        +" is able to reach down between them to where you stand.\n");

}

go_n()
{
        tell_room(PK+"river1",QCTNAME(this_player())+" arrives.\n");
        say(QCTNAME(this_player())+" leaves north.\n");
        this_player()->move_living("M",PK+"river1");
        return 1;
}

go_s()
{
        say(QCTNAME(this_player())+" steps into the river"
           +" and is swept away!\n");
        write("As you step into the cold water of the rushing"
           +" river, the current takes sudden hold. Your feet are"
           +" swept out from beneath you, and you find yourself heading"
           +" downstream, out of control! The high cliffs rush by all"
           +" around you, and as you begin to swallow water, you lose"
           +" consciousness. When you awaken, you are on a sandy shore at the"
           +" south end of the island.\n");
        this_player()->move_living("M",PK+"shore");
        return 1;
}

