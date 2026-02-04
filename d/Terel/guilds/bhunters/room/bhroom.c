/*
 Bounty hunters training room,
 by Udana 05/06
 temp also join room.
*/

#include "/d/Terel/include/Terel.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "../bhunters.h"
#include <files.h>

inherit "/lib/skill_raise";


inherit STDROOM;
/* sets up this room as a training room */
void add_skills()
{}

void create_bhroom()
{}

public void create_terel_room()
{
	create_bhroom();
	set_short("Room in 'Hook & Dagger'");
	set_long("Rooms in 'Hook & Dagger' can't be called luxurious. Besides bed every room has "+
		"a table and a large wardrobe.\n @@room_long@@");
	add_item("table", "An ordinary 4-leg wooden table standing in the middle of the room.\n");
	add_item(({"wardrobe", "large wardrobe"}), "Wooden wardrobe, covering entire wall.\n");
	add_skills();
}

public varargs int sk_hook_allow_train(object who, string str, string verb)
{
	if(sizeof(filter(all_inventory(TO), &->id("_bhkeeper_"))) == 0)
		return 0;
	return (who->query_guild_member(BHNAME) || who->query_wiz_level());
}

public void init()
{
	::init();
	init_skill_raise();
}