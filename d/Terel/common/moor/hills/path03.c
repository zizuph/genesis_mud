// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include "/d/Terel/include/herb_arrs.h"
inherit "/d/Terel/std/herbsearch.c";
#include <ss_types.h>

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

#define VOTEROOM ("/d/Terel/common/moor/vote_puzzle/vote_room")

void
init()
{
     add_action("do_push", "push");
     ::init();
}

void
create_room()
{
    set_short("snowy path");
    set_long(
	"The incline becomes steeper here and the evergreens have grown " +
	"very close together. The snow crunches below your feet as it " +
	"is packed down under your weight. The snow covers the evergreens " +
	"and weighs heavily upon their branches.\nThere is strange obelisk " +
	"here.\n"
    );

    add_item("obelisk", "@@ob_desc");
    add_item("runes", "@@ob_desc");
       
    add_prop(ROOM_I_INSIDE, 0);

    add_exit("path02", "southwest", 0);
	
	set_up_herbs( ({ ONE_OF_LIST(FOREST_HERBS),
        ONE_OF_LIST(FROST_HERBS), ONE_OF_LIST(FOREST_HERBS)}),
      ({"trees","evergreens","tree","shrubs","here"}) , random(3) );

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

int
do_push(string str)
{
     notify_fail("Push what?\n");
     if (str == "obelisk") {
	  if (VOTEROOM->is_occupied()) {
	       write("Nothing happens, prehaps you should try again later?\n");
	       return 1;
	  }
	  
	  write("You feel yourself magically transferred.\n");
	  say(QCTNAME(TP)+" touches the obelisk and disappears in a puff of " +
	      "smoke!\n");
	  TP->move_living("trapdoor", VOTEROOM, 1);
	  return 1;
     }
     return 0;
}
