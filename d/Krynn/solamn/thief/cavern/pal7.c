/* created by Aridor 03/09/94
 * herbs added by Teth, Feb.26,96
 */

#include "../local.h"

inherit ROOM_BASE
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs( ({"meadow","urban",}) );


#include "/d/Krynn/common/defs.h"

void
reset_thief_room()
{
    set_searched(random(2));
}

void
create_thief_room()
{
    set_short("On a path.\nThere is one obvious exit: east");
    set_long("You are standing on a narrow path on an overgrown meadow, " +
	     "which is more like a thicket now, preventing you from going " +
	     "north or south. To your east, a small entrance opens up in " +
	     "the mountainside of the Vingaard Mountains and to your west " +
	     "the Palanthas city wall blocks any view of the city.\n" +
	     "There is one obvious exit: east.\n");
    
    set_noshow_obvious(1);
    add_exit(CAVERN + "pal6","east","@@tell_aridor@@");
    add_exit(PALANWALL,"west","@@thieves_only");
    
    LIGHT;
    OUTSIDE;
    
    add_item("wall","It's the Palanthas city wall from the outside. It is " +
	     "made from large stone blocks and the path just leads " +
	     "up to it and then comes to an end.\n");
    add_search("wall",10,"You find that you can just go west into the wall " +
	       "from here.\n");
    add_item(({"blocks","block","stone","stone blocks","stone block"}),
	     "The larger ones have about a man's height in diameter, " +
	     "but there are smaller ones in between, too.\n");
    add_item(({"thicket","meadow","grass","bushes"}),
	     "A lot of grass, bushes and thorny shrubs grow here.\n");
    add_item(({"shrubs","thorny shrubs"}),
	     "The thorny shrubs are brambles.\n");
    add_item(({"brambles"}), "They have thorns.\n");
    add_item(({"thorns"}), "They are very sharp.\n");
    add_item(({"entrance","small entrance","mountainside"}),
	     "The entrance leads into the mountains! Right next to " +
	     "it on the mountainside you notice a few symbols.\n");
    add_item("symbols","You decipher the symbols to be the words 'DANGER - " +
	     "KEEP OUT'.\n");
    add_item("path","The path leads from the wall to the small entrance in the " +
	     "mountainside.\n");
    
    add_cmd_item(({"against wall","against the wall","on wall","the wall",
		     "on the wall","wall"}),({"push","lean"}),
		 "@@thieves_only@@");

    reset_room();
    seteuid(getuid(TO));
    set_up_herbs(({ONE_OF(herbs),ONE_OF(herbs),ONE_OF(herbs),
        ONE_OF(herbs)}),({"thicket","meadow","grass","bushes","shrubs",
        "thorny shrubs"}), 4);

}

int
thieves_only()
{
    SAY(" leans onto the wall and suddenly a hole opens.");
    tell_room(PALANWALL,"A large stone block in the east wall moves aside.\n");
    write("Knowing you must be able to get through somewhere at the end of " +
	  "the path you push hard on the stones and a large stone block " +
	  "suddenly swings inside the wall. You topple through the opening " +
	  "and the stone block shuts behind you.\n");
    TP->move_living("M",PALANWALL,1,0);
    set_alarm(1.0,0.0,"close_again",TP);
    find_living("aridor")->catch_msg(TP->query_name() + " leaves THIEFAREA " +
				     "to Palanthas.\n");
    call_out("close_again",1,TP);
    return 1;
}

void
close_again(object who)
{
    tell_room(TO,
	      "The stone blocks moves back into place, closing the hole.\n");
    tell_room(PALANWALL, "The stone blocks moves back into place.\n", who);
}

int
tell_aridor()
{
    find_living("aridor")->catch_msg(TP->query_name() + " enters THIEFAREA " +
				     "from Palanthas.\n");
    return 0;
}
