/*
	*Pony, Maggot's farm
	*Altrus, April 2005
 *
 * 2005/05/01 Last update
 * 2011/08/02 Lavellan - Changed monster to creature so hitlocs/attacks work
 *                     - Improved descriptions and chances for them too
 *                     - Removed quickness and see invis (it's a pony!)
*/
//inherit "/std/monster";
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";
//inherit "/cmd/std/command_driver";
inherit "/d/Shire/common/lib/tell";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <wa_types.h>
#include <composite.h>
#include "/d/Shire/sys/defs.h"

#define A_KICK    0
#define A_LFFOOT  1
#define A_RFFOOT  2

#define H_BODY    0
#define H_BACK    1
#define H_HEAD    2
#define H_LFLEG  3
#define H_RFLEG  4
#define H_LHLEG  5
#define H_RHLEG  6
#define H_TAIL    7

//void create_monster()
void create_creature()
{
	set_name("pony");
	add_name("animal");
	add_adj("small");
	add_adj("grey-spotted");
	set_race_name("pony");
	
	set_short("small grey-spotted pony");
	
	set_long("This pony looks a bit worn, but healthy. It has probably served as a reliable work animal for many a year.\n");
	
	set_stats(({130, 150, 145, 5, 5, 50}));
	
	set_alignment(0);
	set_appearance(40);
	
	add_prop(CONT_I_WEIGHT, 60000);
	add_prop(CONT_I_HEIGHT, 400);
	
	set_skill(SS_UNARM_COMBAT, 50);
	set_skill(SS_AWARENESS, 50);
	
	//add_prop(LIVE_I_SEE_INVIS, 100);
	//add_prop(LIVE_I_QUICKNESS, 75);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop(LIVE_I_NEVERKNOWN, 1);
	
	set_attack_unarmed(A_KICK, 50, 60, W_BLUDGEON, 60, "back kick");
	set_attack_unarmed(A_LFFOOT, 40, 50, W_BLUDGEON, 20, "left front hoof");
	set_attack_unarmed(A_RFFOOT, 40, 50, W_BLUDGEON, 20, "right front hoof");
	
	//Remove default hit locations and implement new ones
	//for (int i = 0; i < 5; i++)
    //    remove_hitloc(i);
	
	/*set_hitloc_unarmed(H_BODY, 30, 20, "body");
	set_hitloc_unarmed(H_BACK, 30, 5, "back");
	set_hitloc_unarmed(H_HEAD, 20, 5, "head");
	set_hitloc_unarmed(H_LFLEG, 15, 8, "left front leg");
	set_hitloc_unarmed(H_RFLEG, 15, 8, "right front leg");
	set_hitloc_unarmed(H_LHLEG, 15, 7, "left hind leg");
	set_hitloc_unarmed(H_RHLEG, 15, 7, "right hind leg");
	set_hitloc_unarmed(H_TAIL, 5, 20, "tail");*/
	
	combat_reload();
	set_hitloc_unarmed(H_BODY, 30, 25, "body");
	set_hitloc_unarmed(H_HEAD, 20, 16, "head");
	set_hitloc_unarmed(H_LFLEG, 15, 14, "left front leg");
	set_hitloc_unarmed(H_RFLEG, 15, 14, "right front leg");
	set_hitloc_unarmed(H_LHLEG, 15, 14, "left hind leg");
	set_hitloc_unarmed(H_RHLEG, 15, 14, "right hind leg");
	set_hitloc_unarmed(H_TAIL, 5, 3, "tail");
	
	set_act_time(5);
	//add_act("emote shakes it mane lightly.");
	add_act("emote shakes its mane lightly.");
	add_act("emote nudges you slightly.");
	add_act("emote scuffs the floor with its hoof.");
}
