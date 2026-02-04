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
#include "../room/travel.h"
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <files.h>
#include <const.h>
#include <formulas.h>

#define SCAR_TIME   (2 * 24 * 60 * 60)


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

public int query_vamp_stat();

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
        env = environment(QSW);
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
        env = environment(QSW);
    }

    if (!stringp(sunlight_desc = env->query_prop("_room_s_sunlight_desc")))
    {
        sunlight_lvl = query_sunlight_level(env);

        if (sunlight_lvl < 1)
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


public string * query_known_flight_locations()
{
    return query_manager()->query_known_flight_locations(QSW);
}

public void set_known_flight_locations(string * list)
{
    query_manager()->set_known_flight_locations(QSW,list);
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
    if (!CAN_SEE_IN_ROOM(QSW))
    {
        return SW->do_glance(brief);
    }

    if (query_vamp_option(VOPT_NOTIFY_LIGHT))
    {
        tell_object(SW, light_desc());
    }

    if (query_vamp_option(VOPT_NOTIFY_SUNLIGHT))
    {
        tell_object(QSW, sunlight_desc());
    }

    string filename=MASTER_OB(ENV(QSW));

    if (sizeof(filter(TRAVEL_LOCATIONS,&operator(==) 
        (filename) @ &operator([]) (,4))))
    {
        if (member_array(filename,query_known_flight_locations())==-1)
        {
            tell_object(QSW,"\nYou feel this would be a good location "+
                "to remember, and take note of it.\n\n");
            set_known_flight_locations(query_known_flight_locations()
            + ({ filename }));
        }
    }
    return QSW->do_glance(brief);
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

    scar = query_manager()->query_scars(QSW);

    if (!scar)
    {
        return;
    }

    t = query_manager()->query_scar_age(QSW);

    if (!t || ((SW->query_age() - t) > SCAR_TIME))
    {
        int scar_pos = random(F_MAX_SCAR);
        rand_scar = 1 << scar_pos;
        if (scar & rand_scar)
	{
            scar ^= rand_scar;
            QSW->catch_msg("The scar on your " + F_SCAR_DESCS[scar_pos] +
            " fades completely away.\n");
            query_manager()->set_scars(SW, scar);
	}

        query_manager()->set_scar_age(QSW, QSW->query_age());
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

public int 
query_guild_incognito_occ()
{
    if (query_vamp_option(VOPT_INTRO_TITLE))
    {
        return 0;
    }
    if (query_vamp_option(VOPT_INTRO_PTITLE))
    {
        return 0;
    }
    return 1;
}


