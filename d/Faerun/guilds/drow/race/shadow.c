/*
 * drow/race/shadow.c
 *
 * This is the Shadow for the drow racial guild.
 * remove_guild_race_drow() leaving msg changed to boot ptesters and race changed
 * temporarily to elf to boot them out.
 * 
 * Modifications:
 *   - Fixed leaving code so that it clears the race prefs (no tax).
 *     Petros, May 2009
 *
 *   - Added mana shadow to allow for fairy fire spell inclusion
 *     Arman, Feb 2017
 *
 *   - Added a check to remove mana_shadow for PoT members until they are upgraded
 *     to the new magic system (now removed)
 *     Arman, Feb 2017
 *
 *   - Fixed runtime
 *     2021-05-13 - Cotillion
 */
#pragma no_inherit
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <macros.h>

#include "guild.h"

inherit "/std/guild/guild_race_sh";

//#define ONE_OF_LIST(x)   one_of_list(x)

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define PHRASES     ({  "Vin'ult, C'Rintri!\nMay your deeds this day do tribute to " + GSERVER->query_member_deity(shadow_who)[0] + ".", \
                        "Lil Alurl Velve Zhah Lil Velkyn Uss!\nThe best knife is the unseen one!", \
                        "L'elamshin D'lil Ilythiiri Zhah Ulu Har'luth Jal!\nThe destiny of the drow is to conquer all!", \
                        "Xun Izil Dos Phuul Quarthen, Lueth Dro! \nDo as you are ordered, and live!", "Kyorl Jal Bauth, Kyone, Lueth Lil Quarval-Sharess Xal Balbau Dos Lil Belbol Del Elendar Dro!\nWatch all about, warily, and the Goddess may give you the gift of continued life!"})

// Prototypes
public object   query_top_shadow();

private static string title_string;

public int 
query_guild_tax_race(void)
{ 
    return GUILD_TAX; 
}

public string
query_guild_style_race(void)
{
    return GUILD_STYLE;
}

public string
query_guild_name_race(void)
{
    return GUILD_NAME;
}

public string 
query_guild_title_race(void)
{
    return title_string;
}

/*
 * Constructs the title string and updates the
 * guild object as necessary.
 */
public void
update_member_info_race(void)
{
    string city, house;
    object gobject = present(GOBJECT_NAME, shadow_who);

    city = GSERVER->query_member_city(shadow_who);
    house = GSERVER->query_member_house(shadow_who);

    if (!strlen(house))
    {
	title_string = "Commoner of "+ city;
    }
    else
    {
	mapping dranks = DROW_RANKS;
	string rank = GSERVER->query_house_rank(house, "", shadow_who);

       	title_string  = (strlen(rank) ? dranks[rank][DR_TITLE] : "Commoner");
	title_string += " of House "+ house +" from " + city;
    }

    if (!objectp(gobject))
    {
	gobject = clone_object(GUILD_OBJECT);
	gobject->move(shadow_who, 1);
    }

    gobject->config_object(house);
}

private void
slow_init_race_shadow(void)
{
    string phrase;
    shadow_who->add_cmdsoul(GUILD_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);
    shadow_who->update_hooks();

    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }


    if (!shadow_who->query_ghost())
    {
/*
	tell_object(shadow_who, "\nVin'ult, C'Rintri!  "+
	    "May your deeds this day do tribute to "+
	    GSERVER->query_member_deity(shadow_who)[0] +
	    ".\n\n");
*/
    phrase = ONE_OF_LIST(PHRASES);

	tell_object(shadow_who, "\n" + phrase + "\n\n");

    }

    /* Construct the Guild title. */
    update_member_info_race();
}

public void
init_race_shadow(string arg)
{
    setuid();
    seteuid(getuid());

    /* We are Drow. */
    shadow_who->set_race_name("drow");
    /* This has to be alarmed or bad things happen. */
    set_alarm(2.0, 0.0, &slow_init_race_shadow());
}

public void
remove_object(void)
{
    if (shadow_who)
	GSERVER->update_last_active(shadow_who);

    ::remove_object();
}

/* Frontend to remove_guild_race to handle specific items. */
/* XXX Remember to add in a bit to reset startlocations as necesary */
public varargs void
remove_guild_race_drow(object who, int force)
{
    object gobject = present(GOBJECT_NAME, who);

    /* Clear stat and remove cmdsoul */
    who->clear_guild_stat(SS_RACE);
    who->set_guild_pref(SS_RACE, 0);    
    who->remove_cmdsoul(GUILD_SOUL);
    who->update_hooks();

    /* Did user voluntarily leave? */
    if (force)
    {
	/* Just some spammage so they know why they are being removed. */

    who->catch_tell("\nA malevolent and chaotic presence "+
	    "invades your mind!\n\nFOOL!  Did you really think you "+
	    "could escape Lolth's wrath so easily!?  Well...  "+
	    "think again!!\n\nThe presence inside your mind seems "+
	    "to expand and expand, creating a horrific pressure inside "+
	    "your head.. finally, you can take no more...\n\n");
	who->command("$scream");

//    who->catch_tell("\nPlayer testing of the drow is completed. You have been removed from the guild.\n\n");    
    }

    /* Remove the guild object, if present. */
    if (objectp(gobject))
	gobject->remove_object();

    /* Clear member from server. */
    GSERVER->check_deleted_player(who);

    /* Reset race-name back to 'elf' */
    if (who->query_race_name() == "drow")
	who->set_race_name("elf");    

    /* Time to die. */
   // who->reduce_hit_point(who->query_max_hp() + 10);
//    who->do_die(this_object());

    /* Follow the chain to remove the shadow. */
    who->remove_guild_race();
    remove_guild_race();
}

/* This gets called between the allow_join function
 * and the init_race_shadow one, so take care. */
public int
query_guild_keep_player(object player)
{
    string house, rank;

    setuid();
    seteuid(getuid());

    /* Has the player switched races? */
    if (player->query_race_name() != "elf")
//    if (player->query_race_name() != "goblin")
    {
	    set_alarm(1.0, 0.0, &remove_guild_race_drow(player, 1));
	    return 0;
    }

    /* Has the player switched genders? */
    if (strlen(house = GSERVER->query_member_house(player)) &&
	strlen(rank = GSERVER->query_house_rank(house, "", player)))
    {
	    mapping dranks = DROW_RANKS;
	/* They have, and are no longer suitable for that rank. */
        if (dranks[rank][DR_LIMIT][player->query_gender()] == 0)
        {
            GSERVER->remove_house_rank(house, rank, player);
            /* Silly matron, trying to escape... */
            if (rank == HR_MATRON)
            GSERVER->reorganize_house(house, 0);
        }
    }

    return 1;
}

/*
 * Function name: query_guild_trainer_race
 * Description:   Return one or more references to the object that define
 *                sk_train_max for the player. The returned refernce can
 *                be a string reference, an object pointer or an array of
 *                those.
 * Returns:       See description.
 */
public mixed
query_guild_trainer_race()
{
    return ROOMS_DIR + "train";
}

/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */

public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}

#if 0
/* We do not currently do anything more here. */
public int
query_guild_not_allow_join_race(object player, string type, string style,
    				string name)
{
    if (::query_guild_not_allow_join_race(player, type, style, name))
	return 1;

    return 0;
}
#endif
