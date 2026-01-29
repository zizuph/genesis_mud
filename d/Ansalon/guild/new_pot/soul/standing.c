/* Stralle @ Genesis 020106
 *
 * In what standing we are
 */

#pragma strict_types

#include <macros.h>

#ifdef 0
/*

You are blasphemous
You are undevoted
You are perfidious
You are greatly out of touch with Takhisis
You are out of grace with Takhisis
You are disfavoured by Takhisis
You are out of touch with Takhisis
You have some touch with Takhisis
You are in somewhat good standing with Takhisis
You are poorly guided by Takhisis
You are in good standing with Takhisis
(You are in very good standing with Takhisis)
You are guided by Takhisis
You are favourable by Takhisis
You are greatly guided by Takhisis
You are most favourable by Takhisis
You are the Handmaiden of Takhisis


 */
/*
  Praying *
    if (LAST_TIME_PRAYED + 3600 < time())
        ADJUST_STANDING(query_standing(), RND_RANGE(90, 10));
    else
        ADJUST_STANDING(query_standing(), RND_RANGE(-20, 20));
  
  Died *
    ADJUST_STANDING(query_standing(), RND_RANGE(-250, 50));

  Killed knight *
    ADJUST_STANDING(query_standing(),
        RND_RANGE(knight->query_average_stat() / 4, 5))

  Killed good *
    ADJUST_STANDING(query_standing(),
        RND_RANGE(enemy->query_align() / 50, 5);
  
  Killed evil *
    ADJUST_STANDING(query_standing(),
        RND_RANGE(-(enemy->query_align() / 100, 2);

  Poisoned *
    ADJUST_STANDING(query_standing(),
        RND_RANGE(-60, 20));
  
  Promoted *
    ADJUST_STANDING(query_standing(),
        RND_RANGE(PS_GUILD_LEVEL, 20)
  
  Demoted *
    ADJUST_STANDING(query_standing(),
        RND_RANGE(-(PS_GUILD_LEVEL + PS_GUILD_LEVEL/10), 5))
  
  Punished
    ADJUST_STANDING(query_standing(), -20, -50 or -100 depending on severity)

  Removing medallion *
    ADJUST_STANDING(query_standing(), RND_RANGE(-35, 10));

  Wearing medallion *
    ADJUST_STANDING(query_standing(), query_standing() ?
        RND_RANGE(3, 5) : RND_RANGE(-3, 5));

  Casting a spell *
    ADJUST_STANDING(query_standing(), random(8) ?
        RND_RANGE(query_spell_level() * 3, 10) : RND_RANGE(-10, 10));
  
  Failing to cast a spell *
    ADJUST_STANDING(query_standing(), RND_RANGE(-5, 5));
  
  // For all, if done within too short a timeframe (abuse) lower
  // the standing instead
  Perform dissection (emote pdissect) *
    ADJUST_STANDING(query_standing(), RND_RANGE(20, 10));

  _Receieve_ a blessing (emote pbless) *  
    ADJUST_STANDING(query_standing(), RND_RANGE(10, 5));
  
  Challenge someone (emote pchallenge) *
    ADJUST_STANDING(query_standing(), query_standing() ?
        RND_RANGE(10, 5) : RND_RANGE(-10, 5));

  Claim something (emote pclaim) *
    ADJUST_STANDING(query_standing(), RND_RANGE(5, 2));
  
  Crying out (emote pcry) *
    ADJUST_STANDING(query_standing(), query_standing() ?
        RND_RANGE(10, 5) : RND_RANGE(-20, 10));
  
  Displaying the medallion (emote pdisplay) *
    ADJUST_STANDING(query_standing(), query_standing() ?
        RND_RANGE(20, 10) : RND_RANGE(-20, 10));
  
  Greeting someone (emote pgreet) *
    ADJUST_STANDING(query_standing(), target->query_align() < 0 ?
        RND_RANGE(10, 5) : RND_RANGE(-2, 5));
  
  Invoking desire (emote pinvoke) *
    ADJUST_STANDING(query_standing(), query_standing() ?
        RND_RANGE(20, 10) : RND_RANGE(-8, 10));
  
  Musing over someone's death (emote pmuse) *
    ADJUST_STANDING(query_standing(), corpse->query_race() == "human" || "elf" || "half-elf" ?  
        RND_RANGE(20, 10) : RND_RANGE(-30, 10))

  Being nervous about ones actions (pnervous) *
    ADJUST_STANDING(query_standing(), random(3) ?
        RND_RANGE(5, 5) : RND_RANGE(-20, 10));

  Ponder ones suggestion (pponder) *
    ADJUST_STANDING(query_standing(), RND_RANGE(20, 10));

  Praying (ppray) *
    ADJUST_STANDING(query_standing(), RND_RANGE(15, 5));
  
  Raging (prage) *
    ADJUST_STANDING(query_standing(), RND_RANGE(0, 5);

  Smiling (psmile) *
    ADJUST_STANDING(query_standing(), RND_RANGE(5, 2));
*/

varargs string
query_standing_desc(object who, object for_obj, int standing = PS_STANDING_MIN - 1)
{
    string str, desc;

    if (standing == PS_STANDING_MIN - 1)
        standing = who->query_skill(PS_STANDING);

    if (!who)
        who = this_player();
    
    if (objectp(for_obj) && for_obj != who)
        str = QCTNAME(who) + " is ";
    else
        str = "You are ";
    
    switch (standing)
    {
        case PS_STANDING_MIN..-1000:
            desc = "";
            break;
        case -999..-700:
            desc = "";
            break;
        case -699..-500:
            desc = "";
            break;
        case -499..-300:
            desc = "";
            break;
        case -299..-100:
            desc = "";
            break;
        case -99..-40:
            desc = "";
            break;
        case -39..-10:
            desc = "";
            break;
        case -9..10:
            desc = "without standing";
            break;
        case 11..40:
            desc = "";
            break;
        case 41..100:
            desc = "";
            break;
        case 101..300:
            desc = "";
            break;
        case 301..500:
            desc = "";
            break;
        case 501..700:
            desc = "";
            break;
        case 701..1000:
            desc = "";
            break;
        case 1001..PS_STANDING_MAX:
            desc = "the Handmaiden of Takhisis";
            break;
    }
    
    return str + desc;
}
#endif

int
vitals(string arg)
{
    if (stringp(arg))
        return 0;
    
    write(this_player()->query_standing_desc(this_player()) + ".\n");
    /* Return 0 that it tries other function that matched the verb
     */
    return 0;
}
