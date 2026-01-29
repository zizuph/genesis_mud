/* 
 *  This file is /d/Gondor/school/path/grasshopper.c by Justus.
 *  This file is derived from random_orc.c by Tricky.
 *
 *  Modification history:
 *  Gnadnar 1-Dec-97  made the actions more those of a grasshopper,
 *		      and removed silly reactions to shout/laugh.
 *		      also made more dextrous, less intelligent & wise.
 */
#pragma strict_types

inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";
inherit "/std/act/action.c";
inherit "/std/act/domove.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define A_JUMP 0
#define A_BITE 1
#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

#define RADJ ({ ({"tiny","green"}), ({"tiny","brown"}), \
	({"little","beige"}), ({"little", "green"}), \
	({"little", "brown"}), ({"little", "black"}) })

#define RLONG ({ \
    "This is the tiniest of grasshoppers. Still, it can jump as high " \
  + "as your head.\n", \
    "This tiny brown grasshopper is climbing around in the grass.\n", \
    "The little beige grasshopper doesn't look particularly strong. " \
  + "However, it might be hard to hit since it's hopping around "\
  + "all the time.\n", \
    "This green little grasshopper has strong legs, good for jumping.\n",\
    "This little grasshopper is a beautiful golden brown colour.\n", \
    "The little black grasshopper leaps about vigorously.\n" })

#define RWEIGHT ({ 10, 10, 20, 20, 20, 50 })    /* from 10 to 50 grams */

		/* str dex con int wis dis */
#define RSTAT ({ \
		({  1, 15, 1,  5,  5,  5 }), \
		({  1, 15, 1,  5,  5,  5 }), \
		({  3, 15, 3,  5,  5,  5 }), \
		({  3, 15, 3,  5,  5,  5 }), \
		({  3, 15, 3,  5,  5,  5 }), \
		({  3, 20, 5,  5,  5,  5 }) })

#define SKUCOM ({ 1,1,2,2,2,5 }) /* unarmed combat */
#define SKDEF  ({ 1,1,5,5,5,10 }) /* defence */

public string	ghop_combatmsg();

void
create_creature() 
{
    int  ran = random(6);

    set_name("grasshopper");
    add_name(({"_random_grasshopper_"}));
    set_pname("grasshoppers");
    set_pshort(implode(RADJ[ran], " ") + " grasshoppers");
    set_race_name("grasshopper"); 
    set_adj(RADJ[ran]);
    set_long(BS(RLONG[ran]));
    set_gender(G_NEUTER);
    add_prop(CONT_I_WEIGHT,RWEIGHT[ran]);
    add_prop(CONT_I_HEIGHT,RWEIGHT[ran]);
    add_prop(CONT_I_VOLUME,RWEIGHT[ran]);
    add_leftover(NPC_DIR + "grasshopper_meat", "meat", 1, 0, 0, 0);
    add_leftover(NPC_DIR + "grasshopper_leg", "leg", 2, 0, 0, 0);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 
	"The grasshopper is too tiny to carry anything.\n");

    set_stats(RSTAT[ran]);
    set_skill(SS_UNARM_COMBAT, SKUCOM[ran]);
    set_skill(SS_DEFENCE, SKDEF[ran]);

    set_attack_unarmed( A_JUMP, 12, 5, W_BLUDGEON,  80, "jump");
    set_attack_unarmed( A_BITE,  5, 5, W_SLASH,     30, "tiny jaws");
   
    set_hitloc_unarmed( H_HEAD, ({ 1, 1, 1}), 10, "head");
    set_hitloc_unarmed( H_BODY, ({ 1, 1, 1}), 80, "body");
    set_hitloc_unarmed( H_LEGS, ({ 1, 1, 1}), 10, "long jumping legs");
    /* Hard to hit though because it's hopping around all the time! */

    set_act_time(7);        /* Set some random actions */    
    add_act("emote leaps high in the air.");
    add_act("emote nibbles on a stalk of grass.");
    add_act("emote remains perfectly still.");
    add_act("emote flies for a moment, fluttering softly in the air, "+
	"to land on a tall stalk of grass.");

    set_cact_time(7);
    add_cact(VBFC_ME("ghop_combatmsg"));
}

public string
ghop_combatmsg()
{
    object	pl;
    int		i;
    string	sstr;

    if ( objectp(pl = query_attack()) )
    {
	i = random(4);
	sstr = short();
	tell_object(pl, 
	    ({
	    "The "+sstr+" clicks its tiny jaws furiously at you.\n",
	    "The "+sstr+" leaps high in the air to dodge you.\n",
	    "The "+sstr+" flies into your face!\n",
	    "The "+sstr+" suddenly jumps behind you.\n"
	    })[i]);
	tell_room(ENV(),
	    ({
	    "The "+sstr+" clicks its tiny jaws furiously at "+
		QTNAME(pl)+".\n",
	    "The "+sstr+" leaps high in the air to dodge "+QTNAME(pl)+".\n",
	    "The "+sstr+" flies into "+QTNAME(pl)+"'s face!\n",
	    "The "+sstr+" suddenly jumps behind "+QTNAME(pl)+".\n"
	    })[i], pl);
    }
    return "";
}
