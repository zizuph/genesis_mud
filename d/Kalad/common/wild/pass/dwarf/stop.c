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
      if (ob[i]->query_name() == "Statue")
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
         if (ob[i]->query_prop("korat_quest_thing")==1)
            {
            ok = 1;
           }
       }
      if (ok)
         {
         TP->catch_msg("The glow from the ... ");
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


