// -*-C++-*-
// file name: 	  /d/Avenir/common/village/obj/custom_shoes.c
// creator(s):	  Lilith Jan 2004
// last update:
// 		Lucius Oct 2008: Massive cleanup / rewrite.
// 		Lucius Apr 2018: Added some options
//
#pragma strict_types

#include "custom.h"
inherit CUSTOM_BASE;

mapping style_desc = ([
   "sandals"   : ({ "sandal",
	"They are the simplest type of footwear, "+
	"consisting entirely of thin soles fastened to the "+
	"feet with slender straps."
   }),
   "shoes"     : ({ "shoe",
	"They are a snug fit for the feet, designed "+
	"to cover them entirely while leaving the ankles bare."
   }),
   "slippers"  : ({ "slipper",
	"They cover the toes, but only part of "+
	"the instep, leaving the upper foot and ankle bare. "+
	"They are a comfortably loose fit, designed more for "+
	"leisure than for long walks."
   }),
   "mules"     : ({ "mule",
	"They are a form of slipper that covers "+
	"the toes and insteps, but leaves the heels bare. "+
	"While very comfortable, they are designed for loung"+
	"ing, not long walks."
   }),
   "moccasins" : ({ "moccasin",
	"These are perhaps the most comfortable "+
	"and practical shoes available. The portion covering "+
	"the feet resembles a slipper that covers the heel and "+
	"lower leg. The laces of these mocassins make the "+
	"fit infinately adjustable."
   }),
   "clogs"     : ({ "clog",
	"These heavy shoes are very appealing to "+
	"the eye, being curved over the instep and around the "+
	"toes. There is no covering for the heel, and the base "+
	"is made of wood three-fingers thick."
   }),
   "boots"     : ({ "boot",
	"These boots are a protective fashion "+
	"statement. They cover the foot and ankle, rising "+
	"half-way up the lower leg and ending in a folded "+
	"cuff."
   }),
   "loafers"   : ({ "loafer",
	"These are low step-in shoes with an "+
	"upper resembling a moccasin but with a broad, flat "+
	"heel."
   }),
   "heels"     : ({ "heel",
	"These are step-in, open-toed shoes "+
	"with extravagantly high heels."
   }),
]);

private string
long_desc(void)
{
    return "These "+ desc + style +" have been crafted from "+
	fabric_type[fabric][1] +" and dyed "+ colour +". "+
	style_desc[style][1] +" The stitching is of very fine "+
	"quality, indicating that considerable effort went "+
	"into the crafting of these "+ style +". The soles "+
	"have been protected with a thin layer of stiff leather. "+
	"When wearing them, you can do 'shoeadmire', "+
	"'shoeclick', and 'shoetap'.\n";
}

private string
short_desc(void)
{
    return "pair of "+ colour +" "+ fabric +" "+ 
        (strlen(desc) ? (desc + " ") : desc) + style;
}

public void
create_tailored(void)
{
    ::create_tailored();
    set_adj(({ colour, fabric }));
    add_name(({ style, style_desc[style][1] }));

    if (strlen(desc))
    {
	  add_adj(desc);
    }

    switch (style)
    {
    case "sandals":
	add_item(({"straps", "strap"}), "The straps on the sandals are "+
	    "just wide enough to fasten the shoes without chafing or "+
	    "binding the feet unnecessarily.\n");
	break;
    case "boots":
	add_item(({"cuff", "cuffs"}), "These boots fold down at the top, "+
	    "forming a nice wide cuff in a slightly darker shade of "+
	    colour +".\n");
	break;
    case "moccasins":
	add_item(({"laces", "lacing", "lashings"}), "The laces are "+
	    "a very important part of the shoe because they help "+
	    "hold the leg coverings closed and snug against the "+
	    "lower leg.\n");
	break;
    }
}

public void
create_object(void)
{
    ::create_object();
    config_wearable_item(A_FEET, 1, 15, this_object());
    set_name("shoes");

    add_item(({"sole", "soles" }), "The soles have been covered "+
       "with a thin layer of stiff leather "+
       "so that they last longer.\n");
}

/*
 * Add/mask emotions to make them more fun!
 * click heels
 * admire shoes
 * tap toe
 */
public int
do_click(string str)
{
    if (!query_worn())
    {
        notify_fail("You need to be wearing the "+ short() +" first.\n");;
	return 0;
    }

    if (strlen(str))
	return notify_fail("No argument is necessary.\n");

    write("You click the heels of your "+ short() +
	" together.\n");
    allbb(" clicks the heels of "+ POSSESS(TP) +
	" "+ short() +" together.");

    return 1;
}

public int
do_admire(string str)
{
    if (!query_worn())
    {
        notify_fail("You need to be wearing the "+ short() +" first.\n");;
	return 0;
    }

    if (!strlen(str))
    {
        write("You turn your feet this way and that, admiring your "+
	    "stylish new "+ short() +".\n");
	allbb(" turns "+ POSSESS(TP) +" foot this way and that, admiring "+
	    POSSESS(TP) +" "+ short() +".");

	return 1;
    }

    object *oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
	  notify_fail("Who do you want to admire your shoes?\n");
	  return 0;
    }

    actor("You hold your foot aloft, directing", oblist, "'s attention "+
        "to your "+ short() +".");
    all2actbb(" holds "+ POSSESS(TP) +" foot out to", oblist, " so "+
        PRONOUN(oblist[0]) +" can admire "+ POSSESS(TP) +" "+ short()
        +".");
    targetbb(" holds "+ POSSESS(TP) +" foot out toward you so you can "+
        "admire "+ POSSESS(TP) +" "+ short() +".", oblist);

    return 1;
}

public int
do_tap(string str)
{
    if (!query_worn())
    {
        notify_fail("You need to be wearing the "+ short() +" first.\n");;
	return 0;
    }

    string *how = parse_adverb_with_space(str, "briskly" , 0);

    if (!strlen(how[0]))
    {
        write("You" + how[1] + " tap the toe of your "+ short() +".\n");
        allbb(how[1] + " taps the toe of "+ POSSESS(TP) +" "+
	    short()+".", how[1]);
        return 1;
    }

    object *oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail(capitalize(query_verb()) + " [how] 'at' [who/what]?\n");
        return 0;
    }

    actor("You stare at", oblist, " and"+ how[1] +" tap the toe of your "+
        short() +".");
    target(" stares at you and"+ how[1] + " taps the toe of "+POSSESS(TP)
        +" "+ short() +".", oblist, how[1]);
    all2act(" stares at", oblist, " and"+ how[1] +" taps the toe of "+
        POSSESS(TP) +" "+ short() +".", how[1]);

    return 1;
}

public void
init(void)
{
   ::init();

   if (environment() != this_player())
       return;

   add_action(do_admire,"shoeadmire");
   add_action(do_click, "shoeclick");
   add_action(do_tap,   "shoetap");
}
