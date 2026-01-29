/* 
Citadel, hallway
Made by Korat 
Feb 14. 1995 
*/

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <filter_funs.h>
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
object ob6;
object ob7;




void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_M_NO_TELEPORT, 1);

   hear_bell = 2;
   set_short("Citadel, hallway");
   set_long("You walk along a hallway, where you see an office to the west "+
      "and an exit to the north. All around you "+
      "paintings, statues and other fanciful decorations are spread out, as like "+
      "the owner of this place were trying to "+
      "dazzle you with its magnificence.\n");
   
   add_item(({"painting","paintings","decoration","decorations","statues","statue"}),
      "They almost cramp the room up, stuffing the air with the value they "+
      "symbolizes.\n");
   
   add_exit(CENTRAL(citadel/cit11),"north","@@go_north@@",-1,-1);
   add_exit(CENTRAL(citadel/cit20),"west","@@check_pass@@",-1,-1);
   
   set_alarm(0.0,0.0,"reset_room");
}


void
reset_room()
{
   if (!objectp(ob1))
      {
      ob1 = clone_object("/d/Kalad/common/central/npc/cit_elite");
      ob1 -> arm_me();
      ob1 -> move_living("An elite guard enters the room.", this_object());
   }
   if (!objectp(ob2))
      {
      ob2 = clone_object("/d/Kalad/common/central/npc/cit_elite");
      ob2 -> arm_me();
      ob1 -> team_join(ob2);
      ob2 -> move_living("An elite guard enters the room.", this_object());
   }
   if (!objectp(ob3))
      {
      ob3 = clone_object("/d/Kalad/common/central/npc/cit_elite_b");
      ob3 -> arm_me();
      ob3 -> move_living("xxx",TO);
      ob1 -> team_join(ob3);
      ob3 -> command("w");
   }
   if(!objectp(ob4))
      {
      ob4 = clone_object("/d/Kalad/common/central/npc/cit_elite_b");
      ob4 -> arm_me();
      ob4 -> move_living("xxx",TO);
      ob1 -> team_join(ob4);
      ob4 -> command("w");
   }
   if (!objectp(ob5))
      {
      ob5 = clone_object("/d/Kalad/common/central/npc/cit_elite_b");
      ob5 -> arm_me();
      ob5 -> move_living("xxx",TO);
      ob1 -> team_join(ob5);
      ob5 -> command("w");
   }
   if (!objectp(ob6))
      {
      ob6 = clone_object("/d/Kalad/common/central/npc/cit_elite_offduty");
      ob6 -> arm_me();
      ob6 -> move_living("xxx",TO);
      ob1 -> team_join(ob6);
      ob6 -> command("w");
      ob6 -> command("s");
   }
   if (!objectp(ob7))
      {
      ob7 = clone_object("/d/Kalad/common/central/npc/cit_elite_offduty");
      ob7 -> arm_me();
      ob7 -> move_living("xxx",TO);
      ob1 -> team_join(ob7);
      ob7 -> command("w");
      ob7 -> command("s");
   }
}

go_north()
{
   write("You start to walk northwards, but soon the hallway turns to the east. "+
      "After a while you come to the curtain that you entered through. "+
      "You enter them again.\n");
   return 0;
}

check_pass()
{
   object *ob;
   int pres,i;
   int can_go;
   int ok;
   ob = FILTER_LIVE(all_inventory(this_room()));
   pres = 0;
   if (TP->query_npc()) return 0;
   for (i=0;i<sizeof(ob); i++)
   {
      if ((ob[i]->query_name() == "Guarda") ||
            (ob[i]->query_name() == "Guardb"))
      {
         pres = 1;
        }
   }
   if (pres==1)
      {
      ob = all_inventory(TP);
      ok = 0;
      for (i=0;i<sizeof(ob);i++)
      {
         if (ob[i]->query_prop("korat_lord_note")==1)
            {
            ok = 1;
           }
       }
      if (ok)
         {
         TP->catch_msg("You show the leave to the guards, and they let you pass.\n");
         say(QCTNAME(TP)+" shows a note to the guard, and he let "+
            TP->query_objective()+" pass.\n");
         can_go = 0;
       }
      else
         {
         if (ob1) ob1->command("emote puts a hand on your chest and "+
               "pushes you back.\n");
         if (ob2) ob2->command("emote blocks the door with his weapon.");
         can_go = 1;
         set_alarm(2.0,0.0,"give_warning",TP);
       }
   }
   else
      {
      can_go = 0;
   }
   return can_go;
}

give_warning(object who)
{
   if (who = present(who))
      {
      if (ob1) ob1->command("emote orders you to leave, pointing north "+
            "with his weapon.");
      if (ob2) ob2->command("emote lowers his weapon and gets ready to attack.");
      set_alarm(10.0,0.0,"attack_player",who);
   }
}

attack_player(object who)
{
   if (who = present(who))
      {
      if (ob1) ob1->command("stop searching");
      if (ob1) ob1->command("emote roars: Die then, filth!");
      if (ob1) ob1->command("kill "+who->query_real_name());
      if (ob1) ob1->command("stop searching");
      if (ob2) ob2->command("emote slashes his weapon forward, "+
            "while shouting aloud: Die, enemy of the Lord!");
      if (ob2) ob2->command("kill "+who->query_real_name());
   }
}
