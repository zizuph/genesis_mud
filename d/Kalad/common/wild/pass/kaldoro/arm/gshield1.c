/* 
 * /d/Kalad/common/wild/pass/kaldoro/arm/gshield1.c
 * Purpose    : A standard shield for the Kaldoro guards.
 * Located    : ../npc/kguard1.c and ../npc/kguard2.c
 * Created By : Rico 17.Jan.95
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour.c";

#include "/d/Kalad/defs.h"

create_armour()
{   
   ::create_armour();
   
   set_name("shield");
   add_adj("rough");
   
   set_short("rough shield");
   set_long("This shield has seen a great deal of action.  "+
      "It is blood stained and dented with with many "+
      "gouges hewn out of it's surface.  It gets the job "+
      "done though.\n");
  
   add_prop(OBJ_I_WEIGHT, 2000);
   add_prop(OBJ_I_VOLUME, 900);
   add_prop(OBJ_I_VALUE, 200);

   set_ac(15);
   set_at(A_L_ARM);
}
