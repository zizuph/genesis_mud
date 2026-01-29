/*
 * The audience chamber before the throne room 
 * in the castle in Telseron
 * By Finwe, November 1996
 */

inherit "/std/room";

#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"

void reset_room();

void create_room()
{   
    reset_room();
    add_prop(ROOM_I_INSIDE,1);
    set_short("An audience chamber");
    set_long("   You stand in the audience chamber, located " +
      "south of the throne room. An elf sits here, answering " +
      "questions, making appointments, and letting in elves to " +
      "meet with the King. This is a very busy room as all " +
      "appointments and petitions must be received here before " +
      "being going before the king. Various tired elves await " +
      "their turn while sitting down. Some mill around while " +
      "other come and go from the throne room. Occasionally, an " +
      "elf tries to make a break in to meet with the King, but are " +
      "denied entrance by two large guards.\n\n");

    add_item(({"wall", "walls"}),
      "The walls polished to a dazzling whiteness. The light " +
      "from the chandelier causes the jewels to sparkle. " +
      "Flowing arabesques are carved into the panels. " +
      "Arranged around the walls are flower arrangements.n");
    add_item(({"floor", "ground", "down", "rug", "carpet"}),
      "The carpet is a rich deep blue. The royal insignia, a " +
      "lion draped in a cape of roses, is richly woven into " +
      "the carpet.\n");
    add_item(({"design", "designs", "floral designs"}),
      "The designs are of large flowers twining across the " +
      "wall.\n");
    add_item(({"arabesque", "arabesques"}),
      "They are ornamental designs of intertwining flowers, " +
      "leaves, and geometric shapes.\n");
    add_item("furniture",
      "You see a desk and some chairs in the room.\n");
    add_item("desk",
      "The desk is large and imposing. A servant of the King " +
      "sits behind it, checking appointments.\n");
    add_item("chairs",
      "There are some tall backed chairs. They are expertly " +
      "carved and comfortable looking. They line the walls " +
      "and are filled with eager elves waiting to meet with " +
      "the King.\n");
    add_item("chandelier",
      "The chandelier is enormous. It's multi-tiered and covered " +
      "with diamonds. Candles burn brightly, filling the " +
      "room with light. The diamonds move slightly, catching the " +
      "candlelight and throwing it onto the walls in a " +
      "rainbow of patterns.\n");
    add_item("jewels",
      "You see emeralds, diamonds, rubies, sapphires, plus " +
      "many other gemstones set into the designs. The worth of " +
      "all the gemstones is staggering.\n");
    add_item("guards",
      "These are muscular elves who have devoted their lives to " +
      "protect the Royal Couple. They are menacing and look " +
      "dangerous as well as intimidating.\n");

    add_exit( TCASTLE_DIR + "throne_room",  "north");
    add_exit( TCASTLE_DIR + "cor10",        "east");
    add_exit( TCASTLE_DIR + "cor09",        "west");
}


void reset_room()
{
}
