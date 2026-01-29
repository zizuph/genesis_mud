inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"

/* Sarr */

void
create_room()
{
    ::create_room();
    set_short("Guild Hall");
    set_long("\n   The stone corridor ends here. In front of you, you see "+
    "a large bush covering a section the wall. Back to the north, is "+
    "the guild. Sunlight pokes through the cracks in the bush.\n\n");
    INSIDE;
    add_exit(FANG_DIR(rooms/hall2),"north",0,-1);
    add_item("bush","It seems to block a hole through the other side, "+
    "perhaps you can enter it?\n");
}

void
init()
{
    ::init();
    AA(do_enter,enter);
}

int
do_enter(string str)
{
    NF("Enter what?\n");
    if(str != "bush")
        return 0;
    write("You move aside the bush, and go down a hole.\n\n");
    say(QCTNAME(TP)+" moves aside the bush and goes down a hole.\n");
    TP->move_living("M",FANG_DIR(rooms/hole),1,1);
    set_alarm(5.0,0.0,"do_la");
    return 1;
}

void
do_la()
{
   write("You move further through the tunnel, till you hop out "+
   "of some bushes.\n");
   set_alarm(2.0,0.0,"do_move");
}

void
do_move()
{
    TP->move_living("M",CPASS(w14));
    tell_room(E(TP),QCTNAME(TP)+" pops out of some bushes.\n",TP);
    TP->command("fgrin");
}


