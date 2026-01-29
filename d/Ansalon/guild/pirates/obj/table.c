/*
 * File Name        : table.c
 * By               : Elmore.
 * Inspiration from : The Dragonarmy racks by Milan
 * Date             : Nov. 2000.
 * Description      : This is the table in the droproom.
 *
 *
 * Changes:
 * 17/10-2001    Elmore     Added sort rack, made by Milan.
 *
 *
 */

inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/pirates/local.h"

object king_room = GUILD_ROOM + "pirate_king_room";

void
create_rack()
{
}

void
create_container()
{
    set_name("table");
    set_adj("large");
    add_adj("oakwood");
    set_long("This is a large oakwood table, that has been "+
        "reinforced with tempered steel. It is on this table that "+
        "the Pirates of the Bloodsea drop all of their loot and "+
        "equipment, for others to enjoy.\n");
    add_prop(OBJ_I_VALUE,       0);
    add_prop(CONT_I_ATTACH,     1);
    add_prop(CONT_I_RIGID,      0);
    add_prop(OBJ_M_NO_GET,      1);
    add_prop(CONT_I_WEIGHT,     100000);
    add_prop(CONT_I_VOLUME,     75000);
    add_prop(CONT_I_MAX_WEIGHT, 9000000);
    add_prop(CONT_I_MAX_VOLUME, 9000000);

    create_rack();

    setuid();
    seteuid(getuid());
    
    if (!IS_CLONE)
    {
        return;
    }
    
    // Step 2. Set the options of whether you want to enable logging or recovery
    set_enable_logging(0);
    set_enable_recovery(1);
    
    // Step 3. Initialize the Database and call recover_objects_from_database
    //         using an alarm.
    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());    
}

public int
sort_recover(string str)
{
    int i;
    object *ob, *ob2 = ({});

    if (!(ARMAGEDDON->shutdown_active()))
    {
	NF("Sorting is alloved only during Armageddon.\n");
	return 0;
    }

    if (!strlen(str) ||
      !parse_command(str, E(TP), "[the] %i", ob) ||
      !sizeof(ob = NORMAL_ACCESS(ob, 0, 0)))
    {
	NF(C(query_verb()) + " what?\n");
	return 0;
    }
    if (sizeof(ob) > 1)
    {
	NF(C(query_verb()) + " what?  Be more specific.\n");
	return 0;
    }
    if(ob[0] != TO)
    {
	NF(C(query_verb()) + " what?\n");
	return 0;
    }

    ob = all_inventory(TO);
    if (!sizeof(ob))
    {
	NF("There is nothing to sort on "+short()+".\n");
	return 0;
    }

    for (i=0; i<sizeof(ob); i++)
    {
	if (!ob[i]->check_recoverable())
	    ob2 += ({ ob[i] });
    }
    if (!sizeof(ob2))
    {
	write("Everything on "+short()+" glows.\n");
	return 1;
    }
    ob = ({});

    for (i=0; i<sizeof(ob2); i++)
    {
	if (!ob2[i]->move(E(TO)))
	    ob += ({ ob2[i] });
    }
    if (!sizeof(ob))
    {
	write("You did not sort anything on "+short()+".\n");
	return 1;
    }
    str = COMPOSITE_DEAD(ob);
    write("You sorted "+str+" from "+short()+".\n");
    tell_room(E(TP), QCTNAME(TP)+" sorted "+str+" from "+short()+".\n", TP);
    return 1;
}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
    if ((ARMAGEDDON->shutdown_active()))
        return 0;

    setuid();
    seteuid(getuid());

    if (ob->query_value() > 1000 || ob->query_prop("_magic_am_magic"))
    {
        king_room->log_item("" + extract(ctime(time()), 4, 15)+ " -- "+
                 TP->query_name() + " borrowed: "+
                 ob->short()+ ".");
    }
    return 0;
}


/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container
 *                to see if we allow it to enter.
 * Arguments:     object ob - the object trying to enter
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    if (living(ob))
    {
       write("You can't put THAT thing on the table!\n");
   	   return 1;
    }

    if ((ARMAGEDDON->shutdown_active()))
        return 0;


    setuid();
    seteuid(getuid());

    if (ob->query_value() > 1000 || ob->query_prop("_magic_am_magic"))
    {
        king_room->log_item("" + extract(ctime(time()), 4, 15)+ " -- "+
                 TP->query_name() + " contributed: "+
                 ob->short()+ ".");
    }
    return 0;
}


public void
init()
{
    ::init();
    add_action(sort_recover, "sort");
}
    
/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (from == this_object())
    {
        return;
    }
    
    // Step 4. Add add_rack_entry to enter_inv
    add_rack_entry(ob);
}

/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (to == this_object() || !objectp(to))
    {
        // Not actually leaving this container, just return
        return;
    }
    
    // Step 5. Add remove_rack_entry to leave_inv
    remove_rack_entry(ob);
}
