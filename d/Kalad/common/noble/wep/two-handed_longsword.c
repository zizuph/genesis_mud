/*
 * /d/Kalad/common/noble/wep/th_sword.c
 * Purpose    : Two handed longsword.
 * Located    : 
 * Created By : Sarr
 * Modified By: Rico
 * First Modif: 15.Feb.97
 */

inherit "/d/Kalad/std/weapon";

#include "/d/Kalad/defs.h"

void
create_weapon()
{
   ::create_weapon();

   set_name("longsword");
   add_name("sword");
   set_adj("steel");
   add_adj(({ "two-handed", "two handed", "long" }));
   set_short("two-handed longsword");
   set_long("This is a very large, steel longsword. The blade is long, "+
    "sharp and heavy. You could do some nice damage with this.\n");

   set_hit(33);
   set_pen(32); 
   set_hands(W_BOTH);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 4550);
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop(OBJ_I_VALUE, 1800);
}

