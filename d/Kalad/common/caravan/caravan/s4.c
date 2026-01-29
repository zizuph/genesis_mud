#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Caravan Street");
    set_long(BS(
	"You are on Caravan Street just northeast of Harvest Way. " +
	"This wide concourse is paved in cobblestones and continues " +
	"northeast towards the Caravan Gate. " +
	"Buildings of various sizes compete for space on either side " +
	"and to the west a small sign hangs over the doorway of a " +
	"nondescript dwelling. To the east lies Warehouse Lane.\n"));

    add_item(({ "sign", "small sign" }), "@@sign");

    add_item(({ "street", "caravan street", "concourse", "wide concourse" }),BS(
	"It is paved in cobblestones and " +
	"runs southwest towards Harvest Way and northeast towards " +
	"the Caravan Gate.\n"));

    add_item(({ "stones", "cobblestones", "pavement", "cobbles" }),BS(
	"The stone cobbles of the street are worn and missing in places " +
	"but overall the pavement is in good repair for such a well-travelled " +
	"roadway.\n"));

    add_item(({ "buildings", "structures" }),BS(
	"The structures are of varying sizes, usually two or three stories " +
	"high, and have been squeezed in wherever there was space. They " +
	"provide lodging for the local shopkeepers and laborers of " +
	"the district. A small sign hangs over the doorway of one such " +
	"edifice to the west.\n"));

    add_item(({ "doorway", "edifice", "door", "three story structure",
	"dwelling", "nondescript dwelling" }),BS(
	"A doorway leads in to a three story structure to the west " +
	"and a small sign hangs over it.\n"));

    add_item( ({ "warehouse lane", "lane" }),
      "It is a smaller sideroad that heads eastward, you can see several "+
      "large warehouses lining the street.\n");

    add_exit(CVAN + "caravan_serv", "northeast");
    add_exit(CVAN + "shop/mmshop", "west");
    add_exit(CVAN + "caravan-harvest", "southwest");
    add_exit(CVAN + "warehouse/s1", "east");
}

string
sign()
{
    return "\n" +
    "     *********************\n" +
    "     *                   *\n" +
    "     *    Ystof Olim     *\n" +
    "     *  Master Mapmaker  *\n" +
    "     *                   *\n" +
    "     *   -Open 7 to 10   *\n" +
    "     *                   *\n" +
    "     *********************\n";
}

int
read_sign(string str)
{
    NF("Read what?\n");
    if (!str || (str != "small sign" && str != "sign"))
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
