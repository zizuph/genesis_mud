/**********************************************************************
 * -  adv_guild.c                                                   - *
 * - Adventurer's guild for Port MacDunn in Khalakhor               - *
 * - Created by Khail - Mar 13/97                                   - *
 * - Adjusted to teach skills relevant to local quests              - *
 * - Tapakah, 09/2021                                               - *
 **********************************************************************/

#pragma strict_types

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#include "/d/Khalakhor/sys/defs.h"
#include "room.h"

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Khalakhor/std/room";

/*
 * Prototypes
 */
void set_up_skills ();

int *
query_local_coords ()
{
  return ({10,2});
}

int *
query_global_coords ()
{
  return VILLAGE_COORDS;
}

/*
 * Function name: create_khalakhor_room
 * Description  : Turns this object into an adventurer's guild.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
create_khalakhor_room ()
{
  set_short("The adventurer's guild of Port MacDunn");
  set_long("   This is the adventurer's guild of Port MacDunn. " +
           "The long, low ceiling of the single-room building " +
           "glows with a rich golden colour, the dressed wooden " +
           "rafters reflecting the glow of the fireplace which " +
           "attendants keep burning night and day for wayward " +
           "travellers. A handful talk amongst themselves in " +
           "the room, eager to teach you what skills they know " +
           "if you seek to 'learn' new skills or 'improve' old " +
           "ones. Occasionally, you'll see one or two 'meditate' " +
           "in silence.\n\n");

  add_item(({"fireplace"}),
           "The stone fireplace roars brightly with a burning " +
           "fire safely contained within. Occasionally, an " +
           "attendent will stoke it with a poker, or throw " +
           "another chunk of dried peat onto it if it seems " +
           "ready to die out.\n");
  add_item(({"attendants"}),
           "A handful of people dressed in villager's garb " +
           "wander about the room, or talk in small groups, " +
           "charged with the care of wanderers such as " +
           "yourself.\n");
  add_item(({"ceiling", "roof"}),
           "The ceiling of the building is low, and made " +
           "from large wooden rafters stretching across the " +
           "tops of the stone walls.\n");
  add_item(({"walls"}),
           "The walls of the building are made entirely from " +
           "large stones which have been carefully laid into " +
           "place, the joints sealed with mud or mortar of " +
           "some kind.\n");
  add_item(({"floor"}),
           "The floor is simply hard-packed earth.\n");

  add_exit(ROOM + "road_10_1","north");

  INSIDE;
  add_prop(OBJ_S_WIZINFO, "@@wizinfo");
  add_prop(OBJ_I_HAS_FIRE, 1);

  create_guild_support();
  create_skill_raise();
  set_up_skills();
}

/*
 * Function name: init
 * Description  : Initializes some things when an object
 *                enters the room. Here, it adds the commands
 *                used by guild_support.c and skill_raise.c
 * Arguments    : n/a
 * Returns      : n/a
 */
void
init ()
{
  ::init();

  init_skill_raise();
  init_guild_support();
}

/*
 * Function name: leave_inv
 * Description  : Called when an object leave our inventory. Used
 *                here to make sure the guild_support.c code knows
 *                when a player leaves the room.
 * Arguments    : ob - Object pointer to the object leaving.
 *                to - Object pointer to 'ob's new environment.
 * Returns      : n/a
 */
void
leave_inv (object ob, mixed to)
{
  ::leave_inv(ob, to);
  gs_leave_inv(ob, to);
}

/*
 * Function name: set_up_skills
 * Description  : Instructs this room what skills it trains.
 * Arguments    : n/a
 * Returns      : n/a
 */
void
set_up_skills ()
{
  string me, ot;

  me = "mix powders and potions"; ot = me;
  sk_add_train(SS_ALCHEMY,  ({ me, ot }),     0, 0, 20 );
  me = "defend yourself"; ot = "use defence skill";
  sk_add_train(SS_DEFENCE,  ({ me, ot }),     0, 0, 20 );
  me = "use a sword"; ot = me;
  sk_add_train(SS_WEP_SWORD,  ({ me, ot }),     0, 0, 30 );
  me = "use a knife"; ot = me;
  sk_add_train(SS_WEP_KNIFE,  ({ me, ot }),     0, 0, 30 );
  me = "swim around"; ot = me;
  sk_add_train(SS_SWIM,   ({ me, ot }),	 0, 0, 30 );
  me = "recognize and find herbs"; ot = me;
  sk_add_train(SS_APPR_OBJ,	({ me, ot }),      0, 0, 20 );
  me = "cast spells"; ot = me;
  sk_add_train(SS_SPELLCRAFT,	({ me, ot }), 0, 0, 20 );
  me = "climb"; ot = me;
  sk_add_train(SS_CLIMB,	({ me, ot }), 0, 0, 30 );
  me = "be aware of your surroundings"; ot = "his awareness";
  sk_add_train(SS_AWARENESS, ({ me, ot }),     0, 0, 30 );
}

/*
 * Function name: sk_hook_cant_train
 * Description:   Player can't train that skill that high for some reason
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to which the player wanted training
 * Returns:	  0
 */
int
sk_hook_cant_train (string skill, int to_lev)
{
  notify_fail("Several attendants try, but all fail to " +
              "to teach you how to improve your " + skill + " to " +
              "the ability of " + LANG_ADDART(sk_rank(to_lev)) + ".\n");
  return 0;
}

/*
 * Function name: sk_hook_unknown_skill
 * Description:   Player tries to improve or learn an unknown skill
 * Arguments:	  skill - The skill he sought for
 *		  verb  - 'learn' or 'improve'
 * Returns:	  0
 */
int
sk_hook_unknown_skill (string skill, string verb)
{
  notify_fail("The attendants seem rather puzzled at your " +
              "request, none of them seem to know anything about " +
              skill + " to teach you.\n");
  return 0;
}

/*
 * Function name: sk_hook_improve_unknown
 * Description:	  Player wants to improve a skill he has never learned
 * Arguments:	  skill - The skill
 * Returns:	  0
 */
int
sk_hook_improve_unknown (string skill)
{
  notify_fail("The attendants caution you to learn to " +
              "walk before you run, and suggest you try to learn " +
              skill + " first.\n");
  return 0;
}

/*
 * Function name: sk_hook_cant_pay
 * Description:   Player can't pay for session (kill him?)
 * Arguments:	  skill  - The skill
 *		  to_lev - The level to wich the player wanted training
 *		  cost   - The price
 * Returns:	  0
 */
int
sk_hook_cant_pay (string skill, int to_lev, int cost)
{
  notify_fail("The attendants look crestfallen, for " +
              "they have sworn an oath not to teach for free, " +
              "and you do not have the " + cost + " coppers " +
              "that training costs.\n");
  return 0;
}

/*
 * Function name: sk_hook_raise_rank
 * Description:   The player trains and pays, write something
 * Arguments:	  snum  - The skill he trained
 *		  to_lev - Which level he reached
 *		  cost   - How much he payed
 */
void
sk_hook_raise_rank (int snum, int to_lev, int cost)
{
  string rank,
    message_tp,
    message_others,
    poss,
    pron,
    obj;

  rank = sk_rank(to_lev);

  message_tp = "You readily pay the fee of " + cost + 
    " coppers, and the attendants ";    
  message_others = QCTNAME(TP) + " readily pays a " +
    "small fee, and the attendants ";

  poss = TP->query_possessive();
  pron = TP->query_pronoun();
  obj = TP->query_objective();

  switch(snum) {
  case SS_UNARM_COMBAT:
    if (to_lev < 11) {
	    message_tp += "slap you around " +
        "for awhile, until you " +
        "you start landing a few " +
        "yourself, and obtain a " +
        "skill in unarmed combat " +
        "equivalent to " + rank + ".\n";
	    message_others += "slap " + obj +
        "around silly for awhile, " +
        "until " + pron + " starts " +
        "landing a few " + obj + "self, " +
        "and obtains a skill in unarmed " +
        "combat equivalent to " + rank +
        ".\n";
    }
    else if (to_lev < 21)	{
	    message_tp += "soon have you throwing " +
        "punches and kicks until your " +
        "ability to fight unarmed is that " +
        "of " + LANG_ADDART(rank) + ".\n";
	    message_others += "soon have " + pron +
        "throwing punches and kicks until " +
        poss + " ability to fight " +
        "unarmed is that of " + 
        LANG_ADDART(rank) + ".\n";
    }
    else	{
	    message_tp += "start showing you a " +
        "few new punches, until they " +
        "realize you're winning and one " +
        "looks like he's nursing a broken " +
        "nose, at which point they proclaim " +
        "your unarmed combat skill that of " +
        LANG_ADDART(rank) + ".\n";
	    message_others += "start showing " +
        obj + " a few new punches, until " +
        "they realize " + pron + "'s winning " +
        "and one looks like he's nursing a " +
        "broken nose, at which point they " +
        "proclaim " + poss + " unarmed combat " +
        "skill to be that of " +
        LANG_ADDART(rank) + ".\n";
    }   
    break;
  case SS_DEFENCE:
    message_tp += "soon have you ducking and " +
      "dodging attack after attack, until " +
      "your defensive skills are those of " +
      LANG_ADDART(rank) + ".\n";
    message_others += "soon have " + obj +
      " ducking and dodging attack after " +
      "attack, until " + poss + " defensive " +
      "skills are those of " + LANG_ADDART(rank) +
      ".\n";
    break; 
  case SS_WEP_SWORD:
    if (to_lev < 21)	{
	    message_tp += "bring you a practice sword, " +
        "and with it you lunge and thrust, parry " +
        "and slash. When you return the weapon, " +
        "your ability with a sword is that of " +
        LANG_ADDART(rank) + ".\n";
	    message_others += "bring " + obj + " a practice " +
        "sword, and with it " + pron + " lunges and " +
        "thrusts, parries and slashes. When " + pron +
        " returns the weapon, " + poss + " ability " +
        "with a sword is that of " + LANG_ADDART(rank) +
        ".\n";
    }
    else	{
	    message_tp += "bring you a practice sword, " +
        "and after a few practiced strokes, " +
        "you deftly slice through one's belt, " +
        "dropping his pants to his ankles! " +
        "The others congratulate you on your " +
        rank + " skill with a sword as they " +
        "gasp for breath between fits of " +
        "howling laughter.\n";
	    message_others += "bring " + obj + " a " +
        "practice sword, and after a few " +
        "practiced stroked, " + pron + " deftly " +
        "slices through the belt of one of the " +
        "attendants, dropping his pants to his " +
        "ankles! The others congratulate " + obj +
        " on " + poss + " " + rank + " skill " +
        "with a sword as they gasp for breath " +
        "between fits of howling laughter.\n";
    }
    break;
  case SS_WEP_KNIFE:
    message_tp += "hand you a few small " +
      "daggers, and spend awhile instructing " +
      "you in their balance, and how to land " +
      "a lethal blow with one. By the time " +
      "you return them, you've the skill of " +
      LANG_ADDART(rank) + ".\n";
    message_others += "hand " + obj + " a " +
      "few small daggers, and spend awhile " +
      "instructing " + obj + " in their " +
      "balance, and how to land a lethal " +
      "blow with one. By the time " + pron +
      " returns them, " + pron + "'s attained " +
      "the skill of " + LANG_ADDART(rank) + ".\n";
    break;
  case SS_WEP_CLUB:
    message_tp += "loan you a big stick and " +
      "have you flail away at a bag of sand " +
      "like a maniac for awhile, taking it " +
      "back when they think you've the skill " +
      "of " + LANG_ADDART(rank) + " with a " +
      "club.\n";
    message_others += "loan " + obj + " a big " +
      "stick and have " + obj + " flail away " +
      "at a bag of sand like a maniac for " +
      "awhile, taking it back when they think " +
      pron + "'s the skill of " + 
      LANG_ADDART(rank) + " with a club.\n";
    break;
  case SS_APPR_OBJ:
    message_tp += "begin to jabber all at " +
      "once about what makes different " +
      "objects of different materials " +
      "bigger and heavier than others, " +
      "and before you've realized what " +
      "happens, they're proclaiming you " +
      "have the skill of " + 
      LANG_ADDART(rank) + " in appraising " +
      "objects.\n";
    message_others += "begin to jabber all " +
      "at once about what makes different " +
      "materials bigger and heavier than " +
      "others, and before you realize it, " +
      "they're proclaiming " + obj + " has " +
      "the skill of " + LANG_ADDART(rank) +
      " in appraising objects.\n";
    break;
  case SS_APPR_VAL:
    message_tp += "start lecturing on the " +
      "finer points of something called " +
      "'economics', which soons bores " +
      "you to a light sleep. Suddenly " +
      "you wake up to their affirmations " +
      "you've now the skill of " +
      LANG_ADDART(rank) + " in appraising " +
      "the value of objects.\n";
    message_others += "start lecturing " + obj +
      " on the finer points of something " +
      "called 'economics', which soon bores " +
      obj + " into a light sleep. You watch " +
      "in amusement as " + pron + " wakes with " +
      "a start as they tell " + obj + " " + pron +
      " now has the skill of " +
      LANG_ADDART(rank) + " in appraising the " +
      "value of objects.\n";
    break;  
  case SS_CLIMB:
    message_tp += "show you to a long rope " +
      "hanging from the ceiling, and tell " +
      "you the best way to climb it. ";
    message_others += "show " + obj + " to " +
      "a long rope hanging from the " +
      "ceiling, and tell " + obj + " the " +
      "best way to climb it. ";
    if (to_lev < 10)	{
	    message_tp += "They laugh out loud " +
        "as you fall on your butt after " +
        "barely getting your feet off " +
        "the floor, but you've still " +
        "gained the climbing ability of " +
        LANG_ADDART(rank) + ".\n";
	    message_others += "They laugh out " +
        "loud as " + pron + " falls on " +
        poss + " butt after barely getting " +
        poss + " feet off the floor, but " +
        pron + "'s still gained the climbing " +
        "ability of " + LANG_ADDART(rank) +
        ".\n";
    }
    else if (to_lev < 30)	{
	    message_tp += "They watch in amusement " +
        "as you struggle up the rope, and " +
        "burst into laughter as you lose " +
        "your grip halfway up and hit the " +
        "floor with a thud, despite your " +
        "newfound abilities as " +
        LANG_ADDART(rank) + " in climbing.\n";
	    message_others += "They watch in " +
        "amusement as " + pron + " struggles " +
        "up the rope, and burst out into " +
        "laughter as " + pron + " loses " +
        poss + " grip and hits the floor " +
        "with a thud, despite " + poss +
        " newfound abilities as " +
        LANG_ADDART(rank) + " in climbing.\n";
    }
    else {
	    message_tp += "They watch in amazement " +
        "as you clamber easily up the rope, " +
        "give the ceiling a slap, and drop " +
        "down again lightly to your feet, " +
        "and congratulate you on your " +
        "climbing skill as " +
        LANG_ADDART(rank) + ".\n";
	    message_others += "They watch in amazement " +
        "as " + pron + " clambers easily up " +
        "the rope, gives the ceiling a slap, " +
        "and drops down again lightly to " + 
        poss + " feet, and congratulate " + obj +
        " on " + poss + " climbing skill as " +
        LANG_ADDART(rank) + ".\n";
    }
    break;
  case SS_AWARENESS:
    message_tp += "instruct you how to extend " +
      "all of your senses to work with each " +
      "other, to detect things that alone " +
      "none of them could. Shortly, you " +
      "find your awareness is much improved, " +
      "to the standing of " + LANG_ADDART(rank) +
      ".\n";
    message_others += "instruct " + obj + " how " +
      "to extend all of " + poss + " senses to " +
      "work with each other, to detect things " +
      "that alone none of them could. Shortly, " +
      poss + " awareness is that of " +
      LANG_ADDART(rank) + ".\n";
    break;
  default:
    message_tp += "help you achieve the rank of " +
      LANG_ADDART(rank) + ".\n";
    message_others += "help " + obj + " achieve the rank of " +
      LANG_ADDART(rank) + ".\n";
  }

  write(message_tp);
  tell_room(environment(TP), message_others, ({TP}));
}

/*
 * Function name: sk_hook_no_list_learn
 * Description:   No more unknown skills for the player in this guild
 * Returns:	  1
 */
int
sk_hook_no_list_learn ()
{
  write("The attendants apologize, for they have " +
        "nothing new left to teach you.\n");
  return 1;
}

/*
 * Function name: sk_hook_no_list_improve
 * Description:   No more skills that the player can improve
 * Returns:	  1
 */
int
sk_hook_no_list_improve ()
{
  write("The attendants apologize, for they cannot " +
        "further improve any of your existing skills.\n");
  return 1;
}

/*
 * Function name: sk_hook_improved_max
 * Description:   Player can't improve this skill any higer
 * Arguments:	  skill - The skill player wanted to improve
 * Returns:	  0
 */
int
sk_hook_improved_max (string skill)
{
  notify_fail("The attendants seem completely baffled " +
              "by the whole concept of improving your " + skill +
              " skill any higher, obviously they will be of " +
              "no more use to you.\n");
  return 0;
}

