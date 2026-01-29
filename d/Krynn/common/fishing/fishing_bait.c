/*
 *  Inherit this item as a basic bait type.
 *
 *  Arman, March 2021
 */
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/food";
inherit "/lib/keep";

int bait_value;

public void
set_bait_value(int val)
{
    bait_value = val;
}

public int
query_bait_value()
{
    return bait_value;
}

public string
query_bait_quality_description()
{
    string str;
    int val = bait_value;

    switch(val)
    {
        case 0:
            str = "This bait is of very poor quality. You " +
                "wouldn't even waste your time hooking it " +
                "to your rod.\n";
        break;
        case 1..5:
            str = "This bait is suitable for casual fishermen " +
                "who are content to occasionally catch small-" +
                "sized fish.\n";
        break;
        case 6..10:
            str = "This is good bait, used by experienced fishermen " +
            "to catch fish of a sporting size.\n";
        break;
        case 11..20:
            str = "This is exotic bait, used by master fishermen " +
            "hunting the most difficult of fish to catch.\n";
        break;
        default:
            str = "This bait is unfamiliar and most curious! You " +
                "have no clear idea how effective it would be " +
                "at catching fish.\n";
        break;
    }

    return str;
}


public void
create_bait()
{
    // Mask this function to customize the bait type.
    // Make sure query_bait_quality_description is included
    // in the redefinition of set_long.

    set_long("Bait for fishing.\n" +
        "@@query_bait_quality_description");

    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VALUE, 0);
}

public void 
create_food()
{
    set_name("bait");
    add_name("_fishing_bait");

    create_bait();	
}

/*
 * Function name: query_recover
 * Description  : This function is called to see whether this object may
 *                recover. It will only function for food that has a
 *                real file rather than being cloned from /std/food.c
 *                since only the amount of food on the heap is saved.
 */
public string
query_recover()
{
    string file = MASTER;
    /* Don't recover bare /std/drinks since we only recover the amount of
     * drinks and no descriptions.
     */
    if (file == FOOD_OBJECT)
    {
        return 0;
    }
    return file + ":heap#" + num_heap() + "#" + bait_value;
}


/*
 * Function name: init_recover
 * Description  : This function is called when the food recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_recover(string str)
{
    string foobar;
    int    num;

    if (sscanf(str, "%sheap#%d#%s", foobar, num, foobar) == 3)
    {
        set_heap_size(num);
    }

    string *a = explode(foobar,"&&");
    bait_value = atoi(a[0]);
}
