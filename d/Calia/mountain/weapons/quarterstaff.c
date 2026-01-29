/*
    A quarterstaff used by lesser krougs.

    Coder(s) : Maniac

    History : 
          4/8/95             Created             Maniac
         14/3/99             Plurals updated     Maniac
*/

inherit "/std/weapon";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

void
create_weapon()
{
  set_name("quarterstaff");
  add_name("staff");
  set_pname("quarterstaves"); 
  add_pname("quarterstaffs"); 
  set_adj("wooden");
  set_short("wooden quarterstaff"); 
  set_pshort("wooden quarterstaves"); 
  set_long("An ordinary looking weapon used by lesser kroug warriors. "+
           "It's just a stout wooden pole.\n"); 
  set_hit(34);
  set_pen(10);
  set_wt(W_POLEARM);
  set_dt(W_BLUDGEON);
  set_hands(W_BOTH);
  add_prop(OBJ_I_WEIGHT, 4000);
  add_prop(OBJ_I_VOLUME, 3000);
}
