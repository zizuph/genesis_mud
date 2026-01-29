/*
   /std/object.c

   Contains all basic routines for configurable objects.
   Inherited by: EVERY OBJECT in the game.

   In all of the set_ functions it is possible to give an argument that
   might be a function that then will be called when the corresponding query_
   function is called. The function must then be given as "@@func_name@@" in
   order for it to be recognized as a function. If the function is defined in
   another object, give the value string as "@@func_name:obj_filename@@".

   There are query_xx() functions for all of the set_xx().

 */

#pragma save_binary
inherit "/std/callout";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <std.h>
#include <ss_types.h>

/* Added by Dumrik for use of the COMMAND_DRIVER */

#include <cmdparse.h>

static string   obj_short,	/* Short description */
                obj_pshort,	/* Plural short description */
                obj_long,	/* Long description */
		obj_subloc,     /* Current sublocation */
    		*obj_names,	/* The name(s) of the object */
                *obj_pnames,	/* The plural name(s) of the object */
                *obj_adjs;	/* The adjectivs accepted */
static mixed    obj_items,      /* The items (pseudo look) of this object */
                obj_cmd_items,  /* The command items of this object */
		obj_commands,   /* The commands for each command item */
		obj_state,      /* The internal state, used for light etc */
                magic_effects;  /* Magic items effecting this object. */
static int      obj_no_show,	/* Don't display this object. */
	  	obj_no_show_c,	/* Don't show this object in composite desc */
		obj_no_change;	/* Lock value for configuration */
static object   obj_previous;   /* Caller of function resulting in VBCF */
static mapping  obj_props;	/* Object properties */
private static int hb_index,	/* Identification of hearbeat callout */
		reset_interval;	/* Constant used to set reset interval */

/*
 * Prototypes
 */
public 	varargs	mixed 	check_call(string retval, object for_obj);
	void 	add_prop(string prop, mixed val);
	void 	add_name(mixed name);
public 	mixed 	query_prop(string prop);
	mixed 	query_adj(int arg);
	mixed 	query_adjs();
	void	set_no_show_composite(int i);
public  nomask varargs int check_recoverable(int flag);

/* 
 * PARSE_COMMAND
 *
 * These lfuns are called from within the efun parse_command() to get the
 * three different sets of ids. If no plural ids are returned then the
 * efun will try to make pluralforms from the singular ids.
 *
 * If no normal ids are returned then parse_command will never find the object.
 */
public string *
parse_command_id_list() 	
{ 
    return obj_names; 
}

/*
 * Description: This function is used buy the efun parse_command()
 */
public string *
parse_command_plural_id_list() 
{ 
    return obj_pnames; 
}

/*
 * Description: This function is used buy the efun parse_command()
 */
public string *
parse_command_adjectiv_id_list() 
{
    return (sizeof(obj_adjs) ? obj_adjs : (stringp(obj_adjs) ?
					   ({ obj_adjs }) : 0));
}

#if 0 
    /* This a little trick to fool the documentation maker.
	  Don't use '*/' after 'Description:' in the example.

 * Description: Simple usage of /std/object.c  

      inherit "/std/object";

      create_object()
      {
   	  set_name("drutten");   /* This is what it can be called id()
	  set_short("small object"); /* Don't use articles
	  set_long("This is a little but very nice object.\n");
      }
 */
public
USAGE()
{}
#endif

/*
 * Function name: set_heart_beat
 * Description:   Emulate old heartbeat code
 * Arguments:     repeat - 1 to enable, 0 to disable
 * Returns:       Return value from call_out()
 */
nomask int
set_heart_beat(mixed repeat, string func = "heart_beat")
{
    float delay;
    int ret;
    object tp;
    
    if (intp(repeat))
	delay = itof(repeat * 2);
    else if (floatp(repeat))
	delay = repeat;
    else
	throw("Wrong argument 1 to set_heart_beat.\n");

    if(hb_index)
	remove_alarm(hb_index);

    if (delay > 0.0)
    {
	tp = this_player();
	set_this_player(0);
	ret = call_out(func, -delay);
	set_this_player(tp);
    }
    return hb_index = ret;
}

/*
 * Function name: create_object
 * Description:   Create the object (Default for clones)
 */
public void
create_object()
{
    add_name("object");
    add_prop(OBJ_I_WEIGHT, 1000);	/* 1 Kg is default */
    add_prop(OBJ_I_VOLUME, 1000);	/* 1 l is default */
    add_prop(OBJ_I_VALUE, 0);		/* 0 is default */
    obj_no_change = 0;
    obj_no_show = 0;
}

/*
 * Function name: create
 * Description  : Object constructor, called directly after load / clone.
 *                It calls the public create function and sets the only
 *                default variable.
 */
public nomask void
create()
{
    obj_names = ({ OB_NAME(this_object()) });

    this_object()->create_object();
}

#if 0
/*
 * Function name: reset_object
 * Description:   Reset the object (Default for clones)
 */
public void
reset_object() 
{
}
#endif

/*
 * Function name: reset
 * Description:   Reset the object (always called, used as constructor)
 * Arguments:	  arg: The reset argument.
 */
public nomask void
reset()
{
    float reset_time = -log(rnd()) * 540000.00;
    mixed *calls = get_all_alarms();
    int i;
    
    for (i = 0; i < sizeof(calls); i++)
	if (calls[i][1] == "reset")
	    remove_alarm(calls[i][0]);

    if (!reset_interval)
	return;

    reset_time /= itof(reset_interval);
    if (reset_time < 0.0)
	reset_time = 0.0;

    if (function_exists("reset_object", this_object()))
	call_out("reset", reset_time);

    this_object()->reset_object();
}

/*
 * Function name: enable_reset
 * Description:   Used to enable or disable rests in an object
 * Arguments:     interval (optional) - frequency of resets, 100
 *                is default. Legal values are 0 (disabled) or
 *                10 (seldom) to 200 (often).
 */
nomask void
enable_reset(int on=100)
{
    float reset_time;
    mixed *calls = get_all_alarms();
    int i;
    
    if (obj_no_change || (on && (on<10 || on>200)))
	return;

    reset_interval = on;

    for (i = 0; i < sizeof(calls); i++)
	if (calls[i][1] == "reset")
	    remove_alarm(calls[i][0]);

    if (reset_interval) {
	reset_time = -log(rnd()) * 540000.0 / itof(reset_interval);

	if (reset_time < 0.0)
	    reset_time = 0.0;

	if (function_exists("reset_object", this_object()))
	    call_out("reset", reset_time);
    }
}

int cmditem_action(string str);

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. Note that if
 *		  you redefine this function, the command items will not
 *		  work unless you do ::init()
 */
public void
init()
{
    int il;
    string *cmd;

    if (!sizeof(obj_commands))
	return;

    for (il = 0; il < sizeof(obj_commands); il++)
	add_action(cmditem_action, obj_commands[il]);
}


/*
 * Function name: update_actions
 * Description:   Updates our defined actions in all relevant objects.
 */
public void
update_actions()
{
    if (environment(this_object()))
	move_object(environment(this_object()));
}

/*
 * Function name: id
 * Description:   Identify the object.
 * Arguments:	  str: String to test with.
 * Returns:	  True or false.
 */
public int
id(string str)
{
    return (member_array(str, obj_names) >= 0);
}

/*
 * Function name: plural_id
 * Description:   Identify the object.
 * Arguments:	  str: String to test with in plural form.
 * Returns:	  True or false.
 */
public int
plural_id(string str)
{
    return (member_array(str, obj_pnames) >= 0);
}

/*
 * Function name: long
 * Description:   Describe the object or one item (pseudo look) in it
 *		  *** NOTE! This lfun does not do a write() !! ***
 * Arguments:	  str: name of item or 0
 *		  for_obj: The object for which tries to get the long
 * Returns:	  Description of object in a string.
 */
varargs public mixed
long(string str, object for_obj)
{
    int i;

    if (!str)
    {
	if (obj_long)
	    return check_call(obj_long, for_obj);
	else
	    return "You see a non-descript object.\n";
    }
    if (!pointerp(obj_items))
	return 1;

    for (i = 0; i < sizeof(obj_items); i++)
	if (member_array(str,obj_items[i][0]) >= 0)
	{
	    return (strlen(obj_items[i][1]) ?
		    (string) check_call(obj_items[i][1]) :
		    "You see nothing special.\n");
	}
    /* If we end up here there were no such item
       Why 1?
    */
    return 1;
}

/*
 * Function name: query_long
 * Description:   Gives the set long description
 * Returns:       Exactly what was given to set_long()
 */
public string
query_long()
{
    return obj_long;
}

/*
 * Function name: check_seen
 * Description:   True if this object can be seen by a given object
 * Arguments:     for_obj: The object for which visibilty should be checked
 * Returns:       1 if this object can be seen.
 */
public int
check_seen(object for_obj)
{
    if (!for_obj || obj_no_show ||
	(!for_obj->query_wiz_level() &&
	 (for_obj->query_prop(LIVE_I_SEE_INVIS) <
	  this_object()->query_prop(OBJ_I_INVIS) ||
	  for_obj->query_skill(SS_AWARENESS) <
	  this_object()->query_prop(OBJ_I_HIDE))))
	return 0;

    return 1;
}

/*
 * Function name: short
 * Description:   Return the short description of the object.
 */
public varargs string 
short(object for_obj)
{
    if (!obj_short)
    {
	if (sizeof(obj_adjs) && sizeof(obj_names))
	    obj_short = implode(obj_adjs," ") + " " + obj_names[0];
	else if (sizeof(obj_names))
	    obj_short = obj_names[0];
	else
	    return 0;
    }
    return check_call(obj_short, for_obj);
}

/*
 * Function name:   vbfcshort
 * Description:     Gives short as seen by previous_object
 * Returns:         string holding short()
 * Arguments:       pobj: Object which to make the relation for
 *                  if not defined we assume that we are doing a vbfc
 *                  through the vbfc_object
 */
varargs public string
vbfc_short(object pobj)
{
    if (!objectp(pobj))
	pobj = previous_object(-1);
    if (!this_object()->check_seen(pobj) || !CAN_SEE_IN_ROOM(pobj))
	return "something";

    return short(pobj);
}

/*
 * Function name: query_short
 * Description:   Gives the set short description
 * Returns:       Exactly what was given to set_short()
 */
public string
query_short()
{
    return obj_short;
}

/*
 * Function name: plural_short
 * Description:   Return the plural short description of the object.
 */
public varargs string
plural_short(object for_obj)
{
    if (!obj_pshort)
	return 0;

    if (!check_seen((objectp(for_obj) ? for_obj : this_player())))
	return 0;

    return check_call(obj_pshort, for_obj);
}

/*
 * Function name: query_plural_short
 * Description:   Gives the set plural_short description
 * Returns:       Exactly what was given to set_plural_short()
 */
public string
query_plural_short()
{
    return obj_pshort;
}

/*
 * Function name: adjectiv_id
 * Description:   Identify the objects adjectives.
 * Arguments:	  str: String to test with.
 * Returns:	  True or false.
 */
public int
adjectiv_id(string str)
{
    return (member_array(str, obj_adjs) >= 0);
}

/*
 * Function name: add_prop
 * Description:   Add a property to the property list
 *                If the property already exist, the value is replaced
 *		  If a function "add_prop" + propname is declared or
 *		  is shadowing this_object then that function is called
 *		  prior to the setting of the property. 
 *		  NOTE
 *		    If the optional function above returns something other
 *		    than 0. The property will NOT be set.
 *
 * Arguments:	  prop - The property string to be added.
 *                val: The value of the property
 * Returns:       None.
 */
public void
add_prop(string prop, mixed val)
{
    int c;
    mixed oval;

    if (obj_no_change)
	return;			/* All changes have been locked out */

    if (!mappingp(obj_props))
	obj_props = ([]);

    oval = query_prop(prop);
    if (call_other(this_object(), "add_prop" + prop, val))
	return 0;
    obj_props[prop] = val;

    if (environment(this_object()))
	environment(this_object())->notify_change_prop(prop, 
						       query_prop(prop), oval);
}

/*
 * Function name: change_prop
 * Description:   Change a property value.
 * Arguments:	  prop - The property string to be changed.
 *                val: The value of the property
 * Returns:       None.
 */
public void
change_prop(string prop, mixed val)
{
    add_prop(prop, val);
}

/*
 * Function name: remove_prop
 * Description:   Removes a property string from the property list.
 * Arguments:	  prop - The property string to be removed.
 * Returns:       1 / 0.
 */
public varargs int
remove_prop(string prop)
{
    if (obj_no_change)
	return 0;		/* All changes has been locked out */

    if (!prop)
	return 0;

    if (call_other(this_object(), "remove_prop" + prop))
	return 0;

    if (mappingp(obj_props))
	obj_props = m_delete(obj_props, prop);
}

/*
 * Function name: query_prop
 * Description:   Find the value of a property.
 * Arguments:	  prop - The property searched for.
 * Returns:       The value or 0.
 */
#undef CFUN
#ifdef CFUN
public mixed
query_prop(string prop) = "query_prop";
#else
public mixed
query_prop(string prop)
{
    if (!mappingp(obj_props))
	return 0;
    return check_call(obj_props[prop]);
}
#endif

/*
 * Function name: query_props
 * Description:   Give all the existing properties
 * Returns:       An array of property names or 0.
 */
public nomask mixed
query_props() 
{
    if (mappingp(obj_props))
	return m_indexes(obj_props);
    else
	return 0;
}

/*
 * Function name: query_prop_setting
 * Description:   Returns the true setting of the prop
 * Arguments:	  prop - The property searched for
 * Returns:	  The true setting (mixed)
 */
public nomask mixed
query_prop_setting(string prop)
{
    if (!mappingp(obj_props))
	return 0;
    return obj_props[prop];
}

/*
 * Function name: notify_change_prop
 * Description:   This function is called when a property in an object
 * 		  in the inventory has been changed.
 * Arguments:	  prop - The property that has been changed.
 *		  val  - The new value.
 *		  oval - The old value
 */
public void
notify_change_prop(string prop, mixed val, mixed oval)
{
}

/*
 * Function name: mark_state
 * Description:   Mark the internal state so that update is later possible
 */
public void
mark_state()
{
    /* More properties can be added here if need be
     */
    obj_state = ({ query_prop(OBJ_I_LIGHT), query_prop(OBJ_I_WEIGHT),
		   query_prop(OBJ_I_VOLUME) });
}

/*
 * Function name: update_state
 * Description:   Update the environment according to the changes in our
 *		  state;
 */
public void
update_state()
{
    int l, w, v;

    l = query_prop(OBJ_I_LIGHT); 
    w = query_prop(OBJ_I_WEIGHT);
    v = query_prop(OBJ_I_VOLUME);

    /* More properties can be added here if need be
     */
    if (environment(this_object()))
	environment(this_object())->update_internal(l - obj_state[0],
						    w - obj_state[1],
						    v - obj_state[2]);
}
    
/*
 * Function name: move
 * Description:   Move this object to the destination given by string /
 *                obj. If the second parameter exists then weight
 *  		  accounting and tests on destination is not done.
 * Arguments:	  dest: Object or filename to move to,
 *                subloc: 1 == Always move, otherwise name of sublocation
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
 */
varargs public int
move(mixed dest, mixed subloc)
{
    object          old;
    int             is_room, rw, rv, is_live_dest, is_live_old,
                    uw,uv,
		    sw,sv;
    mixed	    tmp;

    if (!dest)
	return 5;
    old = environment(this_object());
    if (stringp(dest))
    {
	call_other(dest, "??");
	dest = find_object(dest);
    }
    if (!objectp(dest))
	dest = old;

    if (subloc == 1)
    {
	move_object(dest);
    }
    else if (old != dest)
    {
	if (!dest || !dest->query_prop(CONT_I_IN) || dest->query_prop(CONT_M_NO_INS))
	    return 5;
	if ((old) && (old->query_prop(CONT_M_NO_REM)))
	    return 3;
	if (old && old->query_prop(CONT_I_CLOSED))
	    return 9;

	is_room = (int) dest->query_prop(ROOM_I_IS);

	if (old)
	    is_live_old = (function_exists("create_container",
					   old) == "/std/living");
	is_live_dest = (function_exists("create_container",
					dest) == "/std/living");

	if (old && is_live_old && this_object()->query_prop(OBJ_M_NO_DROP))
	    return 2;

	if (!is_live_dest)
	{
	    if ((!is_room) && (this_object()->query_prop(OBJ_M_NO_INS)))
		return 4;
	    if (dest && dest->query_prop(CONT_I_CLOSED))
	 	return 10;
	}
	else
	{
	    if ((!is_live_old) && (this_object()->query_prop(OBJ_M_NO_GET)))
		return 6;
	    else if (is_live_old && this_object()->query_prop(OBJ_M_NO_GIVE))
		return 3;
	}
	
	if (!is_room)
	{
	    rw = dest->query_prop(CONT_I_MAX_WEIGHT) - 
		dest->query_prop(OBJ_I_WEIGHT);
	    rv = dest->volume_left();
	    if (!query_prop(HEAP_I_IS))
	    {
		if (rw < query_prop(OBJ_I_WEIGHT))
		    return 1;
		if (rv < query_prop(OBJ_I_VOLUME))
		    return 8;
	    }
	    else
	    {
		sw = 0;
		sv = 0;
		if (rw < query_prop(OBJ_I_WEIGHT))
		{
		    uw = query_prop(HEAP_I_UNIT_WEIGHT);
		    if (uw > rw)
			return 1;
		
		    sw = rw / uw; /* This amount of the heap can be carried */
		    sv = sw;
		}

		if (rv < query_prop(OBJ_I_VOLUME))
		{
		    uv = query_prop(HEAP_I_UNIT_VOLUME);
		    if (uv > rv)
			return 8;

		    sv = rv / uv; /* This amount of the heap can be carried */
		    if (!sw)
			sw = sv;
		}
		if (sw || sv)
		    this_object()->split_heap((sw < sv) ? sw : sv);
	    }
	}
	move_object(dest);
    }

    if (subloc != 1)
	obj_subloc = subloc;

    if (old != dest)
    {
	if (old) 
	{
	    this_object()->leave_env(old, dest);
	    old->leave_inv(this_object(),dest);
	}

	if (dest)
	{
	    this_object()->enter_env(dest, old);
	    dest->enter_inv(this_object(),old);
	}
    }
    mark_state();
    return 0;
}

/*
 * Function name: query_subloc
 * Description:   Get the current sub location's name
 */
mixed
query_subloc() 
{ 
    return obj_subloc; 
}

/*
 * Default movedetect functions
 */

/*
 * Description: This function is called each time an object enters the
 *	 	inventory of this object.
 */
void enter_inv(object ob, object old) 
{
}

/*
 * Description: This function is called each time this object enters a
 *		new environment.
 */
void enter_env(object dest, object old) 
{
}

/*
 * Description: This function is called each time an object leaves the
 *		inventory of this object.
 */
void leave_inv(object ob, object dest) 
{
}

/*
 * Description: This function is called eack time this object leaves
 *		an environment.
 */
void leave_env(object old, object dest) 
{
}

/*
 * Function name: remove_object
 * Description:   Removes this object from the game.
 * Returns:       True if the object was removed.
 */
public int
remove_object()
{
    map(all_inventory(), "recursive_rm", this_object());
    if (environment(this_object()))
	environment(this_object())->leave_inv(this_object(),0);
    this_object()->leave_env(environment(this_object()),0);
    destruct();
    return 1;
}

void
recursive_rm(object ob)
{
    if (query_ip_number(ob))
	ob->move(ob->query_default_start_location());
    else
	ob->remove_object();
}

/*
 * Function name: vbfc_caller
 * Description:   This function will hopfully return correct object which this
 *		  vbfc is for.
 * Returns:	  The object who wants a vbfc
 */
public object
vbfc_caller() 
{ 
    return obj_previous; 
}

/*
 * Function name: check_call
 * Description:   Fixes a call to a named function if the value is on the form:
 *                '@@function[:filename][|arg1|arg2..|argN]@@'
 *                Both filename and arguments are optional.
 * Arguments:     retval: The value to be returned immidiatelly or a function
 *                        description.
 */
#ifdef CFUN
public nomask varargs mixed
check_call(string retval, object for_obj = previous_object()) = "check_call";
#else
public nomask varargs mixed
check_call(string retval, object for_obj = previous_object())
{
    int 	    more;
    string 	    a, b, euid;
    mixed	    s, proc_ret;

    if (!stringp(retval))
	return retval;

    more = sscanf(retval, "@@%s@@%s", a, b);

    obj_previous = for_obj;

    if (more == 0 && extract(retval, 0, 1) == "@@")
        proc_ret = process_value(extract(retval, 2), 1);
    else if (more == 1 || (more == 2 && !strlen(b)))
	proc_ret = process_value(a, 1);
    else
	proc_ret = process_string(retval, 1);

    obj_previous = 0;
    return proc_ret;
}
#endif

public void
reset_euid() 
{ 
    seteuid(getuid(this_object())); 
}

/* Define set/query functions for the ordinary variables in an object */

/*
 * Function name: add_list
 * Description:   Common routine for set_name, set_pname, set_adj etc
 * Arguments:	  list: The list of elements
 *		  elem: string holding one new element.
 *                first: True if it is the main name, pname adj
 * Returns:	  The new list.
 */
private string *
add_list(string *list, mixed elem, int first)
{
    int il;
    string *e;

    if (obj_no_change)
	return list;			/* All changes has been locked out */

    if (!pointerp(list))
	list = ({});

    if (pointerp(elem))
	e = elem;
    else
	e = ({ elem });
    
    if (first)
	list = e + list;
    else
	list = list + e;

    return list;
}

/*
 * Function name: del_list
 * Description:   Removes one or many elements from a list.
 * Arguments:	  list_old: The list as it looks.
 *		  list_del: What should be deleted
 * Returns:	  The new list.
 */
private string *
del_list(string *list_old, mixed list_del)
{
    int il, pos;

    if (obj_no_change)
	return list_old;       		/* All changes has been locked out */

    if (!pointerp(list_del))
	list_del = ({ list_del });

    for (il = 0; il < sizeof(list_del); il++)
    {
	pos = member_array(list_del[il], list_old);
	if (pos >= 0)
	    list_old = exclude_array(list_old, pos, pos);
    }
    return list_old;
}

/*
 * Function name: query_list
 * Description:   Gives the return of a query on a list.
 * Arguments:	  list: The list in question
 *		  arg: If true then the entire list is returned.
 * Returns:       A string or an array as described above.
 */
private mixed
query_list(mixed list, int arg)
{
    if (!pointerp(list))
	return 0;

    if (!arg && sizeof(list))
	return list[0];
    else
	return list + ({});
}

/*
 * Function name: set_name
 * Description:   Sets the name(s) of the object. This is the name that
 *                the object can be referenced by. set_name can be called
 *                repeatedly to add more names.
 * Arguments:	  name: string holding one name.
 */
public void
set_name(mixed name) 
{ 
    obj_names = add_list(obj_names, name, 1); 
}

/*
 * Description: Adds a name to the object.
 */
public void
add_name(mixed name) 
{ 
    obj_names = add_list(obj_names, name, 0); 
}

/*
 * Function name: remove_name
 * Description:   Removes one name
 * Arguments:	  name: string of one name or an array of names
 */
public void
remove_name(mixed name) 
{ 
    obj_names = del_list(obj_names, name); 
}

/*
 * Function name: query_name
 * Description:   Gives the name(s) of the object.
 * Arguments:	  arg: If true then the entire list is returned.
 * Returns:       A string or an array as described above.
 */
varargs public mixed
query_name(int arg) 
{ 
    return query_list(obj_names, arg); 
}

/*
 * Description: Returns all names of the object
 */
public string *
query_names() 
{ 
    return query_list(obj_names, 1); 
}

/*
 * Function name: set_pname
 * Description:   Sets the pluralform of the name(s) of the object. This is
 *                used when refering to the object in plural. If not defined
 *                then the singular form is used. set_pname can be called
 *                repeatedly to add more pluralforms for names.
 * Arguments:	  name: string holding one name.
 */
public void
set_pname(mixed pname) 
{ 
    obj_pnames = add_list(obj_pnames, pname, 1); 
}

/*
 * Description: Adds a plural name to the object.
 */
public void
add_pname(mixed pname) 
{ 
    obj_pnames = add_list(obj_pnames, pname, 0); 
}

/*
 * Function name: remove_pname
 * Description:   Removes one pname
 * Arguments:	  pname: string of one pname or an array of pnames
 */
public void
remove_pname(mixed pname) 
{ 
    obj_pnames = del_list(obj_pnames, pname); 
}

/*
 * Function name: query_pname
 * Description:   Gives the pluralform(s) of the name of the object.
 *                If not defined then last word of plural_short() is used
 * Arguments:	  arg: If true then the entire list is returned.
 * Returns:       A string or an array as described above.
 */
varargs public mixed
query_pname(int arg) 
{
    if (!sizeof(obj_pnames))
    {
	string      *w;

	w = explode(plural_short() + " ", " ");
	if (!arg)
	    return w[sizeof(w) - 1];
	else
	    return ({ w[sizeof(w) - 1] });

    }
    return query_list(obj_pnames, arg);
} 

/* 
 * Description: Returns all plural names of the object.
 */
public string *
query_pnames() 
{ 
    return query_list(obj_pnames, 1); 
}

/*
 * Function name: set_adj
 * Description:   Sets the accepatble adjective(s) of the object.
 *                This is used as a complement to name in refering to the
 *                object. It is also used when refering to nondescript objects
 *                like for example: "get all the red ones"
 *                If not defined then all but last word of short() is used.
 * Arguments:	  adj: string of one adjective or array of strings of
 *		  adjectives
 */
public void
set_adj(mixed adj) 
{ 
    obj_adjs = add_list(obj_adjs, adj, 1); 
}

/*
 * Description: Adds an adjective to the object
 */
public void
add_adj(mixed adj) 
{ 
    obj_adjs = add_list(obj_adjs, adj, 0); 
}

/*
 * Function name: remove_adj
 * Description:   Removes one adjective
 * Arguments:	  adj: string of one adjective or an array of adjectives
 */
public void
remove_adj(mixed adj) 
{ 
    obj_adjs = del_list(obj_adjs, adj); 
}
  
/*
 * Function name: query_adj
 * Description:   Gives the accepatble adjective(s) of the object.
 *                If not defined then all but last word of short() is used
 * Arguments:	  arg: If true then the entire list is returned.
 * Returns:       A string or an array as described above.
 */
varargs public mixed
query_adj(int arg) 
{ 
    return query_list(obj_adjs, arg); 
}

/*
 * Description: Returns all adjectives of an object.
 */
public string *
query_adjs() 
{ 
    return query_list(obj_adjs, 1); 
}

/*
 * Function name: set_short
 * Description:   Sets the string to return for short description.
 *		  If not defined, the first name is used instead.
 * Arguments:     short: The short description
 */
public void
set_short(string short)
{
    if (!obj_no_change)
	obj_short = short;
}

/*
 * Function name: set_pshort
 * Description:   Sets the string to return for plural short description.
 *		  If not defined, 0 is returned.
 * Arguments:     pshort: The plural short description
 */
public void
set_pshort(string pshort)
{
    if (!obj_no_change)
	obj_pshort = pshort;
}

/*
 * Function name: set_long
 * Description:   Sets the string to write as a long description.
 *      	  If not defined, the short() is used instead.
 * Arguments:     long: The long description
 */
public void
set_long(string long)
{
    if (!obj_no_change)
	obj_long = long;
}

/*
 * Function name: set_lock
 * Description:   Locks out all changes to this object through set_ functions.
 */
public void
set_lock()
{
    obj_no_change = 1;
}

/*
 * Function name: query_lock
 * Description:   Gives the lock status of this object
 * Returns:       True if changes to this object is locked out
 */
public int
query_lock()
{
    return obj_no_change;
}

/*
 * Function name: set_no_show
 * Description:   Don't show these objects.
 */
public void
set_no_show()
{
    obj_no_show = 1;
    set_no_show_composite(1);
}

/*
 * Function name: unset_no_show
 * Description:   Show it again. Note that if you want the object to appear
 *		  in composite descriptions you have to set_no_show_composite(0)
 *		  to since it is automatically set when setting no_show.
 */
public void
unset_no_show() 
{ 
    obj_no_show = 0; 
}

/*
 * Function name: query_no_show
 * Description:   Return no show status.
 */
public int
query_no_show()
{
    return obj_no_show;
}

/*
 * Function name: set_no_show_composite
 * Description:   Don't show this object in composite descriptions, otherwise
 *		  this object is part of the game like any other.
 * Arguments:     1 - don't show, 0 - show it again
 */
void
set_no_show_composite(int i) 
{ 
    obj_no_show_c = i; 
}

/*
 * Function name: unset_no_show_composite
 * Description:   Show an object in compisite descriptions again.
 */
void unset_no_show_composite() 
{ 
    obj_no_show_c = 0; 
}

/*
 * Function name: query_no_show_composite
 * Description:	  Return status if to be shown in composite descriptions
 */
int query_no_show_composite() 
{ 
    return obj_no_show_c; 
}

/*
 * Function name:  add_magic_effect
 * Description:    Notifies this object that it has been placed
 *                 a magical effect upon it.
 * Arguments:      The effect object, or the filename of
 *                 the code which handles the magical 
 *                 effect. (Filename for a shadow.)
 */
varargs void
add_magic_effect(mixed what)
{
    if (!what)
        what = previous_object();

    if (!pointerp(magic_effects))
	magic_effects = ({ what });
    else
	magic_effects += ({ what });
}

/*
 * Function name:  remove_magic_effect
 * Description:    Removes the magical effect from the
 *                 list of effects affecting this object.
 * Arguments:      What effect.
 * Returns:        If the effect was found.
 */
varargs int
remove_magic_effect(mixed what)
{
    int il;

    if (!what)
        what = previous_object();

    il = member_array(what, magic_effects);

    if (il == -1)
        return 0;

    magic_effects = magic_effects[0 .. (il-1)] + 
	            magic_effects[(il+1) .. (sizeof(magic_effects)-1)];
    return 1;
}

/*
 * Function name:  query_magical_effects
 * Description:    Returns the magical effects upon this
 *                 object.
 */
object *
query_magic_effects()
{
    if (!pointerp(magic_effects))
	magic_effects = ({});
    magic_effects -= ({ 0 });
    return magic_effects;
}

#if 0
/*
 * Function name: query_magic_res
 * Description:   Return the total resistance of worn objects
 * Arguments:     prop - The searched for property.
 * Returns:	  How resistant this object is to that property
 */
public int
query_magic_res(string prop)
{
    int res;

    res = this_object()->query_prop(PRE_OBJ_MAGIC_RES + prop);
    return res > 100 ? 100 : res;
}
#endif

/*
 * Function name: query_magic_res
 * Description:   Return the total resistance for this object
 * Arguments:     prop - The searched for property.
 */
int
query_magic_res(string prop)
{
    int no_objs, max, max_add, max_stat, i;
    mixed value;
    object *list;

    list = this_object()->query_magic_effects();
    
    if (!sizeof(list))
        return (int)this_object()->query_prop(PRE_OBJ_MAGIC_RES + prop);

    max_add = 100;

    for (i = 0; i < sizeof(list); i++)
    {
        value = list[i]->query_magic_protection(prop, this_object());
        if (intp(value))
            value = ({ value, 0 });
        if (pointerp(value))
        {
            if ((sizeof(value) > 0) && !value[1])
                max_stat = max_stat > value[0] ? max_stat : value[0];
            else
                max_add = max_add * (100 - value[0]) / 100;
        }
    }

    if (max_add > 0)
        max_add = 100 - max_add;

    max = max_stat > max_add ? max_stat : max_add;
    max += (int)this_object()->query_prop(PRE_OBJ_MAGIC_RES + prop);

    return max < 100 ? max : 100;
}

/*
 * Function name:  query_magic_protection
 * Description:    This function should return the
 *                 amount of protection versus an 
 *                 attack of 'prop' on 'obj'.
 * Arguments:      prop - The element property to defend.
 *                 protectee  - Magic protection for who or what? 
 */
varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (protectee == this_object())
        return query_prop(prop);
    else
        return 0;
}

/* 

   Items (pseudo look) 
   -------------------

*/
	

/*
 * Function name: item_id
 * Description:   Identify items in the object.
 * Arguments:	  str: String to test with.
 * Returns:	  True or false.
 */
public int
item_id(string str)
{
    int i;
    
    if (!obj_items) return 0;
    
    for (i = 0; i < sizeof(obj_items); i++)
	if (member_array(str, obj_items[i][0]) >= 0) return 1;
}

/*
 * Function name: add_item
 * Description:   Adds an additional item to the object. The first 
 *		  argument is a single string or an array of 
 *      	  strings holding the possible name(s) of the item.
 *		  The second argument is the long description of 
 *		  the item. add_item can be repeatedly called with 
 *		  new items.
 * Arguments:	  names: Alternate names for the item, 
 *                desc: desc of the item
 * Returns:	  True or false.
 */
public int
add_item(mixed names, string desc)
{
    if (query_prop(ROOM_I_NO_EXTRA_ITEM)) return 0;
    if (!pointerp(names)) names = ({ names });
    if (obj_items) obj_items = obj_items + ({ ({ names , desc }) });
    else obj_items = ({ ({ names , desc }) });
}

/*
 * Function name: set_add_item
 * Description:   Sets the 'pseudo items' of an object.
 * Arguments:     pseudo_items - a mixed array of pseudo items to be added.
 */
public void
set_add_item(mixed pseudo_items)
{
   obj_items = pseudo_items;
}

/*
 * Function name: query_item
 * Description:   Get the additional items array.
 * Returns:	  Item array, see below:

  [0] = array
     [0] ({ "name1 of item1", "name2 of item1",... })
     [1] "This is the description of the item1."
  [1] = array
     [0] ({ "name1 of item2", "name2 of item2", ... })
     [1] "This is the description of the item2."
*/
public mixed
query_item() 
{ 
    return obj_items; 
}

/*
 * Function name: remove_item
 * Description:   Removes one additional item from the additional item list
 * Arguments:	  name: name of item to remove.
 * Returns:	  True or false. (True if removed successfully)
 */
public int
remove_item(string name)
{
    int i;
    
    if (!pointerp(obj_items))
	return 0;
    
    if (query_prop(ROOM_I_NO_EXTRA_ITEM))
	return 0;
    for (i = 0; i < sizeof(obj_items); i++)
	if (member_array(name, obj_items[i][0]) >= 0 )
	{
	    obj_items = exclude_array(obj_items, i, i);
	    return 1;
	}
    return 0;
}

static string gExcmd;

/*
 * Function name: query_item_rest_command
 * Description:   Give the rest of the command given when executing a cmditem
 *                command, ie 'from stream' when 'get flower from stream'
 * Returns:       The rest of the command
 */
public string query_item_rest_command() 
{ 
    return gExcmd; 
}

/*
 * Function name: cmditem_action
 * Description:   Find and execute a command for a specific command item
 * Arguments:     str: The rest of the command
 */
public int
cmditem_action(string str)
{
    /* Here we search all commanditems and try out the command
       This is a LOT of cpu, maybe a simpler system will have to suffice
    */

    int il, pos;
    string *words, ex, verb, rest;

    if (!sizeof(obj_cmd_items))
	return 0;

    verb = query_verb();
    notify_fail(capitalize(verb) + " what?\n");
    if (!str)
	return 0;

    for (il = 0; il < sizeof(obj_cmd_items); il++)
    {
	if ((pos = member_array(verb, obj_cmd_items[il][1])) < 0)
	    continue;
        if (pos >= sizeof(obj_cmd_items[il][2])) pos = 0;

	words = obj_cmd_items[il][0] + ({});
	if (parse_command(str, ({}), "%p %s", words, rest))
	{
	    gExcmd = rest;
	    ex = check_call(obj_cmd_items[il][2][pos]);
	    if (stringp(ex))
	    {
		write(ex);
		return 1;
	    } else {
	        if (!ex)
		    continue;
	    	else
		    return 1;
	    }
	}
    }
    return 0;
}

/*
 * Function name: add_cmd_item
 * Description:   Adds a specific item with associated commands to the
 *		  object. These are similar to the normal items but
 *		  they add commands which can then executed by players.
 *                The first argument is a single string or an array of 
 *      	  strings holding the possible name(s) of the item.
 *		  The second argument is the command / description array of 
 *		  the item. add_cmd_item can be repeatedly called with 
 *		  new items.
 * Arguments:	  names: Alternate names for the item, 
 *                cmd_arr:  Commands to give to get the desc
 *		  desc_arr: descs of the item for each command
 * Returns:	  True or false.
*/
public int
add_cmd_item(mixed names, mixed cmd_arr, mixed desc_arr)
{
    if (query_prop(ROOM_I_NO_EXTRA_ITEM)) return 0;
    if (!pointerp(names)) names = ({ names });
    if (!pointerp(cmd_arr)) cmd_arr = ({ cmd_arr });
    if (!pointerp(desc_arr)) desc_arr = ({ desc_arr });
    if (!pointerp(obj_commands)) obj_commands = ({ });

    if (obj_cmd_items) 
	obj_cmd_items = obj_cmd_items + ({ ({ names , cmd_arr, desc_arr }) });
    else obj_cmd_items = ({ ({ names , cmd_arr, desc_arr }) });

    if (sizeof(cmd_arr))
	obj_commands = obj_commands + (cmd_arr - (cmd_arr & obj_commands));
}

/*
 * Function name: query_cmd_item
 * Description:   Get the command items array.
 * Returns:	  Item array, see below:

  [0] = array
     [0] ({ "name1 of item1", "name2 of item1",... })
     [1] ({ "command1", "command2", .... "commandN" })
     [2] ({ 
	    "string to print if command1 given",
	    "string to print if command2 given",
	           ......
	    "string to print if commandN given",
         })

  Example:
  	({ 
	    ({ "flower", "viola" }), 
	    ({ "smell", "taste", "get" }),
	    ({ "It smells nice", "It tastes awful!", "@@tryget" }),
	})

*/
public mixed
query_cmd_item() 
{  
    return obj_cmd_items; 
}
    
/*
 * Function name: remove_cmd_item
 * Description:   Removes one command item from the command item list
 * Arguments:	  name: name of item to remove.
 * Returns:	  True or false. (True if removed successfully)
 */
public int
remove_cmd_item(string name)
{
    int i, il;
    string *cmd_arr;
    
    if ( !pointerp(obj_cmd_items) ) return 0;
    
    if (query_prop(ROOM_I_NO_EXTRA_ITEM)) return 0;
    for ( i = 0; i<sizeof(obj_cmd_items); i++)
	if ( member_array(name, obj_cmd_items[i][0])>=0 )
	{
	    obj_cmd_items = exclude_array(obj_cmd_items,i,i);
	    obj_commands = ({});
	    for (il = 0; il < sizeof(obj_cmd_items); il++)
	    {
		cmd_arr = obj_cmd_items[il][1];
		if (sizeof(cmd_arr))
		    obj_commands = obj_commands + 
			(cmd_arr - cmd_arr & obj_commands);
	    }
	    return 1;
	}
    return 0;
}

/*
 * Function name: set_trusted
 * Description:   Sets the effuserid to the userid of this object. This is
 *		  used by the 'trust' command mainly on wiztools.
 * Arguments:	  arg - 1 = set the euid of this object.
 *	      		0 = remove the euid.
 */
public void
set_trusted(int arg) 
{
    object cobj;

    cobj = previous_object();

    if (!cobj)
	return;

    if (geteuid(cobj) != getuid(this_object()) && geteuid(cobj) !=
	(string) SECURITY->query_domain_lord(getuid(this_object())) &&
	WIZ_TYPE(SECURITY->query_wiz_level(geteuid(cobj))) < WIZ_ARCH &&
	geteuid(cobj) != ROOT_UID)
	return;

    if (arg)
	seteuid(getuid(this_object())); 
    else
	seteuid(0);
}

/*
 * Function name: add_prop_obj_i_broken
 * Description  : This function automatically adds the adjective
 *                "broken" when the property OBJ_I_BROKEN is set.
 * Arguments    : value - the value of the property set
 * Returns      : 0 - always, the prop may be set.
 */
public int
add_prop_obj_i_broken(mixed value)
{
    if (value)
        set_adj("broken");
    else
        remove_adj("broken");

    return 0;
}

/*
 * Function name: remove_prop_obj_i_broken
 * Description  : This function is automatically called to remove the
 *                adjective "broken" if OBJ_I_BROKEN is removed.
 * Returns      : 0 - always, the prop may be removed.
 */
public int
remove_prop_obj_i_broken()
{
    remove_adj("broken");

    return 0;
}

/*
 * Function name: cut_sig_fig
 * Description:   Will reduce the number given to a new number with two
 *		  significant numbers.
 * Arguments:	  fig - the number to correct.
 * Returns:	  the number with two significant numbers
 */
public int
cut_sig_fig(int fig)
{
    int fac;
    fac = 1;

    while(fig > 100)
    {
    	fac = fac * 10;
    	fig = fig / 10;
    }
    return fig * fac;
}

/*
 * Function name: appraise_value
 * Description:   This function is called when someon tries to appraise value
 *		  of this object.
 * Arguments:     num - use this number instead of skill if given.
 */
public string
appraise_value(int num)
{
    int value, skill, seed;

    if (!num)
	skill = this_player()->query_skill(SS_APPR_VAL);
    else
	skill = num;

    skill = 1000 / (skill + 1);
    value = query_prop(OBJ_I_VALUE);
    sscanf(OB_NUM(this_object()), "%d", seed);
    skill = random(skill, seed);
    value = cut_sig_fig(value + (skill % 2 ? -skill % 70 : skill) *
	value / 100);

    return value + " cc";
}

/*
 * Function name: appraise_weight
 * Description:   This function is called when someon tries to appraise weight
 *                of this object.
 * Arguments:     num - use this number instead of skill if given.
 */
public string
appraise_weight(int num)
{
    int value, skill, seed;

    if (!num)
        skill = this_player()->query_skill(SS_APPR_OBJ);
    else
	skill = num;

    skill = 1000 / (skill + 1);
    value = query_prop(OBJ_I_WEIGHT);
    sscanf(OB_NUM(this_object()), "%d", seed);
    skill = random(skill, seed);
    value = cut_sig_fig(value + (skill % 2 ? -skill % 70 : skill) *
        value / 100);

    if (value > 10000)
	return (value / 1000) + " kilograms";
    else
	return value + " grams";
}

/*
 * Function name: appraise_volume
 * Description:   This function is called when someon tries to appraise volume
 *                of this object.
 * Arguments:     num - use this number instead of skill if given.
 */
public string
appraise_volume(int num)
{
    int value, skill, seed;

    if (!num)
        skill = this_player()->query_skill(SS_APPR_OBJ);
    else
	skill = num;

    skill = 1000 / (skill + 1);
    value = query_prop(OBJ_I_VOLUME);
    sscanf(OB_NUM(this_object()), "%d", seed);
    skill = random(skill, seed);
    value = cut_sig_fig(value + (skill % 2 ? -skill % 70 : skill) *
        value / 100);

    if (value > 10000)
	return (value / 1000) + " liters";
    else
        return value + " milliliters";
}

/*
 * Function name: appraise_object
 * Description:   This function is called when someon tries to appraise this
 *		  object.
 * Arguments:    num - use this number instead of skill if given.
 */
public void
appraise_object(int num)
{
    write(this_object()->long() + "\n");
    write(break_string("You appraise that the weight is " +
	appraise_weight(num) + " and you guess its volume is about " +
	appraise_volume(num) + ".\n", 75));
    write("You estimate its worth to " + appraise_value(num) + ".\n");
    if (this_object()->check_recoverable() == 1)
	write("This object seems to be able to last a while.\n");
}

/*
 * Function name: check_recoverable
 * Description:   This function checks if the object can be stored as
 *                recoverable or not.
 * Arguments    : flag - if this flag is true, then the may_not_recover
 *                       function is not called. This is done to allow
 *                       a 'fails to glow' message.
 * Returns:       1 / 0 depending on outcome.
 */
public nomask varargs int
check_recoverable(int flag)
{
    string str, path, arg;

    /* Armours and weapons have a chance to fail on recovery.
     */
    if (!flag && this_object()->may_not_recover())
    {
	return 0;
    }

    /* Check for recover string */
    str = (string)this_object()->query_recover();
    if (strlen(str) > 0)
    {
	if (sscanf(str, "%s:%s", path, arg) != 2)
	{
	    path = str;
	    arg = 0;
	}

	/* Check for arg to be <= 128 bytes long */
	if (strlen(arg) <= 128)
	    return 1;
    }

    return 0;
}


/*
 * Function namn: query_value
 * Description:   Does the same thing as query_prop(OBJ_I_VALUE)
 *		  but is needed since unique_array() doesn't send an
 *		  argument.
 * Returns:	  The value
 */
int
query_value() 
{ 
    return query_prop(OBJ_I_VALUE); 
}

/*
 * Function name: search_now
 * Description:   Perform the search now.
 * Arguments:	  arr - An array consisting of ({ searcher, str })
 */
void
search_now(mixed *arr)
{
    string fun, hidden,new_line;
    object *live, *dead, *found, *everyone, *temp;
    int i;

    if (query_prop(ROOM_I_IS))
    {
        everyone= all_inventory(this_object());
	
        found = filter(everyone, "search_hidden", this_object(), arr[0]);
        if (sizeof(found))
        {
            dead = filter(found, "is_live_dead", this_object(), 0);
            live = filter(found, "is_live_dead", this_object(), 1);
	}

	/* I am aware of that this is not the nicest way....but it seems
	   to be the only way....at least right now  /Dumrik */
	
	if(sizeof(live) || sizeof(dead)) 
	{
	    if (!sizeof(dead))
		new_line = "\n";
	    else
		new_line = "";
	    
	    if(sizeof(live)) 
	    {
		temp = everyone - live - ({ arr[0] });
		arr[0]->catch_msg("You find " + COMMAND_DRIVER->desc_many(live) +
				  new_line);
		
		if (sizeof(temp)) 
		{
		    temp->catch_msg(QCTNAME(arr[0]) + " finds " +
				    COMMAND_DRIVER->desc_many(live) + new_line);
		}
		
		live->catch_msg(QCTNAME(arr[0]) + " finds you.\n");
		
		if (sizeof(live) > 1) 
		{
		    for(i=0;i<sizeof(live);i++) 
		    {
			temp = live - ({ live[i] });
			live[i]->catch_msg(QCTNAME(arr[0]) + " finds " +
					   COMMAND_DRIVER->desc_many(temp) + new_line);
		    }
		}
	    }
	    
	    if (sizeof(dead) && !sizeof(live)) 
	    {
		hidden = COMPOSITE_DEAD(dead);
		arr[0]->catch_msg("You find " + hidden + "\n");
		temp = everyone - ({ arr[0] });
		temp->catch_msg(QCTNAME(arr[0]) + " finds " + hidden + "\n");
	    }
	    
	    if (sizeof(dead) && sizeof(live)) 
	    {
		hidden = COMPOSITE_DEAD(dead);
		arr[0]->catch_msg(" and " + hidden + "\n");
		temp = everyone - ({ arr[0] });
		temp->catch_msg(" and " + hidden + "\n");
	    }
	}
    }

    fun = query_prop(OBJ_S_SEARCH_FUN);
    if (fun)
	fun = call_other(this_object(), fun, arr[0], arr[1]);
    if (strlen(fun))
	tell_object(arr[0], fun);
    else
	if (!sizeof(found))
	    tell_object(arr[0], "Your search reveals nothing special.\n");
}

int
is_live_dead(object obj, int what)
{
    if (living(obj))
	return what == 1 ? 1 : 0;
    else
	return what == 1 ? 0 : 1;
}

int
search_hidden(object obj, object who)
{
    if (!obj->query_prop(OBJ_I_HIDE))
	return 0;

    if (who && !who->query_wiz_level() &&
	    who->query_skill(SS_AWARENESS) < 
		obj->query_prop(OBJ_I_HIDE))
	return 0;
    obj->remove_prop(OBJ_I_HIDE);
    return 1;
}

/*
 * Function name: search_object
 * Description:   Someone tries to search this object
 * Arguments:     str - The string searched
 */
void
search_object(string str)
{
  int time;
  object obj;
  
  time = query_prop(OBJ_I_SEARCH_TIME) + 5;
  
  if (!time || time < 1)
    search_now(({ this_player(), str }));
  else {
    call_out("search_now", time, ({ this_player(), str }) );
    seteuid(getuid(this_object()));
    obj = clone_object("/std/paralyze");
    if (query_prop(ROOM_I_IS))
      obj->set_standard_paralyze("searching");
    else
      obj->set_standard_paralyze("searching " + short(this_player()));
    obj->set_stop_fun("stop_search");
    obj->set_remove_time(time);
    obj->move(this_player());
  }
}

/*
 * Function name: stop_search
 * Description:   This function is called if the player decides to stop his
 *		  search.
 * Arguments:	  arg - If string extra string when player made a command
 *		  if object, the time ran out on the paralyze.
 * Returns:	  If this function should not allow the player to stop search
 *		  it shall return 1.
 */
varargs int
stop_search(mixed arg)
{
    if (!objectp(arg))
    	remove_call_out("search_now");
    return 0;
}

/*
 * Function name: stat_object
 * Description:   This function is called when a wizard wants to get more 
 *		  information about an object.
 * Returns:       str - The string to write..
 */
string
stat_object()
{
    string str, tstr;
    mixed tmp;

    str = "File: " + file_name(this_object()) + ", Creator: " + 
	creator(this_object()) + ", Uid: " + getuid(this_object()) + 
	", Euid: " + geteuid(this_object()) + "\n";
    if (tstr = query_prop(OBJ_S_WIZINFO))
	str += "Special info:\n\t" + tstr;
    str += "Name: " + query_name() + " \t";
    str += "Short: " + short() + "\n";
    str += "Long: " + long();

    tstr = "";
    if (tmp = query_prop(OBJ_I_WEIGHT))
	tstr += "Ob Weight: " + tmp + " \t";
    if (tmp = query_prop(OBJ_I_VOLUME))
	tstr += "Ob Volume: " + tmp + " \t";
    if (tmp = query_prop(OBJ_I_VALUE))
	tstr += "Ob Value: " + tmp + "";
    if (strlen(tstr))
	str += tstr + "\n";

    tstr = "";
    if (tmp = query_prop(OBJ_I_HIDE))
	tstr += "hidden\t";
    if (tmp = query_prop(OBJ_I_INVIS))
	tstr += "invis\t";
    if (tmp = query_prop(MAGIC_AM_MAGIC))
	tstr += "magic\t";
    if (query_no_show())
	tstr += "no_show\t";
    if (!query_no_show() && query_no_show_composite())
	tstr += "no_show_composite\t";
    if ((this_object()->query_recover()) &&
	(!(this_object()->may_not_recover())))
	tstr += "recoverable";
    if (strlen(tstr))
	str += tstr + "\n";

    return str;
}

/*
 * Function name: query_alarms
 * Description:   This function gives all alarms set in this object.
 * Returns:       The list as given by get_all_alarms.
 */
mixed
query_alarms()
{
    return get_all_alarms();
}





