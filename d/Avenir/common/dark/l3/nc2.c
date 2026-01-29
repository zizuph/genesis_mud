
// file name: ~Avenir/common/dark/l3/nc2.c
// creator(s):
// revision history:
// purpose: Provides (sometimes) player with piece of source for ghost quest
//          by 'exa crack'
//    I've taken out the exa_fun until the quest can be finished
//            -Ilyian, 1 May, 1995
//        May 14, put back in the exa_crack function   -I.
// bug(s):
// to-do:

#include "l3_defs.h"
inherit "/std/room";
inherit SOURCE_CHECKER;
#include "/d/Avenir/common/dark/dark.h"

create_room()
{
    set_short("Tunnel ending");
    set_long(
"You are at dead-end in the tunnels. The floor is covered with dust, "+
"with no traces of the tunnel inhabitants. The place looks quite "+
"safe and rarely visited. The walls are of brown rock and are in rather "+
"bad condition, being marred by cracks.\n");

    add_item( ({"wall","walls"}),
             "The walls are of brown rock and are in rather bad condition.\n"+
             "There are several cracks on the walls.\n");
    add_item( ({"crack","cracks"}),
             "@@exa_fun");

    add_exit("/d/Avenir/common/dark/l3/n5","east",0);

    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
    can_contain_source=1;
}

string exa_fun()
{
    if(find_source(TP,1))
     return "Inside one of the cracks you find a small glowing crystal.\n"+
            "You get it, clean the dust from it and put in your pocket.\n";
    else
        return "There is nothing of interest about them, just small "+
               "cracks in the old tunnel wall.\n";
}

