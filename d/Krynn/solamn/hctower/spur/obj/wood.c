// a piece of wood for the quest in the Spur
// Grace,  Dec 30 1994

inherit "/std/object"; 
#include "../local.h"
#include "/sys/stdproperties.h"                                                     
                                                                                    
void                                                                                
create_object()                                                                     
{                                                                                   
   set_name("_quest_wooden_log"); 
   add_name(({"log", "wood", "firewood", "piece", "pieces", "chunk"}));
   set_short("piece of firewood");
   set_pshort("pieces of firewood");

   add_adj(({"large", "dry"}));

   set_long("This rather large chunk of wood is suitable for burning " +
     "in fireplaces and wood stoves. It is very dry and will likely "+
     "give you splinters if you carry it for too long.\n");

   add_prop(OBJ_I_WEIGHT, 2500);
   add_prop(OBJ_I_VOLUME, 5000);
   add_prop(OBJ_I_VALUE,  50);                                                                                                                                                                           
}     
