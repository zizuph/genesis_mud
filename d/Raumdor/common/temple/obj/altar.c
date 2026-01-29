/* Sarr */
#include "defs.h"
inherit "/std/object";

void
create_object()
{
    set_name("altar");
    set_adj("stone");
    set_short("stone altar");
    set_long(
      "This is an altar made of black stone. It is decorated with many " +
      "strange runes. In the center front, there is a carving of a grim " +
      "looking skull. The top of it is covered in blood, both fresh and old " +
      "looking.\n");
    add_item(({"runes"}), "You don't know what they say.\n");
    add_item(({"skull"}), "Scary looking.\n");
    add_prop(OBJ_I_NO_GET, 1);
}
