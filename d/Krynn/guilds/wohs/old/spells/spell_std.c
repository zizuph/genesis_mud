/*
 * wohs/spells/spell_std
 *
 * Base for all WoHS spells. 
 */
#pragma strict_types

inherit "/d/Genesis/newmagic/spell";
inherit "/lib/commands";

#include "../guild.h";

#include <tasks.h>

//#ifndef F_SPELL_EXP
#define F_SPELL_EXP(mana, task, power, factor)  max(0, ftoi(itof(mana) * \
    (itof(power * factor) / 1000.0)) + ((task - TASK_SIMPLE) / 2)) * 4
//#endif


/*
 * Global Variables 
 */
static int study_difficulty;

/* 
 * Prototypes
 */
static int query_study_success(object caster);
public string spell_wohs_fail(object caster, object *targets, string arg);

/*
 * Spell Defaults
 */ 
public void
default_config_spell()
{
    ::default_config_spell();

    set_spell_fail(spell_wohs_fail);
}

public string 
spell_wohs_fail(object caster, object *targets, string arg)
{
    switch(random(2))
    {
    case 0:
        write("You fail to concentrate enough upon the spell.\n");
        break;
        
    case 1:
        write("You fail to pronounce one of the spidery words right.\n");
        break;
    }
}

/*
 * Spell Studying
 *
 * The study of magic is difficult and can at times be dangerous.
 * Magic can be unreliable even to a well trained mage.
 *
 */ 

/*
 * Function Name: set_study_difficulty
 * Arguments    : int - the task difficulty
 */ 
void
set_study_difficulty(int i)
{
    study_difficulty = i;
}

/*
 * Function Name: query_study_difficulty
 * Returns      : int - the task difficulty
 */
int
query_study_difficulty()
{
    return study_difficulty;
}


/*
 * Function Name: valid_study
 * Description  : This function is checked at the beginning of 
 *                spell studying to verify is the student is allowed
 *                to perform the action. It is expected to print messages
 *                on failure.
 * Returns      : int - true if the spell can be studied.
 */ 
int 
valid_study(object caster)
{
    if (!wildmatch(ROOMS + "*", file_name(environment(caster))) &&
        !caster->query_wiz_level())
    {
        write("You can not study this spell here.\n");
        return 0;
    }
    
    return 1;
}

/*
 * Function Name: study_spell
 * Description  : This is called from the spellbook when a mage 
 *                is studying the spell. It is expected to print 
 *                messages and apply effects. Mask it for more interesting
 *                effects.
 * Arguments    : object - student
 * Returns      : int - true on success 
 */
int
study_spell(object caster)
{
    int res;
    
    res = query_study_success(caster);

    if (!res)
    {
        write("You fail to learn the magic.\n");
        return 0;
    }
    
    write("You finish studying " + capitalize(query_spell_name()) + 
        " confident in your ability to cast it.\n");
    return 1;
}

/*
 * Function name: query_study_success
 * Description:   Determine if a spell is successfully studied
 * Returns:       The result as an integer indicating success or
 *                failure (0 indicating failure, positive integer
 *                indicating % success, possibly > 100)
 */
static int
query_study_success(object caster)
{
    int task = study_difficulty;
    int elem = caster->query_skill(gElement_skill),
        form = caster->query_skill(gForm_skill);
    
    task += (gElement_needed > elem ? (gElement_needed - elem) * 50 :0);
    task += (gForm_needed > form ? (gForm_needed - form) * 50 : 0);

    return max(0, caster->resolve_task(task, ({
        SKILL_WEIGHT, 70, gElement_skill,
            SKILL_WEIGHT, 70, gForm_skill,
            SKILL_WEIGHT, 20, TS_INT,
            SKILL_WEIGHT, 20, TS_WIS,
            SKILL_WEIGHT, 20, TS_DIS, })));
}






/*
 * We need to mask the actual casting routines from the spell base
 * to intercept successfull casts. 
 *
 * When a spell is successfully cast the study counter in the spellbokk
 * should be lowered.
 */
static int
query_casting_success(object caster)
{
    int result, xp;

    result = ::query_casting_success(caster);

    if (result > 0)
    {
        object book;

        book = present(SPELL_BOOK, caster);

        if (!book)
        {
            /* wizard using the test spell object ? */
            return result;
        }

        book->modify_usage(query_spell_name(), -1);

        xp = F_SPELL_EXP(gMana_needed, gSpell_task, 
            (gElement_needed + gForm_needed) / 2, (gSpell_exp_factor ? : 100));

        this_player()->add_wohs_xp(xp);
        dump_array(xp);
    }
    
    return result;
}
