/**********************************************************************
 * - crystal.c                                                      - *
 * - Eil-Galaith Crystal room                                       - *
 * - Created by Damaris 08/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/

#pragma strict_types

#include "../guild.h"
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
inherit GUILD_ROOM;

#define GLOBE_PATH	"/d/Khalakhor/guilds/eilgalaith/"
#define GLOBE_LIMIT ({ 7, 50, "You have taken plenty of globes, leave "+ \
	"some for others.\n", "Sorry, the globes are unavailble at "+ \
	"this time.\n" })
static public string *globe;
static mapping requested = ([ "MAX":0 ]);
object coffer;
 
int
chk(string id, string fname)
{
	if (!objectp(present(id,coffer)))
	{
		(clone_object(ROOM+fname))->move(coffer);
		return 1;
	}
	return 0;
}

nomask static int
request_globe(string str)
{
	string verb = query_verb(), name;
	object ob;
	if ((str != "globe"))
	{
		NF("Request what? a globe maybe?\n");
		return 0;
	}
//	if (!IS_MEMBER(TP))
//	{
//		write("Globes are for members only, Sorry.\n");
//		return 1;
//	}
	
	/* Are there any left to request? */
	if (requested["MAX"] >= GLOBE_LIMIT[1])
	{
		write(GLOBE_LIMIT[3]);
		return 1;
	}
	
	/* See if we requested too many already */
	name = this_player()->query_name();
	if (requested[name] >= GLOBE_LIMIT[0])
	{
		write(GLOBE_LIMIT[2]);
		return 1;
	}
	setuid();
	seteuid(getuid());
	clone_object(GLOBE_PATH + "globe")->move(TP, 1);
	write("You look over the small crystal globes and select one.\n");
	say(QCTNAME(this_player()) +" looks over the small crystal "+
	"globes and selects one.\n");
	
	/* Adjust the limits */
	requested["MAX"]++;
	requested[name]++;
	return 1;
}

void
create_guild_room()
{
	set_short("Eil-Galaith's crystal room");
	set_long("   This round shaped room is small but has a large "+
	"skylight that allows light to fill this area. There are "+
	"small crystals hanging from the skylight that lets the "+
	"sun stream through to dance across them. The atmosphere "+
	"is warm and lively with rainbow colours dancing along "+
	"the walls and floor. There also is a small crystal plaque "+
	"placed along a wall.\n");
	add_item(({"light"}),
	"The light streams in from the skylight filling the room with "+
	"warmth.\n");
	add_item(({"plaque", "crystal plaque"}),
	"          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
	"          | Among the crystals some globes abound. |\n"+
	"          | Within a globe a treasure is found.    |\n"+
	"          | You may request thus solely from me.   |\n"+
	"          | To give or not is up to thee.          |\n"+
	"          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
	add_item(({"globe", "crystal globe", "crystal globes", "globes"}),
	"The globes sparkle in the light. You might want to try to "+
	"request one.\n");
	add_item(({"wall", "walls"}),
	"The walls are made from a mysterious white marble with a spiral "+
	"of black intertwining in seamless patterns. There are rainbow "+
	"colours dancing along them from the crystals.\n");
	add_item(({"floor", "flooring"}),
	"The floor is made from a mysterious white marble with a spiral "+
	"of black intertwining in seamless patterns. There are rainbow "+
	"colours dancing along it from the crystals.\n");
	add_item(({"crystal", "crystals"}),
	"The skylight is filled with small crystals hanging down. They "+
	"are teardrop shaped and sparkle with rainbow colours.\n");
	add_item(({"skylight"}),
	"The skylight covers the entire ceiling and lets warm light in. "+
	"There are small crystals hanging from it.\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	coffer=clone_object(ROOM + "coffer");
	coffer->move(TO);
	add_exit("start", "down");
	add_fail("auto", "A wall stops you.\n");   
}
public int
read_me(string str)
{
	if (str == "plaque" || str == "crystal plaque")
	{
		write("          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n"+
		"          | Among the crystals some globes abound. |\n"+
		"          | Within a globe a treasure is found.    |\n"+
		"          | You may request thus solely from me.   |\n"+
		"          | To give or not is up to thee.          |\n"+
		"          *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*\n");
		return 1;
	}
	return
	notify_fail("Read what?\n");
}

public void
init()
{
	::init();
	add_action(request_globe, "request");
	add_action(read_me, "read");
}
