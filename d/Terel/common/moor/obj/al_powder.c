// This is one of the powders found in the toolshed.
// It is a component needed for making thermite for
// the cottage  chest quest.

inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

void
create_object()
{
     set_name("powder");
     add_name(({"alum", "aluminum", "pile", "is_aluminum"}));
     set_short("pile of reddish-gray powder");
	 set_pshort("piles of reddish-gray powder");
     set_long("A reddish powder made of ground-up bauxite mineral. The alum "+
     "in this powder is useful for increasing acidity in soil, tanning hides, "+
	 "baking, and preserving foods. If handled improperly it can burn your "+
	 "skin and other things.\n");
     add_adj(({"grey", "gray", "reddish", "reddish-gray"}));

     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);

}
     
