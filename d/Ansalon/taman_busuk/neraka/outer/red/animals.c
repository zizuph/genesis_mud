/* Ashlar, 7 Sep 97 */

#include "../local.h"
#include "/d/Ansalon/common/defs.h";
#include <money.h>
#include <macros.h>

inherit "/lib/trade";
inherit OUTER_IN;

void
create_neraka_room()
{
    set_short("inside an animal shop");
    set_long("This is an animal shop, the prime purveyor of the wild " +
    "and the exotic, according to a large sign hanging from the top " +
    "of a tattered counter. A small, almost rat-like man stands behind " +
    "the counter, studying you with curious eyes. Many different kinds " +
    "of cages line the walls, but they are all empty, and the shop is " +
    "strangely quiet. The only kind of animal for sale, it seems, is " +
    "a bunch of parrots sitting in a large cage on the counter.\n");

    add_item(({"sign","large sign"}),"The sign announces the shop to be " +
    "\"The prime purveyor of the wild and exotic\". The sign shows " +
    "definite signs of being an old sign, and together with the " +
    "resigned look on the owners face, this signifies that the glory days " +
    "of this establishment are long gone.\n");

    add_cmd_item(({"sign","large sign"}),"read",
    "\"The prime purveyor of the wild and exotic!\"\n" +
    "Now! For a limited time only, exotic parrots for only 5 silver coins!\n");

    add_item(({"counter","tattered counter"}),"The counter, once a " +
    "magnificent piece of carved oak, now covered with dust and " +
    "the residue of caged animals, is a pitiful sight. It has an air " +
    "about it, as if stating that the only thing still holding it up " +
    "is the fact that the floor is much dirtier than it already is.\n");

    add_item(({"cages"}),"The cages that line the walls are of many " +
    "different kinds, from great works of finely wrought iron bars to " +
    "nothing more than a wicker basket. They share the common traits of " +
    "dirtiness and emptiness.\n");

    add_item(({"man","owner","small man","rat-like man","small rat-like man"}),
    "The small rat-like man behind the counter is the owner of this shop. " +
    "He studies you hopefully, yet his resignation is plain on his face. " +
    "He looks like a man who put his last pennies on a horse that did not " +
    "only prove to be lame but blind as well.\n");

    add_item(({"large cage","cage"}),
    "The large cage holds a bunch of parrots, the latest craze that the " +
    "owner is trying to cash in on. Obvious from the surroundings, he has " +
    "not done well so far.\n");

    add_item(({"parrots","parrots in cage","bunch of parrots"}),
    "The parrots in the cage are mostly sleeping, probably out of boredom.\n");

    add_item("walls","The walls, hard to see behind the layer of cages " +
    "and the layer of dust, are made of wood.\n");

    add_item("floor","The floor is best left unmentioned, save mentioning " +
    "that walking around in foot-deep mud would have made your marginally " +
    "cleaner.\n"),

    add_item("ceiling","Only a fool looks up at the ceiling when there are " +
    "birds present, unless one wants to present them with a golden " +
    "opportunity of improving their aim.\n");

    add_item("dust","The dust is everywhere, it is no wonder this place " +
    "lacks for customers. It would probably even make goblins want to take " +
    "a bath (though that might be stretching things).\n");

    add_exit(NOUTER+"red/r11","east");
    config_default_trade();
}

void
init()
{
    ::init();
    add_action("do_buy","buy");
}

int
do_buy(string str)
{
    int value, *money_arr;
    string pay_type, get_type, coin_pay_text, coin_get_text;
    object item;
    object ob;
    ob = TP;
    NF("Buy what?\n");
    if(!str)
        return 0;

    switch(str)
    {
        case "parrot":
            item = clone_object(NNPC+"parrot");
            value = 5*12;
        break;
        default:
            NF("You cannot buy any " + str + " here.\n");
            return 0;
    }

    if (TP->query_prop(NERAKA_I_KILLED_PARROT))
    {
        NF("I won't sell to people who torture the poor animals!\n");
        item->remove_object();
        return 0;
    }

    if (sizeof(money_arr = pay(value,TP, pay_type, 0, 0, get_type)) == 1)
    {
        item->remove_object();
        return 0;
    }
    
    coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
				       sizeof(MONEY_TYPES)*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
    write("You pay the owner " +coin_pay_text+ ".\n");
    if (coin_get_text)
      write("You get " + coin_get_text + " in return.\n");

    tell_room(TO,"The small rat-like man opens the large cage and removes " +
    "a parrot, which he hands to " + QTNAME(TP) + ".\n", TP);

    write("The owner opens the large cage and removes a parrot, which " +
    "he hands to you.\n");

    if (item->move(TP))
    {
        write("However, you cannot take the parrot, so he puts it on the " +
        "ground.\n");
        tell_room(TO, "However, " + QTNAME(TP) + " cannot take the parrot, " +
        "so the small rat-like man puts the parrot gently on the ground.\n",
        TP);
        item->move(TO);
    }
    return 1;
}

