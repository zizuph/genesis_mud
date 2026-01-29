inherit "/d/Gondor/common/room";
inherit "/d/Gondor/pelargir/city_items.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

string  exa_letters();

void
create_room()
{
    set_short("in the middle of the Pelargir Square");
    set_long(BSN("Before you stands a beautiful statue of a great lord "
     + "of the sea, and at his feet a fleet of ships is carved. "
     + "Here, in the middle of the square, the statue stands alone "
     + "and gives the people of Pelargir a feeling of majestic "
     + "independence. Besides the people who travel by it on their "
     + "daily chores and errands, some just come to stare and ponder. "
     + "Most of the traffic here comes from the Gates of Pelargir "
     + "to the north, and the Pelargir docks to the east. West of "
     + "the square is the city hall."));

    add_cobble();

    add_item(({"statue","lord", "lord of the sea",}), BSN(
        "The statue is carved from finest marble, rising high into "
      + "the sky on its mighty pedestal of black granite. Hewn into "
      + "the granite are letters of an inscription which at one "
      + "time were inlaid with gold, but little remains of it now."));

    add_item(({"letters", "inscription", "pedestal",}), exa_letters());
    add_cmd_item(({"letters", "inscription", "pedestal",}),
        "read", exa_letters());

    add_item(({"fleet", "ships", }), BSN("At the feet of the Lord "
      + "depicted by the statue a fleet of ships was carved from "
      + "the marble. It shows the ship of the fleet which Hyarmendacil "
      + "led towards Harad to conquer it."));
    add_item("gates", BSN("The gates leading to the road to the Harlond "
      + "and to Minas Tirith are to the north, past the bridge. The "
      + "gates leading to the road to Linhir are to the south."));
    add_item("docks", "They are to the east, towards the Anduin.\n");
    add_item(({"river", "anduin", "river anduin", }), BSN(
        "You cannot see the river from here, but it must be to the east."));

    add_item(({"hall", "city hall", }), BSN(
        "The city hall is a large stone building. In the city hall the "
      + "citizen of Pelargir assemble for festivities or when they are "
      + "summoned by the authorities. The city hall also contains the "
      + "offices of the City Council and the Lord Councillor."));

    add_exit(PELAR_DIR + "street/groad",  "north",0);
    add_exit(PELAR_DIR + "street/sroad3", "east",0);
    add_exit(PELAR_DIR + "street/sroad4", "south",0);
    add_exit(PELAR_DIR + "misc/cityhall", "west",0);
}

string
exa_letters()
{
    return ("The inscription reads:\n\n"
      + "\t    Ciryaher son of Ciryandil, Hyarmendacil\n\n"
      + "\t    Fifteenth King of Gondor TA 1015 - 1149\n"
      + "\tVictorious in Battle in Endor and on the Belegaer\n"
      + "\t               Conqueror of Harad\n\n"
      + "\t   Lord of Harad, Lord of Umbar, Lord of Rhun,\n"
      + "\tLord of Rhovanion, Lord over Greenwood the Great.\n\n"
      + "\t       Erected in memory of his father by\n"
      + "\t      Atanatar Alcarin son of Hyarmendacil\n"
      + "\t        in the tenth year of his reign.\n\n");
}

