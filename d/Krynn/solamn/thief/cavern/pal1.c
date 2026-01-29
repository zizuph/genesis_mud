/* created by Aridor 03/09/94 */
/* Aug 27, 2018: Added no-scry protection in guild (Gorboth) */

#include "../local.h"

inherit ROOM_BASE

#include <stdproperties.h>

#define OTHER    CAVERN + "pal6"

void
create_thief_room()
{
    set_short("In a cavern.\nTo your west, there is a door.\n" +
	      "There is one obvious exit: southeast");
    set_long("This is a bend in the hallway, which continues to " +
            "your west, and also to your southeast. To your west, " +
	     "there is a door.\n" +
	     "There is one obvious exit: southeast.\n");
    
    set_noshow_obvious(1);

    add_prop(ROOM_M_NO_SCRY, "Haze, and nothing more, is all that"
      + " appears.");

    add_exit(GUILDR + "chapel","southeast");
    add_exit(CAVERN + "pal6","west","@@thieves_only");
    
    LIGHT;
}

int
thieves_only()
{
    SAY(" opens the door.");
    tell_room(OTHER,"The door opens.\n");
    write("You open the door, walk through, and close the door again.\n");
    set_alarm(0.0,0.0,"close_again",TP);
    return 0;
}

void
close_again(object who)
{
    tell_room(TO,"The door closes again.\n");
    TELL_ROOM(OTHER, who, " closes the door.\n", who);
}
