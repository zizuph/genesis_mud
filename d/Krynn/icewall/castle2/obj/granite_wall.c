#pragma strict_types
inherit "/std/object";
#include "/d/Krynn/common/defs.h"
#include <macros.h>


void
create_object()
{
    set_name("wall");
    set_short("thick granite wall");
    set_long("A solid, dark, granite wall stands right across " +
      "the corridor. You can see no cement, but the wall is fit " +
      "exactly to the floor, walls, and ceiling. Whats more, it " +
      "appears to have been brought here in one piece. Though " +
      "the purpose of it is quite obvious - to keep the Thanoi out " +
      "of the main building, where draconians reside, the means " +
      "of putting it up here remain quite a mystery. There are " +
      "some scratch marks on the wall and on the floor in front " +
      "it.\n");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 1000000);
    add_prop(OBJ_I_VOLUME, 300000);
    add_prop(OBJ_M_NO_GET, "How on Krynn would you do that?!\n");
    add_prop(OBJ_M_NO_STEAL, "Not even a kender can attempt that...\n");
    add_prop(MAGIC_AM_MAGIC, ({5, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This wall is not really " +
      "magical.\n", 1, "The granite wall is simply the result " +
      "of a 'wall of stone' spell cast on the corridor.\n", 20}));
    add_prop(OBJ_S_WIZINFO, "Draconians despise the primitive Thanoi. " +
      "Thanoi are a very aggressive race. Separating their quarters " +
      "was the only logical choice for Fael-theas, the White Dragon" +
      "army Highlord. 'Nuff said.\n");
}
      