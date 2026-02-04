/* mound 3 */
/* janus 921111 */
/*
 * Lucius - Jan 2021
 *    Cleaned up and modernized.
 */
inherit "/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()

public int ITEMS = 2;

public void
reset_room()    { ITEMS = 2; }

public void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("guard chamber");
    set_long("The tunnel widens here to a large chamber. You can feel "+
	"fresh air blowing from the south exit. The air coming from "+
	"the north and northeast tunnels has a heavy acrid odour "+
	"to it.\n");

    add_item(({"ground","floor","walls"}),
        "The walls, floor and ceiling are warm to the touch.\n");

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(JANUSDIR + "garden/hive/mound4","north",0,0);
    add_exit(JANUSDIR + "garden/hive/mound5","northeast",0,0);
    add_exit(JANUSDIR + "garden/hive/mound2","south",0,0);

    add_npc(JANUSDIR + "monsters/wwbug", 2);
}

public string
do_search()
{
    int i1 = TP->query_skill(SS_AWARENESS),
        i2 = i1 - random(15);

    if (!CAN_SEE_IN_ROOM(TP))
    {
	return "You are blind as a bat in the darkness, so you'd better " +
	  "get some light if you want to search here. \n";
    }

    if (ITEMS > 0 && i2 > 0)
    {
	object ob = clone_object(JANUSDIR + "garden/gem");
	ob->move(environment(TP));
	ITEMS--;
	return "Hidden under some slime you find a valuable stone.\n";
    }
    return "Maybe you should train your observational skills.\n";
}
