#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;

object trainer;

void
reset_sanction_room() {
    if (!trainer) {
    trainer = clone_object("/d/Ansalon/taman_busuk/sanction/npc/wyvern_seller");
        trainer->move(TO);
    }
}
void
create_sanction_room()
{
    set_short("On a tower landing in the city of Sanction");
    set_long("@@long_descr");

    add_item(({"wide wooden platform","wooden platform","platform","roof"}),
      "A wide wooden platform, banded in iron. In some places " +
      "it is deeply gouged, probably by dragon's claws as " +
      "they land here.\n");
    add_item(({"tower","tall stone tower","stone tower"}),
      "You stand on the roof of a tall stone tower in the " +
      "city of Sanction.\n");
    add_item(({"lava","lava stream","stream"}),
      "While dangerously close, you are sure dragons landing " +
      "and taking off from here take full advantage of the " +
      "rising superheated air, allowing them to glide and " +
      "take off with ease.\n");
    add_item(({"city","sanction"}),
      "The city of Sanction has often been referred to as " +
      "the city that most closely resembles the Abyss. " +
      "With the volcanoes and lava streams flowing through the city, " +
      "it takes little imagination to see why this is " +
      "the case.\n");
    add_item("hatch","A hatch leads down into the tower.\n");
    add_item(({"wyvern","wyverns"}),
        "Wyverns circle the tower, keeping an eye on the "+
        "surrounding area.\n");

    add_exit(SCITY + "tower_base","down",0);

    reset_sanction_room();
}


string
long_descr()
{
    return "You stand on a wide wooden platform on the roof " +
    "of a tall stone tower. Beneath you to your north flows " +
    "a lava stream perilously close to the " +
    "tower base, while to your south sprawls the city " +
    "of Sanction.  "+
    "Wyverns circle the area, shrieking in flight.  "+
    "A hatch leads down into the tower from here.\n";
}
