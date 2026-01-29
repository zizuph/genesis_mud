/*
 * Queen's audience chamber
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
 
 
void reset_room();
void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    set_short("Queen's audience chamber");
    set_long("   This audience chamber is where the Queen's " +
        "guests come to seek a meeting with her. Most of the " +
        "time, it is used as a waiting room for those who are " +
        "seeing the Queen. Like the rest of the castle, mother " +
        "if pearl covers the walls. Floral designs decorate " +
        "the walls and are inlaid with numerous jewels. The " +
        "ceiling has a large fresco on it. Some chairs, and " +
        "a large table dominate the room. A deep luxurious " +
        "carpet, bearing the royal insignia of the Queen, " +
        "fills the room. A chandelier hangs from the ceiling, " +
        "illuminating the room. A servant waits here, making " +
        "appointments for the Queen.\n\n");
        
    add_item(({"wall", "walls"}),
        "The walls polished to a dazzling whiteness. The light " +
        "from the chandelier causes the jewels to sparkle. " +
        "Flowing arabesques are carved into the panels. " +
        "Arranged around the walls are flower arrangements.n");
    add_item(({"floor", "ground", "down", "rug", "carpet"}),
        "The carpet is a rich deep blue. The Queen's ensignia " +
        "has been woven into the carpet. It is of a lioness " +
        "bearing a red rose.\n");
    add_item(({"design", "designs", "floral designs"}),
        "The designs are of large flowers twining across the " +
        "wall.\n");
    add_item(({"arabesque", "arabesques"}),
        "They are ornamental designs of intertwining flowers, " +
        "leaves, and geometric shapes.\n");
    add_item("furniture",
        "You see a desk and some chairs in the room.\n");
    add_item("desk",
        "The desk is large and imposing. A servant for the Queen " +
        "sits behind it, checking appointments for the queen.\n");
    add_item("chairs",
        "There are some tall backed chairs. They are expertly " +
        "carved and comfortable looking. They line the walls " +
        "and are filled with eager elves waiting to meet with " +
        "the Queen.\n");
    add_item("fresco",
        "The painting depicts the justice of the Queen.\n");
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
 
    add_exit( TCASTLE_DIR + "q_dr",  "west");
    add_exit( TCASTLE_DIR + "cor20", "southeast");
}
 
 
void
reset_room()
{
}
