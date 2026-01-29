inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
add_door()
{
    object  door;

    door = clone_object("/std/door");
    door->set_door_id("pel_mansion_1_door");
    door->set_other_room(PELAR_DIR + "homes/mangrhall");
    door->set_pass_command(({"n", "north", }));
    door->set_door_desc(BSN(
        "The door leading into the mansion has two wooden wings, "
      + "both carefully joined and painted. There is no inscription "
      + "on the door to reveal the name of the family living here, "
      + "but the emblem of Pelargir has been carved into it."));
    door->set_door_name(({"large door", "door", }));
    door->set_name(({"door", "pel_mansion_1_door", }));
    door->set_adj(({"large", "two-winged",}));
    door->add_item(({"emblem", "coat", "coat of arms", }), BSN(
        "The emblem of Pelargir has been carved onto the door: "
      + "Three golden ships surmounted by a crown."));
    door->set_open(0);
    door->set_locked(0);
    door->move(TO);

//  add_exit(PELAR_DIR + "homes/mangrhall","in",0);
}

void
create_room()
{
    set_short("in the garden district of Pelargir");

    set_long(BSN("You stand outside one of the largest mansions of "
      + "Pelargir. The mansion's lavish columns and garden give credit "
      + "to the generations of family it has passed through. To the "
      + "south the street heads back among the other houses of the "
      + "garden district."));
    add_item("mansion", BSN("This large mansion is nearly as beautiful "
      + "as it is old. The columns in front give it an air of majesty, "
      + "and the garden adds both beauty and a feeling of security."));
    add_item(({"column","columns"}), BSN("These columns have born "
      + "their age well. Though they are a bit chipped in places, the "
      + "polish that time has given them bestow them with a distinct "
      + "majestic feeling."));
    add_item(({"garden","gardens"}), BSN("These gardens are one of the "
      + "few assurances left in Gondor that beauty may survive the "
      + "coming storm."));

    add_cobble();
    add_admiral();

    add_exit(PELAR_DIR + "street/xroad2","south",0);

    add_door();
}

