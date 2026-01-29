/*
 *  /d/Emerald/common/guild/aod/race_shadow.c
 *
 *  This is the shadow for the Ogre race.
 *
 *  Copyright (c) August 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/guild/guild_race_sh";

#include "defs.h"

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "aod_titles.h"

#define GUILD_SUBLOC  RACE_GUILD_NAME + " subloc"

#define SW shadow_who

static string *titles = ({ "Trainee", "Fighter", "Warrior", });

/* Prototypes */
void remove_race_member();

/* 
 * Function name: query_guild_tax_race
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_race() 
{ 
    return GUILD_TAX_RACE; 
}

/*
 * Function name: query_guild_style_race
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_race()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_race
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_race()
{
    return RACE_GUILD_NAME;
}

/*
 * Function name: acceptable_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
mixed
acceptable_member(object who)
{
    /* currently, no restrictions */
    return 0;
}
      
/* 
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:	  1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    mixed why;

    if (stringp(why = acceptable_member(ob)))
    {
	ob->catch_msg(why);

        /* Normally we would just return 0 here, and the player would be
         * removed from the guild.  We want to make sure a few cleanup
         * actions happen, though, so we'll return 1 here and remove
         * the member ourselves.
         */

        set_alarm(1.0, 0.0, remove_race_member);

        return 1;
    }

    return 1;
}

/* 
 * Function name: query_guild_not_allow_join_race
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_race(object player, string type, string style,
				string name)
{
    /* This checks to make sure that the new guild is not racial */
    if (::query_guild_not_allow_join_race(player, type, style, name))
        return 1;

    return 0;
}

/* Function name: query_guild_level_race
 * Description:   What is the member's level within the guild?
 * Returns:	  int - the level
 */
int
query_guild_level_race()
{
    int     lvl;

    switch(query_shadow_who()->query_race())
    {
        case "human":
            lvl = 0;
            break;
        case "elf":
            lvl = 1;
            break;
        case "hobbit":
            lvl = 2;
            break;
        case "dwarf":
            lvl = 3;
            break;
        case "gnome":
            lvl = 4;
            break;
        case "goblin":
            lvl = 5;
            break;
        default:
            lvl = 6;
            break;
    }

    return lvl;
}


/*
 * Function name: query_guild_title_race
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string 
query_guild_title_race()
{
    return "of the " + AOD_RACE_TITLES[query_guild_level_race()]
         + " Tribe";
}


/*
 * Function name: init_guild_member
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
void
init_guild_member()
{
    object  guild_emblem,
            who = query_shadow_who();
    string  title;

    setuid();
    seteuid(getuid());

    if (who->query_gender() == 1)
    {
        title= AOD_TITLES_FEMALE[AOD_MASTER->compute_title(who)];
    }
    else
    {
        title= AOD_TITLES_MALE[AOD_MASTER->compute_title(who)];
    }

    /* set the sub-race name */
    who->set_race_name("ogre");

    /* clone the guild emblem and move it to the player */    
    if (guild_emblem = clone_object(AOD_RACE_EMBLEM))
    {    
        guild_emblem->move(who, 1);
        set_alarm(1.0, 0.0, &who->command("$wear belt"));
    }

    /* add the guild subloc */
    who->add_subloc(GUILD_SUBLOC, this_object());

    /* set the sub-race name */
    who->set_race_name("ogre");

    /* greet the player */
    who->catch_msg("\n"
      + sprintf("%|80s", "The blessings of Val-Shoreil are upon you,"
      + " mighty Ogre!\n")
      + sprintf("%|80s", "Go forth, and accomplish his Harvest!\n\n"));

} /* init_guild_member */


/*
 * Function name: start_player
 * Description:   This is called when the player logs in.
 */
public void
start_player()
{
    init_guild_member();
    SW->start_player();
}


/* 
 * Function name: add_race_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int add_race_shadow(object who)
{
    int ret = shadow_me(who, "race", "fighter", RACE_GUILD_NAME);

    if (ret == 1)
    {
        init_guild_member();
    }

    return ret;
}


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
public string
show_subloc(string subloc, object me, object for_obj)
{
    object  belt;
    string  str,
            head_desc,
            his,
            for_obj_compare;

    if (subloc != GUILD_SUBLOC)
    {
        return me->show_subloc(subloc, me, for_obj);
    }

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (!(belt = present(AOD_RACE_EMBLEM_ID, SW)))
    {
        return "";
    }

    if (!belt->query_worn())
    {
        return "";
    }

    setuid();
    seteuid(getuid());

    if (belt->query_occupied())
    {
        head_desc = belt->short_func() + ".";

        if (for_obj == me)
        {
            his = "your";
        }
        else
        {
            his = me->query_possessive();
        }
        for_obj_compare = "head of "
            + LANG_ADDART(for_obj->query_nonmet_name()) + ".";

        if (head_desc == for_obj_compare)

        {
            head_desc = "head of yourself!";
        }

        str = "Hanging from " + his + " trophy belt is the blood-smeared "
              + head_desc + "\n";
    }
    else
    {
        if (for_obj == me)
        {
            str = "You have your empty";
            his = "your";
        }
        else
        {
            str = capitalize(me->query_pronoun()) + " has an empty";
            his = me->query_possessive();
        }

        str += " trophy belt tied around " + his + " waist.\n";
    }

    return str;
} /* show_subloc */


/*
 * Function name: remove_race_member
 * Description:   remove this member from the guild
 */
void
remove_race_member()
{
    object emblem, who = query_shadow_who();

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_RACE);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(AOD_RACE_EMBLEM_ID, who))
    {
        emblem->remove_object();
    }

    /* If the player is using our start location, remove it */
    if (who->query_default_start_location() == AOD_STARTLOC)
    {
        who->set_default_start_location(who->query_def_start());
    }

    /* They should no longer be an ogre */
    who->set_race_name(who->query_race());

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_race();
}


/*
 * Function name:        query_guild_family_name
 * Description  :        Give the Ogre his designation among the
 *                       Tribe - similar to a family name, though not
 *                       literally so.
 * Returns      :        int - true so that query_guild_title_race()
 *                             returns the family name and not a normal
 *                             guild title formatting.
 */
public int
query_guild_family_name()
{
    return 1;
} /* query_guild_family_name */


/*
 * Function name:        query_m_in
 * Description  :        we mask this function to give ogres a unique
 *                       entrance message.
 * Returns      :        string - the m_in description
 */
public string
query_m_in()
{
    if (shadow_who->query_prop(LIVE_I_SNEAK) ||
        shadow_who->query_prop(LIVE_O_STEED))
    {
        return shadow_who->query_m_in();
    }

    return "stomps in";
} /* query_m_in */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 * I'm redefining this function to allow ogres to stomp around so loudly
 * that their footfalls echo into adjascent rooms.
 */
public void
enter_env(object dest, object old)
{
    mixed  *exit_array = environment(this_player())->query_exit(),
           *room_array = allocate(sizeof(exit_array) / 3),
           *direction_array = allocate(sizeof(exit_array) / 3);
    int     i, n, d;
    string  stomp_text, direction;

    /* If rooms are not connected by normal exit code, we assume that
     * the player has been teleported somehow, or moved in some non-
     * standard way. So, we don't have them broadcast stomps.
     */
//  if (member_array(file_name(old), exit_array) == -1)
    if (!old || member_array(file_name(old), exit_array) == -1)
    {
        shadow_who->enter_env(dest, old);
        return;
    }

    n = 0;
    for (i = 1; i < sizeof(exit_array); i = i + 3)
    {
        direction_array[n] = exit_array[i];
        room_array[n] = exit_array[i-1];
        n++;
    }

    for (i = 0; i < sizeof(direction_array); i++)
    {
        switch(direction_array[i])
        {
            case "north":
                direction = "the south";
                break;
            case "northeast":
                direction = "the southwest";
                break;
            case "east":
                direction = "the west";
                break;
            case "southeast":
                direction = "the northwest";
                break;
            case "south":
                direction = "the north";
                break;
            case "southwest":
                direction = "the northeast";
                break;
            case "west":
                direction = "the east";
                break;
            case "northwest":
                direction = "the southeast";
                break;
            case "up":
                direction = "below";
                break;
            case "down":
                direction = "above";
                break;
            default:
                direction = "somewhere nearby";
                break;
        }

        if (old) /* sanity check! */
        {
            if (room_array[i] != file_name(old))
            {
                tell_room(room_array[i], "You hear thunderous footfalls"
                  + " approaching from " + direction + ".\n");
            }
        }
    }

    shadow_who->enter_env(dest, old);
} /* enter_env */


/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 *
 * I'm redefining this function to allow ogres to stomp around so loudly
 * that their footfalls echo into adjascent rooms. Also, this can help
 * prevent bouncing with special attacks.
 */
public void
leave_env(object old, object dest)
{
    mixed  *exit_array = old->query_exit(),
           *room_array = allocate(sizeof(exit_array) / 3),
           *direction_array = allocate(sizeof(exit_array) / 3);
    int     i, n, d;
    string  stomp_text, direction;
    object  who = query_shadow_who();

    /* If rooms are not connected by normal exit code, we assume that
     * the player has been teleported somehow, or moved in some non-
     * standard way. So, we don't have them broadcast stomps.
     */
    if (dest)
    {
        if (member_array(file_name(dest), exit_array) == -1)
        {
            who->leave_env(dest, old);
            return;
        }
    }

    n = 0;
    for (i = 1; i < sizeof(exit_array); i = i + 3)
    {
        direction_array[n] = exit_array[i];
        room_array[n] = exit_array[i-1];
        n++;
    }

    for (i = 0; i < sizeof(direction_array); i++)
    {
        switch(direction_array[i])
        {
            case "north":
                direction = "the south";
                break;
            case "northeast":
                direction = "the southwest";
                break;
            case "east":
                direction = "the west";
                break;
            case "southeast":
                direction = "the northwest";
                break;
            case "south":
                direction = "the north";
                break;
            case "southwest":
                direction = "the northeast";
                break;
            case "west":
                direction = "the east";
                break;
            case "northwest":
                direction = "the southeast";
                break;
            case "up":
                direction = "below";
                break;
            case "down":
                direction = "above";
                break;
            default:
                direction = "somewhere nearby";
                break;
        }

        if (dest) /* sanity check! */
        {
            if (room_array[i] != file_name(dest))
            {
                tell_room(room_array[i], "From " + direction + " you hear"
              + " thunderous footfalls fading into the distance.\n");
            }
        }
    }

    /* If AOD_I_CRUSH_STATUS is set to 2 rather than one, that means
     * we are fighting a player, and do not interrupt the special
     * while moving between rooms.
     */
    if (who->query_crush() &&
        who->query_prop(AOD_I_CRUSH_STATUS) == 1 )
    {
        set_alarm(0.5, 0.0, &who->catch_tell(
            "By stomping around, you lose track of how to"
          + " crush your enemy.\n"));
        who->reset_crush();
    }

    who->leave_env(dest, old);
} /* leave_env */


/*
 * Function name:        query_m_out
 * Description  :        we mask this function to give ogres a unique
 *                       exit message.
 * Returns      :        string - the m_out description
 */
public string
query_m_out()
{
    if (shadow_who->query_prop(LIVE_I_SNEAK) ||
        shadow_who->query_prop(LIVE_O_STEED))
    {
        return shadow_who->query_m_out();
    }

    return "stomps off, leaving";
} /* query_m_out */
