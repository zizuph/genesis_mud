/*
 * /d/Ravenloft/core/darkon/martira_bay/arm/cpants.c
 *
 * Pants used by Zombie Citizens of Il Aluk
 * Coded by Mirandus with help from Mercade
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define ADJ1 ({"extravagant","shimmering"})
#define ADJ2 ({"golden","platinum"})

void
create_armour()
{
   string adj1 = one_of_list(ADJ1);
   string adj2 = one_of_list(ADJ2);
   
   set_name("necklace");
   add_name("medallion");
   set_adj(adj1);
   add_adj(adj2);
   set_short(adj1 + " " + adj2 + " necklace");
   set_long("A long, beautifully-crafted "+adj2+" chain necklace. It is a "+
      "symbol of servitude to the beliefs and purpose of the Thanarians "+
      "and the patron god of humanity, Thanar.\n"+
      "A symbol of a dark sun hangs from its end.\n");
   set_at(A_NECK);
   set_ac(1);
   add_prop(OBJ_I_VALUE,1500);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
}
