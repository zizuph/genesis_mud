#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/rhovanion/mirkwood/defs.h"

inherit "/std/drink";

int do_smell(string str);
int do_sip(string str);
int do_taste(string str);
int do_stir(string str);
int do_finish(string str);

void
create_drink() 
{
	set_name("tea");
    set_pname("teas");
    set_short("cup of herbal tea");
    set_pshort("cups of herbal tea");
    set_adj(({"cup", "herbal"}));
    set_long("This is a hot cup of herbal tea. Every time you stir the " +
        "tea, a pungent aroma wafts up into the air, almost begging you " +
        "to take a sip before you finish the entire cup.\n");
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
    add_action("do_stir","stir");
    add_action("do_taste","taste");
    add_action("do_finish","finish");
}

int
do_smell(string str)
{
    notify_fail("Smell what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You close your eyes and inhale the pungent aroma of herbs " +
        "which waft up from your cup of tea. The scent is almost " +
        "intoxicating, it feels as if it is cleansing your soul.\n");
    SAYBB(" gently closes their eyes and calmly inhales the " +
        "pungent aromas which curl up from their cup of tea.");
    return 1;
}


int
do_sip(string str)
{
    notify_fail("Sip what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0;

    write("You take a slow, careful sip of the herbal tea, savouring " +
        "the rich flavour as its warmth spreads through your body. " +
        "A feeling of peaceful contentment seems to spread through " +
        "you as a result.\n");
    SAYBB(" lifts up their hot cup of tea to take a small sip.\n");
    return 1;
}

int
do_stir(string str)
{
    notify_fail("Stir what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You take up your spoon and gently stir some honey " +
        "into your herbal tea to sweeten it up slightly.\n");
    SAYBB(" slowly stirs some honey into their cup of tea.\n");
    return 1;
}

int
do_taste(string str)
{
    notify_fail("Taste what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You take a slow, careful sip of the herbal tea, savouring " +
        "the rich flavour as its warmth spreads through your body. " +
        "A feeling of peaceful contentment seems to spread through " +
        "you as a result.\n");
    SAYBB(" lifts up their hot cup of tea to take a small sip.\n");
    return 1;
}

int
do_finish(string str)
{
    notify_fail("Finish what?\n");
    if (!str || !strlen(str)) return 0;

    if (!id(str)) return 0; 

    write("You lift the cup of tea to your lips, pausing only briefly " +
        "to enjoy the wonderful aroma, before slowly finishing off " +
        "the cup of tea. A unique sensation of calming relaxation " +
        "spread through your body and mind, putting you at peace " +
        "with the world.\n");
    SAYBB(" raises a cup of herbal tea to their lips, drinking it down " +
        "with great satisfaction.\n");
    TP->command("drink tea");
    TP->command("smile contentedly");
    return 1;
}