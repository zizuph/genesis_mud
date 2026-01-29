/* Dry Leaf, by Teth, April 9, 1996 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"

create_object()
{
    set_name("leaf");
    set_short("dried leaf");
    set_pshort("dried leaves");
    set_adj("dried");
    set_long("This is a dried leaf, but from which plant it is impossible "+
             "to tell. It is merely a ghost of its former self, only showing "+
             "the venation of its previous green structure.\n");

   add_prop(OBJ_I_VOLUME, 1);
   add_prop(OBJ_I_WEIGHT, 1);

}



