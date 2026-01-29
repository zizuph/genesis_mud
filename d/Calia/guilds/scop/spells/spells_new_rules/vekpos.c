/*
 * vekpos.c
 *
 * Vekpos (Turn Undead) spell for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, September 1st, 2003
 *
 * Balance Review Done By Shiva - September 2003
 *
 * Fixed problem with the component. Can't have it taking just
 * any skull. - Bishop, April 2004.
 *
 * Further modifications - Bishop, April 2004.
 */

/* Spell completely redone in the late fall of 2006.
 * The spell has reduced duration, but added damage
 * effect to undeads. It also cannot instant kill 
 * anyone.
 * -- Navarre
 */


#pragma strict_types
#pragma save_binary

//inherit "/d/Genesis/newmagic/spell";
inherit "/d/Genesis/newmagic/spells/harm";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>

#include "defs.h"
#include SPIRIT_HEADER

#define I_HAVE_BEEN_SPIRIT_TURNED "_i_have_been_spirit_turned"
#define I_HAVE_BEEN_VEKPOSSED "_scop_i_have_been_vekpossed"
#define TURN_LOG "spirit_circle/spirit_undead_turn_log"
#define DELAY_TIME 6


string
query_spell_level()
{
    return "Apprentice";
}


/*
 * A combination of spell_target_one_other_present_living
 * and spell_target_one_present_enemy
 */
public object*
vekpos_target(object caster, string str)
{
    if (!stringp(str) || (str == ""))
        return spell_target_one_present_enemy(caster, str);
    else
        return spell_target_one_other_present_living(caster, str);
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (caster == 0)
    {
        set_spell_name("vekpos");
        set_spell_desc("Turn Undead");
        set_spell_target(vekpos_target);
        set_spell_target_verify(spell_verify_present);
        set_spell_time(6);
        set_spell_mana(126);
        set_spell_vocal(0);
        set_spell_offensive(1);
        set_spell_task(TASK_ROUTINE);
        set_spell_resist_task(TASK_FORMIDABLE);
        set_spell_element(SS_ELEMENT_SPIRIT, 30);
        set_spell_form(SS_FORM_DIVINATION, 20);
        set_spell_ingredients(({"bloodstone", "skull"}));
        set_spell_object(SPIRIT_SPELLS + "vekpos_obj");        

        add_element_resistance(SS_ELEMENT_SPIRIT, MAGIC_I_RES_LIFE);
    }
    else
    {
        if (caster->query_intoxicated())
        {
            caster->catch_tell("You cannot use Psuchae's gifts while intoxicated!\n");
            return 1;
        }
        if (caster->query_alignment() < 0)
        {
            caster->catch_tell("You cannot use Psuchae's gifts while you are not "+
                               "good aligned.\n");
            return 1;
        }

        if (!targets[0]->query_npc() && (targets[0]->query_ghost() || 
            !interactive(targets[0])))
        {
            caster->catch_tell("You cannot use this gift on a ghost.\n");
            return 1;
        }

        if(caster == targets[0])
        {
            caster->catch_tell("You can't target yourself with this gift.\n");
            return 1;
        }

        if(caster->query_feared_scop_shadow())
        {
            caster->catch_tell("Performing this prayer again this quickly, won't have any effect.\n");
            return 1;
        }

        if (!targets[0]->query_prop(LIVE_I_UNDEAD))
        {
            caster->catch_tell(targets[0]->query_The_name(caster)+" is not undead!\n");
            return 1;
        }

        if(present("_scop_undead_turned_ob_", targets[0]))
        {
            caster->catch_tell(targets[0]->query_The_name(caster)+
                    " is already affected by such a prayer.\n");
            return 1;
        }

        if((time() - caster->query_prop(SCOP_CAST_TIME)) < caster->query_prop(SCOP_SPELL_DELAY))
        {
          caster->catch_tell("You need to regain your mental focus before "+
                             "concentrating on another complicted prayer.\n");
          return 1;
        }
    }
    return 0;
}

/*
 * Function name: concentrate_msg
 * Description:   Give messages indicating that spell concentration has begun
 * Arguments:     1. (object)   The caster
 *                2. (object *) The targets
 *                3. (string)   The arguments passed to the "cast" command
 */

public void
concentrate_msg(object caster, object *targets, string arg)
{
    caster->catch_tell("You concentrate on the powers of Psuchae.\n");
    say(QCTNAME(caster) + " appears to be in deep concentration.\n");
    if(targets[0]->query_prop(LIVE_I_UNDEAD))
    {
	caster->attack_object(targets[0]);
    }
}


void ready_again(object me)
{
    me->catch_tell("You feel the mental strain from performing " +
                   "the Vekpos prayer dispersing.\n");
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */

public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    int success, pen;
    mixed* hitresult;
    object spellob;
    object tar = targets[0];


    if (random(100) < resist[0] || 
        time() - tar->query_prop(I_HAVE_BEEN_VEKPOSSED) < 300)
    {
        caster->catch_tell("You complete the spell, but your target is" +
                           " unaffected.\n");
        return;
    }

    caster->catch_tell("Brandishing your sacred mandala, you call out to" +
                       " Psuchae to aid you in removing the abomination that is " +
                       tar->query_the_name(caster) + " from your sight!\n");
    tar->catch_tell(caster->query_The_name(tar) + " brandishes "+
                    caster->query_possessive() + " sacred mandala in your direction, " + 
                    caster->query_possessive() + " face a mask of anger and disgust at" +
                    " your presence.\n");
    tell_room(environment(caster), QCTNAME(caster) + " brandishes " + 
              caster->query_possessive() + " sacred mandala in " + 
              LANG_POSS(QTNAME(tar)) + " direction, " +
              caster->query_possessive() +" face a mask of anger and disgust at " + 
              LANG_POSS(QTNAME(tar))+ " presence.\n", ({caster, tar}));

    success = (caster->resolve_task(TASK_SIMPLE,
              ({SKILL_WEIGHT, 20, MIN(result, 100),
                SKILL_WEIGHT, 40, TS_WIS,
                SKILL_WEIGHT, 40, TS_OCC,
                SKILL_AVG, SS_SPELLCRAFT, SS_ELEMENT_LIFE, SKILL_END}),
              tar, 
              ({SKILL_AVG, SS_ELEMENT_DEATH, tar->query_prop(LIVE_I_UNDEAD),
                SKILL_END, TS_INT})));

    if (success>=0)
    {
        if (tar->query_prop(NPC_I_NO_RUN_AWAY))
        {
            tell_room(environment(caster), QCTNAME(tar) + " looks" +
                      " shaken, but does not run.\n", ({tar}));
        }
        else 
        {
            setuid();
            seteuid(getuid());

          
            caster->catch_tell(tar->query_The_name(caster) + " appears" +
                               " shaken by your prayer!\n");
            tar->catch_tell("Pain and light floods your world. You " +
                            " feel your whole body tremble, you attempt to flee " +
                            "from the pain.\n");
            tell_room(environment(caster), QCTNAME(tar) + " appears" +
                      " shaken!\n", (({caster, tar})));

            spellob = make_spell_effect_object(query_spell_object(), caster, 
                                               tar, resist[0], result);
            spellob->move(tar, 1); 
            success = MIN(200, success);
            pen = 2 * success + 2*caster->query_skill(SS_OCCUP)+
                                2*caster->query_skill(SS_SPELLCRAFT)+
                                caster->query_skill(SS_ELEMENT_LIFE);
              
            pen = MIN(pen, 840);

            if (present("_metaballo_weapon_", caster))
            {
                // Metaballo gives around 32% combat aid, heal can therefore at most give 68%.
                pen = MIN(539, pen);
            }

            hitresult = do_harm_damage(caster, tar, pen);


            setuid();
            seteuid(getuid());
            write_file(SPIRIT_LOGS + "vekpos_damage_log", ctime(time()) + ": " + 
                       caster->query_name() + " cast a " + pen + " pen Vekpos," +
                       " dealing " + hitresult[3] + " damage.\n");

            if (tar->query_hp() <= 0)
            {
              tar->do_die(caster);
            }
            caster->add_prop(SCOP_CAST_TIME, time());
            caster->add_prop(SCOP_SPELL_DELAY, DELAY_TIME);
            set_alarm(itof(DELAY_TIME), 0.0, &ready_again(caster));
        }
    }
    else
    {
        caster->catch_tell(tar->query_The_name(caster) + " smirks" +
                           " in amusement at your antics.\n");
        tar->catch_tell("You smirk in amusement at " + 
                        LANG_POSS(caster->query_the_name(tar)) + " antics.\n");
        tell_room(environment(caster), QCTNAME(tar) + " smirks in" +
                  " amusement at " + LANG_POSS(QTNAME(caster)) + " antics.\n",
                  (({caster, tar})));
    }
}
