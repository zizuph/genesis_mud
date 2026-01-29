/* Standard hobbits equipment coded by Anri */                                  
inherit "/std/armour";                                                          

#include "/sys/macros.h"                                                        
#include <stdproperties.h>                                                      
#include <wa_types.h>                                                           
#include "/sys/formulas.h"                                                      

void                                                                            
create_armour()                                                                 
{ set_name("shield");                                                           
   set_short("large oval shield");                                               
   set_long("This large oval shield is made of wood "+
   "with iron plating on the front to make it suffer "+
   "damage more readily.\n");
   set_adj(({"large","oval"}));
   set_ac(10);                                                                     
   set_at(A_SHIELD);                                                               
   set_am(({0,-1,1}));                                                             
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10));                                       
   add_prop(OBJ_I_VOLUME,150);                                                     
   add_prop(OBJ_I_WEIGHT,590);                                                     
}                                                                               

