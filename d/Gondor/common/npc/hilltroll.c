#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define GEMS_DIR "/d/Genesis/gems/obj/"

inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/lib/add_gems.c";

public void
create_gondor_monster()
{
    set_name("hill-troll");
    add_name("troll");
    set_race_name("troll");
    set_adj("nasty");
    set_long("It is a very ugly and nasty looking troll.\n");
    default_config_npc(52);
    set_base_stat(SS_CON, 125);
    set_base_stat(SS_DIS, 120);
    set_base_stat(SS_STR, 119);
    set_base_stat(SS_DEX, 100);
    set_aggressive(1);
    set_alignment(-350 - random(100));
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_PARRY, 57);
    set_skill(SS_BLIND_COMBAT, 94);
    set_skill(SS_DEFENCE, 59);
    set_skill(SS_AWARENESS, 49);

    set_all_hitloc_unarmed(20);

    add_prop(LIVE_I_SEE_DARK, 4);
    add_prop(CONT_I_HEIGHT, 360);
    add_prop(CONT_I_WEIGHT, 450000);
    add_prop(CONT_I_VOLUME, 420000);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_equipment( ({ WEP_DIR + "trollclub", ARM_DIR + "trollcape", }) );


//set_gems(3);

    seq_new("do_things");
    seq_addfirst("do_things",
     ({"@@arm_me","say I will crush you with my club, and eat your brains!"}));
}

/* Solamnian prestige */
public int query_knight_prestige() {return (450);}


void
do_die(object killer)
{
	
	setuid();
	seteuid(getuid());
	
	if(!difficulty==0)
	{
	    clone_object(GEMS_DIR + make_gems())->move(TO);
	}
	
	::do_die(killer);
}
	