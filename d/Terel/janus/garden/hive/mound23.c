/* mound 23 */
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

public int ITEMS = 3;

public void
reset_room()    { ITEMS = 3; }

public void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("dump");
    set_long("This small room must be used as a dump for the refuse "+
	"that the bugs produce. The smell in here is almost overwhelming. "+
	"there are large piles of debris, consisting of skeletons, trash and"+
	" more recent refuse.\n");

    add_item(({"ground","floor","walls"}),
        "The walls, floor and ceiling are warm to the touch.\n");
    add_item(({"room","debris"}),
        "There is a lot of debris lying around in this room. "+
        "The piles of debris might contain something useful.\n");

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(JANUSDIR + "garden/hive/mound19","southeast",0,3);

    add_npc(JANUSDIR + "monsters/wbug");
    add_npc(JANUSDIR + "monsters/wwbug");
}

public string
do_search()
{
    int i1 = TP->query_skill(SS_AWARENESS),
        i2 = i1 - random(15);

    if (!CAN_SEE_IN_ROOM(TP))
    {
	return "You are blind as a bat in the darkness, so you'd better " +
	  "get some light if you want to search here.\n";
    }

    if (i2 > 0)
    {
        object ob;
        switch(ITEMS--)
        {
        case 3:
        {
	    ob=clone_object(JANUSDIR + "garden/qjelly");
	    ob->move(environment(TP));
	    return "Stuck to some garbage you find some red jelly"+
	      " in a soft membrane.\n";
	}
        case 1:
        {
	    ob=clone_object(JANUSDIR + "garden/mandible");
	    ob->move(environment(TP));
	    return "You find the remains of a bug.\n";
	}
        case 2:
        {
	    ob=clone_object(JANUSDIR + "garden/potion");
	    ob->move(environment(TP));
	    return "You find a small bottle containing a strange fluid.\n";
	}
        } // switch()
    }
    return "";
}
