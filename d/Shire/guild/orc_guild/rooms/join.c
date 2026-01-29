/* 
	*Entrance of the orc race guild cave
	*Altrus, May 2005
*/
#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/lib/guild_support";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>
#include "/d/Shire/guild/orc_guild/orc.h"
#include "/d/Shire/guild/orc_guild/orc_titles.h"

#define MEMBERS_ADJ		0
#define MEMBERS_TITLE	1
#define MEMBERS_LOCALE	2
#define MEMBERS_TIME	3
#define DID_BEG			"_begged_for_sorcery"

/*
	* Global variables.
	*
	* The mapping members has the names of the players as indices and the
	* values are an array with two elements, the family name of the player
	* and the date the player joined.
*/
private mapping members;
static private string *adjs = ADJS;
static private string *titles = TITLES;
static private string *locales = LOCALES;

object magic_human;

void make_npc();

void create_shire_room()
{
	set_short("A darkened, smoke-filled room");

	set_long(short() + ". The walls have been cut from the surrounding stone, very crudely. There is a large cauldron on the floor here, from which the smoke is eminating. There is no light in here except from the small fire being used to heat the cauldron. A small plaque is affixed to one of the walls. A feeling of malevolence permeates the room.\n");
	
	add_item(({"room"}), "This room looks to have been completely carved out of the stone of one of the walls of the main cave. It is dark, and fumes hanging in the air make it even harder to see.\n");
	add_item(({"smoke", "fumes", "vapor", "haze"}), "The smoke from the fire warming the cauldron fills the room with dizzying haze. It almost looks like some kind of vapor, or fumes, as if something unnatural has been added to the fire. Whatever it is, the fumes are not normal smoke from a woodfire.\n");
	add_item(({"walls", "stone"}), "The walls are completely carved from the rock, and nearly square.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic.\n");
	add_item(({"arc"}), "The arc of the cave walls is about three meters above the ground here, but it could be higher as that point becomes so dark that you are not certain if you are seeing the top of the cave or simply shadow.\n");
	add_item(({"cauldron", "pot"}), "This great iron cauldron dominates the room. It looks large enough to fit a large-sized human in it. That thought doesn't fill you with comfort.\n");
	add_item(({"fire", "small fire"}), "It is a very small fire to be heating such a large cauldron. Interestingly enough the fire hardly gives off any smoke, while whatever is in the cauldron is eminating vasts amounts of fumes into the air of the room.\n");
	add_item(({"plaque", "small plaque"}), "It has something written on it. Try reading it.\n");
	add_cmd_item("plaque","read","@@read_plaque@@");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine, but was dug and fashioned for use as the warren you see now.\n");
	add_exit("/d/Shire/guild/orc_guild/rooms/entry2", "west");
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_NO_CLEANUP, 1);
	add_prop(ROOM_I_NO_ATTACK, 1);
	add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
   
	create_guild_support();
	
	setuid();
	seteuid(getuid());
   
	restore_object(ORC_RACE_GUILD_SAVE);
	if (!mappingp(members))
	{
		members = ([ ]);
	}

	// Test the validity of the members only at the first day of the month.
	if (atoi(ctime(time())[8..9]) == 1)
	{
		set_alarm(12.0, 0.0, "test_members");
	}
	
	reset_shire_room();
}

void reset_shire_room()
{
	make_npc();
}

void make_npc()
{
	if (!magic_human)
		magic_human = clone_object("/d/Shire/guild/orc_guild/dark_sorcerer");
	if (!present(magic_human,this_object()))
		magic_human->move(this_object());
}

/*
* Function name: log_guild
* Description  : This function logs some actions of members of the guild.
*                It uses a larger cycle than basically coded.
* Arguments    : string text - the message to log.
*/
nomask private void
log_guild(string text)
{
   setuid();
   seteuid(getuid());
   
   if (file_size(ORC_RACE_GUILD_LOG) > LOG_SIZE)
      {
      rename(ORC_RACE_GUILD_LOG, (ORC_RACE_GUILD_LOG + ".old"));
   }
   
   write_file(ORC_RACE_GUILD_LOG, text);
}

void init()
{
	::init();
	
	init_guild_support();
	
	add_action("do_beg", "beg");
	add_action("do_claim", "claim");
	add_action("do_castoff", "cast");
	add_action("request", "request");
	
}

//do_beg, adds the prop to begin the transformation process.
int do_beg(string str)
{
	object tp = this_player();
	if(str == "for sorcery")
	{
		if (tp->query_guild_name_occ() == "Union of the Warriors of Shadow")
		{
			write("How could you even think of becoming a grostesque?!\n");
			return 1;
		}
		
		if (tp->query_race() != "elf" && tp->query_race() != "goblin")
		{
			write("You are not an elf or a goblin! Despised as they are, the elven body is the only one with enough latent power to undergo the change. Goblins can be changed as well, as their bodies are already twisted, thus require less potency.\n");
			return 1;
		}
	   
		if(tp->query_alignment() > -500)
		{
			write("And why should a do-gooder such as yourself be allowed to undergo the change?!\n");
	      return 1;
		}
		
		if (IS_MEMBER(tp))
		{
			write("You are already a member of the guild. If you need feel you are not living up to your claimed title and home, you must leave the guild and rejoin in order to claim a new role.\n");
			return 1;
		}
		
		if (tp->query_guild_member(ORC_RACE_GUILD_TYPE))
		{
			write("You cannot be a member of two racial guilds at the same time!\n");
			return 1;
		}
		
		if(tp->query_prop(DID_BEG))
		{
			write("You have already begged enough!\n");
			return 1;
		}
		
		else
		{
			tp->add_prop(DID_BEG, 1);
			write("You get on your knees before the sorcerer, and beg him to twist your form!\n");
			write("The sorcerer hears your pleas, and nods slightly.\n\n");
			write("Before you are changed, you must first claim a title.\n");
			say(QCTNAME(tp) + " gets on " + HIS_HER(tp) + " knees, and begins to beg and plead before the sorcerer, who nods his head slightly.\n");
			return 1;
		}
		
		return 1;
	}
	
	else
	{
		write("Beg for what? Do you wish to become an orc? If so, then beg for sorcery.\n");
		return 1;
	}
}

/*
	*Function name: do_claim
	*Description  : claims a title for the player
	*Arguments    : string str - the command line argument.
	*Returns      : int    1/0 - success/failure.
*/
nomask static int do_claim(string str)
{
	object shadow;
	object tp = this_player();
	string adj;
	string title;
	string loc;
	
	int result;
	
	if(tp->query_prop(DID_BEG))
	{
		if (!strlen(str))
		{
			notify_fail(capitalize(query_verb()) + " what? To claim a title, 'claim <adjective>, <title>, <location>'.\nThe possible adjectives are Aggressive, Cunning, Deceitful, Destructive, Detestable, Ferocious, Foul, Furtive, Malicious, Malodorous, Menacing, Offensive, Revolting, Savage, Scabrous, Shifty, Tenacious, Twisted, Unrelenting, and Vicious.\nThe possible titles are Fighter, Marauder, Pillager, Raider, Scavenger, Scoundrel, Scrounge, Spy, Warmonger, and Warrior.\nThe possible locations are Barad-dur, Carn Dum, Cirith Gorgor, Dol Guldur, Durthang, Gorgoroth, Lugburz, Moria, the Ash Plain, the Grey Mountains, and the Misty Mountains. (Articles, spaces and capitalization are important)\n");
		      return 0;
		}
		
		if (sscanf(str, "%s, %s, %s", adj, title, loc) != 3)
		{
		      notify_fail(capitalize(query_verb()) + " what? To claim a title, 'claim <adjective>, <title>, <location>'.\nThe possible adjectives are Aggressive, Cunning, Deceitful, Destructive, Detestable, Ferocious, Foul, Furtive, Malicious, Malodorous, Menacing, Offensive, Revolting, Savage, Scabrous, Shifty, Tenacious, Twisted, Unrelenting, and Vicious.\nThe possible titles are Fighter, Marauder, Pillager, Raider, Scavenger, Scoundrel, Scrounge, Spy, Warmonger, and Warrior.\nThe possible locations are Barad-dur, Carn Dum, Cirith Gorgor, Dol Guldur, Durthang, Gorgoroth, Lugburz, Moria, the Ash Plain, the Grey Mountains, and the Misty Mountains. (Articles, spaces and capitalization are important)\n");
		      return 0;
		}
		
		if(member_array(adj, adjs) == -1)
		{
			write("The adjective '" + adj + "' does not exist in this guild. The possible adjectives are Aggressive, Cunning, Deceitful, Destructive, Detestable, Ferocious, Foul, Furtive, Malicious, Malodorous, Menacing, Offensive, Revolting, Savage, Scabrous, Shifty, Tenacious, Twisted, Unrelenting, and Vicious.\n");
			return 1;
		}
		
		if(member_array(title, titles) == -1)
		{
			write("The title '" + title + "' does not exist in this guild. The possible titles are Fighter, Marauder, Pillager, Raider, Scavenger, Scoundrel, Scrounge, Spy, Warmonger, and Warrior.\n");
		      return 1;
		}
		
		if(member_array(loc, locales) == -1)
		{
			write("The location '" + loc + "' does not exist in this guild. The possible locations are Barad-dur, Carn Dum, Cirith Gorgor, Dol Guldur, Durthang, Gorgoroth, Lugburz, Moria, the Ash Plain, the Grey Mountains, and the Misty Mountains. (Articles, spaces and capitalization are important)\n");
			return 1;
		}
		
		shadow = clone_object(ORC_RACE_GUILD_SHADOW);
		
		if ((result = shadow->shadow_me(tp, ORC_RACE_GUILD_TYPE, ORC_RACE_GUILD_STYLE, ORC_RACE_GUILD_NAME)) != 1)
		{
			log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " failed to add shadow with result " + result + ".\n");
		      shadow->remove_shadow();
		      
		      write("Strange, the sorcery failed. However, that should not have happened. Please leave a bugreport in this room.\n");
		      
		      return 1;
		}
		
		//write("You seem to have a shadow...\n\n");
		write("Before you can react, the sorcerer binds you with a spell and levers you into the cauldron!\n\n");
		write("You here a faint mumbling, and suddenly you are wracked with an intense pain!\n\n");
		write("You must have blacked out, because right now, you are standing in front of the sorcerer, who is holding up a polished sheet of silver, in which you can see your face... You have become an orc!\n\n");
		if(tp->query_race() == "elf")
			write("What have you done to yourself?!\n\n");
		if(tp->query_race() == "goblin");
			write("Orcs are superior to goblins!\n\n");
		write("A small orc enters the room and hands you an iron arm band and leaves.\n");
		
		say(QCTNAME(tp) + " claims a title, then suddenly the sorcerer utters some words and binds " + HIM_HER(tp) + " with a spell! " + QCTNAME(tp) + " is levered into the cauldron.\n\n");
		say("You here a faint mumbling coming from the sorcerer, then suddenly " + QCTNAME(tp) + " begins to convulse... " + HE_SHE(tp) + " passes out!\n\n");
		say(HE_SHE(tp) + " isn't out long though, and is quickly hauled out of the cauldron and placed on " + HIS_HER(tp) + " feet again, standing before the sorcerer. " + HE_SHE(tp) + " has become and orc!\n\n");
		say("A small orc enters the room and hands " + QCTNAME(tp) + " an iron arm band and leaves.\n");
		
		clone_object(ORC_RACE_GUILD_BAND)->move(tp, 1);
		tp->set_clan_name(adj, title, loc);
		//write("Setting clan name - Joinroom.\n");
		set_alarm(3.0,0.0,"init_me",tp);
		log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " + ORC_RACE_GUILD_NAME + ".\n");
		
		tp->remove_prop(DID_BEG);
		tp->clear_guild_stat(SS_RACE);
		tp->set_guild_pref(SS_RACE, ORC_RACE_GUILD_TAX);
		tp->add_cmdsoul(ORC_RACE_GUILD_SOUL);
		tp->update_hooks();
		//write("Normaly would be adding cmdsoul here...\n");
		
		members[tp->query_real_name()] = ({ adj, title, loc, tp->query_age(), time() });
		save_object(ORC_RACE_GUILD_SAVE);
		//write("Saving master object...\n");
		
		return 1;
	}
	
	else
	{
		write("You must first beg! Beg for it!\n");
		return 1;
	}
}

int
init_me(object ob)
{
   ob->init_race_shadow();
   return 1;
}

void dest_band(object player)
{
    object band;
   
    band = present(BAND_ID, player);
    if (objectp(band))
    {
        band->remove_object();
    }
}

/*
* Function name: lower_skill
* Description  : When a member leaves the guild or is kicked out due
*                to a change of race, this function punishes him/her,
*                removes the soul, shadow, etcetera.
* Arguments    : object tp - the object leaving.
*/
nomask private void lower_skill(object tp)
{
	object band;
	
	tp->set_guild_pref(SS_RACE, 0);
	tp->clear_guild_stat(SS_RACE);
	tp->remove_cmdsoul(ORC_RACE_GUILD_SOUL);
	tp->update_hooks();
	tp->setup_skill_decay();
	
	/* If the player starts in the guild by default, set this to
   * the default starting location for all players.
   */
	if (tp->query_default_start_location() == START)
	{
		tp->set_default_start_location(tp->query_def_start());
	}
   
	set_alarm(2.0,0.0,&dest_band(tp));
	{
		band->remove_object();
	}
   /* Remove him/her from the list of members.
   */
	members = m_delete(members, tp->query_real_name());
   
	setuid();
	seteuid(getuid());
   
	save_object(ORC_RACE_GUILD_SAVE);
	
}

void remove_from_list(string player)
{
   player = lower_case(player);
   members = m_delete(members,player);
   setuid(); seteuid(getuid());
   save_object(ORC_RACE_GUILD_SAVE);
}

/*
* Function name: remove_player_changed_race
* Description  : Whenever a member changes his/her race (s)he is
*                mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void remove_player_changed_race(object tp)
{
   tp->catch_msg("\nYour body, being not of elven-kind, can no longer be sustained by dark sorcery in the form of an orc. Therefore you do not " +
      "belong in the " + ORC_RACE_GUILD_NAME + " any more. You " +
      "are being expelled from the guild.\n");
   
   lower_skill(tp);
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (race " +
      tp->query_race_name() + ") was kicked out.\n");
}

/*
* Function name: remove_player_low_alignment
* Description  : Whenever the alignment of a player is too low, the player
*                is mercilessly kicked out the guild by this function.
* Arguments    : object tp - the object to kick out.
*/
nomask public void remove_player_high_alignment(object tp)
{
   tp->catch_msg("\nSo you are no longer devoted to bringing about the subjegation of the Free Peoples? Then there is no place for you in the " + ORC_RACE_GUILD_NAME + " any more. " +
      "You are being expelled from the guild.\n");
   
   tp->set_race_name(tp->query_race());
   lower_skill(tp);
   
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " (alignment " +
      tp->query_alignment() + ") was kicked out.\n");
}

/*
* Function name: do_cast
* Description  : This is a waste of memory since no-one would ever
*                consider leaving a guild like this, or would they?
*                Just for the completeness, this function takes care
*                of a voluntary leave.
* Arguments    : string str - the command line argument
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_castoff(string str)
{
   object tp = this_player();
   object band;
   int result;
   int death_number;
   int health;
	if (str != "off" && str != "off sorcery" && str != "off the sorcery")
	{
		notify_fail("Cast? Cast off the sorcery?\n");
		return 0;
	}
   
   if (!IS_MEMBER(tp))
      {
      write("You cannot cast off the sorcery, as it holds no sway over you.\n");
      return 1;
   }
   
   if ((result = tp->remove_guild_race()) != 1)
      {
      log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
         " failed to remove shadow with result " + result + ".\n");
      
      write("You cannot seem to cast off the vile sorcery! However, everyone who " +
         "wishes so, should be able to do so. Please leave a bugreport " +
         "in this room.\n");
      
      return 1;
   }
   
   write("You feel much pain as the magic that held your twisted form is ripped from you, leaving you weak and frail...\n");
   
   tp->set_race_name(tp->query_race());
   lower_skill(tp);
   
   band = present(BAND_ID, tp);

    if (objectp(band))
    {
        band->remove_object();
        write("Your iron arm band suddenly catches fire, then is completely vanished!\n");
    }
    
   log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
      ORC_RACE_GUILD_NAME + ".\n");
   
    health = tp->query_hp();
    tp->heal_hp(- (health - 1));
    
   /* death_number = random(10);
    if(death_number = 3)
    {
	write("Two orcs rush into the room! Seeing you, a weak and pathetic elf, they draw their swords and run your through! As your blood flows onto the ground, they laugh and revel in the slaughter, then leave you alone to die.\n\n");
	write("You slowy die in a pool of your own blood.\n\n");
	say("Two orcs rush into the room, and seeing " + QCTNAME(tp) + ", a weak and pathetic elf, they draw their swords and run " + HIM_HER(tp) + " through! The laugh for a moment as blood flows freely onto the floor, then leave.\n\n");
	say(QCTNAME(tp) + " dies in a pool of blood.\n\n");
	tp->heal_hp(-1000);
	tp->do_die(this_object());
	}
	*/
	return 1;
}

/*
* Function name: request
* Description  : Members who have lost their circlet, may get it back here.
* Arguments    : string str - the command line argument.
* Returns      : int 1/0    - success/failure.
*/
nomask static int request(string str)
{
    if (str != "arm band")
    {
        notify_fail("Request what? A new arm band?\n");
    return 0;
    }
   
    if (!IS_MEMBER(TP))
    {
        write("You are not a member of this guild. You have no " +
            "right to an arm band.\n");
    return 1;
    }
   
    if (objectp(present(BAND_ID, TP)))
    {
        write("You already have an arm band. You don't need two.\n");
    return 1;
    }
   
    setuid();
    seteuid(getuid());
   
    clone_object(ORC_RACE_GUILD_BAND)->move(TP, 1);
   
    write("A small orc rushes into the room and hands you another arm band and leaves.\n");
    say(" A small orc rushes into the room and hands " +QCTNAME(TP)  + " an iron arm band and leaves.\n");
   
    return 1;
}

public string query_clan_name(string name)
{
   if (!members[name])
      {
      return "";
   }
   
   return "the " + members[name][MEMBERS_ADJ] + " " + members[name][MEMBERS_TITLE] + " of " + members[name][MEMBERS_LOCALE];
}

string read_plaque(string str)
{
	
	return " \n __________________________________________________________\n"+
			"|O  _____________________________________________________ O|\n"+
			"|  /                                                     \\ |\n"+
			"| |                  BE FOREWARNED!!                     | |\n"+
			"| |          Orcs do not take betrayal lightly.          | |\n"+
			"| |       If you join, and later decide to reject        | |\n"+
			"| |     that which you have become, or do not remain     | |\n"+
			"| |     sinister enough for the sorcery to bind you,     | |\n"+
			"| |       whatever happens to you then is on your        | |\n"+
			"| |        own head. You have been fairly warned.        | |\n"+
			"| |        Ask the wretched human about leaving.         | |\n"+
			"| \\______________________________________________________/ |\n"+
			"|O                                                        O|\n"+
			" ----------------------------------------------------------\n\n";
}