inherit "/std/object";
#include "/d/Kalad/defs.h"

#define CHAIR_O_OCCUPIED "_chair_i_occupied"
#define PLAYER_I_STANDS  "_player_i_stands"

public int no_command();

create_object()
{
   add_prop(OBJ_I_WEIGHT,100000);
   add_prop(OBJ_I_VOLUME,50000);
   set_name(({"throne","gigantic"}));
   set_short("gigantic throne lined with cushions");
   set_long("Sitting in the far end of the room is a gigantic throne, "+
      "cushioned with the soothing texture of silk pillows. At the top of "+
      "the throne is a carving of a golden coin with rays of light radiating "+
      "from it, the symbol of the Trading Company.\n");
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_NO_GET,1);
}

init()
{
   add_action("sit_down","sit");
   add_action("stand_up","stand");
   add_action("stand_up","leave");
   add_action("stand_up","climp");
   add_action("stand_up","step");
   if (query_prop(CHAIR_O_OCCUPIED)==this_player())
      add_action("do_all_commands", "", 1);    
   ::init();
}

public int
do_all_commands(string str)
{
   string verb;
   string *not_allowed;
   
   not_allowed=({"n","north","s","south","w","west","e","east","nw",
         "northwest","sw","southwest","se","southeast",
         "northeast","ne","teleport","u","up","d","down",
         "goto","home"});
   not_allowed += environment(TP)->query_exit_cmds();
   
   verb = query_verb();
   
   if (member_array(verb,not_allowed)==-1)
      return 0;
   else 
      return no_command();
   
   return 1; /* should never occur */
}


no_command()
{
   write("You have to stand up first to do that.\n");
   return 1;
}


sit_down(string str)
{
   object who,*list;
   string check;
   
   if (!str)
      return 0;
   
   if (sscanf(str,"down on %s",check)==1)
      str = check;
   
   
   if (sscanf(str,"on %s",check)==1)
      str = check;
   
   list=FIND_STR_IN_OBJECT(str,environment(this_player()));
   notify_fail("Can't find any "+str+" here.\n");
   if (member_array(this_object(),list)==-1)
      return 0;
   if ((who = query_prop(CHAIR_O_OCCUPIED)))
      {
      write(QCTNAME(who)+" is sitting on the chair.\n");
      return 1;
   }
   change_prop(CHAIR_O_OCCUPIED,this_player());
   change_prop(OBJ_I_NO_GET,1);
   change_prop(OBJ_I_NO_DROP,1);
   this_player()->add_prop(LIVE_S_EXTRA_SHORT," sitting on a throne");
   write("You settle into the throne. It is without a doubt the most "+
      "comfortable seat you have ever rested in. You feel as if everything "+
      "in the world is not worth your concern, now that you are upon this "+
      "grand throne.\n");
   say(QCTNAME(this_player())+" sits down on the throne.\n");
   this_object()->move(this_player(),1);
   add_prop(OBJ_I_INVIS,1);
   return 1;
}

stand_chair(string str)
{
   object who,*list;
   
   list=FIND_STR_IN_OBJECT(str,environment(this_player()));
   notify_fail("Can't find any "+str+" here.\n");
   if (member_array(this_object(),list)==-1)
      return 0;
   if ((who = query_prop(CHAIR_O_OCCUPIED)) && who!=this_player())
      {
      write(QCTNAME(who)+" is sitting on the throne.\n");
      return 1;
   }   
   change_prop(CHAIR_O_OCCUPIED,this_player());
   change_prop(OBJ_I_NO_GET,1);
   this_player()->change_prop(PLAYER_I_STANDS,1);
   this_player()->change_prop(LIVE_S_EXTRA_SHORT," standing on a throne");
   write("You stand on the throne.\n");
   say(QCTNAME(this_player())+" stands on the throne.\n");
   this_object()->move(this_player(),1);
   add_prop(OBJ_I_INVIS,1);
   return 1;
}

stand_up(string str)
{
   object who,*list;
   string check;
   
   if (str && (sscanf(str,"on %s",check)==1 || (check=str)!="up"))
      {
      if (stand_chair(check))
         return 1;
      return 0;
   }
   if (str && str!="up")
      return 0;
   
   notify_fail("You are not sitting on it.\n");
   if (query_prop(CHAIR_O_OCCUPIED)!=this_player())
      return 0;
   change_prop(CHAIR_O_OCCUPIED,0);
   change_prop(OBJ_I_NO_GET,0);
   change_prop(OBJ_I_INVIS,0);
   change_prop(OBJ_I_NO_DROP,0);
   this_player()->change_prop(PLAYER_I_STANDS,0);
   this_object()->move(environment(this_player()),1);
   this_player()->change_prop(LIVE_S_EXTRA_SHORT,"");
   write("You reluctantly stand up from the throne, stretching.\n");
   say(QCTNAME(this_player())+" stands up from the throne.\n");
   return 1;
}

