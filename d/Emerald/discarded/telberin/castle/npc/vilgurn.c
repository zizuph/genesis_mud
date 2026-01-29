/*
 * VILGURN.c
 * This is the npc guildmaster/record-keeper of the Keepers of Telberin.
 * He is a very integral part in the joining process of the guild. You need
 * to ask him for his blessing, and you must be seated while doing this, otherwise
 * he thinks you're being rude and don't really want to talk.
 * - Alaron November 1996
 */

#include "/d/Emerald/defs.h"
#include "/d/Emerald/common/guild/kot/guild.h"
#include "default.h"
#include <macros.h>
#include <stdproperties.h>
#include <const.h>

inherit "/d/Emerald/std/emerald_monster";   
inherit "/d/Emerald/common/guild/kot/lib/npc_convey";

static int convey_time;

void give_blessing(object player);
void react_introduce(string np);

void
create_emerald_monster()
{
  set_name("vilgurn");
  set_living_name("vilgurn");

  set_race_name("elf");

  set_stats( ({180, 200, 170, 160, 150, 180}) );

  set_title("Lord Commander of the Protectorate of Telberin");

  map(({ SS_WEP_POLEARM, SS_UNARM_COMBAT, SS_AWARENESS, SS_DEFENSE,
              SS_PARRY }), &set_skill(, 100));

  add_prop(CONT_I_HEIGHT,250);
  add_prop(CONT_I_WEIGHT,62000);
  add_prop(LIVE_I_NON_REMEMBER, 1);

  set_long("   This enormous man is most likely the largest elf you have ever "+
	   "encountered. He towers over you. His bulk is "+
	   "large and muscular, in contrast with the tall, lean elves most "+
	   "people are familiar with. His face is the only thing which gives away "+
	   "his race. Muscles and tendons tense like twisted rope in his arms "+
	   "as he moves about the room. He is very well armed and his outfitting "+
	   "bears many tokens and badges of past victories. He certainly does not look "+
	   "like a man you would enjoy being in a fight with, although he looks as if "+
	   "he would not be opposed to being spoken to.\n");

  add_equipment( ({"/d/Emerald/telberin/castle/wep/astaff",
		     "/d/Emerald/telberin/castle/arm/rlpmail",
		     "/d/Emerald/telberin/castle/arm/wcloak"}) );
  
  log_my_kills("/d/Emerald/telberin/castle/log/vilgurn_kills");
  log_my_deaths("/d/Emerald/telberin/castle/log/vilgurn_deaths");
  
  add_ask( ({"blessing", "for blessing", "telberin's blessing",
	       "blessing of telberin"}),
	   VBFC_ME("respond_to_blessing"),
	   0);

}

string
respond_to_blessing()
{
    string a, b;
    string title = 
        ((this_player()->query_gender() == G_MALE) ? "sir" : "madam");
    object requestor = this_player();

    a = "Vilgurn leans across his desk and looks down at you: ";
    b = "Vilgurn launches out of his chair and looms over you: ";

    if (!CAN_SEE(this_object(), requestor) || !CAN_SEE_IN_ROOM(this_object()))
    {
        command("say You will have to reveal yourself before we can " +
            "speak.\n");
        return "";
    }

    if (requestor->query_kot_member())
    {  
        command("say You are already a member of the Keepers of Telberin, " +
            "though, " + requestor->query_name() + ".\n");
        return "";
    }

    if (requestor->query_prop("_newbie_wannabe_keeper"))
    {
        command("say I've already given you my blessing, " + 
            requestor->query_name() + ".\n");
        return "";
    }

    if (!requestor->query_prop("_introduced_to_vilgurn"))
    {
	return a + "Before we begin asking for anything, it is usually "+
	    "customary to introduce yourself to your host, " + title + ".\n";
    }
  
    if (requestor != environment(this_object())->query_sitter())
    {
	return a + "I am sorry good " + title + ", but I feel it is rather "+
	    "rude of you to ask of me such a thing without even sitting "+
	    "at my desk.\n";
    }
    else
    {
	if (requestor->query_race() != "elf") 
	{
	    return a + "I am sorry good " + title + " but the Keepers of "+
		"Telberin have historically been an elven institution. We "+
		"will not accept members of your race.\n";
	}
	else 
	{
	    if ((requestor->query_alignment() < -10) ||
                requestor->query_prop(LIVE_I_UNDEAD))
	    {
		command("shout The Keepers of Telberin do not associate " +
                    "with your type!\n");
		return b + "Out! Out of my office, infidel! Your vile, "+
		    "vicious kind shall not be welcome in the "+
		    "Keepers! We are dedicated to ridding our "+
		    "kingdom of foul folk like you! Be gone before "+
		    "I have you killed on the spot!!\n";
	    }
	    else if (requestor->query_guild_name_race())
	    {
	       command("say to "+requestor->query_real_name()+" You already "+
		   "have ties to those of your race. Unless you break "+
		   "those ties, you will not prove that you have the "+
		   "commitment to become a Keeper of Telberin.");
	       return "Return to me once you have broken your other racial "+
		   "ties.\n";
	    }
	    else
	    {
		set_alarm(4.0, 0.0, &give_blessing(requestor));
		return a + "So, you wish my blessing for your membership " +
		    "in the Keepers of Telberin, then?\n";
	    }
	}
    }
}

void
give_blessing(object player)
{
    object sash;
  
    if (!present(player, environment()))
    {
	return;
    }
  
    if (!CAN_SEE(this_object(), this_player()) || 
	!CAN_SEE_IN_ROOM(this_object()))
    {
	command("peer");
	command("say You will have to reveal yourself before I can " +
	    "give you my blessing, " + player->query_name() + ".\n");
	 return;
    }
  
    player->add_prop("_newbie_wannabe_keeper", 1);
  
    if (sizeof(filter(deep_inventory(player), &->id(GUILD_EMBLEM_ID))))
    {
	command("say I see you already have a sash, " + player->query_name() +
	    ".\n");
    }
    else
    {  
	setuid();
	seteuid(getuid());
	sash = clone_object(GUILD_OBJECT);
	command("say to "+ OB_NAME(player) + " I give you this token as proof "+
	    "of my blessing.  With this, all may know that I have given my " +
	    "approval that you may enter the elite ranks of the Keepers of " +
	    "Telberin. Take this and show it to the king or queen that they " +
	    "might know my approval of you.");

        player->catch_tell(query_The_name(player) + " gives you " +
            LANG_ASHORT(sash) + ".\n");

        tell_room(environment(), QCTNAME(this_object()) + " gives " +
            QTNAME(player) + " " + LANG_ASHORT(sash) + ".\n",
            ({ this_object(), player }));

        sash->move(player, 1);
    }
}

public void
add_introduced(string name)
{
  object nplayer;

  nplayer = present(name,environment(this_object()));  // get an object ref to this player

  if (nplayer->query_prop("_introduced_to_vilgurn")) {
    command("nod "+name);
    command("say We have met.");
  } else {
     TP->add_prop("_introduced_to_vilgurn", 1);
      set_alarm(1.0, 0.0, &react_introduce(name));
  }
}

void
react_introduce(string np)
{
  command("introduce myself to "+np);
    command("say A true pleasure to meet you.");
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    if ((time() - convey_time) > 90)
    {
        convey_time = time();
        ktconvey("red");
    }
}
