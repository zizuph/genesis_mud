#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/food";

int do_nibble(string str);
int do_dip(string str);
int do_stir(string str);
int do_toss(string str);

void
create_food() 
{
    set_name(({"ears"}));
    add_name(({"ears", "bowl"}));
    set_pname(({"bowls of ears", "bowls"}));
    set_short("bowl of fried elf ears");
    set_pshort("bowls of fried elf ears");
    set_adj(({"elf", "fried", "of", "bowl", "bowls"}));
    set_long("This is a bowl of fried elven ears. It comes with a " +
        "small jar of sauce so you can dip the ears for an extra tasty " +
        "treat. The ears themselves look perfect for a quick nibble " +
        "anytime you are feeling a bit hungry.\n");
    add_item(({"sauce", "jar"}),
        "This small jar seems to be a sauce made of elf puree, lightly " +
        "spiced and extra chunky. You might use one of your ears to " +
        "stir it up before dipping.\n");
    set_amount(375);
    add_prop(OBJ_I_WEIGHT, 400);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 195);
}

init()
{
    ::init();
    add_action("do_nibble","nibble");
    add_action("do_dip","dip");
    add_action("do_stir","stir");
    add_action("do_toss","toss");
}


int
do_nibble(string str)
{
    notify_fail("Nibble on what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You reach into the bowl and pull out one of your fried elf ears " +
    "to snack on. You feel rather content as you happily nibble on the " +
    "crispy treat.\n");
    SAYBB(" happily nibbles on a fried elf ear.\n");
    return 1;
}

int
do_dip(string str)
{
    notify_fail("Dip what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("This jar of elf puree looks so appetizing, you cannot resist " +
        "sneaking out a fried elf ear from your bowl and dipping " +
        "it in the jar for a tasty snack.\n");
    SAYBB(" licks their lips as they dip an elf ear into their jar " +
        "of sauce.\n");
    return 1;
}

int
do_stir(string str)
{
    notify_fail("stir what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("Noticing that your jar of sauce looks a little extra chunky " +
        "today, you decide to use one of the elf ears to stir it up " +
        "a little before taking a quick bite.\n\n" +
        "MMMMMMMMMMMmmmmmmmmmmmmmm  CHUNKY!\n");
    SAYBB(" absentmindedly stirs a jar of sauce with one of their " +
        "fried elf ears.\n");
    return 1;
}


int
do_toss(string str)
{
    notify_fail("toss what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You grab a fried elf ear from your bowl and toss it " +
        "up into the air before catching it with your open mouth.\n");
    SAYBB(" casually tosses a fried elf ear up into the air and "+
        "catches it in their mouth.\n");
    TP->command("grin evil");
    return 1;
}