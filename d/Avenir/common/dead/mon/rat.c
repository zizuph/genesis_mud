// -*-C++-*-
// file name: ~Avenir/common/dead/mon/rat.c
// creator(s):  Lilith June 2021
// last update: 
// purpose:     inhabitant of catacombs
// note: 
// bug(s):
// to-do:     

inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";

#include <tasks.h>
#include "../dead.h"

#define H_BODY 0
#define H_TAIL 2
#define H_HEAD 4

void
create_creature ()
{
    if (!IS_CLONE)
        return;
  
    set_name ("rat");
    add_name ("_Dead_Isle_rat", "_crypt_crawler");
    set_short ("large swamp rat");
    add_adj(({"large", "sleek", "swamp"}));
  
    set_race_name ("rat");
    set_long ("This rat is identical to all the others you've seen. "
	    +"It is of an indeterminant color somewhere between gray "
		+"and brown, with a very long and very pale tail. "
		+"It looks at you with eerie intelligence in its eyes.\n");
  
  set_gender (G_NEUTER);
  set_stats ( ({15,15,15,1,1,5}) );
  
  set_random_move(5);
  
  set_skill (SS_UNARM_COMBAT, 10);
  set_skill (SS_DEFENSE, 50);
  // hard to hit becausw he's so small.
  set_stat_extra(SS_DEX, 100);
  // fast little guy
  add_prop (LIVE_I_QUICKNESS, 50);
  
  set_attack_unarmed (0, 20, 20, W_IMPALE, 50,"teeth");
  set_attack_unarmed (2, 20, 20, W_SLASH, 50,"paws");
  
  set_hitloc_unarmed ( H_BODY, 10, 10, "body");
  set_hitloc_unarmed ( H_HEAD, 10, 20, "head");
  set_hitloc_unarmed ( H_TAIL, 10, 10, "tail");

  add_prop (LIVE_I_SEE_DARK, 5);
  add_prop (CONT_I_WEIGHT, 2000);
  add_prop (CONT_I_VOLUME, 2000); 
  add_prop (CONT_I_MAX_WEIGHT, 4000);
  add_prop (CONT_I_MAX_VOLUME, 5000);
  add_prop (OBJ_I_WEIGHT, 2000);
  add_prop (OBJ_I_VOLUME, 2000);
  
  set_act_time(10);
  add_act("emote scurries by.");
  add_act("emote stands on it's back legs and sniffs the air.");
  add_act("emote squeaks and scurries off.");
  add_act("emote nibbles on a corpse.");
  
  set_cact_time(2);
  add_cact("scream");
  add_cact("emote squeals.");
  add_cact("emote flashes sharp teeth at you.");

}  
