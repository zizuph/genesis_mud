
/* 
	*A bedroom in the house of farmer Maggot
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

#define SLAY 	"_laying_on_bed"
#define SSIT 	"_sitting_on_bed"

inherit BASE_HOUSE;
inherit "/d/Shire/std/room";

void create_shire_room()
{
	set_short("In a bedroom inside a small house");

	set_long(short() + ". Considering this is a farm house, " +
	"the accomodations are quite plush. A rather large, " +
	"comfortable bed occupies a corner, with a wooden " +
	"nightstand next to it. There is a dresser standing against " +
	"one of the walls beside an open closet. Two " +
	"windows are set into the walls here, looking to the yard " +
	"outside.\n");
	
	add_item(({"bed"}), "The bed is amazingly soft; it must " +
	"be stuffed with down. The pillows feel the same. " +
	"The quilt covering the bed is enormous, falling over the " +
	"sides and trailing on the floor. It looks like it would be very comfortable to lay on.\n");
	add_item(({"pillows", "pillow"}), "The pillows are filled " +
	"with down, and are very large.\n");
	add_item(({"quilt"}), "It is a patchwork quilt. The stitching " +
	"detail is amazing; the scenes on each patch are quite " +
	"lively. It looks quite comfortable and perfect for snuggling.\n");
	add_item(({"stitching", "scenes", "detail", "patches"}), "The detail " +
	"of the scenes on the quilt is amazing, depicting various " +
	"places, animals, and different aspects of hobbit life.\n");
	add_item(({"dresser"}), "The dresser appears to be " +
	"made of a solid wood, probably oak. It is about as tall " +
	"as a hobbit, and twice as wide as one.\n");
	add_item(({"dresser drawers", "drawers"}), "The drawers are filled with neatly folded clothing.\n");
	add_item(({"wood", "solid wood", "oak"}), "The wood of the dresser appears to be oak.\n");
	add_item(({"closet"}), "Inside the closet you can see " +
	"a few articles of clothing; there are shirts, coats and dresses " +
	"mostly.\n");
	add_item(({"clothing", "articles", "clothes"}), "The " +
	"clothes are simply made, modest in decor, but look " +
	"quite durable, perfect for life on a farm.\n");
	add_item(({"shirts"}), "Most of them look like the " +
	"the rugged attire of someone who fills his day with " +
	"hard toil in the fields, but there are also a couple " +
	"of nicer, more decorative, shirts that look to be " +
	"for special occasions.\n");
	add_item(({"coats"}), "There are only a couple of " +
	"coats in here; they are very drab-colored.\n");
	add_item(({"dresses"}), "They are plain dresses for " +
	"the most part, made for enduring the endless hours " +
	"of hard work that are required for keeping a house " +
	"such as this in good condition.\n");
	add_item(({"windows", "window"}), "There are two " +
	"windows here, one set into the east wall, and one " +
	"set into the south wall. Which window do you want? " +
	"The east one or the south one?\n");
	add_item(({"east window"}), "Outside the east " +
	"window you can see a well-kept yard with a few " +
	"trees bordering it. There is a red barn to the east " +
	"of the house.\n");
	add_item(({"south window"}), "Outside the south " +
	"window you can see a well-kept yard with a few " +
	"trees bordering it. There is a lane just south of " +
	"the house.\n");
	add_item(({"yard"}), "You can see a yard outside " +
	"the windows.\n");
	add_item(({"trees"}), "Through the windows, you " +
	"can see small trees bordering the yard.\n");
	add_item(({"barn"}), "Through the east window " +
	"you can see a faded-red barn.\n");
	add_item(({"lane"}), "Through the south window " +
	"you can see a hedge-lined lane running east and " +
	"west.\n");
	add_item(({"nightstand"}), "The nightstand is " +
	"placed next to the bed. It looks solidly made. There " +
	"are a few odds and ends on top of it.\n");
	add_item(({"odds and ends", "odds", "ends"}), "There appears to be a hand mirror, a small mug, and some kind of cross-stitching.\n");
	add_item(({"hand mirror", "mirror"}), "It is a very " +
	"small mirror, set into a tin frame. It has a small handle.\n");
	add_item(({"frame", "tin frame"}), "The frame is not very decorative, but houses the mirror adequately enough.\n");
	add_item(({"handle", "small handle"}), "The handle is very small, almost as if it were made for a child's hand.\n");
	add_item(({"small mug", "mug", "clay mug"}), "It is " +
	"a simple clay mug. Probably it is filled with water " +
	"before its owner goes to sleep, to prevent " +
	"midnight trips out of bed to get a drink.\n");
	add_item(({"cross-stitching", "cross-stitch"}), "It looks like " +
	"a project the wife of the house is working on, " +
	"but it is not far enough along to tell what it " +
	"will be.\n");
	
	set_add_house();
	set_add_rtells_house();
	
	add_exit(ROOM_DIR + "maggothall01", "west");

	reset_shire_room();
}

void reset_shire_room()
{
	
}

void init()
{
	::init();
	add_action("action_sit", "sit");
	add_action("action_lay", "lay");
	add_action("action_stand", "stand");
	add_action("jump_bed", "jump");
	add_action("snuggle_bed", "snuggle");
}

int action_sit(string str)
{
	if(TP->query_prop(SSIT))
	{
		write("But you are already sitting on the bed!\n");
		return 1;
	}
	   
	if(TP->query_prop(SLAY))
	{
		write("But you are laying on the bed! Perhaps " +
		"you should stand up first.\n");
		return 1;
	}
	   
	if(str == "down" | str == "on bed" | str == "on the bed" | str == "bed") 
	{
		TP->catch_msg("You sit down on the bed.\n");
		say(QCTNAME(TP) + " sits down on the bed.\n");
		TP->add_prop(SSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT,", sitting on the bed");
		
		return 1;
	}
}

int action_lay(string str)
{
	if(TP->query_prop(SSIT))
	{
		write("But you are already sitting on the bed! Perhaps " +
		"you should stand up first.\n");
		return 1;
	}
	   
	if(TP->query_prop(SLAY))
	{
		write("But you are already laying on the bed!\n");
		return 1;
	}
	
	if(str == "in bed" | str == "in the bed" | str == "on " +
	"bed" | str == "on the bed" | str == "bed" | str == "down") 
	{
		TP->catch_msg("You lay down on the bed.\n");
		say(QCTNAME(TP) + " lies down on the bed.\n");
		TP->add_prop(SLAY, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT,", laying " +
		"on the bed.\n");
		
		return 1;
	}
	
	else
	{
		TP->catch_msg("Lay where?\n");
		
		return 1;
	}
	
	return 1;
}

int action_stand(string str)
{
	if(str == "up")
	{
		if(TP->query_prop(SSIT))
		{
			TP->catch_msg("You stand up and leave " +
			"the bed.\n");
			say(QCTNAME(TP)+" stands up.\n");
			TP->remove_prop(SSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			
			return 1;
		}
		
		if(TP->query_prop(SLAY))
		{
			TP->catch_msg("You stand up and leave " +
			"the bed.\n");
			say(QCTNAME(TP)+" stands up.\n");
			TP->remove_prop(SLAY);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			
			return 1;
		}
	}
	
	else
	{
		TP->catch_msg("Stand? Stand up?\n");
		
		return 1;
	}
	
	return 1;
}

int jump_bed(string str)
{
	if(str == "bed" | str == "on bed" | str == "on the bed")
	{
		if(TP->query_prop(SLAY) || TP->query_prop(SSIT))
		{
			TP->catch_msg("Perhaps you should stand up before jumping on the bed.\n");
			return 1;
		}
		
		else
		{
			TP->catch_msg("You take a big jump on the bed!\n");
			TP->catch_msg("OUCH! You hit your head on the low ceiling!\n");
			say(QCTNAME(TP)+" takes a big jump on the bed!\n");
			say(QCTNAME(TP)+" hits " + HIS_HER(TP) + " head on the ceiling!\n");
			return 1;
		}
	}
	
	else
	{
		TP->catch_msg("Jump on what?\n");
		return 1;
	}
}

int snuggle_bed(string str)
{
	if(str == "bed" | str == "quilt" | str == "into quilt" | str == "into bed" | str == "into the quilt" | str == "into the bed")
	{
		if(!TP->query_prop(SLAY))
		{
			TP->catch_msg("Perhaps you should laying down to do that.\n");
			return 1;
		}
		
		if(TP->query_prop(SSIT))
		{
			TP->catch_msg("Perhaps you should laying down to do that.\n");
			return 1;
		}
		
		else
		{
			TP->catch_msg("You snuggle into the soft quilt. It is so comfortable!\n");
			say(QCTNAME(TP)+" snuggles into the soft quilt on the bed. " + HE_SHE(TP) + " smiles, looking very comfortable.\n");
			return 1;
		}
	}
	
	else
	{
		TP->catch_msg("Snuggle where?\n");
		return 1;
	}
}

void leave_inv(object ob, object to)
{
	::leave_inv(ob, to);	
	
	if(!objectp(to) || !objectp(ob))
		return;
	
	if(TP->query_prop(SSIT))
	{
		TP->catch_msg("You rise from the bed before leaving.\n");
		
		say(QCTNAME(TP) + " stands up as " + HE_SHE(TP) +" leaves.\n");
		
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		
		TP->remove_prop(SSIT);
	}
	
	if(TP->query_prop(SLAY))
	{
		TP->catch_msg("You rise from the bed before leaving.\n");
		
		say(QCTNAME(TP) + " stands up as " + HE_SHE(TP) +" leaves.\n");
		
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		
		TP->remove_prop(SLAY);
	}
}  
