// file name:     ~/th_boots.c
// creator(s):    Zielia
// last update:
// purpose:       boots for maddy
// note:	copied bits from the custom shoes by Lilith.
// bug(s):
// to-do:
#pragma strict_types

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "zigg.h"

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/commands";
inherit "/lib/keep";

public static string color = one_of_list(({
    "black","brown","red","blue", "green","purple",
}));

public void
set_color(string str)
{
    remove_adj(color);
    color = str;
    add_adj(color);
    set_pshort("pairs of thigh-high "+ color +" leather boots");
    set_short("pair of thigh-high "+ color +" leather boots");
    set_long("These imposing boots have been crafted from "+
	"supple deerskin leather and dyed "+ color +". "+
	"Designed to make the legs look long and lean, these boots hug "+
	"the legs, sheathing them well past the knee. A tall, spiked "+
	"heel gives the wearer height and makes a bold statement. These "+
	"boots are laced from ankle to thigh along the back of the boot "+
	"with strong, thin leather laces which allow the sheath to be "+
	"adjusted along the total length of the leg for an optimal fit "+
	"as well as providing a tiny peek at the skin between the criss-"+
	"crossing laces. The stitching on these boots is of very fine "+
	"quality, indicating that diligent and careful effort went into "+
	"their crafting. The soles have been protected with a thin layer "+
	"of stiff leather. When wearing them, you can do 'bootadmire', "+
	"'bootoffer' and 'boottug'.\n");
}

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    config_wearable_item(A_FEET | A_LEGS, 2, 3, TO);
    set_name(({"boots", "boot", "shoes", "shoe", "stat::item"}));
    set_adj(({"leather", "thigh-high", "thigh", "high",
	"stilletto", "sybarun", "ziggurat"}));

    set_color(color);

    add_item("leather", "This leather comes from the tiny deer native to "+
	"the Sybarus Holm. It has been tanned to bring out the fine "+
	"grain, texture and suppleness of the skin.\n");
    add_item(({"stitching", "stitches"}), "They are good, regular stitches.\n");

    add_item(({"laces", "lacing", "lashings"}), "The laces are "+
	"a very important part of the boot because they help "+
	"hold the leg coverings snug around the leg and add an extra bit "+
	"of style and appeal by granting a small enticing glimpse of the "+
	"leg beneath.\n");
    add_item(({"sole", "soles" }), "The soles have been covered "+
	"with a thin layer of stiff leather so that they last longer.\n");
    add_item(({"heel", "heels", "spike", "spikes", }),
	"The heels are stilletto style spikes "+
	"that look both precarious and dangerous. They are nearly as long "+
	"as the sole of the foot, forcing the wearer to stand on tip-toe "+
	"and make the legs look firm, long and lean, making them well worth "+
	"the discomfort to some wearers.");

    add_prop(OBJ_I_VALUE, 1050);
    add_prop(OBJ_M_NO_SELL, "It is of purely sentimental value.\n");
}

public int
wear(object ob)
{
    if (TP != environment(TO))
	return 0;

    write("You slip your feet into your "+ short() +
        " and smooth the leather over your legs before snuggly lacing "+
	"the back.\n");

    say(QCTNAME(TP) +" slips "+ HIS(TP) +" feet into "+ HIS(TP) +" "+
        short() + " and smooths the leather over "+ HIS(TP) +
        " legs before snuggly lacing the back.\n");

    return 1;
}

public int
remove(object ob)
{
    if (TP != environment(TO))
	return 0;

    write("You deftly unlace your "+ short() +" and step out of them, "+
        "removing them with alluring precision.\n");

    say(QCTNAME(TP)+" deftly unlaces "+ HIS(TP) +" "+ short()+
	" and steps out of them, removing them with alluring precision.\n");

    return 1;
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
     wearable_item_leave_env(from, to);
}

public void
appraise_object(int num)
{
     ::appraise_object(num);
     appraise_wearable_item();
}

/*
 * Add/mask emotions to make them more fun!
 * click heels
 * admire shoes
 * tap toe
 */

public int
do_offer(string str)
{
    object *oblist;

    if (!query_worn())
        return 0;

    if (!strlen(str))
    {
        write("You gracefully and deliberately extend one foot in front "+
            "of you, silently offering to let someone lick your "+ short() +
	    ".\n");
	allbb(" gracefully and deliberately extend one foot in front of "+
	    HIM(TP)+ " silently offering to let someone lick "+ HIS(TP) +
	    " "+ short() +".");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
          notify_fail("Who do you want to admire your shoes?\n");
          return 0;
    }

    actor("You gracefully and deliberately extend one foot in front "+
	"of you, silently indicating to", oblist, " that "+
	HE(oblist[0]) +" can lick your "+ short() +".");
    all2act(" gracefully and deliberately extend one foot in front "+
	"of "+ HIM(TP) +" silently indicating to", oblist, " that "+
	HE(oblist[0]) +" should lick "+ HIS(TP) +" "+ short() +".");
    target(" gracefully and deliberately extend one foot in front "+
	"of "+ HIM(TP) +" silently indicating to you that you can "+
	"lick "+ HIS(TP) +" "+ short() +".", oblist);

    return 1;
}

public int
do_admire(string str)
{
    object *oblist;

    if (!query_worn())
        return 0;

    if (!strlen(str))
    {
        write("You turn your feet this way and that, admiring your "+
            "stylish new "+ short() +".\n");
	allbb(" turns "+ HIS(TP) +" foot this way and that, admiring "+
            HIS(TP) +" "+ short() +".");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ this_player });

    if (!sizeof(oblist))
    {
          notify_fail("Who do you want to admire your shoes?\n");
          return 0;
    }

    actor("You hold your foot aloft, directing", oblist, "'s attention "+
        "to your "+ short() +".");
    all2act(" holds "+ HIS(TP) +" foot out to", oblist, " so "+
        HE(oblist[0]) +" can admire "+ HIS(TP) +" "+ short()
        +".");
    target(" holds "+ HIS(TP) +" foot out toward you so you can "+
        "admire "+ HIS(TP) +" "+ short() +".", oblist);

    return 1;
}

public int
do_tap(string str)
{
    object *oblist;
    string *how, adverb, tmp;

    how = parse_adverb_with_space(str, "impatiently" , 0);
    adverb = how[1];

    if (!strlen(how[0]))
    {
        write("You" + adverb + " tap the toe of one of your thigh-high "+
	    color +" leather boots.\n");
        allbb("" + adverb + " taps the toe of one of "+ HIS(TP) +
           " thigh-high "+ color +" leather boots.", adverb);
        return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail(capitalize(query_verb()) + " [how] 'at' [who/what]?\n");
        return 0;
    }

    actor("You stare at", oblist, " and"+ adverb +" tap the toe of one of your "+
        "thigh-high "+ color +" leather boots.");
    all2actbb(" stares at", oblist, " and"+ adverb +" taps the toe of "+
        HIS(TP) +" thigh-high "+ color +" leather boots.", adverb);
    targetbb(" stares at you and"+ adverb + " taps the toe of one of "+HIS(TP) +
        " thigh-high "+ color +" leather boots.", oblist, adverb);
    return 1;
}

public int
do_tug(string str)
{
    string *how, adverb;

    if (!query_worn())
        return 0;

    how = parse_adverb_with_space(str, "carefully", 0);
    adverb = how[1];

    write("You give the tops of your "+ short() +
	" a good tug and"+ adverb +" tighten the "+
	"laces at the back.\n");
    allbb(" gives the tops of "+ HIS(TP) +" "+
	short() +" a good tug and then"+ adverb +
	" tightens the laces at the back.");

    return 1;

}

public int
kick(string str)
{
    object *oblist;
    string *how;

    how = parse_adverb_with_space(str, "fanatically", 1);

    oblist = parse_this(how[0], "[the] %i",
        ACTION_CONTACT | ACTION_MACTIVITY | ACTION_OFFENSIVE);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Kick whom/what [how]?\n");
        return 0;
    }

    actor("You kick", oblist, how[1] + " with the toe of your thigh-high "+
	color +" leather boot.");
    all2act(" kicks", oblist, how[1] + " with the toe of "+ HIS(TP) +
	" thigh-high "+ color +" leather boot.", how[1],
        ACTION_CONTACT | ACTION_MACTIVITY | ACTION_OFFENSIVE);
    target(" kicks you" + how[1] + " with the toe of "+ HIS(TP) +
	" thigh-high "+ color +" leather boot.", oblist, how[1],
        ACTION_CONTACT | ACTION_MACTIVITY | ACTION_OFFENSIVE);
    return 1;
}

public void
init(void)
{
   ::init();

   add_action(do_admire,"bootadmire");
   add_action(do_offer, "bootoffer");
   add_action(do_tap,   "tap");
   add_action(do_tug,   "boottug");
   add_action(kick,     "kick");
}

public string
query_recover(void)
{
    return MASTER + ":" + query_keep_recover() +"#!"+ color +"!#";
}

public void
init_recover(string arg)
{
    string rcolor;

    init_keep_recover(arg);
    sscanf(arg, "%s#!%s!#%s", arg, rcolor, arg);
    set_color(rcolor);

    will_not_recover = (random(100) < RECOVERY_LOST);
}

