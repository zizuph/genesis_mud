/**********************************************************************
 * - train.c                                                        - *
 * - Training room of Eil-Galaith                                   - *
 * - npc Dromadus will load in here                                 - *
 * - Created by Damaris 09/Y2K                                      - *
 * - Recoded by Damaris 2/2002                                      - *
 * - Recoded by Damaris 4/2005                                      - *
 **********************************************************************/
#pragma strict_types

#include "../guild.h"
#include <ss_types.h>
#include <stdproperties.h>
inherit GUILD_ROOM;
inherit "/d/Khalakhor/lib/train";
inherit "/lib/guild_support";

public void
set_up_skills()
{
	create_skill_raise();
	sk_add_train(SS_LOC_SENSE, "be aware of surroundings", 0, 0, 50);
	sk_add_train(SS_DEFENCE, "defend yourself", 0, 0, 20);
	sk_add_train(SS_BLIND_COMBAT, "fight in the dark", 0, 0, 20);
	sk_add_train(SS_SWIM, "swimming", 0, 0, 30);
	sk_add_train(SS_CLIMB, "climbing", 0, 0, 40);
}

object meditate;

public void
create_guild_room()
{
	set_short("Training Hall");
	set_long("   This room is obviously a training hall. There "+
	"are a few tapestries along the walls. In here you may "+
	"increase your knowledge of a few skills. Dromadus is "+
	"eager to assist young and old alike in the ways of elven. "+
	"Also along the far wall there is a small sign with instructions "+
	"on it stating: Please use <help train> for more information.\n");
	add_item(({"tapestry", "tapestries"}),
	"The tapestries are made with vibrant silken threads. "+
	"Finely crafted with elven hands depicting elves in "+
	"battle scenes.\n");
	add_item(({"thread", "threads"}),
	"The silken threads which make of the tapestries are "+
	"vibrant and give depth to each tapestry.\n");
	add_item(({"training hall", "hall", "room"}), query_long);
	add_item(({"sign", "instructions"}),
	"Please use <help train> for more information.\n");
	add_cmd_item("sign","read","Please use <help train> for more "+
	"information.\n");
	add_cmd_item("instructions","read","Please use <help train> "+
	"for more information.\n");
	
	add_exit("start", "east");
	add_fail("auto", "You walked into a wall!\n"+
	"Ouch! That's gotta hurt!\n");
	
	add_prop(ROOM_I_INSIDE, 1);
	clone_here(NPC + "dromadus")->move(this_object());
	
	create_guild_support();
	set_up_skills();
}

public void
init()
{
	::init();
	init_skill_raise();
	init_guild_support();
	add_action("help","help");
}
