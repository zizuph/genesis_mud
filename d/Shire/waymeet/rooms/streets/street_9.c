/* Outdoors in Waymeet
 * Raymundo, Feb 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/waymeet/defs.h"
#include "/d/Shire/eastroad/western/local.h"
inherit WAYM_LIB_DIR + "base_waymeet.c";




void reset_shire_room();

void
create_waymeet_room()
{
	extraline = ("To the north the street continues toward a well. West of "
		+ "here is a bright yellow shop with a square sign out front. "
		+ "To the east you see more reserved two-storey building with an "
		+ "oval sign. The street itself continues to the south deeper "
		+ "into Waymeet.\n");
	add_item( ({"sign", "signs"}), "Sign, sign, everywhere a sign. Blockin' "
		+ "out the scenery, breakin' your mind. Which sign did you want to "
		+ "look at, the square one or the oval one?\n");
	add_item( ({"square sign", "square"}), "@@square_sign@@");
	add_item( ({"oval sign", "oval"}), "@@oval_sign@@");
	add_cmd_item( ({"square sign", "square"}), "read", "@@square_sign@@");
	add_cmd_item( ({"oval sign", "oval"}), "read", "@@oval_sign@@");
	
	add_item( ({"building", "buildings"}), "You see two buildings here, a "
		+ "yellow building and a two-storey building.\n");
	add_item( ({"yellow", "yellow building"}), "The yellow building is "
		+ "made of river stone, mortared together together to make its "
		+ "walls. The roof is steeply pitched and covered with cedar "
		+ "shingles. There is a square sign out front.\n");
	add_item( ({"two-storey building", "two-storey", "two storey"}), 
		"This building is made of stout timbers. The door is open and "
		+ "welcoming, and you can hear drunken laughter coming from inside. "
		+ "There is an oval sign out front.\n");
	add_street(0);
	
	
	add_exit(WAYM_STREET_DIR + "street_8", "north", gravel_sound, 0, 0);
	add_exit(EAST_R_DIR + "foam_mug_2020", "east", gravel_sound, 0, 0);
	add_exit(WAYM_STREET_DIR + "street_10", "south", gravel_sound,0,0);
	add_exit(WAYM_SHOP_DIR + "novelty_shop", "west", gravel_sound, 0,0);
	
}
void
reset_shire_room()
{
	
}



void
init()
{
	::init();


}

string
square_sign()
{
	return("You read the square sign. It says:\n"
		+ "+----------------------------------------------------------+\n"
		+ "|              XXXXXXXXXXXXX      XXXXXXXXXXXX             |\n"
        + "|           XXX XX XXXXX  X  X   XXXXXX XX XXX XX          |\n"
        + "|         XXXXXXXXXXXXXXXXX  X XXXXXXXXXXXX XXXX XX        |\n"
        + "|        XX  XXXXXXXXX X XXXXX XXXX X XXXXXXXXXXXX XX      |\n"
        + "|       XX  XXXXXXXXXX XXXXXX  XXX XXXX XXX XX   XX  X     |\n"
        + "|       X  XXXX XXXXXXXX  XXXXXXXX XX XXXXXXXXXXXXXXX X    |\n"
        + "|      X  XXX  XXXX   XXXXX       XXXXXXXXXXXXXX XXX XXX   |\n"
        + "|     XX XXXXXXX  XXXX                  XXXX  XXXXXXXXXX   |\n"
        + "|     X XXXXX   XXX                        XXX  XXXXXX X   |\n"
        + "|    XX XXXX  XX          THE BUSHY          XXX  XXXXXX   |\n"
        + "|    X XXX  XX            MOUSTACHE            XX XXXXXXX  |\n"
        + "|    X XX XXX         purveyors of fine         XXXXXXX X  |\n"
        + "|    X  XXX                novelty                XXXXXXX  |\n"
        + "|    XXXX                   goods                  XXXXX   |\n"
        + "|    XXX                                            XXX    |\n"
		+ "|                                                          |\n"
		+ "+----------------------------------------------------------+\n\n");
}

string
oval_sign()
{
	return("\n"
	+ "                   @@@@@@@@@@@@@@ \n"
	+ "             @@@@@@@             @@@@@@@ \n"
	+ "        @@@@@@                         @@@@@@\n"
	+ "     @@@@            .sssssssss.             @@@@\n"
    + "  @@@@           .sssssssssssssssssss           @@@@\n"
    + "  @@           sssssssssssssssssssssssss          @@\n"
    + " @@           ssssssssssssssssssssssssssss         @@\n"
    + " @            @@sssssssssssssssssssssss@ss          @\n"
    + " @             |s@@@@sssssssssssssss@@@@s|s         @\n"
    + " @      _______|sssss@@@@@sssss@@@@@sssss|s         @\n"
    + " @    /         sssssssss@sssss@sssssssss|s         @\n"
    + " @   /  .------+.ssssssss@sssss@ssssssss.|          @\n"
    + " @  /  /       |...sssssss@sss@sssssss...|          @\n"
    + " @ |  |        |.......sss@sss@ssss......|          @\n"
    + " @ |  |        |..........s@ss@sss.......|          @\n"
    + " @ |  |        |...........@ss@..........|          @\n"
    + " @  .  ,       |............ss@..........|          @\n"
    + "  @  .  '------+...........ss@...........|         @\n"
    + "  @@  .________ .........................|        @@\n"
    + "  @@@          |......THE FOAMING .......|       @@@\n"
    + "    @@@       |............MUG............|    @@@\n"
    + "      @@@    |.............................| @@@\n"
    + "        @@@     |.......................|    @@\n"
    + "          @@@       |...............|      @@@\n"
	+ "            @@@                         @@@@@\n"
	+ "              @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
	+ "\n");
}

