

inherit "/std/room";
#define TP "this_player()"
#include <macros.h>
create_room ()

{

     set_short ("Geraden's Private Bedroom");
     set_long(break_string("Here is the place Geraden goes when he is "+
               "very tired and "+
               "wants to get away from it all.  It is also where he goes when "+
               "he has someone special he wants to entertain, like you.  "+
               "You must be very special to him, for very few people "+
               "have ever seen this place.  The room itself is sparsely "+
               "furnished, yet very comfortable.  There is a wardrobe "+
               "against one wall, and a small vanity against the other. "+
               "Situated midway between the north and south walls, opposite "+
               "the door, is a large featherbed.  Beautiful rugs from exotic "+
               "place are arranged about the floor, adding warmth to the "+
		"room.  There is a large fireplace next to the "+
			"wardrobe.  "+
			"As you enter, you can not help but feel as it you are "+
               "home.\n",70));

     add_exit ("/d/Rhovanion/geraden/workroom", "work",0);
     add_exit ("/d/Rhovanion/geraden/bored/spar", "fight",0);

	add_item(({"fireplace"}), ("It is a large fireplace with a marble "+
		"mantle.\n"));
     add_item(({"bed"}), break_string("It is a soft feather bed.  On it is a dark green "+
          "blanket, which is turned down to reveal crips pale green "+
          "sheets.  Looking at the bed, you feel drawn to it.  Such "+
          "comfort and pleasure can be found there that you find it hard "+
          "not to crawl into it.\n",70));

     add_item(({"wardrobe"}), break_string("This is a truly beautiful "+
          "piece of furniture.  "+
          "It is made from walnut and is polished to a deep "+
          "luster.  Inside are various articles of clothing.\n",70));

     add_item(({"vanity"}), break_string("The vanity is made of dark "+
          "walnut and matches the wardrobe.  On one side is a mirror and "+
          "brush.  On the other is a picture in a silver frame\n",70));

     add_item(({"picture"}), break_string("This is a picture of Geraden's "+
          "first and only true love.  You see a beautiful Chestnut "+
          "haired green-eyed elf.  You instictively know this is Terissa.\n",70));

	add_item(({"mirror"}), break_string("When you look into the mirror, "+
		"at first all you see is your relection.  But then "+
		"you think you see something deep in the mirror.  You "+
		"blink once and whatever it was is gone.\n",70));

	add_item(({"rugs"}), break_string("These rugs are from various "+
		"locations around the world.  By looking at these rugs, you "+
		"can see that Sir Geraden is well travelled indeed.\n",70));

	add_item(({"clothes", "clothing"}), break_string("Arranged in the "+
		"wardrobe are "+
		"various articles of clothing.  Although there is a large "+
		"selection, all seem to have some green in them.\n",70));

	add_item(({"blanket"}), break_string("Made from the finest "+
		"materials available, this blanket must indeed be "+
		"be expensive.\n",70));

	add_item(({"sheets"}), break_string("The sheets are clean a"+
		"and crisp.  They are made of the purest silk.  You feel "+
		"an almost overwelming urge to remove your garments "+
		"and slide between them to feel their coolness against "+
		"your skin.\n",70));
}

init()
{
add_action("do_emote", "emote");
::init();
}
do_emote(string str)
{
	if(!str)
	{
		NF("Emote what?\n");
		return 0;
	}
	say(QCTNAME(TP)+ " " +str+ "\n");
	write("You emote: " +NAME+ " " +str+ "\n");
	return 1;
}
