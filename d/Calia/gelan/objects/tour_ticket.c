/* This is a ticket for the tour in Gelan */
/* 	this is an abject of the town Gelan 
 
    coder(s):	Deinonychus
 
    history:    XX.YY.ZZ    what done                       who did 
		    21.02.93    created			    Deinonychus
    purpose:	none 
 
    quests:     none 
    special:    none 
 
    to do:      none 
    bug:        none known 
*/ 
 
inherit "/std/object"; 
 
#include "object.h" 
#include <stdproperties.h> 
 
create_object()
{
    set_name("ticket");
    set_short("sightseeing ticket");
    set_long("This is a ticket for the sightseeing tour in Gelan.\n");
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}
