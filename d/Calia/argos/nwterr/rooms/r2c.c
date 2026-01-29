/* Argos Road
** History
** Date        Coder         Action
** -------- ---------------  ------------------------------------------
** 10/1/96  Zima             Argos road extened
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include KR_HERBSEARCH

void
reset_herb_room()
{
    set_searched(0);
}

void
reset_room()
{
    reset_herb_room();
}

 
void create_room() {
   set_short("A path through the forest");
   set_long(
       "You are making your way through a thick forest of various " +
       "types of trees, along a path which winds its way through " +
       "the tranquil woods. The forest creatures seem a little " +
       "quiet along this stretch, even the wind is strangely calm. "+
       "The path winds to the west and northeast.\n");
 
    add_item("path",
        "A narrow dirt path winding through the woods, it winds "  +
        "towards the west and northeast.\n");
#include "r2.h"
    /* exits */
    add_exit(ROOM_DIR+"r2b","west",0);
    add_exit(ROOM_DIR+"r2d","northeast",0);

    reset_room();

    seteuid(getuid(this_object()));
    set_search_places(({"forest"}));
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(KRHERBS+"nightshade");
    add_herb_file(KRHERBS+"kuko");
    add_herb_file(KRHERBS+"drudgeworth");
    add_herb_file(KRHERBS+"lore");
    add_herb_file(KRHERBS+"blade");
    add_herb_file(KRHERBS+"bloodweed");
    add_herb_file(KHERBS+"fdlhead");
    add_herb_file(KHERBS+"chantrelle");
    add_herb_file(KHERBS+"poison_ivy");
    add_herb_file(KHERBS+"onoclea");
    add_herb_file(KHERBS+"dandelion");
}
