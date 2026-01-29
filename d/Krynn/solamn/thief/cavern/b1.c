/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#include <macros.h>
#define THIS_ROOMS_VALUE   2

object *spider = ({ });
object sp;

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a cavern that looks like it is almost natural. " +
	     "Just here and there, you see traces of manual work, " +
	     "enlarging the cavern and evening out the floor. On " +
	     "the east wall, someone has painted a large picture " +
	     "of a spider.\n");
    
    add_exit(CAVERN + "b4","south");
    
    add_cmd_item(({"picture","spider"}),
		 ({"grab","take","pick","get"}),"@@solved_this");
    
    DARK;

    add_item(({"spider","picture"}),
	     "This spider looks almost alive, it seems to be sitting on the " +
	     "wall, glaring at you. It is quite large and black and has eight " +
	     "hairy legs.\n");
    add_search(({"spider","picture"}),-4,"search_solved_this",1);
}


string
search_solved_this(object searcher, string what)
{
    object vic;
    if (!CAN_SEE_IN_ROOM(searcher))
      {
	  NF("It is too dark to get things.\n");
	  return 0;
      }
    if (member_array(searcher,spider) != -1)
      {
	  if (!sizeof(searcher->query_team_others()))
	    searcher->add_prop(THIEF_I_CAN_ENTER, 
			 searcher->query_prop(THIEF_I_CAN_ENTER) | THIS_ROOMS_VALUE);
	  return "You try to take the spider from the wall, and as you have " +
	    "pulled the picture a few inches away from the wall, you hear a " +
	    "soft click.\nThe picture is torn out of your hand and snaps " +
	    "back to the wall!\n";
      }
    else if (!sp)
      {
	  searcher->catch_msg("As you try to take the picture from the wall, a " +
			      "dark shape bulges out of the picture and starts to " +
			      "crawl towards you!\n" +
			      "An image of the spider has turned alive!\n");
	  SAYBB(" messes around with the picture of the spider.");
	  vic = searcher;
	  sp = clone_object(LIV + "spider");
	  sp->move(TO);
	  
	  tell_room(TO,"The " + sp->short() + " attacks " + QTNAME(vic) + ".\n",vic);
	  vic->catch_msg("The " + sp->short() + " attacks you!\n");
	  sp->attack_object(vic);
	  return "\n";
      }
    else if ((searcher->query_attack())->id("spider"))
      return "The spider prevents you from reaching the picture.\n";
    else
      return "You try to take the picture of the spider from the wall, but it " +
	"must be glued to the wall.\n";
}

string
solved_this()
{
    return search_solved_this(TP,"dummy");
}

void
add_player_killed_spider(object who)
{
    spider += ({ who });
}


void
reset_thief_room()
{
    if (!random(5))
      spider = ({ });
}
