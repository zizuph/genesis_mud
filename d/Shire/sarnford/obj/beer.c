#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/drink";

int do_sip(string str);
int do_wipe(string str);
int do_chug(string str);

void
create_drink() 
{
    set_name(({"beer", "brown beer", "mug of brown beer"}));
    set_pname(({"beers", "brown beers", "mugs of brown beers"}));
    set_short("mug of brown beer");
    set_pshort("mugs of brown beer");
    set_long("This is a mug of rich, dark beer which has obviously "
        + "been brewed by some local farmer. The beer is somewhat "
        + "foamy, so you might want to wipe it first before you take "
        + "a sip. Of course, some people prefer to just chug down "
        + "their beer regardless.\n");

    set_soft_amount(100);
    set_alco_amount(15);

    add_prop(OBJ_I_WEIGHT, 54);
    add_prop(OBJ_I_VOLUME, 54);
    add_prop(OBJ_I_VALUE, F_VALUE_ALCO(15));
}

void

init()
{
    ::init();
    add_action("do_sip","sip");
    add_action("do_wipe", "wipe");
    add_action("do_chug", "chug");
}

int
do_sip(string str)
{
    notify_fail("Sip what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("You raise the foaming mug of dark, brown beer to your lips " +
        "and savour the rich flavour as you take a long sip.\n");
    SAYBB(" takes a long sip from their mug of brown beer.\n");
    return 1;
}

int
do_wipe(string str)
{
    notify_fail("wipe what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("You carefully wipe the foam off the top of your beer " +
        "to avoid making a mess.\n");
    SAYBB(" wipes away some foam from their beer.\n");
    return 1;
}

int
do_chug(string str)
{
    notify_fail("Chug what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You pause to admire your beer for a moment and then quickly " +
        "chug it down, enjoying every last drop!\n");
    SAYBB(" quickly chugs down the last of their brown beer.\n");
    TP->command("drink brown beer");
    return 1;
}