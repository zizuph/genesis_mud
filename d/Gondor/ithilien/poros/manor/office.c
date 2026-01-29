/*
 *   /d/Gondor/ithilien/poros/manor/office.c
 *
 *   This is the room where the corsair captain assigns tasks for players.
 *
 *   Talisan,  January 1996
 *   Modifications log:  Tigerlily, April, 2006: moved cloning objects
 *         to reset_room
 *   Added teleportation blocks, Finwe January 2020
 */

#pragma strict_types

inherit "/d/Gondor/ithilien/poros/manor/manor.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

//    Prototypes:
void  reset_room();
string	exa_tapestry();
string	move_tapestry();
string	do_search(object tp, string arg);

//    Global Variables:
object   Guard1,
         Guard2,
         Captain;

object  chest;
object  door2;
int add_furnishings();

void
create_manor()
{
    set_area("office");
    set_extraline("The office is only sparsly furnished. A desk and chair "
      + "stand in the center of the small room, while a tapestry hangs "
      + "on the southern wall. Next to the desk, a wooden chest sits on "
      + "the floor. A doorway leads out of the room to the southeast.");

    add_item(({"office", "ground", "floor"}), BSN(
        "You determine this room is where the leader of the corsairs "
      + "spends most of his time making plans, and gives out orders "
      + "when he is not out personally leading in raids."));

    add_item(({"desk"}), BSN(
        "The desk is little more than a table being used to keep various "
      + "papers and charts on. A pen and inkwell also lie on top "
      + "of the desk."));
    add_item("chest", "The chest lies empty on its side.\n");

    add_item(({"papers", "reports", "orders", "manifests"}), BSN(
        "The papers seem to be various orders, reports, and manifests. "
      + "You find nothing of remarkable interest in any of them."));

    add_item(({"charts", "maps"}), BSN(
        "You can see the charts are for areas such as the Anduin and Poros "
      + "rivers, the Bay of Belfalas, and the Havens of Umbar. You notice "
      + "on one of the charts that the port town of Linhir, along the "
      + "coast of the Belfalas has been ominously circled ..."));

    add_item(({"pen", "ink", "inkwell"}), BSN(
        "The pen and inkwell are common writing tools."));

    add_item(({"chair"}), BSN(
        "The chair is wooden, and of standard make."));

    add_item(({"tapestry", "the tapestry"}), exa_tapestry);

    add_cmd_item(({"behind tapestry", "behind the tapestry"}),
	"move", move_tapestry);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_HIDE, 90);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 5);

    reset_room();
    add_furnishings();
}

string
exa_tapestry()
{
    if (TP->query_skill(SS_AWARENESS)>50)
      return BSN("The tapestry is made from fine black cloth and thread. "
      + "It depicts a scene from a great sea battle in which Castamir "
      + "and his followers are defeating the Gondorian Navy in on of "
      + "the many battles during the Kin-Strife. You notice the tapestry "
      + "flutter slightly.");

    else
      return BSN("The tapestry is made from fine black cloth and thread. It "
      + "depicts a scene from a great sea battle in which Castamir and "
      + "his followers are defeating the Gondorian navy in one of the "
      + "many battles during the Kin-Strife.");
}


public string
move_tapestry()
{
    object blocker;
    if ((objectp(blocker = Captain) &&
	 ENV(blocker) == TO) ||
	objectp(blocker = present("corsair guard", TO)))
    {
        TP->catch_msg(QCTNAME(blocker) + " stands between you "
              + "and the tapestry. You can't reach it!\n");
        return "";
    }
    write("When you move behind the the tapestry, you discover a hidden room!\n");
    TP->move_living("going behind the tapestry", POROS_DIR + "manor/secret");
      return "";
}

void
reset_room()
{

    if (!objectp(Guard1))
    {
      Guard1 = clone_object(POROS_DIR + "npcs/guard");
      Guard1->set_living_name("gaerhir_guard1");
      Guard1->arm_me();
      Guard1->move_living("down", TO);
    }

    if (!objectp(Guard2))
    {
      Guard2 = clone_object(POROS_DIR + "npcs/guard");
      Guard2->set_living_name("gaerhir_guard2");
      Guard2->arm_me();
      Guard2->move_living("down", TO);
    }


    if (!objectp(Captain))
    {
      Captain = clone_object(POROS_DIR + "npcs/captain");
      Captain->arm_me();
      Captain->move_living("down", TO);
    }

}

int
add_furnishings()
{
    object door;

/*
    chest = clone_object(POROS_DIR + "obj/chest_new");
    chest->move(TO);
*/
    door = clone_object(POROS_DIR + "obj/door2");
    door->move(TO);
}


/*
 * Function name:	do_search
 * Description	:	handle searching tapestry
 * Arguments	:	object tp	this player
 *		:	string		whatever the player searched
 * Return	:	msg to display to player
 */
public string
do_search(object tp, string arg)
{
    if (arg == "tapestry" ||
	arg == "the tapestry" ||
        arg == "behind tapestry" ||
	arg == "behind the tapestry")
    {
	return BSN("The tapestry seems to be concealing something. "+
	    "Perhaps you could move behind the tapestry ...");
    }
    return "";
}
