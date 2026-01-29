/* An ogre's skull. Found in the pool at /blackwall/valley1/valley1_34
   It is of no use.

   Code (c) 1999 to Damian Horton (BKA Casimir)
*/

inherit "/std/object";

#include <stdproperties.h>

create_object()
{
    set_name("skull");
    set_adj("large");
    add_adj("ugly");
    set_short("large skull");
    set_long("A large skull, too big to have come from a human. Though "+
	     "it presents the shape of a human skull, it is slightly "+
	     "deformed. It is also discolored, being more of a dirty "+
	     "brown in coloration, rather than ivory.\n");
 
    add_prop(OBJ_I_WEIGHT, 5600);  
    add_prop(OBJ_I_VOLUME, 2300);
    add_prop(OBJ_I_VALUE, 0);
}





