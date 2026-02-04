/* -*- C++ -*- */

/*
 * frost1.c
 *
 * SOrgum 951216
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

public int do_light (string str);
public int do_turn (string str);
public int do_enter (string str);
public string west_wall ();

int opened;

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("do_light",  "light",  0);
    add_action("do_turn",  "turn",  0);
    add_action("do_enter",  "enter",  0);        
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short ("Frosty stairway");
    set_long ("You are following a long frosty stairway that abruptly comes to " +
	      "an end.  High, ice covered walls surround you on three " +
	      "sides (east, west, and north).\n");

    add_item(({"snow"}), "Don't you just wanna build a Snowman?\n");

    add_item(({"ground"}), "the ground is covered with ice and snow.\n");

    add_item (({"wall", "walls"}),
	      "They are frost covered with a smooth sheen that does not "+
            "appear to be entirely natural.\n");

    add_item (({"east wall"}),
	      "Looking closer at the eastern wall, you notice a dial with " +
	      "numbers ranging from zero to ninety-nine.\n");


    add_item ("dial", "It is large and is labeled with numbers.\n");

    add_item ("west wall", "@@west_wall");

    add_item (({"west door","door"}), "@@west_door");
    
    add_item (({"feast", "table"}),
	      "What a bountiful feast is this!  There are three main " +
	      "courses of beef, poultry, fish.  Assorted appetizers, " +
	      "several baskets of bread, a flowered centerpiece with " +
	      "a large candle in the middle, place settings for twelve, " +
	      "complete with napkins and all the utensils.  Several " +
	      "flagons of wine are scattered about the table.\n");

    add_item (({"candle", "large candle"}),
	      "It is 3 feet high and 2 inches around. It is intricately " +
	      "carved with runes.  It has a large wick.\n");

    add_item("wick", "It is a large wick. It looks like it would be "+
             "easy to light.\n");

    add_item ("north wall",
	      "Looking closer at the northern wall, you notice a giant " +
	      "crystal orb has been carved into a recess fifteen feet up.\n");

    add_item (({"orb", "cystal orb"}), "Light radiates within it.\n");

    add_item (({"door"}), "It is etched into the western wall.\n");
    add_item (({"flagon", "flagons"}),
	      "If only they were real!  A drink would warm you up some.\n");
    add_item (({"beef", "poultry", "fish", "course", "courses", "main corse",
		    "main courses"}),
	      "Looks fit for a king!\n");
    add_item (({"basket", "bread", "basket of bread", "baskets of bread"}),
	      "smallish dinner rolls, about the size of your fist.\n");
    add_item (({"appetizer", "appetizers"}),
	      "There are various tidbits of food here, suitable for a giant.\n");
    
	      
    OUTSIDE;
    opened = 0;

    add_exit ("/d/Terel/mountains/ice8", "south", 0);


}

public int
do_turn (string str)
{
    if (!strlen (str) || (str != "dial"))
    {
	NF ("Turn what?\n");
	return 0;
    }

    TP->catch_msg ("The dial is broken now.\n");
    return 1;
}

public string
west_wall ()
{
    string ret;

    if (opened)
    {
	ret = "Looking closer at the western wall, you see an "+
          "etching of a table set for a feast with a lighted "+
          "candle jutting out of it, confusing your eyes "+
          "which also perceive a door that is ajar!  It looks like "+
          "you could enter the doorway.\n";
    }
    else
    ret = "Looking closer at the western wall, you see an etching " +
	   "into the ice of a table set for a feast, with a real "+
         "candle jutting out from the wall.  The etching also shows " +
	   "a door behind the table.\n"; 

    return ret;
}
 

public string
west_door ()
{
    string ret;

    if (opened)
    {
	ret = "Your confused eyes seem to perceive a door that is ajar! "+
           "It looks like you could enter the doorway, but that might "+
           "not be a good idea, as this is frost giant territory.\n";
    }
    else
      ret = "The realistic etching gives the appearance of a door "+
          "behind the table, confusing your eyes.\n"; 

    return ret;
}
   

public int
do_light (string str)
{
    if (!strlen (str))
    {
	NF ("Light what?\n");
	return 0;
    }

    if (str == "wick")
    {
	NF ("Light wick with what?\n");
	return 0;
    }

    if (str == "wick with torch")
    {
	if (!present("torch", TP))
	{
	    TP->catch_msg("You have no torch!\n");
	    return 1;
	}
	
	tell_room (TO, QCTNAME(TP) + " lights the ice wick with a torch. " + 
		   "The ice portion of the door in the scene " +
		   "melts away!\n", TP);
	TP->catch_msg("You light the wick with your torch, and the ice " +
		      "portion of the door in the scene melts away!\n");
	opened = 1;
	return 1;
    }
}    

public int
do_enter (string str)
{
    if (!strlen (str))
    {
	NF ("Enter what?\n");
	return 0;
    }

    if ((str == "door") || (str == "doorway"))
    {
	if (opened == 0)
	{
	    TP->catch_msg ("There is no " + str + " here.\n");
	    return 1;
	}
    if(TP->query_average_stat() < 100)
    {
        TP->catch_msg("You tremble thinking about entering the door and "+
            "decide not to enter.\n");
        return 1;
    }

	TP->catch_msg ("You enter the doorway and a sick feeling settles in your stomach.\n");
	tell_room (TO, QCTNAME(TP) + " enters the doorway.\n", TP);
	TP->move_living ("through the doorway", FROST2_DIR + "frost2", 1);
	return 1;
    }
}
