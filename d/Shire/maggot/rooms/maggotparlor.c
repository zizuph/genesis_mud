
/* 
	*A parlor in the house of farmer Maggot
	*Altrus, March 2005
*/
#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit BASE_HOUSE;
inherit "/d/Shire/std/room";

#define SLAY 	"_laying_on_sofa"
#define SSIT 	"_sitting_on_sofa"
#define CSIT	"_sitting_on_chair"

void create_shire_room()
{
	set_short("In a cozy parlor in a small house");

	set_long(short() + ". There are several " +
	"comfortable looking chairs, a large sofa and a low " +
	"lying table here, as well as a large fireplace set " +
	"into the northwest corner of the room. There are " +
	"a couple of windows through which light may enter " +
	"the room.\n");
	
	add_item(({"parlor", "sitting room"}), "The parlor, or sitting room, looks quite cozy.\n");
	add_item(({"windows", "window"}), "There are two " +
	"windows here, one set into the west wall, and one " +
	"set into the south wall. Which window do you want? " +
	"The west one or the south one?\n");
	add_item(({"west window"}), "Outside the west " +
	"window you can see a well-kept yard with a few " +
	"trees bordering it. In the distance there appears " +
	"to be a field.\n");
	add_item(({"south window"}), "Outside the south " +
	"window you can see a well-kept yard with a few " +
	"trees bordering it. There is a lane just south of " +
	"the house.\n");
	add_item(({"yard"}), "You can see a yard outside " +
	"the windows.\n");
	add_item(({"trees"}), "Through the windows, you " +
	"can see small trees bordering the yard.\n");
	add_item(({"field"}), "Through the west window " +
	"you can see what looks like a field of turnips.\n");
	add_item(({"lane"}), "Through the south window " +
	"you can see a hedge-lined lane running east and " +
	"west.\n");
	add_item(({"turnips", "turnip"}), "They are too far " +
	"away to see clearly.\n");
	add_item(({"ceiling"}), "It is very low, barely six feet " +
	"from the floor. A fixture is hanging from the ceiling in " +
	"the middle of the room.\n");
	add_item(({"walls", "wall"}), "The walls are whitewashed " +
	"and clean. They are decorated with various paintings and " +
	"small shelves.\n");
	add_item(({"floor"}), "The floors are spotlessly clean, " +
	"not a speck of dust mars the wooden surface.\n");
	add_item(({"fixture"}), "It is circular, made of wood, and is " +
	"hanging in the center of the room from a small chain. It " +
	"contains beeswax candles, filling the room with a pleasant " +
	"smell.\n");
	add_item(({"candle", "candles", "beeswax candle", "beeswax candles"}), "They " +
	"fill the room with a pleasant smell.\n");
	add_item(({"paintings"}), "Just a couple framed canvases " +
	"depicting scenes of hobbit life.\n");
	add_item(({"shelves"}), "They are holding a few vases filled " +
	"with wild and garden flowers.\n");
	add_item(({"flowers"}), "The flowers look a little dry.\n");
	add_item(({"chain"}), "It is a short, linked chain. It is " +
	"attached to the ceiling, and is being used to suspend " +
	"a round wooden fixture holding candles.\n");
	add_item(({"chair", "chairs"}), "For a farmhouse, the " +
	"chairs are far from utilitarian. They are, in fact, quite " +
	"exquisite in their craftsmanship, made from a carved " +
	"and polished wood and upholostered with comfort as " +
	"the utmost priority.\n");
	add_item(({"sofa"}), "It is, if possible, even more " +
	"comfortable looking than the chairs. It seemingly " +
	"begs to be laid on or sat in.\n");
	add_item(({"table"}), "The table is roughly in the " +
	"center of the room, underneath the light fixture. It " +
	"is made from a polished wooded, and seems very " +
	"worn, but still quite useable.\n");
	add_item(({"fireplace", "fire"}), "It is set into the " +
	"the northwest corner of the parlor, and appears to be " +
	"shared with the kitchen in the adjoining room, and " +
	"as such, is kept buring most of the day. The result " +
	"being a very warm parlor.\n");
	add_item(({"corner", "northwest corner"}), "In the northwest corner is set a fireplace.\n");
	add_item(({"wood"}), "You can not tell what kind " +
	"of wood the chairs and table are carved from, but it " +
	"certainly looks sturdy. Perhaps oak?\n");
	
	set_add_rtells_house();
	
	add_exit(ROOM_DIR + "maggothall01", "east");
	
	reset_shire_room();
}

void reset_shire_room()
{
	
}

void init()
{
	add_action("action_sit", "sit");
	add_action("action_lay", "lay");
	add_action("action_stand", "stand");
	::init();
}

int action_sit(string str)
{
	if(TP->query_prop(CSIT))
	{
		write("But you are already sitting on a chair! Perhaps " +
		"you should stand up first.\n");
		return 1;
	}
	   
	if(TP->query_prop(SSIT))
	{
		write("But you are already sitting on the sofa! Perhaps " +
		"you should stand up first.\n");
		return 1;
	}
	   
	if(TP->query_prop(SLAY))
	{
		write("But you are laying on the sofa! Perhaps " +
		"you should stand up first.\n");
		return 1;
	}
	   
	if(str == "down" | str == "in chair" | str == "in a " +
	"chair" | str == "on chair" | str == "on a chair" | str == "down " +
	"in chair" | str == "down in a chair" | str == "down " +
	"on chair" | str == "down on a chair" | str == "in the " +
	"chair" | str == "on the chair" | str == "chair") 
	{
		TP->catch_msg("You sit down in one of the " +
		"comfortable chairs.\n");
		say(QCTNAME(TP) + " sits down in one of " +
		"the comfortable looking chairs.\n");
		TP->add_prop(CSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT,", sitting " +
		"in a comfortable looking chair");
		
		return 1;
	}
	
	if(str == "in sofa" | str == "in the sofa" | str == "on " +
	"sofa" | str == "on the sofa" | str == "sofa") 
	{
		TP->catch_msg("You sit down on the large " +
		"sofa.\n");
		say(QCTNAME(TP) + " sits down on the large " +
		"sofa.\n");
		TP->add_prop(SSIT, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT,", sitting " +
		"on a large sofa");
		
		return 1;
	}
	
	else
	{
		TP->catch_msg("Sit where?\n");
		
		return 1;
	}
	
	return 1;
}

int action_lay(string str)
{
	if(TP->query_prop(CSIT))
	{
		write("But you are already sitting on a chair! Perhaps " +
		"you should stand up first.\n");
		return 1;
	}
	   
	if(TP->query_prop(SSIT))
	{
		write("But you are already sitting on the sofa! Perhaps " +
		"you should stand up first.\n");
		return 1;
	}
	   
	if(TP->query_prop(SLAY))
	{
		write("But you are laying on the sofa! Perhaps " +
		"you should stand up first.\n");
		return 1;
	}
	
	if(str == "in sofa" | str == "in the sofa" | str == "on " +
	"sofa" | str == "on the sofa" | str == "sofa" | str == "down") 
	{
		TP->catch_msg("You lay down on the large " +
		"sofa.\n");
		say(QCTNAME(TP) + " lies down on the large " +
		"sofa.\n");
		TP->add_prop(SLAY, 1);
		TP->add_prop(LIVE_S_EXTRA_SHORT,", laying " +
		"on a large sofa");
		
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
		if(TP->query_prop(CSIT))
		{
			
			TP->catch_msg("You stand up and leave " +
			"the chair.\n");
			say(QCTNAME(TP)+" stands up.\n");
			TP->remove_prop(CSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			
			return 1;
		}
		
		if(TP->query_prop(SSIT))
		{
			TP->catch_msg("You stand up and leave " +
			"the sofa.\n");
			say(QCTNAME(TP)+" stands up.\n");
			TP->remove_prop(SSIT);
			TP->remove_prop(LIVE_S_EXTRA_SHORT);
			
			return 1;
		}
		
		if(TP->query_prop(SLAY))
		{
			TP->catch_msg("You stand up and leave " +
			"the sofa.\n");
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
	
void leave_inv(object ob, object to)
{
	::leave_inv(ob, to);	
	
	if(!objectp(to) || !objectp(ob))
		return;
	
	if(TP->query_prop(CSIT))
	{
		TP->catch_msg("You rise from your chair before leaving.\n");
		
		say(QCTNAME(TP) + " stands up as "+ HE_SHE(TP) +" leaves.\n");
		
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		
		TP->remove_prop(CSIT);
	}
	  
	if(TP->query_prop(SSIT))
	{
		TP->catch_msg("You rise from the sofa before leaving.\n");
		
		say(QCTNAME(TP) + " stands up as " + HE_SHE(TP) +" leaves.\n");
		
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		
		TP->remove_prop(SSIT);
	}
	
	if(TP->query_prop(SLAY))
	{
		TP->catch_msg("You rise from the sofa before leaving.\n");
		
		say(QCTNAME(TP) + " stands up as " + HE_SHE(TP) +" leaves.\n");
		
		TP->remove_prop(LIVE_S_EXTRA_SHORT);
		
		TP->remove_prop(SLAY);
	}
}  