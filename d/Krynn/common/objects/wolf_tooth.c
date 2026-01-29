/* Wolf Tooth, by Teth, April 9, 1996 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"

create_object()
{
    set_name("tooth");
    set_pname("teeth");
    set_short("canine tooth");
    set_pshort("canine teeth");
    set_adj("canine");
    add_adj("wolf");
    set_long("This tooth belongs to some canine animal, most likely a wolf. "+
      "Some have said that the teeth of such animals can give the "+
      "person the power of the animal itself if used in the right "+
      "manner. It is yellowing with age.\n");

    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VALUE, 75);
}



