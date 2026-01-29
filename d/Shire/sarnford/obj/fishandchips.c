#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/food";

int do_smell(string str);
int do_munch(string str);
int do_dip(string str);
int do_chew(string str);
int do_dine(string str);

void
create_food() 
{
    set_name(({"plate of fish and chips", "fish and chips", "fish", "chip", "chips"}));
    set_pname(({"plates of fish and chips"}));
    set_short("plate of fish and chips");
    set_pshort("plates of fish and chips");
    set_adj(({"crispy"}));
    set_long("One of the remarkable fish specials from the " 
        + "famous Sleeping Fisherman Inn, this plate of fish and chips " 
        + "has been made from freshly caught fish from the Brandywine " 
        + "river and roasted taters, lightly salted and cut into chips. "
        + "This meal smells fantastic, and offers you a chance to really "
        + "enjoy a moment to dine.\n");
    add_item(({"tater", "taters"}),
        "These chips have been roasted into crispy perfection! They have " +
        "also been lightly salted, and are accompanied by a tasty sauce " +
        "that you can dip them in. They appear to be perfect for munching " +
        "and chewing on before you decide to dine on the fish itself.\n");
    set_amount(375);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 195);
}

init()
{
    ::init();
    add_action("do_smell","smell");
    add_action("do_munch","munch");
    add_action("do_dip","dip");
    add_action("do_chew","chew");
    add_action("do_dine","dine");
}

int
do_smell(string str)
{
    notify_fail("Smell what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("The smell of fried fish and roasted chips wafts in the air " +
        "before you as you inhale the tantalizing aroma of this " +
        "delicious meal.\n");
    SAYBB(" smiles as they enjoy the wonderful aroma of their fish " +
        "and chips.");
    return 1;
}


int
do_munch(string str)
{
    notify_fail("Munch on what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("You grab a handful of roasted taters and casually pop them " +
        "into your mouth one at a time, fully enjoying yourself as " +
        "you munch on them.\n");
    SAYBB(" munches on a handful of roasted potatoes.\n");
    return 1;
}

int
do_dip(string str)
{
    notify_fail("Dip what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You take a small chunk of roasted potato and casually dip " +
        "it into the small container of sauce that came with your " +
        "order of fish and chips. You then toss the tater into your " +
        "mouth, savouring every bite.\n");
    SAYBB(" dips one of their roasted potatoes into a small container " +
        "of sauce before popping it into their mouth.\n");
    return 1;
}

int
do_chew(string str)
{
    notify_fail("Chew what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Being in the mood for a quick snack, you dig out a tater from " +
    "your order of fish and chips and begin to chew contentedly on it.\n");
    SAYBB(" chews rather noisily on a roasted potato.\n");
    return 1;
}

int
do_dine(string str)
{
    notify_fail("Dine on what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You pause for a moment to appreciate the wonderful meal in " +
        "front of you. The fish has been fried to perfection, and the " +
        "roasted taters have been salted just right! Occasionally dipping " +
        "the fish and the chips in the small container of sauce which " +
        "came with the meal, you take your time and enjoy the meal " +
        "properly, savouring each and every bite.\n");
    SAYBB(" dines peacefully on a delicious looking order of fish and chips.\n");
    TP->command("eat fish and chips");
    return 1;
}