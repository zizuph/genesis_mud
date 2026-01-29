/* A circle of stones located at Emerald/Blackwall/valley1/encrypt.
   It is a container, capable of holding objects which are players answers
   to the encrypted riddles found at that location. It destroys any objects
   which are put within it, in spectacular manner.

   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>
#include "/d/Emerald/quest_handler/quest_handler.h"

inherit "/std/container";

void
create_container()
{
    set_name("stones");
    add_name("circle");
    set_adj("white");
    add_adj(({"circle", "of"})); //allows the object to respond to
                                 //"circle of stones"
    set_short("circle of stones");
    set_long("At the very center of the central mound of vines lies a "+
	     "circle of foot-tall white stones. The circle is barely a "+
	     "metre in diameter and raw earth lies within. This is the "+
	     "only portion of the glade which is not vegetated to some "+
	     "degree. You get a strange yearning to put something "+
	     "within the circle, but at the same time, your intuition "+
	     "suggests that placing the wrong thing within the circle "+
	     "might be dangerous.\n");

    add_prop(CONT_I_ATTACH, 0);
    add_prop(CONT_I_MAX_VOLUME, 50000);
    add_prop(CONT_I_MAX_WEIGHT, 50000);
    add_prop(OBJ_M_NO_GET, "The circle of stones cannot be taken "+
	     "intact.\n");
    add_prop(MAGIC_AM_MAGIC, ({40, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO,
	     ({"The circle of stones is clearly a focal point for "+
		 "the magic of the glade.\n", 15, "Strong summoning "+
		 "and identification magic are present within the "+
		 "confines of the circle.\n", 40, "The magic is of "+
		 "a strange nature, as if the creation of something "+
		 "very far from human.\n", 60}));
    
}

/* Determines whether or not an object has an id matching any provided
   in an array of strings. Returns 1 (true) if it does, 0 otherwise.
*/
int
test_name(object answer, string* names)
{
    int i;//loop index

    for (i = 0; i < sizeof(names); i++)
    {
	if (answer->id(names[i]))
	{
	    return 1;
	}
    }
    return 0;
}
       

/* Determines whether or not an object is a satisfactory answer to the
   riddle posed in encrypt.c (where this object resides).
   
   arg object - the object to be tested
   returns 1 : if the object satisfies the riddle
   returns -1: the object satisfies an answer to a different riddle then the
               one posed (assumption: the player is cheating)
   returns 0 : if the object does not satisfy the riddle and does not
               answer any of the riddles
*/

int
test_answer(object answer)
{
    string* names; //a list of names which make-up answers to riddles other
                   //than the one currently being asked
    int riddle = environment(this_object())->get_riddle();
    //this gets the number of the riddle currently set in the encrypt.c

    switch (riddle)
    {
    case 0: //answer = fire
      
      if (answer->id("lamp") || answer->id("torch") || answer->id("candle"))
	{
	    /*the answer is correct IF the torch or lamp is lit so we next
	      check to see if it emits light */
	    if (answer->query_prop(OBJ_I_LIGHT) > 0)
	    {
		return 1; //the riddle was answered correctly
	    }

	    return 0; //answer was incorrect, there is no fire in an
	              //unlit lamp or torch
	}

	//setting names to answers to other riddles which could not possibly
	//be considered as answers to the current riddle
	names = ({"egg", "skull", "ring", "necklace", "die",
		      "chalk board", "medallion", "amulet"});
	break;

    case 1: //answer egg
       
	if (answer->id("egg")){return 1;}
	
	names = ({"lamp", "torch", "skull", "die", "candle", "chalk board"});
	break;

    case 2: //answer skull

	if (answer->id("skull")) { return 1;}
	
	names = ({"lamp", "torch", "egg", "die", "candle", "chalk board",
		      "ring", "medallion", "necklace", "amulet"});
	break;

    case 3: //answer ring or necklace

	if (answer->id("ring") || answer->id("necklace") ||
	    answer->id("medallion") || answer->id("amulet"))
	    //consider medallion and amulet close enough to necklace
	{
	    return 1;
	}

	names = ({"lamp", "torch", "skull", "egg", "candle", "chalk board"});
	break;

    case 4: //answer six-sided die

	if (answer->id("die")) { return 1;}

	names = ({"lamp", "torch", "skull", "egg", "candle", "chalk board",
		      "necklace", "ring", "medallion", "amulet"});
	break;

    case 5: //answer candle

	if (answer->id("candle")) { return 1;}
		
	names = ({"lamp", "skull", "egg", "candle", "chalk board",
		    "necklace", "ring", "medallion", "amulet", "die"});
	break;

    default: // (case 6) answer water - anything containing
	// water will do

	if (answer->query_prop(OBJ_I_CONTAIN_WATER)){ return 1;}

	names = ({"lamp", "skull", "egg", "candle", "chalk board",
		    "necklace", "ring", "medallion", "amulet", "die"});
    } //end switch
    
    if (test_name(answer, names))
    {
	return -1; //player cheated, in all likelihood; he gave answer to
	           //another riddle
    }
	
    return 0; //wrong answer, but not the answer to another riddle
}	    

/* This function is called from enter_inv (via alarm) when there is
   reasonable reason to believe that a player has cheated in coming up
   with his answer to the quest riddle.

   Args - object ob, the object which was used to answer the riddle
*/

void
kill_cheater(object ob)
{
    write("Eerily, the wind begins to pick up around you. Soon, it "+
	  "is gusting all around you at gale force. Then, you notice "+
	  "a flash of light from the within the circle of stones. "+
	  "You notice that the " + ob->short() + " has burst into "+
	  "brilliant multi-hued flames. Then, as you watch, the flames "+
	  "begin to grow higher and higher. As if by magic, a tongue "+
	  "of flame leaps from the circle of stones and strikes you!\n"+
	  "You catch fire and the flames quickly engulf your form. "+
	  "Screaming in agony, you get the the distinct feeling that "+
	  "someone or something is VERY displeased with you.\n");

    this_player()->set_hp(-500); //must do this before killing someone
    this_player()->do_die(environment(this_object())); //player dies

    ob->remove_object();
    environment(this_object())->update_light(1);
}

/* This function is called from enter_inv (via alarm) when a player has
   correctly answered the riddle by placing the correct object within
   the circle.
   
   Args - object ob, the object which was used to answer the riddle.
*/

void
reward_solution(object ob)
{
    object stone1, stone2, stone3; //teleport_stones given out as quest
                                   //reward (if applicable)
    
    write("As soon as you place the " + ob->short() + " within the "+
	  "circle, you notice smoke beginning to arise from it. Shortly "+
	  "thereafter, the " + ob->short() + " bursts into flames!\nQuickly "+
	  "the flames consume it, leaving behind not ashes, but three "+
	  "delicate crystalline stones!\n");
    write("An apparition of a beautiful winged woman appears to you. "+
	  "She tells you: Very well done mortal. Take the stones as "+
	  "a token of my appreciation for your intellect.\n");

    stone1 = clone_object(BLACKWALL_DIR + "obj/teleport_stone");	
    stone2 = clone_object(BLACKWALL_DIR + "obj/teleport_stone");
    stone3 = clone_object(BLACKWALL_DIR + "obj/teleport_stone");
    
    stone1->move(this_object());	
    stone2->move(this_object());
    stone3->move(this_object());
    
    if (QH_QUEST_COMPLETED(this_player(), "Faerie_riddle2"))
    {
	    
	/*the player has just completed the second  part of the 
	  Faerie riddle quest - the award is taken care of by the
	  QH_QUEST_COMPLETED macro. */
	
	if (this_player()->query_average_stat() > 50)
	{
	    write("You feel much more experienced.\n");
	}
	
	else
	{
	    write ("You feel more experienced.\n");
	}
    }
    
    else
    {
	//award could not be given for some reason:
	write("If there is no reason why you should "+
	      "not be awarded experience for your "+
	      "actions, please file a bug report.\n");
    }

    ob->remove_object();
    environment(this_object())->update_light(1);
}

/* This function exists to be called from an alarm so that the message 
   "You put the <x> into the circle of stones" is written before
   the object is destroyed, and before any further write statements
   are made (ie write statements called by the function argument). It
   examines the object which entered the inventory and determines if
   it answers the riddle posed by the quest.  It also checks to see if
   it was likely placed in the stone in an effort to cheat at the
   quest.
   
   arg object foreign - the object which entered the circle and is to
                        be destroyed  
*/

void
deal_with_inventory(object foreign)
{  
    if (test_answer(foreign) == -1)
    {   //player is considered to have cheated
	kill_cheater(foreign);
	return;
    } 

    if (test_answer(foreign) == 1)
    {	/* The player answered the riddle correctly */
	reward_solution(foreign);
	return;
    }

    /* The object entering the inventory was not a correct answer, but
       there is no reason to suspect cheating. */

    write("Shortly after you place the " + foreign->short() + " upon the "+
	  "ground within the circle, you notice smoke beginning to "+
	  "arise from it. Then, the " + foreign->short() + " bursts into "+
	  "brilliant orange flame, the fire consuming it entirely "+
	  "within moments.\n");

    foreign->remove_object();
    environment(this_object())->update_light(1);
}

/* Redefined so that something special occurs if the answer to the riddle
   enters its inventory, and something nasty happens to a player
   who happens to place something else into the inventory which corresponds
   to the answer to another riddle which might be within the clearing.
   This is used to make cheating by attempting to guess which riddle
   is encrypted dangerously impractical. Also, anything placed within
   the container is destroyed, regardless of whether or not it is an
   answer (correct or otherwise) to a riddle.
*/

public void
enter_inv(object ob, object from)
{
    ::enter_inv();

    if (ob->id("_faerie_teleport_stone"))
    {
      //the quest reward must be able to enter this object without being
      //destroyed - we dont do anything further  
    }

    else
    {
	/* Deal further with the impact of an object entering the
	   inventory after printing "You put <x> into the circle"
	   messages are printed. */
	set_alarm(0.1, 0.0, &deal_with_inventory(ob));
    }
}


   





