/*
 */

#include "../guild.h"
#include <math.h>
#include <files.h>

#define FORMULA(x)  (((x)->query_stat(SS_OCCUP) * 2 + \
                        (x)->exp_to_stat((x)->query_skill(PS_SKILL_POINTS)) * 3) / 5 + \
                        GUILD_ADMIN->query_days_in_level((x)->query_real_name()))

#define R_NOPROMO       0
#define R_CLERIC        -1
#define R_PRIEST        -2
#define R_HIGHPRIEST    -3
#define R_LEADER        -4
#define R_DEMOTION      -5
#define R_PROMOTION     -6

int
level2time(object tp)
{
    int glev;
    
    if (!tp->query_skill(PS_GUILD_LEVEL))
        glev = GUILD_ADMIN->query_guild_level(tp->query_real_name());
    else
        glev = tp->query_skill(PS_GUILD_LEVEL);
    
    switch (glev / 10)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            return R_CLERIC;
        case 4:
            return R_PRIEST;
        case 5:
            return 5; // 30
        case 6:
            return 10; // 45
        case 7:
            return 15; // 68
        case 8:
            return 20; // 100
        case 9:
            return R_HIGHPRIEST;
        case 10:
            return 15; // 60
        case 11:
            return 20; // 90
        case 12:
            return 25; // 136
        case 13:
            return 30; // 200
        case 14:
            return R_LEADER;
    }

    return 0;
}

int
query_promotions(object tp)
{
    int gs;

    gs = GUILD_ADMIN->query_promoted(tp->query_real_name());
    if (gs <= 0)
        return R_NOPROMO;
    
    if (gs < tp->query_skill(PS_GUILD_LEVEL))
    {
        /* Demotion */
        tp->adjust_standing(RND_RANGE(-(tp->query_skill(PS_GUILD_LEVEL) +
            tp->query_skill(PS_GUILD_LEVEL) / 10), 5));
        tp->set_skill(PS_GUILD_LEVEL, gs);
        GUILD_ADMIN->clear_promotions(tp->query_real_name());
        GUILD_ADMIN->set_level_age(tp->query_real_name(),
            tp->query_age() * 2);
        return R_DEMOTION;
    }
    else if (gs > tp->query_skill(PS_GUILD_LEVEL))
    {
        if (tp->query_priest_level() < tp->query_priest_level(gs))
        {
            /* Quest */
            switch (tp->query_priest_level(gs))
            {
                case GUILD_LEVEL_PRIEST:
                    return R_PRIEST;
                case GUILD_LEVEL_HIGH_PRIEST:
                    return R_HIGHPRIEST;
            }                    
        }
        else
        {
            /* Cleric promotion */
            tp->adjust_standing(RND_RANGE(tp->query_skill(PS_GUILD_LEVEL), 20));
            tp->set_skill(PS_GUILD_LEVEL, tp->query_skill(PS_GUILD_LEVEL) + 10);
            GUILD_ADMIN->set_guild_level(tp->query_real_name(),
                tp->query_skill(PS_GUILD_LEVEL));
            GUILD_ADMIN->clear_promotions(tp->query_real_name());
            GUILD_ADMIN->set_level_age(tp->query_real_name(),
                tp->query_age() * 2);
            return R_CLERIC;
        }
    }
    else if (tp->query_priest_sublevel() != tp->query_priest_sublevel(gs))
    {
        if (gs >= 140 && GUILD_ADMIN->query_leader() != tp->query_real_name())
        {
            /* Leader */
            return R_LEADER;
        }
    }

    return R_NOPROMO;
}

int
due_in(string name)
{
    int gs, atleast, isn_real;
    object tp;

    if (!(tp = find_player(name)))
    {
        isn_real = 1;
        tp = SECURITY->finger_player(name);
    }

    gs = min(level2time(tp), FORMULA(tp));

    /* We need atleast to be this old in the current lelvel */
    if (gs > 0)
    {
        atleast = (level2time(tp) * 2) / 3 +
            NAME_TO_RANDOM(tp->query_real_name(), 56234878, 5);
        if (atleast > gs)
            gs = atleast;

        return gs - GUILD_ADMIN->query_days_in_level(tp->query_real_name());
    }

    if (isn_real)
        tp->remove_object();

    return gs;
}

int
foobar(object tp)
{
    int gs;
    object scroll;

    if (GUILD_ADMIN->query_leader_absent() &&
        GUILD_ADMIN->query_leadership_claimable(tp->query_real_name()) == 1)
        return R_LEADER;
    
    if (query_promotions(tp) != 0)
        return query_promotions(tp);

    if (level2time(tp) < 0)
        return R_NOPROMO;

    /* We need atleast to be this old in the current lelvel */
    if (GUILD_ADMIN->query_days_in_level(tp->query_real_name()) <
        ((level2time(tp) * 2) / 3 +
        NAME_TO_RANDOM(tp->query_real_name(), 56234878, 5)))
        return R_NOPROMO;
    
    /* Need sufficiant standing (3 top stages) */
    if (tp->query_skill(PS_STANDING) < 501)
        return R_NOPROMO;

    /* We can only have one leader */
    if (tp->query_skill(PS_GUILD_LEVEL) >= 140 &&
        GUILD_ADMIN->query_leader() &&
        GUILD_ADMIN->query_leader() != tp->query_real_name())
        return R_NOPROMO;

    gs = FORMULA(tp);
#ifdef 0
    gs = (tp->query_stat(SS_OCCUP) * 2 +
        tp->exp_to_stat(PS_SKILL_POINTS) * 3) / 5 +
        GUILD_ADMIN->query_days_in_level(tp);
#endif
    
    /* If it works out, we go up one level */
    if (gs > level2time(tp))
    {
        tp->set_skill(PS_GUILD_LEVEL, tp->query_skill(PS_GUILD_LEVEL) + 10);
        GUILD_ADMIN->set_level_age(tp->query_real_name(),
            tp->query_age() * 2);

        if (level2time(tp) == -4)
            return R_LEADER;

        return R_PROMOTION;
    }

    return R_NOPROMO;
}

void
do_rank(object tp)
{
    switch (foobar(tp))
    {
        case R_NOPROMO:
            return;
            break;
        case R_DEMOTION:
            tp->catch_tell("\nYou feel a stabbing at your heart as " +
                "the Queen of Darkness revokes your standing within " +
                "the guild.\n");
            break;
//        case -2:
        case R_PROMOTION:
        case R_CLERIC:
            tp->catch_tell("\nYou feel an inner warmth as the Queen " +
                "Darkness recognises your exploits and grants you a " +
                "higher standing within the guild.\n");
            break;            
        case R_PRIEST:
            tp->catch_tell("\nYou realise you are ready to become a " +
                "Priest.\n");
            tp->add_prop(TMP_POT_DEDICATION_SCROLL, GUILD_LEVEL_PRIEST);
            break;
        case R_HIGHPRIEST:
            tp->catch_tell("\nYou realise you are ready to become a " +
                "High Priest.\n");
            tp->add_prop(TMP_POT_DEDICATION_SCROLL, GUILD_LEVEL_HIGH_PRIEST);
            break;
        case R_LEADER:
            tp->catch_tell("\nA soothing voice in your mind speaks '" +
                "You my child shall be known as the leader of my " +
                "priesthood'\n");
            GUILD_ADMIN->set_leader(tp->query_real_name());
            break;
    }
    
    GUILD_ADMIN->set_guild_level(tp->query_real_name(),
        tp->query_skill(PS_GUILD_LEVEL));
}
