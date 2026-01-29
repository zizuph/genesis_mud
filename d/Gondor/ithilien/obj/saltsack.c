/*
 * /d/Gondor/ithilien/obj/saltsack.c
 *
 * Coded by Elessar.
 *
 * Modification log:
 * 30-Dec-1997, Gnadnar: general revision
 *
 */

#pragma strict_types

inherit "/std/object";

#include "/d/Gondor/defs.h"
#include <stdproperties.h>


#define	SALT	(ITH_DIR + "obj/salt")

public int	mess_with(string arg);

public void
create_object()
{
    set_name("sack");
    add_name("saltsack");
    add_name("sack of salt");
    set_short("open grey sack full of salt");
    set_adj("open");
    set_adj("grey");
    set_adj("full");
    set_adj("salt");
    set_long(BSN("The grey sack seems to have been torn open. "+
	"It is full of salt."));
    add_prop(OBJ_M_NO_GET,
	"The sack full of salt is too heavy. You cannot pick it up.\n");
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME,  20000);
}

public void
init()
{
    ::init();
    add_action(mess_with, "tear");
    add_action(mess_with, "open");
    add_action(mess_with, "close");
    add_action(mess_with, "put");
    add_action(mess_with, "take");
    add_action(mess_with, "get");
}

public int
mess_with(string arg)
{
    string	tmp1, vb = query_verb();
    object	ob;

    if ( !strlen(arg) )
	return 0;

    arg = LOW(arg);
    if ( sscanf(arg, "the %s", tmp1) )
	arg = tmp1;
    switch(vb)
    {
    case "tear":
    case "open":
	if ( arg == "sack" || arg == "saltsack" || arg == "sack of salt" )
	{
	    write("The sack already is open.\n");
	    return 1;
	}
	break;
    case "close":
	if ( arg == "sack" || arg == "saltsack" || arg == "sack of salt" )
	{
	    write("The sack has been torn open; it cannot be closed.\n");
	    return 1;
	}
	break;
    case "put":
	if ( parse_command(arg, all_inventory(TP), "%o 'in' [the] [open] %s",
	  ob, tmp1) &&
	( tmp1 == "sack" || tmp1 == "saltsack" || tmp1 == "sack of salt" ) )
	{
	    if ( ob->id("salt") )
	    {
		ob->remove_object();
		write("You put the salt in the sack.\n");
	    }
	    else
		write("The sack is completely full of salt.\n");
	    return 1;
	}
	break;
    case "get":
    case "take":
	/* this is the quest stuff -- be generous in parsing */
	if ( arg == "salt" || arg == "pinch" ||
	parse_command(arg, ({ }),
            "[pinch] [of] 'salt' [from] [the] [open] [sack]") )
	{
	    FIX_EUID;
	    clone_object(SALT)->move(TP);
	    write("You take a pinch of salt out of the sack.\n");
	    SAY(" takes something out of a sack.");
	    return 1;
	}
	break;
    }
    NF0(capitalize(vb)+" what?\n");
}
