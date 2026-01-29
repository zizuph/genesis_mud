/* vamp_desc.c created by Shiva@Genesis
 *
 * This file contains code related to descriptions received
 * by those interacting with a vampire and descriptions
 * received by the vampire himself.
 *
 * This is part of the vampire guild shadow
 */

#include "../guild.h"
#include "../voptions.h"
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <files.h>
#include <const.h>
#include <formulas.h>

#define SCAR_TIME   (2 * 24 * 60 * 60)

static private string ptitle;
static private string vamp_title;
static private int obscured;
static private int unseen_level;
static private int scar = -1;

static private string *dark_arr = 
    ({ 
      "The area is covered in a blanket of darkness.\n",
      "The area is submerged deep in a pool of darkness.\n",
      "The area is engulfed in a sea of darkness.\n"
    });

static private string *light_arr = 
    ({ 
      "The area is bathed in soft light.\n",
      "The area is brightly illuminated.\n",
      "The area is overwhelmed with brilliant light.\n"
    });

/*
 * Function name: light_desc
 * Description:   Return a string describing the light level (OBJ_I_LIGHT) in
 *                the environment.
 * Arguments:     object env - the environment to check
 * Returns:       string description
 */
varargs string
light_desc(object env)
{
    int light_lvl;
    string *desc_arr, light_desc;

    if (!env)
    {
        env = environment(SW);
    }

    /* If "_room_s_light_desc" is set, just use that */
    if (!stringp(light_desc = env->query_prop("_room_s_light_desc")))
    {
        /* Figure out the description based on OBJ_I_LIGHT */

        light_lvl = env->query_prop(OBJ_I_LIGHT);

        desc_arr = (light_lvl < 1 ? dark_arr : light_arr);

        light_lvl = (light_lvl > 0 ? light_lvl-- : -light_lvl);
        light_lvl = MIN(light_lvl / 2, sizeof(desc_arr) - 1);
        light_desc = desc_arr[light_lvl];
    }
    
    return light_desc;
}

/*
 * Function name: sunlight_desc
 * Description:   Return a string describing the sunlight level 
 *                ("_room_i_sunlight") in the environment.
 * Arguments:     object env - the environment to check
 * Returns:       string description
 */
varargs string
sunlight_desc(object env)
{
    string sunlight_desc, str;
    int sunlight_lvl;

    if (!env)
    {
        env = environment(SW);
    }

    if (!stringp(sunlight_desc = env->query_prop("_room_s_sunlight_desc")))
    {
        sunlight_lvl = query_sunlight_level(env);

        if (!sunlight_lvl)
        {
            return "The area is sheltered from the sun's rays.\n";
        }

        switch (sunlight_lvl)
        {
            case 1..5:
                str =  "faint";
                break;
            case 6..10:
                str = "weak";
                break;
            case 11..20:
                str = "normal";
                break;
            case 21..30:
                str = "bright";
                break;
            default:
                str = "blazing";
                break;
        }

        return "The area is exposed to " + str + " sunlight.\n";
    }

    return sunlight_desc;
}
       
/*
 * Function name: query_met
 * Description:   Determine if this vampire knows a given living.
 * Arguments:     as for query_met() in /std/living.c
 * Returns:       1 if the given living is a vampire
 *                as for query_met() in /std/living.c, otherwise.
 */
int
query_met(mixed nuts)
{
    object ob;
  
    if (stringp(nuts))
    {
        ob = find_player(nuts);
    }
    else if (!objectp(nuts))
    {
        return SW->query_met(nuts);
    }
    else
    {
        ob = nuts;
    }
  
    if (ob && !QP(ob, LIVE_I_NEVERKNOWN) && IS_MEMBER(ob))
    {
        return 1;
    }
  
    return SW->query_met(nuts);
}

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
  
    if (SW->query_wiz_level())
    {
        vamp_title = ptitle = "";
        return;
    }

    if (query_vamp_coven() == ROGUE_VAMPIRE)
    {
        string sire;

        if (strlen(sire = query_sire()))
	{
            ptitle = "Childe of " + capitalize(sire);
        }
        else
	{        
  	    ptitle = ((SW->query_gender() == G_FEMALE) ? "Mother" : "Father") +
                " of All Vampires";
	}

        vamp_title = "Rogue Vampire";

        return;
    }

    setuid();
    seteuid(getuid());
  
    if (!(ptitle = MANAGER->query_personal_title(SW)))
    {
        ptitle = "";
    }
  
    if (sizeof(gtitles = MANAGER->query_guild_titles(query_vamp_coven())))
    {
        /* The first title in the array should be the title for the
         * covenmaster
         */
        if (query_guild_leader_occ())
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
        vlevel = query_vamp_stat() - MANAGER->query_tmp_power_offset();
    
        if (sizeof(gtitles) == 1)
        {
            vamp_title = gtitles[0];
            return;
        }

        top = MANAGER->query_max_level(query_vamp_coven());

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
 * Description:   Get this vampire's coven title
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
 * Description:   Get this vampire's guild title, coven and personal
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
 * Function name: query_guild_title_occ
 * Description:   This is called to get the guild title for introductions
 *                and such.
 * Returns:       The title.
 */
string
query_guild_title_occ()
{
    /* Update the title on occasion in case the vampire has gained a level
     * recently.
     */
    if (!random(30))
    {
        update_title();
    }

    /* We only want the titles to be revealed when it is the
     * vampire himself performing the action (introduce, who, etc.).
     * All others who are accessing the title should see no title.
     */
    if ((this_interactive() == this_player()) &&
        (this_player() == SW))
    {
	if (query_vamp_option(VOPT_INTRO_TITLE))
	{
	    if (query_vamp_option(VOPT_INTRO_PTITLE))
	    {
		return query_full_vamp_title();
	    }
    
 	    return query_vamp_title();
	}
    
	if (query_vamp_option(VOPT_INTRO_PTITLE))
	{
	    return query_personal_title();
	}
    }

    return "";
}

/*
 * Function name: do_glance
 * Description:   Called to make this vampire look around.
 *                We add a special description of the light level
 *                in the environment to the standard room description.
 * Arguments:     as do_glance() in /std/living.c
 * Returns:       as do_glance() in /std/living.c
 */
int
do_glance(int brief)
{
    if (!CAN_SEE_IN_ROOM(SW))
    {
        return SW->do_glance(brief);
    }

    if (query_vamp_option(VOPT_NOTIFY_LIGHT))
    {
        tell_object(SW, light_desc());
    }

    if (query_vamp_option(VOPT_NOTIFY_SUNLIGHT))
    {
        tell_object(SW, sunlight_desc());
    }

    return SW->do_glance(brief);
}

/*
 * Function name: update_scars
 * Description:   Remove a vampire's scars
 */
public void
update_scars()
{
    int t, rand_scar;

    setuid();
    seteuid(getuid());

    scar = MANAGER->query_scars(SW);

    if (!scar)
    {
        return;
    }

    t = MANAGER->query_scar_age(SW);

    if (!t || ((SW->query_age() - t) > SCAR_TIME))
    {
        rand_scar = 1 << random(F_MAX_SCAR);
        if (scar & rand_scar)
	{
            scar ^= rand_scar;
            MANAGER->set_scars(SW, scar);
	}

        MANAGER->set_scar_age(SW, SW->query_age());
    }
}

/*
 * Function name: query_scar
 * Description:   Get an integer value indicating which scars the
 *                vampire has.
 & Returns:       The scars
 */
public int
query_scar()
{
    if (scar == -1)
    {
        update_scars();
    }

    return scar;
}

int
query_guild_incognito_occ() { return 1; }

public int
check_seen(object for_obj)
{
    int seen = SW->check_seen(for_obj);

    if (seen || 
        !IS_MEMBER(for_obj) ||
        SW->query_no_show() ||
        SW->query_wiz_level())
    {
        return seen;
    }

    return 1;
}
