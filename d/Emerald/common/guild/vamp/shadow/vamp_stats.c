/* Vamp_stats.c created by Shiva@Genesis.
 * This file contains code related to various guild-related stats
 * This is part of the vampire guild shadow.
 *
 * Lucius 2008: Added routine for resetting power offsets.
 */

#include "../guild.h"
#include <ss_types.h>
#include <macros.h>

#define SW shadow_who
#define STAT_CAP 15

static private int start_age;
static private int offset;
static private int offset_set;
static private int start_time;

/* 
 * Function name: query_vamp_age
 * Description:   Get the amount of game time that this vampire
 *                has been a vampire.
 * Returns:       age in seconds
 */
int
query_vamp_age()
{
    if (!start_age)
    {
        setuid();
        seteuid(getuid());
  
        if (!(start_age = MANAGER->query_start_age(SW)))
        {
            MANAGER->set_start_age(SW, SW->query_age());
            return 1;
        }
    }
  
    return SW->query_age() - start_age;
}

int
query_vamp_time()
{
    if (!start_time)
    {
        setuid();
        seteuid(getuid());

        if (!(start_time = MANAGER->query_start_time(SW)))
        {
            MANAGER->set_start_time(time());
            return 1;
        }
    }

    return time() - start_time;
}

/*
 * Function name: update_power_offset
 * Description:   Reset this vampire's power offset.
 */
void
update_power_offset()
{
    setuid();
    seteuid(getuid());
  
    offset = MANAGER->query_base_power_offset(SW) +
             MANAGER->query_power_offset(SW);
}

/*
 * Function name: query_power_offset
 * Description:   Get this vampire's power offset, which
 *                represents miscellaneous minuses and bonuses
 *                to the vampire's level and abilities.
 * Returns:       The power offset
 */
int
query_power_offset()
{
    if (!offset_set)
    {
        update_power_offset();
        offset_set = 1;
    }
  
    setuid();
    seteuid(getuid());
    return (offset + MANAGER->query_tmp_power_offset(SW));
}

/* 
 * Function name: query_max_vamp_stat
 * Description:   Get the maximum occupational stat of this vampire
 *                based on his/her age.
 * Returns:       See above
 */
int
query_max_vamp_stat()
{
    return min(999, max(query_vamp_age() / 3600,
        query_vamp_time() / 450000) + 10);
}

/*
 * Function name: query_base_vamp_stat
 * Description:   Get this vampire's occupational stat, limited by
 *                max_vamp_stat (see query_max_vamp_stat())
 * Returns:       See above
 */
int
query_base_vamp_stat()
{
  int max = query_max_vamp_stat();
  int occ = SW->query_stat(SS_OCCUP);

  return MIN(occ, max);
}

/*
 * Function name: query_vamp_stat
 * Description:   Get this vampire's base vamp stat, modified by
 *                his/her power offset (see query_power_offset() and
 *                query_base_vamp_stat())
 * Returns:       See above
 */
int
query_vamp_stat()
{
    return max(1, query_base_vamp_stat() + query_power_offset());
}

/*
 * Function name: query_stat
 * Description:   Returns the value of the given stat, possibly 
 *                modified if the vampire is in torpor.
 * Arguments:     The stat to check
 * Returns:       The stat's value.
 */
int
query_stat(int stat)
{
    int level;

    level = SW->query_stat(stat);

    if (stat < SS_NO_EXP_STATS)
    {
        if (query_excess_thirst())
        {
            level = MIN(level, STAT_CAP);
        }
    }

    return level;
}

/*
 * Function name: query_effective_vamp_stat
 * Description:   get the "effective" occupational stat.
 *                This is the base_vamp_stat, modified by
 *                a few minuses and bonuses, including sunlight
 *                modifier, power offset, and thirst.
 * Returns:       See above
 */
int
query_effective_vamp_stat()
{
    int stat, offset, sunmod, thirst;
  
    stat = query_base_vamp_stat();
    offset = query_power_offset();
    sunmod = query_sunlight_modifier();
    thirst = query_thirst_modifier();
  
    offset = (offset < 0 ? -random(offset) : random(offset));
  
    stat = MAX(1, stat - sunmod - thirst + offset);
  
    DEBUG(VAMP_STATS, "Effective stat: " + stat + " (" + 
        query_stat(SS_OCCUP) + ")\n");
  
    return stat;
}

int
query_vamp_generation()
{
    setuid();
    seteuid(getuid());
    return MANAGER->query_generation(SW);
}

void
add_tmp_vamp_stat_mod(int mod)
{
    setuid();
    seteuid(getuid());
    MANAGER->set_tmp_power_offset(SW,
        mod + MANAGER->query_tmp_power_offset(SW));
}

public int
restore_vamp_power(void)
{
    if (MANAGER->query_power_offset(SW) < 0)
    {
	/* Reset perm power penalty first. */
	MANAGER->set_power_offset(SW, 0);
	update_power_offset();
	return 1;
    }

    int cur_off = MANAGER->query_base_power_offset(SW);
    int new_off = CALC_POWER_OFFSET + POWER_MULTIPLIER;

    /* We are at the power level we should be. */
    if (cur_off == new_off)
	return 0;

    int diff1 = new_off / 3;
    int diff2 = (new_off - cur_off) / 3;

    if (diff1 > diff2)
	cur_off = min(new_off, cur_off + diff1);
    else
	cur_off = min(new_off, cur_off + diff2);

    MANAGER->set_base_power_offset(SW, cur_off);
    update_power_offset();

    return 2;
}
