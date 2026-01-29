inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"


void
create_object()
{
    set_name("note");
    add_adj("sealed");
    set_short("sealed note");
    set_long("This note is sealed with a piece of red wax "+
      "stamped with the letter F.\n");
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_SELL, "You don't want to sell this note!\n");
    add_cmd_item((({"seal", "note", "wax"})), "break", "You don't "+
      "want to break the seal!\n");
    add_cmd_item((({"note", "sealed note"})), "read",
      "You cannot read the "+
      "note since it is sealed for privacy.\n");


}

int
query_focsles_note()
{
    return 1;
}

