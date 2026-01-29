#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KEN_OUT;

void
reset_kendermore_room()
{
    return;
}

create_kendermore_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"oak tree","giant oak tree","tree"}),
      "You stand high up on the edge of a branch in a giant " +
      "oak tree.\n");

    add_exit(KROOM + "r4","southeast",0);
    clone_object(KEN_OBJ + "kender_board")->move(TO);

    reset_kendermore_room();
}

string
short_descr()
{
    return "On the end of a branch of a giant oak tree";
}

string
long_descr()
{
    return "You are standing on the end of a large " +
    "branch high up in a giant oak tree. Here, notes " +
    "have been pinned up to a nearby limb, allowing " +
    "other kender to read them.\n";
}
