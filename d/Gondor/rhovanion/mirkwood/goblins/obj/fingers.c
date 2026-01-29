#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/food";

int do_munch(string str);
int do_snack(string str);
int do_gobble(string str);

void
create_food() 
{
    set_name(({"fingers", "charred fingers", "bowl"}));
    set_pname(({"fingers", "charred fingers", "bowls"}));
    set_short("bowl of charred fingers");
    set_pshort("bowls of charred fingers");
    set_long("This small bowl contains many long, thin strips of " +
        "charred and blackened meat called fingers. A specialty dish " +
        "from the Chipped Mug tavern, fingers are great for snacking " +
        "and munching on, even if most people gobble them up far too " +
        "quickly.\n");
    set_amount(375);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 195);
}

init()
{
    ::init();
    add_action("do_munch","munch");
    add_action("do_snack","snack");
    add_action("do_gobble","gobble");
}


int
do_munch(string str)
{
    notify_fail("Munch on what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Plucking a tasty looking charred finger from you bowl, you " +
        "munch happily on it, savouring the crispy treat.\n");
    SAYBB(" plucks a charred finger from their bowl and munches " +
        "happily on it.\n");
    return 1;
}

int
do_snack(string str)
{
    notify_fail("Snack on what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Feeling a touch hungry, you reach into your bowl of fingers " +
        "and take one out for a snack. The crispy, charred flavour " +
        "of the meat is delicately balanced by being generously " +
        "salted. Elven food never tasted good!\n");
    SAYBB(" sneaks a charred finger out from their bowl for a " +
        "discreet snack.\n");
    return 1;
}

int
do_gobble(string str)
{
    notify_fail("Gobble what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Eyeing the bowl of fingers, you grab one out and pop it in " +
        "your mouth. Finding the salty, crispy taste of the fingers " +
        "rather enticing, you soon grab another. And then another! " +
        "until you finally find yourself gobbling down the entire " +
        "bowl!\n");
    SAYBB(" pulls out a bowl of charred fingers and promptly proceeds " +
        "to gobble them all down ravenously.\n");
    TP->command("eat bowl of charred fingers");
    return 1;
}