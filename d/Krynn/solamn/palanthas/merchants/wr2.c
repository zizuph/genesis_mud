/* Mortis 12.2005 
 * Way to enter wood?  Found by smell?
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit MERCH_BASE;

#define TRIED_TOGO_SOUTH  "_tried_togo_south"
#define FLED_GROVE        "_palanthas_fled_shoikan_grove"


string
query_to_jail()
{
  return "east";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the east is the palatial plaza, its great white "
	+ "tower still visible above the buildings from this distance.  To the "
	+ "west the road leads through the merchants district, and south of you "
	+ "is a grove of great oaks out of the center of which looms a tower "
	+ "of dark, grey stone.  A grove of thick woods is to the north.  From "
	+ "it rises a squat, square tower of great marble blocks.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Merchants' Way and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Merchants' Way and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Merchants' Way catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants and shoppers make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent "
	+ "marble of Merchants' Way amplifying the yellow glow of the street "
	+ "lamps.  A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Merchants' Way west of the palatial plaza");
    LONG("@@get_time_desc@@");

	ITEM(({"oak", "oaks", "tree", "trees", "grove", "shoikan grove"}),
	  "Before you is a grove of oaks, much larger than most you've seen, "
	+ "moving unnaturally on chill surges in the breeze.  As you peer into "
	+ "their midst your eyes are drawn deeper in and for a moment you almost "
	+ "feel as if you're falling before the feeling passes.  No buildings "
	+ "border closely with the trees.  A wooden sign has been nailed to a "
	+ "post in the ground by the path to the south.  It reads, \"Don't go "
	+ "south or you will die.  -Thanks, City of Palanthas\".\n");
	ITEM(({"wood", "woods", "north wood", "north woods", "thick wood",
		   "thick woods"}), "A thick wood of trees stands to your north.  "
	+ "They are the Gallant Field Woods and home to the constabulary of "
	+ "Palanthas, the Palanthian Guard.  Their Tower of Arms rises from "
	+ "the vast field at its center.\n");
	ITEM("sign", "A wooden sign has been nailed to a "
	+ "post in the ground by the path to the south.  It reads, \"Don't go "
	+ "south or you will die.  -Thanks, City of Palanthas\".\n");

	CMD("sign", "read", "@@read_sign");

	EXIT(ROOM + "wr1", "east", 0, 0);
	EXIT(MERCH + "tohs", "south", "@@dont_go_south", 0);
	EXIT(MERCH + "wr3", "west", 0, 0);

}

int
dont_go_south()
{
    if(TP->query_prop(FLED_GROVE))
    {
        write("You can't bring yourself to attempt to approach the grove " +
            "again. The irrational fear is still too fresh in your mind.\n");
        return 1;
    }

    if (TP->query_prop(TRIED_TOGO_SOUTH))
    {
	write("You head south with a small amount of trepidation.\n");
	say(QCTNAME(TP) + " trepidatiously heads down an abandoned " +
            "street.\n");
        return 0;

         /*
		int i = random(5);
		switch (i)
		{
		case 1:
		write("No.  Don't do that.\n");
		say(QCTNAME(TP) + " looks south into the grove in confusion.\n");
		break;
		case 2:
		write("No.  You haven't thought this through well enough.\n");
		say(QCTNAME(TP) + " scratches " + HIS(TP) + " head with a dull "
		+ "look in " + HIS(TP) + " eyes as " + HE(TP) + " peers south "
		+ "into the grove.\n");
		break;
		case 3:
		write("Ok, you start going south...  No, you don't go south!  "
		+ "What are you crazy?\n");
		say(QCTNAME(TP) + " pretends to walk boldly into the grove to the "
		+ "south.\n");
		break;
		case 4:
		write("You don't have the guts to go south.  Ha!\n");
		say(QCTNAME(TP) + " clutches at " + HIS(TP) + " bowels and " + HIS(TP)
		+ " cheeks puff up as " + HE(TP) + " peers south into the grove.\n");
		break;
		default:
		write("Eager to die you go south.  No, you don't really go "
		+ "south, but you wish you had.\n");
		say(QCTNAME(TP) + " wipes " + HIS(TP) + " nose and sniffles while "
		+ "wishing " + HE(TP) + " too could go south into the grove.\n");
		break;
		return 1;
		}
		return 1;
         */
    }
    else
    {
	TP->add_prop(TRIED_TOGO_SOUTH, 1);
	write("As you are about to go south you notice a warning " +
            "sign planted clearly in front of you. If you are " +
            "sure you want to continue, by all means try heading " +
            "south again.\n");
	say(QCTNAME(TP) + " considers going south, but stops after " +
            "noticing a warning sign planted in that direction.\n");
	return 1;
    }
}

read_sign()
{
	write("It reads, \"Don't go south or you will die.  -Thanks, City of "
	+ "Palanthas\".\n");
	return 1;
}