inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

create_room(){

set_short("Ice Stairs");
set_long(
"Incredible in its majesty, this set of stairs climbs upwards\n"
+"around the side of an icy mountain. The wind is strong and the\n"
+"clouds seem to wrap themselves about the side of the mountain.\n"
);

add_item(({"cloud", "clouds"}), "Like the heavens have descended they\n"
+ "cradle the mountain in their gentle splendour.\n");
add_item("stairs", "They are cut into the ice.\n");
add_item("mountain", "It is a tall icy mountain, obscured by clouds.\n");


add_exit("/d/Terel/mecien/mountains/mtop", "up", 0);
add_exit("/d/Terel/mecien/mountains/istairs1", "down", -10);

}

