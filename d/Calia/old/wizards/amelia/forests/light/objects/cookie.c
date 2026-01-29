/*
*  by Amelia for use in the Light Forest
*/

inherit "std/food";
#include "defs.h";
#include <macros.h>
#include <stdproperties.h>

void
create_food()
	{
		set_amount(300);
		set_name(({"cookie", "chocolate chip cookie"}));
		set_short("Granny's famous chocolate chip cookie");
set_pshort("Granny's famous chocolate chip cookies");
set_long("This is one of Granny's famous chocolate chip "+
		"cookies.  It is round and flat, and you can see that "+
		"it is chock full of chocolate chips.  It looks very "+
"delicious.\n");
		}
