/*
 * - cage.c
 *
 * A cage for pets.
 *
 * Revised to remove all "push" code as it was a massive
 * abuse potential for mortals. It's impossible to safely
 * and properly have push code in the mortal realms.
 *
 */
#pragma strict_types

inherit "/std/object";

#include <zigg.h>
#include <macros.h>
#include <stdproperties.h>

#define SHADOW  (ZIG_OBJ + "cage_sh")

private static int open;
private static object pet;

public void
reset_cage(void)	{ pet = 0; }

public object
query_pet(void)		{ return pet; } 

public int
query_no_get(void)	{ return objectp(pet); }

private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name(({ "cage", "zigg::cage" }), 1);
    set_pname(({ "cages" }));
    set_adj(({ "large", "gilded", "bell" }));
    set_short("large gilded bell-cage");
    set_pshort("large gilded bell-cages");
    set_long("It is a large rounded cage, shaped like a bell. The "+
	"interior is fairly ample, enough to provide the occupant room "+
	"to stand and move around to a limited degree. The entire cage "+
	"is a metallic steel-gray in colour and manufactured from "+
	"beryllium in order to be very light and yet extremely strong "+
	"and rigid. It has a raised floor with a layer of white, "+
	"cushioned padding on top. The edge of the padding is fringed "+
	"and hangs outside the bars to give it a modicum of dressing. "+
	"The bars themselves are fairly plain at the bottom but become "+
	"increasingly gilded towards the cental apex. The door of the "+
	"cage is seemlessly inline with the flow of the bars and "+
	"gilding, so as not to overly mar its appearance. The lock upon "+
	"the door is sealed and self-contained, with inner mechanisms "+
	"to make it self-latching as well when it closes.\n");

    add_item(({"padding", "cushion", "white padding"}),
	"The white, cushioned padding is thick and fringed, appearing to "+
	"be made of fine-spun sheeps wool.\n");

    add_item(({"bars", "gilding", "gilded bars"}),
	"The steel-gray bars are plain at the base but increasingly "+
	"gilded as they reach the apex. The gilding consists mainly "+
	"of delicate and growingly exaggerated curlicues that then span "+
	"the entire upper portion of the bell-shaped cage.\n");

    add_item(({"door", "inline door"}),
	"The door is seemlessly integrated with the rest of the cage's "+
	"construction, its gilding a match of that with the bars around "+
	"it and is only really visible as a door because of the locking "+
	"mechanism.\n");

    add_item(({"lock", "locking mechanism"}),
	"The lock is square with a small keyhole and a bit of metallic "+
	"flange outlining it to make it difficult to access from within "+
	"the cage. The mechanism allows the cage to self-latch when the "+
	"door is shut.\n");

    add_prop(OBJ_I_VALUE,  25000);
    add_prop(OBJ_I_WEIGHT, 23000);
    add_prop(OBJ_I_VOLUME, 50000);
    add_prop(OBJ_I_NO_SELL,    1);
    add_prop(OBJ_M_NO_GET, query_no_get);
	
	if (IS_CLONE)
      set_item_expiration();  	


//    opps = "/secure/master"->query_move_opposites();
}

public varargs string
real_short(object for_obj)	{ return ::short(for_obj); }

/*
 * Pseudo-exit the cage.
 */
public int
f_exit(string str)
{
    if (pet != TP)
	return 0;

    if ((str != "cage") && (str != "the cage"))
	return NF("Exit what?\n");

    if (!open)
    {
	write("The "+ real_short(TP) +" is closed.\n");
	return 1;
    }

    write("You exit the "+ real_short(TP) +".\n");
    say(QCTNAME(TP) +" exits the "+ real_short() +".\n");

    pet = 0;

    /* Shadow removal handles cleanup. */
    TP->remove_cage_shadow();
    return 1;
}

/*
 * Pseudo-enter the cage.
 */
public int
f_enter(string str)
{
    object sh;

    if (pet == TP)
	return 0;

    if ((str != "cage") && (str != "the cage"))
	return NF("Enter what?\n");

    if (!present(TO, environment(TP)))
    {
	write("Just how do you propose to do that?\n");
	return 1;
    }

    if (!open)
    {
	write("The cage is closed.\n");
	return 1;
    }

    if (objectp(pet))
    {
	write("There is only enough room in the cage for one.\n");
	return 1;
    }

    if (!objectp(sh = clone_object(SHADOW)))
    {
	write("You approach the cage, but a malicious shadow stops you.\n");
	return 1;
    }

    if (!sh->shadow_me(TP))
    {
	write("The cage's opening seems to shrink as you approach, "+
	    "barring your entrance.\n");
	
	sh->remove_shadow();
	return 1;
    }

    write("You enter the "+ real_short(TP) +".\n");
    say(QCTNAME(TP) +" enters the "+ real_short() +".\n");

    pet = TP;
    sh->set_cage_object(TO);

    return 1;
}

/*
 * Unlock and open the cage.
 */
public int
f_open(string str)
{
    object key;

    if ((str != "cage") && (str != "the cage"))
	return NF("Open what?\n");

    if (open)
    {
	write("The "+ real_short() +" is already open.\n");
	return 1;
    }

    if (TP == pet)
    {
	write("You cannot reach the latch to open the door.\n");
	return 1;
    }

    write("You unlatch the "+ real_short() +" and swing open its door.\n");
    say(QCTNAME(TP) +" unlatches the "+ real_short() +
	" and swings open its door.\n");

    /* Toggle status. */
    open = !open;
    return 1;
}

/*
 * Close and lock the cage.
 */
public int
f_close(string str)
{
    if ((str != "cage") && (str != "the cage"))
	return NF("Close what?\n");

    if (!open)
    {
	write("The "+ real_short() +" is already closed.\n");
	return 1;
    }

    /*
     * The cage is self-latching, so no key needed to close.
     */

    write("You swing the cage door closed and hear the 'snict' "+
	"sound of the lock catching.\n");
    say(QCTNAME(TP) +" swings shut the cage door and you hear the "+
	"sound of the lock catching.\n");

    /* Toggle status. */
    open = !open;
    return 1; 
}

public void
init(void)
{
    ::init();

    add_action(  f_open, "open"  );
    add_action(  f_exit, "exit"  );
    add_action( f_close, "close" );
    add_action( f_enter, "enter" );
}

/*
 * Masked to mimic a receptacle.
 */
public varargs string
short(object for_obj)
{
    string desc = real_short(for_obj);

    if (objectp(pet))
    {
	desc += " with ";

	if (pet == TP)
	    desc += "you";
	else
	    desc += pet->query_the_name(TP);

	desc += " inside";
    }

    if (open)
	desc += " (open)";

    return desc;
}

/*
 * Modified to show a pet.
 */
public varargs string
long(string str, object for_obj)
{
    string desc = "";

    if (objectp(pet) && (pet != TP) && !strlen(str))
    {
	desc += "Inside the "+ (open ? "open" : "closed") +
	    " cage is "+ pet->query_the_name(TP) + ".\n";
    }

    return ::long(str, for_obj) + desc;
}

/*
 * If we have a pet, make sure to free them.
 */
public void
remove_object(void)
{
    pet->remove_cage_shadow();
    ::remove_object();
}


public string
query_recover(void)
{
    return MASTER + ":" + query_item_expiration_recover(); 
}

public void
init_recover(string arg)
{
    init_item_expiration_recover(arg);
}
