inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
void reset_room();
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The central hall of House Claddath");
   set_long("The central hall of House Claddath.\n"+
      "This long, rectangular-shaped hall reaches out to the north and "+
      "south, dominated by the single, blood-red column of light that "+
      "connects both floor and ceiling in the center of the hall. A "+
      "pair of darkened archways lead to the north and south. "+
      "Decorations wrought of mystical faerie fire lie upon the walls, "+
      "while various busts and statues line the western and eastern walls.\n");
   add_item(({"central hall","hall"}),
      "A long, rectangular-shaped hall with its greatest length running to "+
      "the north and south.\n");
   add_item(({"single column","single light","blood-red column","column","light"}),
      "A five-foot wide beam of scarlet light that runs from the floor of "+
      "this hall to the ceiling.\n");
   add_item(({"floor","ceiling","walls","wall"}),
      "It has been constructed out of a stone that is as dark as obsidian, "+
      "yet of greater quality.\n");
   add_item(({"pair","darkened archways","archways","archway"}),
      "The dark stone structures appear to lead to other areas of the house "+
      "compound.\n");
   add_item(({"decorations","decoration","mystical faerie fire","mystical fire","faerie fire","fire"}),
      "Images of drow battling dwarves and gnomes in gruesome detail are "+
      "shown above, while a figure from above, Lolth herself, watches in savage "+
      "and malicious glee.\n");
   add_item(({"busts","bust"}),
      "They portray drow of incredible beauty...power...fanaticism. Another "+
      "fact of import you notice is that they are all females.\n");
   add_item(({"statues","statue"}),
      "Many figures dressed in robes and cloaks, apparently priestesses of "+
      "the fey goddess Lolth, have been wonderfully carved and placed along "+
      "the length of this hall, seeming like frozen guardians of "+
      "House Claddath.\n");
   add_exit(CPASS(drow/house7/entrance),"north",0,-1,-1);
   add_exit(CPASS(drow/house7/slaves),"down","@@msg",-1,-1);
   add_exit(CPASS(drow/house7/chapel),"south","@@check",-1,-1);
   add_exit(CPASS(drow/house7/warriors),"up",0,-1,-1);
   set_noshow_obvious(1);
   reset_room();
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h7_golem));
      ob1 -> move_living("X",TO);
   }
}
check()
{
   object *ob;
   int pres,i;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   for(i = 0; i < sizeof(ob); i++)
   {
      if(ob[i]->query_name() == "Golem")
         {
         pres = 1;
       }
   }
   if(pres == 1)
      {
      write("The iron statue suddenly blocks your way!\n");
      say(QCTNAME(TP) + " tries to go south but is suddenly stopped by the "+
         "iron statue!\n");
   }
   return pres;
}
msg()
{
   write("You step into the red light, and feel yourself grow lighter as "+
      "you are transported by the column.\n");
   say(QCTNAME(TP) + " steps into the red light, and seems to grow lighter "+
      "as " + TP->query_pronoun() + " is transported by the column.\n");
   return 0;
}
