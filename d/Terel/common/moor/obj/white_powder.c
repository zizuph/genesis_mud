// One of the powders found in the toolshed.
// It is a red-herring, and can foil attempts to
// make thermite for the cottage chest quest.

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_object()
{
     set_name("saltpeter");
     set_short("mound of white powder");
	 set_pshort("mounds of white powder");
     set_long("A white crystalline powder you think is the mineral "+
         "niter, also known as saltpeter. It is used as a fertilizer "+
		 "in the garden.\n");
     add_name(({"powder", "mound"}));
	 add_adj(({"white", "salt", "peter"}));
     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);

}
     
