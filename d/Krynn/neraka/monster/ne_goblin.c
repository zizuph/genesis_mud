/* Standard Goblin Guards that patrol Tantallon*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>

inherit M_FILE

#define M1   MONEY_MAKE_SC(random(15))->move(TO);

void
create_krynn_monster()
{
    int i;

    set_name("goblin");
    set_race_name("goblin");
    set_long("This is one of the many goblins in the dragon highlord army.\n");
    set_adj("evil");

    set_random_move(30);

    set_pick_up(30);

    for (i = 0; i < 6; i++)
        set_base_stat(i, 10 + random(10));
    set_skill(SS_DEFENCE, random(5) + 10);
    set_skill(SS_WEP_SWORD, 45);

    set_alignment(-200);
    set_knight_prestige(150);

    NEVERKNOWN;

    set_all_attack_unarmed(10, 10);
    set_all_hitloc_unarmed(10);


    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me");
}

void
arm_me()
{
    seteuid(getuid(this_object()));

    clone_object(OBJ + "gob_arm")->move(TO);
    clone_object(OBJ + "gob_wep")->move(TO);

    command("wear armour");
    command("wield weapon");

    M1

}  
