inherit "/d/Rhovanion/common/esgaroth/esroom";
inherit "/lib/pub";

#include <stdproperties.h>

create_room()
{
    set_short("Western pub");
    set_long("This is the pub of the golden claw.  It seems to be far more " +
        "popular than its competitor.  You can leave here to the west or " +
        "the south, both leave back out to the street, providing a " +
        "sporadic flow from one side of the bar to the other.  There is a " +
        "menu here with the food and drinks you can buy.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("/d/Rhovanion/common/esgaroth/es-3-4", "west");
    add_exit("/d/Rhovanion/common/esgaroth/es-4-5", "south");
    add_drink(({ "true beer", "beer" }), "beer", "true", 100, 10, 100,
        "true beer", "true beers", "This is a true beer, icy cold from " +
        "the water of the lake, and golden in the light.\n");
    add_drink(({ "wine", "sweet wine" }), "wine", "sweet", 150, 15, 200,
        "sweet wine", "sweet wine", "This sweet wine is imported from " +
        "other places, since no grapes grow in Esgaroth.  It is rather " +
        "strong for a wine.\n");
    add_drink(({ "bourbon", "straight bourbon" }), "bourbon", "straight", 200, 20, 300,
        "straight bourbon", "straight bourbons", "This is a bourbon served " +
        "straight from the bottle, without water or ice to dilute it.\n");
    add_food(({ "steak", "tender steak" }), "steak", "tender", 300, 155,
        "tender steak", "tender steaks", "This is a tender steak, but you " +
        "aren't really sure where it is from, since you see no cows here " +
        "in Esgaroth.\n");
    add_food(({ "steak", "grand steak", "big steak", "big grand steak" }), 
        "steak", ({ "big", "grand" }), 600, 610,
        "big grand steak", "big grand steaks", "This is a big portion of a "+
        "tender steak. It is quite expensive and so only real grand can "+
        "afford it. You aren't really sure where it is from, since you see "+
        "no cows here in Esgaroth.\n");
    add_food(({ "fish", "baked fish" }), "fish", "baked", 150, 45,
        "baked fish", "baked fish", "This is baked fish, caught from the " +
        "lake here in town.\n");
    add_food(({ "fish", "smoked fish", "small fish", "small smoked fish" }), 
        "fish", ({ "small", "smoked" }), 75, 15,
        "small smoked fish", "small smoked fish", 
        "This is small fish caught from the lake here in town. It has been "+
        "smoked in the chimney of this pub.\n");
    add_item("menu", "You could read it.\n");
    add_cmd_item("menu", "read", "You can buy the following things from us" +
        "(all purchases are final):\n" +
        " drinks:\n" +
        "    true beer for 100 coppers\n" +
        "    sweet wine for 200 coppers\n" +
        "    straight bourbon for 300 coppers\n" +
        " meals:\n" +
        "    tender steak for 155 coppers\n" +
        "    big grand steak for 610 coppers\n" +
        "    baked fish for 45 coppers\n" +
        "    small smoked fish for 15 coppers\n");
}

init()
{
    ::init();
    init_pub();
}
