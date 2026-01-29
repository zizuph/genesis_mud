/* Ckrik June 1998
 */

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/remember.c";
inherit "/d/Earthsea/lib/width_height.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>

#define WEP "/d/Earthsea/ckrik/marisol/staff.c"
#define BARMOUR "/d/Earthsea/ckrik/marisol/shirt.c"
#define LEG "/d/Earthsea/ckrik/marisol/pants.c"

void
create_earthsea_monster()
{
  ::create_earthsea_monster();
  set_name("Kynes");
  set_adj("young");
  add_adj("goat-herding");
  set_race_name("human");
  set_gender(G_MALE);
  set_short("young goat-herding human");
  set_long("A young goat-herder. His eyes carefully watch his " +
	   "small herd of goats. He is always on constant " +
	   "alert for wolves or even worse, goat-thieves.\n");

  set_title("the Goat Herder");
  set_height("tall");
  set_width("normal");
  set_act_time(50);
  
  set_stats(({60, 55, 60, 45, 45, 55}));

  set_hp(query_max_hp());
  set_all_hitloc_unarmed(50);
  
  set_skill(SS_DEFENSE,70);
  set_skill(SS_PARRY,50);
  set_skill(SS_WEP_POLEARM, 65);
  set_skill(SS_AWARENESS, 60);
  set_skill(SS_BLIND_COMBAT,50);
  
  add_act("emote quickly scans the area.");
  add_act("say Those goat-thieves better not even try to steal my goats.");
  add_act("emote starts counting his goats.");

  set_alignment(55);

}

int
arm_me()
{
    object weapon, shirt, pants;

    weapon = clone_object(WEP);
    weapon->move(this_object());
    shirt = clone_object(BARMOUR);
    shirt->move(this_object());
    pants = clone_object(LEG);
    pants->move(this_object());
    this_object()->command("wield all");
    this_object()->command("wear all");
    (MONEY_MAKE_SC((random(60) + 1)))->move(this_object());
    return 1;
}

int
query_knight_prestige()
{
    return -30;
}
