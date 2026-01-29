/*
 *	/d/Gondor/guilds/bnumen/obj/horn.c
 *
 *	Olorin, 31-Jan-1997
 *
 *	Copyright (c) 1997 by Christian Markus
 *
 *	Modification log:
 */
#pragma strict_types

inherit "/std/object.c";
inherit "/lib/keep.c";
inherit "/d/Gondor/common/lib/tell_funcs.c";

#include <cmdparse.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define HIS(x)		(x)->query_possessive()

public string  exa_letters(string what);
public string  long_desc();

static string  House;

public string
check_sell()
{
    if (strlen(House))
	return "You are not permitted to sell an heirloom of the " +
	       "House of " + House + ".\n";
    else
	return 0;
}

public string
check_give()
{
    if (strlen(House))
    {
	if (House == TP->query_bnumen_house())
	    return 0;
	else
	    return 0;
    }
    return 0;
}

public string
check_drop()
{
    if (query_verb() == "give")
	return check_give();
    if (strlen(House))
	return "You are not permitted to drop " +
	    "an heirloom of the House of " + House + ".\n";
    else
	return 0;
}

public void
create_object()
{
    set_name("horn");
    set_name("hunting-horn");
    add_name("_bnumen_horn");
    set_adj("ivory");
    set_adj("silver-clad");
    set_short("silver-clad ivory horn");
    set_long(long_desc);

    add_item( "script" , &exa_letters("script"));
    add_item( "letters", &exa_letters("letters"));

    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE,  864);

    add_prop(OBJ_M_NO_SELL,  check_sell);
    add_prop(OBJ_M_NO_GIVE,  check_give);
    add_prop(OBJ_M_NO_DROP,  check_drop);

    FIX_EUID;
}

public int
blow_horn(string str)
{
    int		s;
    object	tp = TP,
	   	*targets,
           	*players = ({ });

    if ((!strlen(str)) ||
	(!parse_command(LOW(str), all_inventory(tp), "%i", targets)) ||
	!(s = sizeof(targets = NORMAL_ACCESS(targets, 0, 0))))
    {
        NFN0(CAP(query_verb()) +" what?");
    }
    if (s > 1)
    {
	NFN0("You can only blow one thing at a time.");
    }
    if (targets[0] != TO)
    {
	return 0;
    }

    write("You breathe deeply, and blow the horn.\n"
        + "You produce a deep and mighty, bellowing sound!\n");
    say(QCTNAME(tp)+" blows into "+HIS(tp)+" horn, and produces a mighty sound!\n", tp);

    if (ENV(tp)->query_prop(ROOM_I_INSIDE))
        return 1;

    players  = tell_next_room_with_dir(ENV(tp),
        "You hear the sound of a mighty horn from");
    players += tell_players_in_same_subdir(tp,
        "The sound of a hunting horn echoes through the area.\n",
	0, players);
    if (House == tp->query_bnumen_house())
    filter(users() - players - ({ tp }), &operator(==)(House) @ 
	   &->query_bnumen_house())->catch_tell("From afar, you hear " +
	   "the sound of a mighty horn.\n");
						
    return 1;
}

public void
init_arg(string arg)
{
    sscanf(arg, "#DH#%s#DH#", House);
}

public string
query_auto_load()
{
    if (strlen(House) && (ENV(TO)->query_bnumen_house() == House))
	return MASTER + ":" + "#DH#" + House + "#DH#";
    return 0;
}

public void
init()
{
    ::init();

    add_action(blow_horn, "blow");
    add_action(blow_horn, "play");
    add_action(blow_horn, "wind");

    if (!strlen(House) && interactive(TP))
	House = TP->query_bnumen_house();
}

public string
long_desc()
{
    string  desc = 
	    "This ivory horn is from the great Kine of Araw. Silver is clad "
      + "around it in intricate patterns, and the horn has been hollowed out "
      + "to make it possible to blow in it, and produce a strong sound.";

    if (strlen(House))
    {
	   switch (TP->query_skill(SS_LANGUAGE))
	   {
          case 0..10:
	         break;
          case 11..20:
	         desc += " Within the pattern are letters in an elvish script.";
	         break;
          case 21..100:
            desc += " Within the pattern are letters in an elvish script."
                 +  " They read \"" + House + "\".";
            break;
       }
    }

    return desc;
}

public string
exa_letters(string what)
{
    string  desc = "You find no "+what+".\n";

    if (strlen(House))
    {
	   switch (TP->query_skill(SS_LANGUAGE))
	   {
	      case 0..10:
	         break;
	      case 11..20:
	         desc = "The letters are cleverly integrated into the "
		         +  "intricate pattern etched into the silver clad "
		         +  "around the horn, but you are unable to read "
		         +  "the elvish script.";
	         break;
	      case 21..100:
	         desc = "The letters are cleverly integrated into the "
		         +  "intricate pattern etched into the silver clad "
		         +  "around the horn. You can make out that they "
		         +  "read \"" + House + "\".";
	      break;
	   }
    }

    return desc;
}

/*
 * Function name: move
 * Description:   We permit moving only to another member of the House.
 * Argument:      see move() in /std/object.c
 * Returns:       see move() in /std/object.c
 *                error code 11 if it is attempted to give it to someone
 *                who is not a member of the House.
 * Bogus code in this function <snip> from sman move;
 * Returns:       Result code of move:
                  0: Success.
                  1: To heavy for destination.
                  2: Can't be dropped.
                  3: Can't take it out of it's container.
                  4: The object can't be inserted into bags etc.
                  5: The destination doesn't allow insertions of objects.
                  6: The object can't be picked up.
                  7: Other (Error message printed inside move() func)
                  8: Too big volume for destination
                  9: The container is closed, can't remove
                 10: The container is closed, can't put object there
 * <snap>
 */
varargs public int 
move(mixed dest, mixed subloc)
{
    if (!objectp(dest))
	   return 5;

    if (strlen(House) && living(dest) && 
	(dest->query_bnumen_house() != House))
    {
	   write("You may not give the " + short() +
	      " to anyone but to a member of the House of " + House + ".\n");
	   return 7;
    }

    return ::move(dest, subloc);
}

public string
query_bnumen_house()
{
    return House;
}

public int
set_bnumen_house(string str, int force = 0)
{
    if (!strlen(House) || force)
    {
	   House = str;
	   return 1;
    }
    return 0;
}
