
inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <macros.h>
#include <stdproperties.h>

#define BS(s)	(break_string(s, 70))
#define TP	this_player()

#define WEST_EXIT  MANSION + "second/gallery_c"

#define OTHER_ROOM MANSION + "second/passage"

int side;

int
query_side()
{
    return side;
}

do_turn_paint()
{
    side = 1 - side;
}

init()
{
    ::init();
    add_action("do_push","push");
}

create_room()
{
    set_short("Portrait Room");
    set_long(BS("This is the east end of an incredibly long room, " +
		"containing a number of portraits of various important " +
		"looking people.  There is a thick, plush burgandy " +
		"carpet running west, from the east wall, into the " +
		"further reaches of the room.\n"));

    add_item(({"carpet", "plush carpet"}), BS("The thick carpet covers " +
		"most of the carpet except along the north and south walls " +
		"where you can see the highly polished floorboards.\n"));

    add_item(({"boards", "floorboards", "polished floorboards"}),
		"These boards are in very good condition and look " +
		"quite slippery.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(WEST_EXIT, "west", 0);

    add_item(({"portraits", "paintings"}), 
		"There are nine different portraits.\n");

    add_item(({"portrait", "painting"}),  "There are nine of these.\n" +
		"Please specify the number of the one you are looking at.\n");

    add_prop(OBJ_S_WIZINFO,
		" The portraits are located round the walls :\n\n" +
		"               1 2 3 4 5\n" +
		"     west exit           6 -> passage\n" +
		"                9  8  7\n");

    add_item(({"first portrait", "first painting", "1",
	       "portrait 1", "painting 1"}),  BS(
		"This portrait is on the north wall; it is of a " +
		"blond-haired elf.  His blue eyes make you feel " +
		"very comfortable.\n"));

    add_item(({"second portrait", "second painting", "2",
	       "portrait 2", "painting 2"}),  BS(
		"Standing slightly to the left of the centre of the " +
		"north wall, this is a portrait of a swarthy gnome.  " +
		"You notice his dark eyes are focused on the huge book " +
		"that he is holding.  " +
		"This is the only portrait of a gnome in the room.\n"));
 
    add_item(({"third portrait", "third painting", "3",
 	        "portrait 3", "painting 3"}),  BS(
		"Standing at the centre of the north wall, this " +
		"painting details an elf with purple hair.  This " +
		"clean-shaven elf has such a smug expression " +
		"that you wonder what he knows that you don't....\n"));

    add_item(({"fourth portrait", "fourth painting", "4",
	       "portrait 4", "painting 4"}),  BS(
		"Standing slightly to the right of the centre of the " +
		"north wall, this portrait is of a nefarious little " +
		"hobbit.  He looks very evil indeed.  " +
		"This is the only portrait of a hobbit in the room.\n"));

    add_item(({"fifth portrait", "fifth painting", "5",
	       "portrait 5", "painting 5"}),  BS(
		"This portrait is on the north wall; it is of an " +
		"incredibly philosophical elf.  His gray eyes show the " +
		"tiredness gained from months of deep thought.\n"));

    add_item(({"sixth portrait", "sixth painting", "6",
	       "portrait 6", "painting 6"}),  "@@port_desc");

    add_item(({"seventh portrait", "seventh painting", "7",
	       "portrait 7", "painting 7"}),  BS(
		"Standing at the east end of the southern wall, this " +
		"tiny portrait shows an insignificant little elf.  " +
		"You can see the friendliness in her wide blue eyes, " +
		"yet you feel that she is nervous about something.\n"));

    add_item(({"eighth portrait", "eigth painting", "8",
	       "portrait 8", "painting 8"}),  BS(
		"Standing at the centre of the south wall, the human " +
		"occupant of this portrait has large black eyes.  Despite " +
		"his otherwise menacing appearance, he seems quite " +
		"content with his place on the south wall.\n"));

    add_item(({"ninth portrait", "ninth painting", "9",
	       "portrait 9", "painting 9"}),  BS(
		"This painting stands at the west end of the southern " +
		"wall.  It is a portrait of an elf with dark, black " +
		"eyes.  Her long black hair makes her appear quite " +
		"attractive.\n"));
    side = 1; 
}

int
do_push(string str)
{
    notify_fail("Hmm, I don't see what you try to push... yourself?\n");
    if (strlen(str) < 1) return 0;
    notify_fail("You try to push " + str + ", but nothing happens.\n");
    if (str != "sixth portrait" && str != "sixth painting" && str != "6" &&
	str != "portrait 6" && str != "painting 6") return 0;
    do_turn_paint();
    write(BS(
	"As you push the huge painting on the east wall, the painting " +
	"suddenly begins to rotate together with a piece of floor you're " +
	"standing on.  You can't jump away from the floor, so you're " +
	"moved into a room behind the painting....\n"));
    say(BS(
	QCTNAME(this_player()) + " plays around with the big painting on " +
	"the east wall, which suddenly rotates.\n"));
    this_player()->move_living("through the painting",OTHER_ROOM);
    return 1;
}

string
port_desc()
{
    if (side)
	return(
"This amazing portrait stands alone, almost completely filling the entire\n" +
"eastern wall.  It is a larger than life portrait of a gray-bearded human\n" +
"looking extremely wise and knowledgable.  There is a magnificent\n" +
"ornately gilded mirror behind and to the right of this man.  In the\n" +
"mirror you can see the back of the his head; it looks like he's\n" +
"beginning to go bald!  Despite his wizened apearance, the human appears\n" +
"to be looking slightly annoyed as he glances to his left.\n");
    return(

"This amazing portrait stands alone, almost completely filling the entire\n" +
"eastern wall.  It is a larger than life portrait of a balding human.\n" +
"This portrait appears peculiar, maybe it is because the man is facing\n" +
"into the picture rather than out of the painting as all the other\n" +
"portraits in this room do.  You notice a magnificent ornately gilded\n" +
"mirror at the back of the painting, in front and to the left of the man.\n" +
"In the mirror you can see the front of the man; he has a long gray beard\n" +
"and looks extremely wise.  Despite this wise appearance, the human\n" +
"appears to be quite blatantly posing in the mirror.\n");
}

