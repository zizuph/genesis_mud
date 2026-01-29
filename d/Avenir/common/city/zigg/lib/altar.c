// file name:   /d/Avenir/inherit/altar.c
// creator(s):  Lilith, March '97
// revision(s): Lucius, July 2006:
// 		  Cleaned up the code, added support to
// 		  assign multiple gods (two only). Also, removed the
// 		  reset_object and reset_altar bits, since nothing used
// 		  them and they activate an alarm.
// purpose:     Standard inheritable object for altars to Sybarite Gods
// note:        For working example, see /holm/obj/b_altar.c
//          Special offerings:
//              Modified the function do_offer() to check for the
//              prop SPECIAL_OFFERING in offered objects. If true
//              the function altar_special(object altar) is called
//              in the offered object.
//          Resetting:
//              Put your reset code into reset_object()
//              This will activate the reset alarm. You can create
//              a seperate reset_altar and call it manually upon other
//              criteria if you wish, but it will not be alarmed.
//          Errata:
//              This is sperated from /d/Avenir/inherit/altar.c as the
//              code is not directly compatible. Some soul sometime may
//              update the altars in the future to use this should they
//              see fit to do so.
// bug(s):

#pragma strict_types

inherit  "/std/object";

#include "/d/Avenir/include/deities.h"   /* Altar & diety-related defines */
#include "/d/Avenir/include/relation.h"  /* Sybarite status defines */

#include <composite.h>
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#define COMP_OR(wl)	COMPOSITE_WORDS_WITH(wl, "or")

/* Variables */
public static int hour,      /* The number of the Hour 			    */
		  offer_max, /* The maximum number of offerings at one time */
		  offer_num; /* The current number of offerings		    */

public static string  altar_name,   /* The unique name of the altar	    */
		      altar_short,  /* The base short description	    */
		      short_desc,   /* The modified short description	    */
		      id_long,      /* The long desc for identified altar   */
		      unid_long;    /* The long desc for unidentified altar */

public static string *bless_cmds,   /* Commands to bless/sanctify the altar */
		     *defile_cmds,  /* Commands used to defile the altar    */
		     *repair_cmds,  /* Commands used to repair the altar    */
		     *destroy_cmds, /* Commands used to destroy the altar   */
		     *offer_cmds,   /* Commands to make offerings at altar  */
		     *pray_cmds;    /* Commands to pray or worship at altar */

public static string *oprop,   /* The name(s) of acceptible offerings props */
		     *deities, /* The name(s) of the god(s) of the altar    */
		     *offer_shorts,  /* Short descs of offerings	    */
		     *offer_bloody;  /* Short descs of blood offerings	    */


/*
 * Function name: id_altar_check
 * Description	: Called to check if player identifies the altar.
 * Arguments	: pl - The player
 * Returns	: 1 for identification, else 0.
 */
public varargs int
id_altar_check(object pl = this_player())
{
    int task = pl->resolve_task(TASK_HARD, ({TS_INT, SS_AWARENESS}));

    /* Sybarites have a slightly better chance of id-ing it */
    if (IS_SYBARITE(pl) && (task > 0))
	return 1;
    else if (task > 25)
	return 1;
    else
	return 0;
}

/*
 * Function name: set_id_long
 * Description	: Set the long description you see if you know
 * 		  what altar it is.
 * Arguments	: str - The description.
 */
public void
set_id_long(string str)		{ id_long = str; }

/*
 * Function name: query_id_long
 * Description	: The long description if you can id the altar.
 */
public string
query_id_long(void)		{ return id_long; }

/*
 * Function name: set_unid_long
 * Description	: Set the long description you see if you cannot
 *		  identify the altar.
 * Arguments	: str - The long description.
 */
public void
set_unid_long(string str)	{ unid_long = str; }

/*
 * Function name: query_unid_long
 * Description	: Query the long description you get if you cannot
 *                identify the altar.
 */
public string
query_unid_long(void)		{ return unid_long; }

/*
 * Function name: set_altar_short
 * Description	: Set the short desc of the altar.
 * Arguments	: str - The description.
 */
public void
set_altar_short(string str)	{ altar_short = str; }

/*
 * Function name: query_altar_short
 * Description	: What is the short description?
 */
public string
query_altar_short(void)		{ return altar_short; }

/*
 * Function name: set_god
 * Description	: Set the name of the god to whom the altar is erected
 * Arguments	: str   - The god's name  - or -
 *                str * - The names of the gods. (up to two)
 */
public void
set_god(mixed str)
{
    if (stringp(str) && strlen(str))
	deities = ({ lower_case(str) });

    if (pointerp(str) && (sizeof(str) < 3))
    {
	foreach(string god : str)
	    deities += ({ lower_case(god) });
    }
}

/*
 * Function name: query_god
 * Description	: What are the names of the gods of this altar.
 */
public string *
query_god(void)			{ return secure_var(deities); }

/*
 * Function name: set_altar_hour
 * Description	: Set the Hour the God/Altar belongs to, if any.
 * Arguments	: i - The Hour.
 */
public void
set_altar_hour(int i)		{ hour = i; }

/*
 * Function name: query_altar_hour
 * Description	: What is the Hour of the god of this altar.
 */
public int
query_altar_hour(void)		{ return hour; }

/*
 * Function name: set_offer_max
 * Description	: Set the maximum number of offerings on the altar.
 * Arguments	: i - The max number.
 */
public void
set_offer_max(int i)		{ offer_max = i; }

/*
 * Function name: query_offer_max
 * Description	: What is the maximum number if offerings permitted.
 */
public int
query_offer_max(void)		{ return offer_max; }

/*
 * Function name: add_offer_short
 * Description	: Set the short(s) for offerings on the altar.
 * Arguments	: shorts - The short(s) for the offerings.
 */
public void
add_offer_short(mixed shorts)
{
    if (pointerp(shorts))
	offer_shorts += shorts;
    else
	offer_shorts += ({ shorts });
}

/*
 * Function name: query_offer_short
 * Description	: Get the short(s) for offerings on the altar.
 */
public string *
query_offer_short(void)		{ return offer_shorts; }

/*
 * Function name: add_offer_bloody
 * Description	: Set the short(s) for blood-offerings on the altar.
 * Arguments	: shorts - The short(s) for the blood-offerings.
 */
public void
add_offer_bloody(mixed shorts)
{
    if (pointerp(shorts))
	offer_bloody += shorts;
    else
	offer_bloody += ({ shorts });
}

/*
 * Function name: query_offer_bloody
 * Description	: Get the short(s) for offerings on the altar.
 */
public string *
query_offer_bloody(void)	{ return offer_bloody; }

/*
 * Function name: set_altar_name
 * Description	: Set the true name of the altar.
 * Arguments	: str - The altar name.
 */
public void
set_altar_name(string str)	{ altar_name = str; }

/*
 * Function name: query_altar_name
 * Description	: Get the true name of the altar.
 */
public string
query_altar_name(void)		{ return altar_name; }

/*
 * Function name: set_offering_prop
 * Description	: Set the 'acceptable offerings' prop.
 *                (prop defines will be in the deities.h file)
 * Arguments	: str - The property.
 */
public void
set_offering_prop(mixed prop)
{
    if (pointerp(prop))
	oprop = prop;
    else
	oprop = ({ prop });
}

/*
 * Function name: query_offering_prop
 * Description	: Get the 'acceptable offerings' properties.
 */
public string *
query_offering_prop(void)	{ return oprop; }

/*
 * Function name: set_bless_command
 * Description	: Set the command(s) to bless the altar.
 * Arguments	: command - The command(s).
 */
public void
set_bless_command(mixed command)
{
    if (pointerp(command))
	bless_cmds = command;
    else
	bless_cmds = ({ command });
}

/*
 * Function name: query_bless_command
 * Description	: Get the command(s) to bless the altar.
 */
public string *
query_bless_command(void)	{ return bless_cmds; }

/*
 * Function name: set_defile_command
 * Description	: Set the command(s) to defile the altar.
 * Arguments	: command - The command(s).
 */
public void
set_defile_command(mixed command)
{
    if (pointerp(command))
	defile_cmds = command;
    else
	defile_cmds = ({ command });
}

/*
 * Function name: query_defile_command
 * Description	: Get the command(s) to bless the altar.
 */
public string *
query_defile_command(void)	{ return defile_cmds; }

/*
 * Function name: set_repair_command
 * Description	: Set the command(s) to repair the altar.
 * Arguments	: command - The command(s).
 */
public void
set_repair_command(mixed command)
{
    if (pointerp(command))
	repair_cmds = command;
    else
	repair_cmds = ({ command });
}

/*
 * Function name: query_repair_command
 * Description	: Get the command(s) to repair the altar.
 */
public string *
query_repair_command(void)	{ return repair_cmds; }

/*
 * Function name: set_destroy_command
 * Description	: Set the command(s) to destroy the altar.
 * Arguments	: command - The command(s).
 */
public void
set_destroy_command(mixed command)
{
    if (pointerp(command))
	destroy_cmds = command;
    else
	destroy_cmds = ({ command });
}

/*
 * Function name: query_destroy_command
 * Description	: Get the command(s) to destroy the altar.
 */
public string *
query_destroy_command(void)	{ return destroy_cmds; }

/*
 * Function name: set_offer_command
 * Description	: Set the command(s) to make offerings at the altar.
 * Arguments	: command - The command(s).
 */
public void
set_offer_command(mixed command)
{
    if (pointerp(command))
	offer_cmds = command;
    else
	offer_cmds = ({ command });
}

/*
 * Function name: query_offer_command
 * Description	: Get the command(s) to make offerings at the altar.
 */
public string *
query_offer_command(void)	{ return offer_cmds; }

/*
 * Function name: set_pray_command
 * Description	: Set the command(s) to pray at the altar.
 * Arguments	: command - The command(s).
 */
public void
set_pray_command(mixed command)
{
    if (pointerp(command))
	pray_cmds = command;
    else
	pray_cmds = ({ command });
}

/*
 * Function name: query_pray_command
 * Description	: Get the command(s) to pray at the altar.
 */
public string *
query_pray_command(void)	{ return pray_cmds; }

/*
 * Function name: alter_short
 * Description	: Creates the modified short description for the altar.
 */
static void
alter_short(void)
{
    string *arr = ({ });

    if (query_prop(ALTAR_IS_BROKEN))
	arr += ({ "damaged" });

    if (query_prop(ALTAR_IS_DEFILED))
	arr += ({ "defiled" });

    short_desc = (sizeof(arr) ? implode(arr, " and ") + " " : "");
    short_desc += altar_short;
    short_desc += (query_prop(ALTAR_IS_BLOODY) ? " covered in blood" : "");
}

/*
 * Function name: create_altar
 * Description	: create the altar object, set default names, etc.
 *                Use this when inheriting this file to create an altar.
 */
public void
create_altar(void)
{
#if 0
// A Simplified example setup.

    set_god("unknown");
    set_altar_hour(0);
    set_altar_name("unknown");
    set_altar_short("unknown altar");

// NOTE: Don't use \n here. It is added automatically.

     set_id_long("This is the long description for those who can "+
	 "identify this altar.");
     set_unid_long("This is the long description for those who cannot "+
	 "identify this altar.");

// NOTE: Below, the set_* refers to add_actions. If you want these
	 actions added, you have to set them in your altar file. These
	 are the 'default' commands, and you should review the functions
	 to see if they are suitable. They can be easily redefined for
	 customization of your altar.

    set_bless_command(({"bless", "sanctify"}));
    set_defile_command(({"desecrate", "defile"}));
    set_repair_command(({"repair", "restore"}));
    set_destroy_command(({"destroy", "break"}));

    set_pray_command(({"pray", "worship"}));
    set_offer_command(({"offer", "sacrifice"}));
#endif
}

/*
 * Function name: create_object
 * Description	: Initialize object.
 */
static nomask void
create_object(void)
{
    setuid();
    seteuid(getuid());

    deities      = ({ });
    bless_cmds   = ({ });
    defile_cmds  = ({ });
    repair_cmds  = ({ });
    destroy_cmds = ({ });
    offer_cmds   = ({ });
    pray_cmds    = ({ });
    offer_shorts = ({ });
    offer_bloody = ({ });

    /* Have this name by default. */
    set_name("altar");

    /* Default maximum offerings. */
    set_offer_max(5);

    /* Default to universal offerings. */
    set_offering_prop(UNIVERSAL_OFFERING);

    /* Altars typically aren't portable. */
    add_prop(OBJ_M_NO_GET, "The altar is far too heavy to be moved.\n");

    /* Weight is used in the do_destroy calculations */
    add_prop(OBJ_I_WEIGHT, 110000);
    add_prop(OBJ_I_VOLUME, 70000);

    /* Now call the regular code. */
    create_altar();
    alter_short();

    /* Add the altar name as a parsable name. */
    if (strlen(altar_name))
	add_name(altar_name);
}

/*
 * Function name: real_short
 * Description	: Returns the unaltered short description.
 */
public varargs string
real_short(object for_obj)
{
    return altar_short;
}

/* Function name: short
 * Description	: Add the status of the altar to it.
 * Arguments	: for_obj - who wants to know the short.
 * Returns	: The altered short description.
 */
public varargs string
short(object for_obj)
{
    return short_desc;
}

/*
 * Function name: long
 * Description	: Add the altar status to the long description.
 * Arguments	: string str     - The psuedo-item the person wants to see.
 * 		  object for_obj - Who wants to know the long.
 * Returns	: The modified long description.
 */
public varargs string
long(string str, object for_obj = this_player())
{
    if (strlen(str))
	return ::long(str, for_obj);
    else
	str = "";

    if (query_prop(ALTAR_IS_BROKEN))
	str += " It has been damaged.";

    if (query_prop(ALTAR_IS_DEFILED))
	str += " It has been defiled.";

    if (sizeof(offer_shorts))
    {
	string *arr = map(offer_shorts, LANG_FILE->add_article);
	str += " Someone has made the offering of "+
	    COMPOSITE_WORDS(arr) +" on the altar.";
    }

    if (sizeof(offer_bloody))
    {
	string *arr = map(offer_bloody, LANG_FILE->add_article);
	str += " It has the corpse of "+ COMPOSITE_WORDS(arr) +" on it.";
    }

    if (id_altar_check(for_obj))
	return id_long + str +"\n";
    else
	return unid_long + str +"\n";
}

/*
 * Function name: altar_result_pos
 * Description	: Here the message is written when the player
 *                does something positive to the altar.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 */
public void
altar_result_pos(string verb, string god)
{
    write("A feeling of ecstasy uplifts you, as though you can feel "+
	LANG_POSS(god) +" pleasure in your actions.\n");

    say(QCTNAME(this_player()) +" appears to be momentarily over"+
	"come with ecstacy.\n");
}

/*
 * Function name: altar_result_neg
 * Description	: Here the message is written when the player
 *                does something negative to the altar.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 */
public void
altar_result_neg(string verb, string god)
{
    write("You have the sense of something malignant preying upon "+
	"your mind, as though you have offended the being to whom "+
	"this altar was erected and it is intent upon vengeance.\n");

    say(QCTNAME(this_player()) +" suddenly looks frightened by "+
	this_player()->query_possessive() +" actions, as if "+
	this_player()->query_pronoun() +" fears the consequences.\n");

    WRATHOBJ->load_me();
    WRATHOBJ->mark_enemy(this_player());
}

/*
 * Function name: valid_anchorite
 * Description	: See if 'who' is an anchorite able to affect this altar.
 * Arguments	: object who - The person to test.
 * Returns	: 1 - valid / 0 - invalid.
 */
public varargs int
valid_anchorite(object who = this_player())
{
    /*
     * This can be fleshed out should there ever be any real anchorites.
     * Until then, it can be masked as-needed to allow people the access.
     */
    return 0;
}

/*
 * Function name: query_idrys
 * Description	: Which god is 'who' an anchorite of?
 * 		  This is needed since altars may belong to more than
 * 		  one god but 'who' might only be devoted to one of them.
 * Arguments	: object who - Who we are checking.
 * Returns	: string - The name(s) of deities 'who' follows.
 */
public varargs string
query_idrys(object who = this_player())
{
    /*
     * This can be fleshed out should there ever be any real anchorites.
     * Until then, it can be masked as-needed to allow people the access.
     */
    return capitalize(one_of_list(deities));
}

/*
 * Function name: bless_text
 * Description	: Here the bless message is written.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 */
static void
bless_text(string verb, string god)
{
    write("You invoke "+ god +" and channel the power "+
	"of the Idrys to "+ verb +" the "+ real_short() +".\n");

    say(QCTNAME(this_player()) +" invokes the power of the Idrys "+
	"and "+ LANG_PWORD(verb) +" the "+ real_short() +".\n");
}

/*
 * Function name: do_bless
 * Description	: Bless/sanctify this altar.
 * Arguments	: str - The words after the verb.
 */
public int
do_bless(string str)
{
    object ob;
    string verb = query_verb(), *gods = map(deities, capitalize);

    if (!strlen(str) ||
	!parse_command(str, ({ this_object() }), "[the] %o", ob) ||
	(ob != this_object()))
    {
	return notify_fail(capitalize(verb) + " what? The altar?\n");
    }

    /* We don't know what this is. */
    if (!id_altar_check())
    {
	write("You are not certain as to the nature of the "+
	    real_short() +", so you decide not to "+ verb +
	    " anything after all.\n");
	return 1;
    }

    if (!valid_anchorite())
    {
	write("You are not an anchorite of "+
	    COMP_OR(gods) +".\nYour attempt to "+ verb +
	    " this "+ real_short() +" has failed.\n");
	say(QCTNAME(this_player()) +" attempts to "+ verb +
	    " the "+ real_short() +", but fails.\n");

	return 1;
    }

    if (query_prop(ALTAR_IS_BROKEN))
    {
	write("The "+ real_short() +" has been damaged.\n"+
	    "You cannot "+ verb +" it in this condition!\n");
	return 1;
    }

    str = query_idrys();
    bless_text(verb, str);

    if (query_prop(ALTAR_IS_DEFILED))
    {
	altar_result_pos(verb, str);
	remove_prop(ALTAR_IS_DEFILED);
	alter_short();
    }

    return 1;
}

/*
 * Function name: defile_text
 * Description	: Here the defile message is written.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 */
static void
defile_text(string verb, string god)
{
    write("You commit an act of blasphemy by your defilement "+
	"of the "+ real_short() +".\n");

    say(QCTNAME(this_player()) +" "+ LANG_PWORD(verb) +
	" the "+ real_short() +".\n");
}

/*
 * Function name: do_defile
 * Description	: Defile this altar.
 * Arguments	: str - The words after the verb.
 */
public int
do_defile(string str)
{
    object ob;
    string verb = query_verb(), *gods = map(deities, capitalize);

    if (!strlen(str) ||
	!parse_command(str, ({ this_object() }), "[the] %o", ob) ||
	(ob != this_object()))
    {
	return notify_fail(capitalize(verb) + " what? The altar?\n");
    }

    if (query_prop(ALTAR_IS_DEFILED))
    {
	write("The "+ real_short() +" has already been defiled!\n");
	return 1;
    }

    defile_text(verb, COMPOSITE_WORDS(gods));
    altar_result_neg(verb, COMPOSITE_WORDS(gods));

    add_prop(ALTAR_IS_DEFILED, 1);
    alter_short();

    return 1;
}

/*
 * Function name: repair_text
 * Description	: Here the repair message is written.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 */
static void
repair_text(string verb, string god)
{
    write("You set about "+ verb +"ing the "+ real_short() +", "+
	"restoring it to its proper glory.\n");

    say(QCTNAME(this_player()) +" sets about "+ verb +"ing the "+
	real_short() +" and restores it to its proper glory.\n");
}

/*
 * Function name: do_repair
 * Description	: Repair this altar.
 * Arguments	: str - The words after the verb.
 */
public int
do_repair(string str)
{
    object ob;
    string verb = query_verb(), *gods = map(deities, capitalize);

    if (!strlen(str) ||
	!parse_command(str, ({ this_object() }), "[the] %o", ob) ||
	(ob != this_object()))
    {
	return notify_fail(capitalize(verb) + " what? The altar?\n");
    }

    if (!query_prop(ALTAR_IS_BROKEN))
    {
	write("The "+ real_short() +" isn't damaged, you cannot "+
	    verb +" it further.\n");
	return 1;
    }

    /* We don't know what this is. */
    if (!id_altar_check())
    {
	write("You are not certain as to the nature of the "+
	    real_short() +", so you decide not to "+ verb +
	    " anything after all.\n");
	return 1;
    }

    if (!valid_anchorite())
    {
	write("You are not an anchorite of "+
	    COMP_OR(gods) +".\nYour attempt to "+ verb +
	    " this "+ real_short() +" has failed.\n");
	say(QCTNAME(this_player()) +" attempts to "+ verb +
	    " the "+ real_short() +", but fails.\n");
	return 1;
    }

    /* This should probably be a delayed process, but I'm lazy. */
    repair_text(verb, COMPOSITE_WORDS(gods));

    remove_prop(ALTAR_IS_BROKEN);
    alter_short();

    return 1;
}

/*
 * Function name: destroy_text
 * Description	: Here the destroy message is written.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 */
static void
destroy_text(string verb, string god)
{
    write("You set about "+ verb +"ing the "+ real_short() +", enough "+
	"to disrupt its sanctity to the Idrys.\n");

    say(QCTNAME(this_player()) +" sets about "+ verb +"ing the "+
	real_short() +", disrupting its sanctity to the Idrys.\n");
}

/*
 * Function name: do_destroy
 * Description	: Destroy this altar.
 * Arguments	: str - The words after the verb.
 */
public int
do_destroy(string str)
{
    object ob;
    string verb = query_verb(), *gods = map(deities, capitalize);

    if (!strlen(str) ||
	!parse_command(str, ({ this_object() }), "[the] %o", ob) ||
	(ob != this_object()))
    {
	return notify_fail(capitalize(verb) + " what? The altar?\n");
    }

    if (query_prop(ALTAR_IS_BROKEN))
    {
	write("The "+ real_short() +" is already broken.\n"+
	    "You cannot "+ verb +" it any more than it already is!\n");
	return 1;
    }

    if (this_player()->resolve_task(TASK_FORMIDABLE, ({ TS_STR })) <= 1)
    {
	write("You do not have the strength to do any serious damage "+
	    "to the "+ real_short() +".\n");
	say(QCTNAME(this_player()) +" doesn't seem to have the strength "+
	   "to damage the "+ real_short() +".\n");
	return 1;
    }

    str = COMPOSITE_WORDS(gods);

    destroy_text(verb, str);
    altar_result_neg(verb, str);

    add_prop(ALTAR_IS_BROKEN, 1);
    alter_short();

    return 1;
}

/*
 * Function name: item_filter
 * Description	: Filter player inventory for wielded weapons.
 * Returns	: 0 - if no wielded weapons, 1 - if there are.
 */
static int
item_filter(object ob)
{
    return IN_ARRAY(ob->query_wt(), ({ W_KNIFE, W_SWORD }));
}

/*
 * Function name: check_oprop
 * Description	: Check offered object for 'acceptable' property.
 * Returns	: string - empty if no match, God if matching.
 */
static string
check_oprop(object ob)
{
    foreach(string prop : oprop)
    {
	if (!ob->query_prop(prop))
	    continue;

	if (sscanf(prop, "_obj_i_am_%s_offering", prop))
	    return prop;
	else
	    return "Universal";
    }

    return "";
}

/*
 * Function name: offer_text
 * Description	: The text given for a normal offering.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 * 		  string what - What was offered.
 */
static void
offer_text(string verb, string god, string what)
{
    write("Your "+ verb +" of "+ LANG_ADDART(what) +" at the "+
	real_short() +" has been accepted by "+ god +".\n");

    say(QCTNAME(this_player()) +" "+ LANG_PWORD(verb) +" "+
	LANG_ADDART(what) +" at the "+ real_short() +".\n");
}

/*
 * Function name: bloody_offer_text
 * Description	: The text given for a bloody offering.
 * Arguments	: string verb - The verb used.
 * 		  string god  - The god invoked.
 * 		  string what - What was offered.
 * 		  object wep  - The weapon used.
 */
static void
bloody_offer_text(string verb, string god, string what, object wep)
{
    write("Making an offering to "+ god +", you slit the "+ what +
	" open on the "+ real_short() +" with your "+ wep->short() +
	".\nThe "+ what +" writhes and twitches spasmodically "+
	"under your hands, splashing blood everywhere.\n");

    say(QCTNAME(this_player()) +" offers the "+ what +" as a blood "+
	"sacrifice upon the "+ real_short() +".\n"+
	QCTNAME(this_player()) +" slits the "+ what +" open with "+
	this_player()->query_possessive() +" "+ wep->short() +
	"and watches as it writhes and twitches spasmodically, "+
	"splashing blood everywhere.\n");
}

/*
 * Function name: do_offer
 * Description	: Make an offering on this altar.
 * Arguments	: str - The words after the verb.
 */
public int
do_offer(string str)
{
    object *obs, ob;
    string verb = query_verb(), parse, god;

    if (!strlen(str))
	return notify_fail(capitalize(verb) + " what?\n");

    obs   = all_inventory(this_player());
    parse = "[the] %o 'at' / 'on' / 'to' [the] %w";

    /* Parse the input. */
    if (!parse_command(str, obs, parse, ob, god) ||
	!objectp(ob) || !strlen(god) ||
	!IN_ARRAY(god, deities + ({ "altar" })))
    {
	notify_fail("The correct syntax is: '"+ verb +
	    " <item> on the altar', or, '"+ verb +
	    " <item> to <god>'\n");
	return 0;
    }

    /* We don't know what this is. */
    if (!id_altar_check())
    {
	write("You are not certain as to the nature of the "+
	    real_short() +", so you decide not to "+ verb +
	    " anything after all.\n");
	return 1;
    }

    /* Altar is damaged. */
    if (query_prop(ALTAR_IS_BROKEN))
    {
	write("The "+ real_short() +" is damaged.\n"+
	    "You cannot "+ verb +" anything on it in this condition!\n");
	return 1;
    }

    /* Altar is defiled. */
    if (query_prop(ALTAR_IS_DEFILED))
    {
	write("The "+ real_short() +" has been defiled!\n"+
	    "You cannot "+ verb +" anything on it in this condition!\n");
	return 1;
    }

    /* Too many offerings. */
    if (query_prop(ALTAR_IS_OCCUPIED) >= offer_max)
    {
	write("No further offerings can be made "+
	   "at the "+ real_short() +".\n");
	return 1;
    }

    /* No worn or wielded items. */
    if (ob->query_worn() || ob->query_wielded())
    {
	write("You cannot "+ verb +" worn or wielded items.\n");
	return 1;
    }

    /* Get the proper short. */
    if (ob->query_prop(HEAP_I_IS))
	str = ob->singular_short();
    else
	str = ob->short();

    /* Don't accept broken items. */
    if (ob->query_prop(OBJ_I_BROKEN))
    {
	write("The Idrys would not accept a broken offering.\n");
	return 1;
    }

    /* Check for props. */
    if (!strlen(parse = check_oprop(ob)))
    {
	write("The "+ str +" is not an acceptable offering.\n");
	return 1;
    }

    /* Just to make sure players don't sacrifice each other. */
    if (query_interactive(ob))
    {
	write("You cannot offer "+ ob->query_the_name(this_player()) +"!\n");
	return 1;
    }

    /* If an object has this prop defined, it does something special
     * when offered. Since the effect depends upon the offering, the
     * function altar_special(object altar) -must- be defined in the
     * offered object or an error will result.
     */
    foreach (string prop : oprop)
    {
        if (ob->query_prop(prop))
        {
        	if (ob->altar_special(this_object(), this_player()))
            {
	            return 1;
            }
        }
    }

    /* Get the proper god. */
    if (parse != "Universal")
	god = parse;
    else if (god == "altar")
	god = query_idrys();
    else
	god = capitalize(god);

    /* Living (bloody) sacrifice. */
    if (living(ob))
    {
	object wep;

	obs = filter(this_player()->query_weapon(-1), item_filter);
	wep = one_of_list(obs);

	if (!objectp(wep))
	{
	    write("You need to be wielding a blade in order to "+
		verb +" the "+ str +" properly.\n");
	    return 1;
	}

	/* Bloody offering. */
	bloody_offer_text(verb, god, str, wep);
	altar_result_pos(verb, god);

	/* Add the bloody sacrifice to the altar long */
	add_offer_bloody(str);
	alter_short();

	/* Increase blood-offering count in player by one */
	this_player()->add_prop(I_MADE_BLOOD_OFFERING,
	    this_player()->query_prop(I_MADE_BLOOD_OFFERING) + 1);

	/* Increase the number of offerings in the altar by one. */
	add_prop(ALTAR_IS_OCCUPIED, query_prop(ALTAR_IS_OCCUPIED) + 1);

	/* Blood-sacrifices are messy. */
	add_prop(ALTAR_IS_BLOODY, 1);
	ob->remove_object();

	return 1;
    }

    /* Normal offering. */
    offer_text(verb, god, str);
    altar_result_pos(verb, god);

    /* Add the sacrifice to the altar long */
    add_offer_short(str);
    alter_short();

    /* Increase offering count in player by one. */
    this_player()->add_prop(I_MADE_OFFERING,
	this_player()->query_prop(I_MADE_OFFERING) + 1);

    /* Increase the number of offerings in the altar by one. */
    add_prop(ALTAR_IS_OCCUPIED, query_prop(ALTAR_IS_OCCUPIED) + 1);

    /* This handles heaps like leftovers. */
    if (ob->query_prop(HEAP_I_IS))
	ob->set_heap_size(ob->num_heap() - 1);
    else
	ob->remove_object();

    return 1;
}

/*
 * Function name: pray_text
 * Description	: Here the prayer/worship message is written.
 * Arguments	: string verb - The verb used (pray or worship)
 * 		  string god  - The god invoked.
 */
static void
pray_text(string verb, string god)
{
    if (verb == "pray")
	verb += "ing";

    write("You assume the proper posture for "+ verb +" to "+ god +
	".\n\nYou kneel before the "+ real_short() +", pressing "+
	"your forehead against the ground and stretching your "+
	"arms out toward it.\n");

    say(QCTNAME(this_player()) +" kneels before the "+
	real_short() +" in supplication.\n");
}

/*
 * Function name: do_pray
 * Description	: Pray / Worship at the altar.
 * Arguments	: str - The words after the verb.
 */
public int
do_pray(string str)
{
    string verb = query_verb(), god;

    if (!strlen(str))
    {
	notify_fail(capitalize(verb) +" how?\n");
	return 0;
    }

    /* Parse the input. */
    if (!parse_command(lower_case(str), ({}), "[at] [to] [the] %w", god) ||
	!strlen(god) || !IN_ARRAY(god, deities + ({ "altar" })))
    {
	notify_fail(capitalize(verb) +" how? To what?\n");
	return 0;
    }

    /* Altar is damaged. */
    if (query_prop(ALTAR_IS_BROKEN))
    {
	write("The "+ real_short() +" is damaged.\n"+
	    "You cannot "+ verb +" here.\n");
	return 1;
    }

    /* Altar is defiled. */
    if (query_prop(ALTAR_IS_DEFILED))
    {
	write("The "+ real_short() +" has been defiled!\n"+
	    "You cannot "+ verb +" here.\n");
	return 1;
    }

    /* Get the proper god. */
    if (god == "altar")
	god = query_idrys();
    else
	god = capitalize(god);

    if (id_altar_check())
    {
	pray_text(verb, god);
	altar_result_pos(verb, god);
	return 1;
    }

    write("You take a moment to "+ verb +" silently.\n");
    say(QCTNAME(this_player()) +" takes a moment to "+
	verb +" silently.\n");

    return 1;
}

public void
init(void)
{
    int i, s;

    ::init();

    for (i = 0, s = sizeof(pray_cmds); i < s; i++)
	add_action(do_pray, check_call(pray_cmds[i]));

    for (i = 0, s = sizeof(offer_cmds); i < s; i++)
	add_action(do_offer, check_call(offer_cmds[i]));

    for (i = 0, s = sizeof(bless_cmds); i < s; i++)
	add_action(do_bless, check_call(bless_cmds[i]));

    for (i = 0, s = sizeof(defile_cmds); i < s; i++)
	add_action(do_defile, check_call(defile_cmds[i]));

    for (i = 0, s = sizeof(repair_cmds); i < s; i++)
	add_action(do_repair, check_call(repair_cmds[i]));

    for (i = 0, s = sizeof(destroy_cmds); i < s; i++)
	add_action(do_destroy, check_call(destroy_cmds[i]));
}
