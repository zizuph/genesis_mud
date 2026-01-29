#include "../default.h"
inherit CVAN_ROOM;

#define STEP	("@@step:/d/Kalad/common/caravan/step")

void
create_cvan_room()
{
    (CVAN + "step")->load();

    set_short("Wayfarer's Boulevard");
    set_long(
      "You are standing on Wayfarer's Boulevard. " +
      "This well-used thoroughfare is paved in " +
      "cobblestone and runs west towards "+
      "Caravan Street and east towards Wall Street. "+
      "Tightly packed buildings line the north side " +
      "of the street and a worn sign hangs over the doorway " +
      "to one of them. Just south of the street is " +
      "the Caravan Lot, a large muddy field, filled " +
      "to capacity with the wagons and pack animals " +
      "of the visiting merchants and their retinues. " +
      "The ground here is littered with animal refuse. " +
      "\n");

    add_item(({ "sign", "worn sign" }), "@@sign");

    add_item(({ "street", "boulevard",
	"wayfarer's boulevard", "thoroughfare" }),
      "It is paved in cobblestones and runs " +
      "east towards Caravan Street and west " +
      "towards Wall Street. It is littered with animal refuse.\n");

    add_item(({ "buildings", "tightly packed buildings",
	"north", "north side", "north side of street" }),
      "Tightly packed buildings line the north side of " +
      "the street, providing housing for the merchants " +
      "and laborers of the Caravan District. A worn sign " +
      "hangs over one of the doorways.\n");

    add_item("ground",
      "The ground is completely littered with animal refuse " +
      "and it takes most of your attention to avoid " +
      "stepping in it.\n");

    add_item(({ "stones", "cobblestones", "pavement", "cobbles" }),
      "The stone cobbles of the street are worn and missing in places " +
      "but overall the pavement is in good repair for such a well-travelled " +
      "roadway. They are completely littered with animal refuse.\n");

    add_item(({ "refuse", "animal refuse" }),
      "The ground is completely littered with it. " +
      "Upon closer examination, for those who find " +
      "interest in such things, it appears to come " +
      "from many varieties of animal, though ox " +
      "seems to be prominent.\n");

    add_item(({ "caravan lot", "lot", "field", "large field",
	"large muddy field", "muddy field" }),
      "This large muddy field to the south of the street " +
      "is commonly known as the Caravan Lot. It is filled " +
      "to capacity with the wagons and pack animals of " +
      "visiting merchant's and their retinues, here to " +
      "sell their wares in the districts of Kabal.\n");

    add_item(({ "pack animals", "animals" }),
      "Pack animals of all types can be seen amidst " +
      "the wagons to the south and are probably responsible " +
      "for much of the mess about your feet. Mules, " +
      "horses, oxen, and camels are most prominent, " +
      "though an occasional exotic can be seen.\n");

    add_item(({ "merchants", "visitors", "retinues", "laborers",
	"guards", "caravan guards" }),
      "Visiting merchants are abundant in the field " +
      "to the south, directing the loading and unloading " +
      "of goods into and out of the wagons. Laborer's " +
      "hurry about their chores, sweating under the " +
      "relentless Kalad sun, as the hired caravan guards " +
      "watch idly from the shade of the wagons.\n");

    add_item(({ "wagons", "caravans" }),
      "Wagons are crowded in to every available space " +
      "in the field to the south. They contain the wares " +
      "of the visiting merchants and laborers busy " +
      "themselves with the loading and unloading. Some " +
      "of the larger caravans have their wagons pulled " +
      "up in a circle.\n");

    add_exit(CVAN + "shop/wayfar_guild", "north");
    add_exit(CVAN + "beggar_wayfar", "east");
    add_exit(CVAN + "caravan-wayfar", "west", STEP);
}

string
sign()
{
    return
    "     ****************************\n" +
    "     *                          *\n" +
    "     *  Kabal Wayfarer's Guild  *\n" +
    "     *                          *\n" +
    "     *  - Travellers Welcome    *\n" +
    "     *  - Information           *\n" +
    "     *  - Training Facilities   *\n" +
    "     *  - Open 24 hrs           *\n" +
    "     *                          *\n" +
    "     ****************************\n";
}

int
read_sign(string str)
{
    NF("Read what?\n");
    if (!str || (str != "worn sign" && str != "sign"))
	return 0;

    write(sign());
    return 1;
}

void
init()
{
    ::init();
    AA(read_sign,read);
}
