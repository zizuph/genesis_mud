/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"
#include <macros.h>

inherit INROOM;

int gOpen = 0;

public void
create_xak_room()
{    
    set_short("Southern crypts");
    set_long("@@my_long");

    add_exit(HALL + "hall3", "north");
    add_exit(HALL + "lifttop", "south");
    add_exit(HALL + "southcrypt5", "west");
}

public string
my_long()
{
    if (gOpen)
        return "This is the east end of the corridor. To the north " +
	       "you can see the Hall of the Ancestors. There is a doorway " +
	       "leading south, and another leading east into darkness. " +
	       "The strange screeching sound seems to come from south. " +
	       "To the west is a lit corridor filled with coffins.\n";
    else
        return "This is the east end of the corridor. To the north " +
	       "you can see the Hall of the Ancestors. There is a doorway " +
	       "leading south. The strange screeching sound seems to come " +
	       "from there. To the west is a lit corridor filled with " +
	       "coffins.\n";
}

public int
query_rat_room() { return !gOpen; }

public void
close_secret_door()
{
    tell_room(TO, "The doorway on the east wall starts to slide shut.\n");
    remove_exit("east");
    gOpen = 0;
    (HALL + "southtmpl")->close_secret_door();
}

public void
open_secret_door()
{
    set_alarm(itof(10 + random(10)), 0.0, close_secret_door);
    add_exit(HALL + "southtmpl", "east");
    gOpen = 1;
    (HALL + "southtmpl")->open_secret_door();
}






