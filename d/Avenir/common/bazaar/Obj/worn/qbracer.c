// file name:    ~Avenir/common/bazaar/Obj/worn/qbracer
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
  set_short("wide ivory bangle");
  set_name("bangle");
  add_name("bracelet");
  set_adj(({"antique","ivory", "wide"}));
  set_long ("A wide ivory bangle which has yellowed with age. Intertwined "+
            "figures have been carved on its silk-smooth surface.\n");

  add_item(({"figure", "figures"}),
     "There are dozens of people, male and female, some of which are both "+
     "genders, all intertwined in highly provocative and nearly impossible "+
     "positions which are sexual in nature.\n");
                                                              
  config_wearable_item(A_R_WRIST, 1, 15, this_object());      
  set_ac(5);
  set_keep(1);
  add_prop(OBJ_I_VALUE, 900);
  add_prop(OBJ_I_WEIGHT, 500);
  add_prop(OBJ_I_VOLUME, 500);
}
