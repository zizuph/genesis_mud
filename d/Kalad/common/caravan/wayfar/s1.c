#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Wayfarer Boulevard");
    set_long("You are travelling along Wayfarer Boulevard, a wide "+
      "cobblestoned street that heads west towards an intersection with "+
      "High Street and stretches into the distance east. To the north, "+
      "behind a pair of steel gates, is the large stone edifice that is "+
      "the headquarters for the powerful Trading Company. High stone walls, "+
      "which stretch out from the gates, travel west and east aside the "+
      "street. Several buildings can be seen in the south. Also, a smaller "+
      "intersection is visible eastward.\n");

    add_item(({ "steel gates", "gates" }),
      "You see a pair of black-steel gates that cover the small road leading "+
      "north. They are almost as high as the walls surrounding the edifice, "+
      "rising to around twelve feet in height.\n");

    add_item(({ "large stone edifice", "edifice" }),
      "You gaze in wonder at the structure, not really knowing why, then it hits "+
      "you. The Trading Company's headquarters looks exactly like a nobleman's "+
      "or perhaps even a king's castle! The massive structure, although built "+
      "in the image of a fortress, isn't exactly one. For instance, you can "+
      "see no battlements upon which archers would have a good shot at "+
      "intruders. Also, there is no moat surrounding the building, just "+
      "manicured lawns of grass. Given all these facts, you still feel as "+
      "if you should not come closer, unless you have been invited. "+
      "Something about its appearance, perhaps the dark grey, almost black "+
      "stones it was built of, gives you an eerie feeling.\n");

    add_item(({ "high stone walls", "stone walls", "walls" }),
      "The fifteen foot high walls, which are remarkably clean of filth, "+
      "encircle the entire edifice. If not for the opening made by the "+
      "gates, you would be able to see at most, the very top of the "+
      "building.\n");

    add_item(({ "buildings" }),
      "A few buildings can be seen, among the most noteworthy are a red "+
      "brick building, a wooden house painted black, and another building "+
      "made of white granite.\n");

    add_item(({ "red brick building" }),
      "A small building made of red bricks, uncommon around this area since "+
      "most of the buildings here are made of wood, or rarely stone. It "+
      "looks as if anyone could just enter it.\n");

    add_item(({ "black wooden house" }),
      "A home that looks like any other in the city, except that the wood "+
      "it is built out of is dark black. It looks as if anyone could just "+
      "walk into it.\n");

    add_item(({ "white granite building" }),
      "One of the rare structures in Kabal that are built of stone, since "+
      "only the most important buildings, such as government structures, "+
      "are made of anything other than wood. Near the front of the house "+
      "is a vicious-looking guard dog, it looks like you'll have to run by "+
      "him if you are to get anywhere near the white building.\n");

    add_exit(CVAN + "high-wayfar", "west");
    add_exit(CVAN + "company/s1", "north");
    add_exit(CVAN + "chains_wayfar", "east");

    add_cmd_item(({ "southwest", "red" }), "enter", "@@enter");
    add_cmd_item("red", "enter", "@@enter");
    add_cmd_item(({ "south", "black" }), "walk", "@@walk");
    add_cmd_item("black", "walk", "@@walk");
    add_cmd_item(({ "southeast", "white" }), "run", "@@run");
    add_cmd_item("white", "run", "@@run");
}

int
block()
{
    write("The gates have been barred shut, you cannot enter.\n");
    return 1;
}

string
enter()
{
    write("You open the door to the red building.\n");
    set_dircmd("red");
    TP->move_living("into the red building", CVAN + "wayfar/red");
    return "You close the door behind you.\n";
}

string
walk()
{
    write("You walk into the black building.\n");
    set_dircmd("black");
    TP->move_living("into the black building", CVAN + "wayfar/black");
    return "You close the door behind you.\n" ;
}

string
run()
{
    write("You quickly run past the guard dog and into the white building!\n");
    set_dircmd("white");
    TP->move_living("past the guard dog and into the white building", CVAN + "wayfar/white");
    return "You quickly slam the door shut before the dog catches up to you!\n";
}
