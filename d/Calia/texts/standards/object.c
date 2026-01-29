/* 	this is an abject of the town Gelan 
 
    coder(s):	Standard 
 
    history:    XX.YY.ZZ    what done                       who did 
    purpose:	none 
 
    quests:     none 
    special:    none 
 
    to do:      none 
    bug:        none known 
*/ 
 
inherit "/std/object"; 
 
#include "object.h" 
#include "/sys/stdproperties.h" 
 
create_object() 
{ 
 
    set_name("%"); 
 
    set_adj("%"); 
 
    set_short("%"); 
    set_long(BS("%\n")); 
 
    add_prop(OBJ_I_WEIGHT, %); 
    add_prop(OBJ_I_VOLUME, %); 
 
} 
 
/* 
 * Function name: 
 * Description:   none 
 * Arguments:     none 
 * Returns:       none 
 */ 
 
