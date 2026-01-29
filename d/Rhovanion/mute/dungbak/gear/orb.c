inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object()
{
   set_name("orb");
   set_adj("glowing");
   set_long("This orb is large enough to occupy your entire hand and is covered with hundreds and hundreds of perfectly cut identical facets.  The orb itself is colorless and clear yet seems to emit an intense, very bright white light filling the room with its cold beams.\n" +
      "Close inspection reveals a tiny rune on every facet.  This item must be worth a tidy sum you figure.\n");
   add_prop(OBJ_I_VALUE, 100000);
   add_prop(OBJ_I_LIGHT, 1);
}
