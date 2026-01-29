/* the inside of the tent */

/* hmm, the idea is to hold people prisoner in here. Dunno if that makes
 * sense though. For now this is just an empty room. Write your own
 * tent inside room, please.
 */
#include "/d/Krynn/common/defs.h"

inherit R_FILE

void
create_krynn_room()
{
    set_short("Inside a large tent");
    set_long("You are inside a large tent.\n");
    INSIDE;
    NO_TIME;
}

public int
prevent_enter(object ob)
{
    if(ob->query_race_name()=="dragon" ||
       ob->query_race_name()=="horse" ||
       ob->query_race_name()=="wolf" ||
       ob->query_race_name()=="goat" ||
       ob->query_race_name()=="pony" ||
       ob->query_race_name()=="warhorse")
    {
	return 1;
    }
    return 0;
}

int
quit(string str)
{
    write("You can't quit the realms from inside the tent. You will " +
        "need to exit first.\n");
    return 1;
}

void
init()
{
    ADA("quit");
    ::init();
}