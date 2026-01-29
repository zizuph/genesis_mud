/*                     The Wild Runners Guild Shadow.
 *    This shadow was taken from Tulix's great grunts shadow (It smelt a
 *    bit, but that's besides the point). Thatnks go to tulix for helping
 *    compile the list of titles and for quite a few suggestions.
 *                      Mylos, 20.4.93
 *    Recoded 28/08/95 by Tulix III, gee this code looks familiar....
 * soul and guild objects added by shadow now -- Shiva 12/02/96
 *
 * Updated for Cypress
 * Finwe, June 2001
 * Updated titles, Finwe Jan 2017
 * Updated when titles occur. Was missing 142-152. - Mirandus Feb 2018
 */

inherit "/std/guild/guild_race_sh";

#include "/d/Shire/cypress/sys/defs.h"
#include "/d/Shire/cypress/guilds/wrunner/wrunner_defs.h"
#include <macros.h>
#include <ss_types.h>

#define JOINROOM (WRUNNER_DIR + "rooms/join")


/* The wildrunner titles                        */


#define SERF_LEVELS ({  "Serf", \
                        "Trainee Guard", \
                        "Blooded Guard", \
                        "Promising Scout", \
                        "Dashing Scout", \
                        "Lead Scout", \
                        "Warrior", \
                        "Proud Warrior", \
                        "Lightning Warrior", \
                        "Experienced Warrior", \
                        "Veteran Warrior", })

#define NCO_LEVELS ({   "Corporal", \
                        "Knowledgeable Corporal", \
                        "Rookie Sergeant", \
                        "Guard Sergeant", \
                        "Grizzled Sergeant", \
                        "Elf-at-arms", \
                        "Aspiring Squire", \
                        "Blooded Squire", \
                        "Veteran Squire", \
                        "Noble Squire", })

#define LORD_LEVELS ({  "Royal Squire", \
                        "Adjutant", \
                        "Noble", \
                        "Baronet", \
                        "Haughty Baronet", \
                        "Lord", \
                        "Lord Lieutenant", \
                        "Regent", \
                        "Commander", })

/* ************************************************************************
 * Set the tax for our civilized little guild.
 */

int
query_guild_tax_race()
{
    return GUILD_TAX;
}

/* ************************************************************************
 * Do we want this player to join our guild?
 */

query_guild_not_allow_join_race(player, type, style, name)
{
    if (::query_guild_not_allow_join_race(player, type, style, name))
        return 1;

    return 0;
}

/********************************************************************
 * Lets face it, you need to be an elf to join an elf race guild!
 */
query_guild_keep_player(player)
{
    if (player->query_race_name() !="elf")
    {
//        notify_fail("You suddenly realise that you're not an elf! Eeks!!\n");
        call_other(JOINROOM, "remove_player_changed_race", player);
	    return 0;

    }

    return 1;
}

/* ************************************************************************
 * Get the players guild level. This is based on INT and DEX.
 */
int
query_wildrunner_level()
{
//    return shadow_who-> query_base_stat(SS_INT) / 2 +
//           shadow_who-> query_base_stat(SS_DEX) / 2;
    return shadow_who-> query_base_stat(SS_RACE) * 4 / 9;
}

/* ************************************************************************
 * Get the players title
 */
public string
get_title(mixed title)
{
    if (!pointerp(title))
    {
        return title;
    }

//    return title[((gender == G_MALE) ? 0 : 1)];
}



/* ************************************************************************
 * Give the player a title that is dependent on their level.
 */
string
query_guild_title_race()
{
    int stat = shadow_who->query_base_stat(SS_RACE);
    mixed title;

    switch(stat)
    {
        case 0..4:   title = "Serf"; break;
        case 5..9:   title = "Trainee Guard"; break;
        case 10..14: title = "Blooded Guard"; break;
        case 15..19: title = "Promising Scout"; break;
        case 20..24: title = "Dashing Scout"; break;
        case 25..29: title = "Lead Scout"; break;
        case 30..34: title = "Trainee Warrior"; break;
        case 35..39: title = "Blooded Warrior"; break;
        case 40..44: title = "Promising Warrior"; break;
        case 45..49: title = "Experienced Warrior"; break;
        case 50..55: title = "Tenacious Warrior"; break;
        case 56..59: title = "Veteran Warrior"; break;
        case 60..64: title = "Trainee Corporal"; break;
        case 65..70: title = "Promising Corporal"; break;
        case 71..74: title = "Rookie Sergeant"; break;
        case 75..79: title = "Promising Sergeant"; break;
        case 80..85: title = "Grizzled Sergeant"; break;
        case 86..90: title = "Elf-At-Arms"; break;
        case 91..95: title = "Aspiring Squire"; break;
        case 96..99: title = "Victorious Squire"; break;
        case 100..104: title = "Veteran Squire"; break;
        case 105..108: title = "Noble Squire"; break;
        case 109..110: title = "Royal Squire"; break;
        case 111..116: title = "Maverick"; break;
        case 117..120: title = "Champion"; break;
        case 121..126: title = "Adjutant"; break;
        case 127..131: title = "Noble"; break;
        case 132..136: title = "Baronet"; break;
        case 137..141: title = "Haughty Baronet"; break;
        case 142..147: title = "Lord"; break;
        case 148..153: title = "Lord Lieutenant"; break;
        case 154..160: title = "Regent"; break;
        case 161..165: title = "Commander"; break;
        case 166..170: title = "Heroic Commander"; break;
		case 171..180: title = "Legendary Command"; break;
        case 181..999: title = "Mythical Commander"; break;
    }
   return title + " of the " +
        ((shadow_who->query_alignment() >= 0) ? "Wildrunner" : "Deathstalker")
        + " Legion";

/*
// Old way titles were calculated. Updated 1/2/2016 because they werent
// calculating correcting.
    stat = query_wildrunner_level() / 7;

    if(stat < 0)
        stat = 0;
    if(stat > 29)
        stat = 29;

    if(stat > 0 && stat <= 10)
    {
        return SERF_LEVELS[stat] + " of the " +
        ((shadow_who->query_alignment() >= 0) ? "Wildrunner" : "Deathstalker")
        + " Legion";
    }
    else
    if((stat > 10 && stat <= 20) &&
        (shadow_who->query_skill(SS_AWARENESS) > 25) &&
        (shadow_who->query_skill(SS_TRACKING) > 10))
        {
        return NCO_LEVELS[stat - 11] + " of the "+
        ((shadow_who->query_alignment() >= 0) ? "Wildrunner" : "Deathstalker")
        + " Legion";
        }
    else
    if((stat > 20) && (shadow_who->query_skill(SS_AWARENESS) > 35) &&
        (shadow_who->query_skill(SS_TRACKING) > 15))
        {
        return LORD_LEVELS[stat - 21] + " of the "+
        ((shadow_who->query_alignment() >= 0) ? "Wildrunner" : "Deathstalker")
        + " Legion";
    }
    else
        return SERF_LEVELS[stat % 11] + " of the "+
        ((shadow_who->query_alignment() >= 0) ? "Wildrunner" : "Deathstalker")
        + " Legion";
*/
}

/* ************************************************************************
 * Get the style of the guild.
 */

string
query_guild_style_race()
{
    return GUILD_STYLE;
}

string
query_guild_name_race()
{
    return GUILD_NAME;
}

void delay_init_wildrunner()
{
  object ob;

  setuid();
  seteuid(getuid());

  if (ob = clone_object(GUILD_OBJECT))
  {
    ob->move(shadow_who, 1);
  }
  write("Your golden ring of the Wild Elves appears in your hand.\n");



/*
    if (news==1)
    {
        write("\n\nThere is some fresh NEWS about the " + GUILD_NAME +
        ". See 'help wild news' for more information.\n\n");
    }
*/
//    shadow_who->catch_tell("\n\nThere is some fresh NEWS about the " + GUILD_NAME +
//        ". See 'help wild news' for more information.\n\n");

  shadow_who->add_cmdsoul(GUILD_SOUL);
  shadow_who->update_hooks();
// make the elves look the picture of perfection
    shadow_who->set_appearance_offset(-50);

}

void news_announce()
{
    write("\n*** There is NEWS about the " + GUILD_NAME + ".\n");
    write("*** See 'help wild news' for more information.\n\n");
}

void init_race_shadow(string str)
{
    int news;
    setuid();
    seteuid(getuid());


    if (shadow_who->query_login_time() <= file_time(GUILD_NEWS))
    {
        set_alarm(5.0, 0.0, news_announce);
    }


/*
    if (shadow_who->query_login_time() <= file_time(GUILD_NEWS))
    {
        write("+++ There is some fresh NEWS about the " + GUILD_NAME + ".\n");
        write("+++ See 'help wild news' for more information.\n\n");
    }
*/
  set_alarm(5.0, 0.0, delay_init_wildrunner);


}

int add_wildrunner_shadow(object who)
{
  int ret = shadow_me(who, "race", GUILD_STYLE, GUILD_NAME);


  if (ret == 1)
  {
    set_alarm(1.0, 0.0, &init_race_shadow(0));
  }

  return ret;
}


public string
query_guild_trainer_race()
{
    return (ROOM_DIR + "train");
}
