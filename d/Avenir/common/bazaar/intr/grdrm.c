// Bazaar Street4 (/d/Avenir/common/bazaar/intr/grdrm.c)
// creator(s):	Ilyian May 95
// last update: Denis, Oct'97, Made the east exit obvious.
// purpose:
// note:
// bug(s):
// to-do:

inherit "/std/room";
inherit "/d/Avenir/inherit/tail";

#include <macros.h>
#include "/sys/stdproperties.h"

#include "/d/Avenir/common/bazaar/bazaar.h"

object guard1, guard2, guard3, guard4;

reset_room()
{
  if (!guard1)
   {
      guard1 = clone_object(BAZAAR + "NPCS/rgrd.c");
      guard1->arm_me();
      guard1->move_living("M", this_object());
    }
  if (!guard2)
   {
      guard2 = clone_object(BAZAAR + "NPCS/rgrd.c");
      guard2->arm_me();
      guard2->move_living("M", this_object());
    }
  if (!guard3)
   {
      guard3 = clone_object(BAZAAR + "NPCS/rgrd.c");
      guard3->arm_me();
      guard3->move_living("M", this_object());
    }
  if (!guard4)
   {
      guard4 = clone_object(BAZAAR + "NPCS/rgrd.c");
      guard4->arm_me();
      guard4->move_living("M", this_object());
    }
}

void
create_room()
{
   AE(EXTR + "str21", "west", 0);
   AE(EXTR + "str25", "east", 0);

   AI(({"bench","benches"}),
     "They are wooden and uncomfortable.\n");
   AI(({"bunk","bunks", "south wall"}), 
      "There are only a few bunks along the south wall, which "+
      "leads you to think that most of the guards probably have "+
      "houses or quarters elsewhere.\n");
   AI(({"north wall", "signs"}),
      "There are two signs on this wall. Both have huge letters "+
      "above them. One reads 'INFIDELS' and the other reads "+
      "'ABSOLVED'.\n");
   AI(({"sign"}),
      "Which one? The infidels sign or the absolved sign?\n");  
   AI(({"infidel", "infidels", "infidels sign", "infidel sign"}),
      "@@do_infidel@@The people listed above are infidels unless "+
      "their names also appear on the 'absolved' sign.\n");
   ACI(({"infidel", "infidels", "infidels sign", "infidel sign"}), "read",
      "@@do_infidel@@The people listed above are infidels unless "+
      "their names also appear on the 'absolved' sign.\n");
   AI(({"absolved", "absolved sign"}),
      "@@do_absolved@@The people listed above have been "+
      "absolved of their crimes.\n");
   ACI(({"absolved", "absolved sign"}), "read",
      "@@do_absolved@@The people listed above have been "+
      "absolved of their crimes.\n");
  
   SHORT("guard house");
   LONG("You are inside a long, low building with two entrances, "+
       "one leading toward the Bazaar, and the other toward the "+
       "Tribunal. This central location makes this place the "+
       "ideal location for the guards to rest between their "+
       "patrols. A row of benches faces the north wall, "+
       "upon which two signs have been posted. Along the "+
       "south wall a few bunks have been placed.\n");

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


   reset_room();
}

string
do_infidel()
{
    string text;
    text = read_file("/d/Avenir/log/misc/malefactor");
    this_player()->more(text);
    return "\n";      
}

string
do_absolved()
{
    string text;
    text = read_file("/d/Avenir/log/misc/absolved");
    this_player()->more(text);
    return "\n";      
}