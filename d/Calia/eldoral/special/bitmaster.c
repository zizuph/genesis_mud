/*
 * bitmaster.c
 *
 * Object handles all quest completion routines, including
 * bit setting, questxp reward, and logging.
 *
 * Coded by Khail, Jan 12/97
 */
#pragma strict_types

#include "defs.h"
#include <time.h>
#include <const.h>

public int
test_bit(int questnum, object who)
{
    return who->test_bit("Calia", ELDORAL_QUEST_GROUP, questnum);
}

public void
set_bit(int questnum, object who)
{
    string questname;
    int questxp,
        currentxp,
        state;

    if (!who || test_bit(questnum, who))
        return;
    
    switch(questnum)
    {
        case ELDORAL_HORN_QUEST_BIT:
            questname = "Horn and the Skiff";
            state = who->query_prop(LIVE_I_HORN_QUEST);
            questxp = 400;              // Reward for sounding horn.
            if (state & HQ_KILLED_KROUG)
                questxp += 300;        // Bonus for killing kroug.
            if (state & HQ_FOUND_HORN)
                questxp += 200;        // Bonus for finding horn.
            if (state & HQ_HUNG_HORN)
                questxp += 100;        // Bonus for hanging horn.
            who->remove_prop(LIVE_I_HORN_QUEST);
            break;

        case ELDORAL_SEER_QUEST_BIT:
            questname = "Seer and the Lord";
            state = who->query_prop(LIVE_I_SEER_QUEST);
            questxp = 1000;            // Default reward.
            if (state & SEQ_SPOKE_SEER)
                questxp += 500;        // +200 for speaking to seer.
            if (state & SEQ_FOUND_DAGGER)
                questxp += 500;        // +500 for finding dagger.
            if (state & SEQ_FOUND_CLOTH)
                questxp += 500;        // +500 for finding cloth.
            if (state & SEQ_SPOKE_LORD)
                questxp += 500;        // +500 for speaking to lord.
            who->remove_prop(LIVE_I_SEER_QUEST);
            break;

        case ELDORAL_SWORD_QUEST_BIT:
            questname = "Sword in the Stone";
            state = who->query_prop(LIVE_I_SWORD_QUEST);
            questxp = 2000;            // Default reward.
            if (state & SWQ_FOUND_PARCH)
                questxp += 200;        // +200 for finding parchment.
            if (state & SWQ_FOUND_CHAR)
                questxp += 200;        // +200 for finding charcoal.
            if (state & SWQ_COPY_CHIM)
                questxp += 400;        // +400 for making chimera copy.
            if (state & SWQ_COPY_WARR)
                questxp += 400;        // +400 for making warrior copy.
            if (state & SWQ_MARKED_X)
                questxp += 400;        // +400 for marking the pool.
            if (state & SWQ_WEIGHT_STONE)
                questxp += 400;        // +400 for weighting triggers.
            if (!(state & SWQ_FAILED))
                questxp += 3000;        // +3000 for no mistakes.
            who->remove_prop(LIVE_I_SWORD_QUEST);
            break;

        case ELDORAL_BEAST_QUEST_BIT:
            questname = "Eye of the Beast";
            state = who->query_prop(LIVE_I_BEAST_QUEST);
            questxp = 7000;            // Default reward.
            if (state & BQ_SPOKE_FIRESTORM)
                questxp += 1000;        // +1000 for speaking to firestorm.
            if (state & BQ_FOUND_SCEPTRE)
                questxp += 1000;        // +1000 for finding sceptre.
            if (state & BQ_USED_SCEPTRE)
                questxp += 1000;        // +1000 for using sceptre.
            if (state & BQ_KILLED_LORD)
                questxp += 1000;        // +1000 for kiling death lord.
            who->remove_prop(LIVE_I_BEAST_QUEST);
            break;

        case ELDORAL_GURU_QUEST_BIT:
            questname = "Calian Sup. Guru";
            questxp = 100;            // Token xp reward.
            break;
        default:
            questname = "XXX";
            questxp = 0;
    }

    if (questname == "XXX")
    {
        tell_object(who, "Quest is bugged, please leave a buglog.\n");
        log_file("eldoral_quest_errors", "Bitmaster tried to reward " +
            who->query_real_name() + " for a quest number " +
            questnum + " on " + ctime(time()) + ".\n");
        return;
    }

  /* Set player's quest bit _before_ the questxp is given out, */
  /* to reduce the chances of the set failing after the */
  /* xp reward, which would permit the quest to be solved */
  /* again. Then force a save for another level of security.*/
    who->set_bit(ELDORAL_QUEST_GROUP, questnum);
    log_file("eldoral_quests", capitalize(who->query_real_name()) + 
        " completed the " + questname + " Quest at " +
        ctime(time()) + ", and was awarded " + questxp + " exp. " +
        "Statave: " + who->query_average_stat() +
        ". Age: " + CONVTIME(who->query_age() * 2) + ".\n" +
        "QuestFlags: " + state + ".\n");
    who->save_me(0);
  /* Calculate actual xp to award. Get the player's current */
  /* total questxp, reduce it according to the current quest */
  /* modifier to get a 'base' amount of the player's current */
  /* quest xp. If this amount is less than the normal quest */
  /* xp reward, use the modified base amount instead, so the */
  /* player can never more than double his quest xp. */
    if (questxp)
    {
/*
 * WRONG WRONG WRONG! Domains need not concern themselves with the total
 * amount of experience a player has, plus, multiplying big numbers like
 * this may very well exceed MAXINT, with all due problems. Just add the
 * experience the player is due and the mudlib will take care of the rest.
 * /Mercade
 *
        currentxp = who->query_exp() - who->query_combat_exp();
        currentxp = currentxp * QUEST_FACTOR / 100;
        questxp = (questxp < currentxp ? questxp : currentxp);
 *
 */
        if (questxp < 1000)
            tell_object(who, "You feel a little more experienced!\n");
        else if (questxp < 5000)
            tell_object(who, "You feel more experienced!\n");
        else
            tell_object(who, "You feel much more experienced!\n");
        who->add_exp(questxp);
        who->save_me(0);
    }
}
