inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herbsearch.h"

void
create_room()
{
    set_short("in a private garden in Belfalas Street in Minas Tirith");
    set_long(BSN("Lovely red flowers grow in flowerbeds along the walls of "
      + "this garden. The garden itself is not large, but nice enough. "
      + "An open gate leads north into Belfalas Street in the Fifth Circle."));
    add_item(({"flowers", "red flowers", }), BSN(
        "The red flowers makes the garden smell pleasant. They are placed in "
      + "well-tended flower-beds on each side of the garden."));
    add_item("garden", BSN(
        "The garden is not big, being only about twenty times thirty feet. It "
      + "looks nice though, with well-tended flower-beds on each side. Worn "
      + "out tiles lead up to the front door from the open gate."));
    add_item(({"path","tiles"}), BSN(
        "The tiles are old and worn, from being trodden on year "
      + "after year. They would be best replaced with new ones."));
    add_item(({"flower-beds","flowerbeds"}), BSN(
        "The flowerbeds are well-tended, and large red flowers stretch upwards "
      + "during daylight hours. In a second row of beds, further away from "
      + "the tiled path, herbs have been planted."));
    add_item("gate", BSN(
        "A simple iron gate without lock or bar. It is painted black. With a "
      + "small piece of wood it has been blocked so it cannot be closed. Through "
      + "the open gate you can enter Belfalas Street to the north."));

    clone_object(MINAS_DIR + "obj/bar_outdoor")->move(TO);
    add_exit(MINAS_DIR + "s3crc5", "north", 0, 1);

    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,3);
    set_search_places(({"flowers","flower-beds","flowerbeds","garden"}));
    add_herb_file(HERB_DIR + "curugwath");
    add_herb_file(HERB_DIR + "handasse");
    add_herb_file(HERB_DIR + "athelas");
    add_herb_file(HERB_DIR + "seregon");
    add_herb_file(HERB_DIR + "fennel");
    add_herb_file(HERB_DIR + "ginger");
    add_herb_file(HERB_DIR + "myrtle");
}

void
reset_room()
{
    set_searched(0);
}
