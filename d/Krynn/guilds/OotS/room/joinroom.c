/*
 * Joining Room for the Order of the Stars
 * Arman, April 2017
 *
 */

#pragma strict_types

#include "/d/Krynn/tharkadan/local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/OotS/defs.h"

inherit THARK_OUT;
inherit "/lib/skill_raise";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

object guildmaster, b1;
public int guildmaster_busy;

/*
 * Prototypes
 */
public void     set_up_skills();

void
reset_tharkadan_room()
{
    if (!objectp(b1))
    {
        b1 = clone_object(LIVING+ "refugee");
        b1->set_faction("Believers");
        b1->move(this_object());        
    }

    // Ensure that the guildmaster is always present
    if (!objectp(guildmaster))
    {
        guildmaster = clone_object(OOTS_GUILDMASTER);
        guildmaster->move(this_object());
        guildmaster->arm_me();        
    }

}

void
create_tharkadan_room()
{
    setuid();
    seteuid(getuid());

    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"valley","vale","wide vale","protected vale",
        "secluded valley","hopeful vale","centre"}),
        "You stand within a secluded valley rimmed by mountains to " +
        "the north and an ice-free lake to the south. Pines and firs " +
        "grow in abundance here, and scattered beneath the trees " +
        "rise the encampment of refugees from the lands to the north " +
        "who escaped the mines of Pax Tharkas and fled south here to " +
        "what they now call 'the Hopeful Vale'.\n");
    add_item(({"aspen","aspen trees","aspens"}),
        "Native to cold regions with cool summers, aspen trees grow " +
        "in large numbers here.\n");
    add_item(({"lodgepole pine","lodgepole pine trees","pine",
        "pine trees"}), "A thin and narrow-crowned tree also known " +
        "as the twisted pine that is common in alpine regions such as " +
        "the Tharkadan Range.\n");
    add_item(({"fir","fir trees","firs"}),
        "Growing throughout the Tharkadan Range are large " +
        "fir trees, evergreen coniferous trees common to " +
        "mountainous regions.\n");
    add_item(({"trees","tree"}),
        "Pines and firs grow in abundance here in this secluded " +
        "valley.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
        "white","snow-covered land","winters snow","winter's snow"}),
        "@@add_item_forest_snow");
    add_item(({"encampment","tents","nomadic tents"}),
        "The refugee encampment consists largely of nomadic tents of " +
        "Abanasinian design. Considering the barbarians of the plains " +
        "make up a large proportion of the refugees, this doesn't " +
        "surprise you.\n");
    add_item(({"refugees","barbarians"}),
        "You notice the refugees seem to come from a range of " +
        "locations - Abanasinian barbarians, townfolk of Solace and " +
        "Haven, even the odd gully dwarf!\n");

    add_exit(ROOM + "hvale2","north",0);     
    add_exit(ROOM + "hvale1","west",0);
    add_exit(ROOM + "hvale5","east",0);
    add_exit(ROOM + "hvale6","southeast",0);
    add_exit(ROOM + "hvale4","south",0);
   
    reset_tharkadan_room();

    create_skill_raise();
    set_up_skills();  
}

string
short_descr()
{
    return short_hopeful_vale_desc();
}

string
mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
        case SPRING:
        case SUMMER:
    	    str = "mountains ";
	    break;
        case AUTUMN:
        case WINTER:
	    str = "ice-capped mountains ";
	    break;
    }
    return str;
}

string
long_descr()
{
    return "You stand within a secluded valley rimmed by " +
        mountain_desc() + "to the north and an ice-free lake to the " +
        "south. Pines and firs grow in abundance here, and scattered " +
        "beneath the trees rise the encampment of refugees from the " +
        "lands to the north who escaped the mines of Pax Tharkas " +
        "and fled south here to what they now call 'the Hopeful Vale'.\n";
}

public void
init()
{
    ::init(); 
    add_action("convert", "convert"); 
    init_skill_raise();
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
    
    // Remove the person's layman guild
    if (!player->remove_guild_lay()) 
    { 
        return 0; 
    } 

    // Clear guild stat, remove guild learn, and begin skill decay
    player->clear_guild_stat(SS_LAYMAN); 
    player->setup_skill_decay(); 
    player->set_guild_pref(SS_LAYMAN, 0);
    // The penalty for leaving means if you rejoin if you have some
    // work to regain levels.
    player->set_skill(OOTS_GUILD_XP, -100000);

    // Reset the start location of the person leaving the guild
    if (player->query_default_start_location() == (OOTS_STARTROOM))
    {
        player->set_default_start_location(player->query_def_start());
    }

    // Remove the command soul
    player->remove_cmdsoul(OOTS_SOUL);
    player->update_hooks();
    
    // Remove the guild object
    object guild_object = present("oots_guild_object", player);
    if (objectp(guild_object))
    {
        player->command("$remove oots_guild_object");
        guild_object->remove_object();
    }
    
    // Update the Guild Manager
    OOTS_MANAGER->remove_member(player);
    OOTS_MANAGER->remove_oots_god(player);
    OOTS_REMOVE_ALL_REV(player);
    
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

    object guild_shadow = clone_object(OOTS_SHADOW);
    int shadow_result = guild_shadow->shadow_me(player, GUILD_TYPE, 
                        GUILD_STYLE, GUILD_NAME);
    switch (shadow_result)
    {
    case -4:
        player->catch_tell("You can't join the Holy Order of the " +
            "Stars while you have a layman guild.\n");
        return 0;
    
    case 1:
        // Everything is fine. Autoshadow should have been added as well.
        break;
    
    default:
        player->catch_tell("An error occurred in the fabric of space "
            + "and you are not able to join the Holy Order of the Stars. "
            + "Please contact the guildmaster for help.\n");
        return 0;
    }



    // Clear the guild stat, in case it wasn't cleared, and add necessary
    // skill decay and guild tax.
    player->setup_skill_decay(); 
    player->clear_guild_stat(SS_LAYMAN); 
    player->set_guild_pref(SS_LAYMAN, GUILD_TAX); 

    // Add the member to the Guild Manager
    OOTS_MANAGER->add_member(player);

    if(player->query_prop("_suitable_for_branchala"))
    {
       OOTS_MANAGER->set_oots_god(player, "Branchala"); 
       OOTS_ADD_REV(TP,"branchala","the aspect of branchala");
       TP->catch_msg("\n\nThe Song of Life sounds joyfully in your " +
                     "mind, and you are filled with divine clarity as " +
                     "a revelation on the aspect of Branchala " +
                     "manifests to you!\n\n\n");
    }
    else   
    {
       OOTS_MANAGER->set_oots_god(player, "Mishakal");
       OOTS_ADD_REV(TP,"mishakal","the aspect of mishakal");
       TP->catch_msg("\n\nA breathtakingly beautiful woman in sky blue " +
                     "robes radiating an aura of peace and well " +
                     "being appears in your mind, and you are filled " +
                     "with divine clarity as a revelation on the " +
                     "aspect of Mishakal manifests to you!\n\n\n");
    }
    
    return 1;    
}

public void
remove_join_confirm_prop(object player)
{
    player->remove_prop(OOTS_I_CONFIRM_JOIN);
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
    object dialogue_stun = clone_object(OOTS_OBJS + 
        "elistan_dialogue_stun");

    guildmaster_busy = 1;
    write("You convert to the Holy Order of the Stars!\n");

    dialogue_stun->move(player);

    set_alarm(1.0,0.0, &write(C(COMPOSITE_LIVE(guildmaster)) + 
        " removes his medallion of faith and gives it to you. It " +
        "glows comfortingly.\n"));
    set_alarm(1.0,0.0, &tell_room(environment(player), 
        QCTNAME(guildmaster) + " removes his medallion of faith and " +
        "puts it around " + QTPNAME(player) + " neck!\n", ({ player })));
    set_alarm(1.5,0.0, &guildmaster->command("smile warmly"));
    set_alarm(3.5,0.0, &guildmaster->command("say And so you begin a " +
        "journey that will help bring the light of hope back to the " +
        "lands of Krynn in this time of darkness."));
    set_alarm(5.0,0.0, &guildmaster->command("say May the disks of " +
        "Mishakal guide you, and the wisdom of the Gods bless you in " +
        "the days to come!"));
    set_alarm(6.5,0.0, &guildmaster->command("emote puts a hand to his " +
          "neck, and a platinum medallion of faith appears around it!"));
    set_alarm(6.5,0.0, &reset_guildmaster_busy());

}

// Note the join sequence for clerics of Kiri-Jolith is in the room
// ~Krynn/tharkadan/room/ledge15.c, with the join function in
// ~Krynn/tharkadan/obj/praying_stun.c

public int
convert(string str)
{
    object player = this_player();
    string race_name = player->query_race_name();

    if (IS_MEMBER(player))
    {
        notify_fail("You are already a disciple of the Holy Order " +
           "of the Stars!\n");
        return 0;
    }
   
    if (!objectp(guildmaster) || environment(guildmaster) != this_object())
    {
        notify_fail("The guildmaster must be present for you to join!\n");
        return 0;
    }

    if(guildmaster_busy)
    {
        notify_fail("Elistan is currently in the process of " +
           "converting another. Be patient until he finishes.\n");
        return 0;
    }


    if(IN_ARRAY(race_name, OOTS_INELIGIBLE_RACES))
    {
        write("Your race is antithesis to the teachings of the " +
            "Holy Order of the Stars.\n");
        return 1;
    }
    

    if (strlen(player->query_guild_name_lay()))
    {
        notify_fail("You can't join the Order while you are "
            + "currently in a layman guild.\n");
        return 0;
    }
    
    // OoTS who are banned from casting, or were kicked out cannot
    // join for the duration of their restrictions
    if (OOTS_MANAGER->is_join_restricted(player)
        || OOTS_MANAGER->is_casting_banned(player))
    {
        notify_fail("Your past behaviours prevent you from being able "
            + "to rejoin the Order. You will need to wait for some "
            + "time before you will be allowed back into the guild.\n");
        return 0;
    }

    if (player->query_alignment() < 600)
    {
        notify_fail("Your recent actions and deeds do not align with the " +
           "gods of the Holy Order of the Stars. Your attempt to convert " +
           "was half-hearted.\n");
        return 0;
    }

    if (!player->query_prop("_suitable_for_mishakal") &&
        !player->query_prop("_suitable_for_branchala"))
    {
        notify_fail("You haven't been completely inspired to join the " +
            "Holy Order of the Stars yet, perhaps you should have " +
            "Elistan teach you a bit about it first before converting?\n");
        return 0;
    }
    
    if (player->query_prop(OOTS_I_CONFIRM_JOIN))
    {
        notify_fail("To confirm that you wish to convert to the Holy " +
            "Order of the Stars, again <convert to holy order of the " +
            "stars>.\n");
    }
    else
    {
        notify_fail("Do you wish to <convert to holy order of the stars> "
            + "and join the Holy Order of the Stars?\n");
    }
    
    if (!strlen(str))
    {
        return 0;
    }
    
    
    switch (str)
    {
    case "to holy order of the stars":
        if (player->query_prop(OOTS_I_CONFIRM_JOIN))
        {
          player->remove_prop(OOTS_I_CONFIRM_JOIN);
          if (join_guild(player))
          {
              display_join_sequence();
          }
          return 1; 
        }
        write("To confirm that you wish to join the Holy Order of the "
            + "Stars, again <convert to holy order of the stars> in "  
            + "the next minute.\n");
        player->add_prop(OOTS_I_CONFIRM_JOIN, 1);
        set_alarm(60.0, 0.0, &remove_join_confirm_prop(player));
        return 1;   
    }
    
    return 0;    
}

void
set_up_skills()
{
    sk_add_train(SS_SPELLCRAFT, "understand divine spellcraft", 0, 0, 60);
    sk_add_train(SS_ELEMENT_LIFE, "cast life spells", 0, 0, 60);
    sk_add_train(SS_FORM_ABJURATION, "cast protection spells", 0, 0, 60);
    sk_add_train(SS_FORM_TRANSMUTATION, "cast transformative spells", 0, 0, 60);
    sk_add_train(SS_HERBALISM, "find herbs", 0, 0, 60);
    sk_add_train(SS_DEFENCE, "defend yourself", 0, 0, 30);
    sk_add_train(SS_PARRY, "deflect blows with your weapon", 0, 0, 30);
    sk_add_train(SS_WEP_CLUB, "fight with a mace", 0, 0, 45);
}

/*
 * Function name: sk_hook_allow_train
 * Description:   Function called when player tries to do the improve command
 *                Will determine if a player can train skills here.
 *                ( Default is:  yes )
 * Arguments:     object - The player trying to improve/learn
 *                string - The string from sk_improve
 *                verb   - improve or learn typically
 * Returns:       1 - yes (default) / 0 - no
 */

public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    setuid();
    seteuid(getuid());
    // Only allow those who are members to train here.
    if (who->query_guild_name_lay() != GUILD_NAME)
    {
        who->catch_msg("You can train here and learn more about the " +
            "Holy Order of the Stars if you join them!\n");
        return 0;
    }
        
    return 1;
}
