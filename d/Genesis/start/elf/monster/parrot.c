#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include "../stddefs.h"
#include "../tefyma.h"

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/domove";
inherit "/std/act/action";
inherit STRINGLIB;

#define LONG \
  "It's a large bird with plumage in all the colours of the rainbow, and " +\
  "some more. It has a large, powerful beak and a stocky body.\n"

#define START_PHRASES \
  ({ \
       "Yo ho ho, and a bottle of rum.", \
       "Nevermore." \
  })

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_RWING 2
#define H_LWING 3
#define H_LEGS 4

string *phrases;

void peer(object obj);

create_creature()
{
  set_race_name("bird");
  set_name(({"parrot", "polly"}));
  set_adj(({"large", "brightly-coloured"}));
  set_long(WRAP(LONG));

  set_gender(G_NEUTER);

  set_base_stat(SS_STR, 5);
  set_base_stat(SS_DEX, 25);
  set_base_stat(SS_CON, 5);
  set_base_stat(SS_INT, 3);
  set_base_stat(SS_WIS, 3);
  set_base_stat(SS_DIS, 25);

  add_prop(NPC_I_NO_LOOKS, 1);
  add_prop(LIVE_I_NEVERKNOWN);
  add_prop(CONT_I_WEIGHT,  5 KG);
  add_prop(CONT_I_HEIGHT, 30 CM);
  add_prop(CONT_I_VOLUME,  5 LITRES);

  set_skill(SS_DEFENCE, 10);

  set_attack_unarmed(A_BITE,  20, 20, W_SLASH, 100, "beak");
   
  set_hitloc_unarmed(H_HEAD,  ({ 15, 25, 20, 20 }), 20, "head");
  set_hitloc_unarmed(H_BODY,  ({ 10, 15, 30, 20 }), 20, "body");
  set_hitloc_unarmed(H_LWING, ({ 15, 25, 20, 20 }), 25, "left wing");
  set_hitloc_unarmed(H_RWING, ({ 10, 15, 30, 20 }), 25, "right wing");
  set_hitloc_unarmed(H_LEGS,  ({ 10, 15, 30, 20 }), 10, "tail");

  set_act_time(0); 
  add_act("say @@random_phrase@@");

  refresh_mobile();
}


string random_phrase()
{
  if (!phrases)
    phrases = START_PHRASES;

  return phrases[random(sizeof(phrases))];
}

  
catch_msg(mixed str, object obj)
{
  string msg, a, b;

  if (!phrases)
    phrases = START_PHRASES;

  if (stringp(str) &&
      sscanf(str, "@@query_The_name:%s@@ @@race_sound:%s@@: %s\n", 
	     a, b, msg) == 3) {

    phrases += ({ msg });

    if (obj) {
      peer(obj);
    }
  }
}

void peer(object obj)
{
  if (obj && present(obj, environment())) {
    obj->catch_msg(QCTNAME(this_object()) + " peers quizzically at you.\n");
  }
}
