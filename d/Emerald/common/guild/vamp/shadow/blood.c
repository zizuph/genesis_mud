/* blood.c created by Shiva@Genesis.
 * This file contains code related to blood's effect on a vampire.
 * This is a subpart of the vampire guild shadow.
 *
 * Lucius Dec 01 2007: Changed start_thirst so that vamps coming out of
 *                     linkdeath don't suffer bloodless for the time 
 *                     spent linkdead.
 */
#include "../guild.h"

#define SW shadow_who
#define EXCESS_THIRST(who) 20
#define DEFAULT_THIRST_RATE 1100

#define TEMP_LOG_ADD_THIRST

static private int thirst_time;
static private int excess_thirst;
static private int max_thirst;
static private int thirst_off;
static private int thirst_rate = DEFAULT_THIRST_RATE;
static private int last_vamp_stat;

void update_thirst();

static void resolve_excess_thirst(int amnt);
void reset_max_thirst();

/*
 * Function name: query_thirst_rate
 * Description:   Get the rate at which this vampire is gaining
 *                thirst.  This is in seconds per point of thirst.
 * Returns:       The thirst rate in seconds
 */
int query_thirst_rate() { return MAX(0, thirst_rate); }

/*
 * Function name: set_thirst_rate
 * Description:   set the rate at which this vampire gains
 *                thirst.  This is in seconds per point of thirst.
 * Arguments:     int rate - The thirst rate in seconds
 */
void set_thirst_rate(int rate) 
{
    update_thirst(); 
    thirst_rate = rate; 
}

/*
 * Function name: modify_thirst_rate
 * Description:   increment the thirst rate by a given value
 * Arguments:     int i - how much to increment the thirst by
 */
void modify_thirst_rate(int i)
{
    set_thirst_rate(thirst_rate + i);
}
 
/*
 * Function name: reset_thirst_rate
 * Description:   set this vampire's thirst rate to the default
 *                value.
 */
void reset_thirst_rate() 
{ 
    set_thirst_rate(DEFAULT_THIRST_RATE);
}

/*
 * Function name: start_blood
 * Description:   initialize some blood-related variables
 */
static void start_blood()
{
    if (!thirst_time)
    {
        update_thirst();
        resolve_excess_thirst(query_thirst() - query_max_thirst());
    }
}

/*
 * Function name: start_thirst
 * Description:   start this vampire's thirst again after it has
 *                been disabled.
 */
void start_thirst()
{
    update_thirst();
    thirst_off = 0;
    resolve_excess_thirst(query_thirst() - query_max_thirst());
}

/* Function name: stop_thirst
 * Description:   Stop this vampire from gaining any more thirst.
 *                Use start_thirst() to restart it.
 */
void stop_thirst()
{
    update_thirst();  
    thirst_off = 1;
}
  
/* Function name: resolve_excess_thirst
 * Description:   Test to see if this vampire's thirst is high
 *                enough to go into torpor.  If so, start torpor.
 * Arguments:     int amnt - The amount of thirst that this vampire 
 *                           has in excess of max_thirst.
 */
static void resolve_excess_thirst(int amnt)
{
#ifndef NO_TORPOR
    object paralysis;
    int fatigue, max_fatigue, hp, max_hp;
  
    if (SW->query_wiz_level())
    {
        DEBUG(BLOOD, "Wiz check succeeded: resolve_excess_thirst.");
        return;
    }
  
    if (!thirst_off && (amnt > EXCESS_THIRST(SW)))
    {
    	if (excess_thirst)
    	{
	    return;
    	}
    
    	/* update hitpoints and fatigue */
    	hp = SW->query_hp();
    	fatigue = SW->query_fatigue();
    
    	excess_thirst = 1;
    
    	/* vamp_stats.c will impose a stat cap now.
    	 * Remove hitpoints and fatigue to reflect the new stats.
    	 */
    
    	if (hp > (max_hp = SW->query_max_hp()))
    	{
	    SW->set_hp(max_hp);
    	}
    
    	SW->set_fatigue(0);
    
    	/* update hitpoints and fatigue again, so that new
    	 * stats take effect immediately.
    	 */
    	SW->query_hp();
    	SW->query_fatigue();
    
    	return;
    }
  
    if (excess_thirst)
    {
    	SW->query_hp();
    	SW->query_fatigue();
    
    	excess_thirst = 0;
    
    	SW->query_hp();
    	SW->query_fatigue();
    }
#endif
}

/*
 * Function name: query_excess_thirst
 * Description:   Find out if this vampire is in torpor
 * Returns:       1/0 in torpor/not in torpor
 */
int query_excess_thirst() 
{
#ifdef NO_TORPOR
    return 0;
#else 
    return excess_thirst; 
#endif
}

/*
 * Function name: set_thirst
 * Description:   Set this vampire's current thirst
 * Arguments:     int amnt - The amount of thirst
 */
void set_thirst(int amnt)
{
    int thirst = MIN(MAX(0, amnt), 300);
  
    update_thirst();
    SW->set_skill(SS_VAMP_THIRST, thirst);
    resolve_excess_thirst(thirst - query_max_thirst());
}

/*
 * Function name: add_thirst
 * Description:   Add thirst to this vampire
 * Arguments:     int amnt - The amount to add
 */
void add_thirst(int amnt)
{
#ifdef TEMP_LOG_ADD_THIRST
    /* There have been some strange reports of major blood loss while in
     * areas where thirst should be suspended, especially when the player
     * has gone linkdead.  This logging should help track down the source.
     */
    string cf = calling_function();
    if (thirst_off && (cf != "complete_ability") && (cf != "do_vamp_cmd"))
    {
        setuid();
        seteuid(getuid());
        log_file("vamp_thirst_log", sprintf("%d %s %d (%s)\n",
            time(), shadow_who->query_real_name(), amnt, cf));
    }
#endif

    set_thirst(query_thirst() + amnt);
}

/*
 * Function name: add_thirst_random
 * Description:   add one point of thirst, given a one in r chance
 * Arguments:     int r - the chance to add a point of thirst
 */
varargs void add_thirst_random(int r = 10)
{
    if (!random(r))
    {
        add_thirst(1);
    }
}

/*
 * Function name: update_thirst
 * Description:   Calculate the amount of thirst this vampire
 *                has gained since last checked and add that
 *                amount of thirst.
 */
void update_thirst()
{
    int thirst_increase;
    
    if (thirst_off || !query_thirst_rate() || !thirst_time)
    {
        thirst_time = time();
        return;
    }
  
    thirst_increase = (time() - thirst_time) / query_thirst_rate();
    if (thirst_increase > 0)
    {
        thirst_time += thirst_increase * query_thirst_rate();
        add_thirst(thirst_increase);
    }
}

// Drink a certain amount of blood
void drink_blood(int amnt)
{
    int excess;
  
    update_thirst();
  
    // Thirst above max thirst is easier to reduce
    if ((excess = SW->query_base_skill(SS_VAMP_THIRST) - 
        query_max_thirst()) > 0)
    {
        amnt += (amnt * 2 < excess ? amnt : excess / 2);
    }
  
    add_thirst(-amnt);
}

/*
 * Function name: query_max_thirst
 * Description:   Return the maximum amount of thirst this
 *                vampire may have and still have use of all
 *                normal vampire abilities.
 * Returns:       max thirst
 */
int query_max_thirst()
{
    int vstat = query_vamp_stat();
  
    if (vstat != last_vamp_stat)
    {
        last_vamp_stat = vstat;
        reset_max_thirst();
    }
     
    return max_thirst;
}

/*
 * Function name: reset_max_thirst
 * Description:   Recalculate this vampire's max thirst.
 */
void reset_max_thirst()
{
    int vstat = query_vamp_stat();
    max_thirst = MIN(250, MAX(20, (vstat <= 0 ? 1 : 
        ftoi(pow(itof(vstat * 3), 0.5) * 10.0 + 0.5))));
}

/*
 * Function name: query_thirst
 * Description:   get this vampire's current thirst
 * Returns:       thirst
 */
int query_thirst()
{
    update_thirst();
    return SW->query_base_skill(SS_VAMP_THIRST);
}

/*
 * Function name: thirst
 * Description:   get this vampire's thirst expressed as a percentage
 *                of maximum thirst.
 */
int thirst()
{
    return (100 * query_thirst() / query_max_thirst()); 
}

/*
 * Function name: query_thirst_modifier
 * Description:   gives a value based on this vampire's thirst
 *                level.  It is used as a minus for various tests.
 * Returns:       See above
 */
int query_thirst_modifier()
{
    int t = thirst() - 50;
    return MAX(0, t) / 10 + query_thirst() / 10;
}

/* 		
 * Function name: linkdeath_hook 		
 * Description: This is called when a vampire goes ld. 		
 * It is used to stop a vampire from gaining 		
 * Thirst while ld. 		
 * Arguments: int i - 1 if linkdying 		
 *                    0 if reviving 		
 */ 		
void linkdeath_hook(int i) 		
{
    if (i)
	stop_thirst();
    else
	start_thirst();

    SW->linkdeath_hook(i); 		
}

/*
 * Function name: query_embrace_offset
 * Description:   Returns the base power offset that is passed
 *                on when this vampire creates another.
 */
public int
query_embrace_offset()
{
#ifdef CALC_POWER_OFFSET
    return CALC_POWER_OFFSET;
#else
    int t;
    int offset;
    int time_factor;

    offset = query_power_offset();
    offset = ((offset > 0) ? offset / 2 : offset * 3 / 2);

    offset += query_base_vamp_stat() / 20 - 4;
    
    t = MANAGER->query_last_embrace_time(SW);

    if (t > 0)
    {
        /* It takes 4 months to get back to full power */
        time_factor = 100 * (time() - t) / (60 * 60 * 24 * 30 * 4);
    }
    else
    {
        time_factor = 100;
    }

    if (offset < 0)
    {
        /* A negative offset can be overcome by waiting longer to embrace.
         * The lower the vampire's generation, the more effective this is.
         */
        if (time_factor > 100)
        {
            time_factor = 100 +
                (time_factor - 100) / max(1, query_vamp_generation() - 1);
        }

        offset += offset * (100 - time_factor) / 100;
    }
    else
    {
        offset = offset * min(100, time_factor) / 100;
    }

    return (offset + random(5) - 2);
#endif
}

/*
 * Function name: desc_vamp_thirst
 * Description:   Returns a string describing the vampire's
 *                thirst level.
 */
varargs public string
desc_vamp_thirst(object for_obj = SW)
{
    if (for_obj != SW)
    {
        switch (max(0, thirst() + random(10) - random(10)))
        {
            case 0..10:
                return SW->query_The_possessive_name(for_obj) + 
                    " skin is still warm with the glow of fresh blood.\n";
            case 11..30:
                return SW->query_The_name(for_obj) + 
                    " appears to be well nourished.\n";
            case 31..60:
                return SW->query_The_possessive_name(for_obj) + 
                    " lusterless eyes indicate " + POS(SW) + " need to feed.\n";
            case 61..80:
                return SW->query_The_possessive_name(for_obj) + 
                    " skin is dry and sallow.  " + capitalize(PRO(SW)) +
                    " is obviously in need of blood.\n";
            case 81..90:
                return SW->query_The_name(for_obj) + 
                    " is obviously barely sustained.\n";
            default:
                if (!query_excess_thirst())
                {
                    return SW->query_The_name() + 
                        " is nearly incapacitated by " + POS(SW) + " thirst.\n";
                }
                else
                {
                    return SW->query_The_name() + " is in torpor.\n";
                }
        }
        
        // Shouldn't get here.
        return "";
    }

    switch (thirst())
    {
        case  0.. 10:
            return "The thirst is sated.\n";
        case 11.. 30:
            return "The thirst is barely noticeable.\n";
        case 31.. 60:
            return "The thirst is becoming ever more noticeable.\n";
        case 61.. 80:
            return "The thirst compels you to seek out a victim.\n";
        case 81.. 90:
            return "The thirst torments you, driving you to seek fresh blood.\n";
        case 91..100:
            return "The thirst is nearly overwhelming, compelling you to "+
                "feed.\n";
        default:
            if (query_excess_thirst())
            {
                return "The thirst virtually incapacitates you.\n";
            }

            return "The thirst is overwhelming; you must feed immediately.\n";
    }
}
