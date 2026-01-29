/*   mocha.c
 *
 * A small bag of quality mocha
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
    set_name("mocha");
    set_adj("small");
    add_adj("bag");
    set_short("small bag of mocha"); 
    set_long("A small bag filled with lovely quality mocha. You can "+
      "probably 'smell' it.\n");      
      
    add_prop(OBJ_I_SHIPWRECK_EQUIPMENT, 1);	
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VALUE, 5);
    
}

int
smell_coffee(string str)
{
    notify_fail("Smell what? the mocha?\n");
    
    if(!strlen(str))
       return 0;

    if (str == "mocha" || str == "the mocha")
    {
        write("You smell the mocha in a subtle manner. This sure is "+
          "quality mocha!\n");
        say(QCTNAME(this_player()) + " smells "+ HIS(TP)+ 
         " mocha. "+capitalize(HE(TP))+" suddenly look very relaxed.\n");	  
	return 1;
    }
    return 0;
}

void
init()
{
   ::init();
   add_action(smell_coffee, "smell");
}
