#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <const.h>
#include "../stddefs.h"

#pragma save_binary

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/domove";
inherit "/std/act/action";
inherit STRINGLIB;

#define LONG \
  "This is an brown insect with four broad, yellow wings. The wings are delicate looking with brown veins.\n"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_RWING 2
#define H_LWING 3
#define H_LEGS 4

create_creature()
{
  set_race_name("butterfly");
  set_name("bbbb");
  set_adj(({"delicate", "yellow" }));
  set_long(WRAP(LONG));

  set_gender(G_NEUTER);
  add_prop( NPC_I_NO_LOOKS,   1);
  add_prop(LIVE_I_NEVERKNOWN, 1);

  set_base_stat(SS_STR, 5);
  set_base_stat(SS_DEX, 5);
  set_base_stat(SS_CON, 5);
  set_base_stat(SS_INT, 3);
  set_base_stat(SS_WIS, 3);
  set_base_stat(SS_DIS, 5);

  set_skill(SS_DEFENCE, 3);

  set_attack_unarmed(A_BITE,  20, 5, W_IMPALE, 100, "antennae");
   
  set_hitloc_unarmed(H_HEAD,  ({ 15, 25, 20, 20 }), 20, "head");
  set_hitloc_unarmed(H_BODY,  ({ 10, 15, 30, 20 }), 20, "body");
  set_hitloc_unarmed(H_LWING, ({ 15, 25, 20, 20 }), 25, "left wings");
  set_hitloc_unarmed(H_RWING, ({ 10, 15, 30, 20 }), 25, "right wings");
  set_hitloc_unarmed(H_LEGS,  ({ 10, 15, 30, 20 }), 10, "legs");
 
  refresh_mobile();
}

