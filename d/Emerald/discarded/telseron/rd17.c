/*
 * The road between the bank and the store in Telseron
 * By Finwe, September 1996        
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
 
void reset_room();
 
void
create_room()
{
    reset_room();
    set_short("A wide boulevard"); 
    set_long("   A boulevard in the eastern part of the city. " +
        "around you, many elven folk greet you as they go " +
        "about their business. It is wide and well used. On " +
        "either side of the road are two story stone buildings. " +
        "The one to the north is plain looking building. South " +
        "of here, sounds of pain and agony echo from the " + 
        "building. West of here is a peaceful park. " +
        "You see signs on both buildings. This is " +
        "Camellia street. It runs east and west.\n\n");
 
    add_item("trees",
        "The trees are large with branches that form a canopy " +
        "across the boulevard. You don't recognise what kind of " +
        "trees they are but they resemble maples. The bark " +
        "is smooth to the touch and a silver color. A dim glow " +
        "surrounds each tree. Under the trees are small plantings " +
        "of colourful flowers.\n");
    add_item(({"road", "street", "boulevard"}),
        "The boulevard is constructed of white marble. So cleverly " +
        "constructed is it that the street seems to be one " +
        "continuous piece of marble. The road is well travelled, " +
        "but oddly enough, doesn't show any wear from all the " +
        "traffic. The boulevard surrounds Telseron like a " +
        "protective wall.\n");
    add_item("sky",
        "You can make the sky from between the canopy of trees. " +
        "It's a deep azure blue without a sign of any clouds.\n");
    add_item("ground",
        "You see a wide boulevard.\n");
    add_item("buildings",
        "A wide variety of buildings surround you.\n");
    add_item("elves",
        "These are the residents of Telseron. Like most elves, " +
        "They love forests, songs, and many good things.\n");
    add_item(({"plantings", "flowers"}),
        "The plantings are full of flowers which fill the " +
        "air with fragrance.\n");
    add_item(({"sign", "signs"}), 
        "Both signs have words painted on them.\n");
    add_cmd_item("north sign", "read", "@@read_n_sign@@");
    add_cmd_item("south sign", "read", "@@read_s_sign@@");
 
                                          
    add_exit(TOWNSHIP_DIR + "post_foyer", "north");
    add_exit(TOWNSHIP_DIR + "adv_guild", "south");
    add_exit(TOWNSHIP_DIR + "rd18", "east");
    add_exit(TOWNSHIP_DIR + "pk05", "west");
}                    
 
void
reset_room()
{
}
 
 
string
read_n_sign()
{
    return "Hanging above the door, you read the sign, it says:\n" +
        "'Telseron Post Office'.\n";
}
 
 
string
read_s_sign()
{
    return "On the sign, hanging above the door, you see painted " +
        "in bright letters:\n" + 
        "Telseron Adventurer's Guild'.\n";
}
