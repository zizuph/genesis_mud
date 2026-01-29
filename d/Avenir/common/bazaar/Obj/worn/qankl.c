// file name:    ~Avenir/common/bazaar/Obj/worn/qankl
// creator(s):    Grace  May  1995
// last update:            
// purpose:       ornamentation for the lovely dancer
// note:                   
// bug(s):                 
// to-do:                                           

inherit "/std/armour";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include <wa_types.h>
#include <stdproperties.h>

void
create_armour()
{
  set_short("pair of thick gold anklets");
  set_pshort("pairs of thick gold anklets");
  set_name("anklet");
  add_name(({"manacle", "fetter", "anklets"}));
  set_adj(({"gold", "thick"}));
  set_long ("These thick gold anklets resemble fetters.  They are hammered "+
            "and of a rich dark colour. They look quite valuable.\n");

  set_ac(20);
  set_am(({ 0, 0, 0}));
  set_at(A_L_ANKLE);
  add_prop(OBJ_I_VALUE,  3000);
  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 500);
}


