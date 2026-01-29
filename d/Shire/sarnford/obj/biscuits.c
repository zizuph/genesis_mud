#include "/d/Gondor/rhovanion/mirkwood/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

inherit "/std/food";

int do_munch(string str);
int do_juggle(string str);
int do_blow(string str);

void
create_food() 
{
    set_name(({ "biscuits", "tray of biscuits" }));
    set_pname("trays of biscuits");
    set_short("tray of biscuits");
    set_pshort("trays of biscuits");
    set_adj("tray");
    set_long("This small tray is full of delicious home-made " 
        + "biscuits that look as though they have just come right out " 
        + "of the oven. They look perfect for munching on, even if "
        + "you might have to blow on them to cool them down first.\n");
    add_item(({"tray"}),
        "This tray contains several warm biscuits, fresh from the " +
        "oven. You could munch on them if you are hungry, or even " +
        "juggle them if you are in a playful mood.\n");

    set_amount(150);

    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 25);
}

void

init()
{
    ::init();
    add_action("do_munch","munch");
    add_action("do_juggle","juggle");
    add_action("do_blow","blow");
}

int
do_munch(string str)
{
    notify_fail("Munch what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You take a warm biscuit from the tray and munch happily upon it.\n");
    SAYBB(" smiles contentedly as they happily munch on a biscuit.");
    return 1;
}


int
do_juggle(string str)
{
    notify_fail("Juggle what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("You grab a couple biscuits from the tray and begin to juggle " +
        "them playfully.\n");
    SAYBB(" plays with their food.\n");
    return 1;
}

int
do_blow(string str)
{
    notify_fail("Blow on what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("The biscuits are still a bit hot, so you quickly blow " +
        "on the tray to cool them down before eating one.\n");
    SAYBB(" cools down their biscuits before devouring a biscuit.\n");
    return 1;
}
