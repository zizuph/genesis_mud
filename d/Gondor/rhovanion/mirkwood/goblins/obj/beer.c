#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/drink";

int do_smell(string str);
int do_sip(string str);
int do_chug(string str);

void
create_drink() 
{
    set_name(({"beer"}));
    set_short("mug of murky beer");
    add_adj(({"murky"}));
    set_long("This mug is rather crudely made, and the beer it holds " +
        "appears to be even cruder. However, it is apparently quite " +
        "popular in the Chipped Mug tavern, where it was originally " +
        "purchased. Many patrons of that tavern are known to not only " +
        "sip their beers carefully, but to chug them down in one swift " +
        "moment!\n");
    set_soft_amount(90);
    set_alco_amount(12);

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, F_VALUE_ALCO(12));
}

init()
{
    ::init();
    add_action("do_smell","smell");
    add_action("do_sip","sip");
    add_action("do_chug","chug");
}

int
do_smell(string str)
{
    notify_fail("Smell what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You carefully sniff the murky beer and notice that it smells " +
        "just fine! You decide to take a quick swig and find it to be " +
        "both tasty and refreshing!\n");
    SAYBB(" smells their murky beer carefully before taking a taste.");
    return 1;
}


int
do_sip(string str)
{
    notify_fail("Sip what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("Casually you lift the murky beer up to your lips and take " +
        "a quick, refreshing sip.\n");
    SAYBB(" sips their murky beer casually.\n");
    return 1;
}

int
do_chug(string str)
{
    notify_fail("Chug what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Swinging the cup up to your mouth and tilting your head back " +
        "you quickly chug every last drop in the cup of murky beer.\n");
    SAYBB(" chugs down the last of their murky beer.\n");
    TP->command("drink murky beer");
    return 1;
}
