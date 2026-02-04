/* mound 21 */
/* janus 921111 */
/* 2017-09-20 Malus: Modified reset_room() to ensure quest NPC respawns */ 
/*
 * Lucius - Dec 2017: Fixed unchecked warrior bug growth.
 * Lucius - Jan 2021: Fixed reset and search.
 * 
 */
inherit "/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()

public int ITEMS = 4;

public void
reset_room()    { ITEMS = 4; }

public void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("egg chamber");
    set_long("This chamber is huge, about twenty times your size in "+
      "radius. A thick cloying acidic stench makes it difficult to "+
      "breathe in here. "+
      "Except from the stench this place is kept meticulous clean "+
      "by the worker ants. The walls are smooth and rounded so that "+
      "all the eggs lying here are kept safe. The worker ants in here "+
      "seem busy with keeping the eggs safe and clean, and the warrior "+
      "ants keep a watchful eye on everything. \n");

    add_item(({"ground","floor","walls"}),
      "The walls, floor and ceiling are warm to the touch. \n");
    add_item(({"room","debris"}),
      "There is a lot of debris lying around in this room. "+
      "The piles of debris might contain something useful.\n");

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_LIGHT,  0);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(JANUSDIR + "garden/hive/mound17","up",0,3);
    add_exit(JANUSDIR + "garden/hive/mound19","south",0,3);

    add_npc(JANUSDIR + "monsters/queen");
    add_npc(JANUSDIR + "monsters/wbug", 2);
    add_npc(JANUSDIR + "monsters/wwbug", 2);
}

public mixed
do_search()
{
    int i1 = TP->query_skill(SS_AWARENESS),
        i2 = i1 - random(15);

    if (!CAN_SEE_IN_ROOM(TP))
    {
	return "You are blind as a bat in the darkness, so you'd better " +
            "get some light if you want to search here. \n";
    }

    if (i2 > 0)
    {
	object ob;
	switch(ITEMS--)
	{
	case 4:
        {
            ob = clone_object(JANUSDIR + "garden/hgem");
            ob->move(environment(TP));
            return "You find a valuable gem. The bugs must have found it "+
                "while digging and building this hive.\n";
	}
	case 3:
        {
            ob = clone_object(JANUSDIR + "garden/qjelly");
            ob->move(environment(TP));
            return "Stuck to some garbage you find some red jelly"+
                " in a soft membrane.\n";
        }
        case 2:
        {
            ob = clone_object(JANUSDIR + "garden/potion");
            ob->move(environment(TP));
            return "You find a small bottle containing a strange fluid.\n";
        }
        case 1:
        {
            ob = clone_object(JANUSDIR + "garden/mandible");
            ob->move(environment(TP));
            return "You find a mandible from a warrior bug. It can probably "+
                "be used as a club.\n";
        }
	} // switch()
    }
    return "";
}
