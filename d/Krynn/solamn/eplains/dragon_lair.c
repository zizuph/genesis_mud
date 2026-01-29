#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

#include <money.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit FOREST_IN; 
inherit "/lib/unique";

object dragon, corpse, knight;

void
reset_flotsam_room()
{
    if(!objectp(dragon))
    {
      dragon = clone_object("/d/Krynn/solamn/eplains/living/b_dragon");
      dragon->move(TO);
    }

    if(!objectp(corpse))
    {
      corpse = clone_object("/d/Krynn/solamn/eplains/obj/horse_remains");
      corpse->move(TO);
    }

    if(!objectp(knight))
    {
      knight = clone_object("/d/Krynn/solamn/eplains/obj/knight_corpse");
      knight->move(TO);
    }

}

create_flotsam_room()
{
    set_short("a stark cave in the Dargaard Mountains");
    set_long("@@long_descr");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_item(({"stark cave","cave"}),
       "With the steam filling much of the cave, you cannot make out many details... " +
       "although you can assume that it was created through seismic activity!\n");
    add_item(({"steam","hissing steam"}),
       "Steam snakes from great cracks in the floor of the cave, filling the room and " +
       "making it very warm in here.\n");
    add_item(({"bones","large bones","small bones","great bones"}),
       "Looking at the bones on the floor of the cave you can make out various creatures, " +
       "in particular those that are human or bovine. A bleached skull stares up at you, " +
       "and its gaze seems to follow you as you move around the room...\n");
    add_item(({"bleached skull","skull"}),
       "Its a skull. Of something dead. What did you expect? It to wink at you?\n");

    add_exit("/d/Krynn/solamn/eplains/rooms/eplain-22-10-L","out","@@out");

    reset_flotsam_room();

}

string
long_descr()
{
    return "You stand in a stark cave in the Dargaard Mountain Ranges. Steam hisses " +
       "from wide cracks in the floor, limiting your visibility and making the cave " +
       "unbearably hot. Bones of various creatures both great and small litter the " +
       "floor, making you wonder if this cave is dangerous to inhabitance, or the " +
       "inhabitant of this cave is dangerous to those who stumble in here?\n";
}

int
out()
{
    write("You pass through the steam out the cave entrance...\n");
    return 0;
}

