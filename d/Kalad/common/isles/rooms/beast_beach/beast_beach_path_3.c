 /*****************************************************************************
*  /d/Kalad/common/isles/rooms/beast_beach/beast_beach_path_3.c
*
*  Room File: Beach area for the Isle of the Beast
*
*  Created June 2019, Greneth
*
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "../local.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit BEAST_BEACH_PATH_STD;

 /*****************************************************************************
*  Defines
 *****************************************************************************/
#define CREVICE_PROP "_found_beach_crevice_"
#define MIN_AWARENESS   30

 /*****************************************************************************
*  Function name: create_std_beach_path
*  Description  : Constructor for the room, modify this to change room.
 *****************************************************************************/
create_std_beach_path()
{   
   set_short("" + B_P + "");
   set_long("You are on a small path hidden inside the rising outcrop of "
   + "rocks. The mist drops down from the small crevice above partially "
   + "obstructing your view. Heading west will lead back to the beach "
   + "while that path continues to the east.\n");
    
   add_exit(BEAST_BEACH + "beast_beach_path_2","west");
   add_exit(BEAST_BEACH + "beast_beach_path_4","east");
	
    /*************************************************************************
   *  Sets the no exit message for unlisted directions
    *************************************************************************/
   set_no_exit_msg(get_all_no_exits(({"e","w"})),
   "You bump against the rock with your body but go nowhere.\n");

   add_prop(OBJ_S_SEARCH_FUN, "do_search");
   reset_room();
}

 /*****************************************************************************
* Function name: init
*
* Description: Adds the search action
 *****************************************************************************/
void
init()
{
   ::init();
	add_action("do_climb","climb");
	add_action("show_path","show");
}

 /*****************************************************************************
* Function name: do_search
*
* Description: Adds the prop
 *****************************************************************************/
mixed 
do_search(object searcher, string str)
{
   int awareness;

   if (!parse_command(str, ({}), "'crevice' [the] "))

      return 0;

   awareness = searcher->query_skill(SS_AWARENESS);
   if (awareness >= MIN_AWARENESS)
   {
      TP->add_prop(CREVICE_PROP,1);
      return "You spot a path to climb up into the crevice!";
   }

   return 0;
}

 /*****************************************************************************
*  Function name: do_climb
*  Description  : Lets the player climb to the upper beach
 *****************************************************************************/
int
do_climb(string str)
{
   notify_fail("What?\n");
   if (!strlen(str))
   {
      return 0;
   }
    
   if (!parse_command(str, TP, " [the] [into] [up] 'crevice' "))
   {
      return 0;
   }

   if (!TP->query_prop(CREVICE_PROP))
	{
		return 0;
	}
		
   if (TP->query_skill(SS_CLIMB) < 30)
   {
      write("You grab on to the sides and slowly attempt to pull yourself "
		+ "up but just don't seem to have the skill to do so.\n");
      return 1;
   }

   if (TP->query_skill(SS_ACROBAT) < 10)
   {
      write("You near the top but the rock is smooth and you can't grab on "
		+ "to anything. Noticing a ledge just out of reach you push off with "
		+ "both your hands and feet but miss the ledge and fall!\n");		
      tell_room(environment(TP), QCTNAME(TP) + " climbs up the crevice but "
      + "makes a mistake and falls all the way down!\n",TP);
		
      TP->heal_hp(-(TP->query_max_hp() * 15 / 100));
      return 1;
   }

    set_dircmd(str);    
    write("You climb your way up and squeeze beteween the crevice.\n");
    tell_room(environment(TP), QCTNAME(TP)+" climbs "+
        "up and squeezes between the crevice.\n",TP);
    TP->move_living("M", BEAST_BEACH+"beast_beach_crevice_1.c");
    tell_room(environment(TP), QCTNAME(TP) + " arrives, squeezing between "
        + "the small crevice below.\n",TP);
    return 1;
}

 /*****************************************************************************
*  Function name: do_show
*  Description  : Lets the player show the exit to the room
 *****************************************************************************/
int 
show_path(string arg)
{
   string path, who;
   object *in_room;
   int i;

   notify_fail("Show what to whom?\n");
   if(TP->query_prop(CREVICE_PROP))
   {
      if((sscanf(arg, "%s to %s", path, who)<1) || (path != "path"))
      {
         return 0;
      }
		
      if((who != "all") && (!present(who, TO)))
      {
         return 0;
      }
		
      if(who == "all")
      {
         in_room=FILTER_LIVE(all_inventory(TO));
         if(sizeof(in_room) == 1)
         {
            TP->catch_msg("But you are alone here!\n");
            return 1;
         }
			
         for (i = 0; i < sizeof(in_room); i++)
         in_room[i]->add_prop(CREVICE_PROP,1);
		
         TP->catch_msg("You show the way to climb up to everybody in the "
			+ "room.\n");
         say(QCTNAME(TP)+" shows you a way to climb up the crevice.\n");
			
         return 1;       
		}
		
      if(present(who, TO))
      {
         if(present(who, TO) == TP)
         {
            TP->catch_msg("It is pretty stupid showing it to yourself.\n");
            return 1;
         }
         present(who, TO)->add_prop(CREVICE_PROP,1);
         TP->catch_msg("You show a way to climb up the crevice to "
			+QCTNAME(present(who, TO))+".\n");
         present(who, TO)->catch_msg(QCTNAME(TP)+" shows you a way to climb "
			+ "up the crevice.\n");
			
         return 1;
      }
   }
   notify_fail("Show what?\n");
   return 0;
}