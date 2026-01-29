#include "soul.h"
#include "../guild.h"

#include <macros.h>

public void convey_message(string color, object player, object conveyer);

int
convey(string str)
{
    object player;
    string color, target;

    notify_fail("Who do you which to convey a thought to?\n");
    if (!strlen(str))
	return 0;

    if ((sscanf(str, "%s to %s", color, target))!=2)
    {
	notify_fail("Usage: ktconvey <color> to <keeper>\n");
	return 0;
    }
    
    player = find_player(target);
    if (!player)
    {
	notify_fail("Your mind cannot sense the presence of anyone "+
		    "to convey that thought to.\n");
	return 0;
    }

    if (!player->query_kot_member())
    {
	notify_fail("Your mind is unable to convey a thought to someone "+
		    "not within the embrace of Telan-Ri.\n");
	return 0;
    }

    if (this_player()->query_mana() < 20)
    {
	notify_fail("You are too mentally fatigued to convey this "+
		    "thought to anyone right now.\n");
	return 0;
    }

    if (this_player()->query_attack())
    {
	notify_fail("You cannot concentrate on conveying a thought while "+
		    "in combat.\n");
	return 0;
    }


    // at this point we have a color, and a target oblist.

    if ( (member_array(color, CONVEY_COLORS))==-1)
    {
	notify_fail("You cannot convey that thought, it is not a color "+
		    "you know how to convey.\n");
	return 0;
    }

    if (file_name(environment(this_player()))==file_name(environment(player)))
    {
	notify_fail("You do not need to convey thoughts to someone "+
		    "who is nearby.\n");
	return 0;
    }

    this_player()->add_mana(-20);
    write("You bow your head in deep concentration. An instant later "+
          "you have the surging feeling of your mind contacting "+
          "another's.\n");
    say(QCTNAME(this_player())+" bows "+POSTP+" head in deep "+
        "concentration. An instant later "+OBJTP+" jerks "+
        POSTP+" head up, a distant, thoughtful "+
        "look in "+POSTP+" eyes.\n");

    convey_message(color, player, this_player());
    return 1;
}

public varargs void
convey_message(string color, object player, object conveyer)
{
    string domain = environment(conveyer)->query_domain();
    player->catch_msg("\n ... A distant image of "+
			 conveyer->query_name()+" appears "+
			 "deep within your mind, above "+
			 OBJTP+" the "+color+"-tinted "+
			 "sky of "+domain+" ... \n");
    tell_room(environment(player),
	      QCTNAME(player)+" seems to get a distant, thoughtful "+
	      "look in "+ POS(player) + " eyes.\n", player);
}
