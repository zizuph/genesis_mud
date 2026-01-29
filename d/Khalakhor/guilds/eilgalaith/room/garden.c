/**********************************************************************
 * - garden.c                                                       - *
 * - Eil-Galaith Garden room                                        - *
 * - May train herbing skills here                                  - *
 * - npc Mateo will load in here along with pickable fruit.         - *
 * - Created by Damaris 08/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Removed pickable fruit because it seems to cause the room not  - *
 * - to load at times and I've not time to figure it out ATM        - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/

#pragma strict_types

#include "../guild.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
inherit GUILD_ROOM;
inherit "/d/Khalakhor/lib/train";
inherit "/lib/guild_support";

#define PATH "/d/Khalakhor/guilds/eilgalaith/room/ceremony"
public void
set_up_skills()
{
	create_skill_raise();
	sk_add_train(SS_HERBALISM, "identify herbs", 0, 0, 50);
	sk_add_train(SS_SPELLCRAFT, "cast spells", 0, 0, 50);
	sk_add_train(SS_ELEMENT_LIFE,  "cast life spells", 0, 0, 20);
	sk_add_train(SS_ELEMENT_AIR,  "cast air spells", 0, 0, 20);
	sk_add_train(SS_FORM_DIVINATION, "use the magic form divination", 0, 0, 20);
	sk_add_train(SS_FORM_CONJURATION, "use the magic form conjuration", 0, 0, 20);
	sk_add_train(SS_ALCHEMY, "create potions", 0, 0, 10);
	sk_add_train(SS_LANGUAGE,  "speak and understand languages", 0, 0, 50);
}


object meditate;

void
create_guild_room()
{
	set_short("Eil-Galaith Garden");
	set_long("   This lovely garden has many plants and flowers "+
	"growing here varying in size. Vines cascade upwards and "+
	"form walls with pink and white blossoms. An air of mystery "+
	"and magic permeates this garden. There is a noticable "+
	"path leading to a grove. Also along the far wall "+
	"there is a small sign with instructions on it stating: "+
	"Please use <help train> for more information.\n");
	add_item(({"room", "area"}), query_long);
	add_item(({"garden", "room"}),
	"This garden is peaceful with many plants and flowers. There "+
	" are also a few fruits growing here as well. The "+
	"bristle of life growing all around you provides this garden "+
	"with peace and sanctuary.\n");
	add_item(({"path"}),
	"There is a path leading to a small grove.\n");
	
	add_item(({"plants", "plant", "flower", "flowers"}),
	"There are a multitude of plants and flowers varying in size, "+
	"shape and colour.\n");
	add_item(({"blossom", "blossoms"}),
	"Many beautiful pink and white blossoms are scattered along "+
	"the vines. They are small in size but very fragrant.\n");
	add_item(({"wall", "walls"}),
	"The walls are created by the long vines that are intertwined "+
	"with each other and beautiful blossoms blanket them.\n");
	add_item(({"sign", "instructions"}),
	"Please use <help train> for more information.\n");
	add_cmd_item("sign","read","Please use <help train> for more "+
	"information.\n");
	add_cmd_item("instructions","read","Please use <help train> for "+
	"more information.\n");
		
	add_exit("start", "south");
	add_fail("auto", "You walk into a wall of vines and get tangled "+
	"up!\nMateo stares at you as you somehow manage to get free.\n");
	clone_here(NPC + "mateo")->move(this_object());
	create_guild_support();
	set_up_skills();
}
int
enter_path(string str)
{
	if (str != "path")
	{
		return notify_fail("Enter what?\n");
	}
	write("You start on the path finding your way through the trees.\n\n");
	say(QCTNAME(TP) + " starts down the path.\n");
	TP->move_living("M", PATH, 1, 0);
	
	say(QCTNAME(TP)+" suddenly appears through a grove of trees.\n");
	return 1;
}
public void
init()
{
	::init();
	init_skill_raise();
	init_guild_support();
	add_action("help","help");
	add_action(enter_path, "enter");
}
