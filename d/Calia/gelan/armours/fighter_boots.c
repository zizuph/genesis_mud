/* 	this is an armour of the town Gelan 

    coder(s):   Merlin 

    history:        8.94    armour stats changed            Maniac
		 9. 1.93    slight modifications            Merlin 
		 8.11.92    created                         Merlin 
                9.29.97  typo corrected        Porta

    purpose:    these are the standard boots for a fighter of Gelan 

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
#define ACDIFF  5                              /* diff between max an min */ 

/* 
 * Function name: create_armour 
 * Description:   creates the armour 
 * Arguments:     none 
 * Returns:       none 
 */ 

create_armour() 
{ 

    set_name("boots"); 

    set_adj(({"fighter","leather","standard"})); 

    set_short("leather boots"); 
    set_pshort("pairs of leather boots");

    set_long(BS("These are fine leather boots.\n")); 

    add_prop(OBJ_I_WEIGHT, 350); 
    add_prop(OBJ_I_VOLUME, 1800); 

    set_default_armour( 
      ACMIN + random(ACDIFF),                 /* armour class */ 
      A_LEGS,                                 /* armour type */ 
      ({0,0,0}),                              /* modifier list */ 
      0);                                     /* special wear remove func */ 

} 

