/*
 * Reeds used to make paper for Bilbo's writing quest
 * by Finwe, March 1999
 */

inherit "/std/object";                                                          
#include <stdproperties.h>                                                      
#include <macros.h>                                                             
                                                                                
void                                                                            
create_object() {                                                               
    set_name("reeds");                                                              
    add_name(({"_imladris_reeds_", "pile of reeds", "reeds"}));
    set_short("pile of reeds");                                                     
    set_pshort("piles of reeds");                                                   
    set_long("This is a large pile of reeds. They are various " +
        "plants that grow alongside rivers and streams. They are " +
        "often harvested to make paper.\n");
    add_prop(OBJ_I_VALUE,50);                                                      
    add_prop(OBJ_I_VOLUME,10000);                                                 
    add_prop(OBJ_I_WEIGHT,1000);                                                  
}                                                                               

