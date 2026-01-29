
  /*
   * Pleko (Hurricane) Spell for the Windwalkers Guild
   * by Jaacar
   * April 27th, 1998
   */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targeting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include "defs.h"
#include WIND_HEADER

public void pleko(object caster, object *targets, int *resist, int result);
public int create_spell_pleko(object caster, object *targets, string argument);

string selected_exit;

public object *
target_pleko(object caster, string str)
{
    string who, dir;
    object *targets, room;

    if (!present("_pleko_potion_object_",caster))
    {
        caster->catch_tell("You are not under the effects of the "+
            "pleko potion!\n");
        return ({});
    }

    if (!strlen(str))
    {
        caster->catch_tell("Use the powers of Pleko in which direction "+
            "and on whom?\n");
        return ({});
    }

    if (!sscanf(str, "%s %s", dir, who))
    {
        caster->catch_tell("Use the powers of Pleko in which direction "+
            "and on whom?\n");
        return ({});
    }

    room = environment(caster);
    selected_exit = dir;
    
    if (member_array(selected_exit, room->query_exit_cmds()) < 0)
    {
        write("There is no valid exit leading "+selected_exit+" here!\n");
        return ({}); 
    }

    return spell_target_one_present_living(caster, who);
}

public void
create_spell_pleko(object caster, object *targets, string argument)
{
    set_spell_time(3);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR,50);
    set_spell_form(SS_PRAYER,50);
    set_spell_ingredients(({ })); // Uses a potion
    set_spell_resist(spell_resist_basic);
    set_spell_target_verify(spell_verify_present);
    set_spell_effect(pleko);
    set_spell_stationary(1);
    return 0;
}

public void
pleko(object caster, object *targets, int *resist, int result)
{
    object room;
    string old_mout;

    if ((!selected_exit) || selected_exit == "")
    {
        write("You must supply a direction to use with Pleko!\n");
        return;
    }

    if (random(100) < resist[0])
    {
        caster->catch_tell("You successfully cast the Pleko spell but "+
            "it seems to have no effect.\n");
        return;
    }

    room = environment(caster);
    
    if (member_array(selected_exit, room->query_exit_cmds()) < 0)
    {
        write("There is no valid exit leading "+selected_exit+" here!\n");
        return; 
    }

    if (targets[0]->query_npc() && targets[0]->query_prop(NPC_I_NO_RUN_AWAY))
    {
        caster->catch_tell("You successfully cast the Pleko spell but "+
            "it seems to have no effect.\n");
        return;
    }

    old_mout = targets[0]->query_m_out();
    targets[0]->set_m_out("flies");
    targets[0]->catch_tell(caster->query_The_name(targets[0])+" mumbles some strange words "+
        "under "+C_HIS+" breath, then closes "+C_HIS+" eyes.  Wind "+
        "begins to blow in your face, gently at first but it is quickly "+
        "gaining in force.  Before long you find yourself having to "+
        "withstand hurricane force winds.  Finally you cannot stand "+
        "your ground any longer and you are blown away by the wind.\n");
    caster->catch_tell("You chant the ancient mantras of Pleko, and "+
        "close your eyes, concentrating on "+targets[0]->query_the_name(caster)+".  "+
        targets[0]->query_The_name(caster)+" tries to stand "+TS_HIS+
        " ground as hurricane force winds begin to blow towards "+C_HIM+".  "+
        "Finally "+TS_HE+" can stand it no longer and is blown away "+
        "by the force of the wind.\n");
    tell_room(environment(caster), QCTNAME(caster)+" mumbles some strange "+
        "words under "+C_HIS+" breath, then closes "+C_HIS+" eyes.  Suddenly, "+
        QNAME(targets[0])+" is assaulted with hurricane force winds.  "+
        capitalize(TS_HE) + " tries to stand "+TS_HIS+" ground but it is "+
        "no use and "+TS_HE+" is blown away.\n",
        ({ caster, targets[0]}));
    targets[0]->command(selected_exit);
    targets[0]->set_m_out(old_mout);
}
