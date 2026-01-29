/* Standard human Guard in Tantallon*/
/* 25/10/15 added coins and gems, reduced unarmed hitloc - Arman */

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>

inherit M_FILE

#define M1   MONEY_MAKE_SC(random(15))->move(TO);
#define M2   MONEY_MAKE_GC(random(4))->move(TO);
#define GEM1 "/d/Genesis/gems/obj/quartz"
#define GEM2 "/d/Genesis/gems/obj/onyx"

void
create_krynn_monster()
{
    int i;

    set_name("human");
    set_race_name("human");
    add_name("guard");
    set_long("He is supposed to guard the south entrance to Tantallon.\n");
    set_adj("evil");
    set_short("evil human guard");

    for (i = 0; i < 6; i++)
        set_base_stat(i, 40 + random(10));
    set_skill(SS_DEFENCE, random(5) + 40);
    set_skill(SS_WEP_SWORD, 60);

    set_alignment(-300);
    set_knight_prestige(500);

    NEVERKNOWN;

    set_all_attack_unarmed(17, 12);
    set_all_hitloc_unarmed(6);


    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    seteuid(getuid(this_object()));

    clone_object(OBJ + "hum_arm")->move(TO);
    clone_object(OBJ + "hum_wep")->move(TO);

    command("wear armour");
    command("wield weapon");

    M1
    M2
    if(random(3) == 1)
	clone_object(GEM1)->move(TO, 1);

    if(random(5) == 1)
	clone_object(GEM2)->move(TO, 1);
}  
