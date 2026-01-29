/* 
   ladder.c
   --------

   Coded ........: 95/01/15
   By ...........: Jeremiah

   Latest update : 95/06/02
   By ...........: Jeremiah


   This is the ladder that has to be used in getting the rag doll from
   the gully dwarf in pax tharkas - low level. The player has to climb
   this ladder to show the gully dwarf how to use it. 

*/

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

public int no_command();

string player_on_ladder;
int    ladder_against_wall = 0;  /* 0 : ladder NOT against wall */

void
create_object()
{
   set_name(({"ladder", "short ladder"}));
   set_short("@@lad_descr");
   set_long("A short ladder made of wood. The ladder is about 5 feet " +
            "long, and would probably be useful if set against " +
            "something solid.\n");
   
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,6000);
}


string
lad_descr()
{
   string ret_str = "ladder";
   
   if (ladder_against_wall)
      ret_str += ", standing against the wall";

   return ret_str;
}


void
init()
{
   ::init();
   add_action("place_ladder", "put");
   add_action("place_ladder", "set");
   add_action("place_ladder", "place");
   add_action("climb_ladder", "climb");
   if (player_on_ladder == TP->query_name())
      add_action("do_all_commands", "", 1);
}


public int
do_all_commands(string str)
{
   string verb;
   string *not_allowed;

   not_allowed = ({"n","north","s","south","w","west","e","east","nw",
                   "northwest","sw","southwest","se","southeast",
                   "northeast","ne","u","up","d","down","teleport",
                   "goto","home"});

   verb = query_verb();
   if (member_array(verb, not_allowed) == -1)
      return 0;
   else 
      return no_command();

   return 1;
}

no_command()
{
   write("You can't do that while standing on the ladder. Climb down " +
         "first.\n");
   return 1;
}

int
place_ladder(string str)
{
   string *s, verb = query_verb(),
          *room;

   if (!str)
   {
      NF(C(verb) + " what?\n");
      return 0;
   }

   if (str == "ladder" || str == "the ladder")
      /* Only ladder - "place ladder" */
   {
      NF(C(verb) + " the ladder where?\n");
      return 0;
   }

   sscanf(str, "the %s", str);  /* Remove 'the' from the words */
   s = explode(str, " ");
   if (s[0] != "ladder")
      return 0; /* No NF set */

   NF(C(verb) + " the ladder where?\n");
   if (sizeof(s) < 2)
      return 0;
   if (s[1] != "against" || sizeof(s) < 3)
   {
      NF("Maybe you should "+verb+" the ladder against something?\n");
      return 0;
   }

   if (s[2] == "nothing")
   {
      NF("Now, that would be clever!\n");
      return 0;
   }
   room = explode(E(TP)->long(), " ");
   if (member_array(s[2], room) == -1 && member_array(s[2]+".", room) == -1)
   {
      NF("There is no "+s[2]+" here for you to "+verb+" the ladder against!\n");
      return 0;
   }

   if (s[2] != "wall")
   {
      NF("That doesn't look solid enough!\n");
      return 0;
   }         

     /* This if() should be obsolete now */
   if (str == "ladder against wall")
   {      
      if(ladder_against_wall)
      {
         write("The ladder is already standing against the wall.\n"); 
         return 1;
      }
      else
      {
         write("You "+verb+" the ladder against the wall.\n");
         say(QCTNAME(TP) + " "+verb+"s the ladder against the wall.\n");
         TO->move(E(TP),1);
         ladder_against_wall = 1;
         return 1;
      }
   }
   else
   {
      NF("You don't seem to be able to do that!\n");
      return 0;
   }
}
            

int
climb_up()
{
   if (player_on_ladder)
   {
      if (player_on_ladder == TP->query_name())
         write("You are already standing on the ladder.\n");

      return 1;
   }

   if (!ladder_against_wall)
   {
      write("You can't climb the ladder like this.\n");
      return 1;
   }
   else
   {
      player_on_ladder = TP->query_name();   
      change_prop(OBJ_I_NO_GET,1);
      change_prop(OBJ_I_NO_DROP,1);
      TP->add_prop(LIVE_S_EXTRA_SHORT," standing on a " +
                                      "ladder");
      write("You climb the ladder.\n");
      say(QCTNAME(TP) + " climbs the ladder.\n");
      TO->move(TP,1);
      ladder_against_wall = 1;
      add_prop(OBJ_I_INVIS,1);
      return 1;
   }         
}


int
climb_down()
{
   if (player_on_ladder == TP->query_name())
   {
      player_on_ladder = 0;
      change_prop(OBJ_I_NO_GET,0);
      change_prop(OBJ_I_INVIS,0);
      change_prop(OBJ_I_NO_DROP,0);
      TO->move(E(TP),1);
      ladder_against_wall = 1;
      TP->change_prop(LIVE_S_EXTRA_SHORT,"");
      write("You climb down from the ladder.\n");
      say(QCTNAME(TP) + " climbs down from the ladder.\n");
   }
   else
      write("You are not standing on the ladder.\n");

   return 1;
}


int
climb_ladder(string str)
{
   if (str == "ladder")
      return climb_up();

   if (str == "down")
      return climb_down();

   NF("Climb what?\n");
   return 0;
}


void
enter_env(object dest, object old)
{
   ::enter_env(dest,old);
   ladder_against_wall = 0;
}
