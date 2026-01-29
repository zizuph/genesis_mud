/*
 * /d/Gondor/common/guild2/spells/morgul_spells.c
 *
 * Olorin, 12-jan-1994
 *
 * Modification log:
 * 26-Oct-1995: New spell system. Olorin
 */
#pragma strict_types

#define NEW_SPELL_SYSTEM

#ifdef NEW_SPELL_SYSTEM
inherit "/std/object.c";
inherit "/d/Genesis/magic/spellcasting.c";
#else
inherit "/std/spells.c";
#endif

#include <cmdparse.h>
#include <comb_mag.h>
#include <composite.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/common/guild2/spells/spell_defs.h"

#define HE(x)	(x)->query_pronoun()
#define HIS(x)	(x)->query_possessive()

#undef DEBUG
#define DEBUG 0

public int      filter_visible(object x) { return (!(x->query_no_show())); }

void
create_object()
{
    set_name("Morgul_Spell_Object");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);

    set_no_show();
}

void
update_morgul_spells()
{
    int     guild_level;
    object  tp = TP;

    if (ENV(TO) != tp)
        return;

    guild_level = tp->query_morgul_level();

    /* remove all spells */
    remove_spell("arhalgul");
    remove_spell("artirith");
    remove_spell("dollost");
    remove_spell("dramalgos");
    remove_spell("ephessul");
    remove_spell("faugoroth");
    remove_spell("morthul");
    remove_spell("mortirio");
    remove_spell("naro");
    remove_spell("nifarist");
    remove_spell("palanquendo");
    remove_spell("ringurth");
    remove_spell("sulambar");
    remove_spell("thunaur");
    remove_spell("yalarochrama");

    /* add available spells */
    if (guild_level >= MS_ARHAL_MIN)
        add_spell("arhalgul", "do_arhalgul", "Magic Revealing");
    if (guild_level >= MS_ARTIR_MIN)
        add_spell("artirith", "do_artirith", "Out of Sight");
    if (guild_level >= MS_DOLLO_MIN)
        add_spell("dollost", "do_dollost", "Emptyhead");
    if (guild_level >= MS_DRAMA_MIN)
        add_spell("dramalgos", "do_dramalgos", "Stormwind");
    if (guild_level >= MS_EPHES_MIN)
        add_spell("ephessul", "do_ephessul", "Windfence");
    if (guild_level >= MS_FAUGO_MIN)
        add_spell("faugoroth", "do_faugoroth", "Choking Horror");
    if (guild_level >= MS_MORTH_MIN)
        add_spell("morthul", "do_morthul", "Black Breath");
    if (guild_level >= MS_MORTI_MIN)
        add_spell("mortirio", "do_mortirio", "See in Darkness");
    if (guild_level >= MS_NARO1_MIN)
        add_spell("naro", "do_naro", "Word of Command");
    if (guild_level >= MS_NIFAR_MIN)
        add_spell("nifarist", "do_nifarist", "Make Forget");
    if (guild_level >= MS_PALAN_MIN)
        add_spell("palanquendo", "do_palanquendo", "Tell Far");
    if (guild_level >= MS_RINGU_MIN)
        add_spell("ringurth", "do_ringurth", "Chill of Death");
    if (guild_level >= MS_SULAM_MIN)
        add_spell("sulambar", "do_sulambar", "Wind of Doom");
    if (guild_level >= MS_THUNA_MIN)
        add_spell("thunaur", "do_thunaur", "Fire Breath");
    if (guild_level >= MS_YALAR_MIN)
        add_spell("yalarochrama", "do_yalarochrama", "Summon Winged Steed");
}

public void
init()
{
    ::init();

    update_morgul_spells();
}

/*
 * Function:    query_spell_time
 * Description: It is called from cmdhooks.c, and should return the time
 *              in seconds it takes to prepare the spell. The actual time
 *              will be (time + 2 + LIVE_I_ATTACK_DELAY).
 * Arguments:   verb - The verb that initiated this spell.
 *              arg  - The arguments to the verb.
 * Returns:     The time in seconds.
 */
public int
query_spell_time(string verb, string arg)
{
    switch(verb)
    {
        case "arhalgul":	return MS_ARHAL_TIME;
        case "artirith":	return MS_ARTIR_TIME;
        case "dollost": 	return MS_DOLLO_TIME;
        case "dramalgos": 	return MS_DRAMA_TIME;
        case "ephessul": 	return MS_EPHES_TIME;
        case "faugoroth": 	return MS_FAUGO_TIME;
        case "morthul": 	return MS_MORTH_TIME;
        case "mortirio": 	return MS_MORTI_TIME;
        case "naro": 		return MS_NARO_TIME;
        case "nifarist": 	return MS_NIFAR_TIME;
        case "palanquendo": 	return MS_PALAN_TIME;
        case "ringurth": 	return MS_RINGU_TIME;
        case "sulambar":
            if (query_caster()->query_npc())
                return 0;
            return MS_SULAM_TIME;
        case "thunaur": 	return MS_THUNA_TIME;
        case "yalarochrama": 	return MS_YALAR_TIME;
    }

    return ::query_spell_time(verb, arg);
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *		  the player soul when the command "spells" is typed.
 */
public void
list_spells()
{
    int     i,
            il;
    string  msg = "\n\t _______________________________________________ \n"+
                    "\t/                                               \\\n"+
                    "\t|  The Dark Lord has granted you these spells:  |\n"+
                    "\t|  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  |\n",
            space;

    if (!(il = sizeof(gVerbs)))
        return;

    for (i = 0 ; i < sizeof(gVerbs) ; i++)
        msg += sprintf("\t|  - %-20s %-20s  |\n", gVerbs[i], gNames[i]);

    msg += "\t\\_______________________________________________/\n\n";

    write(msg);
}

int
query_spell_mess(string verb, string arg)
{
    string  mess;

    write("You prepare to employ Dark Sorcery and draw upon the power of the Dark Lord.\n");

    switch(verb)
    {
        case "arhalgul":
        case "dollost": 
        case "dramalgos":
        case "ephessul":
        case "faugoroth":
        case "morthul":
        case "mortirio":
        case "naro":
        case "nifarist":
        case "palanquendo":
        case "ringurth":
        case "sulambar":
        case "thunaur":
            mess = " draws power from the realm of the shadows.";
            break;
        case "artirith":
            mess = " seems to fade into the realm of the shadows.";
            break;
        case "yalarochrama":
            mess = " starts to summon a creature from the realm of the shadows.";
            break;
    }
    say(({METNAME + mess + "\n", TART_NONMETNAME + mess + "\n", ""}));
    return 1;
}

/*
 * Function name: kill_access
 * Description:   This is to filter out not killable things in the CMDPARSE
 *		  macro.
 * Arguments:     ob - Object to test
 * Returns:	  1 - keep object.
 */
int
kill_access(object ob)
{
    if (!living(ob) || ob->query_ghost() || ob == query_caster())
	return 0;
    else
	return 1;
}

/*
 * Function name: find_one_combat_target
 * Description:   Find exactly one target to attack with a combat spell.
 * Arguments:     arg - argument to command verb
 * Returns:	  an array of object pointers with one element or 0
 */
public object *
find_one_combat_target(string str)
{
    object  tp = query_caster(),
           *all,
            victim;

write("find_one_combat_target called with argument "+str+".\n");
    if (strlen(str))
    {
	all = CMDPARSE_ONE_ITEM(str, "kill_access", "kill_access");
dump_array(all);
	if (sizeof(all))
	    victim = all[0];
    }

    if (!objectp(victim))
        victim = tp->query_attack();
    if (!objectp(victim))
    {
        write("Cast the spell at whom?\n");
        return 0;
    }

    return ({ victim });
}

/*
 * Function name: find_caster_target
 * Description:   Returns the caster as target for a spell.
 * Arguments:     arg - argument to command verb
 * Returns:       an array of object pointers with one element
 *                pointing to the caster of the spell or 0
 */
public object *
find_caster_target(string str)
{
    if (!strlen(str))
        return ({ query_caster() });

    str = LOW(str);
    if ((str == "me") || (str == query_caster()->query_real_name()))
        return ({ query_caster() });

    write("You can cast this spell only onto yourself!\n");
    return 0;
}

/*
 * Function name: find_one_living_target
 * Description:   Returns one living as target for a spell.
 * Arguments:     arg - argument to command verb
 * Returns:       an array of object pointers with one element
 *                pointing to the living as target for the spell or 0
 */
public object *
find_one_living_target(string str)
{
    object *obj;

    if (pointerp(obj = find_caster_target(str)))
        return obj;
    
    str = LOW(str);

    obj = parse_this(str, "[at] [on] [the] %l");

    if (!sizeof(obj))
        return 0;

    return ({ obj[0] });
}

/*
 * Function name: hook_no_magic_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public string
hook_no_magic_fail(object obj)
{
    return MORGUL_S_SPELL_FAIL;
}

/*
 * Function name: hook_no_magic_attack_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC_ATTACK.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public string
hook_no_magic_attack_fail(object obj)
{
    return MORGUL_S_SPELL_FAIL;
}

/*
 * Function name: hook_no_skills_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have good enough skills
 * Returns:       The message to print.
 */
public string
hook_no_skills_fail()
{
    return "The Dark Lord has not given you the power to cast this spell.\n";
}

/*
 * Function name: hook_no_mana_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have enough mana.
 * Returns:       The message to print.
 */
public string
hook_no_mana_fail()
{
    return "You do not feel strong enough to cast the spell.\n";
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public string
hook_no_ingredients_fail()
{
    return "One of the ingredients is missing!\n";
}


// Here the actual spells are included.

#include "/d/Gondor/common/guild2/spells/new/ringurth.c"
#include "/d/Gondor/common/guild2/spells/new/thunaur.c"


