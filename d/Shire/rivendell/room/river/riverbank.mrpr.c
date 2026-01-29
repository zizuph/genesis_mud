/*
 * West bank of bruinen ford
 * Finwe, August 1998
 */
#pragma save_binary
#pragma strict_types

#include "local.h" 
 
inherit FOREST_BASE;

int check_player(string str);

void
create_forest_room()
{
    set_extraline("A large ford is to the east. " + 
        "The forest surrounds you and is peaceful " +
        "here. The river flows along past you. It looks calm " +
        "but there is evidence that it overflows its banks as " +
        "there are washed up logs, sticks, and debris on the " +
        "banks here.\n");
  
    add_item(({"forest","oak forest","trees"}),
      	"The ancient oaks look ominous and gloomy as they grow " +
      	"here. They tower over you as they reach for the sky.\n");
    add_item(({"mountains", "misty mountains", "foothills"}),
      	"The tops of the Misty Mountains rise up before you. " +
      	"They look forbidding and dangerous as they stand in " +
      	"the distance. The foothills appear sporadically " +
		"between the trees on the other side of the river.\n");
    add_item(({"path", "paths"}),
        "A path leads west back to the Great East Road.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "The river flows east out of the mountains south here. " +
        "There is a shallow place here that allows for " +
        "travellers to cross when the river is low. Now and " +
        "again, a leaf or a branch floats by.\n");
    add_item(({"ford", "river ford", "ford of bruinen", 
            "ford of the river bruinen"}),
        "The ford is a shallow place in the river allowing " +
        "travellers to cross into the forest beyond. It looks " +
        "like the river would come up to the knees of an " +
        "average human. An occasional boulder stands in the river.\n");
    add_item(({"debris"}),
        "You notice broken logs and branches, sticks, leaves, " +
        "and large rocks washed up on the bank, evidence that " +
        "the river gets violent on occasion.\n");
    add_item(({"broken branches", "broken branch"}),
		"The broken branches look like they have been ripped or " +
		"broken from trees. Their ends are shattered and " +
		"splintered.\n");
    add_item(({"stump", "stumps"}),
		"You don't see any here.\n");
    add_item(({"large rocks", "large rock"}),
		"They are scattered about the banks of the river.\n");
    add_item(({"bank", "banks"}),
		"The bank is covered in short grass and gently slopes " +
		"down to the river's edge.\n");
    add_item(({"grass"}),
		"The grass is a healthy green and short. It grows all " +
		"the way to the edge of the river.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER); 

    reset_shire_room();
 
    add_exit(RIVER_DIR + "shore06", "north",0, 2);
    add_exit(RIVER_DIR + "shore05", "south",0, 2);
//    add_exit(RIVER_DIR + "in_ford", "east", "@@check_player@@", 2);
/*
    add_exit(RIVER_DIR + "in_ford", "east", "@@block_me@@", 2);
*/
    add_exit(WR_DIR + "imladris_connect", "west", 0, 2);

}

void
init()
{   
    ::init();
    add_action("drink_it", "drink");
    add_action("check_player", "enter");
}


int
block_river()
{
    if (this_player()->query_wiz_level()) 
	return 0;

    write("The river boils and churns as you enter the ford.\n"+
	  "It tosses you about violently and drags you under.\n" +
	  "You swim hard back to the river bank and manage to survive.\n");
    return 1;
}

void
reset_shire_room()
{
}
 

int check_player(string str)
{
    /* Mrpr: Ok, this test is correct, you check for river, ford or
             bruinen and do something if they managed to get that
	     part right. 
    */
    if ((str == "river") || (str == "ford") || (str == "bruinen"))
    {
	/* Mrpr: Now you test if people can enter, and if they can
	         you VERY strangely return 0, i.e. disallow the
		 move. This happens every time you manage to write
		 the correct syntax and CAN_ENTER allows you to
		 enter (or if you are a wizard). I suggest you
		 rethink this part. Also, besides just turning
		 people down (return 0) you should have made a
		 notify_fail() message so that people will understand
		 WHY the command failed. For example:

		 notify_fail("Don't ask why, but you can't do that.\n");
		 return 0;

		 However, I must admit I fail to see why anyone
		 should be stopped from entering the ford. If some
		 players can enter it, why not others? Better make
		 up a real good explanation there :)
	*/
        if (CAN_ENTER(TP) || this_player()->query_wiz_level())
            return 0;

	/* Mrpr: Ok, now you check for the "_no_cross_" property.
	         Imho, it's bad form to use magic numbers or strings
		 directly in code. This is not a bug as such, just
		 possible cause for problems later. Make a
		 #define NO_CROSS_PROP "_no_cross_"
		 in the top of the document instead, and use the
		 define (NO_CROSS_PROP) throughout the code. 
	*/
	if(!TP->query_prop("_no_cross_"))
        {
	    /* Mrpr: Ok, they didn't have the property, so you write
	             some kind of message to them, add the property
		     and then eat the command (return 1). All good
		     and well; a chance to reconsider a stupid move.
	    */
            write("\n" +
		  "The river boils and churns before you, as if to " +
		  "warn you of impending doom, or even death, if you " +
		  "enter the ford. You step back as you consider " +
		  "your options.\n\n");
            say("The river boils and churns suddenly.\n");
            TP->add_prop("_no_cross_",1);
            return 1;
        }

	/* Mrpr: Now they have the property set, which means
	         they decided to move into the ford anyway. You
		 write a message to that effect and then move them
		 into the ford room. HOWEVER, you then return 0,
		 i.e. signal that the command failed?! Why? I
		 think this is a typo of some kind.
	*/
        write("You head east into the ford.\n");
        say(QCTNAME(TP)+ " leaves east into the ford.\n");
        TP->move_living("M", "/d/Shire/rivendell/room/river/in_ford",1);
        return 0;
    }

    /* Mrpr: This is the result of not typing river, ford or bruinen
       	     as the argument to the enter command. This is almost but
	     not quite correct. Instead of write() you should have a
    	     notify_fail() here instead, so that another object which
    	     defines "enter" but with another argument should have a
    	     chance of grabbing the command in its turn. As it is written
    	     now, other objects DO get to grab the command (you return
       	     0), but the error message is ALWAYS printed anwyay, which
	     is wrong. Remember that the last stored notify_fail()-message
	     is used if all commands that uses this command name return 0.
    */
    write("Enter what? The ford?\n");
    return 0;
}
 
int drink_it(string s)
{
 
    int amount;
 
    if(s == "water" || s == "water from river")
    {
	amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
	if (TP->drink_soft(amount))
	{
	    TP->catch_msg("You kneel before the river, dipping " +
			  "your cupped hands into the river and get a " +
			  "drink of the clear icy water. Its taste " +
			  "refreshes your mind and body.\n");
 
	    say(QCTNAME(TP)+" kneels before the river and gets a " +
                "drink.\n");
           
	}
	else
	{
	    write("You cannot drink more water.\n");
	}
 
	return 1;
    }
    else
	NF("Drink what?\n");
}
 
int
block_me()
{
    if (this_player()->query_wiz_level()) return 0;

    write("The river has flooded its banks, making it " +
	  "impossible to cross. Eventually, though, the river " +
	  "should recede and allow passage across it.\n");
    return 1;
}
