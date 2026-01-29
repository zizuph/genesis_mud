/* Forest coded by Lord Rastlin */
/* modified by Teth, Feb.13,96 */
#include "/d/Krynn/common/defs.h"
#include "local.h"

inherit FOROUTROOM;

inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mixedforest",}));

void
reset_solace_room()
{
    set_searched(random(2));
}

void
create_solace_room()
{
    set_place(FOREST);
    set_long_desc("The forest around you consists of Crystalmir pine and " +
             "deciduous trees. It continues both to the north and the " +
             "northeast. To the south, the forest changes. Huge trees " +
             "take over, and the forest opens into what appears " +
             "to be a peaceful village. Sounds of playing children drift " +
             "from the village, as does the smell of homecooked food. There " +
             "must be an inn nearby!");
    add_item("forest", "The forest is a mixture of Crystalmir pine and " +
             "deciduous trees.\n");
    add_item("trees", "They provide a pleasant scenery. Surely the citizens " +
             "of the nearby town take some pride in them.\n");
    add_item("deciduous trees", "These are mainly birch and aspen.\n");
    add_item(({"Crystalmir pine", "pine"}), "Stately and unmoving, these " +
             "magnificent trees stand guard over this forest.\n");
    add_item("huge trees",
	     "You are able to identify them as Vallenwood trees. Squinting " +
             "your eyes, you can make out buildings in the trees, as well " +
	     "as walkways connecting them.\n");
    add_item(({"buildings","walkways"}),
	     "You can't see much from here. Perhaps you should leave " +
             "south to take a closer look.\n");

    add_exit(TDIR + "nforest2", "northeast");
    add_exit(TDIR + "nforest1", "north");
    add_exit(C_SOLACE, "south");
 
    reset_room();
    seteuid(getuid(TO));
    set_up_herbs(({ONE_OF(herbs),ONE_OF(herbs),ONE_OF(herbs),
        ONE_OF(herbs)}), ({"forest",}), 4);

}

int
block()
{
    write("The tree village Solace is under attack by dragons and " +
	  "draconians. The wizards of Krynn, has yet again, gone into " +
	  "battle to defend their creation. The battle will go on for " +
	  "several hours, since the wizards are few and the dragons are " +
	  "many. The only thing you can do is to pray to the gods and " +
	  "give them all the support you can.\n");
    return 1;
}
