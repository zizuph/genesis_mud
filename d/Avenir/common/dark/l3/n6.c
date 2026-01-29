// file name: ~Avenir/common/dark/l3/n6.c
// creator(s):
// revision history:
// purpopse:
// note:
//   - exit to north does not always exist any more. it's existance depends
//     upon loading time setting and wizard can close exit at will.
//     (altar is intendeed to be a part of some quests, so this room
//     provides an easy way to close this area); to prevent unloading
//     this room from memory redefined function clean_up()
//      -=Denis /Jul 94
// bug(s):
// to-do:

#include "l3_defs.h"
inherit L3_ROOM;
#include "/d/Avenir/common/dark/dark.h"

#define GUARD_EXIT 0
// Set this to 1 if you want to forbid passing to north.

create_room()
{

    set_short("Dark hallway");
    set_long(
"You are in a smooth hallway leading from north to south. The walls "+
"are of a beautiful white stone webbed with tiny cracks. There is "+
"a hole in the eastern part of the wall, where it looks like it "+
"has been broken through to reveal a tunnel to the northeast. From "+
"the north comes a hot, dry wind, which mixes with a humid breeze "+
"from the northeast, making the air here hot and steamy.\n");

        AI(({"wall","walls"}),"The walls, constructed ages ago, are "
+"of a smooth stone that does not seem to be indiginous to the caverns. "
+"It is a white rock with swirling, light blue patterns running through "
+"it. The walls have been worn with the passage of time, and cracks have "
+"appeared in the once perfectly smooth surface. The eastern wall has "
+"been smashed through to reveal a tunnel running to the northeast.\n");

        AI(({"crack","cracks"}),"The beautiful white walls are covered "
+"with tiny webs of cracks all through them, possibly due to some "
+"movement of the land ages ago.\n");

        AI(("floor"),"The floor is smooth, and is carved out of the "
+"living rock itself, unlike the walls. It is quite clean, from the "
+"winds that blow down the tunnels.\n");

    add_exit("/d/Avenir/common/dark/l3/center","south",0);
    add_exit("/d/Avenir/common/dark/l3/n7","northeast",0);

    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(STATUES_IN_ROOM,random(2)+1);

    set_alarm(5.0,0.0,"reset_room");

    if(GUARD_EXIT)
        close_exit();
    else
        open_exit();
}

/*-----[ Open exit to the north ]-----*/
open_exit()
{
    remove_my_desc(TO);
    add_exit("/d/Avenir/common/dark/l3/entry","north",0);
}

/*-----[ Close exit to the north ]-----*/
close_exit()
{
    remove_exit("north");
    add_my_desc("The exit to the north is blocked by two enormous boulders "+
                "and many stones.\n",TO);
}

/*-----[ This room don't need to be removed from memory ]-----*/
public int
clean_up()
{
}

