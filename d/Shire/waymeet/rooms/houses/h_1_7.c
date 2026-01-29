/* 
 * A hobbit dwelling in Waymeet
 *
 * --Raymundo, Jan 2020
 */

#pragma strict_types
 
inherit "/d/Shire/std/room";

inherit "/d/Gondor/open/room_chairs/room_chairs";
#include "/d/Shire/waymeet/lib/hobbitmaker.h"
#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define CHAIR_NAME "rocking chair"
inherit WAYM_LIB_DIR + "base_hobbit_hole.c";

public void	init();
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);	/* VBFC for chairs */
void reset_shire_room();
void add_hobbit();
object hobbit;
void
create_shire_room()
{
	set_short("In the Master Bedroom");
	
	set_long("The master bedroom is furnished quite nicely. In the center "
		+ "of the north wall is a four poster bed, its posts reaching to "
		+ "the ceiling. Beneath the window are a rocking chair and "
		+ "bassinet, positioned to catch the sunlight. Thick rugs carpet "
		+ "the floor, but they stop just before the fireplace." 
		+ "@@is_in_chair@@" +"\n");
		
	set_room_tell_time(200);
	add_prop(ROOM_I_INSIDE, 1);
	add_walls();
	add_window("long");
	remove_item("floor");
	add_item("bassinet", "The bassinet looks like the kind of place you'd "
		+ "place an infant while you sat in the rocking chair and red a "
		+ "book or knitted some new sweaters. You notice some hinges on "
		+ "the legs, which make you think you could rock the bassinet. "
		+ "The bassinet has a few blankets inside of it, "
		+ "but they look dusty. You see some cobwebs in the corners "
		+ "as well.\n");
	add_item( ({"blanket", "blankets"}), "The blankets look faded "
		+ "and dusty.\n");
	add_item( ({"cobweb", "cobwebs"}), "There are very tiny cobwebs "
		+ "growing in the corners of the bassinet.\n");
	add_item( ({"floor", "rug", "rugs", "carpet", "carpets"}),
		"Thick rugs carpet the floor. The rugs look like they would feel "
		+ "soft and plush. You notice they overlap some, leaving no hard "
		+ "wooden spots, except right in front of the fire place where "
		+ "perhaps an errant spark would damage the rugs--or worse, "
		+ "start a fire.\n");
	add_item( ({"fireplace", "fire place"}), "The fireplace is along "
		+ "the east wall and its chimney goes straight up through the "
		+ "ceiling. Even without looking insde, you can tell there "
		+ "is no fire lit, but you can feel the cold drafts coming down "
		+ "through the chimney.\n");
	add_item( "inside fireplace", "You look inside the fireplace "
		+ "and notice nothing but soot-stained stones. There are no ashes. "
		+ "Clearly, this fireplace doesn't see much use.\n");
	add_item( "sunlight", "@@exa_sunlight@@");
	add_item( "east wall", "The east wall looks much like all the other "
		+ "walls, except that it has a small fireplace in it. The fireplace "
		+ "is just large enough to heat the bedroom.\n");
	add_item("north wall", "The north wall is covered in wood paneling, "
		+ "much like the rest of the house. It slopes down slightly to the "
		+ "west, where the smial and the hill end. In the center of the "
		+ "wall is a four poster bed.\n");
	add_item("bedroom", "The bedroom is where you sleep. This is a good "
		+ "example of a bedroom.\n");
	add_item( ({"bed", "poster bed", "four poster bed"}), "The bed is "
		+ "quite large, for a hobbit bed. You could picture mommy hobbit, "
		+ "daddy hobbit, and a few baby hobbits all piled together asleep "
		+ "and happy under the covers.\n");
	add_item( ({"post", "poster", "posts"}), "The posts reach from the floor "
		+ "to the ceiling and appear to have been custom-cut to match the "
		+ "curvature of the ceiling.\n");
	add_item( ({"cover", "covers"}), "The covers look deep and warm, which "
		+ "is a good thing since hobbit holes are under ground and it tends "
		+ "to be quite chilly. Looking closely at the covers, you notice "
		+ "that only one side of the covers has any wrinkles on it. The other "
		+ "is perfectly made, as if no one has slept in it for a while now.\n");
	
	add_chair(CHAIR_NAME, 
		"[down] [in] / [on] [the] [comfortable] 'chair' / 'armchair'",
	1, "in");
	
	/* use VBFC for chair/sofa items */
    add_item( ({ "rocking chair", "chair"}), &look_at(CHAIR_NAME) );

	add_cmd_item( ({"draft", "drafts"}), "feel", "You reach your hand "
		+ "toward the fireplace and feel the draft. It's chilled, seeming "
		+ "somehow to be colder than it should be. The draft reminds "
		+ "you of the inside of a crypt for some reason.\n");
	add_cmd_item( ({"carpet", "carpets", "rug", "rugs"}), "feel",
		"The rugs are quite thick, covering the first couple knuckles "
		+ "on your index finger. They are soft as well. If someone were "
		+ "to fall here, they likely wouldn't get too hurt.\n");
	add_cmd_item( "floor", "feel", "You reach down and touch the floor "
		+ "in front of the fireplace. It's quite hard and likely to "
		+ "injure anyone who falls against it.\n");
	add_cmd_item( "bassinet", "rock", "As you rock the bassinet back "
		+ "and forth, you hear the hinges squeak.\n");
		
	add_exit(WAYM_HOUSE_DIR + "h_1_5", "east", check_sitting, 1);

	add_hobbit();
}

void
reset_shire_room()
{
	if(!hobbit)
	{
		add_hobbit();
	}
}

void
init()
{
	::init();
	init_room_chairs();
	add_action("rock_chair", "rock");
	
}

public void
leave_inv(object ob, object dest)
{
	::leave_inv(ob,dest);
	leave_inv_room_chairs(ob, dest);
}

string
look_at(string arg)
{
	switch(arg)
	{
		case CHAIR_NAME:
		return("This is a very comfortable looking rocking chair. You "
			+ "estimate it to be the perfect size for a hobbit woman "
			+ "to sit in, likely while rocking a baby to sleep or nursing "
			+ "her child.\n"
			+ sitting_on_chair(CHAIR_NAME, this_player(), 0));
	}
}
//lets you examine sunlight
string
exa_sunlight()
{
	if(CLOCK->query_night())
	{
		return("It's night time. There is no sunlight. But the moon is "
			+ "surprisingly bright tonight.\n");
	}
	else
	{
		return("Sunlight streams gently through the window, making the "
			+ "room seem warm and comfortable.\n");
	}
}

/* This returns who is in the chair to the long or short description.
 * IF you add + "@@is_in_chair@@" somewhere in your long description.
 */
 
string
is_in_chair()
{
	return("\n" + sitting_on_chair(CHAIR_NAME, this_player(), 0));
}

int
rock_chair(string str)
{
	if(this_player()->query_prop(LIVE_S_SITTING))
	{
		if(strlen(!str))
		{
			notify_fail("Rock what? The chair?\n");
			return 0;
		}
		else if(str == "chair" | str == "rocking chair")
		{
			write("You rock back and forth in the chair and hum softly "
				+ "to yourself, much like a mother would rock in the chair "
				+ "if she were holding her child.\n");
			say(QCTNAME(TP) + " rocks back and forth in the chair, humming "
				+ "softly to " + HIM_HER(TP) + "self.\n");
			return 1;
		}
		else
		{
			notify_fail("Rock what? The chair?\n");
			return 0;
		}
	}
	else
	{
		notify_fail("You must be seated to rock the chair.\n");
		return 0;
	}
}

void
add_hobbit()
{
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(CITIZEN);
	hobbit->set_power(100);
	hobbit->move(TO);
	hobbit->set_gender(0);
	hobbit->set_chat_time(30);
	hobbit->add_chat("What do I tell my child about my wife?");
	hobbit->add_chat("I miss my wife.");
	hobbit->add_chat("Why did the orcs take her?");
	hobbit->add_chat("I try to look happy for my child, but I'm crying inside.");
	hobbit->set_default_answer("The hobbit looks like he'd like to know "
		+ "what exactly happened to his wife.\n");
	
	return;
}