/* Vingaard Keep coded by Percy, Spring 1993
 * Dragonlance Quest added by Macker. 
 * New long desc and add_items by Teth, March 21 1996 
 * Spur Draconian Quest added by Grace, 3 Jun 1996
 * Museum Tour added by Kentari, February 1998
 * Modified July 2005 by Louie
 * - Removed QUERY_QUEST checks for disks of mishakal quest. 
 * - Quest is now repeatable, but only the first person to do the
 * - quest will set the good/evil in the quest_master.c
 * Modified March 2007 by Navarre.
 * - Removed QUERY_QUEST check for dragonlance quest.
 * - The quest is now repeatable.
 *
 * Removed age restriction for quests.
 * Arman, November 2018
 */

#include "../../guild.h"
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>    
#include <filter_funs.h>                 /* filter functions */          

#include TIME_FLOW

inherit IN_BASE;

#define     IS_SITTING       "_player_i_is_sitting"
#define     SIT_SUBLOC       "_subloc_sitting"                          
#define     CELL_KEY         "/d/Krynn/solamn/hctower/spur/obj/cell_key"
#define     Q_PRAYERBOOK     "/d/Krynn/solamn/hctower/spur/obj/prayerbook"
/*    Quest experience values     */
#define     LANCE_XP         15000
#define     SPURQDRAC         1500
#define     SPURVMUSEUM         60

void
reset_vin_room()
{
    if (!present("gunthar", TO))
      clone_object(VNPC + "gunthar")->move(TO);
}

void
create_vin_room()
{
    set_short("Vingaard Keep Inner Office");
    set_long("This well-furnished room is the office of a famous member "+
	     "of the Knights of Solamnia. A prominent table sits in one " +
	     "corner of the room, while a crescent of chairs occupy the " +
	     "northwestern area of the room. A woven rug rests comfortably " +
	     "on the stone floor. The west wall is decorated with a " +
	     "brilliant painting and the south wall bears a sign. The " +
	     "room is cozy, yet still an area that is very utilitarian. " +
	     "A stone arch in the south wall surrounds the doorway leading " +
	     "south and out of the room.\n");
    AI(({"prominent table", "table"}), "This stained oak table is " +
       "littered with papers and letters, some organized into a pile " +
       "and the rest scattered about.\n");
    AI(({"stained table", "oak table", "stained oak table"}), "Upon " +
       "closer inspection, you notice that the table looks rather " +
       "ancient. The edges of the table confirm this.\n");
    AI(({"edges", "table edges", "edge", "table edge"}), "The edge is " +
       "well-worn and sanded with the touch of many a Knight. The " +
       "occasional spot is nicked, perhaps with a sword blade.\n");
    AI(({"letters", "papers"}), "Which ones?\n");
    AI(({"scattered letters", "scattered papers"}), "These are " +
       "strewn about the table.\n");
    AI(({"organized letters", "organized papers"}), "These are " +
       "piled neatly in one corner. Perhaps they are the older " +
       "documents.\n");
    AI(({"documents", "older documents"}), "A quick glance reveals " +
       "that the top paper is a report on how to deal with visitors " +
       "to Vingaard Keep who have to poke and prod everything.\n");
    ACI(({"letters", "papers", "scattered letters",
	    "scattered papers", "organized letters", "organized papers"}),
	"read", "Quick scans of the letters and papers reveal them " +
	"to deal with mundane topics, such as Gunthar's memos to " +
	"the workers. There are some, however, written in an ancient " +
	"script that you do not understand. These bear the symbol " +
	"of Ergoth, and seem to be of some import.\n");
    AI(({"symbol of Ergoth", "Ergothian symbol", "symbol"}), "This " +
       "symbol is of a gull about to land.\n");
    AI(({"chairs", "crescent of chairs"}), "The chairs are made of " +
       "a dark polished wood, most likely black walnut imported from " +
       "Kalaman. Each bears a purple cushion that has been " +
       "embroidered with a golden pattern.\n");
    AI(({"cushion", "purple cushion"}), "It sure looks comfortable, " +
       "and by the rump impressions, well-used.\n");
    AI(({"impression", "rump impression", "rump impressions",
	   "impressions"}), "The impressions are quite big, but it just " +
       "makes sense they'd be as big as the largest rump.\n");
    AI(({"pattern", "golden pattern"}), "Nothing too fancy, just some " +
       "zigs and zags running parallel down the cushion.\n");
    AI("chair", "Each chair is made of a dark polished wood, possibly " +
       "black walnut. Also, each is adorned with a purple cushion " +
       "embroidered with a golden pattern. The chair appears to be " +
       "made for sitting on.\n");
    AI(({"walls", "wall", "floor", "ceiling", "north wall", "east wall",
	   "south wall", "west wall", "stone floor"}), "The entire room " +
       "is made of the typical granite rock that has been used to " +
       "construct Vingaard Keep.\n");
    AI(({"rug", "woven rug"}), "This woven rug is cotton-coloured, " +
       "and has seen better days.\n");
    AI(({"painting", "brilliant painting"}), "This painting is " +
       "certainly old. It is surrounded by a slate frame. The " +
       "painting itself is of Vinas Solamnus, the founder of the " +
       "Knights of Solamnia. This scene shows him giving those in his " +
       "army loyal to Ergoth a chance to leave and go home, instead " +
       "of joining Vinas Solamnus in the rebellion against the cruel " +
       "Ergothian king.\n");
    AI(({"frame", "slate frame"}), "The slate frame is a non-glossy " +
       "black that reflects little light. It must be quite heavy.\n");
    AI(({"arch", "stone arch"}), "This arch is an example of " +
       "Solanthian construction, with its high arc at the apex.\n");
    AI("sign", "@@read_sign");
    ACI("sign", "read", "@@read_sign");
    
    add_exit(VROOM + "great_hall", "south", 0, 0, 1);
    
    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
	     "teleportation in this area... or is it something else?\n");
    
    LIGHT;
    add_my_desc("@@chair_desc@@", this_object());
    reset_vin_room();
}

void
init()
{
    ::init();
    ADD("do_sit", "sit");
    ADD("do_rise", "rise");
    ADD("do_rise", "stand"); 
    ADA("reward");
    ADA("quest");
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (this_player()->query_prop(IS_SITTING))
    {
	this_player()->remove_prop(IS_SITTING);
	this_player()->remove_subloc(SIT_SUBLOC);
    }
} 

/*
 * This makes it so that only Knights may 
 * initiate combat in _their_ guildhall
 */
int
fight_func()
{
    if (!(MEMBER(TP)))
    {
	write("Only Solamnian Knights may initiate combat here.\n");
	return 1;
    }
    return 0;
}


string
read_sign()
{
    return ("The sign reads:\n"+
	    "    These are desperate times and I am short-handed. If you are\n"+
	    "    interested, I have several quests available.\n"+
	    "        Type 'quest'    To take a quest assignment.\n"+
	    "        Type 'reward'   When you have completed a quest.\n"+
	    "\n");
}

/* 
 * Gives the player a QUEST:
 *      Visit Museum (Knights' Spur)
 * 	Question Draconian (Knights' Spur)
 *      Disks of Mishakal (Xak Tsaroth)
 *      DragonLance (Icewall)
 */    
int
quest()
{
    int prp;
    object cell_key;
    object q_prayerbook;
    
    NF("Gunthar is not here to give out any quests currently.\n");
    if (!P("gunthar",TO))
      return 0;
    NF("You have already done all the quests possible here.\n");
    
    /* VISIT KNIGHT MUSEUM QUEST */
    
    if (!(TP->test_bit("Krynn", 3, 2)))
    {
	if (TP->query_alignment() < 50 )
	{
	    write("Gunthar looks you over carefully, taking your measure.\n" +
		  "Gunthar says: You don't look trustworthy enough for this "+
		  "task, friend.\n"+
		  "Gunthar says: Darkness shadows your heart, and with that "+
		  "taint upon you, I question your loyalty to our Cause.\n"+
		  "Gunthar says: Improve your trustworthiness and I will "+
		  "have something for you to do.\n");
	    return 1;
	}
	if ((q_prayerbook = present("_q_prayerbook", TP)))
	{
	    write("Gunthar says: I've already assigned you a task!\n"+
		  "Gunthar says: You are to deliver the prayerbook to "+
		  "Ellard at the museum in the Knights' Spur.\n");
	    return 1;
	}
	write("Gunthar says: I am glad you wish to aid the cause of the " +
	      "Knighthood. As with most things in life, the first step " +

	      "towards reaching a goal is attaining knowledge.\n"+
	      "Gunthar says: My friend Ellard is the curator at the " +
	      "museum of the Knights of Solamnia. There you can learn " +
	      "of the Knighthood of old, and in doing so discover the " +
	      "benevolent gifts Paladine bestowed upon his followers.\n");
	write("Gunthar gets a distant look upon his face.\n");
	write("You hear Gunthar whisper under his breath: ...and may one " +
	      "day bestow upon us again...\n");
	write("Gunthar gives you a small prayerbook.\n"+
	      "Gunthar says: This prayerbook represents the core of a " +
	      "Knight, second only to perhaps the Oath and the Measure.\n");
	clone_object(Q_PRAYERBOOK)->move(TP,1);
	write("Gunthar says: Please take it to Ellard in the museum as he " +
	      "has put in a request for one.\n" +
	      "Gunthar says: When you have done this, return to me for your " +
	      "reward.\n");
	TP->add_prop("_spur_visit_museum", 1);
	say(QCTNAME(TP) + " speaks quietly with Gunthar.\n");
	return 1;
    }
    
    
    /* QUESTION DRACONIAN QUEST */
    
    if (!(TP->test_bit("Krynn", 3, 4)))
    {
	if (TP->query_alignment() < 150 )
	{
	    write("Gunthar looks you over carefully, taking your measure.\n" +
		  "Gunthar says: You don't look trustworthy enough for this "+
		  "task, friend.\n"+
		  "Gunthar says: Darkness shadows your heart, and with that "+
		  "taint upon you, I question your loyalty to our Cause.\n"+
		  "Gunthar says: Improve your trustworthiness and I will "+
		  "have something for you to do.\n");                   
	    return 1;
	}
	if ((cell_key = present("_cell_key", TP))) 
	{
	    write("Gunthar says: I've already assigned you a task!\n"+
		  "Gunthar says: You are to question the draconian "+
		  "being held prisoner in the cell at the Knights' Spur.\n");
	    return 1;
	}
	write("Gunthar says: I have been informed that there is a baaz "+
	      "draconian being held prisoner at the Knights' Spur.\n"+
	      "Gunthar says: This draconian is a high-ranking officer in the "+
	      "Blue Army. He has resisted Palanthian efforts at interrogation.\n");
	write("Gunthar gives you a key.\n"+
	      "Gunthar says: This is the key to the cell at the Knights' Spur.\n");
	clone_object(CELL_KEY)->move(TP);     
	write("Gunthar says: It is your task to question this draconian "+
	      "and succeed where others have failed.\n"+
	      "Gunthar says: Return to me with information regarding DragonArmy "+
	      "activity, and you will be well-rewarded.\n");
	TP->add_prop("_spur_draconian_quest", 1);
	say(QCTNAME(TP) + " speaks quietly with Gunthar.\n");             
	return 1;
    }  
    
    /* DISKS OF MISHAKAL QUEST */
    
    if (!(TP->test_bit("Krynn", 2, 2)))
    {
/*      Removed age restrictions for quests

	if (REALAGE(TP) < 691200)	
	{
	    write("Gunthar says: I don't think you are ready for " +
		  "this kind of adventure yet. Become a bit older first.\n");
	    return 1;
	}
*/

	if (TP->query_alignment() < 450 )
	{
	    write("Gunthar looks you over carefully, taking your measure.\n" +
		  "Gunthar says: You don't look trustworthy enough for this "+
		  "task, friend.\n"+
		  "Gunthar says: Darkness shadows your heart, and with that "+
		  "taint upon you, I question your loyalty to our Cause.\n"+
		  "Gunthar says: Improve your trustworthiness and I will "+
		  "have something for you to do.\n");                   
	    return 1;
	}
	/**** MODIFIED Louie July 2005
	if (QUERY_QUEST("black_dragon"))
	{
	    write("Gunthar says: I'm sorry, currently I do not have any more " +
		  "tasks for you to do. Please check with me regularly, I " +
		  "have a use for a helping hand frequently, just not at this " +
		  "time.\n");
	    return 1;
	}
	*******/
	write("Gunthar says: I have heard reports about one of the items"
	      + " of power that will be needed to defeat the dragon queen. It is"
	      + " thought that the holy Disks of Mishakal are being guarded by"
	      + " evil creatures in Xak Tsaroth, an ancient city ruined during"
	      + " the cataclysm. Find the disks and return them to me.\n");
	prp = TP->query_prop("_player_i_black_dragon_quest");
	/*if you have this prop set you find more money in the treasure chest*/
	TP->add_prop("_player_i_black_dragon_quest",prp | 16);
	return 1;
    }
    
    /* DRAGONLANCE QUEST */
    
    else if (!(TP->test_bit("Krynn", 2, 13)))
    {
/*      Removed age restrictions for quests

	if (REALAGE(TP) < 864000)
	{
	    write("Gunthar says: I don't think you are ready for " +
		  "this kind of adventure yet. Become a bit older first.\n");
	    return 1;
	}
*/

	if (TP->query_alignment() < 450 )
	{
	    write("Gunthar looks you over carefully, taking your measure.\n" +
		  "Gunthar says: You don't look trustworthy enough for this "+
		  "task, friend.\n"+
		  "Gunthar says: Darkness shadows your heart, and with that "+
		  "taint upon you, I question your loyalty to our Cause.\n"+
		  "Gunthar says: Improve your trustworthiness and I will "+
		  "have something for you to do.\n");                   
	    return 1;
	}


	/************ MODIFIED BY NAVARRE, TO ALLOW MORE THAN 1 PLAYER TO DO IT
	if (QUERY_QUEST("dragonlance"))
	{
	    write("Gunthar says: I'm sorry, currently I do not have any more " +
		  "tasks for you to do. Please check with me regularly, I " +
		  "have a use for a helping hand frequently, just not at this " +
		  "time.\n");
	    return 1;
	}
**************/
	write("Gunthar says: " +
	      "The people of Krynn face a severe trial. We are being overcome " +
	      "by the evil forces of Takhisis and her minions. " +
	      "The time has come to recover the legendary might of the past. . . " +
	      "Fetch the Dragonlance, that with it, we might succeed in banishing " +
	      "the evil dragons once and for all. " +
	      "I cannot tell you exactly where to look for it, although it is " +
	      "rumored to lie somewhere far to the south. " +
	      "I have heard of an ancient text in the Palanthas Library which " +
	      "offers some information on the dragonlance.\n" +
	      "\nReturn the dragonlance to me for your reward.\n");
	TP->add_prop("_player_i_lance_quest", 1);
	TP->add_prop("_player_m_pal_lib_audition",
		     ({"say Oh! You are here to see Astinus?",
			 "say You must be the one Gunthar sent the message about.",
			 "say Yes, Astinus is expecting you.", "icewall"}));
	return 1;
    }
    return 0;
}

/* 
 * REWARD the player for any quests he may have done. 
 */
int
reward(string str)
{
    object ob;
    int prp, xp = 6000;
    if (!str)
    {
	NF("You have done no quests to be rewarded for!\n");
	
	/* DISKS OF MISHAKAL QUEST REWARD */
	if (ob = present("black_item", TP))
	{
	    ob->remove_object();
	    seteuid(getuid(this_object()));
	    if (!(TP->test_bit("Krynn", 2, 2)))
	    {
/*      Removed age restrictions for quests

		if (REALAGE(TP) < 691200)
		{
		    write("Gunthar says: I don't think you were ready to go " +
			  "on this kind of adventure all alone yet. Become a " +
			  "bit older first.\n");
		    return 1;
		}
*/
/**** MODIFIED Louie July 2005
		if (QUERY_QUEST("black_dragon"))
		{
		    write("Gunthar says: I have already received the Disks of Mishakal. " +
			  "Did you find another copy? Interesting... Hmm. Or did you " +
			  "steal them from the knights? Well, I can't prove that. Either " +
			  "way, I suggest you contact me about this later, when the " +
			  "time is again right.\n");
		    return 1;
		}
**********/
		write("Gunthar says: Well done! The disks will give us the power"
		      + " of good necessary to defeat the evil queen.\n");
		
		prp = TP->query_prop("_player_i_black_dragon_quest");
		if (prp & 1)		/* means s/he got the bottle him/herself*/
		  xp += 10000;
		if (prp & 2)		/* means s/he killed the dragon */
		  xp += 4000;
		if (prp & 4)		/* means s/he filled acid in bottle */
		  xp += 2000;
		if (prp & 8)		/* means s/he poured acid on lock */
		  xp += 2000;
		if (xp >= 20000)
		  write("You feel much more experienced!\n");
		else
		  write("You feel more experienced!\n");
		TP->add_exp(xp, 0);
		seteuid(getuid(this_object()));
		TP->set_bit(2, 2);
		TP->remove_prop("_player_i_black_dragon_quest");
		
		K_QUEST_LOG("quest", "Black dragon quest (GOOD)",
			    TP, xp);
    /*** ADDED Louie July 2005 ***/
        if (!QUERY_QUEST("black_dragon")) {
		INTERRUPT_PERIOD("kitiara","patrol vkeep");
		DONE_QUEST("black_dragon");
		(ARMYMASTER)->done_quest("black_dragon_good");
        }
		return 1;
	    }
	    write("Gunthar says: Thanks once again for returning the disks to me.\n");
	    return 1;
	}
	
	/* DRAGONLANCE QUEST REWARD */
	if(ob = P("dragon_lance", TP))
	{
	    ob->remove_object();
	    seteuid(getuid(this_object()));
	    if(!(TP->test_bit("Krynn", 2, 13)))
	    {
/*      Removed age restrictions for quests

		if (REALAGE(TP) < 864000)
		{
		    write("Gunthar says: I don't think you were ready to go " +
			  "on this kind of adventure all alone yet. Become a " +
			  "bit older first.\n");
		    return 1;
		}
*/

/******************** Commented out by Navarre march 2007, to allow people to solve the quest.
		if (QUERY_QUEST("dragonlance"))
		{
		    write("Gunthar says: I have already received the Lance of Huma. " +
			  "Did you find another copy? Interesting... Hmm. Or did you " +
			  "steal them from the knights? Well, I can't prove that. Either " +
			  "way, I suggest you contact me about this later, when the " +
			  "time is again right.\n");
		    return 1;
		}
******************/
		write("Gunthar says: Excellent! You have returned Huma's " +
		      "legendary lance to the Knights. You have once again helped " +
		      "the forces of good in Krynn to increase our advantage " +
		      "in our constant fight with the dark queen.\n");
		if((TP->query_prop("_player_i_visited_library") & 2) &&
		   TP->query_prop("_player_i_visited_library"))
		{
		    TP->set_bit(2,13);
		    TP->remove_prop("_player_i_lance_quest");
		    TP->add_exp(LANCE_XP, 0);
		    write("You feel more experienced.\n");
		    
		    K_QUEST_LOG("quest", "Lance quest", TP, LANCE_XP);
		    DONE_QUEST("dragonlance");
		    (ARMYMASTER)->done_quest("dragonlance");
		    return 1;
		}
		else
		{
		    write("Gunthar says: In order to get experience for this quest " +
			  "you have to come see me beforehand, and " +
			  "visit the library in Palanthas. How did you " +
			  "know what to do, anyway?\n");
		    return 1;
		} /* Did or didn't do necessary things for exp */
	    }	
	    else
	    {
		write("Gunthar says: Now we have two lances.\n" +
		      "Gunthar goes hmmm.\n" +
		      "Gunthar says: Interesting.\n" +
		      "Gunthar shrugs.\n");
		return 1;
	    }	/* Already did the quest once before */
	} /* Didn't have the lance */
	
	/* VISIT KNIGHT MUSEUM QUEST REWARD */
	if ( (TP->query_prop("_spur_visit_museum")) &&
	    (!(TP->test_bit("Krynn", 3, 2))) )
	{
	    if (TP->query_prop("_succeed_deliver_prayerbook"))
	    {
		write("Gunthar smiles warmly.\n"+
		      "Gunthar says: I thank you for helping to bring " +
		      "joy to one of my Knights.\n" +
		      "Gunthar says: Hopefully you were able to learn " +
		      "something new, or perhaps just something forgotten.\n");
		write("Gunthar winks and you feel a bit more experienced!\n");
		say(QCTNAME(TP) + " receives a reward from Gunthar.\n");
		seteuid(getuid(this_object()));
		TP->add_exp(SPURVMUSEUM, 0);
		TP->set_bit(3, 2);
		TP->remove_prop("_succeed_deliver_prayerbook");
		TP->remove_prop("_spur_visit_museum");
		
		K_QUEST_LOG("quest", "Visit Knight Museum Quest",
			    TP, SPURVMUSEUM);
		return 1;
	    }
	    else
	    {
		write("Gunthar says: I remember that you've been given this "+
		      "task before.\n");
		return 1;
	    } /* Done the quest before */
	    
	    return 0;
	} /* str existed */
	
	
	/* QUESTION DRACONIAN QUEST REWARD */          
	if ( (TP->query_prop("_spur_draconian_quest")) &&
	    (!(TP->test_bit("Krynn", 3, 4))) )
	{
	    if (TP->query_prop("_i_beat_draconian"))
	    {   
		if (MEMBER(TP))
		{
		    write("Gunthar frowns.\nGunthar intones: You have "+
			  "shamed yourself and the Knighthood.\n");
		    TP->change_prestige(-3); /* take away prestige */
		}
		write("Gunthar cries: There is no Honour in what you have "+
		      "done!\nGunthar says: Torturing prisoners of war is "+
		      "inexcusable!\nGunthar says: Get out of my sight! If "+
		      "I see you before the Black Moon shines white, it will "+
		      "be too soon!\n");
		say(QCTNAME(TP) + " is shamed before Gunthar.\n");                 
		TP->remove_prop("_spur_draconian_quest");
		return 1;      
	    } /* no bits set: player can try again and do it right */                      
	    if (TP->query_prop("_succeed_question_draconian"))
	    {
		if (MEMBER(TP))
		{
		    write("Gunthar smiles proudly.\n"+
			  "Gunthar intones: You have shown great wisdom "+
			  "and diplomacy.\n"+
			  "Gunthar says: Having compassion for your enemy "+
			  "reveals magnanimity of spirit--a quality "+
			  "in every great Knight.\n");
		    write("Gunthar's praise raises your prestige within the Knighthood.\n");
		    TP->change_prestige(5000); /* give prestige */
		}
		write("Gunthar says: Truly, the information you have gained "+
		      "will be of great service to the Cause of Good "+
		      "in this Land.\nGunthar says: I cannot adequately "+
		      "express my gratitude at your skillful and honourable "+
		      "questioning of the prisoner.\n");
		write("You feel more experienced!\n");
		say(QCTNAME(TP) + " receives a reward from Gunthar.\n");          
		seteuid(getuid(this_object()));
		TP->add_exp(SPURQDRAC, 0);
		TP->set_bit(3, 4);
		TP->remove_prop("_succeed_question_draconian");
		TP->remove_prop("_spur_draconian_quest");
		
		K_QUEST_LOG("quest", "Question Draconian Quest",
			    TP, SPURQDRAC);
		(ARMYMASTER)->done_quest("drac_prisoner");
		return 1;
	    }
	    else
	    {
		write("Gunthar says: I recall that you've tried questioning the "+
		      "prisoner before.\nGunthar says: You've had your chance.\n");
		return 1;
	    }	/* Done the quest before */
	    
	    return 0;
	} /* str existed */
    }
}


/* 
 * Code for chairs
 */
nomask static int
do_sit(string str)
{
    object *pl;
    int i;
    
    pl = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());
    pl = filter(pl, "filter_sitting_in_chair", this_object());
    
    NF("Sit where?\n");
    if (str && str != "chair" && str != "in chair" &&
	str != "on chair" && str != "down")
      return 0;
    
    NF("You cannot sit in two chairs at once!\n");
    if (this_player()->query_prop(IS_SITTING))
      return 0;
    else
    {
	this_player()->add_prop(IS_SITTING, 1);
	write("You sit in one of the chairs.\n");
	say(QCTNAME(this_player()) + " sits in one of the chairs" +
	    ".\n");
    }
    this_player()->add_subloc(SIT_SUBLOC, this_object());
    return 1;
}        
nomask static int
do_rise(string str)
{
    
    NF("Rise from where?\n");
    if (str && str != "chair" && str != "from chair")
      return 0;
    
    NF("You are already standing.\n");
    if (!this_player()->query_prop(IS_SITTING))
      return 0;
    
    else
    {
	this_player()->remove_prop(IS_SITTING);
	/*this_player()->unset_no_show_composite();*/
	this_player()->remove_subloc(SIT_SUBLOC);
	write("You get up from the chair.\n");         
	say(QCTNAME(this_player()) + " gets up from the chair.\n");
    }
    return 1;
}


static int
filter_sitting_in_chair(object pl)
{
    return pl->query_prop(IS_SITTING) == 1;
}

static int
filter_remove_sit(object pl)
{
    /*pl->unset_no_show_composite();*/
    return 1;
}

static int
filter_add_sit(object pl)           
{
    /*pl->set_no_show_composite(1);*/
    return 1;
}

static string
map_live(object pl)
{
    if (pl == this_player())
      return "you";
    return pl->query_the_name(this_player());
}

nomask string
chair_desc()
{
    object *pls;
    string *who, str = "";
    int i;
    
    pls = FILTER_CAN_SEE(FILTER_LIVE(all_inventory()), this_player());           
    pls = filter(pls, "filter_sitting_in_chair", this_object());
    filter(pls, "filter_remove_sit", this_object());
    
    who = map(pls, "map_live", this_object());
    filter(pls, "filter_add_sit", this_object());
    if (sizeof(pls) == 1 && pls[0] == this_player())
      str += " You are sitting in one of the chairs.";
    else if (sizeof(pls) > 1)
      str += " " + capitalize(COMPOSITE_WORDS(who)) +
	" are sitting in " + LANG_WNUM(sizeof(pls)) +
	  " of the chairs.";
    
    else if (sizeof(pls))
      str += "" + capitalize(COMPOSITE_WORDS(who)) +
	" is sitting in a chair.";
    
    str += "\n";
    return break_string(str, 70); 
}

nomask string
show_subloc(string subloc, object on, object for_pl)
{
    string str;
    
    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) ||
	subloc != SIT_SUBLOC)

      return "";
    if (for_pl == on)
      str = "You are";
    else
      str = capitalize(on->query_pronoun()) + " is";
}                                


