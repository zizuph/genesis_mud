inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/wild/pass/drow/guild/default.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
set_short("The private hall of House Claddath");
set_long("The private hall of House Claddath.\n"+
      "This darkened area is lit by the eerie glow of lit braziers, which cast a "+
      "sickly green aura over the room. The rectangular-shaped hall itself is, "+
      "besides the braziers, filled with a single glowing pyramid, suspended "+
      "at the exact center of the room.\n"+
      "A black archway leads to the west.\n");
   add_item(({"private hall","hall","rectangular-shaped hall","darkened area","area"}),
      "A dim and sinister-appearing place, a veritable breeding ground for vileness.\n");
   add_item(({"lit braziers","braziers","lit brazier","brazier"}),
      "The obsidian stands are spaced around the entire perimeter of the room, "+
      "an eerie green glow emanating from them.\n");
   add_item(({"single glowing pyramid","single pyramid","glowing pyramid","pyramid"}),
      "An object whose sides measure approximately three feet, you note the "+
      "plaque on one side, upon which some writing has been placed.\n");
   add_item(({"black archway","archway"}),
      "It appears to lead out of this hall and into another chamber.\n");
   add_item("plaque","Several words have been written upon it.\n");
   add_cmd_item("plaque","read","Here you may join or leave the "+
      "eighth-ranked House of Undraeth, House Noquar.\n"+
      "To join our ranks, simply <enter> house.\n"+
      "To leave our ranks, simply <forsake> house.\n"+
      "NOTE: Traitors to House Noquar are treated accordingly...\n");
   add_exit(CPASS(drow/house8/mm_chamber),"west","@@msg",-1,-1);
   set_noshow_obvious(1);
   reset_room();
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h8_golem));
      ob1 -> move_living("X",TO);
   }
}
void
init()
{
   ::init();
   AA(join,enter);
   AA(leave,forsake);
}

join(str)
{
   object insignia;
   int i;
insignia = present("_h7_insignia", TP);
   
   if(str == "house")
      {
      
      if(TP->query_race_name() != "elf")
         {
         NF("Only elves may join House Noquar!\n");
         return 0;
      }
      
      if(!TP->query_guild_member("Drow race guild"))
         {
         NF("Only Drow may join House Noquar!\n");
         return 0;
      }
      if(insignia)
         {
NF("You are already a member of House Claddath.\n");
         return 0;
      }
if(TP->query_base_stat(SS_RACE) < 20)
{
NF("You are not highly-ranked enough as a Drow to join House Claddath!\n");
return 0;
}
write("You are now a member of House Claddath.\n");
      
log_file("house7",TP->query_real_name()+" joined "+
         extract(ctime(time()),4,15)+".\n");
      
      if(!insignia)
         {
insignia = clone_object(CPASS(drow/guild/h7_i));
         insignia -> move(TP);
write("You receive the house insignia of Claddath.\n");
say(QCTNAME(TP) + " enters the ranks of House Claddath!\n");
      }
      return 1;
   }
   return 0;
}

leave(str)
{
   object insignia;
   int result;
   insignia = present("_h8_insignia",TP);
   
   if(str != "house")
      {
      write("What do you wish to forsake?\n");
      return 1;
   }
   if(!insignia)
      {
      write("You are not a member of House Noquar!\n");
      return 1;
   }
   
   write("You are no longer a member of House Noquar!\n");
   if(insignia)
      {
      insignia->remove_object();
      write("Your insignia dissolves in your hands.\n");
      say(QCTNAME(TP) + " leaves the ranks of House Noquar!\n");
      log_file("house8",TP->query_real_name()+" left   "+
         extract(ctime(time()),4,15)+".\n");
   }
   write("You feel an impending sense of doom...\n");
   /* Drow that leave are attacked by house guardians */
   return 1;
}
msg()
{
   write("You step into the black archway...\n");
   say(QCTNAME(TP) + " steps into the black archway...\n");
   return 0;
}
