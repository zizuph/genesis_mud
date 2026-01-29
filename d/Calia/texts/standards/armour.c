/* 	this is an armour of the town Gelan 
 
    coder(s):   standard 
 
    history:    DD.MM.YY    what done                       who did 
 
    purpose:    none 
 
    quests:     none 
    special:    none 
 
    to do:      none 
    bug:        none known 
*/ 
 
inherit "/std/armour"; 
 
#include "armour.h" 
#include <stdproperties.h> 
#include <ss_types.h> 
#include <wa_types.h> 
 
create_armour() 
{ 
 
    set_name("%"); 
 
    set_adj({"%","%","%"})); 
 
    set_short("%"); 
    set_pshort("%"); 
 
    set_long(BS(".\n")); 
 
    add_prop(OBJ_I_WEIGHT, %); 
    add_prop(OBJ_I_VOLUME, %); 
 
    set_default_armour( 
        %,                                      /* armour class */ 
        A_%,                                    /* armour type */ 
        ({%,%,%}),                              /* modifier list */ 
        0);                                     /* special wear remove func */ 
 
} 
 
/* 
 * Function name: 
 * Description:   none 
 * Arguments:     none 
 * Returns:       none 
 */ 
 
