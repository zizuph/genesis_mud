/* 	this is an armour of the town Gelan 
 
    coder(s):   Merlin 
 
    history:        8.94    armour stats changed            Maniac 
                 9. 1.93    slight modifications            Merlin 
                 8.11.92    created                         Merlin 
 
    purpose:    this is the standard helmet for a fighter fo Gelan 
 
    quests:     none 
    special:    none 
 
    to do:      none 
    bug:        none known 
*/ 
 
inherit "/std/armour"; 
 
#include "armours.h" 
#include <stdproperties.h> 
#include <ss_types.h> 
#include <wa_types.h> 
 
#define ACMIN   15                              /* min value armour class */ 
#define ACDIFF  5                             /* diff between max an min */ 
 
/* 
 * Function name: create_armour 
 * Description:   creates the armour 
 * Arguments:     none 
 * Returns:       none 
 */ 
 
create_armour() 
{ 
 
    set_name("helmet"); 
 
    set_adj(({"fighter","steel","standard"})); 
 
    set_short("steel helmet"); 
    set_pshort("steel helmets"); 
 
    set_long(BS("It's a blue steel helmet. You notice the sign of " 
              + "Gelan on it's front side.\n")); 
 
    add_prop(OBJ_I_WEIGHT, 2000); 
    add_prop(OBJ_I_VOLUME, 256); 
 
    set_default_armour( 
        ACMIN + random(ACDIFF),                 /* armour class */ 
        A_HEAD,                                 /* armour type */ 
        ({0,0,0}),                              /* modifier list */ 
        0);                                     /* special wear remove func */ 
 
} 
 
