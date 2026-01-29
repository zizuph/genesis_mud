inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

void    reset_room();

object  guard;

void
create_room()
{
    set_short("In a private garden in Wainwrights' Street in Minas Tirith");
    set_long(BSN("This is a private garden in Wainwrights' Street in "
      + "Fourth Circle of Minas Tirith. Lovely white and yellow flowers grow "
      + "in flowerbeds along the walls. The garden itself is not large, but "
      + "it is well tended. An open gate leads south into the street and a "
      + "door into the house to the north."));

    add_item(({"flowers", "white flowers", "yellow flowers", }), BSN(
        "The white and yellow flowers make the garden smell pleasant. They are "
      + "placed in well tended flowerbeds on each side of the garden."));
    add_item("garden", BSN("The garden is not big, being only about twenty "
      + "times twenty five feet. It looks nice though, with well tended "
      + "flowerbeds on each side. A tiled path leads up to the front door "
      + "from the open gate."));
    add_item(({"path","tiles", "tiled path", }),BSN(
        "The tiles of the path are in good repair. The path is leading from "
      + "the front door of the house to the open gate."));
    add_item(({"flower-beds","flowerbeds"}), BSN(
        "The flowerbeds are well-tended, and white and yellow flowers "
      + "fill the garden with a pleasant smell. In a second row of beds, "
      + "further away from the tiled path, some herbs have been planted."));
    add_item("gate",BSN(
        "The gate is just a simple wooden board swinging in iron hinges. "
      + "The owner of the house obviously has no trouble with trespassers "
      + "since he does not feel the need for a gate that can be locked."));

    add_exit(MINAS_DIR+"n2crc4","south",0,1);

    clone_object(MINAS_DIR+"doors/h1_ncrc4_out")->move(TO);

    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(OBJ_I_SEARCH_TIME,3);
    set_search_places(({"flowers","flower-beds","flowerbeds","garden"}));

    add_herb_file(ONE_OF_LIST(HERBS));
    add_herb_file(ONE_OF_LIST(HERBS));
    add_herb_file(ONE_OF_LIST(HERBS));

    reset_room();
}

void
start_investigation()
{
    if (!objectp(guard))
    {
        guard = clone_object(MINAS_DIR + "npc/quest/out_guard");
        guard->arm_me();
        guard->move_living("south",TO);
        guard->start_investigation();
    }
}

void
reset_room()
{
    set_searched(0);

    FIX_EUID

    MT_PW5_MASTER->load_me();
    if (MT_PW5_MASTER->query_pw5_status())
        start_investigation();
}

