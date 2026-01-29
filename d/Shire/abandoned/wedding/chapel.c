/*
 *  Wedding chapel
 *					Tricky, Dec 1992
 */
inherit "/std/room";

#include "/sys/stdproperties.h"

int in_progress;	/* Is there a wedding in progress? */

void
create_room()
{
    set_short("Wedding chapel");
    set_long("@@my_long");

    add_exit("/d/Shire/tricky/workroom","out");

    add_prop(ROOM_I_INSIDE, 1);

    /* Let's keep this chapel peaceful */
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_I_NO_STEAL, 1);
}

string
my_long()
{
    string str;

    str = "You are inside a bright and beautiful white chapel that "
	+ "serves a wedding chapel. Light from outside is refracted by "
	+ "the magnificent glass dome in the roof. There are some benches "
	+ "to sit on before the altar that stands in the back of the "
	+ "chapel.";

    if (in_progress)
    {
	str += " There is a wedding in progress at the moment.";
    }
    return break_string(str + "\n", 70);
}
