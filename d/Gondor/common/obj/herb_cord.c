/*
 * /d/Gondor/common/obj/herb_cord.c
 *
 * This is my attempt to code something based on a suggestion
 * by the mortal player Saty.
 * It is a cord that can be used to weave herbs together into
 * a necklace, circlet, or bracelet wreath.
 *  	Gorboth, March 1997
 *
 * Completed by Gnadnar February 1998
 *
 */

#pragma strict_types;

inherit "/std/armour";

#include <language.h>
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>

#include "/d/Gondor/defs.h"

#define	MAX_HERBS	20
#define	MIN_HERBS	10
#define	CORD_VALUE	12

/* only supple herbs may be wound -- no potatoes or peppercorns :-) */
#define	ALLOWED_HERBS	\
    ({ "flower", "flowers", "leaf", "leaves", "lichen", "moss", \
       "umbel", "vine", "weed" })

/* state of cord */
#define	CORD_UNTIED	0
#define	CORD_CIRCLET	1
#define	CORD_BRACELET	2
#define	CORD_NECKLACE	3

#define	ITCH_POISON_FILE	"/d/Gondor/common/poison/sumac_poison"
#define	ITCH_POISON_NAME	"_gondor_herb_sumac_poison"

// Prototypes
public void	create_armour();
public void	init();
public string	describe();
public int	wind_herb(string arg);
public int	unwind_herb(string arg);
public void	return_herbs();
public int	tie_cord(string arg);
public int	untie_cord(string arg);
public mixed	wear_me();
public int	query_value();

// Global Variables
static int	Nherbs = 0,		// How many herbs wound onto cord
		Type = CORD_UNTIED,	// Tied into CORD_*
		Itches;			// Fool is using poison ivy or sumac
static string	Herb_short = "herb",	// Short desc
		Herb_pshort = "herbs",	// Plural short desc
		Type_name,		// "cord", "bracelet", ...
		Herb_desc = "herbs";	// pshort stripped of leading
					// 	"handfuls of "


/*
 * Function name:	create_armour
 * Description	:	set up the cord
 */
public void
create_armour()
{
    set_name("cord");
    set_pname("cords");
    add_adj( ({ "leather","herb","short" }) );
    add_name( ({ "wreath", "herbcord" }) );
    add_pname( ({ "wreaths", "herbcords" }) );
    set_short("leather cord");
    set_pshort("leather cords");
    set_long(describe);

    remove_name("armour");
    set_at(A_HEAD);
    set_ac(0);
    add_prop(OBJ_I_WEIGHT, 113); /* 4 oz */
    add_prop(OBJ_I_VOLUME, 113); /* ?? just make it match weight */
    add_prop(OBJ_I_VALUE, query_value);
    add_prop(CONT_M_NO_REM,
	"You must unwind the cord before removing any herbs.\n");

} /* create_armour */


/*
 * Function name:	init
 * Description	:	add the player verbs
 */
public void
init()
{
    ::init();
    add_action(wind_herb,	"wind");
    add_action(unwind_herb,	"unwind");
    add_action(tie_cord,	"tie");
    add_action(untie_cord,	"untie");
} /* init */


/*
 * Function name:	describe
 * Description	:	VBFC for the cord long
 * Returns	:	string -- the description
 */
public string
describe()
{
    string hd = "This short leather cord may be used"
              + " to form a wreath of herbs. It looks as if";

    if (!Nherbs)
    {
	hd += " one could easily wind herbs around the cord.";
    }
    else if (Type != CORD_UNTIED)
    {
	hd += " the cord has been tied into a "+Type_name
	    + " of "+Herb_desc+".";
    }
    else if (Nherbs >= MIN_HERBS)
    {
	hd += " enough "+Herb_desc+" have been wound around the cord"
	    + " to create a wreath. It could now be tied together into a"
	    + " necklace, circlet or bracelet, and worn.";
    }
    else
    {
	hd += " someone has taken the time to wind "
            + (Nherbs > 1 ? "at least "+LANG_WNUM(Nherbs)+" "+Herb_pshort :
	    		    LANG_ADDART(Herb_short))
	    + " into the wreath, but there is room for more.";
    }
    return BSN(hd);
} /* describe */


/*
 * Function name:	wind_herb
 * Description	:	handle player's attempts to wind herbs around cord
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
wind_herb(string arg)
{
    object	*obs;
    string	tmpstr;
    int		s;

    if (!strlen(arg))
    {
        NFN0("What do you want to wind around what?");
    }

    if (!(parse_command(arg, all_inventory(TP),
	    "%i 'around' [the] [leather] 'cord'", obs)))
    {
        NFN0("Wind which herb around the leather cord?");
    }

    obs = NORMAL_ACCESS(obs, 0, 0);
    s = sizeof(obs);
    if (!s)
    {
        NFN0("Wind which herb around the leather cord?");
    }
    if (s > 1)
    {
	NFN0("This work is too delicate; you can only wind one "
	   + "herb at a time.");
    }

    if (function_exists("create_object", obs[0]) != "/std/herb")
    {
        NFN0("Only herbs may be used to form a wreath with the"
           + " leather cord.");
    }
    if (member_array(obs[0]->query_name(), ALLOWED_HERBS) < 0) 
    {
	NFN0("The "+arg+" is not supple enough to be wound "
	   + "around the cord.");
    }

    if (Type != CORD_UNTIED)
    {
	NFN0("The cord has been tied into a "+Type_name+". "
	   + "You must untie it before winding more herbs into it.");
    }

    if (obs[0]->query_dried())
    {
        NFN0("Unfortunately, the "+obs[0]->query_short()+" is too"
           + " brittle to wind around the cord without"
           + " crumbling. You will need fresh herbs to make a"
           + " wreath.");
    }

    tmpstr = obs[0]->query_short();
    if (Nherbs > 0 &&
	tmpstr != Herb_short)
    {
        NFN0("The cord is already wound with "+Herb_pshort+", and adding "
	   + LANG_ADDART(tmpstr)+ " now would spoil it. "
	   + "Either continue winding "+Herb_pshort
	   + " around the cord, or unwind the wreath and start over.");
    }

    if (Nherbs > MAX_HERBS)
    {
	NFN0("There is no room for more herbs on the cord.");
    }

    if (!Nherbs)
    {
	Herb_short = tmpstr;
	Herb_pshort = obs[0]->query_plural_short();
        if (!Herb_pshort)
        {
            Herb_pshort = LANG_PWORD(Herb_short);
        }
	if (!sscanf(Herb_pshort, "handfuls of %s", Herb_desc))
	{
	    Herb_desc = Herb_pshort;
	}
	if ((tmpstr = obs[0]->query_herb_name()) == "sumac" ||
	    tmpstr == "poison ivy")
	{
	    Itches = 1;
	}
    }
    write(BSN("You carefully wind the "+Herb_short+" around the leather"
       +" cord."));
    SAY(" winds some herbs around a leather cord.");
    ++Nherbs;

    /*
     * move each herb to TO as it's wound so that it continues to dry
     * and we do not provide free rejuvenation.  we'll just crumble a 
     * dried (or decayed) herb when it's unwound
     * N.B. since i forcibly move the herbs into the cord, which is not
     * a container, the player's weight will not include the weight
     * of the wound herbs.  however, the weight of 10 - 20 leaves
     * or flowers isn't enough to worry about.
     */
    obs[0]->move(TO, 1);
    return 1;
} /* wind_herb */


/*
 * Function name:	unwind_herb
 * Description	:	handle player's attempts to unwind herbs from cord
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
unwind_herb(string arg)
{
    object	herb;

    if (!strlen(arg))
    {
        NFN0("What do you want to unwind?");
    }

    if (!parse_command(arg, ({}),
            "[the] [short] [leather] [herb] 'cord' / 'wreath' ") &&
        !parse_command(arg, all_inventory(TO),
            "%o 'from' [the] [short] [leather] [herb] 'cord' / 'wreath' ",
	    herb))
    {
        NFN0("Unwind what, the leather cord?");
    }

    if (Type != CORD_UNTIED)
    {
	NFN0("The cord has been tied into a "+Type_name+". "
	   + "You must untie it first.");
    }

    if (!Nherbs)
    {
        NFN0("Nothing is wound around the cord for you to remove.");
    }

    write(BSN("You carefully unwind the partially completed wreath,"
            + " removing the "+Herb_pshort+" from the leather cord."));
    SAY(" unwinds some herbs from a leather cord.");
    return_herbs();
    return 1;
} /* unwind_herb */


/*
 * Function name:	return_herbs
 * Description	:	return to player unwound herbs
 */
public void
return_herbs()
{
    object	env,
		*herbs;
    int		s,
		moved,		/* moved some herbs to player */
		crumbled; 	/* some herbs were dry */

    // Sanity check:
    if (!objectp(env = ENV(TO)))
    {
        remove_object();
        return;
    }
    herbs = all_inventory(TO);
    s = sizeof(herbs);

    /* return all non-dry herbs to the player */
    while ( s-- > 0 )
    {
	if (!herbs[s]->query_dried())
	{
            if (herbs[s]->move(env))
            {
                herbs[s]->move(env, 1);
	    }
	    ++moved;
        }
	else
	{
	    /* herb was dry, so it crumbles */
	    herbs[s]->remove_object();
	    ++crumbled;
	}
	--Nherbs;
    }
    if (crumbled > 0 ||
	Nherbs > 0)
    {
	/* some of our inventory was dried, or had already decayed */
	write(BSN((moved > 0 ? "Some of the " : "The ")+Herb_pshort
			     + " crumble as you unwind the cord."));
    }
    Nherbs = 0;
    Itches = 0;
    Herb_short = "herb";
    Herb_pshort = Herb_desc = "herbs";
} /* return_herbs */


/*
 * Function name:	tie_cord
 * Description	:	handle player's attempts to tie cord into wreath
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
tie_cord(string arg)
{
    string	tmpstr, which;

    if (!strlen(arg) ||
        !parse_command(arg, ({}),
	    " [the] [short] [leather] [herb] 'cord' / 'wreath'"
	  + " [together] %s", tmpstr))
    {
        NFN0("What do you want to tie?");
    }
    /* ok, they are referring to the cord .. now, which type? */
    if (!strlen(tmpstr) ||
	!parse_command(tmpstr, ({}), "'in' / 'into' [a] %s", which))
    {
	NFN0("The cord can be tied together into a necklace, a circlet "
	   + "or a bracelet.");
    }

    if (Type != CORD_UNTIED)
    {
	NFN0("The cord has already been tied into a "+Type_name+". ");
    }

    if (Nherbs < MIN_HERBS)
    {
	NFN0("There are not enough "+Herb_pshort+" wound around the cord"
	    + " to create a wreath.");
    }

    switch ( which )
    {
    case "necklace":
	Type = CORD_NECKLACE;
	set_at(A_NECK);
	break;
    case "circlet":
	Type = CORD_CIRCLET;
	set_at(A_HEAD);
	break;
    case "bracelet":
	Type = CORD_BRACELET;
	set_at(A_R_WRIST);
	break;
    default:
	NFN0("The cord can be tied together into a necklace, a circlet "
	   + "or a bracelet.");
	/* no break needed -- NFN0 returns 0 */
    }

    set_name(which);
    set_pname(which+"s");
    Type_name = which;
    set_short(Type_name+" of "+Herb_desc);
    set_pshort(Type_name+"s of "+Herb_desc);
    write(BSN("You coil the leather cord around and tie it in a wreath, "
	+ "forming a "+Type_name+" of "+Herb_desc+"."));
    SAY(" ties a leather cord wound with "+Herb_desc+" into a "
      + Type_name+".");
    return 1;
} /* tie_cord */


/*
 * Function name:	untie_cord
 * Description	:	handle player's attempts to untie wreath
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
untie_cord(string arg)
{
    string	desc;
    object	ob;

    if (!strlen(arg) ||
        !parse_command(arg, ({ TO }), "%o", ob))
    {
        NFN0("What do you want to untie?");
    }

    if (Type == CORD_UNTIED)
    {
	NF0("The cord is not tied.\n");
    }

    if (objectp(query_worn()))
    {
	NF0("You must remove the "+arg+" before untying it.\n");
    }

    Type = CORD_UNTIED;
    desc = short();
    write("You untie the "+desc+".\n");
    SAY(" unties the "+desc+".");
    remove_name(Type_name);
    remove_pname(Type_name+"s");
    Type_name = "cord";
    set_name("cord");
    set_pname("cords");
    set_short("leather cord");
    set_pshort("leather cords");
    return 1;
} /* untie_cord */


/*
 * Function name:	wear_me
 * Description	:	handle attempts to wear cord
 * Returns	:	1 on success, err msg on failure
 */
public mixed
wear_me()
{
    mixed	rval;
    object	tp, poison;
    string	body_part;

    if (Type == CORD_UNTIED)
    {
	return "The cord must be tied together before you"
	     + " can wear it.\n";
    }

    tp = TP;
    switch (Type)
    {
    case CORD_BRACELET:
	/* fake A_EITHER_WRIST*/
	if (tp->query_armour(A_R_WRIST) == 0)
	{
            set_at(A_R_WRIST);
	    body_part = "right wrist";
	}
	else if (tp->query_armour(A_L_WRIST) == 0)
	{
            set_at(A_L_WRIST);
	    body_part = "left wrist";
	}
	break;
    case CORD_NECKLACE:
	body_part = "neck";
	break;
    case CORD_CIRCLET:
	body_part = "scalp";
	break;
    }

    rval = ::wear_me();

    if (Itches &&
	intp(rval) &&
	rval &&
	ENV() == tp)
    {
	/* if they can wear the wreath, then they're not wearing
	 * anything else on the relevant location to protect
	 * them from the poison.
	 * the poison ob will check for dups.
	 */
	FIX_EUID;
	poison = clone_object(ITCH_POISON_FILE);
	poison->set_body_part(body_part);
	poison->move(tp, 1);
	poison->start_poison();
    }
    return rval;
} /* wear_me */

/*
 * Function name:	enter_env
 * Description	:	entering new env -- add poison if wreath
 *			is itchy and player not wearing gloves
 * Arguments	:	object dest -- the new environment
 *			object from -- the old environment
 */
public void
enter_env(object dest, object from)
{
    object	poison;
    int		bare_rhand;

    ::enter_env(dest, from);
    if (Itches &&
        ENV() == dest &&
	living(dest) &&
	((bare_rhand = !objectp(dest->query_armour(A_R_HAND))) ||
	 !objectp(dest->query_armour(A_L_HAND))))
    {
	/* handling the wreath and one or both hands ungloved */
	FIX_EUID;
	poison = clone_object(ITCH_POISON_FILE);
	if (bare_rhand)
	{
	    poison->set_body_part("right hand");
	}
	else
	{
	    poison->set_body_part("left hand");
	}
	poison->move(dest, 1);
	poison->start_poison();
    }
} /* enter_env */


/*
 * Function name:	query_value
 * Description	:	compute value of cord based on herbs
 * Returns	:	int -- the value
 */
public int
query_value()
{
    object	*herbs;
    int		s, value = CORD_VALUE;

    herbs = filter(all_inventory(TO), not @ &->query_dried());
    s = sizeof(herbs);
    if (s)
    {
	/* if herbalist has a good stock, only pays half value
	 * so do the same here.  it's still generous, since
	 * normally an ordinary shop won't buy herbs at all.
	 */
	value += ((herbs[0]->query_herb_value()/2) * s);
    }
    return value;
} /* query_value */

query_itches() { return Itches; }
