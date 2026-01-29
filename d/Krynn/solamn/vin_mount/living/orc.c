/* created by Aridor 06/19/93 */


#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/money.h"

inherit M_FILE


void
create_krynn_monster()
{
    int i;

    set_name("hobgob");
    set_race_name("hobgoblin");
    set_living_name("dirty hobgoblin killer");
    set_adj("dirty");
    add_adj("killer");

    set_short("dirty hobgoblin");
    set_long("The hobgoblin is very dirty but nonetheless lethal.\n");


    for(i=0; i<6; i++)
        set_base_stat(i, 50 + random(20));
    set_skill(SS_DEFENCE, 40 + random(10));
    set_skill(SS_WEP_SWORD, 30 + random(40));

    set_alignment(-150);
    set_knight_prestige(100);

    NEVERKNOWN;

    set_all_attack_unarmed(30, 40);
    set_all_hitloc_unarmed(30);

    set_aggressive(1);
    add_prop(OBJ_I_INVIS,1);



    if (IS_CLONE)
      {
	  set_alarm(1.0,0.0,"arm_me");
	  set_alarm(10.0,0.0,"no_aggression");
      }
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(OBJ + "orc_sword")->move(TO);
    MONEY_MAKE_CC(random(3)+3)->move(TO);
    command("emote jumps down on you!");
    change_prop(OBJ_I_INVIS, 0);
    command("wield weapon");
    set_alarm(2.0,0.0,"command","drop copper coins");
    set_alarm(4.0,0.0,"command","oops");
    set_alarm(6.0,0.0,"command","get all");
}


no_aggression()
{
    set_aggressive(0);
}
