#include "../ctower.h"

inherit "/std/object";
inherit (CTOWER_OBJ + "ctower_obj_base");

#include <tasks.h>
#include <ss_types.h>

#define MANA_COST 50

int invoke_skill;
string gem_elem;

void
reset_object()
{
    reset_ctower_object();
}

void invoke_msgs() { }

void
config_gem(string elem, int skill)
{
    gem_elem = elem;
    invoke_skill = skill;

    add_name(elem + "_gem");
}

string
query_element()
{
    return gem_elem;
}

int
invoke(string str)
{
    object obj, *obs;
    int mod;
   
    notify_fail("Invoke what?\n");
    if (!str)
    {
      return 0;
    }
  
    if (parse_command(str, this_player(), " [the] %o ", obj))
    {
	if (obj == this_object()) 
	{
	    if (this_player()->query_mana() < MANA_COST)
	    {
                invoke_msgs();
                return 1;
	    }

            this_player()->add_mana(-MANA_COST);

            mod = 20 - this_player()->query_skill(invoke_skill);
            mod = ((mod > 0) ? mod * mod * mod : 0);

	    if (this_player()->resolve_task(TASK_ROUTINE + mod,
		({ SKILL_AVG, TS_INT, TS_WIS, SKILL_END,
                   SKILL_AVG, SS_SPELLCRAFT, invoke_skill, SKILL_END })) < 0)
	    {
                invoke_msgs();
                return 1;
	    }
    
       	    write("You invoke the power of the gem...\n");

	    obs = ({ environment(this_player()) });
            obs += all_inventory(obs[0]);
       
            if (!sizeof(call_other(obs, "invoke_" + gem_elem) - ({ 0 })))
	    {
		invoke_msgs();
	    }
	
	    return 1;
	}
    }
   
    return 0;
}

void
create_gem()
{
}

nomask void
create_object()
{
    add_name("gem");
    add_name("ctower_gem");

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 20);

    create_ctower_object();
    invoke_skill = SS_SPELLCRAFT;

    create_gem();
}

void
init()
{
    ::init();
    add_action(invoke, "invoke");
}
