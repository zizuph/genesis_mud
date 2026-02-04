/*
 *      A very unexciting dark passageway!
 *                                          Napture.
 */
 
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define BS(s)   (break_string(s, 70))
#define TP      this_player()

#define OTHER_ROOM (MANSION + "second/gallery_e")

init()
{
    ::init();
    add_action("do_push","push");
}

int
do_push(string str)
{
    notify_fail("Hmm, I don't see what you try to push... yourself?\n");
    if (strlen(str) < 3) return 0;
    notify_fail("You try to push " + str + ", but nothing happens.\n");
    if (str != "portrait" && str != "painting") return 0;
    OTHER_ROOM->do_turn_paint();
    write(BS(
	"As you push the huge painting, it " +
	"suddenly begins to rotate together with a piece of floor you're " +
	"standing on. You can't jump away from the floor, and so you're " +
	"moved into a room behind the painting....\n"));
    say(BS(
	QCTNAME(this_player()) + " plays around with the big painting on " +
	"the west wall, which suddenly rotates.\n"));
    this_player()->move_living("through the painting",OTHER_ROOM);
    return 1;
}

string
port_desc()
{
    seteuid(getuid());
    if (!OTHER_ROOM->query_side())
	return(BS(
	"This amazing portrait stands alone, almost completely filling " +
	"the entire " +
	"western wall.  It is a larger than life portrait of " +
	"a gray-bearded human " +
	"looking extremely wise and knowledgable.  There is a magnificent " +
	"ornately gilded mirror behind and to the right of this man.  In the " +
	"mirror you can see the back of the his head; it looks like he's " +
	"beginning to go bald!  Despite his wizened apearance, the human " +
	"appears to be looking slightly annoyed as he glances to his left.\n"));
    return(BS(
    "This amazing portrait stands alone, almost completely filling the " +
    "entire " +
    "western wall.  It is a larger than life portrait of a balding human. " +
    "This portrait appears peculiar, maybe it is because the man is facing " +
    "into the picture rather than out of the painting.  " +
    "You notice a magnificent ornately gilded " +
    "mirror at the back of the painting, in front and to the left of the " +
    "man. " +
    "In the mirror you can see the front of the man; he has a long gray " +
    "beard and looks extremely wise.  Despite this wise appearance, the " +
    "human appears to be quite blatantly posing in the mirror.\n"));
}



create_room()
{
    set_short("A Dark Passage");
    set_long(BS(
        "The twisting passage seems to be slightly wider here.  At the " +
	"west wall you can see a huge painting.  Thick " +
        "dust covers the floor.  The passageway continues in two " +
        "directions.  Both ways are very dark and narrow.\n"));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);

    add_exit(MANSION + "rooms/bstairs_top", "north", 0);
    add_exit(MANSION + "second/upper_gallery", "south", "@@no_go");

    add_item(({"dust", "thick dust"}), "@@dusty_floor");
    add_item(({"footprint", "footprints"}), "@@footprint");
    add_item(({"painting", "picture", "portrait"}), "@@port_desc");
}
    
no_go()
{
    write("The passage is so dark you decide not to go that way!\n");
    return 1;
}

dusty_floor()
{
    if ((TP->query_skill(SS_TRACKING)) + (TP->query_skill(SS_AWARENESS))
            + (TP->query_skill(SS_LOC_SENSE)) > (random(250) + 50) ) {
        return "The dust is very thick here.  You can just about make " +
               "out some footprints.\n";
        }
    return "The dust is very thick here.  You can feel your feet " +
           "sinking into the thickness.\n";
}

footprint()
{
    if ((TP->query_skill(SS_TRACKING)) + (TP->query_skill(SS_AWARENESS))
            + (TP->query_skill(SS_LOC_SENSE)) > (random(250) + 50) ) {
        return "The footprints appear to go into the wall!\n";
        }
    return "You recognise the footprints as your own.\n";
}

  
