#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define H1 "/d/Gondor/common/herbs/mint"
#define H2 "/d/Gondor/common/herbs/oregano"

void
reset_flotsam_room()
{
    set_searched(random(4));
}

create_flotsam_room()
{
    set_short("At the end of the trail");
    set_long("@@long_descr");

    add_item(({"wagon trail","trail"}),"You stand at the end of the " +
      "wagon trail that links up the farmhouses to the road " +
      "that leads to Flotsam. The trail ends at a gate.\n");
    add_item(({"fields","fields of wheat","wheat"}),
      "On either side of the trail grows a hardy variety of " +
      "wheat, used to feed the surrounding population of Flotsam.\n");
    add_item(({"fenced off area","area","small fenced off area",
	"paddock"}),"A fence blocks your way to the east into " +
      "what looks like a small paddock. A gate starts where the trail ends, and a haystack " +
      "can be seen at the far end of the paddock.\n");
    add_item("haystack","Over the fence at the far side of the " +
      "field is a haystack.\n");
    add_item("fence","A low wooden fence with a gate that looks " +
      "like it has been nailed shut. You reckon it would be pretty " +
      "easy to jump over though.\n");
    add_item("gate","A closed gate. It has been nailed shut.\n");
    add_item(({"grazing cattle","cattle"}),"The paddock to your east " +
      "is used for grazing cattle you think.\n");

    add_exit(FROOM + "pathb","west",0);

    add_cmd_item(({"over fence","fence","gate","over gate"}),
      ({"climb","jump"}),
      "@@jump_fence");
    add_cmd_item("gate","open","@@open_gate");

    seteuid(getuid(TO));
    set_search_places(({"herbs","field"}));
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");
    add_herb_file(H1);
    add_herb_file(H2);

    reset_flotsam_room();
}

string
long_descr()
{
    return tod_descr1() + "You stand at the end of the wagon trail. " +
    "To the north and south the cultivated fields of wheat surround " +
    "you, while to your east you notice there is a small fenced off " +
    "area, for what looks like grazing cattle.\n";
}

string
jump_fence()
{
    if (TP->query_prop(LIVE_O_STEED))
    return "Fence is too high for you to jump over it while mounted.\n";

    write("You jump over the fence and into the paddock.\n");
    TP->move_living("over the fence",FROOM + "pathe",1,0);
    return "";
}

string
open_gate()
{
    write("You try and open the gate but it is nailed shut.\n");
    return "";
}
