/* mound 19 */
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

    set_short("egg chamber");
    set_long("This large chamber serves as a hatching chamber for "+
	"the eggs that are ready to hatch. The air is quite warm and dry " +
	"in here, though quite permeated with the strong acrid smell. " +
	"There is almost no debris in here since the worker bugs keeps "+
	"this place clean from all foreign substances.\n");

    add_item(({"ground","floor","walls"}),
        "The walls, floor and ceiling are warm to the touch.\n");
    add_item(({"room","debris"}),
        "There is a lot of debris lying around in this room. "+
        "The piles of debris might contain something useful.\n");

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(JANUSDIR + "garden/hive/mound15","southeast",0,0);
    add_exit(JANUSDIR + "garden/hive/mound21","north",0,0);
    add_exit(JANUSDIR + "garden/hive/mound23","northwest",0,0);

    add_npc(JANUSDIR + "monsters/wbug");
    add_npc(JANUSDIR + "monsters/wwbug");
    add_npc(JANUSDIR + "monsters/hatchling", 4);
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
	    ob=clone_object(JANUSDIR + "garden/hgem");
	    ob->move(environment(TP));
	    return "You find a valuable gem. The bugs must have found it "+
	      "while digging and building this hive.\n";
	}
        case 2:
        {
	    ob=clone_object(JANUSDIR + "garden/potion");
	    ob->move(environment(TP));
	    return "You find a small bottle containing a strange fluid.\n";
	}
        case 1:
        {
	    ob=clone_object(JANUSDIR + "garden/mandible");
	    ob->move(environment(TP));
	    return "You find a mandible from a warrior bug. It can probably "+
	      "be used as a club.\n";
	}
        } // switch()
    }
    return "";
}
