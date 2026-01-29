/*
 * Main hall in the vampire manor
 * Louie 2006
 */  
#pragma strict_types
#include "defs.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <stdproperties.h>
#define HALL_ROOM (VAMP_ROOM_DIR+"manor/upperhall1")
//proto
string chandelier_desc();

void
create_vamp_room()
{
    set_short("entry hall");
    set_long("You stand in a large entry hall of this ancient manor.  "+
        "The room is dominated by an enormous crystal chandelier which "+
        "hangs far above your head, holding dozens of candles.  "+
        "An ornate doorless archway leads west into the living "+
        "room of the manor.  "+
        "Stairs on the east side of the hall lead to the second "+
        "floor.  "+
        "A large banister with elaborate carvings runs along the "+
        "stairs and across the balcony above you.  "+
        "\n");

    add_exit("upperhall1.c", "up");
    add_exit("den.c", "north");
    add_exit("livingroom.c", "west");
    add_exit("storageroom.c", "east");
    add_exit("dining.c", "northeast");
    add_exit("porch.c", "south");

    add_item(({"hall","large hall","entry hall","large entry hall",
        "here","room","manor","ancient manor"}),
        "This is the large entry hall of the manor.\n");

    add_item(({"chandelier","enormous chandelier","crystal chandelier",
        "enormous crystal chandelier","candles","candle"}),
        "@@chandelier_desc@@");

    add_item(({"archway","doorless archway","ornate archway",
        "ornate doorless archway","west"}),
        "The archway to the west is decorated with various "+
        "symbols and designs of unknown origin gilded in silver "+
        "and gold.  "+
        "It leads to "+
        "the living quarters of the manor.\n");

    add_item(({"symbols","designs","symbols and designs",
        "designs and symbols","symbol","design"}),
        "Although the symbols on the archway are too archaic "+
        "to determine the origins of, you cannot help but imagine "+
        "many of them as abstract representations of knives, "+
        "needles, or stakes.\n");

    add_item(({"banister","large banister","wooden banister",
        "large wooden banister","stairs","stairway"}),
        "The stairway to the second floor begins in the middle "+
        "of the east wall and curves to the north, with a "+
        "wooden banister providing a handgrip along the stairs "+
        "and the balcony above.  The banister is covered "+
        "in elaborate carvings.\n");

    add_item(({"carvings","elaborate carvings","images"}),
        "The carvings along the banister appear to be images "+
        "of faces and people.  "+
        "Disturbingly, it appears that most of the carvings are "+
        "of people either sleeping or screaming.\n");

    add_item(({"balcony"}),
        "The balcony on the second floor runs along the north wall.\n");

    add_item(({"up"}),
        "Far above you is an enormous crystal chandelier and the "+
        "balcony of the second floor.\n");

    add_item(({"west","living quarters","living room","livingroom"}),
        "To the west is the living quarters of the manor.\n");

    add_item(({"north","den"}),
        "To the north appears to be a den.\n");

    add_item(({"northeast","dining room"}),
        "To the northeast appears to be the dining room.\n");

    add_item(({"east","storage","storage room"}),
        "To the east appears to be a storage room.\n");
}

string chandelier_desc()
{
    string s = "The crystal chandelier suspended far above the ground "+
        "is simply enormous, holding dozens of candles.  ";

    if (HALL_ROOM->query_lit()){
        s += "The chandelier is currently lit, "+
            "flooding the area with light.  ";
    } else {
        s += "The chandelier is currently dark.  ";
    }

    return s+"\n";

}