/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#include <macros.h>
#define THIEF_I_HAS_FOUND_WHEEL   "_thief_i_has_found_wheel"
#define HOW_MANY                  3

/*Prototype*/
varargs string turn_room_left(int silent = 0);
varargs string turn_room_right(int silent = 0);


void
reset_thief_room()
{
    string str;
    if (random(4))
      return;

    str = ("A small gnome arrives.\n" +
	   "The small gnome rummages about with a crate.\n");
    tell_room(TO,({ str, str, ""}));
    if (random(2))
      turn_room_left(1);
    else
      turn_room_right(1);
    str = ("The small gnome disappears between the crates.\n");
    tell_room(TO,({ str, str, ""}));
}

void
create_thief_room()
{
    set_short("In a cavern.\nThere is one obvious exit: northeast");
    set_long("This is a cavern. It is still rather dark and gloomy " +
	     "here. Apart from that, the stones are very cold and it is quite " +
	     "damp in here. There are a few crates piled up on the south side " +
	     "of the room.\nThere is one obvious exit: northeast.\n");
    
    set_noshow_obvious(1);
    add_exit(DEWAR + "r1", "south","@@only_if_opened");
    add_exit(CAVERN + "pal2","northeast");
    
    add_cmd_parse("[the] 'wheel' [to] [the] 'right'","turn",
		  "@@turn_room_right@@");
    add_cmd_parse("[the] 'wheel' [to] [the] 'left'","turn",
		  "@@turn_room_left@@");
    add_cmd_parse("[the] 'wheel'","turn",
		  "@@turn_wheel@@");
    
    DARK;
    
    add_item(({"pole","hole"}),
	     "The pole in the middle of the room disappears into a hole in the " +
	     "ceiling. The pole is very slippery and you figure you won't have " +
	     "a chance to climb up.\n");
    add_item(({"wall","walls","rock","stones","stone"}),
	     "Since this is a cavern, it is normal that the walls are blank " +
	     "rock.\n");
    add_item(({"crate","crates"}),
	     "You can't see anything special about the crates, they're closed " +
	     "and stacked on each other.\n");
    add_search(({"crate","crates"}),10,"search_crates",1);
    add_cmd_item(({"crate","crates"}),"open",
		 "@@opening_crates");
    add_item(({"wheel"}),"@@examine_wheel");
}

string
turn_wheel()
{
  if (TP->query_prop(THIEF_I_HAS_FOUND_WHEEL) == HOW_MANY)
    return "In which direction do you want to turn the wheel?\n";
  NF("What?\n");
  return 0;
}


string
examine_wheel()
{
  if (TP->query_prop(THIEF_I_HAS_FOUND_WHEEL) == HOW_MANY)
    return "It's a wheel about one foot in diameter made of iron.\n";
  return "You find no wheel.\n";
}


string
opening_crates()
{
  int times = TP->query_prop(THIEF_I_HAS_FOUND_WHEEL);
  if (CAN_SEE_IN_ROOM(TP))
    {
	if (times >= HOW_MANY)
	  {
	      TP->add_prop(THIEF_I_HAS_FOUND_WHEEL, HOW_MANY);
	      return ("You finally get around to open the crates. Unfortunately, " +
		      "there is only dust in each.\n");
	  }
	else if (times >= (HOW_MANY - 1))
	  {
	      TP->add_prop(THIEF_I_HAS_FOUND_WHEEL, HOW_MANY);
	      write("You try to open one of the crates as your eyes catch something behind them, " +
		    "on the wall. It's an iron wheel.\n");
	      return "";
	  }
	else
	  {
	      TP->add_prop(THIEF_I_HAS_FOUND_WHEEL, times + 1);
	      write("As you rummage about with a crate, and trying to open it, you " +
		    "notice something dark at the wall " +
		    "behind the crate." + ((times > 0) ? " Again? Hmmm." : "") + 
		    " You find a hidden entrance behind the crates leading " +
		    "south and down into utter darkness.\n");
	      return "";
	  }
    }
  return 0;
}

string
search_crates(object searcher, string what)
{
    int times = TP->query_prop(THIEF_I_HAS_FOUND_WHEEL);
    if (CAN_SEE_IN_ROOM(TP))
      {
	  if (times >= HOW_MANY)
	    {
		TP->add_prop(THIEF_I_HAS_FOUND_WHEEL, HOW_MANY);
		return ("You search the crates and open them. Unfortunately, " +
			"there is only dust in each.\n");
	    }
	  else if (times >= (HOW_MANY - 1))
	    {
		TP->add_prop(THIEF_I_HAS_FOUND_WHEEL, HOW_MANY);
		return ("You search the crates as your eyes catch something " +
			"behind them, on the wall. It's an iron wheel.\n");
	    }
	  else
	    {
		TP->add_prop(THIEF_I_HAS_FOUND_WHEEL, times + 1);
		return ("As you rummage about with a crate, you notice something dark at " +
			"the wall behind the crate." + ((times > 0) ? " Again? Hmmm." : "") + 
			" You find a hidden entrance behind the crates leading " +
			"south and down into utter darkness.\n");
	}
    }
  return 0;
}
 
varargs string
turn_room_left(int silent = 0)
{
  if (silent || TP->query_prop(THIEF_I_HAS_FOUND_WHEEL) == HOW_MANY)
    {
      (TURNB)->turn_me_left(silent);
      return "";
    }
  NF("What?\n");
  return 0;
}


varargs string
turn_room_right(int silent = 0)
{
  if (silent || TP->query_prop(THIEF_I_HAS_FOUND_WHEEL) == HOW_MANY)
    {
      (TURNB)->turn_me_right(silent);
      return "";
    }
  NF("What?\n");
  return 0;
}


only_if_opened()
{
  if (TP->query_prop(THIEF_I_HAS_FOUND_WHEEL))
    return 0;
  write("There is no obvious exit south.\n");
  return 1;
}
