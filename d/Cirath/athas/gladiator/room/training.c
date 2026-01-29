/* training.c: Glad training room: Shiva, ?.
 *     Modified: Serpine, 4/27/95.
 *     Training functions moved from npc: Serpine, 3/29/96.
 */
inherit "/std/room";
inherit "/d/Cirath/std/shiva_train.c";
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"


/*
#define IS_GLAD_MASTER (TEST_GBIT(TP, GLAD_TRAIN_MASTER))
*/
#define IS_GLAD_MASTER (1)
#define IS_GLAD_GURU   (TEST_GBIT(TP, GLAD_TRAIN_GURU))

void
set_up_skills()
{
	create_skill_raise();
	sk_add_train(SS_CHARGE, "charge an opponent", "charge", 85, 100);
	sk_add_train(SS_BERSERK, "enter a berserked state", "berserk",80, 100);
	sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy", 0, 70);
	sk_add_train(SS_2H_COMBAT, "fight with two weapons", "two handed combat", 0, 90);
	
	sk_add_train(SS_WEP_AXE, "fight with an axe", "axe", 0, 100);
	
        sk_add_train(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat",0,30);
        sk_add_train(SS_PARRY, "parry blows", "parry", 0, 90);
        sk_add_train(SS_DEFENCE, "avoid attacks", "defence", 0, 90);
        sk_add_train(SS_AWARENESS, "be more aware", "awareness", 0, 40);
        sk_add_train(SS_ACROBAT, "be more acrobatic", "acrobat", 0, 30);
        
        
    // sk_add_train(SS_APPR_OBJ, "appraise objects", "appraise object", 0, 50);
    // Appraise Object removed June 2000 by Decius
}

void
reset_room()
{
    bring_room_mob("barkara", GLAD_NPC+"trainer.c", 1, 1);
}

void
create_room()
{
	::create_room();
	set_short("training hall");
        set_long("All around you is the chaos of combat practice, " +
	"only barely kept in check by the harsh scrutiny of the "+
	"trainer. Dozens of gladiators are engaged in sparring and "+
	"training, only occasionally being whipped for lack of "+
	"performance.\nWithin this place you may use the abilities "+
	"listed by <help training>.\n");
	add_item(({"gladiator", "gladiators"}),
	"They seem very absorbed in their training. And only pause "+
	"to give you the most casual of stony glances.\n");
	INSIDE
	add_exit(GLAD_ROOM+"stairwy2", "west", 0, 1);
	reset_room();
	set_up_skills();
}

varargs int
sk_query_max(int skill, int silent)
{
    switch(skill)
    {
	/*
       case SS_2H_COMBAT:
	   if (!IS_GLAD_MASTER) return 60;
	   if (!IS_GLAD_GURU) return 72;
	   break;
       case SS_APPR_MON:
	   if (!IS_GLAD_MASTER) return 50;
	   break;
       case SS_BERSERK:
	   if (!IS_GLAD_MASTER) return 70;
	   if (!IS_GLAD_GURU) return 90;
	   break;
       case SS_CHARGE:
	    if (!IS_GLAD_MASTER) return 70;
	   if (!IS_GLAD_GURU) return 90;
	   break;
       case SS_DEFENCE:
	   if (!IS_GLAD_MASTER) return 60;
	   break;
	       */

    case SS_WEP_AXE:
	if (!IS_GLAD_GURU) return 90;
	break;
    default:
	return ::sk_query_max(skill, silent);
    }
    return ::sk_query_max(skill, silent);
}
void
init()
{
    ::init();
    init_skill_raise();
    add_action("help","help");
}

int sk_no_train(object who)
{
    if (!objectp(present("barkara", E(who))))
    {
	who->catch_msg("Nobody seems here to help you.\n");
	return 1;
    }

    if (!IS_MEMBER(who))
    {
	command("say Only true Gladiators of Athas may train here!");
	return 1;
    }

    if (CHECK_PUNISHMENT(TP, PUN_BAR))
    {
	command("say Sorry " + TP->query_name() + ", but you are " +
	  "considered unworthy to train here by the Overseers.");
	return 1;
    }
    return 0;
}
