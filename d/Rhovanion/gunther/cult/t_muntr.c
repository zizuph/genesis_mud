inherit "/d/Rhovanion/lib/room";

inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <money.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

int closed;
#define OPEN		0	/* 1 = closed,   0 = open.  */
#define CLOSED		1
#define NUM		sizeof(query_money_types(-1))

void set_up_skills();

create_room()
{
	::create_room();
	
	set_short("Mundane skills training room.");
	
	set_long("This round room is the mundande skills training room here in"
		+" the home. A large sparring mat takes up most of the floor space."
		+" Some novices are practicing on it and they cast eerie shadows on"
		+" the perfectly smooth walls. A sign hangs upon one of the walls."
		+" To the south you can see a library of sorts and to the east is the"
		+" gathering hall.\n");
		
	add_item(({ "sparring mat", "mat" }), "The large brown sparring mat looks"
		+" quite thick and you could probably land on it rather hard without"
		+" getting hurt.\n" );
	add_item(({"walls", "wall" }), "The walls are perfectly round and very"
		+" smooth. The light seems to glint off them. A sign hangs on one of"
		+" the walls.\n");
	add_item(({"light", "shadow", "shadows"}), "The light doesn't seem to"
		+" originate from anywhere within the room but still manages to cast"
		+" shadows in all directions.\n");
	add_item("sign", "Throwing a quick glance at the sign you can't help but"
		+" to read it. It says:\nHere you may <improve> skills or <learn> new"
		+" ones.\n");
	add_item("library", "You can't see much of the library from here, perhaps"
		+" you should go and take a look?\n");
	add_item(({"hall", "gathering hall" }), "It is back east from here.\n");
	add_item(({"novice", "novices"}), "The novices seem to be entirely concentrated"
		+" on fighting each other with knives. Noone seems to pay any attention"
		+" to you.\n");
	
	add_exit(CULT_DIR+"t_gather","east",0);
	add_exit(CULT_DIR+"t_spltr", "south", 0);

	change_prop(ROOM_I_LIGHT,1);
	change_prop(ROOM_I_INSIDE,1);
	
	closed = OPEN; 
	add_prop(OBJ_S_WIZINFO, "@@wizinfo");
	set_up_skills();
}

string
wizinfo()
{
   return "If there should be due cause to close down the guild, do so by " +
	   "typing:  Call here close_guild\n" +
	   "This will temporarily prevent mortals from entering. After a " +
	   "reboot, the guild will be open by default. Please send me some " +
	   "mail if there is anything that needs to be fixed. See also t_spltr.c "+
	   "for a training location to close.\n\n   /Gunther.\n";
}

void
init()
{
    ::init();
    init_guild_support();
    init_skill_raise();
}

string
close_guild()
{
	if((closed = CLOSED - closed) == OPEN)
		return "  **The guild is now open**";
	else
		return "  **The guild is now closed**";
}

query_closed() { return closed; }

void
set_up_skills()
{
    sk_add_train(SS_WEP_KNIFE,"use a knife in combat",0,0,60);
    sk_add_train(SS_DEFENCE,"defend against enemies in combat",0,0,50);
}
