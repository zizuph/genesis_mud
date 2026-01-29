/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#include "../../local.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit  INROOM;

int gOpen = 0;

public void
create_xak_room()
{
    set_short("The South Temple");
    set_long("@@my_long");

    add_exit(HALL + "deadtmpl", "north");

    add_item(({"carvings", "carving", "walls", "wall"}), "The walls " +
	     "are covered in detailed carvings depicting scenes " +
	     "of wars and death. Looking at them makes you feel " +
	     "somewhat morbid.\n");

    add_search(({"wall", "walls", "west wall"}), 3, "my_search", 1);
}

public string
my_long()
{
    if (!gOpen)
        return "You are in the secret south temple of the dead. " +
	       "The room rises to a twenty foot high flat ceiling. " +
	       "The walls contain various carvings.\n";
    else
        return "You are in the secret south temple of the dead. " +
	       "The room rises to a twenty foot high flat ceiling. " +
	       "The walls contain various carvings. There is an " +
	       "exit leading west into the main corridor.\n";
}

public string
my_search(object searcher, string what)
{
    tell_room(HALL + "southcrypt6", "Suddenly the east wall shivers, and " +
	      "a doorway opens.\n");
    (HALL + "southcrypt6")->open_secret_door();
    return "You have probably found a trigger somewhere while " +
           "searching the " + what + ".\n";
}

public void
open_secret_door()
{
    tell_room(TO, "Suddenly the west wall shivers, and a doorway " +
	      "opens.\n");
    add_exit(HALL + "southcrypt6", "west");
    gOpen = 1;
}

public void
close_secret_door()
{
    tell_room(TO, "The doorway slides shut.\n");
    remove_exit("west");
    gOpen = 0;
}

