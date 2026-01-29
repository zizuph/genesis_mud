// file name:    ~Avenir/common/bazaar/Obj/worn/qbracel
// creator(s):    Grace  May  1995
// last update:            
// purpose:       ornamentation for the lovely dancer
// note:                   
// bug(s):                 
// to-do:                                           

inherit "/std/armour";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_armour ()
{
  set_short("cluster of small silver bracelets");
  set_name("bracelet");
  add_name("bracelets");
  set_adj(({"small","silver"}));
  set_long ("A cluster of silver bracelets all worn together on one "+
            "arm. They collide against each other when worn, making "+
            "pleasant tinny sounds when you move.\n");
                            
  config_wearable_item(A_L_WRIST, 1, 15, this_object());      
  set_ac(6);
  set_keep(1);
  add_prop(OBJ_I_VALUE, 1000);
  add_prop(OBJ_I_WEIGHT, 500);
  add_prop(OBJ_I_VOLUME, 500);
}

