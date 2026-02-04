/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/weapon";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <comb_mag.h>


void
create_weapon()
{
   set_name("dagger");
   set_adj(({"small", "silvery"}));
    set_short("small silvery dagger");
   
  set_long("It is a small thin dagger, made from some bright silvery steel. " +
   "Upon its hilt is a star of ivory.\n");
   set_hit(12);
   set_pen(12);
   set_wt(W_KNIFE);
   
   set_dt(W_IMPALE);
   set_hands(W_ANYH);
   add_prop("mystic_weapon", 1);
   
}

