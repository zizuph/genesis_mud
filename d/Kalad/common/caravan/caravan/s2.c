#include "../default.h"
inherit CVAN_ROOM;

#define STEP	("@@step:/d/Kalad/common/caravan/step")

void
create_cvan_room()
{
    (CVAN + "step")->load();

    set_short("Caravan Street");
    set_long(
      "You are on Caravan Street just southwest of " +
      "Wayfarer's Boulevard. " +
      "This wide concourse is paved in cobblestones and continues " +
      "southwest towards its terminus at the southern end " +
      "of the city. The odors of hay and manure emanate " +
      "from a large two story building to the west. " +
      "Just to the east of the street is " +
      "the Caravan Lot, a large muddy field, filled " +
      "to capacity with the wagons and pack animals " +
      "of the visiting merchants and their retinues. " +
      "The ground here is littered with animal refuse. " +
      "\n");

    add_item( ({ "building", "large building" }),
      "Apparently a large stable for horses.\n");

    add_item(({ "street", "caravan street", "concourse", "wide concourse" }),BS(
	"It is paved in cobblestones and " +
	"runs northeast towards Wayfarer's Boulevard and " +
	"southwest towards its terminus at the southern end " +
	"of the city. It is littered with animal refuse.\n"));

    add_item("ground",BS(
	"The ground is completely littered with animal refuse " +
	"and it takes most of your attention to avoid " +
	"stepping in it.\n"));

    add_item(({ "stones", "cobblestones", "pavement", "cobbles" }),BS(
	"The stone cobbles of the street are worn and missing in " +
	"places but overall the pavement is in good repair for " +
	"such a well-travelled roadway. They are completely " +
	"littered with animal refuse.\n"));

    add_item(({ "refuse", "animal refuse" }),
      "The ground is completely littered with it. " +
      "Upon closer examination, for those who find " +
      "interest in such things, it appears to come " +
      "from many varieties of animal, though ox " +
      "seems to be prominent.\n");

    add_exit(CVAN + "caravan-wayfar", "northeast", STEP, 1);
    add_exit(CVAN + "caravan/s3", "southwest", STEP, 1);
    add_exit(CVAN + "lot/s4", "east");
}
