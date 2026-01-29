/*
 *	/d/Gondor/common/npc/rescout.c
 *
 *	Cloned by:
 *	/d/Gondor/ithilien/forest/orcpath1.c
 *      (Used by /d/Gondor/common/guild2/npc/morandir.c there.
 *       Do not remove from that location without fixing Morandir!)
 */
#pragma strict_types

inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/common/lib/make_money.c";

#include <ss_types.h>

#include "/d/Gondor/defs.h"

public void
create_gondor_monster()
{
    set_name("orc");
    add_name( ({ "spy", "scout", }) );
    set_race_name("orc");
    set_short("spying orc");
    set_adj( ({ "ugly", "spying", }) );
    set_long("This orc seems to be out spying on something.\n"+
        "Upon the front of his armour and his helm you spot a little symbol:\n"+
        "A red, lidless eye.\n");
    set_pshort("spying orcs");
    default_config_npc(random(5)+12);
    set_alignment(-75);
    set_base_stat(SS_CON,random(6)+16);
    set_aggressive(1);
    set_attack_chance(40);
    set_skill(SS_WEP_SWORD, random(5)+9);
    set_chat_time(8);
    add_chat("Uruk drepa tuluk! Egur lug en vesall hai krimpatul!");
    add_chat("Onreinn hundur drepa!");
    add_chat("Ash nazg gimba, burz goth thraka!");
    add_chat("Rum marzgitul! Auga bukratul!");

    set_equipment( ({ (WEP_DIR + "orcscim"), (ARM_DIR + "releather"),
    	(ARM_DIR + "rehelm") }) );
}

public void
arm_me() 
{
    ::arm_me();
    get_money();
}

/* solemnian prestige */
int query_knight_prestige() { return 100; }

