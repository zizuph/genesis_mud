#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/food";

int do_inspect(string str);
int do_nibble(string str);
int do_gnaw(string str);
int do_chew(string str);
int do_devour(string str);

void
create_food() 
{
    set_name(({"roast", "roasted meat", "chunk", "meat", "chunk of roasted meat"}));
    set_pname(({"roasts", "chunks", "roasted meats", "meats", "chunks of roasted meat"}));
    set_short("chunk of roasted meat");
    set_pshort("chunks of roasted meat");
    set_long("This chunk of meat looks well aged and heavily seasoned. " +
        "Perhaps a little too aged? It might be good to inspect it first " +
        "before devouring the whole thing. The meat looks a little tough " +
        "and chewy, perhaps it might be easier to nibble on before you " +
        "start to gnaw on the bones.\n");
    set_amount(375);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 195);
}

init()
{
    ::init();
    add_action("do_inspect","inspect");
    add_action("do_nibble","nibble");
    add_action("do_gnaw","gnaw");
    add_action("do_chew","chew");
    add_action("do_devour","devour");
}

int
do_inspect(string str)
{
    notify_fail("Inspect what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You carefully inspect your chunk of roasted meat, but either it " +
        "is not really rotten or there is enough spice and seasoning to " +
        "cover it up. Either way, the meat seems edible enough.\n");
    SAYBB(" carefully inspects a suspect piece of meat.");
    return 1;
}


int
do_nibble(string str)
{
    notify_fail("Nibble on what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("You grab your chunk of meat and nibble just a tiny bit rather " +
        "discreetly. Strange, you were not expecting this meat to " +
        "taste.... Elvish.\n");
    SAYBB(" nibbles discreetly on a chunk of roasted meat.\n");
    return 1;
}

int
do_gnaw(string str)
{
    notify_fail("Gnaw what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Grabbing your chunk of meat in both hands, you dive right in " +
        "and gnaw ravenously on some of the meat which is stuck to " +
        "the bone.\n");
    SAYBB(" greedily gnaws on a large chunk of roasted meat.\n");
    return 1;
}

int
do_chew(string str)
{
    notify_fail("Chew what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("After taking a bite of the heavily seasoned meat, you find it is " +
        "perhaps a bit stringy, forcing you to chew on it noisily before " +
        "swallowing your mouthful. The seasoning might be heavy, but your " +
        "discenring palate detects a flavour which appears to be " +
        "distinctly... Elvish.\n");
    SAYBB(" takes a huge bite of roasted meat and chews on it noisily.\n");
    return 1;
}

int
do_devour(string str)
{
    notify_fail("Devour what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Eyeing the chunk of roasted meat greedily, you thrown caution " +
        "to the wind and devour every last scrap in a quick, messy and " +
        "rather disgusting fashion.\n");
    SAYBB(" devours a huge chunk of roasted meat in a rather disgusting " +
        "fashion.\n");
    TP->command("eat chunk");
    return 1;
}