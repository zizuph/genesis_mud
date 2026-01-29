inherit "/std/room";

#include "default.h"
#include "/d/Emerald/defs.h"
#include <macros.h>

int do_offer(string str);
void appar_whisper(mixed args);

void
create_room()
{
   set_short("Temple precinct");
   set_long("You are standing in the magnificent Temple of Luiniris, the " +
            "God of War. The columns are huge and imposing on the nave, " +
            "and the altar is made from black flecked red marble.\n");

   add_exit(THIS_DIR + "t1", "west");
   
   add_item("altar","The altar is large and hewn from black flecked red "+
      "marble. Perhaps you could offer something here?\n");
   add_item(({"column","columns"}), "The columns are wide and smooth, their "+
      "width imposing onto the nave.\n");
   add_item("nave","You are standing in the nave.\n");
}

void
init()
{
   ::init();
   add_action(do_offer, "offer");
}

int
do_offer(string str)
{
   object tooth;
   
   tooth = present("_telberin_quest_tooth_", TP);
   
   NF("Offer what?\n");
   if(!tooth)
      return 0;
   NF("You offer the " + str + " but nothing happens. You take it back.\n");
   if (str != "tooth")
   {
      write("You offer " + str + " to the Gods but nothing happens.\n");
      return 1;
   }
   else
      if((str == "tooth") && (tooth))
      {
      write("You place the tooth on the altar, and there is a "+
         "flash of light. The tooth has disappeared.\n");
      tell_room(TO, capitalize(TP->query_met_name()) + " places a tooth on " +
         "the altar and there is a flash of light. The tooth " +
                "disappears.\n", TP);
      TO->start_whisper(this_player());
      tell_room(TO, "An apparition appears and murmurs something to "+
         QTNAME(this_player())+".\n", TP);
      tooth->remove_object();
      return 1;
   }
}

void
start_whisper(object ob)
{
   if(ob)
      if(objectp(ob))
      if(present(ob, this_object()))
          set_alarm(3.0, 0.0, &appar_whisper(({ ob, 1 })));
}

void
appar_whisper(mixed args)
{
   object ob;
   int time;
   
   if (sizeof(args) != 2)
      return;
   ob = args[0];
   time = args[1];
   if (!ob || !present(ob, this_object()))
      return;
   
   switch(time)
   {
      case 1:
      ob->catch_msg("An apparition appears and says: Only in the "+
         "heart of stone,\n");
      break;
      
      case 2:
      ob->catch_msg("The apparition says: Will the secrets of past ages.\n");
      break;
      
      case 3:
      ob->catch_msg("The apparition says: Be revealed to those,\n");
      break;
      
      case 4:
      ob->catch_msg("The apparition says: Who are humble.\n");
      break;
      
      case 5:
      ob->catch_msg("The apparition disappears.\n");
      break;
      
      default:
      return;
   }
   set_alarm(3.0, 0.0, &appar_whisper(({ ob, time+1})));
}
