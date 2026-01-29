/*
 * /d/Kalad/common/noble/wep/s_dagger.c
 * Purpose    : A slim silver dagger.
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

   set_name("dagger");
   set_adj("slim");
   add_adj("silver");
   set_short("slim silver dagger");
   set_long("This dagger is made of very fine silver. Its edge "+
      "looks razor sharp.\n");

   set_hit(14);
   set_pen(16);
   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 450);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_VALUE, 450);
}

