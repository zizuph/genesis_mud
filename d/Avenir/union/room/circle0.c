/*
 * /d/Avenir/union/room/circle0.c
 * is based on 
 * /d/Avenir/common/bazaar/museum/studio.c
 * Studio where players can have a statue of themselves
 * made.
 *   Cirion 040296
 *
 * Revisions:
 *   Lucius May 2005: Recoded a bit to work fully.
 *   Lilith Jun 2014: Added room tells re the Well of Souls
 *   Lucius Aug 2017: Cleanups.
 *   Lilith Apr 2022: Added ability of Elders to remove statues.
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;
/* Inherit the room_tell functions */
inherit "/d/Avenir/inherit/room_tell";

#include <macros.h>
#include <language.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

#define STATUES		(SAVINGS + "statues")
#define STAT1		(ROOM + "circle1")
#define STAT2		(ROOM + "circle2")
#define SEE_OUT		({ ROOM +"circle1", ROOM +"circle2" })


/* Prototypes */
public string generate_desc(object who);

/* Format for statues : name, desc */
public string  *statue1 = ({ }), *statue2 = ({ });


#ifdef UOPT_RMTXT
public int
skip_room_tells(object who)
{
    return !LIST->query_union_option(who, UOPT_RMTXT);
}
#endif


public object *
get_view(string *arr)
{
    object *inv = ({});

    foreach(string path: arr)
    {
	object room = find_object(path);
	if (objectp(room))
	    inv += all_inventory(room);
    }

    if (sizeof(inv))
	inv = FILTER_CAN_SEE(FILTER_LIVE(inv), TP);

    return inv;
}

public string
see_view(void)
{
    object *obs = get_view(SEE_OUT);
    if (sizeof(obs))
    {
	return " Looking outward, you see "+ COMPOSITE_LIVE(obs) +
	    " standing amongst the statues that form two "+
	    "concentric rings around the center of the cavern.";
    }
    return " Looking outward, you can see that statues have been "+
	"placed in two concentric rings around the center of the "+
	"cavern.";
}

public void 
union_room(void)
{
    set_short("center of the cavern");
    set_long("You stand at the foot of a flue which spirals "+
      "upwards into the ceiling of this cavern. The air fairly "+
      "hums with an energy that lifts the hair on your arms and "+
      "sends tingles coursing down your spine. Below the flue "+
      "is a great blue flame rising from a pool of water whose "+
      "dark depths conceal many mysteries.@@see_view@@\n");

    add_prop(ROOM_S_DARK_LONG, "You are embraced by darkness. "+
      "The air fairly hums with an energy that lifts the hair "+
      "on your arms and sends tingles coursing down your spine.\n"); 

    add_item("statues", "You would have to walk farther out into "+
      "the cavern to see them clearly.\n");

    add_item(({"flue", "spiral"}), 
      "It is a flue or channel made of the same dark stone as the "+
      "rest of this place. It appears to be glossy and smooth, and "+
      "it spirals upward into darkness. Fortunately, the bottom "+
      "lip of it curves upward, so when you were sliding down it, "+
      "you had enough forward lift to miss landing in the pool "+
      "of water and flame located directly below it.\n");

    add_exit("circle1", "outward");
    add_exit("circle1", "out", 0, 1, 1);

    set_tell_time(180);
    add_tell("Voices murmur, ebbing and flowing, barely audible.\n");
    add_tell("You are uplifted by an eddy of Passion.\n");
    add_tell("There is a puff of air, as though something large "+
      "just passed you.\n");
    add_tell("You feel the touch of warm fingers upon your nape, "+
      "and the echo of a kiss upon your cheek.\n");
    add_tell("You sense a familiar presence emanating from the Well.\n");
    add_tell("The water of the well ripples as the flame dances.");
    add_tell("   Embraced by the Flame, tested and proven worthy, "+
      "you are the pride of Jazur.\n");
    add_tell("   All that you need lies within you.\n");
    add_tell("   This moment is a gift. Honour me by fully living it.\n");
    add_tell("The room is pervaded with the spirits of your other selves.\n");
    add_tell("A tendril of blue something extends from the Well of Souls, reaching "+
      "toward you.\nA thousand different voices wash through "+
      "your consciousness, all unified, all echoing a wordless "+
      "message of pride affection duty longing zeal ecstacy "+
      "loyalty perseverance fervor righteousness fealty passion.\n");

    add_object(OBJ + "well");
    restore_object(STATUES);
}

/* Called from the oter rooms of the
 * gallery to see which statues are there
 */
public string *
query_statues(int which)
{
    switch(which)
    {
    default: /* Fallthru */
    case 1: return secure_var(statue1); break;
    case 2: return secure_var(statue2); break;
    }
}

/* Find a name in the arrays of statues, and
 * remove it and the statue desc if it is 
 * there. Returns 1 success, 0 failure
 */
public int
remove_statue(string name)
{
    int index;

    if ((index = member_array(name, statue1)) != -1)
    {
	statue1 = exclude_array(statue1, index, (index + 1));
	find_object(STAT1)->make_statues();
	save_object(STATUES);
	return 1;
    }
    else if ((index = member_array(name, statue2)) != -1)
    {
	statue2 = exclude_array(statue2, index, (index + 1));
	find_object(STAT2)->make_statues();
	save_object(STATUES);
	return 1;
    }
    return 0;
}

/* Remove a statue of yourself from the gallery.
 * If you are an elder or a wiz you can remove 
 * someone else's statue.
 */
public int
remove(string str)
{
    string  name;

    if (!str)
	name = TP->query_real_name();
    else if (str == "my statue")
	name = TP->query_real_name();

    if (TP->query_wiz_level() && strlen(str))
    {
	name = str;
	write("Let's hope you have a good reason for this.\n");
    }
	
	if (IS_ELDER(TP) && strlen(str))
	{
    name = str;
    write("As an Elder, it is within your power to remove the statue "+
        "of "+ capitalize(name));
    }		

    if (!remove_statue(name))
	return NF("Either there does not seem to be such a statue afterall, "+
       "or there was an error. If this is in error, please inform "+
       "the Guildmaster.\n");

    write("So be it. The statue shimmers and then fades away into "+
        "the shadows.\n");
    return 1;
}

public int
do_pay(string str)
{
    object who;
    string name, title, desc;

    /* So that players cannot do this. */
    if (query_verb() == "pay" && !TP->query_wiz_level())
	return 0;

    if (!objectp(who = find_living(str)))
	who = TP;

    name = who->query_real_name();

    /* Is there already a statue? */
    if (member_array(name, (statue1 + statue2)) != -1)
	return 1;

    if (strlen(title = who->query_title()))
	title = CAP(name) + " " + title + ".";
    else
	title = CAP(name) + ".";

    desc = generate_desc(who) +
	"A plaque at the foot of the statue reads:\n"+ title +"\n";

    switch(random(2))  
    {
    default:
	/* Fallthru */
    case 0:
	statue1 = (({ name, desc }) + statue1);
	find_object(STAT1)->make_statues();
	save_object(STATUES);
	return 1;
	break;
    case 1:
	statue2 = (({ name, desc }) + statue2);
	find_object(STAT2)->make_statues();
	save_object(STATUES);
	return 1;
	break;
    }
}

/* The stone and style of the statue is determined by
 * the primary guild of the player
 */
public string
material(object who)
{
    switch(who->query_race())
    {
    case "elf":    
	return "palest alabaster, smooth and flawless"; 
    case "human":  
	return "perfect white marble with a pale, bluish tint"; 
    case "gnome":  
	return "pale granite, streaked with veins of feldspar"; 
    case "hobbit":
	return "grey limestone";
    default:
	return "professionally carved granite";
    }
}

/* Generate the description of the player */
public string
generate_desc(object who)
{
    int    i;
    string ret, sub, *dum, nihil, pro, pos, obj, a, b, c;

    pro = who->query_pronoun();
    pos = who->query_possessive();
    obj = who->query_objective();

    ret = "It is a statue made from "+ material(who) +
	", depicting "+ who->query_nonmet_name() +". "+
	implode(explode(who->long(TO), "\n"), " ");

    if (sscanf(ret, "%shair is%s", nihil, nihil))
    {
	ret = implode(explode(ret, CAP(pos) +" hair is"),
	    "The hair of the statue is crafted to appear");
    }

    /*  No scars shown, there can be so many of them
    if (sscanf(ret, "%shas scars%s", nihil, nihil))
    {
	ret = implode(explode(ret, CAP(pro)+" has scars"),
	    "Skillfully etched into the surface are scars");
    }
     */

    dum = explode(ret, ". ");

    for(i = 0; i < sizeof(dum); i++)
    {
	if (sscanf(dum[i], CAP(pro) +" is an %s", nihil) ||
	    sscanf(dum[i], CAP(pro )+" is a %s", nihil))
	{
	    dum[i] = "The statue shows that "+ pro +" is "+
		LANG_ADDART(nihil);
	}

	if (sscanf(dum[i], "%spresenting%s", nihil, nihil) ||
	    sscanf(dum[i], "%sseems to be%s", nihil, nihil) ||
	    sscanf(dum[i], "%svoice%s", nihil, nihil) ||
	    sscanf(dum[i], "%smove%s", nihil, nihil))
	{
	    dum[i] = "";
	}

	if (sscanf(dum[i], CAP(pro) +" looks%s", nihil))
	    dum[i] = "The figure shows "+ obj +" as looking"+ nihil;
    }

    ret = implode(dum, ". ");
    ret = implode(explode(ret, "\n"), " ");

    /* Get rid of ugly extra stuff */
    while(wildmatch("*  *", ret))
	ret = implode(explode(ret, "  "), " ");

    while(wildmatch("*. .*", ret))
	ret = implode(explode(ret, ". ."), ".");

    ret = implode(explode(ret, ".."), ".");
    ret = implode(explode(ret, " (open)"), "");
    ret = implode(explode(ret, " (closed)"), "");
    ret = implode(explode(ret, "!!"), "!");
    ret = implode(explode(ret, "!!"), "!");

    return (ret + "\n");
}

/*
 * Function name:  help_here
 * Description:    Provide help for the functions in this room
 * Argument:       
 * Returns:        
 */  
public int 
help_here(string str)
{
    if (!str)
    {
	notify_fail("Help what? Help statue?\n");
	return 0;
    }

    if (str == "statue" || str == "here" || str == "statues")
    {

	write("\nYour statue was formed by the shadows as you travelled "+
	  "down the spiral flue.\nIf you do not approve of the manner "+
	  "in which you have been depicted, you may 'destroy' the statue "+
	  "and the shadows will form a new one when next you arrive here.\n");
    if (IS_ELDER(TP))
		write("As an Elder, you have the ability to destroy any statue "+
        "here. This act should be reserved for those who have betrayed "+
        "the Union in unmentionable ways.\n");		
	return 1;
    }

    notify_fail("Help what? Help statue?\n");
    return 0;
}

public int 
do_drink(string str)
{
    int dr;

    if (!strlen(str) || !parse_command(str, ({}),
	    "[from] [the] 'water' / 'pool' / 'well'"))
    {
	return NF("Drink what?\n");
    }


    if (!(dr = TP->query_prop(LIVE_I_MAX_DRINK) / 16))
	dr = 200;

    if (!TP->drink_soft(dr))
    {
	write("The water is too much for you.\n");
	return 1;
    }

    // nourish body as well?
    write("You kneel at the edge of the pool and plunge your hands "+
      "through the blue flames to scoop water from it.\nThe water "+
      "is cool and refreshing.\n");
    say(QCTNAME(TP) +" kneels at the edge of the water and drinks "+
      "deeply from it.\n");

    return 1;
}

public int
dive(string str)
{
    NF(CAP(query_verb()) + " what?\n");
    if (!strlen(str))
	return 0;

    if (!parse_command(str, ({}),
	    "[in] / [into] [the] 'water' / 'pool' / 'well' / 'flames' / 'flame'"))
    {
	return 0;
    }

    write("You dive into the pool, your body arching through the flames.\n");
    say(QCTNAME(TP) + " dives into the the flames.\n");
    TP->move_living("M", ROOM + "well_water", 1);
    return 1;
}

public void
enter_inv(object ob, object from)
{
    string name;

    ::enter_inv(ob, from);
    start_room_tells(); 

    if (IS_TORNU(ob))
	do_pay(ob->query_real_name());
}

public void
init(void)
{
    ::init();

    add_action(dive,	  "dive");
    add_action(dive,	  "enter");
    add_action(do_drink,  "drink");
    add_action(remove,	  "destroy");
    add_action(remove,	  "remove");
    add_action(help_here, "help");
    add_action(do_pay,	  "pay");
}

/*
 * Function name: query_jazur_flame_present
 * Description:   Check to see if the jazur flame is present
 *                in the room. Used for objects that need to
 *                see if they are in a room with the Jazur
 *                flame.
 * Arguments:     none
 * Returns:       1 if Jazur Flame is present, 0 otherwise,
 *                string for a specific fail message.
 */
public mixed
query_jazur_flame_present(void)
{
    return 1;
}

public int
query_prevent_snoop(void)
{
    return 1;
}
