/* From Olorin's ithil_man.c                           */
/* This file is /d/Gondor/minas/npc/gondor_man.c       */
/* Dunstable, March 1993                               */
/* Olorin, July 1993                                   */
inherit "/d/Gondor/minas/npc/mtirith_monster";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void
create_monster()
{
  int rnd;
  seteuid(getuid());
  
  set_race_name("human"); 
  set_pshort("men");
  set_adj("strong");
  set_long(BSN("A tall dark-haired man from Gondor or Lebennin in the " +
    "south, very noble in appearance."));
    
  ::create_monster();

  rnd = random(30);
  default_config_npc(50+rnd/3);
  set_base_stat(SS_INT, 35+rnd/2);
  set_base_stat(SS_WIS, 35+rnd/2);
  set_base_stat(SS_DIS, 45+rnd/2);
  set_alignment(250-rnd*10);
  set_skill(SS_WEP_SWORD,55+rnd/3);
  set_skill(SS_WEP_POLEARM,45+rnd/3);
  set_skill(SS_WEP_CLUB, 45+rnd/3);
  set_skill(SS_WEP_AXE,  45+rnd/3);
  set_skill(SS_WEP_KNIFE,45+rnd/3);
  set_skill(SS_PARRY,    55+rnd/2);
  set_skill(SS_DEFENCE,  65+rnd/2);
  add_prop(CONT_I_HEIGHT,170+rnd);
  add_prop(CONT_I_WEIGHT,75000+rnd*500);
  add_prop(CONT_I_VOLUME,70000+rnd*500);    
  add_prop(LIVE_I_SEE_DARK,0);

  set_chat_time(25+random(15));
  add_chat("I do not fear the shadow!");
  add_chat("If only orcs had the nerve to cross the Anduin!");
  add_chat("I don't like the shadow in the East.");
  add_chat("I will defend Minas Tirith to the death.");

  set_cchat_time(5+random(10));
  add_cchat("You're dead!");
  add_cchat("For Gondor!");
  add_cchat("May the Valar aid you in the next life!");

  set_act_time(15+random(15));
  add_act("tap");
  add_act("bow");
  add_act("get all from corpse");
  add_act("chuckle");
  add_act("smile");

  set_cact_time(2+random(2));
  add_cact("frown"); 
}

query_knight_prestige() { return (-5); }

