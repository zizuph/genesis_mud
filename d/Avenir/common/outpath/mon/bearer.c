#pragma strict_types
// file name: ~Avenir/common/outpath/mon/bearer.c
// creator(s):  Boriska
// purpose: Merchant's per from Avenir's tunnels, works together with
//          him.
/*
 * Revisions:
 *     Lilith, Fed 2014: Updated desc.
 *     Lucius, Jul 2017: Fix runtime error.
 *
 */
inherit "/std/monster";

#include <filter_funs.h>
#include "../outpath.h"

#define SELL_PERIOD     1800.0

public object store, merchant;

void
create_monster()
{
    if (!IS_CLONE)
	return;

    set_name("lucky");
    set_short("big goblin");
    set_adj(({"big","simple"}));
    set_long("This big goblin is a simple fellow who appears to be "+
      "quite happy in his work.\n" );
    set_race_name ("goblin");

    set_stats ( ({80,80,100,2,2,80}) );

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_UNARM_COMBAT, 70);

    add_prop( LIVE_I_SEE_DARK, 1);

    set_whimpy(40);

    set_alarm(SELL_PERIOD, SELL_PERIOD, "empty_store"); 
}

private void
return_lucky()
{
    unset_no_show();
    set_no_show_composite(0);
    tell_room(environment(), QCTNAME(TO)+" arrives.\n");
}

void
empty_store()
{
    object *inv;

    if (!query_attack() && objectp(store) &&
	sizeof(inv = all_inventory(store)))
    {
	set_alarm(200.0, 0.0, return_lucky);
	command("emote trundles off.");

	set_no_show();
	FILTER_DEAD(inv)->remove_object();
	store->reset_store();
    }
}    

public void
set_merchant(object mer)
{
    merchant = mer;
    store = mer->get_store_object();
    store->reset_store();
}

private void
run_away()
{
    command("scream");
    tell_room(environment(),
      "Exhausted by the fight and frightened to death, "+QTNAME(TO)+" runs away\n" +
      "carrying all his load out of reach.\n");

    if (objectp(store))
	FILTER_DEAD(all_inventory(store))->remove_object();

    merchant->bearer_died();
    remove_object();
}

void
do_die(object killer )
{
    run_away();
}
