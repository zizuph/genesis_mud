// name: Langiston   /d/Avenir/common/ships/kalad/keats.c
// creator(s):   Cirion, May 1996
// last update:  
// purpose:      Ship Captain for the Avatar
// note:         
// bug(s):
// to-do:
// revision:     

#include <ss_types.h>
#include "/d/Avenir/common/ships/ship.h"

#define ETO     environment()
#define KTICKET  SPAR_DIR + "ticket"
#define KPRICE   55

#pragma save_binary

inherit "/d/Genesis/ship/captain";

void
create_monster()
{
  set_name("langiston");
  add_name("captain");
  set_title("Captain of the Avatar");
  set_living_name("langiston");
  set_race_name("human");
  set_adj(({"tall", "muscular"}));
  set_stats(({ 80, 60, 90, 80, 60, 70 }));
  set_skill(SS_SWIM, 100);
  set_skill(SS_WEP_SWORD,75);
  set_skill(SS_DEFENCE,75);
  set_skill(SS_PARRY,75);
  set_skill(SS_AWARENESS,50);
  
  LONG("He is an insignificant looking guy.\n");
  set_alignment(-100+random(200));
  set_appearance(80);
  add_prop(LIVE_I_SEE_DARK, 2);

  add_ask(({"where","where to","from"}),
         "say This ship sails between the Bazaar in Sybarus and the Deep "
        +"Realms of Kalad.",1);

  set_ticket(KTICKET);
  set_price(KPRICE);

  trig_new("%s 'introduces' %s", "intro_me");
  seteuid(getuid());
}    

void equip_me()
{
#if 0
  clone_object(KALAD_DIR + "rapier")->move(this_object(),1);
  clone_object(KALAD_DIR + "shirt")->move(this_object(), 1);
  command("wear all");
  command("wield all");
#endif
}

int
intro_me (string s1, string s2)
{
  string *foo;
  object who;
  
  if (sizeof (foo = explode (s2, " as:\n")) != 2)
    return 0;
  foo = explode (foo[1], " ");

  if (!(who = find_player(lower_case(foo[0]))))
    who = find_player(lower_case(foo[1]));

  if (!who)
    return 0;

  if (who->query_met(this_object()))
    return 1;

  foo[0] = "introduce myself to " + who->query_real_name();
  set_alarm (2.0, 0.0, "command", foo[0]);
  
  return 1;
}

string race_sound()
{
  return "shouts";
}

