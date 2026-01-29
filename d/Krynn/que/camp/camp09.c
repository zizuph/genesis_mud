/* Camp in the plains of Abanasinia
 * Aridor, 08/97
 *
 * Changed the barbarian chieftain quest to that the Aurak leader
 * always carry the needed paper, instead of just sometimes.
 * First fix by Hyde, then a fix to the fix by Cherek, January 2016
 *	                                         
 */

#include "local.h"

inherit CAMP_BASE

void
reset_camp_room()
{
    object ob,ob2;
    ob = P("leader_tent",TO);
    ob2 = P("tent",TO);
    if (ob2 && ob2 != ob)
      ob = ob2;
    if (!ob)
    {
	ob = clone_object(LEADER_TENT);
	ob->add_name("leader_tent");
	ob->move(TO,1);
    }
    if (!P("drac_leader",ob->query_tent_inside()))
    {
	ob = clone_object(DRAC_LEADER);
	ob->add_name("drac_leader");
	ob->set_aggressive(1);
	ob->set_color("red");
	all_inventory(ob)->set_color("red");
	clone_object(PAPER)->move(ob);
	ob->move_living("xx",TO);
	ob->command("set up tent");
	ob->command("enter tent");
    }
    if (!P("draconian_statue",TO))
    {
	ob = clone_object(DRAC_STATUE);
	ob->add_prop(OBJ_I_HIDE, 15 + random(15));
	ob->move(TO);
    }
}

void
create_camp_room()
{
    set_short("In a camp");
    set_long("This is the centre of an army camp. There are " +
	     "tents scattered about. One larger tent rises above the others " +
	     "in the middle.\n");
    add_item("tents","They look like standard army tents. One larger tent " +
	     "rises above the others in the middle.\n");
    add_item("larger tent","This must be the leader's tent.\n");
        
    add_exit("camp08","west","@@block@@");
    add_exit("camp12","south","@@block@@");
    add_exit("camp06","north","@@block@@");
    add_exit("camp10","east","@@block@@");

    set_auto_reset("tblwarkiri",random(4)+2);
    reset();
}

