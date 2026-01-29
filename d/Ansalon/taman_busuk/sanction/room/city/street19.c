#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("On a street passing close by a river of lava");
    set_extra_long("Here you stand in the southern parts " +
      "of Sanction, to the southeast of houses that once " +
      "were owned by the nobles and rich merchants before " +
      "the dragonarmy occupation of this city, and to the " +
      "west of a river of lava that flows from " +
      "the south to the north. To your southwest you " +
      "see what looks like a marshalling yard.");

    add_item(({"yard","marshalling yard"}),
      "To your southwest is what looks like " +
      "a marshalling yard where soldiers for the various " +
      "dragonarmies are gathered for deployment.\n");

    add_item("houses",
      "To your northwest rise houses and similar structures " +
      "that were probably owned by the rich and " +
      "influential before the occupation of the city. " +
      "Now they simply stand out as being less rundown " +
      "than those buildings that stand in the expansive " +
      "slums of this city.\n");

    add_item(({"river of lava","lava","river"}),
      "To your east a river of lava flows past you " +
      "from one of the Lords of Doom to your south. " +
      "Even from this distance the heat is almost unbareable.\n");

    add_exit(SCITY + "street18","north",0);
    add_exit(SCITY + "street20","west",0);
    add_exit(SCITY + "yard","southwest",0);

}

int
no_go()
{
    write("The marshalling yard is off limits " +
      "for the time being. Wannabe soldiers should come " +
      "back when the officers are recruiting.\n");
    return 1;
}
