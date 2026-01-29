#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/drink";

int do_smell(string str);
int do_sip(string str);
int do_drink(string str);

void
create_drink() 
{
	set_name("water");
    set_pname("waters");
    set_short("dirty glass of water");
    set_pshort("dirty glasses of water");
    set_adj(({"dirty", "brackish"}));
    set_long("This glass of water looks a little bit dirty and brackish, " +
        "giving it that unique taste you just cannot find in fresh water. " +
        "You might want to smell it first before taking a sip.\n");
    set_soft_amount(100);

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 8);
}

init()
{
    ::init();
    add_action("do_smell","smell");
    add_action("do_sip","sip");
    add_action("do_drink","drink");
}

int
do_smell(string str)
{
    notify_fail("Smell what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You bring the glass of dirty, brackish water up to your face " +
        "so that you can smell the distinct scent which eminates from " +
        "it.\n");
    SAYBB(" smells a glass of water carefully.");
    return 1;
}

int
do_sip(string str)
{
    notify_fail("Sip what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("Taking care to only have a small sip of the dirty, " +
        "brackish water, the unique flavour of muddy bog water " +
        "trickles down the back of your throat.\n");
    SAYBB(" sips carefully on a small glass of water.\n");
    return 1;
}

int
do_drink(string str)
{
    notify_fail("Drink what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("Lifting the glass to your lips, you quickly down the " +
        "contents and feel the dirty, brackish water settle deep " +
        "inside your stomach.\n");
    SAYBB(" lifts a glass of dirty water to their lips.\n");
    TP->command("drink water");
    return 1;
}