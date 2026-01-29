/* 
 * obj/marker.c
 *
 * Modified from /std/coins.c to make markers.
 *
 * Moved to new casino folder. Aligned with updates in /std/coins , made recoverable
 *  Treacher Oct 2021
 */
#pragma save_binary
#pragma strict_types

inherit "/std/heap";

#include <macros.h>
#include <money.h>
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <std.h>

#define MARKER_TYPES ({"red", "green", "blue"})
#define MARKER_VALUE ({12, 144, 1728})
#define MARKER_WEIGHT 100
#define MARKER_VOLUME 100
#define MARKER_NAME(type) ("_marker_" + (type))

/*
 * Global variable. It holds the marker type.
 */
static string marker_type;

/*
 * Prototypes
 */
void set_marker_type(string str);
string query_marker_type();

/*
 * Function name: create_markers
 * Description  : Called at creation of the markers. To create your own markers
 *                you must define this function.
 */
public void
create_markers()
{
    set_name("marker");
    add_name("_cadu_marker");
    //add_name("coin");
    set_pname("markers");
    add_adj("cadu");
    set_heap_size(1);
    set_marker_type(MARKER_TYPES[0]);
}

/*
 * Function name: create_heap
 * Description  : Constructor. This will create the heap and set some stuff
 *                that we want. You may not mask this function. You have to
 *                use create_markers() to create your own markers.
 */
public nomask void
create_heap()
{
    set_heap_size(1);
 
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);

    create_markers();
    
    if (!query_prop(HEAP_S_UNIQUE_ID))
    {
        set_marker_type(MARKER_TYPES[0]);
    }
}

/*
 * Function name: reset_markers
 * Description  : In order to have some code executed when this heap of
 *                markers resets, mask this function. Notice that in order
 *                to make them reset, call enable_reset() from the function
 *                create_markers().
 */
public void
reset_markers()
{
}

/*
 * Function name: reset_heap
 * Description  : Called to make this heap reset. You may not mask this
 *                function, so use reset_markers() instead.
 */
public nomask void
reset_heap()
{
    reset_markers();
}

/*
 * Function name: query_auto_load
 * Description  : Markers are autoloading. This function is called to find
 *                out whether they are. It returns the marker type and the
 *                number of markers in this heap.
 * Returns      : string - the auto-load string.
 */
 public string
 query_auto_load()
 {
     /* Don't auto load if we are about to destroy. */
     if (query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
         return 0;
 
     return (MASTER + ":" + num_heap() + "," + marker_type);
 }

 /* 
 * Function name: init_arg
 * Description  : Called when autoloading. It will set the type of markers
 *                and the number of markers in the heap.
 * Arguments    : string arg - the auto-load argument.
 */
void
init_arg(string arg)
{
    int sum;
    string ct;

    if (sscanf(arg, "%d,%s", sum, ct) == 2)
    {
	    set_heap_size(sum);
	    set_marker_type(ct);
    }
}

/*
 * Function name: short
 * Description  : This function is called to get the short description of
 *                these markers. We make it dependant on the intelligence of
 *                the onlooker and have special cases for different numbers
 *                of markers.
 * Arguments    : object for_object - the object that wants to know.
 * Returns      : string - the short string.
 */
public varargs string
short(object for_object)
{
    string str = ((strlen(marker_type) ? " " : "") + marker_type);

    /* No elements in the heap == no show. */
    if (num_heap() < 1)
    {
        return 0;
    }

    /* No identifier: BAD markers. Remove them. */
    if (!strlen(query_prop(HEAP_S_UNIQUE_ID)))
    {
        set_alarm(0.1, 0.0, remove_object);
        
        return "ghost markers";
    }

    /* One marker, singular, not really a heap. */
    if (num_heap() < 2)
    {
        return "a" + str + " marker";
    }

    /* Less than a dozen, we see the number as a word. */
    if (num_heap() < 12)
    {
        return LANG_WNUM(num_heap()) + str + " markers";
    }

    if (num_heap() == 12)
    {
	    return "a dozen " + str + "markers";
    }

    /* No onlooker, default to this_player(). */
    if (!objectp(for_object))
    {
        for_object = this_player();
    }

    /* If we are smart enough, we can see the number of markers. */
    if (for_object->query_stat(SS_INT) / 2 > num_heap())
    {
        return num_heap() + str + " markers";
    }

    /* Else, default to 'many' or to a 'huge heap'. */
    return (num_heap() < 1000 ? "many" : "a huge heap of") + str + " markers";
}

/*
 * Function name: long
 * Description  : This function will slip the short description into the
 *                long description. Money will always look like good
 *                money, but don't try to fool the shopkeepers with wooden
 *                markers ;-)
 * Returns      : string - the long description.
 */
varargs public mixed
long()
{
    string desc = "";
    string center = "platinum coloured P";

    if ((num_heap() < 2) ||
        (num_heap() >= 1000))
    {
        desc= "It is ";
    }
    else
    {
        desc = "There are ";
    }

    if(query_marker_type() == "red") 
        center = "silvery coloured S";
    else if(query_marker_type() == "green")
        center = "gold coloured G";

    return desc + short() + " from the Cadu casino, ornated with black " +
           "sections stretching out from a big " + center + " in the center.\n";
}

/*
 * Function name: set_marker_type
 * Description  : Set the type of markers we have here. Update all necessary
 *                properties with respect to the markers.
 * Arguments    : string str - the marker type to set.
 */
public void  
set_marker_type(mixed str)
{
    int ix;

    if (intp(str))
    {
        if (str <= 0)
            str = 0;
        if (str >= 2)
            str = 2;
        str = MARKER_TYPES[str];
    }

    /* If this is one of the default marker types, set the weight, volume
     * and value correctly.
     */
    ix = member_array(str, MARKER_TYPES);
    if (ix >= 0)
    {
        mark_state();
        add_prop(HEAP_I_UNIT_VALUE, MARKER_VALUE[ix]);
        add_prop(HEAP_I_UNIT_WEIGHT, MARKER_WEIGHT);
        add_prop(HEAP_I_UNIT_VOLUME, MARKER_VOLUME);
        update_state();
    }

    /* If there is a marker-type, remove that marker type as adjective. */
    if (marker_type)
    {
        remove_adj(marker_type);
        remove_name(MARKER_NAME(marker_type));
    }

    /* Set the new marker type and set it as an adjective. Also, we update
     * our identifier.
     */
    marker_type = str;
    add_prop(HEAP_S_UNIQUE_ID, "_marker_" + marker_type);
    set_adj(marker_type);
    add_name(MARKER_NAME(marker_type));
}

/*
 * Function name: query_marker_type
 * Description  : Return what type of markers we have.
 * Returns      : string - the marker type.
 */
public string
query_marker_type()
{
    return marker_type;
}

/*
 * Function name: config_split
 * Description  : When a part of this heap is split, we make sure the new
 *                heap is made into the correct type of markers as well by
 *                setting the marker type to the marker type of the heap we are
 *                being split from.
 * Arguments    : int new_num - the number of markers in this new heap.
 *                object orig - the heap we are split from.
 */
public void
config_split(int new_num, object orig)
{
    ::config_split(new_num, orig);

    set_marker_type(orig->query_marker_type());
}

/*
 * Function name: stat_object
 * Description  : When a wizard stats this heap of markers, we add the marker
 *                type to the information.
 * Returns      : string - the stat-description.
 */
public string
stat_object()
{
    return ::stat_object() + "Marker type: " + marker_type + "\n";
}

int
query_is_marker()
{
    return 1;
}

public void
remove_marker()
{
    if (leave_behind > 0)
    {
        set_heap_size(leave_behind);
    }
    else
    {
        remove_object();
    }
}
