/*
 * 3k1.c
 * Main lobby for the HQ of the Keepers of Telberin
 * This lobby has the npc guildmaster, Vilgurn ... The players
 * need to ask his blessing to join the guild, he gives them the
 * ornamental sheath, which they show to the queen and then pledge
 * to telberin - which begins the entrance ceremony to the guild.
 *
 * Alaron November 1996
 */

#include <composite.h>
#include "/d/Emerald/defs.h"
#include "default.h"

inherit "/std/room";

object vilgurn;    /* Vilgurn is the npc guildmaster/record-keeper */
object sitter;     /* Person sitting in the chair .... */
void reset_room();

static int someone_is_sitting;

void
create_room()
{
  someone_is_sitting = 0;
  
  set_short("Large, stone-walled foyer");
  set_long("   The foyer spreads out before you. Looking around the "+
	   "stone-walled room, you notice a few sparse furnishings and "+
	   "scattered wall hangings and decorations. The floor is "+
	   "smooth, shining marble which reflects the stone walls and "+
	   "ceiling on its polished surface. At the back of the room, "+
	   "facing the southern entrance, is an enormous, dark wooden "+
	   "desk. The desk is covered with scrolls, tomes and large "+
	   "books. There is a rather elegant-looking ink and quill "+
	   "set arranged neatly at the front of the desk.\n"+
	   "Behind the desk is a closed, heavy wooden door.\n\n");
  
  add_prop(ROOM_I_INSIDE,1);
  
  add_item( ({"floor", "marble", "smooth marble", "shining marble"}),
	    "The floor is made of smooth, shining marble. Its polished "+
	    "surface reflects portions of the ceiling and walls if you "+
	    "peer at it from the right angle.\n");
  
  add_item( ({"furnishings", "hangings", "wall hangings", "decorations"}),
	    "There are a few furnishings and decorations here. There is a "+
	    "chair in front of the desk and several expertly painted "+
	    "portraits of powerful, majestic-looking elves.\n");
  
  add_item("chair",
	   "The chair in front of the desk is simple and ordinary. It "+
	   "is probably used for people to sit and converse with the "+
	   "owner of the desk.\n");
  
  add_item( ({"portraits", "paintings", "portrait", "painting"}),
	    "The portraits appear to be of heroic elves, or perhaps "+
	    "elven leaders. They all have the battle-hardened look of "+
	    "a veteran about them, yet there is something more, something "+
	    "almost regal, about their countenances.\n");
  
  add_item( ({"desk", "enormous desk", "dark desk", "dark wooden desk",
		"enormous dark wooden desk", "wooden desk"}),
	    "The desk at the back of the room in front of the north "+
	    "door is made of a dark, solid wood. It looks like it has "+
	    "been very well used, yet very well cared for. It is probably "+
	    "several hundred years old. There are scrolls, books and "+
	    "tomes resting atop the desk alongside a very elegant looking "+
	    "ink and quill set.\n");
  
  add_item( ({"scroll", "scrolls", "books", "tomes","large books"}),
	    "The desk seems to be cluttered with information. It is "+
	    "in the process of being blanketed by a mass of scrolls, "+
	    "books and tomes. There is information on maps, information "+
	    "on strategies, armies, force strengths and several things "+
	    "which you imagine you might be killed for exploring further. "+
	    "You decide not to sift through the information in more "+
	    "detail for the sake of your health.\n");
  
  add_item( ({"set", "ink set", "ink and quill set", "quill set",
		"ink", "quill"}),
	    "The ink and quill set is very elegant indeed. It is made of "+
	    "solid gold. At the base of the quill holder, there is a "+
	    "separate, bronze plaque with some writing on it.\n");
  
  add_item( ({"plaque", "writing", "bronze plaque"}),
	    "There is a bronze plaque attached to the base of the ink "+
	    "and quill set with some carved writing on it.\n");
  
  add_cmd_item( ({"writing", "carved writing"}),
		"read",
		"The plaque attached to the base of the ink and quill "+
		"set reads:\n"+
		"          For dedicated, exceptional, and honorable service "+
		"to Telberin.\n"+
		"          We thank you, Vilgurn.\n");
  
  add_item( ({"door", "heavy wooden door", "north door"}),
	    "The north door, which stands immediately behind the "+
	    "large desk, is made of obviously heavy, thick wood. It "+
	    "has several gashes and knicks in it, including a few "+
	    "holes which have the unmistakable pattern caused by a "+
	    "short-range shot from a crossbow. Apparently this door "+
	    "has kept out its share of unwanted intruders.\n");
  
  add_exit(CASTLE_DIR + "stairs", "down");
  add_exit(CASTLE_DIR + "3k2", "north", "@@guild_check@@");
  
  set_alarm(1.0, 0.0, reset_room);
}

void
reset_room()
{
#if 0
  if (!vilgurn) {
    vilgurn = clone_object(CASTLE_DIR + "npc/vilgurn");
    vilgurn->arm_me();   /* have vilgurn wield in the void. */
    vilgurn->move(TO);   /* bring vilgurn here. */
    vilgurn->command("cough");
    vilgurn->command("emote sips some water as he pores over his work.");
  }
#endif
}

int
guild_check()
{
  if (!present(vilgurn)) {
      if (TP->query_kot_member()) {
	  write("As you step through the door you wonder why Vilgurn "+
		"is not at his post ... \n\n");
	  return 0;
      }
      else {
	  write("As you step through the door you wonder why the desk "+
		"in the room is unattended ... \n\n");
	  return 0;
      }
  } 
  // Vilgurn is here ... 
  else {   
    if (!TP->query_kot_member())
      {
	write("Vilgurn steps toward you threateningly.\n");
	vilgurn->command("say to "+lower_case(TP->query_real_name())+
			 " Know that if you commit misdeed while under "+
			 "the roof of the Keepers, may your creator have "+
			 "mercy upon your soul.");
	return 0;
      }
    else return 0;
  } /* Vilgurn was here ... else clause */
}

init()
{
  ::init();
  add_action("sit_in_chair", "sit");
  add_action("stand_up", "stand");
}

int
sit_in_chair(string str)
{
    if( (member_array(str, ({"in chair", "chair", "down","at desk", "on chair"})))==-1) {
	notify_fail("Sit where?\n");
	return 0;
    }
    
    if ( someone_is_sitting ) {
	notify_fail("There is already someone sitting in the chair.\n");
	return 0;
    }
    
    someone_is_sitting = 1;
    // add_my_desc(COMPOSITE_LIVE(({TP}))+" is sitting in the chair.\n", this_object());
    sitter = TP;
    add_my_desc(VBFC_ME("resolv_composit"));
    TP->add_prop("_is_sitting_down_", 1);
    write("You sit down in the chair at the desk.\n");
    say(QCTNAME(TP)+" sits down in the chair at the desk.\n");
    
    return 1;
}

string
resolv_composit()
{
    if (sitter == TP) 
	return "You are sitting in the chair at the desk.\n";
    else
	return COMPOSITE_LIVE(sitter)+ " is sitting in the chair at the desk.\n";
}

int
stand_up(string str)
{
    if ( !TP->query_prop("_is_sitting_down_") ) {
	notify_fail("You're not sitting down.\n");
	return 0;
    }
    
    write("You push the chair back and stand up.\n");
    remove_my_desc(this_object());
    sitter->remove_prop("_is_sitting_down_");
    say(QCTNAME(TP)+" pushes the chair back and stands up.\n");
    someone_is_sitting = 0;
    sitter = 0;
    return 1;
}

public void
leave_inv(object ob, object to)
{
    if (ob == sitter) {
	set_this_player(ob);
	stand_up(".");
    }
    ::leave_inv(ob, to);
}

object
query_sitter()
{
    return sitter;
}




