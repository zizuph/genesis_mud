/*
 * Wedding reception room
 * created by Kieryn February 1997
* Code based on Finwe's Inn at Telseron
 */

inherit "/std/room";
inherit "/lib/pub";

#include "/d/Emerald/defs.h"

void
create_room()
{
    set_short("Bright peaceful gazebo");
    set_long("   You gasp in awe of the beauty of this bright gazebo. "+
      "The lattice walls have been lavishly decorated with ribbons and flowers. "+
      "Groups of candles stand tall on the tables and on candelabras in "+
      "the corners of the room. Off to one side there is a long table with "+
      "a quill pen and guestbook. Right next to the book you notice that "+
      "others seem to be putting their presents. As your eyes move around "+
      "the room you notice two more tables piled with many different "+
      "kinds of food, their scents mingling and mixing in the air. "+
      "Around the perimeter of the room, small cloth covered tables and "+
      "benches are decorated for the feasts and festivities. "+
      "At one end of the room, you see an impeccably decorated table. "+
      "Behind that table is an arrangement of flowers and ivy, denoting it "+
      "as the head table. "+
      "On the wall by the door you see a plaque.\n" );

    add_item("menu", "There is writing on it.\n");
    add_item(({ "bench", "benches" }), "They are made of dark wood and "+
      "looks quite solid.\n");
    add_item(({ "table", "tables" }), "The tables are made of hard, light "+
      "wood, and are polished to a shine.\n");

    add_cmd_item("plaque", "read", "@@read");

    add_prop(ROOM_I_INSIDE, 1);

    add_drink( ({ "champagne", "champagnes", "bubbly", "bubbly champagne" }),
      "champagne", "bubbly", 100, 4, 0, 0, 1,
      "The champagne bubbles and tickles your nose when you drink it.\n", 0);
    add_drink( ({ "wine", "wines", "red", "red wine" }),
      "wine", "red", 80, 3, 10, 0, 0, "glass of red wine.\n",0);

    add_food( ({ "potato", "potato soup", "soup", "soups" }),
      "soup", "potato", 65, 80, "plate of potato soup",
      "plates of potato soup",
      "It has potatoes floating around in it, but "+
      "doesn't look like anything you'd particularily want to eat, "+
      "as the potatoes doesn't look all that good.\n" , 0);
    add_food( ({ "meat", "meat soup", "soup", "soups" }),
      "soup", "meat", 100, 120, "plate of meat soup",
      "plates of meat soup",
      "It looks like quite a mouthful, and has large "+
      "lumps of fat and what you think might be meat floating "+
      "around in it.\n" , 0);
    add_food( ({ "steak", "steaks" }),
      "steak", "large", 200, 220, 0, 0,
      "It looks quite delicious. Your mouth start to water.\n", 0);
    add_food( ({ "side", "lamb", "sides", "lambs", "side of lamb",
	"sides of lamb" }),
      "lamb", ({ "side", "of" }), 350, 380, "side of lamb",
      "sides of lamb",
      "It is quite large. You're not sure you can eat it all.\n", 0);

    add_exit(TOWNSHIP_DIR + "rd16", "out", 0);
}

void
init()
{
    ::init();
    init_pub();
}

string
read(string str)
{
    return "  Bubbly champagne       1 gc\n"+
"  Red wine     20 cc\n"+
    "  Potato soup       80 cc\n"+
    "  Meat soup        120 cc\n"+
    "  Steak            220 cc\n"+
    "  Side of lamb     380 cc\n\n"+
    "Use 'buy ale with silver' if you want to be "+
    "specific as to what kind of coins you wish to use, "+
    "or 'test buy steak' to see what would happen if you typed "+
    "'buy steak'. 'buy 5 ale' would get you 5 ales, but it takes "+
    "some time to tap them all up.\n" ;
}
