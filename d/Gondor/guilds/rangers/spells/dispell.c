/*
 *  /d/Gondor/guilds/rangers/spell/dispell.c
 *
 *  Spell for adding resistance to magic
 *
 *  Palmer April 25, 2006
 */

#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

inherit SPELL_INHERIT;


/*
 *  Global variables
 */
int	Lissuin;

/*
 *  Function name: resolve spell
 *  Description  : This is the "guts" of the spell. Everything worked
 *                 and the spell was cast, this function does the spell
 *                 effect and finishes the job.
 *  Arguments    : caster  - the person who cast the spell
 *                 targets - who the spell was cast on
 *                 resist  - how must the targets resisted the spell
 *                 success - how well the spell was cast
 */
void
resolve_spell(object caster, object *targets, int *resist, int success)
{
    int 	power;
    int		dispell_amt;
    string	msg;

    power = caster->query_skill(SS_FORM_CONJURATION) +
        caster->query_skill(SS_ELEMENT_LIFE) +
        (caster->query_ranger_rank() / 2);

    if (targets[0] == caster)
    {
        // Sanity check
        if (!caster->query_company() && !caster->query_wiz_level())
        {
            caster->catch_tell("You cannot cast the spell on yourself.\n");
            return;
        }
    }
    else
    {
        /*
        Only reward / punish someone for actually casting someone.
        if (targets[0]->query_dispell() != targets[0]->query_dispell())
            adjust_valar_disfavour(caster, targets[0], 0.5);
        */
    }

    if (!Lissuin)
        msg = "call upon the Valar,";
    else
        msg = "use the virtues of the lissuin";

    if (targets[0] != caster)
    {
        caster->catch_tell("You " + msg + " in " +
          "an attempt to dispell evil magic "+targets[0]->query_the_name(caster)+".\n");
	if (Lissuin)
	{
	    targets[0]->catch_tell(caster->query_The_name(targets[0]) +
	      " crumples a lissuin between "+ POSSESSIVE(caster) +
	      " fingers and tosses the dust over their head.\n");
	}
	else
	{
	    targets[0]->catch_tell(caster->query_The_name(targets[0]) +
	      " places " + POSSESSIVE(caster) + " hand upon your cheek "+
	      "and begins to chant in an ancient tongue.\n");
	}
    }
    else
    {
	caster->catch_tell("You " + msg + " in an attempt to ward off "+
	  "evil enchantments.\n");
    }

    dispell_amt = 2 + (((power - 50) *
	2) / 100);

    // Half the dispell amount if no component was used.
    if (!Lissuin)
    {
	dispell_amt = dispell_amt / 2;
    }

    if (resist[0])
    {
	// Resistance may make healing less effective
	dispell_amt = dispell_amt - ((resist[0] * dispell_amt) / 100);
    }

    if (Lissuin)
    {
        tell_room(ENV(caster), QCTNAME(caster) + " crumples a lissuin to " +
          "dust between " + POSSESSIVE(caster) + " fingers, then spreads " +
          "it over " + (targets[0] == caster ? POSSESSIVE(caster) + " own" 
            : QTPNAME(targets[0])) + " head while mumbling some words " +
          "in an ancient tongue.\n", ({ caster, targets[0] }));
    }
    else
    {
        tell_room(ENV(caster), QCTNAME(caster) +" places "+POSSESSIVE(caster)+
          " hand on " + (targets[0] == caster ? POSSESSIVE(caster) + " own" 
            : QTPNAME(targets[0])) + " cheek while mumbling some "+
          "words in an ancient tongue.\n", ({caster, targets[0]}));
    }         
    if (dispell_amt <= 0 )
    {
        targets[0]->catch_tell("You feel a jolt, then nothing.\n");
        if (caster != targets[0])
        {
            caster->catch_tell("You feel that your spell had no effect "+
              "on "+targets[0]->query_the_name(caster) + ".\n");
        }
    }
    else
    {
        targets[0]->add_dispell(dispell_amt);
        targets[0]->catch_tell("A powerful confidence spreads through "
          + "your mind.\n");
    }
    setuid(); seteuid(getuid());
    log_file("dispell", ctime(time()) + " " + caster->query_name() + " " +
      "dispells "+ (targets[0] == caster ? OBJECTIVE(caster) + "self" 
	: targets[0]->query_name()) + " " + dispell_amt + ".\n");
}


int
add_dispell(int dispell_amt)
{
    // Do our stuff here
    return 0;
}


mixed
dispell_ingredients(object caster)
{
    object *list;

    list = get_item_search_list(caster);
    list = filter(list, &operator(==)("lissuin") @ &->query_herb_name());

    if (!sizeof(list))
    {
	Lissuin = 0;
	return ({ this_object() });
    }

    Lissuin = 1;
    return ({ list[0] });
}

/* Function name: config_spell
 * Description  : configures the spell, allowing you to set the
 *                various spell functions tothe values you wish
 *                for the spell.  Used much like the create_*
 *                function for rooms, monsters, objects etc...
 * Arguments    : caster  - person casting the spell
 *                targets - what the spell is cast on
 *                args    - Extra arguments for the spell
 * Returns      : 1 if the configuration didn't work
 *                0 if everything went ok
 */
int
config_spell(object caster, object *targets, string args)
{
    set_spell_name("dispell");
    set_spell_desc("Resist evil magic.");
    set_spell_target(spell_target_one_present_living);

    if (!default_ranger_spell_setup(caster))
	return 1;
    set_spell_mana(30);
    set_spell_time(6);
    set_spell_ingredients(dispell_ingredients);
    set_spell_peaceful(0);
    set_spell_task(TASK_ROUTINE - caster->query_ranger_rank());
    set_spell_element(SS_ELEMENT_LIFE, 20);
    set_spell_form(SS_FORM_CONJURATION, 10);
    set_spell_resist(spell_resist_healing);
    set_spell_stationary(0);
}
