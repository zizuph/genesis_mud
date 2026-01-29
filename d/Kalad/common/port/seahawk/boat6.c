#include "../default.h"
inherit PORT_ROOM;

#include <ss_types.h>

#define FOUND_S_TRAP     "_found_ship_trapdoor"
int open;   /*whether trap is open or not*/
/* modified by Antharanos */
create_port_room()
{
    set_short("The bow of the Seahawk");
    set_long("This is the bow of the ship. You hear "+
      "faint noises from below. One of the floor boards has a small "+
      "edge that sticks up above the rest of the floor. The squeaking of "+
      "rats and mice is clearly audible.\n");

    /*
    * if the player merely examines the floor,
       *   there is a lesser chance to find the trapdoor
    */
    add_item(({"floor","floor boards","boards","floor board"}),
      "@@ex_floor"); /*VBFC call to return the description*/

    add_prop(ROOM_NO_TIME_DESC,1);

    add_prop(OBJ_I_SEARCH_TIME, 2); /*extra time to search here*/
    add_prop(OBJ_S_SEARCH_FUN,"search"); /*function to call for search*/

    add_exit(PORT + "seahawk/boat2", "northwest",0);
    add_exit(PORT + "seahawk/boat5", "southwest",0);
}

void
init()
{
    ::init();
    add_action("open","open"); /* AA is our shortcut for               */
    AA(close,close);           /* add_action. They mean the same thing */
    AA(enter,enter);
    AA(enter,go);
    add_action("enter","down",1);/*only part of the command need be typed*/
}

string
search(object player, string str, int examined)
{
    int skill, aware, find;
    string item, rest;

    if (sscanf(str,"%s for %s",item,rest) != 2)
	item = str;

    if (item != "here" && item != "floor" && item != "boards"
      && item != "floor boards" && item != "floor board")
	return "";

    if (open) /*the trapdoor is already open*/
    {
	player->add_prop(FOUND_S_TRAP,1); /*so player can find it later*/
	return "Aside from the open trapdoor, you find nothing special.\n";
    }


    /*
    * The player uses whichever skill is higher to look
    * for the trap: awareness or find and remove traps
    */
    aware = player->query_skill(SS_AWARENESS);
    find = player->query_skill(SS_FR_TRAP);
    if (aware > find)
	skill = aware;
    else
	skill = find;

    if (!examined) /*player searches instead of examining*/
    {
	if (item == "here") /*general search of the room*/
	    skill = skill + 5;
	else
	    skill = skill + 10; /*better chance if specifically searching floor*/

	if (rest == "trapdoor" || rest == "trapdoors" || rest == "traps")
	    skill = skill + 10; /*better chance if specifically looking for door*/
    }


    if (skill > random(20)) /*easy to find*/
    {
	player->add_prop(FOUND_S_TRAP,1);
	return "You discover a closed trapdoor in the floor.\n";
    }

    else
	return ""; /*didn't find the trap*/
}

/*
* function name: ex_floor
* description:   examine the floor of the boat.
*                Sends a call to the search function
*                with a lesser chance of finding the trapdoor
* returns:       description of floor and success of search
*/
string
ex_floor()
{
    string ret;

    ret = "The thick planks are slightly warped.\n";

    ret = ret + search(TP,"floorboards",1);

    return ret;
}

/*
* function name: open
* description:   called when player tries to open trapdoor
*                -checks if player has found the trapdoor first
   * arguments:     str - what the player wants to open
* returns:       1 if successful, 0 if failed
   */
int
open(string str)
{
    notify_fail("Open what?\n"); /*if player isn't trying to open trapdoor*/
    if (str != "door" && str != "trapdoor" && str != "trap")
	return 0;

    NF("It's already open!\n");
    if (open) /*check if door is already open*/
	return 0;

    NF("Open what?\n");
    if (!TP->query_prop(FOUND_S_TRAP))
	return 0; /*don't clue player in if hasn't found trap*/

    write("You pry open the trapdoor in the floor.\n");
    say(QCTNAME(TP) + " opens a trapdoor in the floor.\n");
    add_my_desc("There is an open trapdoor in the floor, leading down.\n");
    open = 1; /*open the door*/
    return 1; /*success*/
}

/*
* function name: close
* description:   called when player tries to close trapdoor
* arguments:     str - what the player wants to close
* returns:       1 if successful, 0 if failed
   */
int
close(string str)
{
    NF("Close what?\n"); /* NF is another shortcut */
    if (str != "door" && str != "trapdoor" && str != "trap")
	return 0;

    if (!TP->query_prop(FOUND_S_TRAP))
	return 0; /*don't clue player in if hasn't found trap*/

    NF("It's already closed!\n");
    if (!open) /*check if door is already closed*/
	return 0;

    write("You gently close the trapdoor in the floor.\n");
    say(QCTNAME(TP) + " closes the trapdoor in the floor.\n");
    remove_my_desc();
    open = 0; /*close the door*/
    return 1; /*success*/
}

enter(string str)
{
    if (query_verb() == "down" || query_verb() == "d")
    {
	NF("what?\n");
	if (str)
	    return 0;
    }

    else /*if verb is 'enter' or 'go' */
    {
	NF(C(query_verb()) + " what?\n");
	if (str != "door" && str != "trapdoor" && str != "floor")
	    return 0;
    }


    if (!open)
    {
	if (TP->query_prop(FOUND_S_TRAP)) /*knows about trap*/
	    NF("It isn't open!\n");
	return 0; /*if hasn't found trap, we won't mention it*/
    }


    write("You enter the trapdoor in the floor.\n");
    TP->move_living("into the trapdoor in the floor",PORT + "seahawk/fl1");
    return 1;
}

