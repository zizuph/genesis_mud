/*
 * The Queen's bedroom in the castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
 
 
void reset_room();
void
create_room()
{
    reset_room();
    set_short("The Queen's bedroom");
    set_long("   This is the bedroom of the Queen. It is large, " +
        "spacious, and elegantly furnished. A large bed dominates " +
        "the room. Unlike the rest of the castle, the walls are " +
        "beautifully covered in rich cherry paneling. Flowing " +
        "arabesques are carved into the walls. Light fills the " +
        "room through a large skylight. Various furniture is spread " +
        "throughout the room. A deep luxurious carpet is laid out " +
        "across the floor.\n\n");
 
    add_item(({"up", "ceiling"}),
        "The ceiling is painted a light blue, resembling the sky. " +
        "A large skylight dominates the ceiling, letting in sunlight. " +
        "is opened. A gentle perfumed breeze from the garden blows " +
        "in.\n");
    add_item(({"wall", "walls"}),
        "The walls covered with cherry wood panels. The wood is " +
        "polished tp a deep rich red. Flowing arabesques are " +
        "carved into the panels.\n");
    add_item(({"floor", "ground", "down", "rug", "rugs", 
               "carpet", "carpets"}),
        "The carpetis a rich deep blue. Floral designs have " +
        "been intricately woven into it.\n");
    add_item(({"design", "designs", "floral designs"}),
        "The designs are of large flowers twining across the " +
        "wall.\n");
    add_item(({"arabesque", "arabesques"}),
        "They are ornamental designs of intertwining flowers, " +
        "leaves, and geometric shapes.\n");
    add_item("bed",
        "It dominates the room. The bed has four posters with an " +
        "elegant cover. The cover is made of fine silk and twinkles " +
        "in the sunlight. A thick feather mattress is covered by " +
        "feather comforters and several pillows.\n");
    add_item(({"pillow", "pillows"}),
        "The pillows are stuffed with feathers and sit on the bed.\n");
    add_item(({"comforter", "feather comforter"}),
        "The feather comforters are thick and stuffed with feathers.\n");
    add_item("furniture",
        "The furniture is carved from from fine oak. You see a bed, " +
        "a night stand, a bench, and a sofa.\n");
    add_item("sofa", 
        "The sofa is quite large over stuffed. It looks " +
        "inviting and is decorated with a floral pattern.\n");
    add_item(({"table", "night stand" }),
        "The night stand sits at one end of the bed and holds various " +
        "articles of the Queen.\n");
    add_item("bench",
        "An ornately carved bench sits at the end of the Queen. It " +
        "allows the Queen a place to sit while dressing.\n");
    add_item("articles",
        "They are private items of the Queen.\n");
 
    add_exit( TCASTLE_DIR + "q_chamber", "east");
    add_exit( TCASTLE_DIR + "q_closet",  "northwest");
}
 
void
reset_room()
{
}
