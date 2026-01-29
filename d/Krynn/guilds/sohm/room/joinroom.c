/*
 * Joining Room for the School of High Magic, based on Petros
 * Academics code.  Arman, January 2016
 *
 */

#pragma strict_types

#include "/d/Krynn/solace/poolbottom/local.h"
#include <macros.h>
#include <ss_types.h>
#include <state_desc.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit POOLBOTTOM_IN;
inherit "/cmd/std/command_driver";

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "../remove_all_spells.h"

// Global Variables
public string * beta_testers = ({ "armanjr", "carnakjr","britanicajr", 
                            "varianjr","cherekjrjr", "hollandjr",
                            "gened","genee","genef","geneg",
                            "rockjr"});

object guildmaster, book;
public int guildmaster_busy;

#define SOHM_GUILD_OPEN         0
#define ANTIMODES_ENDORSEMENT   "_sohm_antimodes_endorsement"

public void
reset_poolbottom_room()
{
    // Ensure that the guildmaster is always present
    if (!objectp(guildmaster))
    {
        guildmaster = clone_object(SOHM_GUILDMASTER);
        guildmaster->move(this_object());
        guildmaster->arm_me();        
    }

    if (!objectp(book))
    {
        book = clone_object(EOBJ + "join_book");
        book->move(this_object());       
    }

}

public void
create_poolbottom_room()
{
    set_short("Within the great hall of the school of High Magic");
    set_long("@@long_descr");

    add_item(({"school","Poolbottom","school of high magic"}),
       "You stand within the walls of the school of High Magic that resides "+
       "outside the hamlet of Solace. Here aspirants wanting to learn the "+
       "art of sorcery come to learn and train.\n");

    add_item(({"hall","great hall"}),"You stand within the massive great hall"+
       " of Poolbottom, the school of High Magic. Sandstone walls rise high "+
       "up to the lofty ceiling, broken only by two great windows and twin "+
       "doors to the south. Long tables line the walls, providing students a "+
       "place to study or eat.\n");

    add_item(({"walls","sandstone walls","grey sandstone walls",
               "blocks","sandstone blocks","grey sandstone blocks",
                "high sandstone walls"}),
       "The school has been build from grey sandstone blocks mined from " +
       "quarries far to the south near Pax Tharkas. The workmanship of the " +
       "walls is seamless, most likely done by a master dwarven mason.\n");

    add_item(({"tables","long tables"}),
       "A number of long tables line the walls of the great hall, " +
       "providing students a place where they can study or eat.\n");

    add_item(({"doors","twin doors","double doors"}),
       "Tall double doors of thick oak, strengthened with iron bands, " +
       "stand closed at the southern end of the great hall.\n");

    add_item(({"lectern","wooden lectern"}),
       "Near the twin doors at the southern end of the great hall stands a "+
       "wooden lectern with a leather-bound book sitting open upon it.\n");

    add_item(({"book","leather-bound book"}),
       "A leather-bound book sits open upon the lectern near the twin doors "+
       "at the southern end of the great hall. It provides instructions on "+
       "how to join - or leave - the school of High Magic.\n");

    add_item(({"ceiling","lofty ceiling","high ceiling","roof"}),
        "@@exa_ceiling");

    add_item(({"windows","great windows","window","two great windows",
        "two windows","glass"}), "@@exa_windows");

    add_item(({"torches","torch"}),"@@exa_torches");
    add_item("extinguished torches","@@exa_extinguished_torches");
    add_item("lit torches","@@exa_lit_torches");

    add_exit(ROOM + "ng_hall","north","@@enter_school");
    add_exit(ROOM + "poolbottom_path3","south","@@exit_doors");
   
    reset_poolbottom_room();
  
}

public void
init()
{
    ::init(); 
    add_action("enroll", "enroll"); 
//    add_action("endorse", "endorse");
}

/*
 * Function: endorse
 * Description: For the opening of the guild, Antimodes
 *              needs to endorse new members until the
 *              guild is formally opened.
 */

int
endorse(string arg)
{
    object * oblist;

    if(!TP->query_wiz_level() && TP->query_real_name() != "antimodes")
        return 0;

    if (!arg || sscanf(arg, "%s", arg) != 1)
    {
        notify_fail("Endorse whom?\n");
        return 0;
    }

    oblist = parse_this(arg, "%o");

    if (!sizeof(oblist))
    {
        notify_fail("Endorse what?\n");
        return 0; 
    }

    if(oblist[0]->query_prop(ANTIMODES_ENDORSEMENT))
    {
        notify_fail("Already endorsed.\n");
        return 0; 
    }

    oblist[0]->add_prop(ANTIMODES_ENDORSEMENT, 1);

    write("You say: I bring this aspirant to you Theobald " +
       "for training in the Arts.\n");
    say(QCTNAME(TP) + " says: I bring this aspirant to you " +
       "Theobald for training in the Arts.\n");
    set_alarm(1.0,0.0, &guildmaster->command("say Hmm. Very " +
       "well."));
    return 1;
}


/*
 * Function:    leave_guild
 * Description: Function to remove someone from the guild.
 */
public int 
leave_guild(object player) 
{ 
    if (!IS_MEMBER(player))
    {        
        return 0;
    }
    
    // Remove the person's occupational guild
    if (!player->remove_guild_occ()) 
    { 
        return 0; 
    } 

    // Clear guild stat, remove guild learn, and begin skill decay
    // Guild stat not cleared if you have successfully passed the Test
    if (!SOHM_MANAGER->query_passed_wohs_test(player))
    {
       player->clear_guild_stat(SS_OCCUP); 
       player->setup_skill_decay(); 
       player->set_guild_pref(SS_OCCUP, 0);
    }

    // Remove all spells from memory and spellbook, 
    // defined in remove_all_spells.h excluding when they are 
    // promoting up to the WoHS after completing the Test.

   if (!SOHM_MANAGER->query_passed_wohs_test(player))
    remove_all_spells(player);

    // Reset the start location of the person leaving the guild
    if (player->query_default_start_location() == (SOHM_STARTROOM))
    {
        player->set_default_start_location(player->query_def_start());
    }

    // Remove the command soul
    player->remove_cmdsoul(SOHM_SOUL);
    player->remove_cmdsoul(SOHM_SOULS + "common_spell_soul");
    player->update_hooks();
    
    // Remove the guild object
    object guild_object = present("sohm_guild_object", player);
    if (objectp(guild_object))
    {
        guild_object->remove_object();
    }
    
    // Update the Guild Manager
    SOHM_MANAGER->remove_member(player);
    
    return 1; 
}

/*
 * Function:    join_guild
 * Description: Function to add someone to the guild
 */
public int
join_guild(object player)
{
    // Add Guild Shadow
    setuid();
    seteuid(getuid());

    object guild_shadow = clone_object(SOHM_SHADOW);
    int shadow_result = guild_shadow->shadow_me(player, GUILD_TYPE, 
                        GUILD_STYLE, GUILD_NAME);
    switch (shadow_result)
    {
    case -4:
        player->catch_tell("You can't join the School of High Magic while you "
            + "currently have an occupation. Come back when you are ready to "
            + "commit to the life of a Magi, then return and try again.\n");
        return 0;
    
    case 1:
        // Everything is fine. Autoshadow should have been added as well.
        break;
    
    default:
        player->catch_tell("An error occurred in the fabric of space "
            + "and you are not able to join the School of High Magic. "
            + "Please contact the guildmaster for help.\n");
        return 0;
    }



    // Clear the guild stat, in case it wasn't cleared, and add necessary
    // skill decay and guild tax.
    player->setup_skill_decay(); 
    player->clear_guild_stat(SS_OCCUP); 
    player->set_guild_pref(SS_OCCUP, GUILD_TAX_INITIATE); 

    // In case they are rejoining after being kicked and didn't have their 
    // spells cleared originally.  They start again from scratch.
    // Remove all spells from memory and spellbook, 
    // defined in remove_all_spells.h
    remove_all_spells(player);

    // Add the member to the Guild Manager
    SOHM_MANAGER->add_member(player);
    
    return 1;    
}

public void
remove_join_confirm_prop(object player)
{
    player->remove_prop(SOHM_I_CONFIRM_JOIN);
}

int
reset_guildmaster_busy()
{
     guildmaster_busy = 0;
}

public void
display_join_sequence()
{
    object player = this_player();
    object dialogue_stun = clone_object(SOHM_OBJS + "theobald_dialogue_stun");

    guildmaster_busy = 1;
    write("You enroll yourself to the school of High Magic.\n");
    player->catch_msg(QCTNAME(guildmaster) + " scrutinizes you doubtfully " +
                      "as you enroll.\n");

    dialogue_stun->move(player);

    tell_room(environment(player), QCTNAME(guildmaster) + " scrutinizes "
        + QTNAME(player) + " as " + player->query_pronoun() + " enrolls "
        + "as a student of High Sorcery.\n", ({ player }));
    set_alarm(1.5,0.0, &guildmaster->command("say As you sign up to my " +
              "school, be forewarned!"));
    set_alarm(1.5,0.0, &guildmaster->command("gesture dramatically"));
    set_alarm(4.0,0.0, &guildmaster->command("say Realise magic will not solve " +
        "your problems. It will only add to them."));
    set_alarm(8.0,0.0, &guildmaster->command("say Magic will not make people " +
        "like you. It will only increase their distrust."));
    set_alarm(12.0,0.0, &guildmaster->command("say Magic will not be a balm for " +
        "pain. It will twist and burn inside you until sometimes you " +
        "think that even death would be preferable."));
    set_alarm(16.0,0.0, &guildmaster->command("say But a mage's soul can only " +
        "be forged in the crucible of magic..."));
    set_alarm(20.0,0.0, &guildmaster->command("say And you have now chosen " +
        "to go voluntarily into that fire."));
    set_alarm(21.0,0.0, &guildmaster->command("smile grimly"));
    set_alarm(24.0,0.0, &guildmaster->command("say The blaze might well destroy " +
        "you... but if you survive, every blow of the hammer will serve " +
        "to shape your being."));
    set_alarm(25.0,0.0, &player->catch_msg(QCTNAME(guildmaster) + " gives you " +
        "a leather-bound spellbook.\n"));
    set_alarm(25.0,0.0, &tell_room(environment(player), QCTNAME(guildmaster) + 
        " gives "+ QTNAME(player) + " a leather-bound spellbook.\n", ({ player })));
    set_alarm(27.0,0.0, &guildmaster->command("say This is your spellbook. It " +
        "is the beginning of your path to becoming Magi."));
    set_alarm(31.0,0.0, &guildmaster->command("say It is empty now, but in time " +
        "it will be your most treasured possession filled with spells of " +
        "power you have scribed and mastered."));
    set_alarm(35.0,0.0, &guildmaster->command("say But let us not get ahead of " +
        "ourselves..."));
    set_alarm(39.0,0.0, &guildmaster->command("say Make your way to the library " +
        "and begin your studies!"));
    set_alarm(39.5,0.0, &guildmaster->command("point north"));
    set_alarm(43.0,0.0, &guildmaster->command("say Your first task, master the " +
       "mental exercise that will allow you to understand the taxing runes " +
       "of magic."));
    set_alarm(47.0,0.0, &write("You are now a student of the School of High Magic!\n\n"));
    set_alarm(47.0,0.0, &write("For general help on the guild, read <help sohm>.\n"));
    set_alarm(47.0,0.0, &tell_room(environment(player), QCTNAME(player) + " is now a "
        + "student of the School of High Magic!\n", ({ player })));
    set_alarm(47.5,0.0, &reset_guildmaster_busy());

}

public int
enroll(string str)
{
    object player = this_player();
    string race_name = player->query_race_name();

    if (IS_MEMBER(player))
    {
        notify_fail("You are already a member of the school "
            + "of High Magic!\n");
        return 0;
    }
   
    if (!objectp(guildmaster) || environment(guildmaster) != this_object())
    {
        notify_fail("The guildmaster must be present for you to join!\n");
        return 0;
    }

    if(guildmaster_busy)
    {
        notify_fail("Master Theobald is currently in the process of " +
           "enrolling another student. Be patient until he finishes.\n");
        return 0;
    }


    if(IN_ARRAY(race_name, SOHM_INELIGIBLE_RACES))
    {
        notify_fail("Master Theobald will not train a " +race_name+ " at the "+
            "school of High Magic.\n");
        return 0;
    }
    

    if (strlen(player->query_guild_name_occ()))
    {
        notify_fail("You can't join the school of High Magic while you "
            + "currently have an occupation. Come back when you are ready to "
            + "commit to the life of a Magi, then return and try again.\n");
        return 0;
    }

    if (player->query_average_stat() < SD_AV_APPRENTICE)
    {
        notify_fail("Until you reach the mortal rank of 'wanderer' you " +
            "cannot join the school of High Magic. Until then, consider " +
            "learning the magic craft from the Academics in Gelan.\n");
        return 0;
    }
    
/*  Guild now open! Dec-16

    if (!player->query_wiz_level() 
        && !player->query_prop(ANTIMODES_ENDORSEMENT))
    {
        notify_fail("Sorry, the school of High Magic is currently only open "
            + "to select applicants. Please try again later.\n");
        return 0;
    }
*/

    // SoHM who are banned from casting, or were kicked out cannot
    // join for the duration of their restrictions
    if (SOHM_MANAGER->is_join_restricted(player)
        || SOHM_MANAGER->is_casting_banned(player))
    {
        notify_fail("Your past behaviours prevent you from being able "
            + "to rejoin the school. You will need to wait for some "
            + "time before you will be allowed back into the guild.\n");
        return 0;
    }
    
    if (player->query_prop(SOHM_I_CONFIRM_JOIN))
    {
        notify_fail("To confirm that you wish to join the school of "
            + "High Magic, again <enroll in school of high magic>.\n");
    }
    else
    {
        notify_fail("Do you wish to <enroll in school of high magic> "
            + "and join the School of High Magic?\n");
    }
    
    if (!strlen(str))
    {
        return 0;
    }
    
    
    switch (str)
    {
    case "in school of high magic":
        if (player->query_prop(SOHM_I_CONFIRM_JOIN))
        {
          player->remove_prop(SOHM_I_CONFIRM_JOIN);
          if (join_guild(player))
          {
              if(SOHM_MANAGER->query_renegade_wohs(player))
              {
                 write("\n\nIn re-enrolling in the School of High Magic, " +
                   "your slate as a renegade is wiped clean.\n\n");
                 SOHM_MANAGER->remove_renegade_wohs(player);
              }

              display_join_sequence();
          }
          return 1; 
        }
        write("To confirm that you wish to join the School of High Magic, "
            + "again <enroll in school of high magic> in the next minute.\n");
        player->add_prop(SOHM_I_CONFIRM_JOIN, 1);
        set_alarm(60.0, 0.0, &remove_join_confirm_prop(player));
        return 1;   
    }
    
    return 0;    
}


// Room descriptions for joinroom

string
torch_desc()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "lit torches that drive the nighttime shadows up to " +
            "the lofty ceiling above. ";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "extinguished torches. ";
	    break;
    }
    return str;
}

string
window_desc()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "reveal the blackness of night outside. ";
	    break;
	case EARLY_MORNING:
	case MORNING:
	    str = "illuminate the hall with the morning sun. ";
	    break;
	case NOON:
	    str = "illuminate the hall with the midday sun. ";
	    break;
	case AFTERNOON:
	    str = "illuminate the hall with the afternoon sun. ";
            break;
	case EVENING:
	    str = "illuminate the hall with the evening sun. ";
	    break;
    }
    return str;
}

string
lightning_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
    case AUTUMN:
	str = "";
	break;
    case WINTER:
       switch(GET_TIME_STRING)
      {
	case MIDNIGHT:
	case NIGHT:
	    str = "The walls are occasionally illuminated with the flash of "+
                  "lightning from the winter storm outside. ";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "";
        break;
       }
         break;
    }
    return str;
}

string
exa_windows()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
          switch (GET_SEASON)
          {
            case SPRING:
            case SUMMER:
            case AUTUMN:
	        str = "Situated high up on the southern wall of the great " +
                "hall are two great " +
                "windows of glass, revealing the darkness of night beyond.\n";
	        break;
            case WINTER:
	        str = "Situated high up on the southern wall of the great " +
                "hall are two great windows of glass, revealing the " +
                "darkness of night beyond and the occasional " +
                "flash of lightning from the storm raging outside.\n";
                break;
           }
	   break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
          switch (GET_SEASON)
          {
            case SPRING:
	        str = "Situated high up on the southern wall of the great " +
                "hall are two great " +
                "windows of glass, illuminating the hall with the warm " +
                "spring rays of the sun.\n";
            case SUMMER:
	        str = "Situated high up on the southern wall of the great " +
                "hall are two great windows of glass, illuminating the " +
                "hall with the hot summer rays of the sun.\n";
	        break;
            case AUTUMN:
	        str = "Situated high up on the southern wall of the " +
                "great hall are two great windows of glass, illuminating " +
                "the hall with the warm autumn rays of the sun.\n";
	        break;
            case WINTER:
	        str = "Situated high up on the southern wall of the great " +
                "hall are two great windows of glass, illuminating the hall " +
                "with the cool winter rays of the sun.\n";
                break;
           }
	    break;
    }
    return str;
}

string
exa_extinguished_torches()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "Looking along the wall, you notice no torch is lit. " +
                  "Sensible, seeing it is not night and the great windows " +
                  "above you let in plenty of natural light.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "Unlit torches line the walls of the great hall, ready " +
            "to be lit with the " +
            "darkness that comes with nightfall.\n";
	    break;
    }
    return str;
}

string
exa_lit_torches()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "The walls of the great hall are lined with lit torches " +
            "that dance brightly, casting the shadows of night up " +
            "high to the ceiling, cloaking it in darkness.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "Looking along the wall, you notice no torch is lit. " +
                  "Sensible, seeing it is not night and the great " +
                  "windows above you let in plenty of natural light.\n";
	    break;
    }
    return str;
}

string
exa_torches()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "The walls of the great hall are lined with lit torches " +
            "that dance brightly, casting the shadows of night up high to " +
            "the ceiling, cloaking it in darkness.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "Unlit torches line the walls of the great hall, ready " +
            "to be lit when darkness comes with nightfall.\n";
	    break;
    }
    return str;
}

string
exa_ceiling()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "You can make out little detail of the ceiling " +
            "above you, it being cloaked with nighttime shadows.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "High above you is the ceiling of the great hall.\n";
	    break;
    }
    return str;
}

int
exit_doors()
{
    write("You push the twin doors open and make your way out of the " +
          "great hall.\n");
    return 0;
}

int
enter_school()
{
    if(TP->query_wiz_level())
        return 0;

    if (!IS_MEMBER(this_player()) && 
        TP->query_guild_name_occ() != "Wizards of High Sorcery")
    {        
        write("The master of Poolbottom stops you from entering any " +
              "further into the school of High Magic.\n");
        return 1;
    }
    return 0;
}

string
long_descr()
{
    return "You stand within the great hall of the school of High Magic, " +
    "Poolbottom. To your north the hall extends further, while to your " +
    "east and west rise high sandstone walls lined with " + torch_desc() +
    "Long tables line the walls of the hall, providing students a place " +
    "to study or eat. To your south stand twin doors, the exit to the " +
    "school, while high above them two great " +
    "windows " + window_desc() + lightning_desc()+ "\n";
}
