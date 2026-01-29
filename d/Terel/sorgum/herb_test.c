inherit "/std/room";

#include <stdproperties.h>
#include "/d/Terel/common/herbsearch.h"

#define HERB_DIR "/d/Gondor/common/herbs/"

reset_room()
{
    set_searched(0);
}

void
create_room()
{
    set_short("In forest");
    set_long("You are in the forest.  There are herbs here.\n");
    add_prop(ROOM_I_INSIDE, 0);

    add_item("forest", "The green forests might very well " +
	     "resemble paradise - fresh flowers and fragrant herbs, " +
	     "green trees and a number of grassing game.\n");
    
    add_item("oaks", "The oak trees are old and magnificent of stature.\n");
    
    add_item("larches","The larch trees are tall and green, reaching even " +
	     "higher than the oaks.\n");
    
    add_item("bushes", "The broad-leaved bushes are the primary contents of " +
	     "the undergrowth here.\n");
    
    add_item("shrubberies", "The green shrubberies with small flowers " +
	     "grow amongst the broad-leaved bushes.\n");
    
    add_item("ground", "The ground is overgrown with flowers, herbs " +
	       "and bushes.\n");
    
    add_item(({"flowers","herbs"}),
	     "The flowers and herbs growing here give the air a sweet " +
	     "fresh fragrance.\n");

    set_search_places(({"bushes","shrubberies","forest","flowers"}));
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(HERB_DIR+"attanar");
    add_herb_file(HERB_DIR+"fennel");
    add_herb_file(HERB_DIR+"sage");
    add_herb_file(HERB_DIR+"clove");
    add_herb_file(HERB_DIR+"seregon");    
}
