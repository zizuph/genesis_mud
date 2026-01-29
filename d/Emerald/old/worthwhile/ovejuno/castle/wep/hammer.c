/*Hammer coded by Glindor(?), unknown date
Revised by Marisol to be used for the smith in the new Re Albi
Marisol Ramos (1/20/98) */


inherit "/std/weapon";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>


create_weapon()
{
  set_name("hammer");
  set_adj("heavy");
  set_short("heavy hammer");
  set_long("A heavy weaponsmith-hammer.\n");


  set_hands(W_ANYH);
  set_hit(15);
  set_pen(15);
  set_wt(W_CLUB);
  set_dt(W_BLUDGEON);

  add_prop(OBJ_I_WEIGHT,8000);
  add_prop(OBJ_I_VOLUME,2000);

}
  
