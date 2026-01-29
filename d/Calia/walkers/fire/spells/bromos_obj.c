
/* Frenzy Object

   Conjured by the Bromos spell of the Firewalkers.

   Coded by Bishop, 2.6.1999.

*/

#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/magic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <filter_funs.h>
#include <defs.h>

varargs public int dispel_spell_effect(object dispeller);
public void frenzy_act();
public int stopfight(string str);

int success, alarm_id;

void 
create_object()
{
    set_name("_bromos_obj_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
}

public int
start()
{
    int duration, success;
    string desc;

    success = spell_caster->resolve_task(TASK_DIFFICULT, ({ SKILL_WEIGHT,
        75, TS_OCC, SKILL_END, SKILL_WEIGHT, 25, TS_WIS, SKILL_END, SKILL_AVG,
        SS_FORM_ENCHANTMENT, SS_ELEMENT_FIRE, SKILL_END}));
    success = min(max(success, 0), 100);
    success = success/2 + 20;
    duration = success * 4;

    set_spell_effect_desc("Frenzy");
  
    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    // In case the targets dex is lower than our success.

    if (success >= spell_target->query_stat(SS_DEX) - 10)
    {
        success = spell_target->query_stat(SS_DEX) - 10;
    }

    spell_target->set_stat_extra(SS_DEX, -success);
    spell_target->set_stat_extra(SS_DIS, success);

    if (spell_caster->query_wiz_level())
    {
        spell_caster->catch_msg("Stat modification was: " + success + ".\n"); 
    }

    switch(success)
    {
        case 20..35:
            desc = "little";
            break;
        case 36..55:
            desc = "moderate";
            break;
        default:
            desc = "great";
            break;
    }

    spell_caster->catch_msg("You lay the Bromos enchantment upon " +
        QTNAME(spell_target) + ", fanning the flames of " +
        spell_target->query_possessive() + " anger with " + desc + 
        " success.\n");
    spell_target->catch_msg("You suddenly feel a violent, storming rage" +
        " from within. Completely unable to control this feeling, you" +
        " look around, searching for someone to tear limb from limb!\n");
    tell_room(environment(spell_target), QCTNAME(spell_target) + " suddenly" +
        " looks furious! Wild-eyed, " + spell_target->query_pronoun() + 
        " searches the area, ready to tear someone limb from limb!\n", 
        spell_target);

    alarm_id = set_alarm(0.5, 20.0, &frenzy_act());

    set_alarm(itof(duration), 0.0, &dispel_spell_effect());

    return 1;
}

public void
frenzy_act()
{
    object *livings;
    string *exits, *angry_emotes;
    int i;

    angry_emotes = ({"roar", "roar violently", "growl", "growl furiously",
        "explode", "fume", "steam", "scream"});
    livings = FILTER_LIVE(all_inventory(environment(spell_target)));
    livings -= ({spell_target});
    exits = environment(spell_target)->query_exit_cmds();
    i = 0;

    // Take no action if already in a fight.
    if (spell_target->query_attack())
    {
        spell_target->command(angry_emotes[random(sizeof(angry_emotes))]);
        return;
    }

    if (!CAN_SEE_IN_ROOM(spell_target))
    {
        spell_target->command(angry_emotes[random(sizeof(angry_emotes))]);
        spell_target->catch_msg("You explode with anger, unable to find" +
            " a release for it in this darkness.\n");
        return;
    }

    // Remove anyone we can't see from the list of possible targets.  
    while (sizeof(livings) > i)
    {
        if (!CAN_SEE(spell_target, livings[i]))
        {
            livings -= ({livings[i]});
        }
        else
        {
            i++;
        }
    }

    // Noone here to kill? Let's move.
    if (!sizeof(livings))
    {
        spell_target->command(angry_emotes[random(sizeof(angry_emotes))]);
        spell_target->catch_msg("Unable to find anyone here to kill," +
            " you leave this place.\n");
        spell_target->command(exits[random(sizeof(exits))]);
        return;
    }
    // Otherwise, attack someone.
    else
    {
        i = random(sizeof(livings));
        spell_target->catch_msg("Seething with a fury you have no control" +
            " over, you attack " + QTNAME(livings[i]) + ".\n");
        tell_room(environment(spell_target), QCTNAME(spell_target) + " howls" +
            " in fury and leaps towards " + QTNAME(livings[i]) + ".\n", 
            ({spell_target, livings[i]}));
        livings[i]->catch_msg(QCTNAME(spell_target) + " howls in fury and" +
            " leaps towards you!\n");
        spell_target->command("kill " + OB_NAME(livings[i]));
        return;
    }
}   

public int
stopfight(string str)
{
    if (!strlen(str))
    {
        return 0;
    }
    else
    if (wildmatch("fight*", str) || wildmatch("fighting*", str))
    {
        spell_target->catch_msg("You don't feel like stopping this fight, you" +
            " want to continue till the bloody end!\n");
        return 1;
    }
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->set_stat_extra(SS_DEX, success);
    spell_target->set_stat_extra(SS_DIS, -success);

    tell_room(environment(spell_target), QCTNAME(spell_target) +
        " seems to calm down.\n", spell_target);
    spell_target->catch_msg("The uncontrollable rage within you" +
        " subsides, allowing you to think clearly again.\n");
    remove_alarm(alarm_id);

    remove_spell_effect_object();

    return 1;
}


public void
init()
{
    ::init();

    add_action(stopfight, "stop");
}