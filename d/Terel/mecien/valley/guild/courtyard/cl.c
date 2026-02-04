/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
inherit "/d/Gondor/common/lib/herbsearch.c";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define PATH "/d/Terel/mecien/valley/guild/courtyard/"
#define TP this_player()


int num;


create_room(){

set_short("Inner Forest");
set_long(
"Here in the midst of the grand and towering redwoods and cedars,\n"
+"a small pond forms. It is a clear and beautiful pond that seems\n"
+"to be the product of an old stone fountain. A layer of moss grows\n"
+"about the edges of the pond, as do small shrubs and evergreens.\n"
);

num = 2;

add_prop(OBJ_I_SEARCH_TIME, 2);
add_prop(OBJ_S_SEARCH_FUN, "herb_search");
add_item("shrubs", "They grow about the edges of the pond. They are\n"
+"small and colourful and add to the tranquil beauty of this place.\n");
add_item("pond", "It is a simple clear pond, it looks like the result\n"
+"of a natural spring that was capped by a stone fountain.\n");
add_item("water", "It is clear and pure.\n");
add_item("moss", "It is plush, like a carpet that circles the pond.\n");
add_cmd_item("water", "drink", "It is refreshing.\n");
add_item("trees", "They are tall cedars and redwoods, they reach high into the sky and\n"
  + "they keep out most light.\n");
add_item("cedars", "An aromatic coniferous tree, its bark reddish.\n");
add_item("redwoods", "Beautiful noble trees, huge and ancient. They are coniferous.\n");

add_search_places(({"pond", "shrubs"}));
add_herb_file("/d/Terel/mecien/valley/guild/obj/herb1");
add_item("fountain", "It is an old stone fountain, it rests in the midst\n"
+"of a small pond. It is a simple shape of rough stone, water pours out\n"
+"from the top and descends into the pool. Some ancient runes are\n"
+"carved upon it.\n"
);
add_cmd_item(({"fountain", "runes"}), "read",
"To the world of knowing and seeing, sing to the glory of the Ancients\n");

  add_exit(PATH + "rf2", "south", 0);
}




