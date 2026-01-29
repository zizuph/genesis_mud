inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/filter_funs.h"

object sitter;
   

static int picture_status;
#define MOVED 0
#define INPLACE 1

string longtxt;
string holetxt;
  
void reset_room();
 
void create_room()
{
    set_short("The bed room");
    set_long ("@@long_func");

    add_item("bed","An old and well used bed. On the side you "
            +"can see a small button.\n");

                add_item("hole","@@exa_hole");
    add_item("button","A small grey button. You might be able to press it.\n");
    add_item("painting","The painting looks almost worthless "
            +"and no shopkeeper would buy that piece of art.\n");

    add_exit(EDORAS_DIR + "rooms/uphall", "west" , "@@leave_room" , 1);
  
   reset_room();
 
    add_prop(ROOM_I_INSIDE,1);

}

  
init()
{
    ::init();
    add_action("c_press","press");
    add_action("sit_on_bed","sit");
    add_action("stand_up","stand");
    add_action("move_painting","push");
}

int
move_painting(string arg)
{
        if (arg != "painting")
        {
        NFN0("Push what?");
        }
        else
	if (arg == "painting")
	{
		if (picture_status == MOVED)
		{
		write("You move the painting aside, and reveal a hole.\n");
		say(QCTNAME(TP) + " pulls the painting aside, and reveals a hole.\n");
		picture_status = INPLACE;
		return 1;
		}
		else /* !picture status = MOVED  */
		{
		write("But the painting is already pulled aside.\n");
		return 1;
		}
	}
	else
	return 0;
}

mixed
sit_on_bed(string arg)
{
	if (arg == "in bed" ||
	    arg == "on bed")
	{
		if (sitter == 0)
		{
		write("You sit down on the bed.\n");
		say(QCTNAME(TP) + " sits down on the bed.\n");
           sitter = this_player();
		return 1;
		}
		else if (sitter == this_player()) /* !sit status = SIT  */
		{
		write("But you are already sitting on the bed.\n");
		return 1;
		}
          else
          {
          write("The bed is already occupied!\n");
          return 1;
          }
	}
	else
	return 0;
}

mixed
stand_up(string arg)
{
   if (!arg || arg == "up")
	{
		if (sitter == this_player())
		{
		write("You stand up from the bed.\n");
		say(QCTNAME(TP) + " stands up on the floor.\n");
           sitter = 0;
		return 1;
		}
		else /* !sit status = STAND  */
		{
		write("But you are already standing on the floor.\n");
		return 1;
		}
	}
	else
	return 0;
}

mixed
c_press(string arg)
{
	if (arg == "button")
	{
          if (picture_status != INPLACE ||
          sitter == 0)
          {
          write("Nothing happens!\n");
          say(QCTNAME(TP) + " presses the button, but nothing " +
                            "seems to happen.\n");
          return 1;
          }
          if (sitter == this_player())
		{
		write("The bed yanks up and throws you with an " +
                      "incredible force into the hole.\n");
		say(QCTNAME(TP) + " is thrown into the hole by the " +
                   "catapulting bed, and the picure swings back over " +
                   "the hole, so nothing can be seen from it anymore. ");
                TP->move_living("M",EDORAS_DIR + "rooms/secret",1,0);
        tell_room(environment(sitter),(QCTNAME(TP) + " arrives.",sitter));
		picture_status = MOVED;
                sitter = 0;
		return 1;
		}
		else 
		{
		TP->catch_msg("The bed yanks up and throws " + QCTNAME(sitter) +
                      " with an incredible force into the hole. " +
    "The bed falls down with a bang, and the painting swings back " +
   "to its place.\n");
		say("You are thrown into the hole by the catapulting bed!");
              sitter->move_living("M",EDORAS_DIR + "rooms/secret",1,0);
		picture_status = MOVED;
                sitter = 0;
		return 1;

		}
	}
	else
	return 0;
}


long_func()
{
  longtxt = "In this bed room there is not much to see. " +
	    "An old bed and a crappy painting on the wall. " +
	    "The best thing that can be said about it, is " +
	    "that its different from all the family portraits " +
     "on the other walls. ";
  if (picture_status == INPLACE) 
   {
      longtxt = longtxt + "The painting is hanging loose, and you can see a hole behind it.\n";
  return break_string(longtxt,70);
   }
   else 
   {
      longtxt = longtxt + "\n";
  return break_string(longtxt,70);
   }
}

exa_hole()
{
  if (picture_status == INPLACE) 
  {
       holetxt = "The hole is black. From down here you can only see a faint light from it. Its even to hard to reach or enter the hole from down here.\n";
            return break_string(holetxt,70);
  }
  else
  {
       holetxt = "What hole??\n";
       return break_string(holetxt,70);
   }

}
  
leave_room()
{
   if (sitter == this_player()) {
   sitter = 0;
   return 0;
   }
   else
   return 0;
}
  
void
reset_room()
{
if (!sizeof(FILTER_PLAYERS(all_inventory(TO)))) {
picture_status = MOVED;
   }
   else
   return;
}
