/*
 * /std/spell.c
 */

#include "defs.h"

//inherit "/d/Krynn/rastlin/open/spells/spell";
inherit "/d/Shire/healers/lib/spell/spell";
inherit "/d/Shire/healers/lib/extra";
inherit "/d/Shire/healers/lib/spellmsg";
inherit "/d/Shire/healers/lib/parse";
//inherit TELLEM_FILE;

#include <macros.h>
#include <ss_types.h>
#include <comb_mag.h>

#define FORM_NEEDED query_prop(SPELL_I_FORM_NEEDED)
#define ELEM_NEEDED query_prop(SPELL_I_ELEMENT_NEEDED)

/* Variables. */
int    spell_obj_mana;     /* The parsed spell class. */

nomask void
create_spell()
{
    add_prop(SPELL_I_MANA, "@@query_mana@@");
    add_prop(SPELL_I_DIFFICULTY, "@@query_difficulty@@");
    add_prop(SPELL_I_CASTING_TIME, "@@query_casting_time@@");

    this_object()->create_spellobj();

    add_prop(SPELL_I_ELEMENT_NEEDED, "@@query_element_needed@@");
    add_prop(SPELL_I_FORM_NEEDED, "@@query_form_needed@@");
}

int
query_element_needed()
{
    return 10; // query_spell_level() * MAX(1, (200 - INT(caster)) / 25);
}

int
query_form_needed()
{
    return 10; // query_spell_level() * MAX(1, (200 - WIS(caster)) / 25);
}

string
query_syntax()
{
    string syntax;

    syntax = query_prop(SPELL_S_NAME) + " ";
    syntax += query_prop(SPELL_S_SYNTAX);

    return "SYNTAX: "+syntax+"\n";
}

void
set_mana(int mana_needed)
{
    spell_obj_mana = mana_needed;
}

void
set_data(string verb, int class, string name)
{
    add_prop(SPELL_I_CLASS, class);
    add_prop(SPELL_S_NAME, name);
}

int 
query_mana()            
{ 
    return spell_obj_mana;  
}

int 
query_spell_level()     
{ 
    return query_mana()/10; 
}

int 
query_spell_class()     
{ 
    return query_prop(SPELL_I_CLASS); 
}

int
start_spell_fail(string str)
{
    notify_fail(query_syntax());

    if (::start_spell_fail(str))
	return 1;

    return 0;
}

int
query_normal_casting_time()
{
    int slvl = query_spell_level();

    if (level(caster) >= slvl+40)
	return 2;
    if (level(caster) >= slvl+20)
	return 3;
    if (level(caster) >= slvl+10)
	return 4;
    if (level(caster) >= slvl+6)
	return 6;
    if (level(caster) >= slvl+3)
	return 10;

    return 15;
}

/*
 * Function name:   query_casting_time
 * Returns:	    The amount of time needed to cast this spell.
 */
int
query_casting_time()
{
    int normal_time;
    int chanting_time;
    int relative;

    normal_time = query_normal_casting_time();
    chanting_time = caster->query_chanting_time();

    if (!chanting_time)
	return normal_time;

    relative = caster->query_relative_chanting_time();

    if (relative)
	chanting_time = normal_time + chanting_time;

    if (chanting_time <= 2)
	return 2;

    if (chanting_time >= 60)
	return 60;

    return chanting_time;
}

/*
 * The difficulty should be a function of your spell level
 * and the level for which the spell is.
 */
varargs int
query_difficulty()
{
    int slvl;
    int lvl;
    int diff;
    int normal_time;
    int wanted_time;

    slvl = query_spell_level();
    lvl  = level(caster);

    if (slvl <= lvl)
	diff = MAX(0, 700 - 50 * (lvl-slvl));
    else
	diff = MIN(700 + (slvl-lvl) * 100, 2000);

	/* diff = 700 at same level, 0 when 15 levels above. */

    normal_time = query_normal_casting_time();
    wanted_time = query_casting_time();

    if (wanted_time < normal_time)
	diff += (normal_time - wanted_time) * 50;
    else if (wanted_time > normal_time)
	diff -= (wanted_time - normal_time) * 100;

    return MAX(diff, 0);
}

/*
 * Function name:   query_real_difficulty
 * Description:     Returns the real difficulty, including not
 *		    having enough skills.
 */
int
query_real_difficulty()
{
    int diff;

    diff = query_difficulty();

    extra_difficulty = 0;
    valid_skills();
    return diff + extra_difficulty;
}

/*
 * Function name:   query_power_for_extra_time
 * Description:     Returns the amount of extra power for chanting
 *		    more time than normal. Formula is made so that
 *		    half normal casting time gives - 10 on power.
 *		    twice normal casting time means + 10 on power.
 *		    three times normal gives + 20 on power and so on.
 */
int
query_power_for_extra_time()
{
    int normal_time;
    int wanted_time;

    normal_time = query_normal_casting_time();
    wanted_time = query_casting_time();

    if (wanted_time >= normal_time)
	return (wanted_time - normal_time) * 10 / (normal_time);
    else
	return (wanted_time - normal_time) * 10 / (wanted_time);
}

/*
 * Masking calc_power().
 * Example:
 *   Wisdom        : 100     10
 *   Mana          : 200     40
 *   Form needed   :  10      1
 *   Elem needed   :  10      1
 *   Extra power   :   0      0
 * ------------------------------
 *                    31     30
 * ==============================                            
 */
int
calc_power(int result)
{
    if (caster->query_wiz_level())
	write("WIZINFO: result = " + result + "\n");

    spell_power = query_mana() * ((WIS(caster) + FORM_NEEDED + ELEM_NEEDED) / 10 +
				  query_power_for_extra_time()) / 100;

    return spell_power;
}

/*
 * Function name:   start_spell_msg
 * Arguments:	    arg - The arguments passed with the spell.
 * Description:     Handles the output given when the caster begins
 *		    to chant a spell.
 */
int
start_spell_msg(string arg)
{
    string mess, element, form;

    element = ELEMENT_NAMES[query_prop(SPELL_I_ELEMENT_SKILL)];
    form    = FORM_NAMES[query_prop(SPELL_I_FORM_SKILL)];

    write("You start singing an arcane hymn of Illuvatar.\n" +
	  "You sing: Hyarmen Eru Illuvatar tananda " + spell_name +"!\n"+
	  "You gain great wisdom in twisting the essence of " + element + ", forming "+
	  LANG_ADDART(form)+ " spell.\n");

    mess = " starts singing: Hyarmen Eru Illuvatar tananda " + CAP(spell_name);

    say( ({ METNAME + mess + "!\n",
	    TART_NONMETNAME + mess + "!\n",
	    "Someone" + mess + "!\n" }) );
    return 1; 
}

/*
 * Function name:   in_spell_range
 *
 * Arguments:	    target (object) : Target of a spell.
 *
 * Description:     Checks to see weather or not a target is within
 *		    the spell range.
 *
 * Returns:	    1 - If target is withing spell range.
 *		    0 - If not.
 */
int
in_spell_range(object target)
{
/*
    int range_bits = query_prop(SPELL_I_RANGE);
    int in_range = 0;

    if ((range_bits & RBIT_SELF) && (target == caster))
	return 1;

    if ((range_bits & RBIT_INVENTORY) && environment(target) == caster)
	return 1;

    if ((range_bits & RBIT_ROOM) && environment(caster) == target)
	return 1;

    if ((range_bits & RBIT_PRESENT) && environment(caster) == environment(target))
	return 1;

    if (range_bits & RBIT_PRESENT)
	if (!present(target, environment(caster))
	    return 0;

    if (range_bits & RBIT_VISIBLE)
	if (!CAN_SEE_IN_ROOM(caster) || !CAN_SEE(caster, target))
	    return 0;

    if (range_bits & RBIT_LIVING)
	if (!living(target))
	    return 0;

    if (range_bits & RBIT_OBJECT)
	if (living(target))
	    return 0;

    if (range_bits & RBIT_TEAM)
	if (member_array(target, caster->query_team()) >= 0)
	    return 0;

    if (range_bits & RBIT_NOT_TEAM)
	if (member_array(target, caster->query_team()) == -1)
	    return 0;

    if (range_bits & RBIT_FRIEND)
	if (member_array(target, caster->query_enemy(-1)) >= 0)
	    return 0;

    if (range_bits & RBIT_ENEMY)
	if (member_array(target, caster->query_enemy(-1)) == -1)
	    return 0;

    if (range_bits & RBIT_ATTACK)
	if (target != caster->query_attack())
	    return 0;

    if (range_bits & RBIT_NOT_ATTACK)
	if (target == caster->query_attack())
	    return 0;
*/
    return ::in_spell_range(target) || environment(caster)==target;
}

/*
 * Function name:	spell_msg
 * Description: 	Produces text when a spell is actually cast.
 */
varargs void
spell_msg(int tell_all)
{
    object caster = query_caster();
    object *targets = query_targets();

    string mesg1, mesg2;

    write("You stop chanting upon your spell and wave furiously with your "
	+ "arms!\n");

    mesg1 = " stops chanting upon " + HIS_HER(caster) + " spell";
    mesg2 = mesg1 + " and waves furiously with " + HIS_HER(caster) + " arms!";

    say(({
	break_string(METNAME + mesg2 +"\n", 74),
	break_string(TART_NONMETNAME + mesg2 + "\n", 74),
	break_string("Someone" + mesg1 + "\n", 74)
    }));

    spell_message(caster, targets,
		  CAP(query_prop(SPELL_S_NAME)), tell_all);
}

