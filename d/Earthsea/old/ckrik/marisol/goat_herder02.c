/* Ckrik June 1998
 */

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/remember.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>

#define WEP "/d/Earthsea/ckrik/marisol/staff.c"
#define BARMOUR "/d/Earthsea/ckrik/marisol/shirt.c"
#define LEG "/d/Earthsea/ckrik/marisol/pants.c"
#define FLUTE "/d/Earthsea/ckrik/marisol/panflute.c"

void
create_earthsea_monster()
{
  ::create_earthsea_monster();
  set_name("dunst");
  set_adj("small");
  add_adj("day-dreaming");
  set_race_name("human");
  set_gender(G_MALE);
  set_short("small day-dreaming human");
  set_long("A small goat-herder. It seems that he is not paying " +
	   "much attention to his goats. He is busy engaging in " +
	   "reverie.\n");

  set_act_time(50);
  
  set_stats(({45, 55, 45, 55, 55, 45}));

  set_hp(query_max_hp());
  
  set_skill(SS_DEFENSE,70);
  set_skill(SS_PARRY,50);
  set_skill(SS_WEP_POLEARM, 65);
  set_skill(SS_AWARENESS, 60);
  set_skill(SS_BLIND_COMBAT,50);
  
  add_act("emote day-dreams about being just like Ogion.");
  add_act("say I want to be a wizard some day.");
  add_act("emote wonders what it is like to be a Wizard of Roke.");
  add_act("play pan flute");

  set_alignment(75);

}

int
arm_me()
{
  object weapon, shirt, pants, flute;
  
  weapon = clone_object(WEP);
  weapon->move(this_object());
  shirt = clone_object(BARMOUR);
  shirt->move(this_object());
  pants = clone_object(LEG);
  pants->move(this_object());
  flute = clone_object(FLUTE);
  flute->move(this_object());
  this_object()->command("wield knife");
  this_object()->command("wear all");
  (MONEY_MAKE_SC((random(60) + 1)))->move(this_object());
  return 1;
}

int
query_knight_prestige()
{
  return -35;
}
