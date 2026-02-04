inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>


#define TP this_player()
#define TO this_object()
#define ENV environment

#define PATH "/d/Terel/mecien/valley/guild/"
create_room(){

set_short("Sky Point");
set_long(
"This small circular chamber rests at the top of the ancient shrine, small" +
" panes of sparkling crystal glass encasing it, forming a small observation " +
"point to the stars. Symbols are engraved into the floor and the walls, just " +
"below the glass barrier. A circular staircase desends from here.\n");

add_item("staircase", "It descends to the main part of the shrine.\n");
add_item("floor", "It is covered with symbols.\n");
add_item("walls", "The rise only a few feet before turning into a glass dome.\n");
add_item("dome", "It is a crystal glass case that covers this chamber.\n");
add_item("symbols", "The are constellations and markings to help orient one " +
"to astronomical positions.\n");
add_item("glass", "It is a mysterious crystal glass.\n");

add_cmd_item("glass", "break", "It seems to be unbreakable.\n");

add_prop("_can_summon_the_stars", 1);

add_exit(PATH + "starchamber", "down", 0);


}


