inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Terel/common/terel_defs.h"     
#include "tomb.h"

#define VOTEROOM (TOMBDIR + "vote_room")

init()
{
     add_action("do_push", "push");
     ::init();
}

create_room()
{
    set_short("snowy path");
    set_long(
	"The incline becomes steeper here and the evergreens have grown " +
	"very close together.  The snow crunches below your feet as it " +
	"is packed down under your weight.  The snow covers the evergreens " +
	"and weighs heavily upon their branches.  There is strange obelisk " +
	"here.\n"
    );

    add_item("obelisk", "@@ob_desc");
    add_item("runes", "@@ob_desc");
       
    add_prop(ROOM_I_INSIDE, 0);

    add_exit(TOMBDIR + "path02", "southwest", 0);
}

string
ob_desc()
{
     int lang;
     int statwis, statint;
     string str;

     str = "The strange obelisk is covered with mystical runes.\n";

     
     lang = TP->query_skill(SS_LANGUAGE);
     statwis = TP->query_stat(SS_WIS);
     statint = TP->query_stat(SS_INT);
     if ((lang > 50) && (statwis + statint > 150))
	  return str + "The runes are too mystical for you to comprehend, " +
	       "but you think one of them might be the symbol of the " +
	       "domain of Terel.\n";
     else
	  return str;
}

do_push(string str)
{
     notify_fail("Push what?\n");
     if (str == "obelisk") {
	  if (VOTEROOM->is_occupied()) {
	       write("Nothing happens.\n");
	       return 1;
	  }
	  
	  write("You feel yourself magically transferred.\n");
	  say(QCTNAME(TP)+" touches the obelisk and disappears in a puff of " +
	      "smoke!\n");
	  TP->move_living("trapdoor", TOMBDIR + "vote_room", 1);
	  return 1;
     }
     return 0;
}
