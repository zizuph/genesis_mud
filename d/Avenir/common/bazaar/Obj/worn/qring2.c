// file name:    ~Avenir/common/bazaar/Obj/worn/qring2
// creator(s):    Grace  May  1995
// last update:            
// purpose:       ornamentation for the lovely dancer
// note:                   
// bug(s):                 
// to-do:                                           

inherit "/std/armour";
#include "/d/Avenir/common/bazaar/bazaar.h"
#include <stdproperties.h>

void
create_armour ()
{
  set_short("delicate gold signet ring");
  set_name("signet ring");
  add_name(({"ring", "gold ring"}));
  set_adj(({"delicate","gold"}));
  set_long ("A delicate gold ring with a flattened circular surface "+
            "serving as a signet. There is a design of sorts on the "+
            "signet, and writing on the band of the ring.\n");

  add_item("signet", "On the signet is a small, exquisitely depicted "+
           "picture of two figures, one male and nude, the other female "+
           "and wearing a jeweled girdle. Their bodies are intertwined "+
           "in an erotic position which brings warmth to your cheeks.\n");
  add_item(({"writing", "band", "inside"}),
     "You read the writing:\n   Jazur and Sisera, Passion and Sex, Gods "+
     "of the Twelfth Hour.\n");
  add_cmd_item(({"writing", "band", "inside", "inscription"}), "read",     
     "You read the writing:\n   Jazur and Sisera, Passion and Sex, Gods "+
     "of the Twelfth Hour.\n");


  set_ac(6);
  set_am(({ 0, 0, 0}));
  set_at (A_ANY_FINGER);
  add_prop(OBJ_I_VALUE, 2000);
  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 200);
}
