#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>

inherit FOREST_OUT;
object guard;

void
reset_flotsam_room()
{
    if(!objectp(guard))
    {
	guard = clone_object(FNPC + "centaur_guard");
	guard->move(TO);
    }
}

create_flotsam_room()
{
    set_short("Before a tent in a serene glade in an " +
      "ancient forest");
    set_long("@@long_descr");

    add_item(({"serene glade","glade","natural clearing",
	"clearing"}),"@@long_descr");
    add_item(({"ancient forest","forest","trees","thicket",
	"oak trees","oaks",
	"thicket of trees","branches","shadows"}),"Surrounding " +
      "this serene glade is an ancient forest of oak trees. The " +
      "branches of the forest sway gently with the wind as if " +
      "beckoning you, and eerie sounds echo from its shadows.\n");
    add_item(({"lush green grass","green grass","lush grass",
	"grass"}),"Throughout the glade grows lush green grass. " +
      "In some areas it looks like it has been trampled.\n");
    add_item(({"tent","teepee-like tent"}),
      "A small teepee-like tent made of skins stands " +
      "to the east.\n");

    add_exit(FROOM + "g27","northwest",0);
    add_exit(FROOM + "g22","southwest",0);

    add_cmd_item("tent","enter","@@enter_tent");

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand within a serene glade in an ancient " +
    "forest. Lush grass grows all through this natural clearing, " +
    "ending at a thicket of trees that surround the glade. " +
    "A teepee-like tent stands to the east of the glade. " +
    tod_descr3() +
    "\n";
}
string
enter_tent()
{
    if(objectp(guard))
    {
	write("The burly dull centaur blocks your way into " +
	  "the tent.\n");
	say(QCTNAME(TP) + " is blocked from entering the tent " +
	  "by the burly dull centaur.\n");
	return "";
    }
    TP->move_living("into the tent",FROOM + "tent",0,0);
    return "";
}
