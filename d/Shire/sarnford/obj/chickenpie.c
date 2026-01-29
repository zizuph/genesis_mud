#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/food";

int do_nibble(string str);
int do_snack(string str);

void
create_food() 
{
    set_name("pie");
    set_pname("pies");
    set_short("chicken pie");
    set_pshort("chicken pies");
    set_adj(({"chicken"}));
    set_long("Baked with a golden crust which seems perfect for nibbling on, " 
        + "you can smell the delicious chicken which has been baked with " 
        + "carrots and peas inside this pie. This delicious treat looks "
        + "perfect for snacking on!\n");
    set_amount(250);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 75);
}

init()
{
    ::init();
    add_action("do_nibble","nibble");
    add_action("do_snack","snack");
}

int
do_nibble(string str)
{
    notify_fail("Nibble what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You casually break off a piece of crust from your chicken " +
        "pie so that you have something to nibble on.\n");
    SAYBB(" nibbles casually on a piece of chicken pie crust.");
    return 1;
}


int
do_snack(string str)
{
    notify_fail("Snack on what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("You set your chicken pie before you and settle down for a nice " +
        "snack. The chicken has been cooked just right, and a creamy " +
        "sauce covers the carrots and peas hidden within the crust. " +
        "The warm meal settles comfortably inside your stomach.\n");
    SAYBB(" enjoys a quick snack, eating their chicken pie.\n");
    TP->command("eat chicken pie");
    return 1;
}