inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <const.h>
#include <macros.h>
#include "../garden.h"
#include <stdproperties.h>

static object store_cont;

void create_plant() { }

nomask void create_creature()
{
    set_gender(G_NEUTER);
    set_race_name("plant");
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop("_live_i_no_blood", 1);  // prop for vamps
  
    set_act_time(5);
  
    setuid();
    seteuid(getuid());
  
    if (store_cont = clone_object("/std/container"))
    {
    	store_cont->add_prop(CONT_I_MAX_VOLUME, 1000000);
    	store_cont->add_prop(CONT_I_MAX_WEIGHT, 1000000);
    }
  
    create_plant();
}

object make_corpse()
{
    return clone_object(POISON_GARDEN_OBJ + "plant_corpse");
}

void get_it(object ob)
{
    if (!store_cont || !present(ob, environment() ||
	!CAN_SEE(this_object(), ob) || !CAN_SEE_IN_ROOM(this_object()) || 
	ob->move(store_cont)))
    {  
        return;
    }
  
    tell_room(environment(),
	({ query_name() + " reaches out with its leaves.\n",
	   "The " + query_nonmet_name() + " reaches out with its leaves.\n",
	   ""
	}), this_object(), this_object());
}


void pick_it_up(object ob)
{
    if (!store_cont || !ob)
    {
        return;
    }
  
    set_alarm(itof(random(3) + 1), 0.0, &get_it(ob));
}
 
string get_stuff()
{
    return "get all";
}

int query_plant_base() { return 1; }
