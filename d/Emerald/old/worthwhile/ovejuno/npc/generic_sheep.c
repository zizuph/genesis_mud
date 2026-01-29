/* Coded by Ckrik June 1998
 * A goat.
 *Modified by Marisol (08/21/98) to be used as a sheep in the 
 *village of Ovejuno in Emerald.
*/

inherit "/d/Emerald/std/emerald_creature.c";
inherit "/std/combat/unarmed.c";
inherit "/std/act/action.c";

#include "wa_types.h"
#include "ss_types.h"
#include "macros.h"
#include "filter_funs.h"
#include "/sys/stdproperties.h"

#define A_BITE 101
#define A_KICK 102

#define H_BODY 0
#define H_HEAD 1
#define H_R_FORELEG 10
#define H_L_FORELEG 11
#define H_R_HINDLEG 20
#define H_L_HINDLEG 21

void
create_sheep();

void
create_emerald_creature()
{
  set_name("sheep");
  set_pname("sheep");
  set_race_name("sheep");

  set_attack_unarmed(A_BITE, 20, 30, W_BLUDGEON, 15, "bite");
  set_attack_unarmed(A_KICK, 28, 25, W_BLUDGEON, 50, "kick");

  set_hitloc_unarmed(H_BODY, 15, 40, "body");
  set_hitloc_unarmed(H_HEAD, 15, 20, "head");
  set_hitloc_unarmed(H_R_FORELEG, 15, 10, "right foreleg");
  set_hitloc_unarmed(H_L_FORELEG, 15, 10, "left foreleg");
  set_hitloc_unarmed(H_R_HINDLEG, 15, 10, "right hind leg");
  set_hitloc_unarmed(H_L_HINDLEG, 15, 10, "left hind leg");

  change_prop(OBJ_I_WEIGHT, 50000);
  change_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT));
  change_prop(CONT_I_WEIGHT, 50000);
  change_prop(CONT_I_VOLUME, query_prop(CONT_I_WEIGHT));
  create_sheep();
}

void
create_sheep()
{
}
