/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"

object monster;

public void
reset_room()
{
    if (monster) return;
    monster = clone_object(PATH + "mystic2");
    monster->move_living("M", this_object());
}

public void
create_room()
{
   set_short("Hallway");
   set_long("Shadows abound in this small dark hall. The stone is "
           +"darker and some grief or misery seems to dwell within its "
           +"very depths. An inaudible voice cries out, nothing real, "
           +"only the melancholy intonations of those long forgotten. "
           +"Upon the stone floor is an incription that forms a small "
           +"circle, the letters are silver.\n");

   add_item("inscription", "Silver letters upon the floor in a circle.\n");
   add_cmd_item("inscription", "read",
        "Ye who live shall not forget the dead. For in the dead lives all "
      + "that once was and all that yet shall be.\n");
   add_item("letters", "They are silver and have been placed into the floor.\n");
   add_item(({"floor", "ground", "stone floor"}),
            "The stone floor has an inscription.\n");
   add_item("arch", "It is of black obsidian, it leads into the dark "
                   +"tower of the shrine.\n");
   add_my_desc("An obsidian arch leads east into the shrine tower.\n");

   add_exit(PATH + "temple", "west", 0);

   add_exit(PATH + "tower1", "east", "@@whispers");

   reset_room();
}

public int
whispers()
{
   write("You pass beneath the black arch and enter the tower.\n");
   say(QCTNAME(this_player()) + " passes under the obsidian arch.\n");
   say("You hear whispers from all around you.\n");
   
   return 0;
}
