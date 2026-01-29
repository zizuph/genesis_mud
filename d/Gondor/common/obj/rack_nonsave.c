// 2007/08/14 ? Previous update
// 2010/11/09 Lavellan  Update for new saving rack system
// 2011/08/29 Lavellan  Fix for change to Avenir code...
//                      Disabled hidden broken "netrack list"
// January 2020 Finwe, Copied from Halfling Guild and converted to ME
//      This rack does not track donated items.

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"

inherit "/std/container";
inherit "/d/Faerun/std/rack_shop_list";
inherit "/d/Genesis/specials/lib/item_recovery_lib";

#define SHADOW  ("/d/Faerun/std/rack_shelf_shadow")

#define MAX_SORT  150

// #define SHELF_LOG_GET  ("/d/Faerun/faerun_logs/nov_shelf_get")
// #define SHELF_LOG_PUT  ("/d/Faerun/faerun_logs/nov_shelf_put")

#define DONATE   "donate"
#define BORROW   "borrow"


#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 5000) ? (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif

/* mapping donate = ([
 *   (string)name: ([ (string)how: ({ ({ (string)what, (int)time, }), }), ]),
 *   ]);  */

public void create_rack() {}

static private mapping donate = ([]);

string rack_location = "Along a wall is a large rack";

public int
special_sort(object a, object b)
{
    int v1, v2;

    v1 = a->query_prop(OBJ_I_VOLUME);
    v2 = b->query_prop(OBJ_I_VOLUME);

    if (v1 == v2)
   return 0;
    if (v1 < v2)
   return 1;
    if (v1 > v2)
   return -1;
}

public string
external_within(void)
{
    int size;
    object *obs = all_inventory(TO);
    string str = " " + rack_location;

    if (!(size = sizeof(obs)))
    {
        return str + ".";
    }
    else if (size <= 5)
    {
        return str + ", in it you see " + COMPOSITE_DEAD(obs) + ".";
    }
    else
    {
        obs = sort_array(obs, special_sort)[0..min(4, sizeof(obs) - 1)];
        return str + ", in it, which many items have been stacked, "+
            "including "+ COMPOSITE_DEAD((obs)) + ".";
    }
}


public void
describe_contents(object for_obj, object *obarr)
{
    do_list("all");
}

/*
 * Function name: within
 * Description:   Give a description of items in this container
 */
public string
within(void)
{
    object *stuff;

    if (!query_prop(CONT_I_CLOSED))
    {
       return "";
    }

    if (!sizeof(all_inventory(TO)))
    {
        return " The rack is bare.";
    }

    do_list("all");
    return "";
}

public string
show_help(void)
{
    /*if (!IS_MEMBER(TP))
   return "";*/

    return " Your skilled eyes make out the words 'help rack' etched " +
        "onto the side of the rack.";
}

public void
create_container(void)
{

    set_name("rack");
    set_adj(({"large","steel","sturdy"}));
    set_short("equipment rack");
    set_long("This is a large steel rack. It is set against a wall and " +
        "used to store donated equipment." + "@@show_help@@@@within@@\n");

    remove_prop(CONT_I_TRANSP);

    add_prop(CONT_I_MAX_WEIGHT, 6000000);
    add_prop(CONT_I_MAX_VOLUME, 6000000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 1934);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(OBJ_M_NO_GET, "It does not move.\n");

    set_maxlist(100);
    set_show_price(0);
    config_default_trade();
    set_store_room(file_name(TO));

    if (!IS_CLONE)
    {
        return;
    }

    set_enable_logging(0);
    set_enable_recovery(1);

    init_database();
    set_alarm(0.0, 0.0, &recover_objects_from_database());

    create_rack();
}

public void
update_internal(int l, int w, int v)
{
    sorted_arr = 0;
    ::update_internal(l, w, v);
}

public void
dump_donate(void)
{
    dump_mapping(donate);
}

public int
track_shelf(string str)
{
    string *arr;



    /*if (!this_player()->query_skill(COUNCIL) >= 1)
    {
    	write("What?\n");
    	return 1;
    }*/

    if (!strlen(str))
    {
        return notify_fail("What exactly are you attemping to do?\n "+
            "See 'help rack' for more information.\n");
    }

    arr = explode(str, " ");

    if (sizeof(arr) == 1)
    {
        arr += ({ (string)0 });
    }

    switch(arr[0])
    {
        case "clear":
            if (!arr[1] || !donate[arr[1]])
            {
                write("That individual doesn't appear to have used the rack.\n");
                return 1;
            }

            write("Clear what?\n");
            break;

        case "list _UNUSED_":
        {
            string *who = m_indices(donate);
            int ix, size = sizeof(who);

            if (!size)
            {
                write("Nobody has made use of the rack recently.\n");
                return 1;
            }

            write(capitalize(LANG_NUM2WORD(size)) +
                (size > 1 ? " people" : " person") +
                " has used the rack:\n");

            ix  = -1;
            who = sort_array(who);

            while(++ix < size)
            {
                write(sprintf("%s (%s) has donated %d items while borrowing %d.\n",
                    capitalize(who[ix]),
                    sizeof(donate[who[ix]][DONATE]),
                    sizeof(donate[who[ix]][BORROW])));
            }
        }
            break;
        default:
        {
            string how;
            mixed *items;
            int ix, size, ln;

            if (!donate[arr[0]])
            {
                write(capitalize(arr[0]) +" doesn't appear to have used " +
                    "the rack.\n");
                return 1;
            }

            if (arr[1] == DONATE)
            {
                how = "donated";
            }
            else if (arr[1] == BORROW)
            {
                how = "borrowed";
            }
            else
            {
                write("What information are you trying to query?\n"+
                "See 'help rack' for more information.\n");
                return 1;
            }

            ix = -1;
            items = donate[arr[0]][arr[1]];
            size = sizeof(items);
            ln = strlen((size + 1) + "");

            write(capitalize(arr[0]) +" has "+ how +" the following items:\n");

            while(++ix < size)
            {
                write(sprintf("%*d) %s on %s\n",
                ln, (ix + 1), items[ix][0], ctime(items[ix][1])));
            }
        }
        break;
    }

    return 1;
}

private void
track_donate(object who, object what, string how)
{
    string name = who->query_real_name(), item = what->short();

    if (!donate[name])
        donate[name] = ([]);

    if (!donate[name][how])
        donate[name][how] = ({ });

    donate[name][how] += ({ ({ item, time() }) });
}

public int
prevent_enter(object ob)
{
    string dirty;

    if (living(ob))
    {
        TP->catch_msg(QCTNAME(ob) + " doesn't belong in there.\n");
        return 1;
    }

    if (IS_CONTAINER_OBJECT(ob))
    {
       if (!ob->query_prop(CONT_I_CLOSED))
       clone_object(SHADOW)->shadow_me(ob);
    }
/*
 * We dont need to track who donated what
 * Finwe, Jan 2017
 */
/*
    track_donate(TP, ob, DONATE);
    SCROLLING_LOG(SHELF_LOG_PUT, TP->query_real_name() +
        " put "+ ob->short() +" in the equipment rack.");
*/

    return 0;
}

/*
 * Function name: prevent_leave
 * Description:   only friends and union members may get items.
 */
public int
prevent_leave(object ob)
{
/*
 * We dont need to track who got/donated what
 * Finwe Jan 2017
 */

/*
    ob->remove_union_shelf_shadow();

    track_donate(TP, ob, BORROW);
    SCROLLING_LOG(SHELF_LOG_GET, TP->query_real_name() +
        " got "+ ob->short() +" from the equipment rack.");
    return 0;
*/
}


/*
 * Function name: reject_me
 * Description  : Move item to environment
 * Returns      : 1 = success  0 = fail
 */
public int
reject_me(object ob, object env)
{
    if (!ob->move(env) == 0)
    {
        return 1;
    }

    return 0;
}

/*
 * Function name: check_lasting
 * Description  : check to see if item is recoverable or autoloading
 */
public void
check_lasting(object ob, object env)
{
    if (ob->check_recoverable())
    {
        reject_me(ob, env);
    }

    if (ob->query_auto_load())
    {
        reject_me(ob, env);
    }
}

/*
 * Function name: do_sort
 * Description  : runs inventory through check_lasting.
 */
public void
do_sort(void)
{
    map(all_inventory(this_object()),
         &check_lasting(,environment(this_object())));
}

/*
 * Function name: start sort
 * Description  :
 */
public int
start_sort(string arg)
{
    if (arg != "rack")
    {
        return notify_fail("Sort what? The rack?\n");
    }

    if (sizeof(all_inventory(TO)) < MAX_SORT)
    {
        do_sort();
        write("You sort the equipment rack. Everything that saves falls out onto the floor.\n");
        say(QCTNAME(this_player()) +" sorts the equipment rack.\n");
        return 1;
    }

    notify_fail("There are too many items. Remove some objects and try again.\n");
    return 0;
}

public int
help_shelf(string str)
{
    if (str != "rack" && str != "here")
    {
        return notify_fail("Help what? <help rack>?\n");
    }

    write("Rack Commands:\n"+
//        "\t<rasort rack>. . . . . . . Sort items that will recover.\n" +
        "\t<ralist 'type'>. . . . . . View certain types of gear.\n" +
        "\t<rashow 'item'>. . . . . . Show details of an item.\n" +
//"  <ratrack <who> <donate | borrow> . . . List what has placed or taken.\n" +
        "\t<ravalue 'item'> . . . . . Show value of item.\n\n");

 /* if (this_player()->query_skill(COUNCIL) >= 1)
    {
   write("\nAdditional commands for the High Maguses:\n\n"+
//"  <netrack list>       : List who has used the shelf.\n" +
"  <netrack clear <who> : Clears information on 'who'.\n" +
    }*/

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(help_shelf,  "help");
    add_action(start_sort,  "rasort");
//    add_action(track_shelf, "ratrack");

    add_action(do_list,  "ralist");
    add_action(do_show,  "rashow");
    add_action(do_value, "ravalue");
}

/*
 * Masked to not print a message.
 */
public void
shop_hook_appraise_object(object ob)
{
}

public void
shop_hook_value_asking(string str)
{
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (from == this_object())
    {
        return;
    }

    add_rack_entry(ob);
}


public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (to == this_object() || !objectp(to))
    {
        return;
    }

    remove_rack_entry(ob);
}