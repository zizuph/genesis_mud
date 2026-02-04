/* vamp_desc.c created by Shiva@Genesis
 *
 * This file contains code related to descriptions received
 * by those interacting with a vampire and descriptions
 * received by the vampire himself.
 *
 * This is part of the vampire guild shadow
 *
 * Modifications:
 *   - fixed query_vamp_age to return the correct number of seconds.
 *     it was previously returning heartbeats. September 2009, Petros
 */

#include "../guild.h"
#include "../voptions.h"
#include "../room/travel.h"
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <files.h>
#include <const.h>
#include <formulas.h>

#define SCAR_TIME   (2 * 24 * 60 * 60)


static private int start_age;
static private int start_time;
static private string ptitle;
static private string vamp_title;

public int query_vamp_stat();

/*
 * Function name: update_title
 * Description:   Determine this vampire's guild title
 */
void
update_title()
{
    int vlevel, top;
    string *gtitles;
    float interval;
  
    if (QSW->query_wiz_level())
    {
        vamp_title = ptitle = "";
        return;
    }

    setuid();
    seteuid(getuid());
  
    if (!(ptitle = query_manager()->query_personal_title(QSW)))
    {
        ptitle = "";
    }
  
    if (sizeof(gtitles = query_manager()->query_guild_titles()))
    {
        /* The first title in the array should be the title for the
         * covenmaster
         */
        if (TO->query_guild_leader_occ() && TO->query_vampire())
        {
            vamp_title = gtitles[0];
            return;
        }
    
        if (sizeof(gtitles) < 2)
        {
            vamp_title = "";
            return;
        }
    
        gtitles = exclude_array(gtitles, 0, 0);
        vlevel = query_vamp_stat();
    
        if (sizeof(gtitles) == 1)
        {
            vamp_title = gtitles[0];
            return;
        }

        top = query_manager()->query_max_level();

        // Find the interval between titles then which interval we are in
        if ((interval = itof(top) / itof((sizeof(gtitles) - 1))) == 0.0)
        {
            vlevel = 0;
        }
        else
        {
            vlevel = ftoi(itof(vlevel) / interval);
        }
    
        vamp_title = gtitles[MAX(0, MIN(vlevel, sizeof(gtitles) - 1))];
    }
    else
    {
        vamp_title = "";
    }
}

/* 
 * Function name: query_personal_title
 * Description:   Get this vampire's personal title
 * Returns:       The personal title
 */
string
query_personal_title()
{
    if (!ptitle)
    {
        update_title();
    }
  
    return ptitle;
}

/*
 * Function name: query_vamp_title
 * Description:   Get this vampire's title
 * Returns:       The vampire title
 */
string
query_vamp_title()
{
    if (!vamp_title)
    {
        update_title();
    }
  
    return vamp_title;
}


/*
 * Function name: query_full_vamp_title
 * Description:   Get this vampire's guild and honorary title
 * Returns:       The guild title
 */
string
query_full_vamp_title()
{
    string vt = query_vamp_title();
    string pt = query_personal_title();
  
    return vt + ((strlen(pt) && strlen(vt)) ? ", " : "") + pt;
}

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
  
        if (!(start_age = query_manager()->query_start_age(QSW)))
        {
            query_manager()->set_start_age(QSW, QSW->query_age());
            return 1;
        }
    }
  
    // query_age returns the number in heart beats. To get the actual
    // age in seconds, we need to multiply by 2.
    return 2 * (QSW->query_age() - start_age);
}

int
query_vamp_time()
{
    if (!start_time)
    {
        setuid();
        seteuid(getuid());

        if (!(start_time = query_manager()->query_start_time(QSW)))
        {
            query_manager()->set_start_time(time());
            return 1;
        }
    }

    return time() - start_time;
}

