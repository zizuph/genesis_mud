/*
 *   Fixed the do_die function call so it actually works
 *   for leaving members.            Arman, 23 June 2020
 */

#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_occ_sh";

#include "../guild.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <ss_types.h>
#include <macros.h>
#include <math.h>

#define SW shadow_who

/* Following functions needs to be defined in file that inherits this
 *
 * mixed query_guild_trainer_occ();
 * int query_guild_tax_occ()
 * string query_dragonarmy_division()
 * mixed query_guild_skill_name(int type)
 * void remove_dragonarmy_startlocation_souls_skills()
 * void delay_init_dragonarmy()
 */

/* Global variables */
mixed *gTitles;
int promotion_level = 0;
int gAgeToKick = 0;

/* Prototypes */
void remove_dragonarmy_member();

/* Functions to be redefined in file that inherits this one */
void remove_dragonarmy_startlocation_souls_skills() {}
void delay_init_dragonarmy() {}

string
query_guild_style_occ()
{
    return GUILD_STYLE;
}

string
query_guild_name_occ()
{
    return GUILD_NAME;
}

string
query_dragonarmy_division()
{
    return "";
}

string query_color() { return query_dragonarmy_division(); }
string query_colour() { return query_dragonarmy_division(); }

int
query_dragonarmy_occ_member()
{
    return 1;
}

int
query_dragonarmy_promotions()
{
    return promotion_level;
}

int
query_guild_leader_occ()
{
    if (query_dragonarmy_promotions() == 4)
        return 1;
    if (MANAGER->query_master_title(SW, query_dragonarmy_division()))
        return 1;
    return 0;
}

varargs int
set_promotion_level(int promo, object who = 0)
{
    if(promo > 4 || promo < 0)
    {
        NF("Promotion level cannot be set to that level.\n");
        return 0;
    }

    promotion_level = promo;

    if(!interactive(SW))
    {
        return 1;
    }

#ifndef DA_TESTING
    if (SW->query_wiz_level() || extract(SW->query_real_name(), -2) == "jr")
    {
        return 1;
    }
#endif DA_TESTING

    setuid();
    seteuid(getuid());
    return MANAGER->set_promotions(SW, promo, who);
}

int
query_minimum_guild_stat()
{
    int minimum;
    
    minimum = (promotion_level != 1 ? 6 * promotion_level : 7);
    minimum = 1 + ((minimum * 960) / SW->query_average_stat());
    
    return minimum;
}


int
query_dragonarmy_rank_stat()
{
    // Previously, guild stat was reset to a minimum whenever there
    // was a promotion. We are now tracking the GXP at promotion
    // and instead simulating the gstat for title purposes.
    //
    // new gxp = minimum gxp + current gxp - promotion gxp
    int promotion_gxp, current_gxp, minimum_gxp, new_gxp;
    minimum_gxp = SW->stat_to_exp(query_minimum_guild_stat());
    promotion_gxp = SW->query_skill(SS_DRAGONARMY_PROMOTION);
    current_gxp = SW->query_acc_exp(SS_OCCUP);
    if(!promotion_gxp)
    {
        promotion_gxp = minimum_gxp;
        SW->set_skill(SS_DRAGONARMY_PROMOTION, minimum_gxp);            
    }
    else if (promotion_gxp > current_gxp)
    {
        // Because minimum guild stat is dependent on avg stat size,
        // this actually changes. As it changes, we reset to the
        // lowest minimums.
        promotion_gxp = current_gxp;
        SW->set_skill(SS_DRAGONARMY_PROMOTION, current_gxp);
    }
    new_gxp = max(0, minimum_gxp + current_gxp - promotion_gxp);
    
    int newstat = SW->exp_to_stat(new_gxp);
    return (newstat * SW->query_average_stat()) / 960;
}

/*
  How high promotion soldier can get
  0 promotions: 7 subranks
  1 promotions: 5 subranks
  2 promotions: 6 subranks
  3 promotions: 4 subranks
  4 promotions: 1 subrank
*/
int
query_max_promotions()
{
    int rank = query_dragonarmy_rank_stat();

    if(rank > 17)   /* 18.. */
        return 3;
    if(rank > 11)   /* 12..17 */
        return 2;
    if(rank > 6)    /* 7..11 */
        return 1;
    return 0;       /* 0..6 */
}

int
query_dragonarmy_subrank()
{
    int rank_stat = query_dragonarmy_rank_stat();

    switch( query_dragonarmy_promotions() )
    {
    case 0:
        if(rank_stat < 0)
            return 0;
        if(rank_stat > 6)
            return 6;
        return rank_stat;
    case 1:
        if(rank_stat < 7)
            return 0;
        if(rank_stat > 11)
            return 4;
        return (rank_stat - 7);
    case 2:
        if(rank_stat < 12)
            return 0;
        if(rank_stat > 17)
            return 5;
        return (rank_stat - 12);
    case 3:
        if(rank_stat < 18)
            return 0;
        if(rank_stat > 21)
            return 3;
        return (rank_stat - 18);
    default:
        return 0;
    }
}

string
query_guild_title_occ()
{

    string title, master;
    int rank = query_dragonarmy_promotions();
    int subrank = query_dragonarmy_subrank();

    if (!sizeof(gTitles))
        return "Dragonarmy soldier";

    title = gTitles[rank][subrank];

    if(rank == 4)
        return title;
    master = MANAGER->query_master_title(SW, query_dragonarmy_division());
    if (master)
        title += " and " + master;
    return title+" of the "+C(query_dragonarmy_division())+" Dragonarmy";

}

mixed
query_acceptable_occ_dragonarmy_member(object who)
{
    string race, rrace;
    setuid();
    seteuid(getuid());

    if (MANAGER->query_banned(who, query_dragonarmy_division()))
    {
        gAgeToKick = 1;
        return "You have been banned from the "+
            C(query_dragonarmy_division())+" Dragonarmy!";
    }

    if (who->query_alignment() >= 100)
    {
        return "You have strayed from the dark path!";
    }

    race = who->query_race();
    rrace = (SW == who) ? TO->query_race_name() : who->query_race_name();
    DBGMSG("*** "+who->query_name()+", "+race+", "+rrace+" ***\n");
    if (race == "hobbit" || race == "gnome" || (race == "dwarf" && rrace != "minotaur") ||
        (race == "elf" && rrace != "half-elf" && rrace != "orc"))
    {
        if (race == "elf" && who == SW &&
            (SW->query_region_title() == "half-elf" ||
                SW->query_region_title() == "half-human" ||
                TO->query_region_title() == "half-elf" ||
                TO->query_region_title() == "half-human" ||
                SW->query_race_name() == "orc" ||
                TO->query_race_name() == "orc")
            )
            return 1; /* problems with racial guild stuff */
        
        /*we allow orcs*/
        /*
        if (who == SW && rrace == "orc" || rrace == "uruk-hai") {
            return 1;
        }
        */

        /* we allow minotaurs */
        if (who == SW && rrace == "minotaur")
        {
          return 1;
        }

        return "You are "+rrace+"! The Dragonarmy does not "+
            "accept any of your kind.";
    }

    if (who == SW) /* check below this is only for new wannabe members */
    {
        return 1;
    }

    /* To join age and stat requirement has to be met.
     * Both are player dependant and in range
     * age: 100 - 149 hours
     * avg_stat: 43 - 57
     *
     * Age Requirement removed, does not make sense.
     * (who->query_age() / 1800) - 100 <
     * NAME_TO_RANDOM(who->query_real_name(), 87654321, 50) ||
     */
    if (who->query_average_stat() - 43 <
        NAME_TO_RANDOM(who->query_real_name(), 12345678, 15))
    {
        return "The Dragonarmy is not a kindergarden! Return when "+
            "you are bigger and older, kid.";
    }
    
    /* O.K... let him join */
    return 1;
}

private void
candidate_to_kick(string why)
{
    SW->catch_tell("\n"+why+"\n");
    if (!gAgeToKick || gAgeToKick + 7200 > SW->query_age())
    {
        if (!gAgeToKick)
        {
            gAgeToKick = SW->query_age();
            SW->remove_autoshadow(TO);
            SW->add_autoshadow(MASTER + ":" + promotion_level + "#" + gAgeToKick);
            SW->catch_tell("This is first warning before you will be kicked out of Dragonarmy.\n\n");
        }
        else
        {
            SW->catch_tell("Fix it immediately or you will be kicked out of Dragonarmy.\n\n");
        }
    }
    else
    {
        SW->catch_tell("Kicking you out of Dragonarmy now.\n\n");
        remove_dragonarmy_member();
    }
}

private void
secure_delay_remove_check(object who)
{
    mixed why = query_acceptable_occ_dragonarmy_member(who);

    if (stringp(why))
    {
        candidate_to_kick(why);
        //  who->catch_tell(why+"\n");
        //  remove_dragonarmy_member();
    }
}

int
query_guild_keep_player(object who)
{
    mixed why;

    setuid();
    seteuid(getuid());
/*
    if (MANAGER->query_banned(who, query_dragonarmy_division()))
    {
        who->catch_tell("You have been banned from the "+
            C(query_dragonarmy_division())+" Dragonarmy!\n");
        remove_dragonarmy_member();
        return 0;
    }
    if (MANAGER->query_punishment(who, PUN_NOGUILDXP))
    {
        MANAGER->remove_punishment(who, PUN_NOGUILDXP);
        who->clear_guild_stat(SS_OCCUP);
        SW->clear_bit(3,0); // clear guru quest
        who->remove_skill(SS_DRAGONARMY_FUND);
    }
    if (MANAGER->query_punishment(who, PUN_NOFUND_TQ))
    {
        MANAGER->remove_punishment(who, PUN_NOFUND_TQ);
        who->set_skill(SS_DRAGONARMY_FUND, (3 * who->query_skill(SS_DRAGONARMY_FUND)) / 4);
    }
    if (MANAGER->query_punishment(who, PUN_NOFUND_H))
    {
        MANAGER->remove_punishment(who, PUN_NOFUND_H);
        who->set_skill(SS_DRAGONARMY_FUND, who->query_skill(SS_DRAGONARMY_FUND) / 2);
    }
    if (MANAGER->query_punishment(who, PUN_NOFUND_O))
    {
        MANAGER->remove_punishment(who, PUN_NOFUND_O);
        who->remove_skill(SS_DRAGONARMY_FUND);
    }
    if (MANAGER->query_punishment(who, PUN_NOGURU))
    {
        MANAGER->remove_punishment(who, PUN_NOGURU);
        SW->clear_bit(3,0); // clear guru quest
    }
*/

    why = query_acceptable_occ_dragonarmy_member(who);
    if (stringp(why))
    {
        /*
        set_alarm(10.0, 0.0, &secure_delay_remove_check(who));
        */
        set_alarm(350.0, 0.0, &secure_delay_remove_check(who));
    }

    return 1;
}

void
delay_dragonarmy_query_keep_player(object who)
{
    setuid();
    seteuid(getuid());

    if (MANAGER->query_banned(who, query_dragonarmy_division()))
    {
        who->catch_tell("You have been banned from the "+
            C(query_dragonarmy_division())+" Dragonarmy!\n");
        remove_dragonarmy_member();
        return 0;
    }

    if (MANAGER->query_punishment(who, PUN_NOGUILDXP))
    {
        MANAGER->remove_punishment(who, PUN_NOGUILDXP);
        who->clear_guild_stat(SS_OCCUP);
        SW->clear_bit(3,0); // clear guru quest
        who->remove_skill(SS_DRAGONARMY_FUND);
    }

    if (MANAGER->query_punishment(who, PUN_NOFUND_TQ))
    {
        MANAGER->remove_punishment(who, PUN_NOFUND_TQ);
        who->set_skill(SS_DRAGONARMY_FUND, (3 * who->query_skill(SS_DRAGONARMY_FUND)) / 4);
    }

    if (MANAGER->query_punishment(who, PUN_NOFUND_H))
    {
        MANAGER->remove_punishment(who, PUN_NOFUND_H);
        who->set_skill(SS_DRAGONARMY_FUND, who->query_skill(SS_DRAGONARMY_FUND) / 2);
    }

    if (MANAGER->query_punishment(who, PUN_NOFUND_O))
    {
        MANAGER->remove_punishment(who, PUN_NOFUND_O);
        who->remove_skill(SS_DRAGONARMY_FUND);
    }

    if (MANAGER->query_punishment(who, PUN_NOGURU))
    {
        MANAGER->remove_punishment(who, PUN_NOGURU);
        SW->clear_bit(3,0); // clear guru quest
    }

    return;
}

void
init_occ_shadow(string arg)
{
    int old_promotion = 0;

    if (arg)
        sscanf(arg, "%d#%d", old_promotion, gAgeToKick);

#ifdef GUILD_CLOSED
    SW->clear_guild_stat(SS_OCCUP);
    remove_guild_occ();
    return;
#endif

    set_alarm(1.0, 0.0, delay_init_dragonarmy);
    set_alarm(2.0, 0.0, &delay_dragonarmy_query_keep_player(SW));

    if(!interactive(SW))
    {
        return;
    }

#ifndef DA_TESTING
    if (SW->query_wiz_level() || extract(SW->query_real_name(), -2) == "jr")
    {
        return;
    }
#endif DA_TESTING

    setuid();
    seteuid(getuid());
    if(MANAGER->query_division(SW) != query_dragonarmy_division())
    {
        MANAGER->remove_member(SW);
    }
    if(!MANAGER->query_member(SW))
    {
        MANAGER->add_member(SW, query_dragonarmy_division(),
            SW->query_prop("_vouched_for_"+query_dragonarmy_division()+"_army"));
        if (old_promotion > 0)
            MANAGER->set_promotions(SW, old_promotion, 0);
    }
    promotion_level = MANAGER->query_promotions(SW);
    
    find_player("navarre")->catch_msg("Promotion level: "+promotion_level+"\n");

    // arg is used to restore promotion in case savefile corrupts
    SW->remove_autoshadow(TO);
    SW->add_autoshadow(MASTER + ":" + promotion_level + "#" + gAgeToKick);
}

int
add_dragonarmy_shadow(object who)
{
    return shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);
}

varargs int
join_dragonarmy(object who, string div, mixed recruiter)
{
    int ret;

    if (div != query_dragonarmy_division())
        return 0;

    ret = add_dragonarmy_shadow(who);

    if(!interactive(who))
    {
        return ret;
    }

#ifndef DA_TESTING
    if(who->query_wiz_level() || extract(who->query_real_name(), -2) == "jr")
    {
        return ret;
    }
#endif DA_TESTING

    if (ret == 1)
    {
        who->clear_guild_stat(SS_OCCUP);
        who->set_skill(SS_DRAGONARMY_PROMOTION, 0); // reset the promotions level
        setuid();
        seteuid(getuid());
        MANAGER->add_member(who, div, recruiter);
        log_file("dragonarmy_join", who->query_real_name() + " - " +
            extract(ctime(time()), 4, 15) + " - " +
            query_dragonarmy_division() + "\n");
        ATTACKERS_ADMIN->remove_attacker(who->query_real_name(),"joined Dragonarmy");
        who->remove_skill(SS_DRAGONARMY_FUND);
        SW->clear_bit(3,0); // clear guru quest when joining
        set_promotion_level(0, recruiter);
    }
    return ret;
}

void
remove_dragonarmy_member()
{
    deep_inventory(SW)->remove_dragonarmy_object();
    remove_dragonarmy_startlocation_souls_skills();

    /* Be nice and clear the guild stat first so it's less likely
     * that quest xp is lost.
     */
    SW->clear_guild_stat(SS_OCCUP);
    //   SW->add_exp(-SW->query_exp_combat() / 6, 1);

    if (SW->query_skill(SS_DRAGONARMY_ATTACK) > 100)
    {
        SW->set_skill(SS_DRAGONARMY_ATTACK, 100);
    }
#ifndef DA_TESTING
    if((!SW->query_wiz_level()) && (extract(SW->query_real_name(), -2) != "jr"))
#endif DA_TESTING
    {
        setuid();
        seteuid(getuid());
        MANAGER->remove_member(SW);
        log_file("dragonarmy_leave", SW->query_real_name() + " - " +
            extract(ctime(time()), 4, 15) + " - " +
            query_dragonarmy_division() + "\n");
    }

    SW->remove_skill(SS_DRAGONARMY_FUND);
    SW->remove_skill(SS_DRAGONARMY_ATTACK);
    SW->remove_skill(SS_DRAGONARMY_PROMOTION);
    SW->clear_bit(3,0); // clear guru quest when leaving
    SW->set_hp(-10000);
    SW->do_die(MANAGER);
    remove_guild_occ();
}

void
remove_da_shadow()
{
    remove_shadow();
}

public void
do_die(object killer)
{
    MANAGER->remove_killed_leader(this_object(), killer);
    SW->do_die(killer);
}


void
reward_warfare_fundraise(int amount, string army)
{
    if (C(query_dragonarmy_division()) + " Dragon Army" != army)
        return;

    SW->set_skill(SS_DRAGONARMY_FUND,
        SW->query_skill(SS_DRAGONARMY_FUND) + (amount / 1728));
}
