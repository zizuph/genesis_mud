#include "defs.h"

CONSTRUCT_ROOM {
    set_short("You are in King Durin's secret weapon chamber");
    set_long("You are in King Durin's secret weapon chamber. This is where "+
	     "the King must have hidden his most secret things. The room is "+
	     "very simple, almost too simple for a king, but this is "+
	     "obviously due to his interest in keeping this room a secret.\n"+
	     "There is a large sign here.\n"
    );
    add_item(({"room","walls","floor","roof"}),"You see nothing special.");
    add_item("sign", "Perhaps read it?");
    EXIT("throne","up");
    TO->make_things();
}

make_things()
{
/*  if (!present("_durins_axe_"))
	clone_object(MORIA_WEP+"durinaxe")->move(this_object());
    if (!present("plate"))
	clone_object(MORIA_ARM+"durplate")->move(this_object());
    if (!present("shield"))
	clone_object(MORIA_ARM+"durshield")->move(this_object()); */
}

RESET_ROOM {
    if (random(5))
	 return;
    make_things();
}

init()
{
    ::init();
    add_action("do_read","read");
}

int
do_read(string str)
{
    if (str!="sign")
	return notify_fail("Read what?\n");
    write("The sign says:\n"+
	  "    Death to those who steal Durin's Axe without permission!!!\n");
    say(QCTNAME(TP)+" reads the sign.\n");
    return 1;
}
