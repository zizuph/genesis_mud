// file name: enterlab.c
// creator(s): Farlong
// last update: Ilyian (8 March, 1995)
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "park.h"


init()
{
        ::init();
        add_action("thruwall","push");
}

create_room()
{
set_short("End of path");
set_long("You stand at the end of a short dirt path, bordered "
       +"on both sides by crumbling stone walls. The path ends "
       +"in a wall of vines and vegetation, and back west you can "
       +"make out a path that runs north to south. The air is "
       +"perfectly still here, no sound breaks the silence.\n");

AE(PK+"s_path5","west",0);

add_prop(ROOM_I_LIGHT,1);IN

add_item(({"wall","east","vegetation","plants"}),"This path is "
       +"bordered on both sides by a crumbling stone wall covered "
       +"in vines. It comes to a dead end at a wall of vegetation "
       +"that has been inexpliciably constructed. The wall seems "
       +"quite thin, though, so that it might be possible to push "
       +"your way through.\n");

STDEPATH


}

thruwall(string str)
{
        if ((str=="wall")||(str=="through wall")||(str=="east")||

          (str=="thru wall") || (str == "east wall"))
                {
                write("You move along the eastern wall"
                        +" of vegetation, carefully pushing on it. Suddenly,"
                        +" it gives way beneath your hands, and you"
                        +" fall through.\n");
                say(QCTNAME(this_player())+ " pushes on"
                        +" the eastern wall, and suddenly falls"
                        +" through!\n");
     TP->move_living("M", PK + "glade");
                return 1;
                }
}
