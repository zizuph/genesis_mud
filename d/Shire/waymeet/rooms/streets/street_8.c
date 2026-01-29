/* Outdoors in Waymeet
 * Raymundo, Feb 2020
 */
 
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/eastroad/western/local.h"
#include "/d/Shire/waymeet/lib/hobbitmaker.h"

inherit WAYM_LIB_DIR + "base_waymeet.c";
inherit "/d/Gondor/common/lib/drink_water.c";

void add_hobbit();
object hobbit;


void reset_shire_room();

void
create_waymeet_room()
{
	extraline = ("To the north is the Great East Road, leading from "
		+ "Grey Havens to Bree. South is the more commercial section "
		+ "of Waymeet, with shops and whatnot. Here, in the middle of "
		+ "the street, you see a well "
		+ "where thirsty hobbits come to get water.\n");
	
	add_item("well", "This is an old stone well. It rises about a meter from "
		+ "the ground. You see a simple roof protecting the well from leaves "
		+ "and other debris. There is also a bucket here which hobbits use "
		+ "to get water from the well.\n");
	add_item("bucket", "The bucket is big enough to get some water, but "
		+ "not so big as to be heavy when it's full.\n");
	add_item("roof", "The roof keeps leaves out of the well.\n");
	add_item( ({"leaf", "leaves"}), "You see some leaves on top of the roof, "
		+ "but not in the well.\n");
	add_item( ({"shop", "shops", "whatnot"}), 
		"The shops are to the south. You can't "
		+ "tell much from here, so you'll need to get closer.\n");
	add_cmd_item("bucket", ({"lower", "raise"}), "You lower the bucket into "
		+ "the well and then raise it back up again. It's now full of water, "
		+ "and you could drink from it if you're thirsty.\n");
	add_street(1);
	set_drink_from( ({"well", "bucket"}));
	
	add_exit(WAYM_STREET_DIR + "street_9", "south", gravel_sound, 0, 0);
	add_exit(EAST_R_DIR + "er12", "north", gravel_sound, 0, 0);
    add_exit(EAST_R_DIR + "er13s", "east", 0,0,1);
    add_exit(EAST_R_DIR + "er11s", "west", 0,0,1);
	
	add_hobbit();
}
void
reset_shire_room()
{
	add_hobbit();
}


public void
drink_message(string from)
{
	write("You lower the bucket down into the well and then pull it up "
		+ "again. You lift it up to your lips and drink from it.\n");
	say(QCTNAME(TP) + " lowers the bucket down into the well and then "
		+ "pulls it up again. " + CAP(HE_SHE(TP)) + " lifts it up to "
		+ HIS_HER(TP) + " lips and drinks from it.\n");
}

void
init()
{
	::init();
	init_drink();

}

void
add_hobbit()
{
	if(present(hobbit))
	{
		return;
	}
	   if (!present(hobbit))
	   {
		   int i;
		   for(i=0; i<3; i++)
		   {
	hobbit = clone_object(HOBBITMAKER);
	hobbit->set_type(MILITA);
	
	hobbit->move(TO);
		   }
	   return;
	   }
	   return ;
	
}