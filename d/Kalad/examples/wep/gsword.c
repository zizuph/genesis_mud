/*
 * /d/Kalad/examples/wep/gsword.c
 * Purpose    : A sword used as example code.
 * Located    : Cloned by dark guard: (not yet, actually)
 *              => ~Kalad/examples/npc/dguard.c
 * Created By : Rico  4.May.95
 * Modified By: Rico 13.Oct.96
 *              Rico 27.Feb.97
 *              Rico  8.Mar.97
 *              Rico  1.Apr.97
 */

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

void
create_weapon()
{
   ::create_weapon();

   set_name("sword");
   set_short("rough sword");
   set_adj("rough");
   set_long("This sword looks to have been through many battles.  "+
      "It is stained with blood and has many knicks and deep "+
      "scratches in it.  Even so, it looks like a formidable "+
      "weapon.\n");

   /* For these next few functions, you could just use a 
      single function, set_default_wep */
   set_hit(random(15) + 10); /* hit class with vary from 10 - 25 */
   set_pen(random(15) + 10); /* pen class with vary from 10 - 25 */
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH); /* Wieldable in any hand. */

   /* The macros for these next 3 functions are defined in
      ~Kalad/defs.h and need to have ~Kalad/std/weapon.c inherited. */
   KVWEP(50);
   KWWEP(80);
   KVOL(steel);  /* the sword is steel */
}

