/*
 * /d/Shire/guild/heralds/shadow/herald_shadow.c
 *
 * Recode of the Herald's guild shadow
 * 3 May 2017 - Arman Kharas 
 *
 * Changes:
 * 2018-11-01 - Cotillion
 * - Fixed runtime in decay corruption on linkdead players
 */

#pragma save_binary

inherit "/std/guild/guild_lay_sh";
#include "../titles.h"
#include "../herald.h"
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define HERALD_KILLS "/d/Shire/herald/log/heraldkill"
#define NPC_KILLS "/d/Shire/herald/log/heraldnpckill"

#define QSW             shadow_who
#define JOINROOM        (HERALD_DIRECTORY + "room/join")
#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"

#define CORRUPTION_LOG   (HERALD_LOGS + "corruption")

public mixed
query_guild_trainer_lay()
{
    return HERALD_GUILD_TRAINER;
}

/*
 * Function name: query_guild_tax_lay
 * Description  : Returns the tax for the guild.
 * Returns      : int - the tax value
 */

nomask public int
query_guild_tax_lay()
{
    return HERALD_GUILD_TAX;
}

nomask public string
query_guild_style_lay()
{
    return HERALD_GUILD_STYLE;

}
/*
 * Function name: query_guild_name_lay
 * Description  : Returns the name of the guild
 * Returns      : string - the name
 */
nomask public string
query_guild_name_lay()
{
    return HERALD_GUILD_NAME;
}

/*
 * Function name: query_herald_level
 * Description  : This function will return the level of the player in this
 *                guild. The level will range from 0 to the number of
 *                titles possible (defined in NUM_TITLES) minus one.
 * Returns      : the level
 */
nomask public int
query_herald_level()
{
    int level = QSW->query_stat(SS_LAYMAN);

    level = ((level * NUM_TITLES) / MAX_SS_LAYMAN) - 1;

    return ((level >= NUM_TITLES) ? (NUM_TITLES - 1) :
      ((level < 0) ? 0 : level));
}


/*
 * Function name: query_guild_not_allow_join_lay
 * Description  : Returns whether we should allow this player to join another
 *                guild if he wants to.
 * Arguments    : player - the player that wants to join
 *                type   - the type of the guild
 *                style  - the styles of the guild
 *                name   - the name of the guild
 * Returns      : 1 - if the player is rejected
 *                0 - if the player is accepted as a member
 */
nomask public int
query_guild_not_allow_join_lay(object player, string type, string style,
  string name)
{
    /* It is a redefinition, so call the original. All tests in the
     * guild are made in the joinroom before we allow the player to
     * join.
     */
    return ::query_guild_not_allow_join_lay(player, type, style, name);
}

/*
 * Function name: query_guild_keep_player
 * Description  : Tests whether we want to keep a player if he logs in.
 * Arguments    : player - the player to check
 * Returns      : 0 - if the player will be kicked out
 *                1 - the player will remain
 */
public int
query_guild_keep_player(object player)
{
    string buffoon;
    buffoon = player->query_race();


    setuid(); seteuid(getuid());
    /* If the player changed his/her race, we kick him/her out.
     */

    if (buffoon == "goblin" || buffoon == "orc" || buffoon == "dwarf")
    {
	write("Only the creations of Eru Illuvatar may serve the Valar.\n");
	call_other(JOINROOM, "remove_player_changed_race", player);
	return 1;
    }

    /* If the alignment of the player is too low, we kick him/her out.
     */
    if (player->query_alignment() < HERALD_GUILD_ALIGN_MIN)
    {
	call_other(JOINROOM, "remove_player_low_alignment", player);
	return 1;
    }

    // Do a check for illegal sub races.
    call_other(JOINROOM, "valid_race_check", player);

    // Do a check for illegal guilds.
    call_other(JOINROOM, "valid_guild_check", player);

    return 1;
}

/*
 * Function name: query_guild_title_lay
 * Description  : This function will return the title for the Heralds.
 * Returns      : string - the title.
 */
nomask public string
query_guild_title_lay()
{
    if(HERALD_MANAGER->query_herald_corruption(shadow_who) > 75)
        return "Fallen Herald of the Valar";

    return TITLES[query_herald_level()] + " of the Valar";
}

/*
 * Function name: show_subloc
 * Description  : This function is called to display the sublocs
 * Arguments    : subloc  - the sublock to check
 *		  on_obj  - Whom the subloc is on
 *		  for_obj - Who wants to know the subloc
 * Returns      : The string to display
 */
public string
show_subloc(string subloc, object on_obj, object for_obj)
{
    /* Since this is a redefinition, call the original if the call was
     * not meant for us.
     */
    if ((on_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) ||
      (subloc != HERALD_GUILD_NAME))
    {
	return QSW->show_subloc(subloc, on_obj, for_obj);
    }

    return (((for_obj == on_obj) ? "You are" :
	(capitalize(on_obj->query_pronoun()) + " is")) +
      " a Herald of the Valar.\n");
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

nomask public void
get_herald_soul(int news)
{
    object robe;

    shadow_who->catch_tell("Greetings, Herald of the Valar!\n");

    if (news)
	shadow_who->catch_tell("There is NEW news about the Heralds of "+
            "the Valar. Type 'help herald news' to read all about it.\n");

    setuid(); 
    seteuid(getuid());

    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(HERALD_GUILD_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();

    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }
    
    // Clone the guild object
    if (!present("_herald_robe_", shadow_who))
    {
        clone_object(HERALD_GUILD_ITEM)->move(shadow_who, 1);
        shadow_who->command("$wear _herald_robe_");
    }    

}

public void 
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    HERALD_GUILD_SOUL->remove_spells(shadow_who);
    
    // We no longer need to remove the mana shadow. 

    // query_top_shadow()->remove_mana_shadow();
        
    ::remove_shadow();
}


/*
 * Function name: check_herald_location
 * Description  : This function checks whether the location the Herald
 *                is in is close to an area of evil with a greater
 *                chance of detection by the Dark Lord's forces.
 * Returns      : a string of locations that have a different likelihood
 *                of detection. These locations are: 
 *                Havens / Civilised (no-low chance)
 *                Rural / Border / Wilds (low chance)
 *                Shadow-lands (medium chance) 
 *                Shadow-Holds (medium-high chance).  
 */

public string
check_herald_location()
{
    // Check if in Middle-Earth
    int in_middle_earth = wildmatch("/d/Shire/*",
        file_name(environment(shadow_who))) || wildmatch("/d/Gondor/*",
        file_name(environment(shadow_who)));

    // Haven locations, such as Rivendell and ranger guildhalls
    int in_haven = wildmatch("/d/Shire/rivendell/room/valley/*",
        file_name(environment(shadow_who))) ||
        wildmatch("/d/Gondor/guilds/rangers/*",
        file_name(environment(shadow_who))) ||
        wildmatch("/d/Shire/herald/*",
        file_name(environment(shadow_who))) ||
        wildmatch("/d/Shire/guild/heralds/*",
        file_name(environment(shadow_who))) ||
        wildmatch("/d/Shire/guild/noldor/*",
        file_name(environment(shadow_who)));

    // Civilised locations, such as Bree, Edoras, and Minas Tirith
    int in_civilised = wildmatch("/d/Shire/bree/rooms/*",
        file_name(environment(shadow_who))) ||
        wildmatch("/d/Gondor/minas/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Gondor/rohan/edoras/*",
        file_name(environment(shadow_who))) ||
        wildmatch("/d/Gondor/pelargir/*",
        file_name(environment(shadow_who)));

    // Rural locations, such as the Shire
    int in_rural = wildmatch("/d/Shire/eastroad/western/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Shire/eastroad/village/*",
        file_name(environment(shadow_who)));

    // Locations that border on to rural or civilised areas,
    // such as the forest around Rivendell
    int in_border = wildmatch("/d/Shire/rivendell/room/forest/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Shire/rivendell/room/trees/*",
        file_name(environment(shadow_who)));

    // Wild locations, such as the Trollshaws
    int in_wilds = wildmatch("/d/Shire/rivendell/room/river/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Shire/common/trollsh/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Shire/misty/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Shire/anduin/west/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Gondor/rhovanion/mirkwood/oldroad/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Gondor/rhovanion/mirkwood/central_forest/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Gondor/rhovanion/mirkwood/north_forest/*",
        file_name(environment(shadow_who)));

    // Shadow-lands, such as southern Mirkwood forest and east Ithilien
    int in_shadow_lands = wildmatch("/d/Gondor/ithilien/dagorlad/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Gondor/rhovanion/mirkwood/south_forest/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Gondor/ithilien/road/*",
        file_name(environment(shadow_who))) || 
        wildmatch("/d/Shire/downs/*",
        file_name(environment(shadow_who)));

    // Shadow-Hold locations, such as Minas Morgul
    int in_shadow_hold = wildmatch("/d/Gondor/morgul/*",
        file_name(environment(shadow_who)));

    if(in_haven)
        return "a safe haven";
    if(in_civilised)
        return "civilised lands";
    if(in_rural)
        return "rural lands";
    if(in_border)
        return "border lands";
    if(in_wilds)
        return "wild lands";
    if(in_shadow_lands)
        return "Shadow lands";
    if(in_shadow_hold)
        return "a Shadow Hold";

    // default location if not defined and in Middle Earth is wild lands
    if(in_middle_earth)
        return "wild lands";

    // If not in Middle Earth
    return 0;
}

/*
 * Function name: check_herald_detection
 * Description  : This function checks the chance of detection depending
 *                on the Heralds location.
 * Returns      : an integer that represents the chance of detection
 *                that ranges from 0 to 100.  
 */

public int
chance_herald_detection()
{
    if(!check_herald_location())
        return 0;

    string location = check_herald_location();
    int chance;

    switch(location)
    {
        case "a safe haven":
          chance = 0;
          break;
        case "civilised lands":
          chance = 1;
          break;
        case "rural lands":
          chance = 2;
          break;
        case "border lands":
          chance = 3;
          break;
        case "wild lands":
          chance = 4;
          break;
        case "Shadow lands":
          chance = 8;
          break;
        case "a Shadow Hold":
          chance = 12;
          break;
        // Default chance is the same as the Wild Lands
        default:
          chance = 4;
          break;
    }

    // HERALD_DEBUG("Herald location: " +location+ ", chance: " +chance+ ".");

    return chance;   
}

/*
 * Function name: dark_lord_detection_message
 * Description  : This function provides the message when detected
 *                by the Dark Lord. Feel free to add more descriptions! 
 */

void
dark_lord_detection_message()
{
    string detect_msg = "";

    if(environment(shadow_who)->query_prop(ROOM_I_INSIDE))
    {
        switch(random(2))
        {
            case 0: 
                detect_msg = "\nA chill wind blows past you, where no " +
                "wind should blow, chilling your blood. It blows around " +
                "you as if seeking something, then disperses as swiftly " +
                "as it came.\n\n";
            break;
            default:
                detect_msg = "For a moment you are stricken! In " +
                "your mind a dark shadow - blacker and darker than " +
                "any that surround you - parts, revealing a flame of " +
                "red and the flicker of a piercing Eye; and then the " +
                "shadow furls and the terrible vision disappears.\n\n";
        }
    }    
    else switch(random(4))
    { 
        case 0:
            detect_msg = "\nIn the east the sky " +
                "seem to darken, as if a dark cloud had risen from " +
                "beneath the horizon. Alarmingly, that cloud seems to " +
                "move rapidly towards you, revealing itself to be a " +
                "great flock of large crow-like black birds - a murder " +
                "of crebain!\n\nCroaking and squawking horribly, the " +
                "flock of crebain circle chaotically above you before " +
                "taking flight back east.\n\n";
            break;
        case 1:
            detect_msg = "\nA long drawn wail is carried to you by the " +
                "wind, like the cry of some evil and lonely creature.\n\n";
            break;
        case 2:
            detect_msg = "For a moment you are stricken! In " +
                "your mind a dark shadow - blacker and darker than " +
                "any that surround you - parts, revealing a flame of " +
                "red and the flicker of a piercing Eye; and then the " +
                "shadow furls and the terrible vision disappears.\n\n";
            break;
        default:
            detect_msg = "\nA long drawn wail is carried to you by the " +
                "wind, like the cry of some evil and lonely creature. " +
                "It ends with a high piercing note, before being " +
                "answered by another cry... fainter and further off, " +
                "but no less chilling to the blood.\n\n";
    }

    tell_room(environment(shadow_who), detect_msg, ({  }) );

    shadow_who->catch_tell("You have a feeling the forces of Shadow " +
        "may be starting to take an interest in your activities.\n");
}

public void
check_herald_detection()
{
    int chance = chance_herald_detection();
    int alarm_val = 4 + random(8);
    int chance_detected = random(100);

    // HERALD_DEBUG("Chance: " +chance+ ", detected: " +chance_detected+ ".");

    if(chance > chance_detected)
    {
        // HERALD_DEBUG("Herald detected by Dark Lord check.");
        set_alarm(itof(alarm_val), 0.0, dark_lord_detection_message);
        return;
    }

    // HERALD_DEBUG("Herald not detected by Dark Lord check.");
}

void
spell_failure_corruption_message()
{
    shadow_who->catch_tell("You feel a discordant thrum through " +
        "your being following your failed attempt at channeling, " +
        "leaving you feeling decidely uneasy.\n");
}

/*
 * Function name: spell_failure_corruption_check
 * Description  : This function checks if the Herald is corrupted from
 *                spell failure.
 */

public void
spell_failure_corruption_check(int cast_time)
{
    // HERALD_DEBUG("Corruption spell failure check for " + 
    //    capitalize(shadow_who->query_real_name()) + 
    //    ", cast time " +cast_time+ ".");

    cast_time = cast_time + 2;

    // 25% chance of spell failure corruption for those
    // who are holy, with the chance increasing depending on
    // alignment.

    if(random(shadow_who->query_alignment()) < 300)
    {
        set_alarm(itof(cast_time), 0.0, spell_failure_corruption_message);
        // HERALD_DEBUG("Corruption increased by 1.");
        ADD_CORRUPTION(shadow_who, 1);
    }
}

/*
 * Function name: decay_corruption
 * Description  : This function allows a chance for corruption values
 *                to be reduced on average every 45 minutes of active 
 *                playtime, with quite a bit of variability.
 */

void
decay_corruption()
{
    int hour = 3600;
    int alarm_check = (random(hour) + random(hour) + random(hour) ) / 2;

    // HERALD_DEBUG("Corruption decay check for " + 
    //    capitalize(shadow_who->query_real_name()) + ".");

    set_alarm(itof(alarm_check), 0.0, decay_corruption);

    send_debug_message("heralds", capitalize(shadow_who->query_real_name())
        + " corruption decay check called.", CORRUPTION_LOG);

    // No corruption, so no need to continue check
    if (!HERALD_CORRUPTION(shadow_who))
        return;

    // Need to check if Herald is idle or linkdead -  
    // if so, no corruption decay.
    if (shadow_who->query_linkdead() || !interactive(shadow_who)) 
    {
        return;
    }

    if(query_idle(shadow_who) > (15 + random(30)))
    {
        // HERALD_DEBUG("Idle called, no decrease in corruption for " + 
        //    capitalize(shadow_who->query_real_name()) + ".");
        return;
    }

    // If pure in heart, higher chance of corruption reduced over time.

    if(shadow_who->query_alignment() > random(1500))
    {
        // HERALD_DEBUG("Corruption reduced by 1.");
        REDUCE_CORRUPTION(shadow_who, 1);

        if (HERALD_CORRUPTION(shadow_who))
        {
	    tell_object(query_shadow_who(), "You feel more focused " +
                "on maintaining your discipline and following the " +
                "path set for you by the Valar.\n");
        }
    }
}

void
start_corruption_decay()
{
    int hour = 3600;
    int alarm_check = (random(hour) + random(hour) + random(hour) ) / 2;
    
    set_alarm(itof(alarm_check), 0.0, decay_corruption);
}

/*
 * Function name: init_lay_shadow
 * Description  : This function is called when a player logs in. It adds
 *                the subloc to the player and make a query to the
 *                joinroom for the family name of the player.
 * Arguments    : string foobar - an init-string if there was any.
 */
nomask public void
init_lay_shadow(string foobar)
{
    int news;

    setuid();
    seteuid(getuid());

    shadow_who->add_subloc(HERALD_GUILD_NAME, this_object());

    if (shadow_who->query_alignment() < 100)
    {
	write("\nServants of Melkor are not allowed in the " +
	    HERALD_GUILD_NAME + ".  If you do not change your ways, you "+
	    "will be expelled.\n\n");
    }

    MEMBER_TRACKER->update_member(shadow_who);

    if (shadow_who->query_login_time() <= file_time(HERALD_NEWS))
    {
	news = 1;
    }
    set_alarm(1.0, 0.0, &get_herald_soul(news));

    // HERALD_DEBUG("Started corruption decay.");
    set_alarm(5.0, 0.0, start_corruption_decay);
}

void 
log_killing(object killed, string whom)
{
    string file, domain;

    file = file_name(environment(query_shadow_who()));
    if((domain = explode(file,"/")[2]) == "SHIRE")
	domain = capitalize(explode(file,"/")[3]);
    write_file(HERALD_KILLS, ctime(time()) + " " +
      query_shadow_who()->query_name() + " killed " +
      killed->query_name() + ", " + LANG_ADDART(whom) + ", in " + 
      domain + ".\n");
    write_file(NPC_KILLS, ctime(time()) + " " +
      query_shadow_who()->query_name() + " killed " +
      killed->query_name() + ", " + LANG_ADDART(whom) + " (" +
      file_name(environment(query_shadow_who())) + ").\n");
}

int
notify_you_killed_me(object killed)
{
    string  killed_race = killed->query_race_name();
    mixed   whom;
    int     align = killed->query_alignment();
    int     align_penalty;

    /* you have to do this in case more than one shadow defines the function, Olorin */
    query_shadow_who()->notify_you_killed_me(killed);
    seteuid(getuid(this_object()));

    // Knights using mercy do not get a corruption penalty

    if (query_shadow_who()->query_merciful())
    {
	return 1;
    }


    if (killed->id("_herald_eagle_") || killed->id("ranger"))
    {
	tell_object(query_shadow_who(), "Your actions aid the forces of " +
            "Shadow and run contrary to the path the Valar have set " +
            "you. You feel yourself drawn closer towards the corrupting " +
            "influence of the Dark Lord!\n");
        ADD_CORRUPTION(query_shadow_who(), 10);
    }
    else if (killed->id("elf") && (killed->query_alignment() > 100))
    {
	tell_object(query_shadow_who(), "Your actions aid the forces of " +
            "Shadow and run contrary to the path the Valar have set " +
            "you. You feel yourself drawn closer towards the corrupting " +
            "influence of the Dark Lord!\n");
        ADD_CORRUPTION(query_shadow_who(), 5);
    }
    else if (killed->id("Cityguard") || killed->id("_gondor_guard") ||
        killed->id("rohirrim"))
    {
	tell_object(query_shadow_who(), "Your actions aid the forces of " +
            "Shadow and run contrary to the path the Valar have set " +
            "you. You feel yourself drawn closer towards the corrupting " +
            "influence of the Dark Lord!\n");
        ADD_CORRUPTION(query_shadow_who(), 5);
    }
    else if (align > 100)
    {
	tell_object(query_shadow_who(), "Your actions aid the forces of " +
            "Shadow and run contrary to the path the Valar have set " +
            "you. You feel yourself drawn closer towards the corrupting " +
            "influence of the Dark Lord!\n");

        align_penalty = min(10, (align / 100));
        ADD_CORRUPTION(query_shadow_who(), align_penalty);
    }
    else if (killed->id("hobbit") && (killed->query_alignment() > 100))
    {
	tell_object(query_shadow_who(), "Your actions aid the forces of " +
            "Shadow and run contrary to the path the Valar have set " +
            "you. You feel yourself drawn closer towards the corrupting " +
            "influence of the Dark Lord!\n");
        ADD_CORRUPTION(query_shadow_who(), 1);
    }

    return 1;
}
