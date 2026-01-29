#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/food";

int do_taste(string str);
int do_devour(string str);

void
create_food() 
{
    set_name(({ "catch", "catch of the day", "fish", "fried fish" }));
    set_pname(({ "catches", "catches of the day", "fishes", "fried fishes" }));
    set_short("catch of the day");
    set_pshort("catches of the day");
    set_adj(({"fresh"}));
    set_long("This large serving of pan-fried fish " 
        + "comes satraight from the kitchens of the famous " 
        + "Sleeping Fisherman Inn. Delicately garnished and " 
        + "cooked to perfection, there is not a more satisfying " 
        + "meal to be found anywhere. This dish is just waiting for "
        + "you to take a taste before devoouring the whole thing!\n");
    set_amount(575);
    add_prop(OBJ_I_WEIGHT,750);
    add_prop(OBJ_I_VOLUME,900);
    add_prop(OBJ_I_VALUE, 500);
}

init()
{
    ::init();
    add_action("do_taste","taste");
    add_action("do_devour","devour");
}

int
do_taste(string str)
{
    notify_fail("Taste what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You take a small piece of pan-fried fish to taste. The fish " +
        "has been fried to perfection, with the taste of herbs and lemon " +
        "mingling on your tongue, whetting your appetite for more.\n");
    SAYBB(" takes a small taste of fish.");
    return 1;
}


int
do_devour(string str)
{
    notify_fail("Devour what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("Unable to resist temptation, you devour the entire fish in " +
        "mere moments! You barely have time to appreciate the delicate " +
        "balance of herbs and lemon which the cook has carefully " +
        "prepared to accompany the fried fish.\n");
    SAYBB(" dives into a large serving of fried fish, devouring it in " +
        "mere moments.\n");
    TP->command("eat catch of the day");
    return 1;
}