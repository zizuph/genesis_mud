// file name:    ~Avenir/common/bazaar/Obj/worn/qring1
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
create_armour ()
{
  set_short("ruby ring");
  set_name(({"ring", "ruby ring"}));
  set_adj(({"large","ruby","gold"}));
  set_long ("A filigree gold ring inset with a large ruby. "+
            "There is writing on the inside of the band.\n");

  add_item("ruby", "It is a large, slightly flawed ruby.\n");
  add_item(({"writing", "band", "inside"}),
     "You read the writing: To Qalita from Horzun.\n");
  add_cmd_item(({"writing", "band", "inside", "inscription"}),
     "read", "You read the writing: To Qalita from Horzun.\n");

  set_ac(6);
  set_am(({ 0, 0, 0}));
  set_at (A_ANY_FINGER);
  add_prop(OBJ_I_VALUE, 2500);
  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 200);
}
