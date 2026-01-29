inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

int open;

void
create_room()
{
    ::create_room();
    INSIDE;
    add_prop(ROOM_I_LIGHT,0);
    set_short("Dead End");
    set_long("You are at a dead end of this dark dusty tunnel. The walls "+
    "are all made of rough rock, except south, which oddly seems to be "+
    "smoother than the rest. The air here smells strangely clean (for "+
    "goblins). Water drips down from the ceiling, forming a little "+
    "puddle on the ground.\n");
    add_item(({"walls"}),"The walls are all rough and rock, except for the "+
    "south one, which is strangely smooth...almost shiny.\n");
    add_item("south wall","You run your hands along this smooth wall, and "+
    "you notice a faint outline of a door in the center. Your light shines "+
    "off the smooth surface.\n");
    add_item("puddle","As you examine the pool of water, you notice "+
    "a small metal ring at the bottom.\n");
    add_item("ring","It is attached to the bottom of ground under the "+
    "water.\n");
    add_exit("/d/Kalad/common/wild/pass/goblin/g17","east",0,1,1);
}

void
init()
{
    ::init();
    AA(do_ring,pull);
}

int
do_ring(string str)
{
    if (!parse_command(str, ({}), "[the] [small] [metal] 'ring'"))
    {
        NF("Pull what?\n");
        return 0;
    }
    write("You pull on the ring.\n");
    say(QCTNAME(TP)+" pulls on something in the puddle.\n");
    set_alarm(2.0,0.0,"open_door");
    return 1;
}

void
open_door()
{
    if(!open)
    {
        tell_room(TO,"The south wall opens apart!\n");
        open = 1;
        add_exit(CPASS(goblin/g19),"south",0,1,1);
        call_other(CPASS(goblin/g19),"open_door");
        set_alarm(60.0,0.0,"close_door");
    }
}

void
close_door()
{
    if(open)
    {
        tell_room(TO,"The south wall closes.\n");
        open = 0;
        remove_exit("south");
        call_other(CPASS(goblin/g19),"close_door");
    }
}
