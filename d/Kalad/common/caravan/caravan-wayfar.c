#include "default.h"
inherit CVAN_ROOM;

object ob1;

#define	STEP	("@@step:/d/Kalad/common/caravan/step")

void reset_room();

void
create_cvan_room()
{
    (CVAN + "step")->load();

    set_short("Intersection of Caravan St and Wayfarer's Blvd");
    set_long(
      "This is the intersection of Caravan Street and Wayfarer's " +
      "Boulevard, both streets paved with cobblestones. " +
      "Caravan street heads north towards the " +
      "Caravan Gate and southwest towards its terminus at the " +
      "southern end of the city. Wayfarer's Boulevard crosses " +
      "here, leading east-west. To the southeast is " +
      "the Caravan Lot, a large muddy field, filled " +
      "to capacity with the wagons and pack animals " +
      "of the visiting merchants and their retinues. " +
      "The ground here is littered with animal refuse. " +
      "\n");

    add_item(({ "intersection", "streets" }),
      "You are standing in the intersection of Caravan " +
      "Street and Wayfarer's Boulevard. Both streets are " +
      "paved in cobblestones which are littered with animal " +
      "refuse. Caravan Street heads north towards the " +
      "Caravan Gate and southwest towards its terminus at the " +
      "southern end of the city. Wayfarer's Boulevard leads " +
      "east-west.\n");

    add_item("street", "Which street? Caravan Street or " +
      "Wayfarer's Boulevard.\n");

    add_item(({ "boulevard", "wayfarer's boulevard" }),
      "Wayfarer's Boulevard crosses Caravan Street here, " +
      "leading east-west. It is paved in cobblestones " +
      "which are littered in animal refuse.\n");

    add_item("caravan street",
      "Caravan Street crosses Wayfarer's Boulevard here, " +
      "heading north towards the Caravan Gate and " +
      "southwest towards its terminus at the southern end " +
      "of the city. It is paved in cobblestones " +
      "which are littered in animal refuse.\n");

    add_item("ground",
      "The ground is completely littered with animal refuse " +
      "and it takes most of your attention to avoid " +
      "stepping in it.\n");

    add_item(({ "stones", "cobblestones", "pavement", "cobbles" }),
      "The stone cobbles of the streets are worn and " +
      "missing in places but overall the pavement is in " +
      "good repair for such a well-travelled intersection. " +
      "They are completely littered with animal refuse.\n");

    add_item(({ "refuse", "animal refuse" }),
      "The ground is completely littered with it. " +
      "Upon closer examination, for those who find " +
      "interest in such things, it appears to come " +
      "from many varieties of animal, though ox " +
      "seems to be prominent.\n");

    add_item(({ "caravan lot", "lot", "field", "large field",
	"large muddy field", "muddy field" }),
      "This large muddy field to the southeast of the "+
      "intersection is commonly known as the Caravan Lot. It is " +
      "filled to capacity with the wagons and pack animals of " +
      "visiting merchant's and their retinues, here to " +
      "sell their wares in the districts of Kabal.\n");

    add_item(({ "pack animals", "animals" }),
      "Pack animals of all types can be seen amidst " +
      "the wagons to the southeast and are probably responsible "+
      "for much of the mess about your feet. Mules, " +
      "horses, oxen, and camels are most prominent, " +
      "though an occasional exotic can be seen.\n");

    add_item(({ "merchants", "visitors", "retinues", "laborers",
	"guards", "caravan guards" }),
      "Visiting merchants are abundant in the field " +
      "to the southeast, directing the loading and unloading "+
      "of goods into and out of the wagons. Laborer's " +
      "hurry about their chores, sweating under the " +
      "relentless Kalad sun, as the hired caravan guards " +
      "watch idly from the shade of the wagons.\n");

    add_item(({ "wagons", "caravans" }),
      "Wagons are crowded in to every available space " +
      "in the field to the southeast. They contain the wares  "+
      "of the visiting merchants and laborers busy " +
      "themselves with the loading and unloading. Some " +
      "of the larger caravans have their wagons pulled " +
      "up in a circle.\n");

    add_exit(CVAN + "caravan/s1", "north", STEP);
    add_exit(CVAN + "caravan/s2", "southwest", STEP);
    add_exit(CVAN + "wayfar/s4", "east", STEP);
    add_exit(CVAN + "wayfar/s3", "west");

    reset_room();
}

void
reset_room()
{
    if (!ob1)
    {
	ob1 = clone_object(NPC + "cmilitia");
	ob1->move_living("M", TO);
    }
}
