#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../../local.h"

inherit "/lib/unique";
inherit AM_FILE

void arm_me();

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("kalen");
    add_adj("conniving");
    add_adj("arrogant");
    set_short("conniving arrogant human");
    set_race_name("human");
    set_gender("G_MALE");
    set_long("Before you stands one of the people behind most of the slave trading in Sanction area. "+
             "Business must have seen better days for this guy, as his armours are dirty and he reakes of "+
             "alcohol. His stance reveals that even in this condition, he will be able to put up a decent fight.\n");
        
    set_stats(({140+random(50),
                120+random(40),
                140+random(40),
                140+random(20),
                140+random(20),
                140+random(20)}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(CONT_I_WEIGHT, 120000);
    add_prop(CONT_I_HEIGHT, 185);

    set_all_hitloc_unarmed(40);

    set_alignment(-450);
    set_knight_prestige(40);
    arm_me();
}

void arm_me()
{
    clone_object(SARM+"black_chain")->move(TO, 1);
    clone_unique(SWEP+"big_axe", 5, "/d/Krynn/haven/dwarf_camp/wep/waraxe")->move(TO, 1);
    command("wear all");
    command("wield all");
}
