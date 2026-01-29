
/* 
	*Entrance of the uruk race guild slave pits, Mordor branch
	*Altrus, December 2005
*/
#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>
#include "/d/Shire/guild/uruk_guild/uruk.h"

inherit "/d/Shire/std/room";
inherit "/lib/guild_support";

//void make_npc();
//object uruk_guard;

void create_shire_room()
{
	set_short("A small passage near the slave pits of Minas Morgul");

	set_long("This room needs to be fleshed out.\n");
	/*
	add_item(({"passage", "small passage"}), ".\n");
	add_item(({"pits", "slave pits"}), "The walls, while crudely fashioned, are more or less squared to the floor, at least up to head heighth. There are several small torches hanging on the wall from sconces.\n");
	add_item(({"ground", "floor", "surface"}), "The ground here is all rock and dirt. The rock surface of the floor appears to be worn somewhat smoother than the walls of the cave, probably due to foot traffic.\n");
	add_item(({"torches", "small torches", "weak torches"}), "The torches are made of tar soaked fabric or skins wrapped onto the end of small sticks. They barely shed any light on the cave.\n");
	add_item(({"sconces"}), "The sconces hanging from the walls are made from metal, probably iron. They are rusted and bent, in serious need of replacing.\n");
	add_item(({"passage", "main passage"}), "The broader route leads off to the northwest, and also south back towards the cave entrance.\n");
	add_item(({"sticks", "small sticks"}), "The sticks being used as torches to provide some light for the cave.\n");
	add_item(({"fabric", "skins"}), "The fabric or skin or whatever it is that's wrapped around the torches is soaked in some kind of oil or tar.\n");
	add_item(({"oil", "tar", "substance"}), "The oily or tarry substance on the torches makes them easier to light.\n");
	add_item(({"dirt"}), "The dirt on the cave's floor grinds under foot as you walk around.\n");
	add_item(({"rock"}), "Although hard to see in the dim light, the rock that forms the cave walls is mostly a uniform grey or grey-black. There don't appear to be any significant mineral veins. This was probably never a mine, but was dug and fashioned for use as the warren you see now.\n");
	*/
	add_exit("/d/Gondor/morgul/city/darkstr0", "up");
	add_exit(URUK_RM + "m_passage", "north", "@@check_member@@");
	reset_shire_room();
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_NO_CLEANUP, 1);
	add_prop(ROOM_I_NO_ATTACK, 1);
	add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
}

void reset_shire_room()
{
	//make_npc();
}

/*
void make_npc()
{
	if(!uruk_guard)
	{
		uruk_guard = clone_object("/d/Shire/guild/uruk_guild/guild_guard");
		uruk_guard->move(TO);
		tell_room(TO, capitalize(LANG_ADDART(uruk_guard->query_nonmet_name()))+ " stalks into the room, growling furiously.\n");
	}
}
*/

void init()
{
	::init();
	
	init_guild_support();
	
	add_action("do_commit", "commit");
	add_action("do_renounce", "renounce");
}

int do_commit(string str)
{
	str = lower_case(str);
	object tp = this_player();
	int result;
	
	if(str == "to the dark lord" | str == "dark lord" | str == "to dark lord")
	{
		object shadow;
		
		if (tp->query_guild_name_occ() == "Union of the Warriors of Shadow")
		{
			write("How could you even think of becoming a grotesque?!\n");
			return 1;
		}
		
		if (tp->query_race() != "human" && tp->query_race() != "goblin")
		{
			write("This process is severely limited. Goblins and humans only!\n");
			return 1;
		}
	   
		if(tp->query_alignment() > -500)
		{
			write("And why should we tolerate the presence of a do-gooder like you?!\n");
	      return 1;
		}
		
		if (IS_MEMBER(tp))
		{
			write("You are already a member of the guild. If you are experiencing problems with the guild (such as loss of title and race) contact the guildmaster.\n");
			return 1;
		}
		
		if (tp->query_guild_member(URUK_RACE_GUILD_TYPE))
		{
			write("You cannot be a member of two racial guilds at the same time!\n");
			return 1;
		}
		
		else
		{
		    shadow = clone_object(URUK_RACE_GUILD_SHADOW);
			
		    if((result = shadow->shadow_me(tp, URUK_RACE_GUILD_TYPE, URUK_RACE_GUILD_STYLE, URUK_RACE_GUILD_NAME)) != 1)
		    {
			MANAGER->log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " failed to add shadow with result " + result + ".\n");
		        shadow->remove_shadow();
		      
		        write("Strange, for some reason, you have not been admitted to the guild. Please leave a bugreport in this room.\n");
		      
			return 1;
		    }
		    
		write("This is just the test...Change this message when you have time.\n\n");
		if(tp->query_race() == "human")
			write("What have you done to yourself?!\n\n");
		if(tp->query_race() == "goblin");
			write("Yes! Uruks are far superior to goblins!\n\n");
		
		
		set_alarm(3.0,0.0,"init_me",tp);
		MANAGER->log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " joined the " + URUK_RACE_GUILD_NAME + ", Mordor branch.\n");
		
		tp->clear_guild_stat(SS_RACE);
		tp->set_guild_pref(SS_RACE, URUK_RACE_GUILD_TAX);
		MANAGER->add_uruk(tp->query_real_name(), "mordor");
		//tp->add_cmdsoul(URUK_RACE_GUILD_SOUL);
		write("Normaly would be adding cmdsoul here...\n");
		tp->update_hooks();
		
		save_object(MASTER);
		//write("Saving master object...\n");
		
		return 1;
		    
			return 1;
		}
		
	}
	
	else
	{
		write("Commit what? If you wish to commit, commit to the Dark Lord.\n");
		return 1;
	}
}

/*
* Function name: do_renounce
* Description  : This is a waste of memory since no-one would ever
*                consider leaving a guild like this, or would they?
*                Just for the completeness, this function takes care
*                of a voluntary leave.
* Arguments    : string str - the command line argument
* Returns      : int    1/0 - success/failure.
*/
nomask static int
do_renounce(string str)
{
   str = lower_case(str);
   object tp = this_player();
   object band;
   int result;
   int health;
	if (str != "the dark lord" && str != "dark lord")
	{
		notify_fail("Renounce what? Do you wish to renounce the Dark Lord?\n");
		return 0;
	}
   
   if (!IS_MEMBER(tp))
      {
      write("You're not a member! How could you possibly leave if you are not first a member?.\n");
      return 1;
   }
   
   if ((result = tp->remove_guild_race()) != 1)
      {
      MANAGER->log_guild(ctime(time()) + " " + WRITE_NAME(tp) +
         " failed to remove shadow with result " + result + ".\n");
      
      write("For some reason you could not leave the guild... That shouldn't ever happen, please leave a bug report here and the guildmaster will take care of the problem.\n");
      
      return 1;
   }
   
   write("Fill in some kind of leaving message.\n");
   
   tp->set_race_name(tp->query_race());
   //tp->set_race_name("elf");
   //lower_skill(tp);
   MANAGER->remove_uruk(tp->query_real_name());
   MANAGER->log_guild(ctime(time()) + " " + WRITE_NAME(tp) + " left the " +
      URUK_RACE_GUILD_NAME + ".\n");
   
    health = tp->query_hp();
    tp->heal_hp(- (health - 1));

    return 1;
}

int check_member()
{
	if(!IS_MEMBER(TP) && !TP->query_wiz_level())
	{
		write("The fierce uruk growls slowly at you. Better not go that way.\n");
		say("The fierce uruk growls slowly at  " + QCTNAME(TP) + ", blocking " + HIM_HER(TP) + " from going further.\n");
		return 1;
	}
	
	else
		return 0;
}
