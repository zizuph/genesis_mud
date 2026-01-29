/* taken from Vingaard Keep coded by Percy. 
 * modified for the thief guild by Aridor 
 *
 * Modification log:
 *   - Aug 27, 2018: Added no-scry protection in guild (Gorboth)
 */

#include "guild.h"

inherit "/lib/skill_raise";
inherit ROOM_BASE

#include <stdproperties.h>
#include <ss_types.h>

int levlim;
object trainer;

/*
 * Prototypes
 */
void set_up_skills();

void
reset_thief_room()
{
    if (trainer)
      return;
    trainer = clone_object(TOBJ + "fourfinger");
    trainer->move_living("xxx",TO);
}

void
create_thief_room()
{
    set_short("Training room");
    set_long("You are in the training room. Here, some of the master " +
	     "thieves can help you improve your skills of different " +
	     "types in return for some money. You can either 'learn' " +
	     "a new skill or 'improve' a skill you already know about. " +
	     "The treasury is south, the fence is to the northeast and " +
	     "the quarters are north.\n");
    
    add_exit(GUILDR + "join", "south", 0);
    add_exit(GUILDR + "shop","northeast");
    add_exit(GUILDR + "start","north");
    
    create_skill_raise();
    set_up_skills();
    
    add_prop(ROOM_M_NO_SCRY, "Haze, and nothing more, is all that"
      + " appears.");

    reset_room();
}


void
init()
{
    init_skill_raise();
    ::init();
}

void
set_up_skills()
{
    sk_add_train(SS_WEP_KNIFE,  "use a knife",     0, 0, 60 ); /* 20 (= 30) */
    sk_add_train(SS_HIDE,       "hide from others",0, 0, 60 ); /*  0 */
    sk_add_train(SS_OPEN_LOCK,  "pick locks"      ,0, 0, 60 ); /* 30 */
    sk_add_train(SS_PICK_POCKET,"pick pockets"    ,0, 0, 60 ); /* 30 */
    sk_add_train(SS_AWARENESS,"be aware of things",0, 0, 60 ); /* 25 */
    sk_add_train(SS_SNEAK,      "sneak silently"  ,0, 0, 60 ); /*  0 */
    sk_add_train(SS_BACKSTAB,   "backstab people" ,0, 0, 60 ); /* 50 */
    sk_add_train(SS_FR_TRAP,"find and remove traps",0,0, 60 ); /* 50 */
    sk_add_train(SS_APPR_VAL,"appraise values",    0, 0, 60 ); /* 25 */
    sk_add_train(SS_TRADING,    "trade",           0, 0, 60 ); /* 45 */
    sk_add_train(SS_ACROBAT,    "be acrobatic",    0, 0, 60 ); /* 50 */
    
/* sum skills: 690,   sum above numbers in 'man skills': 340 (=350) => 6% tax*/
}


int
sk_improve(string sk)
{
    if (sk)
      {	
	  if (!MEMBER(TP) && !LAYMAN(TP))
	    {
		NF("You are no member of this guild, you cannot train " +
		   "here.\n");
		write("Only true guildmembers can improve their skills here.\n");
		return 0;
	    }
	  if (!trainer || (E(trainer) != TO))
	    {
		NF("The trainer is not here to teach you, I'm afraid.\n");
		return 0;
	    }
      }
    NF("You can't do this.\n");
    return ::sk_improve(sk);
}


int
sk_hook_improved_max(string skill)
{
    notify_fail("You cannot raise this skill any further here, you have to\n" +
		"seek knowledge elsewhere.\n");
    if (levlim)
      notify_fail("Sorry, but your rank doesn't allow you to train\n" +
		  "to that level in this skill.\n");
    return 0;
}

int
sk_query_max(int snum)
{
    int tlev, mxtrain, *skills_available_here;
    mixed skval,tmp;
    
    /* Added to adapt to the skill_decay function.            */
    /* If a skill isn't available here, this function should  */
    /* return 0.               Jeremiah, 95/07/09             */
    skills_available_here = sk_query_train();
    
    if(member_array(snum, skills_available_here) == -1)
      return 0;
    
    tlev = TP->query_thief_level();
    tmp = MAX_TRAIN[snum];
    if (tmp && sizeof(tmp))
      mxtrain = tmp[tlev];
    else
      mxtrain = 0;
    
    if (!mappingp(sk_default))
      return 0;
    
    skval = sk_trains[snum];
    
    
    if (skval[2] < mxtrain)
      {
	  mxtrain = skval[2];
	  levlim = 0;
      }
    else
      levlim = 1;
    if (sizeof(skval)>2)
      return mxtrain;
    else
      return 0;
}

int
send_trainer_to_tattoo_new_member(object who)
{
    if (!trainer)
      return 0;
    return (trainer->tattoo_new_member(who));
}
