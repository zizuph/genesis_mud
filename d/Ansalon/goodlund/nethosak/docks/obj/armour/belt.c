/*
 * /d/Ansalon/goodlund/nethosak/docks/obj/armour/belt.c
 *
 * glain
 *
 * Belt worn by all the minotaurs.  Will prolly be move a dir.
 *
 */
#pragma strict_types

inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

void 
create_armour()
{
   set_name("belt");
   set_adj("leather");
   add_adj("wide");
   set_short("wide leather belt");
   set_ac(5);
   set_at(A_WAIST);
   set_long("A belt made from leather with a large steel buckle.  " +
      "It is unusually wide, covering the entire waist.\n");

   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(5, A_WAIST));
}