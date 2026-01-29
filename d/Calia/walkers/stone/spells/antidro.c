
 /* Antidro (Wall of Stone) Spell for the Stonewalkers of Thalassia
  * by Jaacar
  * November 7th, 1998
  */ 

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include "defs.h"
#include STONE_HEADER

public void antidro(object caster, object *targets, int *resist,
    int result);
public int create_spell_antidro(object caster, object *targets,
    string argument);

string blocked_exit = "";

public object *
antidro_target_caster(object caster, string str)
{
    if (!present("_antidro_potion_object_",caster))
    {
        caster->catch_tell("You are not under the effects of the "+
            "antidro potion!\n");
        return ({});
    }
    return ({ caster });
}

public int
create_spell_antidro(object caster, object *targets, string argument)
{
    set_spell_time(3);
    set_spell_mana(96);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_EARTH, 40);
    set_spell_form(SS_PRAYER, 40);
    set_spell_ingredients(({ })); // Uses a potion
    blocked_exit = argument;
    return 0;
}

public void
antidro(object caster, object *targets, int *resist, int result)
{
    object wall, room;

    if ((!blocked_exit) || blocked_exit == "")
    {
        write("You must supply a direction to use with Antidro!\n");
        return;
    }
    
    room = environment(caster);
    
    if (member_array(blocked_exit, room->query_exit_cmds()) < 0)
    {
        write("There is no valid exit leading "+blocked_exit+" here!\n");
        return 0;
    }
    
    write("You correctly recite the mantras of the Antidro spell and "+
        "block the "+blocked_exit+" exit.\n");
    tell_room(environment(caster), QCTNAME(caster) +" chants aloud an "+
        "ancient mantra.  A giant wall of stone forms blocking the "+
        blocked_exit+" exit.\n",({caster}));
    seteuid(getuid());
    wall = clone_object(ANTIDRO_OB);
    wall->set_blocked_exit(blocked_exit);
    wall->set_remove_time(ANTIDRO_DURATION);
    wall->move(environment(caster));
}
