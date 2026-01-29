#include "defs.h"

inherit TELBERIN_ARTISANS_WAY;

/* prototypes */
public void        create_artisans_way();


/*
 * Function name:        create_artisans_way
 * Description  :        set up the room
 */
public void
create_artisans_way()
{
    set_em_long("Just inside the western gate of Telberin, the grand " +
        "Artisans Way makes a wide bend, widening to form Artisans"
      + " Plaza before looping back through the " +
        "city's mercantile quarter toward the Royal Circle.  Numerous " +
        "boutiques, markets, and businesses border the outward edge of " +
        "the roadway and occupy this busy plaza.  Inward, the avenue " +
        "rings an area of emerald grass and manicured hedges which frame " +
        "a long, crystal blue pool; its line draws your eye down its length " +
        "to the splendid Royal Circle and up to the gates of the royal " +
        "palace. The palace's magnificent, perfectly symmetrical form " +
        "dominates the skyline. The tall, pure-white stone spires rise " +
        "toward the sky, gleaming brilliantly in the light. A number"
      + " of plaques are visible before the entrances to a few local"
      + " shops. A wide avenue enters the plaza from the west, running"
      + " directly from the main gates of the city.\n");

    add_item( ({ "armourer", "building to the north", "north",
                 "northern building", "north building" }),
        "The building to the north has the look of a forge or smithy,"
      + " with a great chimney rising from its foundation above the"
      + " rooftops.\n");
    add_item( ({ "chimney", "forge" }),
        "No armoury would be complete without a chimney to help fuel"
      + " the flames. This one looks formidable indeed.\n");
    add_item( ({ "long building", "building to the east",
                 "arms shop", "shop", "arms dealer" }),
        "East of here is a shop of some kind. Its doors stand open"
      + " and look ready to accomodate anyone willing to part with"
      + " a bit of their money. A plaque is mounted to the building.\n");
    add_item( ({ "boutique", "boutiques", "market", "markets",
                 "business", "businesses", "outward edge",
                 "edge of the roadway", "outward edge of the roadway" }),
        "The outward edge of the roadway is crowded with all manner"
      + " of businesses hoping to make their wares accessible to the"
      + " purchasing client. Here in the Mercantile Quarter, you will"
      + " find the opportunity to buy or sell most things you could"
      + " wish to find.\n");
    add_item( ({ "emerald grass", "manicured hedges", "hedge",
                 "hedges", "manicured hedge", "area of emerald grass" }),
        "Great care has gone into making this section of the city"
      + " attractive to visitors. It serves as both the business"
      + " district and the gateway into the city.\n");
    add_item( ({ "avenue", "wide avenue", "west" }),
        "The main gates of the city are west of here, at the end of"
      + " the wide avenue that leads into Telberin from outside the"
      + " city walls.\n");
    add_item( ({ "plaques", "signs", "shops", "local shops"}),
        "Two prominant plaques are visible from the plaza. A square"
      + " plaque on a building just to the north reads: 'Armourer.'"
      + " A long building to the east carries an oval plaque which"
      + " reads 'Arms Shop.'\n");
    add_item( ({ "plaque", "sign" }),
        "There are two plaques here, a square one to the north,"
      + " and an oval one on a building to the east. Which do you"
      + " wish to examine?\n");
    add_item( ({ "north plaque", "northern plaque",
                 "north sign", "northern sign",
                 "square plaque", "square sign" }),
        "The square sign reads: 'Eril - Armourer.' It hangs"
      + " on a large building to the north.\n");
    add_item( ({ "east plaque", "eastern plaque",
                 "east sign", "eastern sign",
                 "oval plaque", "oval sign" }),
        "The oval sign reads: 'The Telberin Arms Shop - Annu Vashenti,"
      + " Dealer.' It has been hung before the doorway to a long"
      + " building to the east.\n");

    add_cmd_item( ({ "plaques", "signs", "plaque", "sign" }),
                  ({ "read" }),
        "The square plaque to the north reads: 'Armourer,' while"
      + " the oval plaque to the east reads: 'Arms Shop.'\n");
    add_cmd_item( ({ "north plaque", "northern plaque",
                     "north sign", "northern sign",
                     "square plaque", "square sign" }),
                  ({ "read" }),
        "The plaque reads: 'Eril - Armourer.'\n");
    add_cmd_item( ({ "east plaque", "eastern plaque",
                     "east sign", "eastern sign",
                     "oval plaque", "oval sign" }),
                  ({ "read" }),
        "The plaque reads: 'The Telberin Arms Shop - Annu Vashenti,"
      + " Dealer.'\n");

    add_exit("/d/Emerald/telberin/mercantile/arms_shop", "east", 0, 1, 1);
    add_exit("/d/Emerald/telberin/mercantile/armoury/armoury", "north", 0, 1, 1);
    add_exit("artisans_way05", "southeast");
    add_exit("west_gate", "west");

    add_building(TELBERIN_MERCANTILE_DIR + "armoury/armoury");
    add_building(TELBERIN_MERCANTILE_DIR + "arms_shop");

    set_no_exit_msg( ({ "northeast" }),
        "The way to the northeast has been shut off. In light of the"
      + " recent raids, heavy repair work is being done to the northern"
      + " stretch of Artisans Way.\n");
}
