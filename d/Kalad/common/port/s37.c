#include "default.h"
inherit PORT_ROOM;

object ob1;

void
create_port_room()
{
    add_prop(ROOM_I_INSIDE,1);
    set_short("Watchmaker Shop");
    set_long("You've entered a quaint little shop which consists of "+
      "just this one room. The hardwood walls have been whitewashed and the "+
      "the floor covered with a thick rug. On the western and eastern sides "+
      "of the room are long glass cases. In the south is a wooden counter, "+
      "above which is a sign.\n");
    add_item(({"hardwood walls","walls","hardwood wall","wall"}),"The "+
      "sides of the room have been painted a brilliant white in color. Not "+
      "a single smudge mark is visible on them.\n");
    add_item(({"floor","thick rug","rug"}),"The floor of the room is "+
      "totally covered by a plain red carpet.\n");
    add_item(({"long glass cases","long glass case","long cases","glass cases","long case","glass case","cases","case"}),
      "Large rectangular glass-covered viewing cases. Inside are several "+
      "gold watches.\n");
    add_item(({"wooden counter","counter"}),"An ordinary and quite plain "+
      "counter.\n");
    add_item(({"sign"}),"A wooden sign that hangs from the ceiling above "+
      "the counter. There is writing on it.\n");
    add_item(({"ceiling"}),"It has been painted a brilliant white color.\n");
    add_exit(PORT + "s24", "north");
    reset_room();
}

reset_room()
{
    if(!ob1)
    {
	ob1 = clone_object(PORT + "npc/watchmaker");
	ob1 -> move_living("xxx", TO);
    }

}

init()
{
    ::init();
    AA(read_sign,read);
    AA(touch_cases,touch);
}

string
sign()
{
    return "\n"+
    "                *****************************\n"+
    "                [ If I am present, then you ]\n"+
    "                [ may buy watches from me.  ]\n"+
    "                [               -Goldblum-  ]\n"+
    "                [ ~~~~~~~~~~~~~~~~~~~~~~~~~ ]\n"+
    "                [ DO NOT TOUCH THE CASES!!! ]\n"+
    "                [___________________________]\n"+
    "                *****************************\n";
}

int
touch_cases(string str)
{
    if(!str || str != "case")
	if(!str ||str != "cases")
	{
	    notify_fail("Touch what?\n");
	    return 0;
	}

    write("You discreetly touch one of the glass cases.\n");
    say(QCTNAME(TP) + " tries to be discreet and touches one of the cases.\n");
    set_alarm(3.0,0.0,"kick_out");
    return 1;
}

void
kick_out()
{
    write("A big bouncer appears from nowhere and kicks you out of the shop!\n");
    say("A big bouncer appears from nowhere and kicks " + QCTNAME(TP) + " out of the shop!\n");
    TP->command("n");
    return;
}

