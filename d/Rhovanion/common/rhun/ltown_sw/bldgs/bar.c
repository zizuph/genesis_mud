#pragma save_binary

inherit "/d/Rhovanion/lib/room";
inherit "/lib/pub";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>

void create_room()
{
  set_short("Town pub");
  set_long("This is the town pub. It seems to be the busiest and"
	  +" most successful of this large town's businesses."
	  +" There is a menu here which you can read for selections--"
	  +" it's all the same in these parts-- or you"
	  +" may exit back out on to the street to the north.\n");

  add_prop(ROOM_I_INSIDE, 1);
  add_exit(RHUN_DIR+"ltown_sw/streets/st10","north",0);

  add_drink(({"true beer","beer"}), "beer", "true", 100, 10, 100,
            "true beer", "true beers", 
            "This is a true beer, icy cold and quite tasty.\n");
  add_drink(({"wine", "sweet wine" }), "wine", "sweet", 150, 15, 200,
            "sweet wine", "sweet wines", "This sweet wine is made from " +
	    "the nearby vineyards for which Rhun is famous.\n");
  add_drink(({"bourbon","straight bourbon"}),"bourbon","straight",200,20,300,
        "straight bourbon", "straight bourbons", "This is a bourbon served " +
        "straight from the bottle, without water or ice to dilute it.\n");
  add_food(({"steak","tender steak"}),"steak","tender",300,155,
        "tender steak", "tender steaks", "This is a tender steak, but you " +
        "aren't really sure where it is from, since you see no cows here " +
		"around here.\n");
  add_food(({"fish","baked fish"}), "fish", "baked", 150, 42,
           "baked fish", "baked fish",
           "This is baked fish, caught from the sea, of course.\n");
  add_item("menu", "You could read it.\n");
  add_cmd_item("menu", "read", "You can buy the following things from us" +
        "(all purchases are final):\n\n" +
        "    true beer for 100 coppers\n" +
        "    sweet wine for 200 coppers\n" +
        "    straight bourbon for 300 coppers\n" +
        "    tender steak for 155 coppers\n" +
        "    baked fish for 42 coppers\n");
}

void init()
{
    ::init();
    init_pub();
}