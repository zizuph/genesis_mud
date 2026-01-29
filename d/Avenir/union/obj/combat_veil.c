#pragma strict_types
// creator(s):  Lilith Nov 96
// last update: 07-Jan-97
// purpose:     Concealment & mystery
// note:        There is a shadow associated with this file, so that
//              players don't lose their adjectives when dying, etc.
/* Revisions:
 * 	Cirion, Jan 1997: Some very minor modifications
 * 	Cirion, Mar 1997: Added vtear emote to destroy the veil.
 * 	Lilith, Apr 1997: Added a buy-check for USW's only.
 * 			  Added the vtug emote Rage suggested.
 *	Lilith, Jul 1998: Modified file to use wearable_item.
 *	Lilith, May 2004: Made it so anyone who isn't union and tried to wear
 *			  the scarf destroys it.
 *	Lilith, Jun 2004: Recode of how scarf is handled. It is now bestowed
 *			  at Naming, and is cloned via shadow.
 *	Lucius, Apr 2005: Changed the Veil checking methods.
 *	Lucius, Apr 2009: Changed shadow handling + small tweaks
 *	Lucius, Aug 2017: Cleanups
 *  Zizuph, Jun 2021: Fix logic on vtug notify_fail.
 *  Lilith, Feb 2022: Added "/lib/help" support
 */
inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/commands";
inherit "/lib/keep";
inherit "/lib/help";

#include <macros.h>
#include <wa_types.h>
#include <language.h>
#include <stdproperties.h>

#include "../defs.h"

#define VEIL_SUBLOC	"_veil_subloc"
#define VEIL_SHADOW	(OBJ + "veil_shad")
#define IS_VEILED(x)	((x)->query_union_veil())

#define WEAR_CHECK if (!query_worn()) { \
    NF("You should be veiled, first.\n"); return 0; }
#define VEIL_CHECK if (!objectp(IS_VEILED(TP))) { \
    NF("You should be veiled, first.\n"); return 0; }
#define HELP_DIR   "/d/Avenir/union/help/su/"

public int vtear(string str);


/******* veiling/shadowing, wear and remove functions ***************/
public int
veil_me(string str)
{
    notify_fail("Do what? Veil yourself?\n");
    if (!strlen(str))
	return 0;

    if ((str != "me") && (str != "myself") && (str != "face"))
	return 0;

    if (ENV(TO) != TP)
    {
	notify_fail("You do not have it.\n");
	return 0;
    }

    WEAR_CHECK

    if (!IS_MEMBER(TP))
    {
	notify_fail("You attempt to veil yourself with the "+
	  short() +" but do a sloppy job and the cloth "+
	  "falls back onto your shoulder.\n");
	return 0;
    }

    if (objectp(IS_VEILED(TP)))
    {
	notify_fail("You have already veiled yourself.\n");
	return 0;
    }

    write("You raise the edge of the scarf so that it covers your "+
      "nose and mouth, shrouding your face in shadow.\n");

    say(QCTNAME(TP) +" raises the edge of the "+ short() +
      " up to "+ HIS(TP) + " eyes, shrouding "+ HIS(TP) +" face in "+
      "shadow.\n");

    object veil_shadow = clone_object(VEIL_SHADOW);
    veil_shadow->shadow_me(TP);

    return 1;
}

public int
unveil(string str)
{
    notify_fail("Do what? Unveil yourself?\n");
    if (!strlen(str))
	return 0;

    if ((str != "me") && (str != "myself") && (str != "face"))
	return 0;

    if (ENV(TO) != TP)
    {
	notify_fail("You do not have it.\n");
	return 0;
    }

    if (!objectp(IS_VEILED(TP)))
    {
	notify_fail("You are not currently veiled.\n");
	return 0;
    }

    write("You lower the "+ short() +", exposing your features.\n");
    say(QCTNAME(TP) +" lowers "+HIS(TP)+" "+ short() +", "+
	"revealing an expressionless face and gleaming eyes.\n");

    TP->remove_union_veil();
    return 1;
}

public mixed
wear(object ob)
{
    object tp = environment();

    if ((tp != TP) || (ob != TO))
	return -1;

    /* This is unlikely ever to happen, but we'll keep it here. */
    if (!IS_MEMBER(tp))
    {
	tp->heal_hp(-(tp->query_hp() / 10));
	tp->catch_tell("You drape the "+ short() +" over your "+
	  "head and as you try to loop it around your neck "+
	  "it becomes tangled and starts to strangle you!\n"+
	  "In a panic, you fight to extricate yourself from "+
	  "the "+ short() +" and injure yourself in the "+
	  "process.");
	tell_room(environment(tp), QCTNAME(tp) +" drapes the " +
	  short() +" over "+ HIS(TP) +" head and then suddenly seems "+
	  "to be fighting for "+ HIS(TP) +" life!\n", tp);

	vtear("");
	return "";
    }

    if (member_array(VEIL_SUBLOC, tp->query_sublocs()) > -1)
	return "You are already wearing a head scarf.\n";

    /* Successful wear */
    tp->add_subloc(VEIL_SUBLOC, this_object());
    tp->catch_tell("You drape the "+ short() +" over your "+
      "head and loop it around your neck.\n");
    tell_room(environment(tp), QCTNAME(tp) + " drapes the " +
      short() +" over "+ HIS(TP) +" head and loops "+
      "it around "+ HIS(TP) +" neck.\n", tp);

    return 1;
}

public mixed
remove(object ob)
{
    if ((ob != TO) && (TP != query_worn()))
	return -1;

    TP->remove_subloc(VEIL_SUBLOC);
    TP->remove_union_veil();

    return 0;
}

public string
show_subloc(string subloc, object on, object for_obj)
{
    if (subloc == VEIL_SUBLOC)
    {
	if (for_obj != on)
	{
	    return CAP(HE(on)) +" is wearing " +
		LANG_ADDART(short()) +" draped over "+
		HIS(on) +" head and looped around "+
		HIS(on) +" neck.\n";
	}
	else
	{
	    return "You are wearing " + LANG_ADDART(short()) +
		" draped over your head and looped around"+
		" your neck.\n";
	}
    }
}

/********************** associated emotes ********************/
public int
vflicker(string str)
{
    object *oblist;

    WEAR_CHECK
    VEIL_CHECK

    if (!strlen(str))
    {
	write("Veiled and ready for combat, you look about you with "+
	  "flickering eyes full of menace and distrust.\n");
	allbb("'s eyes are flickering behind "+ HIS(TP) +" shadowy "+
	  "veil.\n");
	return 1;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
    {
	notify_fail("Vflicker at who?\n");
	return 0;
    }

    actor("Veiled and ready for combat, you look at", oblist, " with "+
	"flickering eyes full of malevolence and suspicion.\n");
    targetbb(" looks at you from behind "+ HIS(TP) +" "+ short() +", "+
	HIS(TP) +" eyes flickering with malevolence and suspicion.\n",
	oblist);

    return 1;
}

public int
vgleam(string str)
{
    WEAR_CHECK

    if (strlen(str))
    {
	notify_fail("You cannot gleam "+ str +".\n");
	return 0;
    }

    write("Your eyes gleam as you anticipate the battle ahead.\n");
    allbb("'s eyes seem to gleam brightly as "+ HE(TP) +
	" anticipates the battle ahead.\n");

    return 1;
}

public int
vkill(string str)
{
    object *oblist;

    WEAR_CHECK
    VEIL_CHECK

    if (!strlen(str))
    {
	notify_fail("You want to vkill whom?\n");
	return 0;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
    {
	notify_fail("Vkill who?\n");
	return 0;
    }

    actor("You briefly lower the edge of your "+ short() +" so that",
	oblist, " may look upon a thing of beauty before dying at "+
	"your hands.");
    targetbb(" briefly lowers the edge of "+ HIS(TP) +" "+ short() +
	" so that you may see a thing of beauty before you die.",
	oblist);

    TP->command("$kill " + str);
    return 1;
}

public int
vlaugh(string str)
{
    string *how;
    object *oblist;

    WEAR_CHECK
    VEIL_CHECK

    how = parse_adverb_with_space(str, "softly", 0);

    if (!strlen(str))
    {
	write("You laugh"+ how[1] +" within the folds of your "+
	    short() +".\n");
	allbb(" laughs"+ how[1] +" from within the folds of "+ HIS(TP) +
	    " "+ short() +".");

	return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("Laugh [how] at whom?\n");
	return 0;
    }

    actor("You laugh"+ how[1] +" at", oblist, " from within your "+
	short() +".\n");
    all2actbb(" laughs"+ how[1] +" at", oblist, " from within "+ HIS(TP) +
	" "+ short() +".\n");
    targetbb(" laughs"+ how[1] +" at you from within "+ HIS(TP) + " " +
	short() +".\n", oblist);

    return 1;
}

public int
vnarrow(string str)
{
    string *how;
    object *oblist;

    WEAR_CHECK
    VEIL_CHECK

    how = parse_adverb_with_space(str, "dangerously", 0);

    if (!strlen(how[0]))
    {
	write("You narrow your eyes"+ how[1] +" above the "+
	    short() +" shrouding your face.\n");
	allbb(" narrows "+ HIS(TP) +" eyes"+ how[1] +" above the "+
	    short() +" shrouding "+ HIS(TP) +" face.\n");

	return 1;
    }

    oblist = parse_this(how[0], " [eyes] [at] [the] %l");
    if (!sizeof(oblist))
    {
	notify_fail("Narrow your eyes [how] at whom?\n");
	return 0;
    }

    actor("You narrow your eyes" + how[1] + " at", oblist, " over "+
	"the edge of your "+ short() +", alert and ready for any trouble.");
    all2actbb(" narrows "+ HIS(TP) +" eyes"+ how[1] +" at", oblist,
	" over the edge of "+ HIS(TP) +" "+ short() +", somehow appearing "+
	"more alert and menacing.");
    targetbb(" narrows "+ HIS(TP) +" eyes"+ how[1] +" at you over "+
	"the edge of "+ HIS(TP) +" "+ short() +", somehow appearing "+
	"more alert and menacing.", oblist);

    return 1;
}

public int
do_shred(void)
{
    object shred = clone_object("/std/object");
    shred->set_name(({"shred","cloth","shreads"}));
    shred->set_adj(({"shred","shredded","piece","black","web"}));
    shred->set_short("piece of shredded black cloth");
    shred->set_pshort("pieces of shredded black cloth");
    shred->set_long("It is a piece of finely crafted black webcloth, "+
	"interwoven with tiny strands of silver wire. It has been "+
	"torn to shreds, making its purpose indeterminable.\n");

    shred->add_prop(OBJ_I_WEIGHT, 250);
    shred->add_prop(OBJ_I_VOLUME, 500);
    shred->add_prop(OBJ_I_VALUE,  25);
    shred->move(ENV(TO), 1);

    set_alarm(0.5, 0.0, remove_object);
    return 1;
}

public int
vtear(string str)
{
    if (query_worn() == TP)
    {
	NF("You would need to remove the veil before destroying it.\n");
	return 0;
    }

    if (TP != ENV(TO))
    {
	NF("You would need to be holding it.\n");
	return 0;
    }

    if (living(ENV(TO)))
	ENV(TO)->catch_tell("You tear " + LANG_THESHORT(TO) + " into shreads.\n");
    else
	tell_room(ENV(TO), "The black webcloth scarf falls apart.\n");

    do_shred();
    return 1;
}

public int
vtug(string str)
{
    object *oblist;

    WEAR_CHECK
    VEIL_CHECK

    if (str != "veil" && str != "cowl" && str != "scarf")
    {
	notify_fail("You want to vtug what?\n");
	return 0;
    }

    if (ENV(TP)->query_domain() == "Avenir")
    {
	write("You tug the "+ short() +" a little closer, while "+
	    "glancing in the direction of the Source.\n");
	allbb(" glances upward and tugs "+ HIS(TP) +" "+ short() +" a "+
	    "little closer about "+ HIS(TP) +" face.");
    }
    else if (ENV(TP)->query_prop(ROOM_I_INSIDE))
    {
	write("You tug on the "+ short() +", adjusting the way "+
	    "it is draped about your face.\n");
	allbb(" tugs on "+ HIS(TP) +" "+ short() +" adjusting the "+
	    "way it is draped over "+ HIS(TP) +" head.\n");
    }
    else
    {
	write("Longing for the gentle illumination of the Source,"+
	    " you tug your "+ short() +" closer about your face, "+
	    "to veil yourself from the unnatural brightness of "+
	    "the sun.\n");
	allbb(" tugs the "+ short() +" closer about "+ HIS(TP) +
	    " face.");
    }
    return 1;
}

public int
vwatch(string str)
{
    WEAR_CHECK
    VEIL_CHECK

    if (strlen(str))
    {
	notify_fail("You cannot do <vshadow "+ str +">.\n");
	return 0;
    }

    write("You watch silently from behind the shadowed folds of your "+
	short() +".\n");
    say("You can feel "+ QNAME(TP) +" watching silently from behind "+
	"the shadowed folds of "+ HIS(TP) +" "+ short() +".\n");

    return 1;
}

public int
vlower(string str)
{
    object *oblist;
    string g = "beauty";

    WEAR_CHECK
    VEIL_CHECK

    if (TP->query_gender() == G_MALE)
	g = "masculine beauty";

    if (!strlen(str))
    {
	write("You lower the edge of your "+ short() +
	    ", briefly exposing the "+ g +" of "+
	    "your face.\n");
	allbb(" lowers the edge of "+ HIS(TP) +" "+ short() +
	    ", briefly exposing the "+ g +" of "+ HIS(TP) +
	    " face to your gaze.");

	return 1;
    }

    oblist = parse_this(str, "[the] %l");
    oblist -= ({ TP });

    if (!sizeof(oblist))
    {
	notify_fail("Vlower who?\n");
	return 0;
    }

    actor("You briefly lower the edge of your "+ short() +" so that",
	oblist, " may look upon your "+ g +".");
    all2actbb(" lowers the edge of "+ HIS(TP) +" "+ short() +
	" at", oblist, ", briefly exposing "+ HIS(TP) + " "+ g +".");
    targetbb(" briefly lowers the edge of "+ HIS(TP) +" "+ short() +
	", exposing to your gaze the "+ g +" of "+ HIS(TP) +
	" face and the flames of divine passion in "+ HIS(TP) +
	" eyes.", oblist);

    return 1;
}

/*************** Creation and initialization ********************/
public void
create_object(void)
{
    reset_euid();
    config_wearable_item(A_HEAD, 1, 15, this_object());

    set_name(({"veil", "_union_scarf"}));
    add_name(({"scarf", "shroud", "cowl"}));
    set_adj(({"black", "webcloth", "combat", "union"}));
    add_adj("unworn");
    set_short("@@short_desc@@");
    set_long("This is a length of translucent black webcloth inter"+
	"woven with thin strands of silver wire. It is worn draped "+
	"over the head and looped around the neck, and can be raised "+
	"to cover the face like a veil, shrouding it in shadow. To "+
	"learn more about what you can do when wearing this combat "+
	"veil, use <help veil>.\n");

    add_cmd_item(({"veil", "scarf", "cowl" }), "help",
      "    You may conceal your features by using this scarf to\n"+
      "    <veil myself>. You may also <unveil myself>. Other,\n"+
      "    similar syntax will also create the desired effect.\n\n"+
      "    There are some emotes associated with this scarf:\n"+
      "        <vflicker> and <vflicker at [someone]> : Your eyes flicker.\n"+
      "        <vgleam> : Your eyes gleam in anticipation of the battle ahead.\n"+
      "        <vkill [someone]> : Reveal yourself before attacking.\n"+
      "        <vlaugh> and <vlaugh at [someone]> : Soft laughter.\n"+
      "        <vlower> and <vlower [someone]> : Reveal yourself briefly.\n"+
      "        <vnarrow> and <vnarrow at [someone]> : Narrow eyes over veil.\n"+
      "        <vwatch> : You watch silently from the shadows.\n"+
      "        <vtear> : Destroy the veil.\n"+
      "        <vtug> : You tug it more closely about your face.\n"+
      "\n");

    set_keep(1);
    set_looseness(15);
    set_layers(2);

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE,  100);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_BUY, "The cowl is not available for sale.\n");
    add_prop(OBJ_M_NO_SELL, "You cannot bear to part with it.\n");
    add_prop(OBJ_M_NO_STEAL, "Steal what?\n");

//  Putting this here means these help files are only accessible once
//  someone has passed the Novice stage and has been named.	
//	add_help_topic("sway",  HELP_DIR +"sway.help"); 
	set_help_dir(HELP_DIR);
	set_help_category("su");
}

public string
short_desc(void)
{
    if (objectp(IS_VEILED(TP)))
	return "black webcloth cowl";
    else
	return "black webcloth scarf";
}

public void
init(void)
{
    ::init();

    if (!IS_MEMBER(TP))
	return;

    add_action(veil_me, "veil");
    add_action(unveil,  "unveil");
    add_action(vtear,   "vtear");

    add_action(vnarrow, "vnarrow");
    add_action(vkill,   "vkill");
    add_action(vlaugh,  "vlaugh");
    add_action(vflicker,"vflicker");
    add_action(vgleam,  "vgleam");
    add_action(vtug,    "vtug");
    add_action(vwatch,  "vwatch");
    add_action(vlower,	"vlower");
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    wearable_item_leave_env(from, to);

    from->remove_subloc(VEIL_SUBLOC);
    from->remove_union_veil();
}

public void
check(void)
{
    object *stuff, who = ENV(TO);

    stuff = filter(all_inventory(who), &->id("_union_scarf"));

    if (sizeof(stuff) > 1)
	vtear("");
    /* not Named yet */
    else if (who->query_skill(OCC_LEVEL) < NORMAL)
	vtear("");
    /* somewhat redundant, but it is possible a former
     * member might have the skills set, so...
     */
    else if (!IS_MEMBER(who))
	vtear("");
}

/* After everything that happened with this darned scarf
 * I want to make sure no one but a union member has it.
 */
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!living(to))
	set_alarm(1.0, 0.0, do_shred);
    else
	set_alarm(2.0, 0.0, check);
}
