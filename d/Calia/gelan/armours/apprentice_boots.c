/* 	this is an armour of the town Gelan 
 
    coder(s):   Merlin 
 
    history:    11/1/2000   fixed typo                      Maniac
                24. 1.93    installed include define        Merlin 
                 9. 1.93    slight modifications            Merlin 
                 8.11.92    created                         Merlin 
 
    purpose:    these are the standard boots for an apprentice fighter of Gelan 
 
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
 
#define ACMIN   10                              /* min value for armour class */ 
#define ACDIFF  5                               /* diff between max an min */ 
 
/* 
 * Function name: create_armour 
 * Description:   creates the armour 
 * Arguments:     none 
 * Returns:       none 
 */ 
 
void
create_armour() 
{ 
    set_name("boots"); 
 
    set_adj(({"apprentice","leather","standard"})); 
 
    set_short("leather boots"); 
    set_pshort("pairs of leather boots"); 
 
    set_long(BS("These are solid leather boots. They look a little bit " 
              + "worn, but are still in good condition.\n")); 
 
    add_prop(OBJ_I_WEIGHT, 250); 
    add_prop(OBJ_I_VOLUME, 1200); 
 
    set_default_armour( 
        ACMIN + random(ACDIFF),                 /* armour class */ 
        A_LEGS,                                 /* armour type */ 
        ({0,0,0}),                              /* modifier list */ 
        0);                                     /* special wear remove func */ 
 
} 
 
 
