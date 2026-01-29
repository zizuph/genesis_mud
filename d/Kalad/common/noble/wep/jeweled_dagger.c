/*
 * /d/Kalad/common/noble/wep/j_dagger.c
 * Purpose    : A simple dagger with jewels ornamenting it.
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
   set_adj("jewelled");
   set_short("jewelled dagger");
   set_long("Many beautiful jewels adorn this ornate dagger. Although "+
      "it looks more ceremonial than sturdy, it does have a very sharp "+
      "edge.\n");

   set_hit(14);
   set_pen(14);
   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);

   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_VALUE, 600);
}

