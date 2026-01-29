/*
 * /std/potion.c
 *
 * This is the standard object used for any form of potion.
 *
 * It works much the same way as herb.c. - don't use set_long!
 * Instead, use set_id_long and set_unid_long.
 *
 * /Nick
 * Modifications for identification using Alchemy skill Oct. '93
 * /Elessar
 */
#pragma save_binary

inherit "/std/drink";
inherit "/lib/herb_support";

#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

int     id_diff,
        magic_resistance;	/* How strong is the resistance against magic */
string	smell_msg,
	taste_msg,
        id_long,
        unid_long;

string long_func()
{
  if (TP->query_skill(SS_ALCHEMY) > id_diff) return id_long;
  return unid_long;
}

public void
create_potion()
{
    ::create_drink();
    set_name("potion");
    set_long("@@long_func");
}

public nomask void
create_drink()
{
    smell_msg = "The potion seems without smell.\n";
    taste_msg = "The potion is tasteless.\n";
    id_long = "This potion is not identifiable.\n";
    unid_long = "This unidentified potion looks insignificant.\n";
    create_potion();
}

public nomask void
reset_drink() { this_object()->reset_potion(); }

void
init()
{
    ::init();

    add_action("drink_it", "quaff"); /* Use the same routines */
    add_action("drink_it", "taste");
    add_action("drink_it", "smell");
}

string
drink_fail()
{
    string str;

    str = "You try to " + query_verb() + " " + COMPOSITE_DEAD(gFail) +
	" but fail.\n";
    say(QCTNAME(this_player()) + " tries to " + query_verb() + " " + QCOMPDEAD +
	     " but fails.\n");
    tp_remove_temp(this_player());
    return str;
}

int
drink_one_thing(object ob)
{
    string vb;

    if ((vb = query_verb()) == "quaff")
	return ::drink_one_thing(ob);
    if ((vb = query_verb()) == "drink")
        return ::drink_one_thing(ob);

    if (vb == "taste")
	this_player()->catch_msg(taste_msg);
    else
	this_player()->catch_msg(smell_msg);
    return 1;
}

/*
void
delay_destruct()
{
    this_object()->do_herb_effects();
    ::delay_destruct();
}
*/

/*
 * Function name: set_magic_res
 * Description:   Set how resistance this potion is agains magic / how easy it
 *		  is to dispel it.
 * Arguments:     resistance - the resistance
 */
void set_magic_res(int resistance) { magic_resistance = resistance; }

/*
 * Function name: query_magic_resistance
 * Description:   Query the magic resistance
 * Returns:       How resistive the potion is
 */
int
query_magic_res(string prop)
{
    if (prop == MAGIC_I_RES_MAGIC)
	return magic_resistance;
    else
	return 0;
}

void set_id_diff(int idd) { id_diff = idd; }

void set_id_long(string idl)
{
  id_long = idl;
  if (!query_prop(HEAP_S_UNIQUE_ID)) add_prop(HEAP_S_UNIQUE_ID,idl);
}


void set_unid_long(string unidl) { unid_long = unidl; }

int query_id_diff() { return id_diff; }

string query_id_long() { return id_long; }

string query_unid_long() { return unid_long; }

/*
 * Function name: dispel_magic
 * Description:   Function called by a dispel spell
 * Argument:	  magic - How strong the dispel is
 * Returns:	  0 - No dispelling, 1 - Object dispelled
 */
int
dispel_magic(int magic)
{
    object env;

    if (magic < query_magic_res(MAGIC_I_RES_MAGIC))
	return 0;

    if (living(env = environment(this_object())))
    {
	tell_room(environment(env), "The " + QSHORT(this_object()) +
	    " held by " + QTNAME(env) + " glows white and explodes!\n", env);
	env->catch_msg("The " + QSHORT(this_object()) + " that you hold " +
	    " glows white and explodes!\n");
    } else if (env->query_prop(ROOM_I_IS))
 	tell_room(env, "The " + QSHORT(this_object()) +
	    " glows white and explodes!\n");

    return 1;
}

/*
 * Function name: set_potion_taste
 * Descirption:	  Set the message when player tastes a potion
 * Arguments:	  mess - The message that should be sent to the player
 */
void set_potion_taste(string mess) { taste_msg = mess; }

string query_potion_taste() { return taste_msg; }

/*
 * Function name: set_potion_smell
 * Description:   Set the message player will get when smelling on a potion
 * Arguments:	  mess - The message
 */
void set_potion_smell(string mess) { smell_msg = mess; }

string query_potion_smell() { return smell_msg; }
