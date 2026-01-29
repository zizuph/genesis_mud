
/* **********************************************
 *                  Quest.c
 * File to be inherited by all Avenir quests in
 * the object that gives experience. This handles
 * rewards and messages for experience, alignment,
 * and prestige adjustments, as well as makes sure
 * they are withing the necessary bounds (eg, handles
 * not allowing players to get more xp then they
 * already have.
 *
 * Example 1: Simple quest, just xp reward
 *                  name           who         group bit   xp
 *   reward_quest("book quest", this_player(),   3,   4,   90);
 *
 * Example 2: Quest with evil align & prestige adjustment:
 *
 *                    name         who        group  bit   xp  align prestige
 *   reward_quest("dead quest", this_player(),   5,   8,  2000, -400, -3);
 *
 *           -Lord Cirion, February 10, 1996
 */

#pragma strict_types
#pragma save_binary

#include <macros.h>

#define QUEST_LOG     "/d/Avenir/log/quest/quests"
#define DOMAIN        "avenir"

/*
 * public nomask varargs int 
 * reward_quest(string quest_name, object who, int group, int bit, 
 *              int experience, int alignment, int prestige)
 *
 * Returns: 0  -  if the bit was already set in the player, so no
 *                reward was given, or the player was not
 *                interactive or in the game.
 *          xp -  the amount of experience actually given for
 *                the quest, after taking the minimum of
 *                experience and the player's query_exp()
 *
 */
public nomask varargs int
reward_quest(string quest_name, object who, int group, int bit, 
             int experience, int alignment, int prestige)
{
   string experience_msg;
   string alignment_msg;
   string prestige_msg;
   string log_msg;
   string quest_type;

   if( !who || !interactive(who) )
     return 0;

   if(who->test_bit(DOMAIN, group, bit))
     return 0;

    if(experience < 1) experience = 1;

    // experience given can never be greater than the current experience
    // of the player, based on the guildline in man xp_scale
    experience = MIN(who->query_exp(), experience);

    // Quest types[number] also from man xp_scale
    switch(experience)
     {
       case 1 .. 50:
         experience_msg = "a tiny bit more";
         quest_type = "tour[0]";
         break;
       case 51 .. 100:
         experience_msg = "slightly more";
         quest_type = "serious tour[0]";
         break;
       case 101 .. 1000:
         experience_msg = "a bit more";
         quest_type = "minor assignment[1]";
         break;
       case 1001 .. 10000:
         experience_msg = "more";
         quest_type = "small adventure[2]";
         break;
       case 10001 .. 50000:
         experience_msg = "quite a bit more";
         quest_type = "major adventure[3]";
         break;
       case 50001 .. 100000:
         experience_msg = "much more";
         quest_type = "quest[4]";
         break;

       default:
         experience_msg = "a great deal more";
         quest_type = "ultimate quest[5]";
         break;
    }

    log_msg = ctime(time())+ " " +capitalize(who->query_real_name()) +
              "("+who->query_average_stat()+")"+ 
              " completed " + quest_name + "\n"+
              "          " + experience + " exp (" +
              quest_type + ")";

    who->set_bit(group, bit);
    who->add_exp_quest(experience);
    who->catch_msg("You feel "+experience_msg+" experienced!\n");

    if(alignment)
      {
       // Bound the alignment adjustment based on the
       // guildlines in sman adjust_alignment

        if(alignment < -1000) alignment = -1000;
        if(alignment >  1000) alignment =  1000;

        log_msg += " " + alignment + " align";
        
        if( ( who->query_alignment() > 0 && alignment < 0 ) ||
            ( who->query_alignment() < 0 && alignment > 0 ) )
          alignment_msg = "You feel you have gone against your nature "
                         +"and done ";
        else
          alignment_msg = "You feel you have done ";

        switch(alignment)
         {
           case -1000 .. -800:
             alignment_msg += "an unholy act.";
             break;
           case -799 .. -600:
             alignment_msg += "a vile act.";
             break;
           case -599 .. -400:
             alignment_msg += "an evil act.";
             break;
           case -399 .. -200:
             alignment_msg += "a nasty act.";
             break;
           case -199 .. -100:
             alignment_msg += "a mean thing.";
             break;
           case -99 .. -1:
             alignment_msg += "an unpleasant deed.";
             break;
           case 0:
             alignment_msg += "an insignificant action.";
             break;
           case 1 .. 99:
             alignment_msg += "a nice act.";
             break;
           case 100 .. 199:
             alignment_msg += "an amiable act.";
             break;
           case 200 .. 600:
             alignment_msg += "a good act.";
             break;
           case 601 .. 1000:
             alignment_msg += "a holy act.";
             break;

           default:
             alignment_msg += "an insignificant action.";
             break;
         }
      who->adjust_alignment(alignment);
      who->catch_msg(alignment_msg+"\n");
     }

/* 
 * Check to see if there is any prestige for the quest and if
 * the player is a knight.
 * I don't think this will work for the Prestigion Knights'
 * Club, though.
 */
   if(prestige && 
      (who->query_guild_name_occ() == "Solamnian Knights" ||
       who->query_guild_name_lay() == "Sentries of Solamnia" ))
      {
        // Bound the min/max prestige levels based on the guidelines
        // in /d/Krynn/info/EXPORT/PRESTIGE

        if(prestige < -8) prestige = -8;
        if(prestige >  2500) prestige =  2500;

        log_msg += ", " + prestige + " prestige";

        switch(prestige)
         {
           case -8:
            prestige_msg = "you have done an extremely dishonourable act.";
            break;
           case -7 .. -5:
            prestige_msg = "dishonoured by your actions.";
            break;
           case -4 .. -2:
            prestige_msg = "you have done a dishonurable deed.";
            break;
           case -1:
            prestige_msg = "you are slightly dishonoured by your actions.";
            break;
           case 0 .. 50:
            prestige_msg = "you have done a kind deed.";
            break;
           case 51 .. 100:
            prestige_msg = "you have done a prestigious deed.";
            break;
           case 101 .. 200:
            prestige_msg = "you have done a just act.";
            break;
           case 201 .. 500:
            prestige_msg = "you have done a honourable act.";
            break;
           case 501 .. 1000:
            prestige_msg = "you have done a noble act.";
            break;
           case 1001 .. 1500:
            prestige_msg = "you have done a just and noble deed.";
            break;
           case 1501 .. 2000:
            prestige_msg = "you have done a great deed of honour and justice.";
            break;
           case 2001 .. 2500:
            prestige_msg = "you have done a deed of honour worthy of legends.";
            break;
         }
     who->change_prestige(prestige);
     who->catch_msg("You know in your heart that " + prestige_msg + "\n");
    }

  who->save_me();

  // Don't log tests by wizards and jrs
  if(!who->query_wiz_level() && extract(who->query_real_name(), 
     strlen(who->query_real_name()) - 2, strlen(who->query_real_name())) != "jr")
            write_file(QUEST_LOG, log_msg+".\n");
     return experience;
}

 
