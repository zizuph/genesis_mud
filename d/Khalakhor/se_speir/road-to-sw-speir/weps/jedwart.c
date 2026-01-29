/*
 * A Jedwart stave in the camp at the SE - SW road
 * Tapakah, 09/2021
 */

#pragma strict_types

#include "wa_types.h"
#include "../defs.h"

inherit KSTDWEAPON;

void
create_khalakhor_weapon ()
{
  set_name("stave");
  add_adj(({"long-bladed", "jedwart"}));
  set_short("long-bladed jedwart stave");
  set_long("This polearm looks a bit like a bardiche, but the blade is, "+
           "albeit as long, somewhat lighter and thinner. Still, it is "+
           "very sharp and looks excellently balanced on the five foot "+
           "handle.\n");
  set_default_weapon(30, 30, W_POLEARM, W_SLASH, W_BOTH);
}
