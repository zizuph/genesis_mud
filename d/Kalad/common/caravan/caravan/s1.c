#include "../default.h"
inherit CVAN_ROOM;

#define STEP	("@@step:/d/Kalad/common/caravan/step")

void
create_cvan_room()
{
    (CVAN + "step")->load();

    set_short("Caravan Street");
    set_long(
      "You are on Caravan Street just south of the Caravan "+
      "Gate. This wide concourse is paved in cobblestones and continues " +
      "south towards Wayfarer's Boulevard. "+
      "Buildings of various sizes compete for space on either side " +
      "and an elaborately painted sign is visible in one window " +
      "to the west. To the east there is a two-story stone building. "+
      "The ground here is littered with animal refuse.\n");

    add_item(({ "street", "caravan street", "concourse", "wide concourse" }),
      "It is paved in cobblestones and " +
      "runs north towards the Caravan Gate and south towards "+
      "Wayfarer's Boulevard. It is littered with animal refuse.\n");

    add_item("ground",BS(
	"The ground is completely littered with animal refuse " +
	"and it takes most of your attention to avoid " +
	"stepping in it.\n"));

    add_item(({ "stones", "cobblestones", "pavement", "cobbles" }),
      "The stone cobbles of the street are worn and missing in places " +
      "but overall the pavement is in good repair for such a well-travelled " +
      "roadway. They are completely littered with animal refuse.\n");

    add_item(({ "buildings", "structures" }),
      "The structures are of varying sizes, usually two or three stories " +
      "high, and have been squeezed in wherever there was space. They " +
      "provide lodging for the local shopkeepers and laborers of the district. " +
      "An elaborately painted sign is visible in the window of " +
      "one to the west.\n");

    add_item("window", "Exotic curtains provide " +
      "a colourful backdrop to an elaborately painted sign, " +
      "hanging in the window of a building to the west.\n");

    add_item(({ "curtains", "exotic curtains",
	"coloured curtains", "brightly coloured curtains" }),
      "These brightly coloured curtains hang in the " +
      "window of a building to the west. They have an " +
      "exotic flare to them and were possibly brought " +
      "across the Waste by one of the visiting caravans.\n");

    add_item("ground",
      "The ground is completely littered with animal refuse " +
      "and it takes most of your attention to avoid " +
      "stepping in it.\n");

    add_item(({ "refuse", "animal refuse" }),
      "The ground is completely littered with it. " +
      "Upon closer examination, for those who find " +
      "interest in such things, it appears to come " +
      "from many varieties of animal, though ox " +
      "seems to be prominent.\n");

    add_item(({ "sign", "painted sign", "elaborately painted sign" }),
      "@@sign");

    add_item( ({ "stone building" }),
      "It's a large, squat two-story building just a little to your "+
      "east. In front of the building is a sign proclaiming it as the "+
      "best inn in town : The Journey's End.\n"+
      "The sign also says: No dirty people allowed!\n");

    add_exit(CVAN + "caravan_gate", "north",STEP, 0);
    add_exit(CVAN + "shop/jeinn", "east", "@@dirty_check");
    add_exit(CVAN + "caravan-wayfar", "south",STEP, 0);
    add_exit(CVAN + "shop/perfume_shop", "west");
}

string
sign()
{
    return
    "     {}{}{}{}{}{}{}{}{}{}{}{}{}{}{}\n" +
    "     <>                          <>\n" +
    "     {}        Perfumer          {}\n" +
    "     {}                          {}\n" +
    "     <>  - All manner of exotic  <>\n" +
    "     {}     scents and aromas    {}\n" +
    "     {}  - Open from 7 to 10     {}\n" +
    "     <>                          <>\n" +
    "     {}{}{}{}{}{}{}{}{}{}{}{}{}{}{}\n";
}

int
read_sign(string str)
{
    NF("Read what?\n");
    if (!str || (str != "painted sign" && str != "sign"
	&& str != "elaborately painted sign"))
	return 0;

    write(sign());
    return 1;
}

int
block()
{
    write("The inn doesn't look like its open yet.\n");
    return 1;
}

int
dirty_check()
{
    object *ob;
    int i;

    if(TP->query_invis())
	return 0;

    ob = deep_inventory(TP);
    for(i = 0; i < sizeof(ob); i++)
	if(ob[i]->id("dirty"))
	{
	    write("The innkeeper suddenly pops his head out and shouts: Hey, you can't "+
	      "come in here and ruin my clean inn. Go clean yourself up first.\n");
	    say("The innkeeper appears from within the inn, and stops " + QCTNAME(TP) + " from entering because " + TP->query_pronoun() + " is so dirty.\n");
	    return 1;
	}
    write("You stride into the inn, sounds of drinking and merriment "+
      "greeting you like an old lover.\n");
    say(QCTNAME(TP) + " enters the inn to the east.\n");
    return 0;
}

void
init()
{
    ::init();
    AA(read_sign,read);
}
