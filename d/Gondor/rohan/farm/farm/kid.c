/* 
 *  This file is /d/Gondor/rohan/quest/kid.c
 *
 */

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_monster() 
{
    if (!IS_CLONE) return;

    seteuid(getuid(this_object())); 

    set_name(({"kid","child"}));
    add_name("_farm_quest_kid_");
    set_pname("kids");
    set_short("rohirrim kid");
    set_pshort("kids");
    set_long("This is a rohirrim kid.\n");

    set_race_name("rohirrim"); 
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_gender(0);
    /*          str, dex, con, int, wis,  dis  	 */
    set_stats(({ 10,  10,  20,  15,  15,   10 }));

    set_skill(SS_UNARM_COMBAT, 20); /* Good attack skill */
    set_skill(SS_DEFENCE,       1); /* Low defense skill */

    set_hp(1); 

    set_adj("little");

    set_act_time(1);
    add_act("smile tearf");
    add_act("cry");
    add_act("sob");
}

void
encounter(object ob) { /* do nothing */ }

void
init_living()
{
    ::init_living();
    add_action("carry_me","carry");
}

/*
 *  Description: The actual function action, called by VBFC in seq_heartbeat
 */
void
monster_do_act()
{
    set_hp(1);
    ::monster_do_act();
}

int
carry_me(string who)
{
    string pick_text;
    pick_text = " tenderly picks up the small rohirrim kid and cradles him in " + TP->query_possessive() + " arms.\n";

    if ( who == "kid" ) 
    {
	change_prop(OBJ_M_NO_GET,0);
	this_object()->move(this_player());
	write(BS("You tenderly pick up the small rohirrim kid and cradle him in your arms.\n"));
    say(QCTNAME(TP) + pick_text, TP);
	return 1;
    }
    return 0;
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if ( from == this_player() )
    {
	change_prop(OBJ_M_NO_GET,1);
    }
}
