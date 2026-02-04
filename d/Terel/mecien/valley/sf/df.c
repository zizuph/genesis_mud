inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/sf/"

create_room(){

set_short("Dead Forest");
set_long(
"The forest here is dead and lifeless, as if some strange disease\n"
+ "cast itself down here or the very power of spring washalted. The buds\n"
+"of spring are shrivelled and dried to the branches.\n"
);

add_item("trees", "They are mostly dead, some still have a bit of life though.\n");
add_item("buds", "The spring buds have died too.\n");

  add_exit(PATH + "sf3", "west", 0);
   add_exit(PATH + "df1", "east", 0);
}

