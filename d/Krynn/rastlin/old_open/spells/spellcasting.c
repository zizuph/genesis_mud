/*  LAST EDIT: Wed Apr 22 09:49:09 1992 by Michael Schmidt (michael)  */
/* 
 * spells.c
 *
 * This is the standard spell object. It should be inherited into any
 * object that is supposed to define spells.
 *
 * Please read the documentation on spells if you haven't done so
 * already. (Use "man spells" in lpmud).

 * User function in this object:
 * -----------------------------
 *
 * create_spells()	- The function that initates the object. Should be
 *			  used exactly as create_object() when you inherit
 *			  "std/object" file.
 *
 * add_spell()		- This function is called to add a spell to the 
 *			  used "add_action" for this purpose, since
 *			  that will void most of the built-in functionality
 *			  of spells in the player.
 *
 * remove_spell()	- This function si called to remove a spell from the
 * 			  list of spells a player has access to. It might be
 *			  that you want to give limited access of a spell
 *			  (for example a limited number of times it can be
 *			  cast per session) and then want to remove it after
 *			  a while.
 *

 *
 * Typical usage in your spell object:
 *
 *   inherit "/std/spells";
 *
 *   create_spells()
 *   {
 *	 set_name("book");
 *	 set_short("black book");
 *       add_spell("verb1", "function1", "name1");
 *       add_spell("verb2", "function2", "name2");
 *       .....
 *       add_spell("verbN", "functionN", "nameN");
 *   }
 * 
 *   function1(){}
 *   function2(){}
 *   .....
 *   functionN(){}
 *
 * where functionX should return 1 for success, a fail-message or 0 to get
 * the standard fail-message
 *
 */
#pragma save_binary

inherit "/std/object";
inherit "/cmd/std/command_driver";

inherit "/d/Krynn/rastlin/open/spells/spell";

#include </secure/std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>

static string	*verb_list,	/* The list of spell verbs */
		*func_list,	/* The list of functions to call */
		*name_list;	/* The list of spell names */

void create_spells();

/*
 * Function name: create_object
 */
void
create_object()
{
    verb_list = ({});
    func_list = ({});
    name_list = ({});

    create_spells();
}

/*
 * Function name: add_spell
 * Description:   Add the spell to the list of active spells.
 * Arguments:	  verb - The activating verb string
 *		  function - The function to call
 *		  name - The name of the spell (to be displayed in
 *			 the player spell list).
 */
nomask void
add_spell(string verb, string func, string name)
{
    /* The spell was already added once */
    if (member_array(verb, verb_list) >= 0)
	return;

    SECURITY->add_spell(verb, func, this_object(), name);
    verb_list += ({ verb });
    func_list += ({ func });
    name_list += ({ name });
    /* Make sure the command driver reads the list again */
    update_commands();
}

/*
 * Function name: remove_spell
 * Description:   Remove the spell with the given verb string.
 * Arguments:	  verb - The verb of the spell to remove.
 */
nomask int
remove_spell(string verb)
{
    int index;

    index = member_array(verb, verb_list);

    if (index < 0)
	return 0;

    verb_list = exclude_array(verb_list, index, index);
    func_list = exclude_array(func_list, index, index);
    name_list = exclude_array(name_list, index, index);

    /* Make sure the command driver reads the list again */
    update_commands();
    return 1;
}

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *		  the player soul when the command "spells" is typed.
 */
void
list_spells()
{
    int i;
    string space;

    space = "                                                 ";
    for (i = 0 ; i < sizeof(verb_list) ; i++)
	write(verb_list[i] + extract(space, 0, 17 - strlen(verb_list[i])) +
	      name_list[i] + extract(space, 0, 31 - strlen(name_list[i])) +
	      "\n");
}

/*
 * Function name: create_spells
 * Description:   Default function
 */
public mixed
create_spells()
{
    set_name("book");
    set_short("spell book");
    set_long("A heavy book bearing the title 'Magica Arcana'.\n");
}

/*
 * Function name: query_cmdlist
 * Description:   Used by the command_driver, called each time the
 *		  command set is reloaded.
 */
mapping
query_cmdlist()
{
    if (sizeof(verb_list))
    {
        return mkmapping(verb_list, func_list);
    }
    else
    {
        return ([ ]);
    }
}

/*
 * Function name: query_verbs
 * Description:   Not used by command_driver, do we need it?
 */
string *
query_verbs()
{
    return verb_list;
}

/*
 * Function name: query_funcs
 * Description:   Not used by command_driver, do we need it?
 */ 
string *
query_funcs()
{
    return func_list;
}

/*
 * Function name: enter_env
 * Description:   Add the object to the list of spell objects.
 */
varargs void
enter_env(object dest, object old)
{
    if (!dest || !living(dest))
	return;

    dest->add_spellobj(this_object());
}

/*
 * Function name: leave_env
 * Description:   Remove the object from the list of spell objects
 */
varargs void
leave_env(object old, object dest)
{
    if (!old || !living(old))
	return;

    old->remove_spellobj(this_object());
}

/*
 * Function name: query_spell_time
 * Description:   How long time will it take to cast a spell?
 * Arguments:	  verb - The spell verb
 * Returns:       The time it will take. Real casting time will be time + 2 
 */
int
query_spell_time(string verb, string arg)
{ 
    return spell_time; 
}

/*
 * Function name: query_spell_mess
 * Description:   If you want own messages to be written when a spell is cast
 *		  instead of the standard messages you shuold define this
 *		  funktion.
 * Arguments:     verb - The spell verb
 * Returns:       1 if I took care of the messages
 */
int query_spell_mess(string verb, string arg) { return 0; }

/*
 * Function name: start_spell_fail
 * Description:   Initialize the spell and check if it will work
 * Arguments:	  verb - The spell verb
 *		  arg  - The given argument
 * Returns:	  True if it fails.
 */
int
start_spell_fail(string verb, string arg)
{
    object room;
    string no_magic_fail;

    default_config_spell();
    call_other(this_object(), "create_spell_"+verb, arg);

    room = environment(this_player());

    no_magic_fail = room->query_prop(ROOM_M_NO_MAGIC);
    if (no_magic_fail)
    {
	if (!stringp(no_magic_fail))
            write("Magic is useless in the void!\n");
        else
            write(no_magic_fail);
	return 1;
    }

    no_magic_fail = room->query_prop(ROOM_M_NO_MAGIC_ATTACK);
    if (spell_attack && no_magic_fail)
    {
	if (!stringp(no_magic_fail))
            write("Magic is useless in the void!\n");
        else
            write(no_magic_fail);
	return 1;
    }

    /* Do we have all the needed ingredients? */
    if(!valid_ingredients())
    {
	write("Sorry, but you don't have the right ingredients!\n");
	return 1;
    }

    /* Do we have enough mana to cast the spell? */
    if (caster->query_mana() < spell_mana_needed)
    {
	write("You don't have mana enough to properly cast the spell.\n");
	return 1;
    }

    /* Sort out all the possible targets if the spells needs them */
    if (!spell_no_targets || spell_one_target || spell_multiple_targets)
      {
	  targets = find_targets(arg);
	  if (!spell_no_targets && (!targets || sizeof(targets)==0))
	    return 1;
      }
    
    if (!targets || sizeof(targets)==0)
      targets = ({ this_player() });

    valid_skills();

    /* For now lets pretend the spell will succeed, we reduce some mana. */
    caster->add_mana(-spell_mana_needed);
    /* that part will later be done from /std/living/cmdhooks.c!!! */

    /* was:
    caster->add_mana(-spell_mana_needed/2); * Olorin thinks this is too much. Fix! */

    return 0;
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */







