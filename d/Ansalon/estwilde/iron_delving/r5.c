#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit DWARF_OUT;

void
reset_dwarf_room()
{
    return;
}

create_dwarf_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"large valley","large hills","hills"}),
      "You stand in a large valley that is well sheltered " +
      "and protected by two steep hills.\n");
    add_item("grass",
      "The grass that grows here, while still somewhat brown, " +
      "is quite a lot lusher than that grass that grows out on " +
      "the plains of Estwilde.\n");

    add_item(({"opening","hill side"}),
      "To the northwest a small opening has been crafted " +
      "by skilled hands in the side of the hill. You could " +
      "probably enter it.\n");

    add_exit(IRON + "r4","southwest",0);
    add_exit(IRON + "r7","southeast",0);

    add_cmd_item("opening","enter","@@into_cave");

    reset_dwarf_room();
}

string
into_cave()
{
    write("You enter the opening...\n");
    TP->move_living("into the hill side",
      IRON + "cave",1,0);
    return "";
}

string
short_descr()
{
    return "A hill-enclosed valley";
}

string
cave_description()
{
    if(TP->query_skill(SS_AWARENESS) > 30)
    {
	return "To the northwest you notice a rather " +
	"craftily hidden opening in the hill side.";
    }
    else
	return "";
}

string
long_descr()
{
    return "You stand in a large valley between two large hills. " +
    "The ground here is covered with short browny-green grass, " +
    "and slopes down to the southeast. The sound of a bubbling " +
    "stream comes from the southeast. " +
    cave_description() +
    "\n";
}
