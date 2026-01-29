/*
 * This is the Temple of Telan-Ri
 * There is a candle-lighting quest here.
 * Entrance to the Telan-Ri Quest also here.
 * - Alaron February 1997, March 1997
 */

#include "default.h"
#include "/d/Emerald/defs.h"
#include <stdproperties.h>

#define LIT_CANDLE "_lit_candle_quest_"
#define PAPER_OB "/d/Emerald/telberin/castle/obj/cpaper"

#define ALTAR_PUSHED "_altar_has_been_pushed_"
#define ALTAR_DOWN_ROOM "/d/Emerald/telberin/castle/altar/h1"

inherit "/std/room";

void reset_room();

int light_candle(string str);
int tear_paper(string str);
int push_altar(string str);

object cleric;

void
create_room()
{
   set_short("Temple of Telan-Ri");
   set_long("   You are standing amidst the towering, awe-inspiring "+
	    "temple of Telan-Ri. The temple is dedicated to the worship "+
	    "and praise of the elven God of Light. Immense, vaulted "+
	    "ceilings with shining, polished wooden beams spanning the "+
	    "vast ceilings rest high above the rows of oak pews. At the "+
	    "head of the temple you find yourself standing in awe of "+
	    "a sprawling altar area. Huge settings of ivy and flowering "+
	    "plants make it seem like a small jungle surrounding "+
	    "the white marble altar. Above the pearlescant altar is "+
	    "a diamond-shaped glass opening in the ceiling, letting "+
	    "dazzling rays of light splash across the front of the "+
	    "temple. On the southeast wall, up near the altar, is a quiet, "+
	    "hushed section of the temple which houses a stand of "+
	    "hundreds of little candles.\n\n");

   add_item( ({"ceilings", "ceiling", "up", "vaulted ceiling", "beams",
	       "wooden beams", "polished wooden beams",
	       "polished beams", "beam", "roof"}),
	    "The top of the temple is made of up an array of multiple "+
	    "ceilings, each at a different height, containing its own "+
	    "unique and intricate set of vaulted, wooden beams. The effect "+
	    "is mystifying and awe-inspiring. The amount of talent and "+
	    "hard work that must have gone into the construction of "+
	    "this place is staggering.\n");

   add_item( ({"pews", "chairs", "pew", "seat", "chair", "row", "rows",
	       "rows of pews", "oak pews", "oak pew"}),
	    "The rows of oak pews are all arranged angled inward with "+
	    "an aisle leading down the center of the temple. They are "+
	    "angled slightly inward, as if directing the flow of "+
	    "some unseen liquid toward the altar.\n");

   add_item( ({"altar", "altar area", "sprawling altar area"}),
	    "The altar area at the head of the temple is extremely "+
	    "impressive. The altar itself is made of a pearlescant "+
	    "white marble which shows a few swirls of light gray. Behind "+
	    "the altar, a veritable jungle of plants, ivy and flowers "+
	    "expands in all directions, covering the floor and some of "+
	    "the walls beyond.\n"+
	    "@@altar_desc@@");

   add_item( ({"plants", "flowers", "jungle", "ivy"}),
	    "The plants and flowers sprawling out in all directions "+
	    "behind the altar convey the impression of a small jungle, "+
	    "harboring and nestling the altar safe within its "+
	    "protection.\n");

   add_item(({"stairs", "set of stairs"}),
	    "@@stair_desc@@");

   add_item( ({"candles", "stand", "little candles"}),
	    "The little candles on the stand on the southeast wall "+
	    "of the temple are used to remember lost loved ones "+
	    "and relatives. Each worshipper generally lights a candle "+
	    "in remembrance and honor of the lost relative. Candle wax "+
	    "drips onto strips of paper beneath the candles. The truly "+
	    "religious believe these to be the tears of their relative, "+
	    "and tear off a piece of the paper to take home with them.\n");

   add_item( ({"paper", "strips of paper", "strip"}),
	    "The strips of paper lay beneath each of the candles to act "+
	    "as catchers for the drips of melting wax.\n");
   
   add_exit(THIS_DIR + "t1","southwest");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(OBJ_S_SEARCH_FUN, "search_altar");

   add_prop(OBJ_S_WIZINFO, "This is a quest room. Player can light a "+
	    "candle and get something as evidence to bring back to "+
	    "the river guide.\n"+
	    "Also, for another quest, the player can 'push altar' and "+
	    "go to a hidden sacristy.\n");

   set_alarm(1.0, 0.0, reset_room);
}

string
stair_desc()
{
    if (TO->query_prop(ALTAR_PUSHED))
	return("It is a small, narrow, circular stairwell which winds "+
	       "down from underneath the altar into a mirky, damp "+
	       "darkness.\n");
    else
	return("You don't see any stairs here.\n");
}

string
altar_desc()
{
    if (TO->query_prop(ALTAR_PUSHED))
	return("The altar is pushed forward on one side, revealing a "+
	       "set of narrow stairs leading down into the darkness "+
	       "below the masive slab of marble.\n");
    else
	return "";
}

string
search_altar2(object ob)
{
    return("After carefully examining the altar and its surroundings, you "+
	   "notice that the pattern of the floorboards surrounding the "+
	   "altar changes, almost as if the altar is on a separate piece "+
	   "of floor than the rest of the surrounding area.\n");
}

string
search_altar(object ob, string str)
{
    if ( (member_array(str, ({"altar", "altar area", "marble altar"})))!=-1)
	return search_altar2(ob);
    else
	return "You don't find anything of particular interest.\n";
}

void
reset_room()
{
    if (TO->query_prop(ALTAR_PUSHED))
    {
	tell_room(TO, "The room is suddenly filled with the loud echo "+
		  "of stone grinding against stone.\n");
	TO->remove_prop(ALTAR_PUSHED);
	remove_exit("down");
    }

   if(cleric)	
	return;
   else
   cleric = clone_object(NPC_DIR + "cler_1");
   cleric->move_living("into a room", TO);

}

init()
{
    ::init();
    add_action(light_candle, "light");
    add_action(tear_paper, "tear");
    add_action(push_altar, "push");
}

int
light_candle(string str)
{
    if (str != "candle")
    {
	notify_fail("Light what?\n");
	return 0;
    }

    write("You take the thick source candle from the side of the "+
	  "stand and light a small candle in remembrance of lost "+
	  "loved ones.\n");
    say(QCTNAME(TP)+" takes the source candle from the side of "+
	"the stand and lights a small candle in remembrance of lost "+
	"loved ones.\n");
    write("You notice the wax start to drip from the candle onto the "+
	  "paper.\n");
    TP->add_prop(LIT_CANDLE,1);
    return 1;
}

int
tear_paper(string str)
{
    if (str != "paper")
    {
	notify_fail("Tear what?\n");
	return 0;
    }

    if (!TP->query_prop(LIT_CANDLE))
    {
	notify_fail("Why would you want to tear the paper? It has "+
		    "no meaning for you at this point.\n");
	return 0;
    }

    write("You tear off the piece of paper with the wax from your "+
	  "candle on it.\n");
    say(QCTNAME(TP)+" tears off the piece of paper with the wax from "+
	TP->query_possessive()+" candle on it.\n");
    
    reset_euid();
    clone_object(PAPER_OB)->move(TP,1);
    return 1;
}

int
push_altar(string str)
{
    notify_fail("Push what?\n");
   
    if (str != "altar")
	return 0;

    if (TO->query_prop(ALTAR_PUSHED))
    {
	notify_fail("The altar is already pushed forward.\n");
	return 0;
    }

    write("You grunt and strain and manage to push the altar forward "+
	  "a bit, revealing a set of stairs leading down.\n");
    say(QCTNAME(TP)+" grunts and strains, managing to push the altar "+
	"forward a bit, skewing it to one side.\n");
    add_exit(ALTAR_DOWN_ROOM, "down", "@@go_down@@");
    add_prop(ALTAR_PUSHED,1);
    return 1;
}

int
go_down()
{
    write("You manage to squeeze through the opening provided by the "+
	  "skewed altar and step carefully down the narrow, circular "+
	  "staircase leading into the darkness below ...\n\n");
    return 0;
}




