/*Created by Macker 7/11/94*/
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit VILLAGE_OUTROOM;

create_village_room() {
	set_short("South Side of Village");
   set_long(
	"This is the south side of the village of the ice folk. " +
	"There are quite a few tents here, but it looks like the larger, " +
	"more important buildings are made of ice. Some ice folk are " +
	"wandering around going about their daily business.\n");
   
	add_item("village", "You are in the village, you silly person. Just look around!\n");
	add_item("tents", "There are quite a few here, but they seem " +
		"unimportant. They are probably just used as " +
		"quarters for the poorer families.\n");
	add_item("buildings", "These buildings are made entirely of packed, " +
		"frozen snow. They will never melt because it is always " +
	"freezing here! You will probably enter a few of these buildings " +
		"if you continue to stroll through the village.\n");
	add_item( ({"snow", "ice"}), "It is white and cold. What did you expect?\n");
	add_item( ({"people", "folk", "ice folk", "ice people"}),
		"The ice folk you see are wrapped tightly in hides from " +
		"various animals. Their faces look worn from the years spent " +
		"in this harsh environment. Surprisingly they do not look unhappy. " +
		"In fact, they seem to be content with their lives in this frozen wasteland. You are sure they have their share of problems though.\n");

add_exit(ICE_PLAINS + "plain_4.c", "south");

add_exit(VILLAGE +
		"village_2.c", "northwest");
}


void
snowball_smack(object smacked)
{
	smacked->catch_msg("A snowball hits you in your head.\n");
	tell_room(E(smacked),"A snowball comes out of nowhere and hits "
	+ QCTNAME(smacked) + ".\n", smacked);
	tell_room(E(smacked),"\nIn the distance you hear someone shout: COOPER! "
	+ "Stop throwing snowballs!!!\n");
	tell_room(E(smacked),"\nFrom somewhere nearby you hear someone mutter: "
	+ "I never get to have any fun!\n");
}

void
enter_inv(object ob, object from) 
{
	if((1 + random(10)>8)&&(living(ob)))
		set_alarm(3.0, 0.0, "snowball_smack", ob);
	::enter_inv(ob, from);
}


