/*
 * The throne room in the castle in Telseron
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
    set_short("The Throne Room");
    set_long("   You stand in the Throne Room of Telseron. This is " +
        "truly one of the most opulent rooms you have ever seen. " +
        "Where the castle was richly decorated, this room is lavishly " +
        "embellished. The walls are decorated with large pilasters " +
        "that reach to the vaulted ceiling. The ceiling is made of " +
        "glass, filling the room with natural light. You notice a beam " +
        "of light from the ceiling illuminates the throne. The floor " +
        "is decorated with a large mosaic, made entirely of jewels " +
        "and semi-precious stones. It twinkles in the light. Courtiers " +
        "and other servants of the King are present, court officials " +
        "mill around, supplicants wait to meet with the King, and " +
        "highborn elves talk to each other, seeking to gain favor with " +
        "each other and the King and Queen.\n\n");
 
    add_item(({"servants", "courtiers"}),
        "These elves are well dressed in green, signifying that " +
        "they are of the Court.\n");
    add_item(({"officials", "court officials"}),
        "You see counsellors, advisors, and leaders for the King here. "+
        "They are dressed in hunter green.\n");
    add_item(({"elves", "highborn elves"}),
        "These elves belong to the upper class of society. Some are " +
        "prestigious, while others are simply well to do. They " +
        "gossip about worthless items and are dressed in " +
        "fashionable clothes as they try to impress everyone " +
        "present, including the King and Queen.\n");
    add_item("supplicants",
        "These elves patiently await to plead their case before the " +
        "King and Queen.\n");
    add_item("beam of light",
        "This light comes frction of the ceiling, and " +
        "illuminates the throne.\n");
    add_item("throne",
        "This massive object is made of solid gold. It is decorated " +
        "with reliefs of trees and flowers.\n");
    add_item(({"wall", "walls"}),
        "The walls have pilasters, or columns set into them. They " +
        "are decorated with panels.\n");
    add_item(({"pilaster", "pilasters", "columns"}),
        "The pilasters are carved of white marble and shine from " +
        "constant care. They are shaped like great oak tree trunks.\n");
    add_item("panels",
        "Vertical panels between the wall depict  They are " +
        "painted with great care and detail. They appear to be a " +
        "living history of the elves. As you look at them, the " +
        "panels shift and change, reflecting what is transpiring in " +
        "the elven nations. Dadoes decorate the upper and lower " +
        "portions of the walls.\n");
    add_item("dadoes",    
        "These smaller recessed areas of the walls fram the panels " +
        "and between the pilasters. They measure about 2 feet tall " +
        "and are decorated with raised reliefs of flowers. The frames " +
        "of the upper dadoes are of made gold while the lower dado " +
        "frames are made from ivory.\n");
    add_item(({"capital", "capitals"}),
        "The top of the pilasters are carved to resemble tree tops. " +
        "Solid gold and silver leaves hang from the branches, moving " +
        "slightly as elves pass by them.\n");
    add_item(({"base", "bases"}),
        "The bottom of the pilasters are carved as flowers. Jewels " +
        "are inset into the flowers.\n");
    add_item("ceiling", 
        "The ceiling is made from great panes of etched glass. " +
        "Vining flowers have been etched into its the outer " +
        "edges. Floral motifs decorate the remainder of the " +
        "ceiling except for one section. This section is plain as " +
        "it magnifies light onto the king below, illuminating the " +
        "throne in a bath of golden light.\n");
    add_item(({"mosaic", "down", "floor", "ground"}),
        "The mosaic fills the ground. It is made of jewels set " +
        "into the floor of the room. The pattern of the floor is " +
        "of a meadow complete with flowers and wildlife. The " +
        "jewels twinkle gently in the sunlight from the ceiling " +
        "above.\n");
    add_item(({"door", "gilded door"}),
        "This door is gilded and opens east into " +
        "the King's private office.\n");
 
    add_exit(TCASTLE_DIR + "ac01",     "south");
}

void reset_room()
{
}
