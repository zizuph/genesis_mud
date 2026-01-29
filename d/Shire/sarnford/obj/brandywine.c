#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/drink";

int do_smell(string str);
int do_sip(string str);
int do_nurse(string str);
int do_drain(string str);

void
create_drink() 
{
    set_name(({"wine","brandy","brandywine","glass"}));
    set_pname(({"wines","brandies","brandywines","glasses"}));
    set_short("glass of brandywine");
    set_pshort("glasses of brandywine");
    set_long("This is a glass of distilled wine, most commonly known as " +
        "brandy. A faint, fruity aroma drifts up from the glass, almost as " +
        "if the brandy was encouraging you to smell it and take a sip. " +
        "Most people prefer to carefully nurse their brandy instead of " +
        "just draining it.\n");
    set_soft_amount(90);
    set_alco_amount(18);

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, F_VALUE_ALCO(18));
}

init()
{
    ::init();
    add_action("do_smell","smell");
    add_action("do_sip","sip");
    add_action("do_nurse","nurse");
    add_action("do_drain","drain");
}

int
do_smell(string str)
{
    notify_fail("Smell what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You carefully lift the glass of brandywine up to your " +
        "nose and inhale delicately. You detect a sweet, almost " +
        "fruity aroma mingled with the intense scent of alcohol.\n");
    SAYBB(" smells their glass of brandy in a delicate manner.");
    return 1;
}


int
do_sip(string str)
{
    notify_fail("Sip what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("You take a slow, careful sip of the brandywine, savouring the " +
        "rich fruity flavour which dances on your tongue and enjoying " +
        "the liquid warmth which spreads inside your body.\n");
    SAYBB(" lifts up their glass of brandywine to take a small sip.\n");
    return 1;
}

int
do_nurse(string str)
{
    notify_fail("Nurse what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You carefully nurse your brandy in a series of small, " +
        "flavourful sips before eventually finishing the entire glass.\n");
    SAYBB(" sips the last bit of their glass of brandywine.\n");
    TP->command("drink brandywine");
    return 1;
}

int
do_drain(string str)
{
    notify_fail("Drain what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("The inside of your body feels as if it is on fire as you " +
        "drink your entire glass of brandywine at once! You might " +
        "enjoy the brandy more if you were to nurse it instead of " +
        "draining it down like that.\n");
    SAYBB(" drains their glass of brandywine in one big gulp.\n");
    TP->command("drink brandywine");
    TP->command("choke");
    TP->command("cough desperately");
    return 1;
}