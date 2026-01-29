/* 	this is an armour of the town Gelan 
 
    coder(s):   Merlin 
 
    history:        8.94    armour stats changed            Maniac
                 9. 1.93    slight modifications            Merlin 
                 8.11.92    created                         Merlin 
 
    purpose:    these are the standard gauntlets for an experienced fighter of 
                Gelan 
 
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
 
#define ACMIN   20                              /* min value armour class */ 
#define ACDIFF  5                              /* diff between max an min */ 
 
/* 
 * Function name: create_armour 
 * Description:   creates the armour 
 * Arguments:     none 
 * Returns:       none 
 */ 
 
create_armour() 
{ 
 
    set_name("gauntlets"); 
 
    set_adj(({"experienced","chain","standard"})); 
 
    set_short("chain gauntlets"); 
    set_pshort("chain gauntlets"); 
 
    set_long(BS("These are solid chain gauntlets, as they are use by the " 
              + "fighter guards of Gelan. These have the golden sign of " 
              + "Gelan on it.\n")); 
 
    add_prop(OBJ_I_WEIGHT, 800); 
    add_prop(OBJ_I_VOLUME, 102); 
 
    set_default_armour( 
        ACMIN + random(ACDIFF),                 /* armour class */ 
        A_ARMS,                                 /* armour type */ 
        ({0,0,0}),                              /* modifier list */ 
        0);                                     /* special wear remove func */ 
 
} 
 
