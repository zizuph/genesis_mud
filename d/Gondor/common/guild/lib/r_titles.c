/*
 * The Ranger titles
 *
 * Elessar, July 1995.
 */

#pragma save_binary

inherit "/d/Gondor/common/lib/binbit";
#include <ss_types.h>
#include <language.h>
#include <const.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/ranger_defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"
#include "/d/Gondor/common/guild/lib/titles.h"

#define LEG_STAT   150        /* required guild-stat */
#define LEG_AGE    4320000    /* 100 days of playing age */

nomask public int query_ranger_legend();

string
query_company()
{
    if (query_bin_bits(1,16,2,TO->query_shadow_who()) == 3)
        set_bin_bits(1,16,2,TO->query_shadow_who(), 2);
    return COMPANY_TITLE[query_bin_bits(1,16,2,TO->query_shadow_who())];
}

int
query_ranger_rank(int test = 0)
{
    if (!test)
        return ((TO->query_shadow_who()->query_stat(SS_OCCUP)/3) - 
          TO->query_shadow_who()->query_skill(SS_PUNISHED) +
          TO->query_shadow_who()->query_skill(SS_REWARDED));
    else if (test == 2)   /* Don't add guild-stat */
        return (TO->query_shadow_who()->query_skill(SS_REWARDED) -
                TO->query_shadow_who()->query_skill(SS_PUNISHED));
    /* These are just for getting a sorted list for the 'rlist' */
    else if (COUNCIL->query_captain(TO->query_shadow_who()->query_real_name()))
        return 1000;
    else if (COUNCIL->query_lieutenant(TO->query_shadow_who()->query_real_name()))
        return 990;
    else if (COUNCIL->query_sergeant(TO->query_shadow_who()->query_real_name()))
        return 980;
    else if (TO->query_master_ranger())
        return 970;
    else if (query_ranger_legend())
        return 960;
    else return query_ranger_rank(0);
/*
    else return TO->query_shadow_who()->query_ranger_rank(0);
*/
}

int
test_ranger_skills()
{
    object  tp = TO->query_shadow_who();
    int     co = query_bin_bits(1, 16, 2, tp),
            pl_tot_sk,
            co_tot_sk,
            as, perc, n;
    as = sizeof(SKILLS);
    while(n < as)
    {
        co_tot_sk += COMPANY_SKILLS[co][n];
	pl_tot_sk += tp->query_skill(SKILLS[n]);
        n++;
    }
    perc = (100 * pl_tot_sk) / co_tot_sk;
    return perc;
}

nomask public int
query_ranger_legend()
{
    object  player = TO->query_shadow_who();

    if ((player->query_stat(SS_OCCUP) >= LEG_STAT) &&
        (player->query_age() >= LEG_AGE) &&
        (test_ranger_skills() >= 100))
        return 1;
    return 0;
}

nomask public string
query_ranger_title(int i = 0)
{
    int    ic, 
           rprt,
           mtask,
           co;
    object player = TO->query_shadow_who();
    int  avg_stat;
    object token = present("ranger_guild_object",player);
    if (query_bin_bits(1,16,2,player) == 3)
        set_bin_bits(1,16,2,player, 2);

    co = query_bin_bits(1, 16, 2, player);
    
    FIX_EUID;
    if (query_bin_bits(1, 18, 2, player) == 2)
    {
        return "Captain of the Rangers of " + query_company();
    }
    else if(ic = (int)COUNCIL->is_council_member(player->query_real_name()))
    {
        if(ic < G_LT || ic > I_LT)
        {
            tell_object(player, "BUG: please mail the guildmaster!\n" +
                "Your title in the Rangers' Guild will probably be wrong!\n");
        }
        return "Lieutenant of the Rangers of " + query_company();
    }
    else if(COUNCIL->query_sergeant(player->query_real_name()))
    {
        return "Sergeant of the Rangers of " + query_company();
    }

    avg_stat = query_ranger_rank(0);
    if (i == 0)
    {
        if (co == 0)
            return "Ranger pupil";
        else
            return "Ranger of " + query_company();
    }
    if (query_ranger_rank(2) < 0)
    {
        if (co == 0)
            return "Unready Ranger pupil";
        else return "illoyal member"
               + STD_TITLE[co] + query_company();
    }
    mtask = player->query_skill(SS_MASTER_TASK);
    if (mtask > 0)
    {
        if (TO->query_master_ranger())
            return ("Master " + MASTER_TITLES[mtask])
              + STD_TITLE[co] + query_company();
        else
        {
            rprt = query_ranger_rank(2);
            if (rprt < 0)
                rprt = 0;
            rprt = rprt/5;
            if (rprt >= sizeof(SUB_MASTER_TITLES[mtask]))
                rprt = sizeof(SUB_MASTER_TITLES[mtask]) - 1;
            return (SUB_MASTER_TITLES[mtask][rprt] + " " +
              MASTER_TITLES[mtask] + STD_TITLE[co] + query_company());
        }
    }
    /* Perhaps a Pupil of the Rangers? */
    if (co == 0)
    {
        rprt = COMP_REQUIREMENT / sizeof(PUPIL_TITLES);
        avg_stat = avg_stat / rprt;
        if (avg_stat >= (sizeof(PUPIL_TITLES) - 1))
        {
            if ((player->query_stat(SS_OCCUP) > COMP_REQUIREMENT)
                && (query_ranger_rank(2) >= PUP_RANK_REQUIREMENT))
                avg_stat = sizeof(PUPIL_TITLES) - 1;
            else
                avg_stat = sizeof(PUPIL_TITLES) - 2;
        }
        return PUPIL_TITLES[avg_stat] + " Ranger pupil";
    }
    /* Perhaps a Legend of the Rangers? */
    if ((co > 0) && query_ranger_legend())
        return "Legend" + STD_TITLE[co] + query_company();
    
    rprt = MASTER_RANK / sizeof(MALE_TITLE);
    avg_stat = avg_stat - (COMP_REQUIREMENT/6);
    avg_stat = avg_stat / rprt;
    if (avg_stat >= sizeof(MALE_TITLE))
        avg_stat = sizeof(MALE_TITLE) - 1;

    return ((player->query_gender() == G_FEMALE) ? FEMALE_TITLE[avg_stat] :
         MALE_TITLE[avg_stat]) + STD_TITLE[co] +
         query_company();
}
