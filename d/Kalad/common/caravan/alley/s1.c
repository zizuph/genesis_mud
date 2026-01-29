#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Cargo Alley");
    set_long("You are now at the center of the street called Cargo Alley. "+
      "The street is appropriately named because to your east lie rows "+
      "upon rows of storage sheds, where cargo for the Trading Company is "+
      "stored. To the west is the high stone wall surrounding the Trading "+
      "Company headquarters. Visible to the north are the huge stone walls "+
      "surrounding Kabal. Large amounts of refuse are littered across the "+
      "ground.\n");

    add_item( ({ "street" }),
      "This street is just packed dirt.\n");

    add_item( ({ "sheds", "shed" }),
      "They are wooden sheds about one story in height, used for storing "+
      "valuable trade goods such as spices, armor, weapons and clothing. "+
      "It looks like you could go east towards them.\n");

    add_item( ({ "wall", "stone wall" }),
      "This stone wall is approximately fifteen feet in height, the wall is "+
      "amazing for the lack of graffiti or other filth on its surface.\n");

    add_item( ({ "refuse" }),
      "Upon further examination, you notice that the majority of the animal "+
      "refuse belongs to oxen and horses.\n");

    add_exit(CVAN + "alley_gate", "north");
    add_exit(CVAN + "alley_wayfar", "south");

    add_cmd_item(({ "east", "east" }), "go", "@@go");
}

string
go()
{
    write("You walk to within a few feet of the storage sheds.\n");
    set_dircmd("east");
    TP->move_living("east towards the storage sheds", CVAN + "alley/yard1");
    return "Dusty air swirls about you.\n";
}
