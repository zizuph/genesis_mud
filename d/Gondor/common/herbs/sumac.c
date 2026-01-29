/*
 * /d/Gondor/common/herbs/sumac.c
 *
 * Modification History:
 *
 *    25-Feb-98, Gnandar: add itching poison obj, courtesy of Krynn
 *    1-Mar-98, Gnadnar: rolled our own itching poison so it may
 *		 	 be cured by the rohan mud.
 *    8-Jun-09, Eowul: Stopped poisoning of player when quitting
 *              with herb in pouch without wearing gloves.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define	ITCH_POISON_FILE	"/d/Gondor/common/poison/sumac_poison"
#define	ITCH_POISON_NAME	"_gondor_herb_sumac_poison"
#define	SUMAC_IS_RECOVERED	"sumac_is_recovered"

void
create_herb()
{
    set_name("vine");
    add_name("naro_ingr2");
    set_adj(({"red", "oily", "strand", "of", }));
    set_herb_name("sumac");
    set_short("red oily vine");
    add_pname(({"strands", "herbs", "vines", }));
    set_pshort("strands of oily vine");
    set_ingest_verb("eat");
    set_unid_long("This oily vine's red stems seem to branch "+
      "constantly. The small bumps on the leaves are unpleasant looking.\n");
    set_id_long("This stringy vine is an oily fragment of poison sumac.\n");

    set_effect(HERB_POISONING, "sumac", 40);
    set_poison_damage(({POISON_HP, 50, POISON_FATIGUE, 40, POISON_MANA, 20,
      POISON_STAT, SS_CON}));
    set_id_diff(59);
    set_find_diff(4);
    set_decay_time(5400);
    set_herb_value(216);
    set_dryable();
}


/*
 * Function name:	enter_env
 * Description	:	entering new env -- if just recovered, drop.
 *				else add itching poison if player
 *				is not wearing gloves.
 * Arguments	:	object dest -- the new environment
 *			object source -- the old environment
 */
public void
enter_env(object dest, object source)
{
    object	poison;
    object poisoner;

    ::enter_env(dest, source);

    // Do not perform the poisoning when quitting
    if(query_verb() == "quit") return;

    if(dest->query_prop(LIVE_I_UNDEAD))
        return;

    if (ENV() == dest &&
	living(dest))
    {
	if (query_prop(SUMAC_IS_RECOVERED))
	{
	    remove_prop(SUMAC_IS_RECOVERED);
	    tell_object(dest,
		"You quickly drop the red oily vine to avoid a nasty rash.\n");
	    if (move(ENV(dest)))
	    {
		move(ENV(dest), 1);
	    }
	}
	else if (!dest->query_armour(A_R_HAND) ||
	         !dest->query_armour(A_L_HAND))
    	{
	    /* the poison ob will check for dups */
	    FIX_EUID;
	    poison = clone_object(ITCH_POISON_FILE);
	    if (!dest->query_armour(A_R_HAND))
	    {
		poison->set_body_part("right hand");
	    }
	    else
	    {
		poison->set_body_part("left hand");
	    }
	    poison->move(dest, 1);
            /* If you are given the poison, the giver is the culprit. */
	    poisoner = ((objectp(source) && living(source)) ? source : dest);
            poison->start_poison(poisoner);
	}
    }
} /* enter_env */


/*
 * Function name:	init_herb_recover
 * Description	:	after parent, add SUMAC_IS_RECOVERED prop
 *			so enter_env() will know to drop us.
 * Arguments	:	string arg -- recover args
 */
public void
init_herb_recover(string arg)
{
    ::init_herb_recover(arg);
    add_prop(SUMAC_IS_RECOVERED, 1);
} /* init_herb_recover */
