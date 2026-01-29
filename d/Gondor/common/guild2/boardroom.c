/*
 * The boardroom of the Society of Morgul Mages
 *
 * Created: Olorin, 10-jan-1994
 *          using older code by Soermo and Randor
 *
 * Modification log:
 */
#pragma save_binary

inherit "/d/Gondor/morgul/tower/tower";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/tower/tower_defs.h"

object  board;

void create_morgul_tower_room()
{
    set_level(3);
    set_room_type("dark, gloomy room");
    set_extra_long("In this place, the members of the Society of Morgul"
      + " will often gather to discuss the wishes of the Nine. A"
      + " sheet of dull black metal serves as a bulletin board, and has"
      + " been firmly bolted to the stone wall at the back of this"
      + " chamber. Through a doorway to the north, the winding staircase"
      + " which runs the length of the tower is dimly visible.");

    add_item(({"stairs","staircase","winding staircase",
               "winding stairs"}),
        BSN("The stairway to the north offers access from both above"
      + " and below to those who are worthy to ascend it. Shadows"
      + " fall as long black tiles upon the many steps."));
    add_item(({"shadow","shadows"}),
        BSN("Shadows are strewn about this place as cobwebs in a"
      + " forgotten crypt. They offer comfort against the unsure light"
      + " of the outside world."));
    add_item(({"door","doorway"}),
        BSN("The doorway to the north has been perfectly shaped by"
      + " the careful masonry of ancient stoneworkers. It opens onto the stairway"
      + " which runs the length of the tower."));
    add_item(({"sheet","metal","dull metal","black metal",
               "dull black metal","sheet of dull black metal"}),
        BSN("The sheet of metal is very thick, and has been firmly"
      + " bolted to the wall with huge metal clasps. An unadorned"
      + " bulletin board adheres to its surface by means of some dark"
      + " power."));
    add_item(({"clasp","clasps","huge clasps","huge metal clasps"}),
        BSN("These claps have been cunningly formed from a dark metal"
      + " of great strength and weight. They secure the metal sheet"
      + " firmly to the wall."));
    add_item(({"steps","step"}),
        BSN("There are countless steps on the stairway to the north,"
      + " all of them shrouded in gloom."));

    add_prop(ROOM_I_LIGHT, 1);

    WALLS
    FLOOR
    ROOF

    add_exit(MAGES_DIR + "tower/tower_3c", "north",  0);

    if (!present("board",TO))
    {
        board = clone_object(MAGES_DIR + "obj/mage_board");
        board->move(TO);
    }
}
