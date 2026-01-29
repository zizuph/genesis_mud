/* Thorbardin Cheese slices, for the Tower of Wayreth
 * -Kentari 12/6/96
 */

inherit "/std/food";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_food()
{
    set_name("cheese");
    add_name(({"slice","food"}));
    set_pname("cheeses");
    add_pname(({"slices","foods"}));
    set_adj("Thorbardin");
    set_short("Thorbardin cheese slice");
    set_pshort("Thorbardin cheese slices");
    set_long("A slice of sharp cheese from the Dwarven land of Thorbardin. " +
	"Made in the underground farms there, this cheese has a taste " +
	"totally unique, and it is quite good, though only a small " +
	"portion.\n");
    set_amount(35);
}
