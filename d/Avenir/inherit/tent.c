#pragma strict_types
// Tent
// creator(s):   Zielia 2007
// last update:
// purpose:      Fun tent players can carry around for roleplay.
// note:         some base code from Krynn army tents by Aridor
// bug(s):
// to-do:
/*
 *
 * For customized tents, after inheriting this file, mask these functions:
 *
 ** desc_packed_short    = Packed short description. (bundled)
 ** desc_unpacked_short  = Unpacked short description. (tent)
 *
 ** desc_packed          = Long description, packed. (bundled)
 ** desc_unpacked_open   = Long description, unpacked & unlaced. (tent)
 ** desc_unpacked_closed = Long description, unpacked & laced. (tent)
 ** desc_illuminated     = Extra long description if emitting light. (tent)
 *
 * All desc_ functions should return a string.
 * All desc_ functions take 1 or 2 arguments, see function for details.
 *
 ** hook_tent_packed     = Called after packing.
 ** hook_tent_unpacked   = Called after unpacking.
 ** hook_tent_entered    = Called after entering unpacked tent.
 *
 * All hook_ functions should not return anything.
 *
 */
inherit "/std/object";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <options.h>

#include "/d/Avenir/include/basic.h"

#define DEFAULT_INSIDE  "/d/Avenir/inherit/tent_inside"

private static object tent_inside;
public static string inside_room = "";
public static int lacing, unlacing, unpacked, closed, prop_locked;

public void
hook_tent_packed(void)
{
    /* Put extra code here for after a tent is unpacked. */
    add_name("bundle");
}

public void
hook_tent_unpacked(void)
{
    /* Put extra code here for after a tent is unpacked. */
    remove_name("bundle");
}

public void
hook_tent_entered(void)
{
    /* Put extra code here for after a tent is entered. */
}

public object
query_tent_inside(void)		{ return tent_inside;	}

public void
set_inside_room(string str)	{ inside_room = str;	}

public string
query_inside_room(void)		{ return inside_room;	}

public void
set_closed(int num)		{ closed = num;		}

public int
query_closed(void)		{ return closed;	}

public int
query_lacing(void)		{ return lacing;	}

public int
query_unlacing(void)		{ return unlacing;	}

public nomask int
filter_syb_tent(void)		{ return 1;		}

/*
 * Trap magical darkness inside the tent.
 * If there is light inside the tent, radiate 'light / 2'.
 */
private int
tent_light(void)
{
    if (!objectp(tent_inside))
	return 0;

    /* Tent has to be brighter than room in order to emit light. */
    int val = tent_inside->query_internal_light() - 
	      environment()->query_prop(ROOM_I_LIGHT);

    return max(0, (val > 1 ? val / 2 : val));
}

private int
tent_volume(void)	{ return (unpacked ? 8000000 : 5000);	}

private int
tent_no_get(void)	{ return unpacked;			}

public string
desc_packed_short(object viewer)
{
    return "small tent bundle";
}

public string
desc_unpacked_short(object viewer)
{
    return "small camping tent";
}

public nomask varargs string
short(object viewer)
{
    if (unpacked)
	return desc_unpacked_short(viewer);
    else
	return desc_packed_short(viewer);
}

public string
desc_packed(object viewer)
{
    return "It is a small tent made of thin, lightweight, "+
	"silk designed to be easily packed up and carried for camping.";
}

public string
desc_unpacked_open(object viewer)
{
    return "This is a small bundle of a thin, white silk which "+
	"may be set up into a tent. At the front tent is an opening "+
	"through which you could enter and a flap of silk which "+
	"could be laced shut to prevent wandering creatures from "+
	"entering or for privacy.";
}

public string
desc_unpacked_closed(object viewer)
{
    return "This is a small bundle of a thin, white silk which "+
	"may be set up into a tent. At the front of the tent, a "+
	"flap of silk covers an opening through which you could "+
	"enter, however, it is currently laced closed.";
}

public string
desc_illuminated(object viewer, int size)
{
    if (size)
    {
	return " The thin silk glows with light from "+
	    "within the tent, illuminating the sillhouettes "+
	    "of the "+ LANG_NUM2WORD(size) +
	    (size == 1 ? " figure" : " figures") +" inside.";
    }
    else
    {
	return " The thin silk glows with light from "+
	    "within the tent.";
    }
}

public nomask varargs string
long(string str, object viewer)
{
    if (strlen(str))
	return ::long(str, viewer);

    if (!unpacked)
	str = desc_packed(viewer);
    else if (!closed)
	str = desc_unpacked_open(viewer);
    else
	str = desc_unpacked_closed(viewer);

    if (tent_light())
    {
	object *obs = filter(all_inventory(tent_inside), living);
	int size = sizeof(obs);

	str += desc_illuminated(viewer, size);
    }

    return str +"\n";
}

/*
 * Block functions disabling setting of calculated properties
 */
public nomask int add_prop_obj_i_light(void)      { return prop_locked; }
public nomask int add_prop_obj_i_volume(void)     { return prop_locked; }
public nomask int add_prop_obj_m_no_get(void)     { return prop_locked; }
public nomask int remove_prop_obj_i_light(void)   { return 1; }
public nomask int remove_prop_obj_i_volume(void)  { return 1; }
public nomask int remove_prop_obj_m_no_get(void)  { return 1; }

public void
create_tent(void)
{
    /* Default / Sample tent. */

    set_adj(({"silk","white","camping","small"}));
}

static nomask void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("tent");
    add_name("bundle");

    prop_locked = 0;
    add_prop(CONT_I_CLOSED, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GET,  tent_no_get);
    add_prop(OBJ_I_LIGHT,   tent_light);
    add_prop(OBJ_I_VOLUME,  tent_volume);
    add_prop(OBJ_I_WEIGHT,  5000);
    add_prop(OBJ_I_VALUE,   1000);
    prop_locked = 1;

    set_inside_room(DEFAULT_INSIDE);

    create_tent();

    /* Override these. */
    set_long(0);
    set_short(0);
    set_pshort(0);
}

/*
 * It takes some time to lace and unlace the tent flap so that people
 * inside the tent can have some forewarning of someone coming, but
 * the tents are always accessible and can't be used for escaping
 * combat and whatnot.
 */

public void
syb_tent_close(int count, object tp, object here)
{
    if (!tp)
    {
        lacing = 0;
        return;
    }
    if (!here)
    {
        lacing = 0;
        return;
    }
    if (!present(tp, here))
    {
		lacing = 0;
        return;
    }

    object other = (here == ENV(TO) ? tent_inside : ENV(TO));
    string where = (here == ENV(TO) ? "outside" : "inside");

    switch(count++)
    {
    case 0:
	tp->catch_tell("You begin lacing up the tent flap.\n");
	tell_room(here, QCTNAME(tp) +" begins lacing up the tent flap.\n", 
	  tp, tp);	
	tell_room(other, "The tent flap rustles as someone begins lacing "+
	  "it up from "+ where +".\n", 0, other);
	break;
    case 1:
	tp->catch_tell("You continue lacing up the tent flap. "+
	  "You are nearly a third done.\n");
	tell_room(here, QCTNAME(tp) +" continues lacing up the tent flap. "+
	  CAP(HE(tp)) +" is nearly a third done.\n", tp, tp);	    
	tell_room(other, "The tent flap rustles as someone continues "+
	  "lacing it up from "+ where +".\n", 0, other);
	break;
    case 2:
	tp->catch_tell("You continue lacing up the tent flap. "+
	  "You are nearly two thirds done.\n");
	tell_room(here, QCTNAME(tp) +" continues lacing up the tent flap. "+
	  CAP(HE(tp)) +" is nearly two thirds done.\n", tp, tp);	    
	tell_room(other, "The tent flap rustles as someone continues "+
	  "lacing it up from "+ where +". It is nearly closed.\n", 0, other);
	break; 
    case 3:
	tp->catch_tell("You finish lacing up the tent flap "+
	  "and tie it securely closed.\n");
	tell_room(here, QCTNAME(tp) +" finishes lacing up the tent flap "+
	  "and ties it securely closed.\n", tp, tp);	    
	tell_room(other, "The tent flap becomes still once more as "+
	  "the person "+ where +" finishes tying it closed.\n", 0, other);
	set_closed(1);
	break;   
    }

    if (count < 4)
	lacing = set_alarm(5.0, 0.0, &syb_tent_close(count, tp, here));
    else
	lacing = 0;
}

/*
 * Called by f_unlace() from any valid sybarun tent.
 */
public int
lace_syb_tent(object here)
{
    if (lacing)
    {
	write("Someone is already lacing the flap.\n");
	return 1;
    }    

    if (unlacing)
    {
	write("You cannot lace the flap while someone is unlacing it.\n");
	return 1;
    }     

    if (closed)
    {
	write("The flap on the "+ short() +" is already laced closed.\n");
	return 1;
    }

    syb_tent_close(0, TP, here);
    return 1;
}

public nomask int
f_lace(string str)
{
    if (!unpacked)
    {
	notify_fail("What?\n");
	return 0;
    }  

    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) +" what?\n");
	return 0;
    }  

    object tent, *obs = all_inventory(ENV(TP));
    obs = filter(obs, filter_syb_tent);

    if (!parse_command(str, obs, "[the] %o [flap]", tent))
    {
	notify_fail(CAP(query_verb()) + " up a tent flap maybe?\n");
	return 0;
    }

    return tent->lace_syb_tent(ENV(TO));
}

public void
syb_tent_open(int count, object tp, object here)
{
    if (!tp)
    {
        unlacing = 0;
        return;
    }
    if (!here)
    {
        unlacing = 0;
        return;
    }
    if (!present(tp, here))
    {
    	unlacing = 0;
    	return;
    }

    object other = (here == ENV(TO) ? tent_inside : ENV(TO));
    string where = (here == ENV(TO) ? "outside" : "inside");

    switch(count++)
    {
    case 0:
	tp->catch_tell("You untie the cord and begin unlacing the tent "+
	  "flap.\n");
	tell_room(here, QCTNAME(tp) +" unties the cord and begins "+
	  "unlacing the tent flap.\n", tp, tp);	
	tell_room(other, "The tent flap rustles as someone begins "+
	  "unlacing it from "+ where +".\n", 0, other);
	break;
    case 1:
	tp->catch_tell("You continue unlacing the tent flap. "+
	  "You are nearly a third done.\n");
	tell_room(here, QCTNAME(tp) +" continues unlacing the tent flap. "+
	  CAP(HE(tp)) +" is nearly a third done.\n", tp, tp);	    
	tell_room(other, "The tent flap rustles as someone continues "+
	  "unlacing it from "+ where +".\n", 0, other);
	break;
    case 2:
	tp->catch_tell("You continue unlacing the tent flap. "+
	  "You are nearly two thirds done.\n");
	tell_room(here, QCTNAME(tp) +" continues unlacing the tent flap. "+
	  CAP(HE(tp)) +" is nearly two thirds done.\n", tp, tp);	    
	tell_room(other, "The tent flap rustles as someone continues "+
	  "unlacing it from "+ where +". It is nearly open.\n", 0, other);
	break; 
    case 3:
	tp->catch_tell("You finish unlacing the tent flap.\n");
	tell_room(here, QCTNAME(tp) +" finishes unlacing the tent flap.\n", 
	  tp, tp);	    
	tell_room(other, "The tent flap becomes still once more as "+
	  "the person "+ where +" finishes unlacing it.\n", 0, other);
	set_closed(0);
	break;   
    }

    if (count < 4)
	unlacing = set_alarm(5.0, 0.0, &syb_tent_open(count, tp, here));
    else
	unlacing = 0;
} 

/*
 * Called by f_unlace() from any valid sybarun tent.
 */
public int
unlace_syb_tent(object here)
{
    if (unlacing)
    {
	write("Someone is already unlacing the flap.\n");
	return 1;
    }    

    if (lacing)
    {
	write("You cannot unlace the flap while someone is lacing it.\n");
	return 1;
    } 

    if (!closed)
    {
	write("The flap on the "+ short() +" is already unlaced.\n");
	return 1;
    }

    syb_tent_open(0, TP, here);
    return 1;
}

public nomask int
f_unlace(string str)
{   
    if (!unpacked)
    {
	notify_fail("What?\n");
	return 0;
    } 

    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) +" what?\n");
	return 0;
    }

    object tent, *obs = all_inventory(ENV(TP));
    obs = filter(obs, filter_syb_tent);

    if (!parse_command(str, obs, "[the] %o [flap]", tent))
    {
	notify_fail(CAP(query_verb()) + " up a tent flap maybe?\n");
	return 0;
    }

    return tent->unlace_syb_tent(ENV(TO));
}

/*
 * Called by f_pack() from any valid sybarun tent.
 */
public int
pack_syb_tent(void)
{
    if (!unpacked)
    {
	write("The "+ short() +" is already packed up.\n");
	return 1;
    }

    if (objectp(tent_inside) && sizeof(all_inventory(tent_inside)))
    {
	write("There is still someone or something inside the tent. " +
	    "You can't pack it that way.\n");
	return 1;
    }

    if (lacing)
    {
	write("Wait until the tent flap is finished being laced.\n");
	return 1;
    }

    if (unlacing)
    {
	write("Wait until the tent flap is finished being unlaced.\n");
	return 1;
    }

    write("You pack up the "+ short() +
	" and roll it into a compact bundle.\n");
    say(QCTNAME(TP) + " packs up the "+ short() +
	" and rolls it into a compact bundle.\n");

    tent_inside->remove_object();
    tent_inside = 0;

    unpacked = 0;
    set_short(0);

    /* For extra stuff. */
    hook_tent_packed();
    return 1;
}

public nomask int
f_pack(string str)
{
    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) + " what?\n");
	return 0;
    }

    object tent, *obs = all_inventory(ENV(TP));
    obs = filter(obs, filter_syb_tent);

    if (!parse_command(str, obs, "[up] [the] %o", tent))
    {
	notify_fail(CAP(query_verb()) + " up a tent maybe?\n");
	return 0;
    }

    return tent->pack_syb_tent();
}

/*
 * Called by f_unpack() from any valid sybarun tent.
 */
public int
unpack_syb_tent(void)
{
    if (unpacked)
    {
	write("The "+ short() +" is already unpacked.\n");
	return 1;
    }

    /* Just to make sure. */
    if (ENV(TO) != ENV(TP))
    {
	if (move(ENV(TP)))
	    move(ENV(TP), 1);
    }

    write("You roll out the "+ short() +
	" and set it up into a tent.\n");
    say(QCTNAME(TP) + " rolls out "+ LANG_ADDART(short()) +
	" and sets it up into a tent.\n");

    unpacked = 1;
    set_short(0);

    tent_inside = clone_object(inside_room);
    tent_inside->set_tent_outside(TO);

    /* For extra stuff. */
    hook_tent_unpacked();
    return 1;
}

public nomask int
f_unpack(string str)
{
    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) + " what?\n");
	return 0;
    }

    object tent, *obs = all_inventory(TP);
    obs += all_inventory(ENV(TP));
    obs  = filter(obs, filter_syb_tent);

    if (!parse_command(str, obs, "[a] / [up] [the] %o", tent))
    {
	notify_fail(CAP(query_verb()) + " a tent maybe?\n");
	return 0;
    }

    if (ENV(TP)->query_syb_tent())
    {
	write("Setting up a tent inside a tent!?\n");
	return 1;
    }

    switch(ENV(TP)->query_prop(ROOM_I_TYPE))
    {
    case ROOM_IN_AIR:
    case ROOM_IN_WATER:
    case ROOM_UNDER_WATER:
	write("This is not an appropriate environment "+
	    "to set up a tent!\n");
	return 1;
    }

    return tent->unpack_syb_tent();
}

/*
 * Called by f_enter() from any valid sybarun tent.
 */
public int
enter_syb_tent(string dir)
{
    if (!unpacked)
    {
	write("How do you propose to enter the "+ short() +"?\n");
	return 1;
    }

    if (!objectp(tent_inside))
    {
	write("The entrance seems blocked!\n"+
	    "It is impossible to enter the tent.\n");
	return 1;
    }

    if (closed)
    {
	write("The flap on the "+ short() +" is laced closed.\n"+
	   "You'll need to unlace it first.\n");
	return 1;    
    }
    
    if (TP->query_option(OPT_BLOCK_INTIMATE))
    {
        write("You decide against entering the tent.\n");
        return 1;
    }

    ENV(TO)->set_dircmd(dir);
    TP->move_living("into the tent", tent_inside);

    /* For extra stuff. */
    hook_tent_entered();
    return 1;
}

public nomask int
f_enter(string str)
{
    if (!strlen(str))
    {
	notify_fail(CAP(query_verb()) +" what?\n");
	return 0;
    }

    object tent, *obs = all_inventory(ENV(TP));
    obs = filter(obs, filter_syb_tent);

    if (!parse_command(str, obs, "[up] [the] %o", tent))
    {
	notify_fail(CAP(query_verb()) + " up a tent maybe?\n");
	return 0;
    }

    return tent->enter_syb_tent(str);
}

/* Make sure to cleanup the inside room. */
public void
remove_object(void)
{
    remove_alarm(lacing);
    remove_alarm(unlacing);

    tent_inside->remove_object();
    ::remove_object();
}

public void
init(void)
{
    ::init();

    if (ENV(TP) == ENV(TO))
    {
	/* Can't do these when packed. */
	add_action(   f_lace, "lace"   );
	add_action(   f_lace, "close"  );
	add_action( f_unlace, "unlace" );
	add_action( f_unlace, "open"   );    
	add_action(   f_pack, "pack"   );
	add_action(  f_enter, "enter"  );
    }

    /* Available packed or unpacked. */
    add_action( f_unpack, "unpack" );
    add_action( f_unpack, "setup" );
    add_action( f_unpack, "set" );

    if (unpacked)
    {
	/* Let those inside know people are walking around. */
	tell_room(tent_inside,
	    "You hear a rustling outside the tent.\n",
	    0, tent_inside);
    }
}
