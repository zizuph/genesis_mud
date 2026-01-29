/*
 * /d/Kalad/common/noble/wep/s_lsword.c
 * Purpose    : Steel longsword.
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
   set_short("steel longsword");
   set_long("This is a long, narrow bladed sword made of steel. The "+
    "blade is polished to a high gleam and the longsword looks well "+
    "taken care of.\n");

   set_hit(29);
   set_pen(25); 
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 2730);
   add_prop(OBJ_I_VOLUME, 2000);
   add_prop(OBJ_I_VALUE, 1000);
}
