
 /*
  * Therapeaou (Heal) Spell for the Firewalkers Guild
  * by Jaacar
  * April 28th, 1998
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
#include FIRE_HEADER

public void therapeaou(object caster, object *targets, int *resist, int result);
public int create_spell_therapeaou(object caster, object *targets,  string argument);

public int
create_spell_therapeaou(object caster, object *targets,  string argument)
{
    set_spell_time(5);
    set_spell_mana(120);
    set_spell_task(TASK_SIMPLE);
    set_spell_element(SS_ELEMENT_FIRE, 40);
    set_spell_form(SS_PRAYER, 40);
    set_spell_ingredients(({"fireweed","brown slime"}));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    return 0;
}

public void
therapeaou(object caster, object *targets, int *resist, int result)
{
    int gstat;
    int heal;
    
    if (random(100) < resist[0])
    {
        caster->catch_tell("You successfully cast the Therapeaou spell but "+
            "it seems to have no effect.\n");
        return;
    }

    if (caster == targets[0])
    {
        write("Your blood begins to boil as you feel "+
            "the power of Lord Pyros racing throughout your body, "+
            "cauterizing some of your wounds.\n");
        tell_room(environment(caster), QCTNAME(caster) + " concentrates "+
            "intensely for a moment, then cauterizes some of "+C_HIS+
            " wounds with a searing flame.\n", ({ caster }));

        gstat = caster->query_base_stat(SS_OCCUP);
        heal=(100+(gstat/2));
        if (heal > 300) heal = 300;
        caster->heal_hp(heal);
        return;
    }
    targets[0]->catch_tell(caster->query_The_name(targets[0])+" mumbles some strange words, "+
        "then briefly grasps your shoulder firmly.  Your blood begins "+
        "to boil as you feel waves of heat flowing from "+C_HIS+
        " hands and moves throughout your body.  Flames erupt from "+
        C_HIS+" hands and cauterize some of your wounds.\n");
    targets[0]->command("scream");
    tell_room(environment(caster), QCTNAME(caster)+"'s eyes flash as "+
        C_HE+" grasps "+
        QTNAME(targets[0])+"'s shoulder briefly.  Flames burst from "+
        QTNAME(caster)+"'s hands and cauterize some of "+QTNAME(targets[0])+
        "wounds.\n",
        ({ caster, targets[0] }));
    caster->catch_tell("Your eyes flash as you incant the arcane words "+
        "of Therapeaou, and grasp "+
        targets[0]->query_the_name(caster)+"'s shoulder briefly, cauterizing some of "+
        TS_HIS+" wounds.\n");

        gstat = caster->query_base_stat(SS_OCCUP);
        heal=(100+(gstat/2));
        if (heal > 300) heal = 300;
        targets[0]->heal_hp(heal);
}
