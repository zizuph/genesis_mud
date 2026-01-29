 /* One of the two pieces of armour worn by Avena
 code (c) 1998 Damian Horton
 Redone for Raumdor, March 2001
 */

#pragma strict_types
#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include "/d/Cirath/defs.h"
#include <formulas.h>

void create_armour()
{
  set_name("bracers");
  set_pname("bracers");
  set_short("bone bracers");
  set_pshort("bone bracers");
  set_long("These bracers were created by hollowing out the bone of some "+
	   "very large creature. Very thick, they provide excellent "+
	   "protection to ones arms.\n");
  set_adj("bone");

  set_ac(26);
  set_am(({2,-1,-1}));
  set_at(A_ARMS);

  add_prop(OBJ_I_WEIGHT, 2100);
  add_prop(OBJ_I_VOLUME, 2000);
  add_prop(OBJ_I_VALUE, (F_VALUE_ARMOUR(26)) - random(50) + random(50)); 
}










