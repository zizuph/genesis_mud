inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */

object ob1;
int alarmid;

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("Within a cave-house in the dwarven city of Underhome");
   set_long("You find yourself inside a small cave that "+
      "is lighted up from the hearth in the corner. The "+
      "warmth makes you feel doucy. Along the walls "+
      "you see one bed, a small table and a wooden chair. "+
      "All of it looks fairly well used.\n");
   add_item("hearth","It is an open fireplace in the corner, "+
      "that radiates a doucy heat and a red, weak light.\n");
   add_item(({"bed","chair","table"}),"They are all "+
      "made of wood, and looks fairly well used.\n");
   
   add_exit(CPASS(dwarf/houses/h3),"east",0,-1,-1);
   set_alarm(2.0,0.0,"reset_room");
   
}

reset_room()
{
   if(!objectp(ob1))
      {
      ob1=clone_object(CPASS(dwarf/npc/priest));
      ob1->arm_me();
      ob1->move_living("M",TO);
      tell_room(TO,"A deep dwarf stands up from the chair as you arrive.\n");
   }
}


tell_watcher(string str, object enemy)
{
   object me,*ob;
   int i;
   
   me = present("xarox");
   ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
   ob -= ({ enemy });
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->query_see_blood())
      ob[i]->catch_msg(str);
}

ask_attack()
{
   alarmid=set_alarm(5.0,20.0,"god_attack");
   return;
}


god_attack()
{
   
   int attacktype, i, penet;
   mixed* hitresult;
   string how;
   object me, *ob, *enemies;
   me = present("xarox");
   if(!me)
      {
      remove_alarm(alarmid);
      set_alarm(4.0,0.0,"stop_god");
      return;
   }
   
   attacktype = random(15);
   if(attacktype >2)
      {
      
      ob = FILTER_LIVE(all_inventory(TO)) - ({ me });
      enemies=me->query_enemy(-1);
      if(!member_array(enemies,ob))
         {
         remove_alarm(alarmid);
         set_alarm(4.0,0.0,"stop_god");
         return;
      }
      
      for (i = 0; i < sizeof(ob); i++)
      {
         penet = 500 + random(500);
         penet -= penet * ob[i]->query_magic_res(MAGIC_I_RES_FIRE) / 50;
         hitresult = ob[i]->hit_me(penet, MAGIC_DT, me, -1);
         
         how = "not harmed";
         if (hitresult[0] > 0)                  
            how == "barely burned";
         if (hitresult[0] > 10)
            how = "slightly burned";
         if (hitresult[0] > 20)
            how = "burned quite badly";
         if (hitresult[0] > 40)
            how = "burned very badly";
         if (hitresult[0] > 60)
            how = "utterly devastated";
         
         tell_room(TO,"An intense heat roams around in the room, "+
            "devouring everything in its way.\n");
         ob[i]->catch_msg("You feel "+ how +" from the devouring "+
            "heat!\n");
         tell_watcher(QCTNAME(ob[i]) + " looks "+ how+
            " of the intense heat.\n", ob[i]);
         
         if (ob[i]->query_hp() <= 0)
            ob[i]->do_die(me);
      }
      return;
   }
   
   tell_room(TO,"The priest raises his hands in the air and prays aloud.\n");
   tell_room(TO,"Red flickering flames envelopes him, but "+
      "he seems to draw power from it rather than getting burned!\n");
   me->heal_hp(500);
   return;
}

stop_god()
{
   tell_room(TO,"The heat diminishes slowly, until only the smell of burned "+
      "meat is left in the room as a reminder of the "+
      "havock you survived.\n");
   return;
}
