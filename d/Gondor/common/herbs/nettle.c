/*
 * This file is:
 * /d/Gondor/common/herbs/nettle.c
 *
 * Modified from:
 * /d/Gondor/common/herbs/sumac.c
 *
 * Modification History:
 *
 *    25-Feb-98, Gnandar: add itching poison obj, courtesy of Krynn
 *    1-Mar-98, Gnadnar: rolled our own itching poison so it may
 *		 	 be cured by the rohan mud.
 *    28 June 01, Serif: changed sumac to nettles; changed poison
 *           and herb effects to match nettle and be less toxic.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define	STING_FEELING_FILE	"/d/Gondor/common/poison/nettle_sting"
#define	ITCH_POISON_NAME	"_gondor_herb_nettle_poison"
#define	NETTLE_IS_RECOVERED	"nettle_is_recovered"

void
create_herb()
{
    set_name("leaves");
    add_name(({"leaf"}));
    set_adj(({"handful", "of", "fuzzy", "dark green"}));
    set_herb_name("nettle");
    set_herb_name("nettle");
    set_short("handful of fuzzy dark-green leaves");
    set_pshort("handfuls of fuzzy dark-green leaves");
    set_unid_long("This is a handful of fuzzy dark-green leaves.\n");
    set_id_long("This is a handful of nettle leaves. Nettles (Urtica dioica) "
        + "are leafy herbs of the nettle family which grow on the edges "
        + "of fields and moist places. Tiny hairs on the edge of the "
        + "leaves cause the plant to look slightly fuzzy, and also "
        + "inject a poison upon skin contact.\n");
    set_ingest_verb("eat");

    set_effect(HERB_HEALING, "fatigue", 5);
    set_id_diff(18);
    set_find_diff(1);
    set_decay_time(5400);
    set_herb_value(48);
    set_dryable();
}

/*
 * Function name:	enter_env
 * Description	:	entering new env -- if just recovered, drop.
 *				    else add itching poison if player
 *				    is not wearing gloves.
 * Arguments	:	object dest -- the new environment
 *			        object source -- the old environment
 */

public void
enter_env(object dest, object source)
{
    object	poison;
    object poisoner;
    ::enter_env(dest, source);

    if (ENV() == dest &&
	living(dest))
    {
	if (query_prop(NETTLE_IS_RECOVERED))
	{
	    remove_prop(NETTLE_IS_RECOVERED);
	    tell_object(dest,
	    "You quickly drop the handful of fuzzy dark green leaves "
            + "to avoid a painful sting.\n");
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
	    poison = clone_object(STING_FEELING_FILE);
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
 * Description	:	after parent, add NETTLE_IS_RECOVERED prop
 *	                so enter_env() will know to drop us.
 * Arguments	:	string arg -- recover args
 */

public void
init_herb_recover(string arg)
{
    ::init_herb_recover(arg);
    add_prop(NETTLE_IS_RECOVERED, 1);
} /* init_herb_recover */
