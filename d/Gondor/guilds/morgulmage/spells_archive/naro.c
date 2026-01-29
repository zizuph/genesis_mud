/*
 * Naro, the command word. Spell for the Morgul Mages, based upon
 * the original guild.
 *
 * Created by Eowul, Oktober 2009
 *
 * Updated so naro libo makil no longer breaks imbued weapons.
 * Arman, October 2019.
 *
 */

#pragma strict_types

#include "../morgulmage.h"

#include <options.h>
#include <macros.h>
#include <flags.h>
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <cmdparse.h>

#define NARO_I_SPELL_TYPE   "_naro_i_spell_type"
#define TYPE_LIBO_MAKIL     1
#define TYPE_DREGO_NIN      2
#define TYPE_MAETHO         3

#define RANK_LIBO_MAKIL     14
#define RANK_MAETHO         19

#define RECENTLY_SPELL_DISARMED   ("_recently_spell_disarmed")
#define LIBO_DISARM_OBJ "/d/Gondor/guilds/morgulmage/spells/obj/naro_libo_disarm_obj.c"

#define DEBUG(x)  find_player("arman")->catch_msg("[naro] " + x + "\n")

inherit "/d/Genesis/specials/std/spells/centralized_spell";

#include "/d/Genesis/specials/std/spells/centralized_spell_restrictions.h"
#include "generic_functions.c"
#include "generic_hooks.c"
#include "rank_limitation.c"

public object *naro_target(object actor, string str);
public string *query_naro_ingredients(object caster);
public void   hook_disarm_cooldown(object caster, object target);

public nomask void config_spell()
{
    ::config_spell();

    set_spell_name("naro");
    set_spell_desc("Command others to do your bidding");

    set_spell_time(4);
    set_spell_mana(30);

    set_spell_vocal(1);

    // While some of the actions can be considered offensive, the basis
    // for the spell is fear. As such it's left upon the victim to decide
    // to run or to fight.
    set_spell_offensive(0);
    set_spell_peaceful(0);

    set_spell_element(SS_ELEMENT_DEATH, 20);
    set_spell_form(SS_FORM_ILLUSION, 10);

    set_spell_task(TASK_HARD);
    set_spell_target(naro_target);

    set_morgul_rank(5);

    set_spell_ingredients(query_naro_ingredients);
}

public int
query_spell_form_skill()
{
    switch(this_player()->query_prop(NARO_I_SPELL_TYPE)) 
    {
        case TYPE_LIBO_MAKIL:
            return SS_FORM_ENCHANTMENT;

        case TYPE_DREGO_NIN:
        case TYPE_MAETHO:
        default:
            return SS_FORM_ILLUSION;
    }
}

public int
query_spell_task()
{
    switch(this_player()->query_prop(NARO_I_SPELL_TYPE)) {
        case TYPE_LIBO_MAKIL:
        case TYPE_MAETHO:
            return TASK_HARD;

        case TYPE_DREGO_NIN:
        default:
            return TASK_ROUTINE;
    }
}

public int
get_spell_task()
{
    return query_spell_task();
}

public string *
query_naro_ingredients(object caster)
{
    return ({ "_canwa_charge" });
}


// Had to add a hack to make this work, as the standard
// hook for living_no_magic looks like it has errors in it.
public void
mm_hook_living_no_magic_attack_fail(mixed reason, object target)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    {
        write("You can't cast a spell on " +
            target->query_the_name(this_player()) + ".\n");
    }
}

int 
check_valid_action(object caster, mixed *targets,
                   string arg, int execute = 0)
{
    // While this check is also done in check_valid_action, it is only done
    // in case the spell is set to offensive.
    object room = environment(caster);
    mixed why;

    if (why = room->query_prop(ROOM_M_NO_MAGIC_ATTACK) )
    {
        hook_room_no_magic_attack_fail(why, room);
        return 0;
    }

    foreach (object target: targets) 
    {
        if ((why = target->query_prop(OBJ_M_NO_MAGIC)) || 
            (why = target->query_prop(OBJ_I_NO_ATTACK)))
        {
            mm_hook_living_no_magic_attack_fail(why, target); 
            return 0;
        }
    }

    return ::check_valid_action(caster, targets, arg, execute);
}

public object *naro_target(object caster, string str)
{

    string target, second_target;

    if(!str || str == "") {
        caster->catch_tell("Command your victim to do what?\n");
        return ({ });
    }

    if (parse_command(str, ({ }), "%s 'libo' 'makil' / 'makil!'", target)) {
        caster->add_prop(NARO_I_SPELL_TYPE, TYPE_LIBO_MAKIL);

        if(caster->query_morgul_level() < RANK_LIBO_MAKIL) {
            caster->catch_tell("The Dark Lord didn't grant you the power "
                + "to command 'libo makil'!\n");
            return ({ });
        }

        return ::spell_target_one_other_present_living(caster, target);
    }

    if (parse_command(str, ({ }), "%s 'drego' 'nin' / 'nin!'", target)) {

        object *noblist;
        noblist = PARSE_THIS(target, "[at] / [on] [the] %l");
 
        if (!sizeof(noblist))
        {
            caster->catch_tell("Whom do you wish to target?\n");
            return ({ });
        }

        if (sizeof(noblist) > 1)
        {
            caster->catch_tell("You will have to be more specific!  " +
                "You can only select one target.\n");
            return ({ });
        }

        if(noblist[0]->query_prop(NPC_I_NO_RUN_AWAY)) {
            caster->catch_tell("This target cannot be moved!\n");
            return ({ });
        }

        caster->add_prop(NARO_I_SPELL_TYPE, TYPE_DREGO_NIN);
        return ::spell_target_one_other_present_living(caster, target);
    }

    if (parse_command(str, ({ }), "%s 'maetho' %s", target, second_target)) {
        object target1, target2, *targets;

        if(caster->query_morgul_level() < RANK_MAETHO) {
            caster->catch_tell("The Dark Lord didn't grant you the power "
                + "to command 'maetho'!\n");
            return ({ });
        }

        caster->add_prop(NARO_I_SPELL_TYPE, TYPE_MAETHO);

        targets = ::spell_target_one_other_present_living(caster, target);
        if (sizeof(targets)) {
            target1 = targets[0];
        }

        targets = ::spell_target_one_other_present_living(caster, second_target);
        if (sizeof(targets)) {
            target2 = targets[0];
        }

        if(!objectp(target1) || !objectp(target2)) {
            caster->catch_tell("Cast naro <target> maetho <target>\n");
            return ({ });
        }

        if (target1 == target2) {
            caster->catch_tell("You can not command "
                + target1->query_the_name(caster)+ " to attack itself.\n");
            return ({ });
        }

        return ({ target1, target2 });
    }

    caster->catch_tell("Command your victim to do what?\n");
    return ({ });
}

void resolve_drego_nin(object caster, object target)
{
    caster->catch_tell("Peering deeply into the eyes of "
        + target->query_the_name( caster )+ " you command: Drego nin!\n"
        + "Trembling in fear and panic, " + target->query_pronoun()
        + " runs away!\n");
    target->catch_tell("Staring deeply into your eyes with eyes burning "
        + "like red coals, " + caster->query_the_name(target) + " tells you: "
        + "Drego nin!\nYou do not understand what the words mean, but you "
        + "are filled with fear and panic and try to run away.\n");
    tell_room(environment(caster), QCTNAME(caster) + " stares "
        + "threateningly into the eyes of " + QTNAME(target) + ", rasping "
        + "the words: Drego nin!\n" + QCTNAME(target) + " starts to tremble "
        + "and then runs away in panic.\n", ({ caster, target, }));

    target->run_away();
    target->add_panic(random(caster->query_stat(SS_DIS))
        + caster->query_stat(SS_OCCUP));

    if ((environment(target) != environment(caster)) && target->query_npc())
    {
        setuid();
        seteuid(getuid());
        object naro_ob = clone_object(MORGUL_SPELL_OBJ_DIR + "naro_drego_obj");
        naro_ob->set_from_room(environment(caster));
        naro_ob->move_back_with_delay(caster, 20 + random(20));
        naro_ob->move(target, 1);
    }
}

void resolve_libo_makil(object caster, object target)
{
    if (caster->query_mm_mounted()) {
        caster->catch_tell("Standing atop your steed, you raise your hand,"
            + " menacing " + target->query_the_name(caster)
            + ", and command: Libo makil!\n"
            + target->query_The_name(caster) + " seems stricken, "
            + target->query_possessive() + " chest heaving heavily.\n");

        target->catch_tell(caster->query_The_name(target) + " rises from atop "
            + caster->query_possessive() + " steed and lifts "
            + caster->query_possessive() + " hand, menacing at you, and "
            + "commands: Libo makil!\nYou fail to understand the words, but "
            + "you are stricken dumb.\nYou feel your tongue cleave to your "
            + "mouth, and your heart labouring.\n");

        tell_room(environment(caster), QCTNAME(caster) + " rises from atop "
            + caster->query_possessive() + " steed and lifts "
            + caster->query_possessive() + " hand, menacing at "
            + QTNAME(target) + ", and commands: Libo makil!\n"
            + QCTNAME(target)+ " seems stricken, "
            + target->query_possessive() + " chest heaving heavily.\n",
            ({ caster, target}));
    } else {
        caster->catch_tell("You raise your hand, menacing "
            + target->query_the_name(caster) + ", and command: Libo makil!\n"
            + target->query_The_name(caster) + " seems stricken, "
            + target->query_possessive() + " chest heaving heavily.\n");

        target->catch_tell(caster->query_The_name(target) + " raises "
            + caster->query_possessive() + " hand, menacing at you, and "
            + "commands: Libo makil!\nYou fail to understand the words, but "
            + "you are stricken dumb.\nYou feel your tongue cleave to your "
            + "mouth, and your heart labouring.\n");

        tell_room(environment(caster), QCTNAME(caster) + " raises "
            + caster->query_possessive() + " hand, menacing at "
            + QTNAME(target) + ", and commands: Libo makil!\n"
            + QCTNAME(target)+ " seems stricken, "
            + target->query_possessive() + " chest heaving heavily.\n",
            ({ caster, target}));
    }

    object *weapons = target->query_weapon(-1);
    if (!sizeof(weapons)) return;

    object weapon = weapons[random(sizeof(weapons))];
    if (weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON)) {
        int res = spell_resist(caster, weapon, SS_ELEMENT_DEATH, TASK_DIFFICULT);
        if ( res >= random( 100 ))
        {
            caster->catch_tell(target->query_The_possessive_name(caster)
                + " " + weapon->short() + " resists the effects of your "
                + "spell entirely!\n");
            return;
        }

        if ( weapon->has_imbue_shadow() )
        {
            if (target->query_prop(RECENTLY_SPELL_DISARMED) > time())
            {
                hook_disarm_cooldown(caster, target);
                return;
            }      	 

            caster->catch_tell(target->query_The_possessive_name(caster)
                + " imbuement on " + target->query_possessive() + " "
                + weapon->short() + " tries to resist the effects of your "
                + "spell, and is temporarily drawn into the realm of "
                + "Shadow!\n");

            make_spell_object(LIBO_DISARM_OBJ, caster, target, 
                0, 100, weapon);

            return;
        }

        weapon->set_dull(weapon->query_dull() + random(2) + 1);
        weapon->set_corroded(weapon->query_corroded() + random(3) + 2);

        caster->catch_tell(target->query_The_possessive_name(caster)
            + " "+ weapon->short()+ " is left damaged and heavily "
            + "corroded by your spell.\n" );
        target->catch_tell("Your " + weapon->short() + " is left damaged "
            + " and heavily corroded by "
            + caster->query_the_possessive_name(target) + " spell.\n");
    } else {
        weapon->remove_broken();
        target->command("$drop " + OB_NAME(weapon));
    }
}

void resolve_maetho(object caster, object target, object victim)
{
    caster->catch_tell("You peer deeply into the eyes of "
        + target->query_the_name(caster) + " and pointing at "
        + victim->query_the_name(caster) + ", you command: "
        + "Maetho!\nActing like a possessed creature, "
        + target->query_the_name(caster) + " turns to attack "
        + victim->query_the_name(caster) + "!\n");

    target->catch_tell("Staring deeply into your eyes with eyes burning "
        + "like red coals, " + caster->query_the_name(target) + " points at "
        + victim->query_the_name(target) + " and tells you: Maetho!\nYou do "
        + "not understand what the word means, but feeling as if you are "
        + "possessed and you turn to attack "+ victim->query_the_name(target)
        + "!\n");

    victim->catch_tell(caster->query_The_name(victim) + " stares "
        + "threateningly into the eyes of "+ target->query_the_name(victim)
        + ", and pointing at you rasps the word: Maetho!\nActing like a "
        + "possessed creature, "+ target->query_the_name(victim)
        + " turns to attack you!\n");

    tell_room(environment(caster), QCTNAME(caster) + " stares "
        + "threateningly into the eyes of " + QTNAME(target) + ", and "
        + "pointing at "+ QTNAME(victim)+ " rasps the word: Maetho!\nActing "
        + "like a possessed creature, "+ QTNAME(target)+ " turns to attack "
        + QTNAME(victim)+ "!\n", ({ caster, target, victim, }));

    if (interactive(target))
    {
        target->add_prop(LIVE_O_LAST_KILL, victim);
    }

    target->attack_object(victim);
}

void resolve_spell(object caster, mixed *targets, int *resist, int result)
{
    if (resist[0] >= random(100))
    {
        caster->catch_tell("Your spell has been resisted.\n");
        return;
    }

    dispel_artirith(caster);

    switch(caster->query_prop(NARO_I_SPELL_TYPE)) {
        case TYPE_DREGO_NIN:
            MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
            resolve_drego_nin(caster, targets[0]);
            break;
        case TYPE_LIBO_MAKIL:
            MORGUL_MASTER->increase_activity(caster, ACTIVITY_COMBAT_SPELL);
            resolve_libo_makil(caster, targets[0]);
            break;
        case TYPE_MAETHO:
            MORGUL_MASTER->increase_activity(caster, ACTIVITY_RARE_SPELL);
            resolve_maetho(caster, targets[0], targets[1]);
            break;
    }
}

/*
 * Function:    hook_disarm_cooldown
 * Description: Function that gets called to tell the caster that the cooldown
 *              is in effect.
 */
public void
hook_disarm_cooldown(object caster, object target)
{
    int wait_time = target->query_prop(RECENTLY_SPELL_DISARMED) - time();
    string seconds;
    if(wait_time > 60)
      seconds = "over a minute";
    else if(wait_time > 1)
      seconds = wait_time+ " seconds";
    else
      seconds = wait_time+ " second";
    caster->catch_msg(QCTPNAME(target) + " weapon was recently sent to the " +
        "realms of Shadow. You will need to wait " +seconds+ " before sending " +
            "it back again.\n");
}
