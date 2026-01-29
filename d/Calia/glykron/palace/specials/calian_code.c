
/*
   Calian functions

   Coded by Maniac, spliced from council_code by Glykron

   11.03.95
   
   7/12/96      added removal of maul/swarm registration on leaving
                                                          Maniac
   22/5/96      removal of skills on leaving changed      Maniac
   28.7.95      Another bug corrected                     Maniac
   13.3.95      Bugs taken out from present() and leave   Maniac   
    6.4.95      accepted players feature added            Maniac
   10.7.95      Skill decay stuff sorted out              Maniac
   17/7/95      cleanup cinfo on player leaving, changed
                xp adjustment                             Maniac
  27/10/95      honourable discharge added, lose less xp  Maniac
  28/12/95      when a player leaves, remove special
                calian title                              Maniac

  History:
*/


#pragma save_binary

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <std.h>
#include "defs.h"
#include CALIAN_HEADER
#include COUNCIL_HEADER
#include RECRUITER_HEADER

#define NUM_SKILLS 11

static int *skill_list =
({
    SS_WEP_SWORD, SS_WEP_POLEARM, SS_WEP_AXE, SS_WEP_KNIFE,
    SS_WEP_MISSILE, SS_WEP_JAVELIN, SS_2H_COMBAT, SS_PARRY, SS_DEFENCE,
    SS_SWARM, SS_MOVE_BEHIND
});


int is_calian_wiz(object tp)
{
    return SECURITY->query_wiz_dom(tp->query_real_name()) == "Calia";
}


int is_calian(object player)
{
    return player->query_guild_name_occ() == GUILD_NAME;
}


int
join(string str)
{
    object tp, orb, shadow, gm; 
    int wiz_jr; 

    if (str != "trust" && str != "my trust")
        return 0;

    tp = TP;

    if (!(gm = present("guildmaster", 
         find_object(ROOM("light_trainroom")))))
    {
        write("You cannot join the guild while the guildmaster is not here.\n");
        return 1;
    }

    if (tp->query_guild_member(GUILD_NAME))
    {
        write("You are already a member of this guild.\n");
        return 1;
    }

    if (tp->query_guild_style("magic"))
    {
        write( "You cannot join this guild while you are a member of a " +
            "mage guild.\n");
        return 1;
    }

    if (tp->query_guild_member(GUILD_TYPE))
    {
        write("You are already a member of another " + GUILD_TYPE +
            " guild.\n"); 
        return 1;
    }

    if (tp->query_alignment() < (tp->query_stat(SS_OCCUP) - 1) * 5)
    {
        write(
            "I heard rumours you've been up to no good lately.  " +
            "You must atone for your deeds before you can be trusted.  " +
            "\n");
        return 1;
    }

    if (!(wiz_jr = wildmatch("*jr", tp->query_real_name())) && 
        !objectp(orb = present("Calia_orb", gm))) { 
        write("The guildmaster says: You must give me a crystalline orb " +
            "before you can join this guild.  You'll need help from a " +
            "current member to get it.  " +
            "\n");
        return 1;
    }

    seteuid(getuid());
    COUNCIL_CODE->carry_out_punishments(tp);
    if (COUNCIL_CODE->is_expelled(tp))
    {
        tp->catch_msg(
	    "You were expelled from the guild before, and have not been " +
	    "granted a pardon by the Calian Council.\n");
        return 1;
    }

    shadow = clone_object(SPECIAL("calian_shadow"));
    if (shadow->shadow_me(tp, GUILD_TYPE, GUILD_STYLE, GUILD_NAME) != 1)
    {
        NF("For some unknown reason you cannot join this guild.\n");
        shadow->remove_shadow();
        return 1;
    }

    RECRUITER_CODE->rem_app(tp->query_name()); 
    RECRUITER_CODE->rem_acc(tp->query_name()); 
    if (!wiz_jr) 
        OBJECT("calian_members_poster")->update_poster(
            capitalize(tp->query_real_name()) + " joined our guild!\n"); 

    tp->clear_guild_stat(SS_OCCUP);
    tp->set_guild_pref(SS_OCCUP, GUILD_TAX);
    tp->set_learn_pref(TP->query_learn_pref(-1));
    orb->remove_object();
    write("The guildmaster turn the orb into dust and sprinkles it on you.\n" +
        "You are now a member of this guild.\n");
    say("The guildmaster turns the orb into dust and sprinkles it on " +
        QCTNAME(tp) + ".\n");

    if (!present(MEDALLION_ID, tp))
    {
        write("The guildmaster gives you a medallion.\n");
        say("The guildmaster gives " + QTNAME(tp) + " a medallion.\n");
        clone_object(OBJECT("calian_medallion"))->move(tp);
    }

    tp->add_cmdsoul(SPECIAL("calian_cmdsoul"));
    tp->update_hooks();
    tp->setup_skill_decay();

    return 1;
}



/* Standard function for the various ways of leaving the guild (how), 
   which include leaving by one's own action, expulsion and
   honourable discharge. */
int
leave(string str, object player, string how)
{
    int xp_remove;
    object tp;
    string rm;

    if (str != "trust" && str != "my trust")
        return 0;

    if (!objectp(player))
        tp = TP;
    else
        tp = player;

    if (!stringp(how) || 
        ((how != "discharge") && (how != "expulsion")))
        how = "leaving";

   
    if (!is_calian(tp))
    {
        if (how == "leaving")
            tp->catch_msg("You are not a member of the Calian " +
                          "guild.\n");
        return 1;
    }

    if (tp->remove_guild_occ())
    {
        object medallion;
        int i;

        if (how == "leaving") {
            tp->catch_msg("You are no longer a member of the Calian guild.\n");
            tell_room(environment(tp), QCTNAME(tp) + " leaves the Calian " +
                                                      "guild.\n", tp);
        }

        if (how == "discharge")  {
            xp_remove = tp->query_exp_combat() / 8;
            tp->add_exp(-xp_remove, 1);
            tp->catch_msg("You lose a little of your combat experience.\n");
        }
        else  {
            xp_remove = tp->query_exp_combat() / 4;
            tp->add_exp(-xp_remove, 1);
            tp->catch_msg("A ray of light shines down from the heavens on " +
                  "you. A pained expression comes over your face " +
                  "as you are drained " +
                  "of life force. The light then fades, leaving " +
                  "you looking a broken " + tp->query_race_name() + 
                  ".\n");
            tell_room(environment(tp), "A ray of light shines down from " +
                "the heavens on " + 
                QTNAME(tp) + ". A pained expression comes over " +
                tp->query_possessive() + " face as " +
                tp->query_pronoun() + " is " +
                "drained of life force. The light then fades, " +
                "leaving " + tp->query_objective() + " looking a broken " + 
                tp->query_race_name() + ".\n", tp);
        }

        seteuid(getuid(this_object()));
        CALIAN_INFO_HANDLER->remove_info(tp);
        CALIAN_TITLE_HANDLER->remove_calian_special_title(tp->query_name());
        MAUL_CONTROL->player_left_guild(tp); 
        log_file("left_guild", tp->query_real_name() + " left the " +
                  "Calian guild, " + how + ", " + xp_remove + 
                  " experience lost, " +  ctime(time()) + ".\n"); 

        tp->remove_skill(SS_SWARM); 
        tp->remove_skill(SS_MAUL); 
        tp->remove_skill(SS_MOVE_BEHIND); 
        tp->remove_skill(CALIAN_RACK_POINTS); 
        tp->remove_skill(CALIAN_OPTIONS); 

        rm = explode(ROOM("light_guild"), ".")[0];

        if (tp->query_default_start_location() == rm)
        {
            tp->set_default_start_location(tp->query_def_start());
            tp->catch_msg("You no longer start at the Calian guild.\n");
        }

	tp->clear_guild_stat(SS_OCCUP);
        tp->set_guild_pref(SS_OCCUP, 0);
        tp->remove_cmdsoul(SPECIAL("calian_cmdsoul"));
        tp->update_hooks();
        tp->setup_skill_decay();
    }
    else {
        tp->catch_msg("Because of a bug you cannot leave the guild.\n");
    }
    return 1;
}
