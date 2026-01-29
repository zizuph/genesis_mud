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
	
	set_short("The hall of knowledge.");
	
	set_long("The walls of this room are covered with enormous bookshelves"
		+" going from floor to ceiling. Books of every conceivable title"
		+" line the shelves together with scrolls, maps, drawings and various"
		+" bits of paper. It does seem rather organized though. The books"
		+" in the region you can reach are all about various forms of spellcraft"
		+". Small desks for reading are scattered throughout the room.\n");
		
	add_item(({"bookshelves", "shelves", "bookshelf", "shelf" }),
		"The tall oak bookshelves dominate this room entirely. They are filled"
		+" with everything a learing cult member needs to know about the arcane"
		+" arts.\n");
	
	add_item(({"book","books", "scroll","scrolls","maps","map","drawing",
		"drawings" }),
		"You rifle around the books and scrolls for a while browsing through"
		+" them, and find a small sign saying:\nHere you may <improve> skills"
		+" or <learn> new ones.\n");
	
	add_item(({"desk", "desks"}), "The desks are small and do not look"
		+" very comfortable.\n");
		
	add_item(({ "wall", "walls", "ceiling", "floor"}),
		"You cannot quite make out what the walls are made of, being covered"
		+" with bookshelves as they are, but you assume that they come from"
		+" the same material as the floor and the ceiling; cut directly from"
		+" the mountain. The ceiling is polished smooth but the floor has been"
		+" allowed to keep a slightly rugged surface to prevent slipping.\n");
	
	add_exit(CULT_DIR+"t_muntr","north",0);
	add_exit(CULT_DIR+"t_gather", "northeast", 0);

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
	   "mail if there is anything that needs to be fixed. See also t_muntr.c" +
	   " in this dir for another training loc to close.\n\n   /Gunther.\n";
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
    sk_add_train(SS_SPELLCRAFT,"general spell knowledge",0,0,90);
    sk_add_train(SS_ELEMENT_DEATH,"spells of the element of Death",0,0,90);
    sk_add_train(SS_ELEMENT_EARTH,"spells of the element of Earth",0,0,60);
    sk_add_train(SS_ELEMENT_WATER,"spells of the element of Water",0,0,50);
    sk_add_train(SS_FORM_ILLUSION,"creating illusions and phantasms",0,0,90);
    sk_add_train(SS_FORM_DIVINATION,"gaining information through magic",0,0,70);
    sk_add_train(SS_FORM_ABJURATION,"dispelling and resisting magic",0,0,50);
}
