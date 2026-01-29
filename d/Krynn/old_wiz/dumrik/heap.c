/*
  /std/heap.c

  This is a heap object for things like coins, matches and such stuff.

   Defined functions and variables:


*/
#pragma save_binary

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>

static int      item_count,	/* Number of items in the heap */
                leave_behind;	/* Number of items to leave behind */

/*
 * Description: The stadard create_object
 */
nomask void
create_object()
{
    add_prop(OBJ_I_WEIGHT, "@@heap_weight");
    add_prop(OBJ_I_VOLUME, "@@heap_volume");
    add_prop(OBJ_I_VALUE, "@@heap_value");
    add_prop(OBJ_I_LIGHT, "@@heap_light");
    add_prop(HEAP_I_IS, 1);
    leave_behind = 0;
    this_object()->create_heap();
}

/*
 * Description: The standard reset_object
 */
public nomask void
reset_object()
{
    this_object()->reset_heap();
}

int count(string str);

/*
 * Description: This function is called each time the object 'meet' another
 *		object.
 */
void
init()
{
    add_action(count, "count");
}

/*
 * Description: The weight of the heap, used by OBJ_I_WEIGHT
 */
int
heap_weight()
{
    return query_prop(HEAP_I_UNIT_WEIGHT) * (item_count - leave_behind);
}

/*
 * Description: The volume of the heap, used by OBJ_I_VOLUME
 */
int
heap_volume()
{
    return query_prop(HEAP_I_UNIT_VOLUME) * (item_count - leave_behind);
}

/*
 * Description: The value of the heap, used by OBJ_I_VALUE
 */
int
heap_value()
{
    return query_prop(HEAP_I_UNIT_VALUE) * (item_count - leave_behind);
}

/*
 * Description: The lightvalue of the heap, used by OBJ_I_LIGHT
 */
int
heap_light()
{
    return query_prop(HEAP_I_UNIT_LIGHT) * (item_count - leave_behind);
}

/*
 * Description: Called to restore the heap to its origional state
 */
void
restore_heap()
{
    mark_state();
    leave_behind = 0;
    update_state();
}

/*
 * Description: remove the remove_object call out
 */
void
remove_remove_object_call()
{
    while (remove_call_out("remove_object") != -1);
}

/*
 * Description: Set the size of the heap to num.
 */
void
set_heap_size(int num)
{
    mark_state();

    if(num <= 0)
    {
	call_out("remove_object", 1);
	num = 0;
    }
    item_count = num;

    /*
     * We must update the weight and volume of what we reside in
     */
    update_state();
}

/*
 * Description: Returns the size of the heap.
 */
int
num_heap()
{
    return item_count - leave_behind;
}

/*
 * Description: Called before a pending move of a part of the heap
 *              The heap size / volume is set to the part to be moved
 */
int
split_heap(int num)
{
    mark_state();
    if (item_count <= num)
    {
	leave_behind = 0;
	/* It is ok to return here without updating the state as the
	   entire heap will be moved.
	 */
	return item_count;
    }
    leave_behind = item_count - num;
    call_out("restore_heap", 1);
    update_state();
    return num;
}

/*
 * Description: Get the short description for the heap.
 */
public varargs string
short(object for_obj)
{
    string str, sh;
    
    if (!objectp(for_obj))
	for_obj = this_player();

    sh = ::short(for_obj);

    if (!strlen(query_prop(HEAP_S_UNIQUE_ID)))
    {
	call_out("remove_object", 1);
	return "ghost " + sh;
    }

    if (num_heap() < 1) return 0;
    if (num_heap() < 2) return LANG_ADDART(sh);

    str = this_object()->plural_short(for_obj);
    if (!str)
	str = LANG_PSENT(sh); 

    if (num_heap() < 12) 
	return LANG_WNUM(num_heap()) + " " + str;
    
    if (this_player()->query_stat(SS_INT) / 2 > num_heap())
	return num_heap() + " " + str;

    return (num_heap() < 1000 ? "many" : "a huge heap of") + " " + str;
}

/*
 * Description: Called when heap leaves it's environment
 */
void
leave_env(object env, object dest)
{
    object          ob;

    if (!leave_behind)
	return;

    if (item_count <= leave_behind)
	return;

    if (!geteuid(this_object()))
	seteuid(getuid(this_object()));

    ob = CLONE_COPY;
    ob->config_split(leave_behind, this_object());
    ob->move(env, 1);
    ob->move(env, 0);
    item_count -= leave_behind;
    leave_behind = 0;
}

/*
 * Description: Called when heap enters and environment
 */
void
enter_env(mixed env, object old)
{
    object *ob;
    int i;

    if (!objectp(env))
	env = find_object(env);
    ob = all_inventory(env);
    for (i = 0; i < sizeof(ob); i++)
	if (ob[i] != this_object())
	    if (ob[i]->query_prop(HEAP_I_IS) &&
	    query_prop(HEAP_S_UNIQUE_ID) == ob[i]->query_prop(HEAP_S_UNIQUE_ID))
	    {
		ob[i]->set_heap_size(item_count + ob[i]->num_heap());

		/* item_count = 0; No do, we need the short desc.
 
                   As we need the shortdesc to be correct for the duration
		   of this command, ie 'Blabla drops four something' we
                   must keep this object around intact.
                */

		leave_behind = 0;
		move(ob[i], 1); /* Better place to move it? void? */
		call_out("remove_object", 1);
		return;
	    }
}

/*
 * Function name: query_prop_map
 * Description:   Returns mapping containg all props and their values.
 * Returns:       The obj_props mapping.
 */
public nomask mapping
query_prop_map()
{
    return obj_props;
}

/*
 * Description: This is called before inserting this heap into the game
 */
void
config_split(int new_num, object orig)
{
    int             cp,
                    i;
    item_count = new_num;

    set_name(orig->query_name(1));
    set_pname(orig->query_pname(1));
    set_adj(orig->query_adj(1));

    set_short(orig->query_short());
    set_pshort(orig->query_plural_short());
    set_long(orig->query_long());

    obj_props = orig->query_prop_map();
    add_prop(HEAP_I_IS, 1);
}

int stop(string str);

/*
 * Description: Function called when player gives 'count' command
 */
int
count(string str)
{
    string *tmp;
    int *count_arg, intg;

    if(!str)
        return 0;

    notify_fail("Count what?\n");
    if (!parse_command(str, ({ this_object() }), "%i", tmp))
        return 0;

    intg = this_player()->query_stat(SS_INT);
    /* count_arg contains interval, coins per count and total so far */
    count_arg = ({ 60 / intg, 5 * (intg / 10 + 1), 0 });
    call_out("count_up", count_arg[0], count_arg);
    add_action(stop, "", 1);
    return 1;
}

/*
 * Description: Stop counting the items in the heap.
 */
varargs int
stop(string str)
{
    if (query_verb() == "stop")
    {
        update_actions();
        remove_call_out("count_up");
        write("You stop counting.\n");
        return 1;
    }
    else if (str == "done")
    {
        update_actions();
        return 1;
    }
    else
    {
        write("You are busy counting. You have to stop if you want " +
		"to do something else.\n");
        return 1;
    }
}

/*
 * Description: Count some more, how much depends on intelligence of player
 */
void
count_up(int *count_arg)
{
    count_arg[2] += count_arg[1];
    if (count_arg[2] < num_heap())
    {
        write(count_arg[2] + "\n");
        call_out("count_up", count_arg[0], count_arg);
    }
    else
    {
        write("The last count reached " + num_heap() + ".\n");
        stop("done");
    }
}
/*
 * Function name: appraise_number
 * Description:   This function is called when someon tries to appraise number 
 *                of pices in heap of this object.
 * Arguments:     num - use this number instead of skill if given.
 */
public int
appraise_number(int num)
{
    int value, skill, seed;

    if (!num)
        skill = this_player()->query_skill(SS_APPR_OBJ);
    else
        skill = num;

    skill = 1000 / (skill + 1);
    value = num_heap();
    sscanf(OB_NUM(this_object()), "%d", seed);
    skill = random(skill, seed);
    value = cut_sig_fig(value + (skill % 2 ? -skill % 70 : skill) *
        value / 100);

    return value;
}

/*
 * Description: Called when player tries to appraise the heap.
 */
void
appraise_object(int num)
{
    write(this_object()->long() + "\n");
    write(break_string("You appraise that the weight is " +
	appraise_weight(num) + " and you guess its volume is about " +
	appraise_volume(num) + ".\n", 75));
    write(break_string("You estimate that there are " + appraise_number(num) + 
	" pieces worth approx " + appraise_value(num) + ".\n", 75));
}

/*
 * Function name: stat_object
 * Description:   This function is called when a wizard wants to get more
 *                information about an object.
 * Returns:       str - The string to write..
 */
string
stat_object()
{
    string str;

    str = ::stat_object();

    str += "Num: " + num_heap() + ".\n";

    return str;
}

/*
 * Function name: add_prop_obj_i_value
 * Description:   Hook to avoid wrong settings of OBJ_I_VALUE in a heap
 * Arguments:     val - The value OBJ_I_VALUE is intended to be set to
 * Returns:	  1 - If OBJ_I_VALUE shouldn't get this new setting.
 */
int
add_prop_obj_i_value(mixed val)
{
    if (!stringp(val))
    {
	add_prop(HEAP_I_UNIT_VALUE, val);
	return 1;
    }

    return 0;
}

/*
 * Function name: add_prop_obj_i_volume
 * Description:   Hook to avoid wrong settings of OBJ_I_VOLUME in a heap
 * Arguments:     val - The value OBJ_I_VOLUME is intended to be set to
 * Returns:       1 - If OBJ_I_VOLUME shouldn't get this new setting.
 */
int
add_prop_obj_i_volume(mixed val)
{
    if (!stringp(val))
    {
	add_prop(HEAP_I_UNIT_VOLUME, val);
	return 1;
    }

    return 0;
}

/*
 * Function name: add_prop_obj_i_weight
 * Description:   Hook to avoid wrong settings of OBJ_I_WEIGHT in a heap
 * Arguments:     val - The value OBJ_I_WEIGHT is intended to be set to
 * Returns:       1 - If OBJ_I_WEIGHT shouldn't get this new setting.
 */
int
add_prop_obj_i_weight(mixed val)
{
    if (!stringp(val))
    {
	add_prop(HEAP_I_UNIT_WEIGHT, val);
	return 1;
    }

    return 0;
}


