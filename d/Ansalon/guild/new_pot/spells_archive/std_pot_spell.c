/* 
 * This is basic spell object for PoT. It is to be inherited by actual spells.
 * Created by Milan 15.11.2000
 */
#pragma strict_types

inherit "/d/Genesis/newmagic/spell";
inherit "/lib/commands";

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "../guild.h"
#include "../spells.h"
#include <tasks.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <files.h>
#include <composite.h>
#include <language.h>

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
    object old_tp = TP;

    set_this_player(caster);
    caster->catch_tell("You clutch your black medallion and " +
      "pray to the Queen of Darkness.\n");
    allbb(" clutches " + HIS(caster) +
	" medallion and prays to the Queen of Darkness.");
    set_this_player(old_tp);
}

void
hook_no_mana_fail()
{
    write("You are too mentally exhausted to call upon Takhisis.\n");
}

void
hook_use_ingredients(object *ingrs)
{
    int i, j;
    string *arr;
    
    switch (query_spell_name())
    {
        case "pblind":
            if (IS_LEFTOVER_OBJECT(ingrs[0]))
                i = 0;
            else
                i = 1;
            
            write("A flame raises from within " + LANG_THESHORT(ingrs[i]) +
                ", consuming it in seconds while melting " +
                LANG_THESHORT(ingrs[!i]) + ".\n");
            break;
        case "peyes":
            arr = ingrs->query_race();
            if (arr[0] == arr[1])
                arr = arr[1..];
            write("The pair of " + COMPOSITE_WORDS(arr) + " eyes " +
                "glow briefly, their pupils changing to reptilian, before " +
                "they are consumed.\n");
            break;
        case "phammer":
        case "pimprecate":
            if (ingrs[0]->query_is_takhisis_holy_water())
                i = 0;
            else
                i = 1;

            write("The contents of the " + LANG_THESHORT(ingrs[i]) +
                " starts boiling and vaporises along with the phial " +
                "and " + LANG_THESHORT(ingrs[!i]) + " which decomposes " +
                "in the steam.\n");
            break;
        case "pheal":
            write("The " + ingrs[0]->query_race() + " heart pumps " +
                "one final beat before it crumbles.\n");
            break;
        case "phearing":
            if (IS_LEFTOVER_OBJECT(ingrs[0]))
                i = 0;
            else
                i = 1;
            
            write("The " + ingrs[i]->query_race() + " ear bursts " +
                "into a brilliant light before fading into nothingness " +
                "while " + LANG_THESHORT(ingrs[!i]) + " withers " +
                "away.\n");
            break;
        case "pidentify":
            write(LANG_THESHORT(ingrs[0]) + " cracks into small shards " +
                "and slips through your " +
                (objectp(this_player()->query_armour(A_HANDS)) ? "gloved" :
                "") + " fingers.\n");
            break;
        case "ppain":
            if (ingrs[0]->check_weapon())
                i = 0;
            else if (ingrs[1]->check_weapon())
                i = 1;
            else
                i = 2;

            if (ingrs[i + 1 % 3]->query_herbname() == "green slime")
                j = i + 1 % 3;
            else
                j = i + 2 % 3;
            write("As you stick " + LANG_THESHORT(ingrs[i]) + " into and " +
                "through the elven heart, you let the blood drip onto " +
                LANG_THESHORT(ingrs[j]) + ", making it burst into " +
                "flames, consuming the heart and blade.\n");
            break;
        case "prestore":
            if (IS_LEFTOVER_OBJECT(ingrs[0]))
                i = 0;
            else
                i = 1;
            
            write("You use " + LANG_THESHORT(ingrs[i]) + " to tap " +
                LANG_THESHORT(ingrs[!i]) + " which creates a " +
                "resonance that shatters both.\n");
            break;
        case "pslow":
            write(LANG_THESHORT(ingrs[0]) + " shimmers briefly into " +
                "a myriad of colours before crumbling to dust and " +
                "blowing away.\n");
            break;
        default:
            return ::hook_use_ingredients(ingrs);
    }
}

/*
 * Function name: query_casting_success
 * Description:   Determine if a spell is successfully cast
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success)
 */
static int
query_casting_success(object caster)
{
    object *m = filter(all_inventory(this_player()), &->id(MEDALLION_ID_NEW));
    int ret = ::query_casting_success(caster);

#ifdef 0
    int task = gSpell_task;
    int elem = caster->query_skill(gElement_skill),
        form = caster->query_skill(gForm_skill), ret;

    task += (gElement_needed > elem ? (gElement_needed - elem) * 50 :0);
    task += (gForm_needed > form ? (gForm_needed - form) * 50 : 0);

    /* Another change to better reflect how it should be
     * Statavg 100 again with maxed skills: TASK_ROUTINE; 95%,
     * TASK_DIFFICULT; 62%
     */
    ret = max(0, caster->resolve_task(task, ({
        SKILL_WEIGHT, 80, SS_SPELLCRAFT,
        SKILL_WEIGHT, 125, gElement_skill,
        SKILL_WEIGHT, 125, gForm_skill,
        SKILL_WEIGHT, 30, TS_INT,
        SKILL_WEIGHT, 30, TS_WIS, })));
#endif

    /* If we don't wear the medallion, there is only a 10% chance
     * the spell will actually go through
     */
    if (!sizeof(m) || !(m[0]->query_worn()))
    {
        caster->adjust_standing(RND_RANGE(-200, 50));
        if (random(10))
            return 0;
    }

    if (ret)
        caster->adjust_standing(random(8) ?
            RND_RANGE(TO->query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
    else
        caster->adjust_standing(RND_RANGE(-5, 5));
        
    return ret;
}

/* Function name: all_msg
 * Description: Prints a message to those who wants it
 * Arguments: string str      - the string to print
 *            object caster   - the caster
 *            mixed exclude   - An array or object of those to exclude
 *            int only_vision - Only display it to those who can actually
 *                              see the caster.
 */
public varargs void
all_msg(string str, object caster, mixed exclude, int only_vision)
{
    object *who;
    
    who = FILTER_PLAYERS(all_inventory(environment(caster)) - ({ caster }));
    
    if (pointerp(exclude))
        who -= exclude;
    else if (objectp(exclude))
        who -= ({ exclude });
    
    if (only_vision)
        who = FILTER_CAN_SEE_IN_ROOM(FILTER_IS_SEEN(caster, who));
    
    who->catch_msg(str);
}

/* Function name: all_msgbb
 * Description: An alias for all_msg(,,,1);
 * Arguments: See all_msg
 */
public varargs void
all_msgbb(string str, object caster, mixed exclude)
{
    all_msg(str, caster, exclude, 1);
}

/*
 * Function name: default_config_spell
 * Description:   Set the default values for the variables
 */
public void
default_config_spell()
{
    ::default_config_spell();
    set_spell_fail("Your prayer is unheard.\n");
    set_spell_exp_factor(this_object()->query_spell_level() * 10);
}

public varargs int
reduce_mana(object caster, int amnt, int test)
{
    object gem;
    
    if (caster->query_mana() < amnt)
    {
        return 0;
    }
    
    if (!test)
    {
        /* If we have a gem, and it has enough charge to lower the
         * amount by 1/6th, do that and notify the caster.
         */
        if ((gem = P(MEDALLION_ID, caster)->query_soul_gem()) &&
            gem->query_charge() >= (amnt / 6))
        {
            gem->add_charge(-(amnt / 6));
            amnt -= amnt / 6;
            
            if (calling_function() != "cast_spell")
                caster->catch_tell("The " + gem->short() + " pulses with " +
                    "light.\n");
        }
        
        caster->add_mana(-amnt);
    }
    
    return 1;
}

int
spell_time(int ss_occup, int min, int max)
{
    int t = max + (min - max) * ss_occup / 150;

    if (t < min)
        t = min;
    
    return t;
}
