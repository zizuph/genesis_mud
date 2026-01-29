/**********************************************************************
 * - landing.c                                                      - *
 * - This is an southern hallway located in the SaMorgan Inn        - *
 * - They this leads to the private hall rooms and bathing areas    - *
 * - Created by Damaris 04/2006                                     - *
 **********************************************************************/
 
#pragma strict_types
inherit "/d/Khalakhor/std/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/basic.h"
#include "../inn.h"

string
query_sign()
{
    return("\n"+
    "          *--------------------*` - - `*--------------------*\n"+
    "          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
    "          | `                                             ` |\n"+
    "          | `                 Directions                  ` |\n"+
    "          | `       *`----------------------------`*      ` |\n"+
    "          | `                                             ` |\n"+
    "          | `                Private rooms                ` |\n"+
    "          | `                                             ` |\n"+
    "          | `                      |                      ` |\n"+
    "          | `                      |                      ` |\n"+
    "          | `                      |                      ` |\n"+
    "          | `  Male bath   <--- Landing --->  Female bath ` |\n"+
    "          | `                      |                      ` |\n"+
    "          | `                      |                      ` |\n"+
    "          | `                      |                      ` |\n"+
    "          | `                                             ` |\n"+
    "          | `                Public bathing               ` |\n"+
    "          | `                                             ` |\n"+
    "          | ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` ` |\n"+
    "          *--------------------*` - - `*--------------------*\n");
}

int
verify_ticket(object tic)
{
	if(!objectp(tic))
	{
		write("Sorry but you do not have a ticket for this "+
		"bath area.\n");
		return 1;
	}
	write("You hand your ticket to the attendant, and pass into "+
	"the bathing room.\n");
	tic->remove_object(); // take the ticket
	return 0;
}

int
check_public_ticket()
{
	object tic = present(TICKET_BATH_P, this_player());
	return verify_ticket(tic);
}

int
check_female_ticket()
{
	object tic = present(TICKET_BATH_F, this_player());
	if(this_player()->query_gender() != G_FEMALE)
	{
		write("Nice try. Get a better disguise next time.\n");
		say(QCTNAME(this_player())+" is caught trying to sneak "+
		"into the female bathing area.\n");
		return 1;
	}
	return verify_ticket(tic);
}

int
check_male_ticket()
{
	object tic = present(TICKET_BATH_M, this_player());
	if(this_player()->query_gender() != G_MALE)
	{
		write("Sorry, this is a manly man's bathing area.\n");
		return 1;
	}
	return verify_ticket(tic);
}

void
create_khalakhor_room()
{
	set_short("a decorative landing at top of stairs");
	set_long("\n   This decorative landing spreads out with a "+
	"long hallway to the north. Just beyond the square wooden "+
	"banister are three archways leading west, east and south. "+
	"Precisely west of the stairs stands a large brass sign that "+
	"give directions to the public bathing and private rooms. "+
	"Subtle but adequate light stems from decorative brass lanterns "+
	"hanging from the walls along with a few paintings.\n");
	add_item(({"area", "room", "landing", "top of stairs"}), query_long);
	
	add_item(({"sign", "simple sign", "unadorned sign", "austere sign", "unembellished sign", "meager sign"}), query_sign);
	add_cmd_item(({"sign", "large sign", "brass sign", "large brass sign", "standing brass sign", "standing sign"}),"read", query_sign);

	add_item(({"wooden floor", "floor", "flooring"}),
	"The flooring is made from joined planks of polished wood.\n");
	add_item(({"wood", "polished wood"}),
	"Some of the wood used here is highly polished and in very "+
	"good condition.\n");
	add_item(({"ceiling"}),
	"The ceiling is open with beams running crossways and isn't "+
	"really much to look at.\n");
	add_item(({"wall", "walls"}),
	"The walls are made from wooden panels.\n");

	add_item(({"painting", "paintings"}),
	"There are two paintings that decorate this room.\n");
	add_item(({"unique painting", "first painting", "painting 1", "painting one"}),
	"This painting is large and takes up a good amount of space "+
	"on the east wall. It is a unique representation of a large "+
	"pool of water within a heavily wooded area. When you examine "+
	"it closer you can make out water nymphs bathing and enjoying "+
	"the pool.\n");
	add_item(({"east wall", "eastern wall"}),
	"A large archway with a unique painting just next to it.\n");
	add_item(({"small painting", "second painting", "painting 2", "painting two"}),
	"This small painting isn�t grand scale by any means, quite "+
	"meager at best. Yet it has fine artistic details of a sailing "+
	"vessel that is cast out on a turbulent sea. The thunderous "+
	"sky is obvious with the colour changes and the sway of the "+
	"ship with the upturning waves leaves a lasting impressing "+
	"that this artist painted from experience.\n");
	add_item(({"west wall", "western wall"}),
	"A large archway with a small painting just next to it.\n");
	add_item(({"lanterns", "lantern", "brass lantern", "brass lanters"}),
	"These lanterns are made from brass and etched glass. They "+
	"are highly polished and not a speck of dust can be found on "+
	"their surface. They add to the d�cor of the landing and give "+
	"subtle but adequate lighting to the area.\n");
	add_item(({"south wall", "southern wall"}),
	"The south wall has a small table with vase that is filled "+
	"with sweet honeysuckle and purple heather.\n");
	add_item(({"honeysuckle", "sweet honeysuckle"}),
	"The honesysuckle has pretty pink blossoms and is quite "+
	"fragrant.\n");
	add_item(({"heather", "purple heather"}),
	"The heather is a stunning purple adding colour to this area.\n");
	add_item(({"vase"}),
	"The vase has been placed on a small table and contains sweet "+
	"honesuckle and purple heather.\n");
	add_item(({"banister", "wooden banister", "wood banister", "square banister"}),
	"This square banister is made from highly polished wood and "+
	"very sturdy. It serves as protection for those on the landing "+
	"from falling down the stairs and gives those heading up or "+
	"down the stairs something to hold onto if they so desire.\n");
	add_item(({"maid", "maids"}),
	"There are different maids walking by here and they're helping "+
	"guests with their needs.\n");
	add_item(({"hallway", "hall"}),
	"The hallway extends to the north.\n");	
	
	add_prop(ROOM_I_INSIDE, 1);
	add_prop(ROOM_I_LIGHT, 2);
	
	add_exit("hall1", "north");
	add_exit("pbath", "south", check_public_ticket);
	add_exit("fbath", "east", check_female_ticket);
	add_exit("mbath", "west", check_male_ticket);
	add_exit("inn", "down");
	add_fail("auto", "A wall stops you.\n");
}
int
slide_down(string str)
{
	if (member_array(str, ({"banister", "wooden banister", "down banister", "on banister", "down wooden banister", "on wooden banister", "on wood banister", "down wood banister", "polished banister", "highly polished banister", "down polished banister",})) == -1)
	{
		notify_fail("Slide down what?\n");
		return 0;
	}
	write("You hop up on the highly polished banister then slide "+
	"down it shouting: WEEEEEEEEEE!\n\n");
	say(QCTNAME(this_player())+" hops up on the highly polished banister then slides down it shouting: WEEEEEEEEEE!\n");
	this_player()->move_living("M", "/d/Khalakhor/sw_speir/samorgan/inn/room/inn", 1, 0);
	say(QCTNAME(this_player())+" suddenly appears leaping off "+
	"the end of the highly polished banister.\n");
	return 1;
}

int
take_it(string str)
{
	if((str == "the heather") || (str == "heather") || (str == "purple heather"))
	{
		write("A maid stops you from taking the purple "+
		"heather saying: It is for everyone to enjoy.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" tries to take the purple heather but "+
		"a maid stops "+HIM(TP)+" saying: It is for eveyone to "+
		"enjoy.\n");
		return 1;
	}
	if((str == "the honeysuckle") || (str == "honeysuckle") || (str == "sweet honeysuckle"))
	{
		write("A maid stops you from taking the sweet "+
		"honeysuckle saying: It is for everyone to enjoy.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" tries to take the sweet honeysuckle "+
		"but a maid stops "+HIM(TP)+" saying: It is for everyone "+
		"to enjoy.\n");
		return 1;
	}
	if((str == "the flower") || (str == "flower") || (str == "flowers") || (str == "the flowers"))
	{
		write("A maid stops you from taking the flowers "+
		"saying: It is for everyone to enjoy.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" tries to take the flowers "+
		"but a maid stops "+HIM(TP)+" saying: It is for everyone "+
		"to enjoy.\n");
		return 1;
	}
	if((str == "vase"))
	{
		write("A maid stops you from taking the vase saying: "+
		"You really should leave things that do not belong to "+
		"you alone.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" tries to take the vase but a maid "+
		"stops "+HIM(TP)+" saying: You really should leave "+
		"things that do not belong to you alone.\n");
		return 1;
	}
	if((str == "painting") || (str == "first painting") || (str == "second painting") || (str == "painting 1") || (str == "painting 2"))
	{
		write("The painting is firmly attached and you cannot "+
		"seem to take it.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" thoroughly studies a painting.\n");
		return 1;
	}
	if((str == "lantern") || (str == "brass lantern"))
	{
		write("The brass lantern is firmly attached and you "+
		"cannot seem to take it.\n");
		
		/* This what others in room see. */
		say(QCTNAME(TP)+" thoroughly studies a lantern.\n");
		return 1;
	}
	else
	{
		notify_fail("Take/get what?\n");
		return 0;
	}
}

public void
init()
{
	::init();
	add_action("take_it", "take");
	add_action("take_it", "get");
	add_action("take_it", "grab");
	add_action("take_it", "steal");
	add_action("slide_down", "slide");
}
