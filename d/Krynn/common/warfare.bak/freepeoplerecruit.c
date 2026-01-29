
#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/std/room";
inherit RECRUIT_BASE


void
reset_krynn_room()
{
    do_automatic_recruit();
}

void
create_krynn_room()
{
    setuid();
    seteuid(getuid());
    set_short("Free People Recruit Room");
    set_long("This room is the Recruiting Room of the Free People. However, it " +
	     "is not accessible to any players. The workings are such that this " +
	     "room automatically recruits new guards for the 'Free People' as necessary. " +
	     "It is possible to have funding rooms in specific areas which support " +
	     "the Free People and which simply transfers the money to this room.\n");

    set_army("Free People");
    set_automatic_recruit();

    set_alarm(1.0,0.0,reset);
}

init()
{
    init_recruit_fund();
    ::init();
}
