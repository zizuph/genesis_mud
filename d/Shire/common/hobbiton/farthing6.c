inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/d/Shire/open/herbsearch.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"


create_room()
{
    set_short("garden");
    set_long(break_string(
      "You are in the garden of a herbfarm. This particular slab "
    + "of land looks relatively untended, and is full of flowers of all kinds. "
    + "This field has nearly been reclaimed by nature.\n", 70));

    add_item("ground", break_string(
      "The ground seems to be void of useful greens, but perhaps "
    + "not everything has been harvested and taken away.\n", 70));
    
    add_item("field","The field is full of grass, and could be a void of useful "+
    		     "greens. It looks like it just have been harvested.\n");
    
    add_prop(ROOM_I_INSIDE,0);

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "herb_search");

    set_search_places(({"ground","field"}));
    add_herb_file(GONDOR_HERBS + "blueberry");

    add_exit(HOBBIT_DIR + "farthing4","north");
}

