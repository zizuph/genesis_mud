/* This file is /d/Gondor/olorin/farm/farm/stable2.c       */
/* It belongs to a small farm in the Ered Nimrais          */	
/* Olorin, Nov 1992                                        */

inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

static object gate;

void
move_east(object ob)
{
    if(ob->query_prop("_rohan_horn_quest_start"))
    {
	ob->catch_msg(BS("The horrible stench inside the stable makes you sick. "+
	    "Only with a tremendous effort are you able to fight the impulse "+
	    "to flee at once.\n"));
    }
    else if (ob->query_wiz_level())
    {
	ob->catch_msg(BS("The horrible stench inside the stable makes you sick. "+
	    "Only the discipline of a wizard enables you to resist the impulse "+
	    "to flee at once.\n"));
    }
    else
    {
    if(objectp(present(ob)))
    {
	    if (!objectp(gate) ||
	    gate->query_open())
	        {
	        ob->catch_msg("The horrible stench inside the stable makes you sick, "+
	        "and you run out again.\n");
	         }
	    else
	         {
	         gate->do_open_door();
	        tell_room(TO, QCTNAME(ob) + " flings open the gate.\n", ob);
	        (gate->query_other_door())->do_open_door("The stable gate opens.\n");
	        ob->catch_msg("The horrible stench inside the stable makes you sick; "+
	        "you fling the gate open and run out again.\n");
	         }
	
	    
	    ob->move_living("out",FARM_DIR + "farm/yard1");
	}
    }
}  

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if ( living(ob))
    {
	set_alarm(1.0, 0.0, &move_east(ob));
    }
}

void
create_room()
{
    set_short("A stable");
    set_long("You are in a stable for horses. But there are no "
	+ "horses here. All you can see are human corpses. The " 
	+ "farmer's family obviously tried to defend the horses. " 
	+ "Nothing is alive here. The smell of death makes you sick.\n");
    add_exit(FARM_DIR + "farm/yard1", "east", 0);
    add_item("corpses",
        "The whole family died here. Some have weapons in their hands, " +
        "but there is no doubt all of them are dead. " +
        "There is one corpse of a dunlending " +
        "lying among the other corpses.\n");
    (gate = clone_object(FARM_DIR + "farm/stable2gate"))->move(TO);
    clone_object(FARM_DIR + "farm/trapdoor1")->move(TO);

    add_prop(ROOM_I_INSIDE, 1);
}


int
sunrise()
{
    tell_room(TO, "The sun rises in Gondor and Middle-earth.\n");
    return 1;
}

int
sunset()
{
    tell_room(TO, "The sun sets in Gondor and Middle-earth.\n");
    return 1;
}
