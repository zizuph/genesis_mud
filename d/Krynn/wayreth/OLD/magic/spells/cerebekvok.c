/*
 * Cerebekvok
 *
 * Description: Tell someone something (Tell line)
 * Class:       0
 * Ingredients: two copper coins
 * Mana:        10 to guildmember, 20 to non-member (1/3)
 * Tax:         4%
 * Skills:      SS_ELEMENT_AIR      1
 *              SS_FORM_CONJURATION 2
 * Task:        TASK_SIMPLE
 * Restriction: Must be member and not engaged in combat,
 *              the caster must not be gagged and the caster must
 *              know the target, the target must atleast have 25
 *              in int. to understand the message.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>
#include <options.h>

public void cerebekvok_message(string what, object caster, object *targets);
public object *cerebekvok_target(string who, string arg);

public int
create_spell_cerebekvok(string arg)
{
    string whom, what;

    if (!stringp(arg) || sscanf(arg, "%s %s", whom, what) != 2)
    {
        write("Whom do you want to tell what?\n");
	return 1;
    }

    if (check_gagged())
        return 1;

    if (check_combat())
        return 1;

    set_spell_element(SS_ELEMENT_AIR, 2);
    set_spell_form(SS_FORM_CONJURATION, 2);

    set_spell_time(2);
    set_spell_task(TASK_SIMPLE);

    set_spell_ingredients("two copper coins");

    set_find_target(&cerebekvok_target(whom,));
    set_spell_message(&cerebekvok_message(what,));
}

public int
do_cerebekvok(string str)
{
    return cast_spell();
}

public object *
cerebekvok_target(string who, string arg)
{
    object tar = find_living(who);

    if (tar->query_guild_name_occ() == GUILD_NAME)
        set_spell_mana(10);
    else 
        set_spell_mana(20);

    if (!objectp(tar) || (tar->query_wiz_level() &&
	tar->query_guild_name_occ() != GUILD_NAME) ||
	tar->query_prop(WIZARD_I_BUSY_LEVEL) & ( 4 | 8 | 16 | 128 ) )
        return ({ 0 });

    return ({ tar });
}

public void
cerebekvok_message(string what, object caster, object *targets)
{
    object tar = targets[0];
    string *met = ({});
    mapping tmp;
    string stdfail = "You cast the spell but it didn't feel like " +
                     "the message got through.\n";

    tell_room(E(caster), "With the help of " + POSSESSIVE(caster) +
	      " magic, " + QTNAME(caster) + " casts a spell.\n", caster);

    if (!objectp(tar) || tar->query_linkdead())
    {
        caster->catch_msg(stdfail);
	return;
    }

    if (tar->query_stat(SS_INT) < 25)
    {
        caster->catch_msg(stdfail);
	tar->catch_msg("You start to hear strange noises in your head.\n");
	return;
    }

    if (mappingp(tmp = tar->query_remembered()))
        met += m_indexes(tmp);

    if (mappingp(tmp = tar->query_introduced()))
        met += m_indexes(tmp);

    caster->catch_msg("With the help of your magic powers you manage " +
		      "to tell " + C(RNAME(targets[0])) + " your message.\n");

    if (caster->query_option(OPT_ECHO))
        caster->catch_msg("You tell " + OBJECTIVE(tar) + ": " +
			  what + "\n");

    if(tar->query_wiz_level())
	what += "\n(Wizinfo : From " +
		 capitalize(caster->query_real_name()) + ")";

    tar->catch_msg("Suddenly you hear the voice of " +
		   (member_array(RNAME(caster), met) == -1 ? 
		    LANG_ADDART(caster->query_race_name()) :
		    C(RNAME(caster))) + " who " +
                   "whispers:\n" + what + "\n");
}




