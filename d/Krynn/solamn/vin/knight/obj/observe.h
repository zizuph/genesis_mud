
/* Ability for Level 6 Crown Knights and up (Including Rose and Sword)
* The command lets them observe another object and allows them to
* observe who that object's leader is with a percentage chance based
* on appraise enemy skill and wisdom stat. It has a 10 second resetting
* time to prevent the Knight from using it multiple times to negate the
* chance for error.
* Added 11/96 by Morrigan
*/

int
observe(string str)
{
   
   object *oblist, leader;
   int percentage, chance, appskill;
   string pos, pro;
   
   percentage = random(100) + 1;
   
   if (TP->query_knight_level() == 2 && TP->query_guild_name_lay() ==
         "Sentries of Solamnia")
   {
      write("Only full Knights may do this.\n");
      return 1;
   }
   
   if (TP->query_knight_level() < 3 || (TP->query_knight_level() == 3 &&
            TP->query_knight_sublevel() < 6 ))
   {
      write("You are not yet experienced enough in battle to be able to "+
         "observe someone.\n");
      return 1;
   }
   
   if (TP->query_stat(SS_WIS) < 50)
      {
      write("You lack the wisdom to be able to observe someone properly.\n");
      return 1;
   }
   
   if (TP->query_skill(100) < 25)
      {
      write("You lack the knowledge of military tactics necessary to "+
         "properly observe someone.\n");
      return 1;
   }
   
   if (!str)
      {
      write("Observe whom?\n");
      return 1;
   }
   
   oblist = parse_this(str, "[the] %l");
   oblist -= ({ this_player });
   
   if ((!strlen(str)) || (!sizeof(oblist)))
      {
      notify_fail("You don't see anyone like that here to observe.\n");
      return 0;
   }
   
   if (sizeof(oblist) > 1)
      {
      write("You cannot possibly observe more than one person at a time.\n");
      return 1;
   }
   
   if (TP->query_prop("_observe_resetting"))
      {
      write("Your mind is still strained from observing before.\n");
      return 1;
   }
   
   TP->add_prop("_observe_resetting", 1);
   set_alarm(10.0, 0.0, "reset_observe", TP);
   
   if (oblist[0]->query_team_others())
      {
      leader = oblist[0]->query_leader();
   }
   
   if (sizeof(oblist[0]->query_team()) > 0)
      {
      leader = oblist[0];
   }
   
   if (oblist[0]->query_gender() == 1)
      {
      pos = "her";
      pro = "she";
   }
   else
      {
      pos = "his";
      pro = "he";
   }
   
   appskill = TP->query_skill(100);
   if (appskill > 50)
      appskill = 50;
   
   chance = appskill + TP->query_stat(SS_WIS) / 2;
   if (chance > 99)
      chance = 99;
   
   if (chance < percentage)
      {
      actor("You observe", oblist," carefully, but see no sign of a leader "+
         "present.");
   }
   else if (!leader)
      {
      actor("You observe", oblist," carefully, but see no sign of a leader "+
         "present.");
   }
   else if (!present(leader, E(TP)))
      {
      actor("You observe", oblist," carefully, but see no sign of a leader "+
         "present.");
   }
   else if (leader == oblist[0])
      {
      actor("You observe", oblist, " carefully and realize that "+pro+" is "+
         "the leader.");
   }
   else if (leader == TP)
      {
      actor("You feel stupid as you realize that", oblist, " is on YOUR team.");
   }
   else
      {
      actor("You observe", oblist," carefully, and realize that "+
         leader->query_the_name(TP)+" is "+pos+" leader.");
   }
   
   targetbb(" observes you carefully.", oblist);
   all2actbb(" observes", oblist, " carefully.");
   
   
   return 1;
}

void
reset_observe(object observer)
{
   observer->remove_prop("_observe_resetting");
   observer->catch_msg("Your mind feels clear and observant again.\n");
}

