/*
 * The road between the common room and the pub in Telseron
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
    set_long("   A boulevard in the western edge of the city. All " +
        "around you, many elven folk greet you as they go about " +
        "their business. It is wide and well used. On either side " +
        "of the road are two story stone buildings. The one on the " +
        "south is wide open as elves leave and enter it. You hear " +
        "raucous singing and an occasional yell from it. North, " +
        "the building is deserted. It is boarded up solidly and " +
        "locked. A sign hangs on the south building. West of here, " +
        "the street intersects with Stephanotis street. East is " +
        "a quiet park. You are on Camellia street.\n\n");
 
    add_item("trees",
        "The trees are large with branches that form a canopy " +
        "across the boulevard. You don't recognise what kind " +
        "they are but they resemble maples. The bark " +
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
        "The sign has words painted on it.\n");
    add_cmd_item("sign", "read", "@@read_s_sign@@");
 
    add_exit(TOWNSHIP_DIR + "com_room", "north", "@@no_way@@");                                          
    add_exit(TOWNSHIP_DIR + "pub", "south");
    add_exit(TOWNSHIP_DIR + "pk04", "east");
    add_exit(TOWNSHIP_DIR + "rd15", "west");
}                    
 
void
reset_room()
{
}
 
 
string
read_s_sign()
{
    return "On the sign, hanging above the door, you see painted " +
        "in bright letters:\n" + 
        "Telseron Pub'.\n";
}
 
 
int
pub_closed()
{
    write("You try to go into the pub, but discover it's " +
        "been closed. A sign on the door reads:\n\n" +
        "       Sorry for the inconvenience, but the pub is closed.\n"+
        "       A fight broke out and the drunks destroyed most of\n"+
        "       the place. We hope to reopen as soon as possible.\n\n" +
        "                                       Selatin, Owner\n");
return 1;        
}
int
no_way()
{
    write("You try to head north into the deserted building, " +
        "but realize you can't. The door is locked.\n");
    return 1;
}
 
