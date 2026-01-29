/*   comb.c
 *
 * A small bone comb
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
    set_name("comb");
    set_adj("bone");
    add_adj("engraved");
    set_short("engraved bone comb");                    
    set_long("A thin, toothed comb used to untangle, style, or "+
      "hold hair. You can 'comb' your hair with it.\n"); 
      
    add_prop(OBJ_I_SHIPWRECK_EQUIPMENT, 1);	
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VALUE, 5);
    
}

int
comb(string str)
{
    notify_fail("Comb what? your hair?\n");
    
    if(!strlen(str))
       return 0;

    if (str == "hair" || str == "the hair")
    {
        write("You comb your hair, forming a mohawk-style.\n");
        say(QCTNAME(this_player()) + " combs "+HIS(TP)+ 
         " hair, forming a mohawk-style.\n");	  
	return 1;
    }
    return 0;
}

void
init()
{
   ::init();
   add_action(comb, "comb");
}
