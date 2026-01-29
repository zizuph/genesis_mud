/*   drum.c
 *
 * A small indian drum
 *
 * Baldacin@Genesis, July 2003
 */
inherit "/std/object";
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("drum");
    set_adj("indian");                    
    set_long("Consisting of a cylindrical body covered at "+ 
     "both ends by a tight membrane. It might be "+ 
     "possible to 'drum' it.\n");
     
    add_prop(OBJ_I_SHIPWRECK_EQUIPMENT, 1);
    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VALUE, 5);
    
}

int
drum()
{
    write("A booming sound is produced as you drum your hands "+
      "on the old indian drum.\n"+
	  "Boom-boom boom-boom\n");
    say(QCTNAME(this_player()) + " drums "+ HIS(TP) + 
      " hands on the old indian drum, creating a booming sound.\n"+
	  "Boom-boom boom-boom\n");	  
		 
    return 1;
}

void
init()
{
   ::init();
   add_action(drum, "drum");
}