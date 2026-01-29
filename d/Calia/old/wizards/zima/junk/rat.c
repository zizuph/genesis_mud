/* Azallio 10 3 1993 */
/* Basically a suped-up version of the Rat from Refna's castle. */

inherit "/std/creature";

#include "/d/Roke/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>

inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/domove";


create_creature()
{

  set_name("rat");
  set_race_name("rat");
  set_short("albino rat");
  set_adj("albino");

  set_long("This albino rat looks rather mean.\n");

  set_stats(({85,90,90,20,20,145}));
  set_alignment(-100);

  set_skill(SS_DEFENCE,20);
  set_skill(SS_UNARM_COMBAT,40);
  
  add_act("chew");
  add_act("take all");
  add_act("eat all");
  add_act("drop all");

  set_act_time(2);
  
  call_out("add_eat",2);

   set_attack_unarmed(0,  100, 100, W_IMPALE, 60, "jaws");
   set_hitloc_unarmed(0, ({ 100 }), 10, "head");
   set_hitloc_unarmed(0, ({ 100 }), 80, "body");

   set_fatigue(9000);
   set_hp(40000);


   set_random_move(2);
}

querry_Knight_prestige(){return 200;}

int chew(string str)
{
  object lik;

  if(present("corpse",E(TO)))
    tell_room(E(TO),"The rat chews on a corpse.\n\n");
  else
    return 1;

  while(lik=present("corpse",E(TO)))
    {
      lik->decay_fun();
    }

  command("take all");
  command("eat all");
  command("drop all");

/* food lets you grow... */

  eat_food(-5000,0); /* keep it hungry... */

  return 1;
}
void add_eat()
{
  set_this_player(this_object());
  add_action("chew", "chew");
}
