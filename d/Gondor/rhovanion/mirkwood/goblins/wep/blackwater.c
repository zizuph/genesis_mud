#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/drink";

int do_smell(string str);
int do_sip(string str);
int do_taste(string str);
int do_drain(string str);

void
create_drink() 
{
    set_name(({"alcohol"}));
    add_name(({"blackwater"}));
    set_short("pint of blackwater");
    set_pshort("pints of blackwater");
    set_long("This is roughly a pint of a strong-smelling, alcoholic drink " +
        "that the Chipped Mug tavern calls 'blackwater'. You might want " +
        "to take a sip first, or even just a tiny taste, before you " +
        "try to drain it down like many of the local goblins of Hargnak " +
        "seem to do.\n");
    set_soft_amount(90);
    set_alco_amount(20);

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, F_VALUE_ALCO(20));
}

init()
{
    ::init();
    add_action("do_smell","smell");
    add_action("do_sip","sip");
    add_action("do_taste","taste");
    add_action("do_drain","drain");
}

int
do_smell(string str)
{
    notify_fail("Smell what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You take a cautious sniff of the Blackwater and find that " +
        "the alcohol is so strong it actually stings your eyes.\n");
    SAYBB(" appears to be in some discomfort.");
    return 1;
}


int
do_sip(string str)
{
    notify_fail("Sip what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("Raising the Blackwater to your lips, you take a slow sip " +
        "and resist the urge to cough as liquid fire pours down your " +
        "throat and rumbling inside your stomach.\n");
    SAYBB(" almost seems to choke as they take a sip of Blackwater.\n");
    return 1;
}

int
do_taste(string str)
{
    notify_fail("Taste what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You take just a small taste of the pint of blackwater, and find " +
        "that it is probably best drunk in very small doses.\n");
    SAYBB(" takes a small taste of Blackwater.\n");
    return 1;
}

int
do_drain(string str)
{
    notify_fail("Drain what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Your entire body is on fire and your head is swimming! Draining " +
        "the Blackwater in one big gulp seems to have caused you to " +
        "black out for a moment, as you cannot even remember the act " +
        "of drinking it! Smiling foolishly to yourself, you privately " +
        "admit that even with the pain, that was kind of fun!\n");
    SAYBB(" foolishly drains a pint of Blackwater in one big gulp.\n");
    TP->command("drink blackwater");
    TP->command("choke");
    TP->command("cough desperately");
    return 1;
}