/* Created 29/9/98 by Bishop, of Calia. This is the tavern in
the gnome village of Rust. */

#pragma save_binary

inherit "/std/room";
inherit "/lib/pub";

#include <defs.h>
#include <stdproperties.h>
#include <macros.h>

int
read(string str)
{
    write("\n" +
        "Drinks:\n" +
        "\n" +
        "Sparkling Wine:     70 cc\n" +
        "Red Wine:          110 cc\n" +
        "Gnomish Liquor:    250 cc\n" +
        "\n" +
        "\n" +
        "Food:\n" +
        "\n" +
        "Mushroom Soup:      30 cc\n" +
        "Roasted Salmon:     70 cc\n" +
        "Steaming Stew:      180 cc\n" +
        "\n");
    return 1;
}

void
create_room()
{
    set_short("Tavern in the gnome village");

    set_long("This is a tavern in the gnome village. There's plenty" +
        " of room in here, with about a dozen tables. The plush chairs" +
        " look very comfortable, for someone of gnome size at least." +
        " Behind the counter stands a young gnome, who is wearing" +
        " an apron. Behind him on the wall you see a menu. The room is" +
        " rather dimly lit by a couple of oil-lamps hanging from the" +
        " ceiling.\n");

    add_item("tables","The tables are round, woooden, and placed" + 
        " haphazardly around this tavern.\n");
    add_item(({"chairs","plush chairs"}),"They have polstered" +
        " arm rests and a pillow to sit on. Seems like a good" +
        " place to rest a weary body.\n");
    add_item("counter","It has been fashioned out of a solid oak" +
        " log.\n");
    add_item(({"gnome","young gnome"}),"He looks young for a gnome," +
        " perhaps in his forties.\n");
    add_item(({"wall","walls"}),"The walls are plain.\n");
    add_item("apron","The apron is white and clean.\n");
    add_item("menu","It's written in chalk on a board. You could" +
        " read it.\n");
    add_item(({"lamps","oil-lamps"}),"They cast the room in a dim" +
        " light.\n");
    add_item("ceiling","The ceiling is about 10 feet up. Behind the" +
        " counter you see a ladder leading up through a hole.\n");
    add_item("ladder","It's made out of wood, and looks stable.\n");
    add_item("hole","It leads up to the second floor. You can't get" +
        " a good look at what's up there.\n");
    add_item("pillow","It's red and plush.\n");

    add_drink(({"wine","wines","sparkling wine","sparkling wines"}),
        "wine","sparkling",150,15,70,0,0,
        "This bubbly, clear wine has a mild smell that tickles your" +
        " nose.\n",0);
    add_drink(({"wine","wines","red wine","red wines"}),
        "wine","red",150,25,110,0,0,
        "The rich smell of this deep red wine intoxicates you.\n",0);
    add_drink(({"liquor","liquors","gnomish liquor","gnomish liquors"}),
        "liquor","gnomish",75,40,250,0,0,
        "This clear, tree-coloured liquor smells of damp earth and" +
        " some kind of exotic spice. It looks powerful.\n",0);

    add_food(({"soup","soups","mushroom soup","mushroom soups"}),
        "soup","mushroom",35,30,0,0,
        "This warm, creamy soup looks like it would warm your body.\n",0);
    add_food(({"trout","trouts","roasted trout","roasted trouts"}),
        "trout","roasted",90,70,0,0,
        "This piece of well-seasoned roast trout looks tasty.\n",0);
    add_food(({"stew","stews","steaming stew","steaming stews"}),
        "stew","steaming",180,180,0,0,
        "This is a large portion of a steaming hot stew. Judging" +
        " from the smell, it's based on some kind of smoked meat" +
        " and herbs.\n",0);

    add_cmd_item("menu","read",read);
    add_cmd_item("ladder","climb","The barkeeper shakes his head" +
        " as you approach the ladder, telling you that guests aren't" +
        " allowed to enter the kitchen and private quarters.\n");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"village_path4","out",0,1);
}

void
init()
{
    ::init();
    init_pub();
}



