/*
No move object for when someone is praying before the altar

Also includes the join function for the Order of the Stars
for worshippers of Kiri-Jolith

Arman - 2017
*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/OotS/defs.h"

#define AM_PRAYING "_praying_kirijolith_altar"

public int no_command();
int dawn_message = 0;
int time;
object victim;


create_object() 
{
    seteuid(getuid());
    set_name("kirijolith_prayer_no_move_obj");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

init()
{
    ::init();
    add_action("stop_praying","stop");
    add_action("stop_praying","stand");
    add_action("do_all_commands", "", 1);
}


/*
 * Function:    join_guild
 * Description: Function to add someone to the guild
 */
int
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
        player->catch_tell("You can't join the Holy Order of the Stars " +
            "while you have a layman guild.\n");
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
    OOTS_MANAGER->set_oots_god(player, "Kiri-Jolith");
    OOTS_ADD_REV(TP,"kirijolith","the aspect of kiri-jolith");
       player->catch_msg("\n\nHaving completed your Trial of Faith, " +
                         "your mind is filled with divine clarity " +
                         "as a revelation on the aspect of Kiri-" +
                         "Jolith manifests itself to you!\n\n\n");
    player->command("$stop praying");
    return 1;    
}

public int
do_all_commands(string str)
{
    string verb;
    string *not_allowed;

    not_allowed = ({"n","north","s","south","w","west","e","east","nw",
      "northwest","sw","southwest","se","southeast",
      "northeast","ne","u","up","d","down","teleport",
      "mount"});

    if (TP->query_wiz_level())
	return 0;

    verb = query_verb();
    if (member_array(verb, not_allowed) == -1)
	return 0;
    else
	return no_command();

    return 1;
}


int
no_command()
{
    write("You are currently deep in prayer. You can <stop praying> " +
       "at any time if you wish to end your devotions.\n");
    return 1;
}

void
remove_dialogue_no_move(object victim)
{
    remove_object();
}

int
stop_praying(string str)
{
    if(!str || (str != "up" && str != "praying"))
    {
       notify_fail("What? Stop praying, or stand up?\n");
       return 0;
    }

    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->catch_msg("You end your devotions and stand up.\n");
    say(QCTNAME(TP)+ " ends " + HIS(TP)+ " devotions and rises to " + 
         HIS(TP)+ " feet.\n");    
    TP->remove_prop(AM_PRAYING);
    TP->remove_prop(OBJ_M_NO_TELEPORT);

    set_alarm(0.1, 0.0, "remove_dialogue_no_move", TP);
    return 1;
}



void
check_krynn_time(object victim)
{
    object vict = victim; 
    string time = GET_TIME_STRING;

    if(GET_TIMEOFDAY == "night")
    {
       int night_vision = random(10);

       switch(night_vision)
       {
          case 0..6:
             break;
          case 7:
             write("As you kneel in prayer the pantheon of stars above " +
                "seem to move in a procession around you... silent... " +
                "watching...\n");
             break;
          case 8:
             write("As you kneel in prayer you notice in the celestial " +
                "realm above you the absence of two constellations. " +
                "The Queen of Darkness, bringer of war and " +
                "destruction... and the Valiant Warrior, both gone. " +
                "She has come to Krynn, and he has come to fight her.\n");
             break;
          case 9:
             write("As you kneel in prayer the pantheon of stars above " +
                "seem to move in a procession around you. One " +
                "constellation in particular, the Celestial Bison, " +
                "seems to shine more brightly than the other stars.\n");
             break;
          default:
             break;
        }
    }

    if(GET_TIMEOFDAY == "dawn")
    {
      write("As the glow of the sun begins to outline the Tharkadan " +
         "mountain range with its golden light, you notice the stars " +
         "of the constellation of the Celestial Bison shine more " +
         "brightly above you... as if in anticipation.\n"); 
      dawn_message = 1;

      if(((GET_SEASON == WINTER) || (GET_SEASON == AUTUMN)) &&
          (E(vict)->query_snow_cleared() == 0))
      {
         vict->command("$dig snow");
       }
    }
    if((time == "early morning") && (GET_TIMEOFDAY == "day") && 
        dawn_message)
    {
      write("As the sun rises over the Tharkadan mountain range its " +
         "golden light beams down on to the time-worn altar, blindingly " +
         "reflecting off it for a moment.\nWhen your sight recovers, " +
         "you notice a copper medallion of faith now resting atop of " +
         "it!\nYou reverently lift the copper medallion of faith off " +
         "the altar, declaring yourself a disciple of the god of " +
         "courage, heroism and honour!\n"); 
      say("As the sun rises over the Tharkadan mountain range, a ray of " +
          "golden light beams down on the time-worn altar, blindingly " +
          "reflecting off it for a moment. When your sight recovers, " +
          "you notice " +QTNAME(TP)+ " picking up a copper medallion " +
          "from atop the altar.\n");
      dawn_message = 0;
      join_guild(TP);
      return;
    }
    
    set_alarm(100.0, 0.0, "check_krynn_time", victim);

}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
	remove_object();
	return;
    }

    if(!living(to))
    {
	remove_object();
	return;
    }

    victim = to;
    victim->add_prop(LIVE_S_EXTRA_SHORT, ", kneeling in prayer before a " +
        "time-worn altar");
    victim->add_prop(OBJ_M_NO_TELEPORT, 1);
    set_alarm(0.1, 0.0, "check_krynn_time", victim);
}
