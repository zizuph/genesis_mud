/* function do_say: filters sentances according to 
 *                  listeners language skill.
 * Arguments:
 *                  Arg: the sentance to be filtered.
 */

string *accepted_races = ({"dwarf","duergar"});
public int
do_say(string arg)
{
   if (!strlen(arg))
      {
      NF("Say what in the local jargon?\n");
      return 0;
   }
   
   filter(all_inventory(environment(this_object())) - ({ this_object() }),
      "do_it", this_object(), arg);
   return 1;
}

/* Function do_it: Does the actual filtering of the text.
 * arguments: who - all who can hear the npc
 *            arg - the sentence to be filtered.
*/
public int
do_it(object who, string arg)
{
   int i;
   string text;
   string dummy;
   if (!living(who))
      return 0;
   
   /* listeners with above 50 in language or dwarven with above 40
   understands it perfectly */
   if ((who->query_race_name() == "dwarf" && who->query_skill(SS_LANGUAGE) > 40) ||
        who->query_skill(SS_LANGUAGE) > 50)
   {
      tell_object(who, TO->query_The_name() + " growls "+
         "in the local dwarven jargon: " + arg + "\n");
      return 1;
   }
   
   /* listeners with less than 20 in language doesn't
   understand anything */
   if(who->query_skill(SS_LANGUAGE) < 20)
      {   
      tell_object(who, TO->query_The_name() + " growls "+
         "some harsh sounds. You find it utterly unconprehensable.\n");
      return 1;
   }
   
   /* remove vocals from arg according to ss_language skill */
   
   text="";
   for (i=0;i<strlen(arg);i++)
   {
      dummy=extract(arg,i,i);
      if(dummy != "a" && dummy !="e" && dummy != "i" &&
         dummy != "o" && dummy != "u" && dummy !="s" && dummy != "y")
      text=text+dummy;
      else
         {
         if (random(who->query_skill(SS_LANGUAGE)-20)>10)
            text=text+dummy;
         else
         {
            switch(random(4))
            {
               case 0: text=text+"x"; break;
               case 1: text=text+"r"; break;
               case 2: text=text+"gh"; break;
               case 3: text=text+"z"; break;
               default: text=text+"r"; break;
            }
         }
      }
   }
   tell_object(who, TO->query_The_name() + " growls "+
      "something in the local dwarven jargon. You manage to catch this: "+
      text+".\n");
   return 1;
}


/* The next functions will make this npc react
*  to the race of the arriving livings.
*  Made by Korat with great help from Mercade.
*/

/* init_living() - this function is called each time an object
 *                 enters the environment of this npc.
 *                 It filters away all except players.
*/
void
init_living()
{
   object leader;
   object dummy;
   float time;
   
   ::init_living();
   
   leader = this_player()->query_leader();
   if (!objectp(leader))
   {
      leader = this_player();
   }

   /* if player is not here or cannot be seen then return */
   if (present(leader, environment()) &&
      (CAN_SEE(this_object(),leader)))
   {
      time = itof(random(4)+1);
      set_alarm(time, 0.0, "do_react", leader);
      return;
   }
   return;
}

/* The npc's reaction on someone entering its environment */
void
do_react(object player)
{
   object *team;
   object *team_present;
   string player_race;
   int i;

   /* we don't react to friendly npc's */   
   if(player->query_race_name() == "dwarf" &&
      player->query_npc()) return;

   /* did the player just run by? */
   if (environment(player) != environment()) return;

   /* we need to know players team-status and race */
   team = player->query_team_others();
   player_race = player->query_race_name();
   
   /* if player is alone then just check if race is accepted or not */
   if(!sizeof(team))
   {
      if (member_array(player_race, accepted_races) > -1)
         set_alarm(0.0, 0.0, "do_react_friend_alone", player);
      else
         set_alarm(0.0, 0.0, "do_react_enemy_alone", player);
      return;
   }
   
   /* lets check the team that is here and can be seen */
   team_present = FILTER_CAN_SEE(team, this_object());
   
   /* Deal with the player as being alone if the team is not there. */
   if(!sizeof(team_present))
   {
      if (member_array(player_race, accepted_races) > -1)
         set_alarm(0.0, 0.0, "do_react_friend_alone", player);
      else
         set_alarm(0.0, 0.0, "do_react_enemy_alone", player);
      return;
   }
   
   /* ok, lets react to the player */
   if(member_array(player_race, accepted_races) > -1)
   {
      set_alarm(0.0, 0.0, "do_react_friend_alone", player);
      set_alarm(0.0, 0.0, "do_react_friend_team", player, team_present);
   }
   else
      set_alarm(0.0, 0.0, "do_react_enemy_team", player, team_present);
   return;
}

