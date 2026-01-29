#include "defs.h";
inherit "/std/door";

void
create_door()
{
    ::create_door();
    set_door_desc(
      "This is a gate made of steel. The bars look strong. Looking through " +
      "them, you see only darkness.\n");
    set_open(0);
}
