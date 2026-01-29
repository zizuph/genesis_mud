/* 
 * /d/Kalad/common/wild/pass/wep/dw_spear.c
 * Purpose    : An adamantine spear of drow make
 * Located    : Used by the Drows in Undreath
 * Created By : Antharanos  ??.??.??
 * Modified By: 
 * First Modif: 
 */ 

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"

create_weapon()
{
   ::create_weapon();
   set_name("spear");
   add_name("drowwep");
   set_adj("drow");
   add_adj("long");
   set_long("This spear is very long for a weapon of its type, but is "
      +"still amazingly lightweight. It has a long black haft, which "
      +"is carved intricately with a spider motif.\n");
   set_hit(23);
   set_pen(17);
   set_wt(W_POLEARM);
   set_dt(W_IMPALE);
   add_prop(OBJ_I_VALUE,580);
   add_prop(OBJ_I_WEIGHT,3000);
   add_prop(OBJ_I_VOLUME,3000);
}
