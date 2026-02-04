/*
 *  Riders of Last Guild Shadow
 *  Tomas of Terel  -- April 2000
 *  
 */

#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_lay_sh";

#include "include/guild.h"
#include <ss_types.h>
#include <language.h>
#include <const.h>
#include <stdproperties.h>

#define SW shadow_who

static string *titles = ({
    "Stablekeep of Last",
    "Horseman of Last",
    "Rider of Last",
    "Equestrian of Last",
    "Cavalier of Last",
});


int leave_riders();

private mixed stat_names, title, spurs;

/*
 * Function name: query_guild_tax
 * Description  : Set the initial tax
 */
nomask int
query_guild_tax_lay()
{
    return GUILD_TAX;
}

nomask mixed
query_guild_trainer_lay()
{
    return RIDER_ROOM_DIR + "train";
}

/*
 * Function name: acceptable_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
nomask mixed
acceptable_member(object who)
{
    /* no goblins or undeads */
    if ((who->query_race() == "goblin"))
     {
        return "Goblinkind have no place within the Riders of Last!\n";
     }
    if ((who->query_prop() == "LIVE_I_UNDEAD"))
     {
        return "The Riders of Last are looking for hearty individuals, " +
               "not dead ones.. BEGONE!!";
     }
    if ((who->query_alignment() <= -75))
     {
        return "The Riders of Last does not approve of your alignment!\n";
     }
    return 1;
}

/* Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 *                If we discover a fighter or thief, we will throw
 *                him out
 * Arguments:     ob - the player.
 * Returns:       1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    mixed why;

    if (stringp(why = acceptable_member(ob)))
    {
        tell_object(ob, why);
        set_alarm(2.0,0.0, leave_riders);
    }

    return 1;
}

/* Function name: query_rider_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 * stat * (number of titles) / (MAX_SS_LAYMAN)
 */
int
query_rider_level()
{
    return SW->query_base_stat(8) * NUM_TITLES / MAX_SS_LAYMAN;
}

string
get_title(mixed title)
{
    if (!pointerp(title))
    {
        return title;
    }

    return title;
}

/* Function name: query_guild_title_lay
 * Description:   We change the title of our members depending on their level
 * Returns:       The title
 */
string query_guild_title_lay()
{
   int stat;
   mixed title;

   setuid();
   seteuid(getuid());

   if (COUNCIL_MEMBER(shadow_who->query_real_name()))
   {
       return "Captain of the Riders of Last";
   }

   if (!sizeof(titles))
   {
       return "";
   }

   stat = min(sizeof(titles) - 1, query_rider_level());

   title = titles[stat];

   return get_title(title);
}


/*
 * Function name: query_guild_style_lay
 * Description:   Get the style of this guild
 * Returns:       String describing guild style
 */
string
query_guild_style_lay()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_lay
 * Description:   Get the name of this guild
 * Returns:       String naming guild
 */
string
query_guild_name_lay()
{
    return GUILD_NAME;
}

int
leave_riders()
{
    SW->catch_tell("You are no longer a member of the " +
       "Riders of Last Guild.\n");

    setuid();
    seteuid(getuid());

    SW->remove_cmdsoul(RIDER_SOUL);
    SW->update_hooks();
   SW->setup_skill_decay();

    SW->clear_guild_stat(8);

    filter(deep_inventory(SW), &wildmatch(RIDER_GUILD_EMBLEM + "*") @
        file_name)->remove_object();

    if (SW->query_default_start_location() == RIDER_STARTLOC)
    {
        SW->set_default_start_location(SW->query_def_start());
    }

    SCROLLING_LOG(RIDER_MBR_LOG, capitalize(TP->query_real_name())+ 
       " left the Riders. <--");

    remove_guild_lay();
}

void 
init_rider()
{
    setuid();
    seteuid(getuid());

    if (!sizeof(filter(deep_inventory(SW), 
        &->id(RIDER_GUILD_EMBLEM_ID))))
    {
        clone_object(RIDER_GUILD_EMBLEM)->move(SW, 1);
    }

    SW->add_cmdsoul(RIDER_SOUL);
    SW->update_hooks();

    SCROLLING_LOG(RIDER_MBR_LOG, capitalize(TP->query_real_name())+ 
       " joined the Riders. <--");
}

void
init_lay_shadow(string arg)
{
    set_alarm(1.0, 0.0, init_rider);
}

int add_lay_shadow(object who)
{
    return shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME);
}
