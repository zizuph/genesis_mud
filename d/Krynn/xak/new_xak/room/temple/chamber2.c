/* 
 * Xak Tsaroth - Temple of Mishakal
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

object gDoor;

public void
create_xak_room()
{    
    set_short("In the middle of Chamber of Mishakal");
    set_long("@@my_long@@");

    LIGHT;

    add_item(({"statue", "mishakal", "beautiful statue"}),
	     "The statue is of a woman in flowing robes. Her marble face " +
	     "bears an expression of radiant hope, tempered with sadness. " +
	     "A strange amulet hangs around her neck. You suddenly realize " +
	     "that you are stareing in wonder upon Mishakal, " +
	     "goddess of healing. The statue seems to be unfinished, " +
	     "incomplete. Part of it is missing. The marble woman's hands " +
	     "are curved, as if they had been holding a long slender pole, " +
	     "but the hands are empty.\n");
    
    add_item(({"amulet", "strange amulet"}), "The amulet has the holy " +
	     "symbol of Mishakal on it, two circels joined together. The " +
	     "amulet seem impossible to get.\n");

    add_exit(TEMPLE + "chamber1", "north");
    add_exit(TEMPLE + "small_room", "east");
    add_exit(TEMPLE + "chamber3", "south");
    
    gDoor = clone_object(OBJ + "d_chamber2");
    gDoor->move(TO);
}

public string
my_long()
{
    return "You are standing in the middle of a vast circular chamber, " +
           "which is better known as the Chamber of Mishakal. The chamber " +
	   "is about fifty feet in diameter with white walls made of stone " +
	   "soaring up sixty feet to a domed ceiling. The chamber is " +
	   "given an extra appearence of size by its emptiness, the only " +
	   "thing of note in the chamber being a statue of singular grace " +
	   "and beauty in the center of the room. There is an exit leading " +
	   "east into a smaller room. The chamber extends both to the " +
	   "north and south, and there is a set of " + DOOR(gDoor) + 
	   " golden double doors leading west. The light in this room " +
	   "emanats from the statue.\n";
}








