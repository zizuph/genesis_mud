/*
 * /d/Gondor/lebennin/sirith/farms/npc/rooster.c
 *
 * taken largely from /d/Gondor/common/npc/crow.c
 */
#pragma strict_types

inherit "/d/Gondor/lebennin/sirith/farms/npc/livestock";
inherit "/std/act/action.c";
inherit "/std/act/domove.c";

#include <macros.h>		/* for IS_CLONE			*/
#include <const.h>		/* for G_MALE			*/
#include <ss_types.h>		/* for SS_DEFENCE, etc		*/
#include <stdproperties.h>	/* for CONT_I_WEIGHT, etc	*/
#include <wa_types.h>		/* for W_IMPALE, etc		*/

#include "/d/Gondor/defs.h"

public void	create_sirith_livestock();

/*
 * Function name:	create_sirith_livestock
 * Description	:	set up the rooster
 */
public void
create_sirith_livestock()
{
    if (!IS_CLONE)
    {
	return;
    }

    set_name( ({"rooster", "chicken", "fowl", "bird", "beast" }) );
    set_pname(({"roosters", "chickens", "fowl", "poultry",
	"birds", "beasts" }));
    set_race_name("chicken");
    set_gender(G_MALE);

    set_short("large rooster");
    set_adj( ({ "large", "speckled" }) );
    set_long(BSN("This large rooster has a black body, with a white head "+
	"and neck and long white tail feathers."));

    set_alignment(0);
    set_stats(({ 5, 20, 5, 5, 5, 5 }));

    set_skill(SS_AWARENESS, 90);
    set_skill(SS_DEFENCE,   40);

    add_prop(CONT_I_WEIGHT, 2268);	/* 5 lbs */
    /* 15" tall by 10" long by 8" wide */
    add_prop(CONT_I_HEIGHT, 38);	/* 15 inches */
    add_prop(CONT_I_VOLUME, 19665);	/* 1200 cubic inches */

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " is not able to carry anything.\n");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_attack_unarmed(0,  5, 15, W_IMPALE,            50, "beak");
    set_attack_unarmed(1, 15, 10, W_SLASH | W_IMPALE,  75, "claws");

    set_hitloc_unarmed(0, ({ 12, 12,  5}),  40, "body");
    set_hitloc_unarmed(1, ({ 15,  5, 15}),  20, "left wing");
    set_hitloc_unarmed(2, ({ 15,  5, 15}),  20, "right wing");
    set_hitloc_unarmed(3, ({ 20, 10,  5}),  10, "head");
    set_hitloc_unarmed(4, ({ 10, 10, 20}),  10, "claws");

    set_act_time(20);
    add_act("emote cackles loudly.");
    add_act("emote pecks at the ground.");
    add_act("emote flaps his wings.");
    add_act("peer");

} /* create_sirith_livestock */
