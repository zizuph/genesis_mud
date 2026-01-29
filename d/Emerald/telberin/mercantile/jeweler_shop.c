/*
 *  This is the Jeweler's Shop in Telberin.
 * 
 *  Modified from /d/Gondor/minas/rooms/jewel_shop.c by Olorin
 * 
 *  Copyright (c) July 2003 by Cooper Sherry (Gorboth)
 *
 *  Olorin had the following thoughts on future features:
 *
 * TODO:
 * Add a gold smith.
 * The gold smith can make rings, necklaces, and carcanets
 * from copper, silver, gold, platinum (use coins!). Into the
 * jewelry, the gold smith can set gems from the jeweller.
 * The player will have to give the gold smith the gems, the coins for
 * metal and then he has to pay for the work done.
 *
 */
#include "/d/Emerald/telberin/defs.h";

inherit "/d/Emerald/lib/gem_shop";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h";

#define STORE_ROOM      ("/d/Emerald/telberin/mercantile/jeweler_store")

void
init()
{
    ::init();

    init_shop();
}

void
create_shop()
{
    set_short("Jeweler's Shop in Telberin");
    set_em_long("This is the Jeweler's Shop in Telberin. You stand in a"
     + " long and slender building which leads from its northern"
     + " entrance toward the front of the store, which is adorned"
     + " with much finery. The clear centerpiece of the entire room"
     + " is a large class display case, where the current stock of"
     + " gems can be viewed.\n");

    add_item( ({ "here", "area", "room", "shop", "store",
                 "jewelers shop", "jeweler's shop",
                 "jewelers", "building", "hall" }), long);
    add_item( ({ "north", "northern entrance", "entrance",
                 "door", "northern wall", "north wall" }),
        "A doorway leads through the northern wall out onto"
      + " Artisans Way.\n");
    add_item( ({ "mercantile way", "street" }),
        "The door to the store is closed, preventing you from"
      + " being able to see the street.\n");
    add_item( ({ "front of the store", "south", "southern wall",
                 "south wall", "finery" }),
        "The southern wall of the store is decorated with many"
      + " elegant paintings and fine detailing. A large display"
      + " case stands at the base of the wall.\n");
    add_item( ({ "painting", "elegant painting", "paintings",
                 "elegant paintings", "picture", "elegant picture",
                 "pictures", "elegant pictures" }),
        "A number of the paintings are portraits of various figures,"
      + " while others display landscapes.\n");
    add_item( ({ "portrait", "portraits" }),
        "The nobility diplayed in the portraits are unfamiliar to"
      + " your eyes. The subjects are all elven and dressed in"
      + " spectacularly fine garb.\n");
    add_item( ({ "landscape", "landscapes" }),
        "The landscapes are quite striking, and display a skill"
      + " which is rarely seen outside of very wealthy"
      + " establishments.\n");
    add_item( ({ "sky" }),
        "The sky is not visible from within this building.\n");
    add_item( ({ "case", "glass case", "display", "display case",
                 "large case", "large glass case",
                 "large display case", "large glass display case",
                 "centerpiece", "stock", "current stock" }),
        "The display case is gilded with gold metalwork along the"
      + " glass, and supported on an elegantly carved wooden base."
      + " The current offerings of the store are displayed within,"
      + " which you can <list> to view. Elegant silver scale pans are"
      + " spaced along one edge of the case.\n");
    add_item( ({ "glass", "metalwork", "gilding", "gold metalwork",
                 "gold" }),
        "Gilding laces the edges of the glass which forms the cover"
      + " for the display case. It has been meticulously embossed with"
      + " many beautiful flourishes.\n");
    add_item( ({ "base", "wooden base", "carved wooden base" }),
        "The base of the display case is carved of rich dark wood"
      + " which has been carved with many floral patterns and given"
      + " a beautiful oil finish.\n");
    add_item( ({ "pan", "pans", "scale", "scales", "scale pan",
                 "scale pans", "silver pan", "silver pans",
                 "silver scale", "silver scales",
                 "silver scale pan", "silver scale pans",
                 "elegant silver scale pan",
                 "elegant silver scale pans",
                 "elegant silver scale",
                 "elegant silver scales",
                 "elegant silver pan",
                 "elegant silver pans" }),
        "Scale pans such as these are used to measure the carat"
      + " weight of a gemstone. These ones are particularly beautiful"
      + " in their own right, having been crafted of white silver,"
      + " and polished regularly.\n");
    add_item( ({ "wall", "walls" }), 
        "The walls inside this building are covered with all manner"
      + " of fine detail and lavish display. There are many"
      + " expensive-looking paintings, and even a polished suit of"
      + " armour along the western wall.\n");
    add_item( ({ "west", "west wall", "western wall" }),
        "The western wall is decorated much in the manner of the"
      + " other walls in this building. A suit of armour stands"
      + " guard along its length.\n");
    add_item( ({ "armour", "suit", "suit of armour", "polished suit",
                 "polished armour", "polished suit of armour" }),
        "This armour is clearly not meant for military use. Rather,"
      + " it has been embossed with amazing detail along the gleaming"
      + " metal - a true display of wealth.\n");
    add_item( ({ "east", "east wall", "eastern wall" }),
        "The eastern wall is filled with many paintings.\n");
    add_item( ({ "floor", "ground", "down", "carpet", "rug",
                 "red rug", "red carpet", "rich carpet",
                 "rich rug", "rich red carpet", "rich red rug" }),
        "The ground at your feet is covered with a rich red carpet"
      + " which fills the entire room.\n");
    add_item( ({ "up", "ceiling", "roof", "chandelier" }),
        "A huge glittering chandelier hangs from the finely painted"
      + " celing to light the hall.\n");

    add_cmd_item( ({ "door", "doorway" }),
                  ({ "open" }),
        "You open the door to the north and are greeted for a moment"
      + " with the hubub from the street outside. Once the door"
      + " swings shut, the noise is gone once again.\n");


    set_store_room(STORE_ROOM);
    set_shop_name("Amshal's Jewelery");
    set_keeper_file("/d/Emerald/telberin/mercantile/npc/jeweler");

    setup_gem_shop();

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_EXIT_FROM_DESC,
        "from inside the jewelers shop.");

    add_exit("/d/Emerald/telberin/artisans_way06", "out");
    add_exit("/d/Emerald/telberin/artisans_way06", "north", 0, 1, 1);
}

string
exa_poster()
{
    return "\n"
      + "Welcome to " + shop_name + "!\n"
      + "You can try these instructions: \n"
      + "    buy diamond for gold and get copper back\n"
      + "    buy diamond for gold coins\n"
      + "    sell diamond for copper coins\n"
      + "    sell all  - will let you sell all gems.\n"
      + "    list      - will list all gems in stock.\n"
      + "    value diamond - will give an estimate on the price.\n"
      + "\n";
}

public string
query_entry_desc()
{
    return "into the jewelers shop";
}
