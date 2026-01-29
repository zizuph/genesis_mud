inherit "/std/room";
inherit "/d/Genesis/specials/lib/item_recovery_lib";

#include "../guild.h"

#include <files.h>
#include <macros.h>
#include <stdproperties.h>

#define GSTAT_MOD   15

/*
 * Function name:   cloned
 * Description:     Cloning indicator
 * Arguments:       None
 * Returns:         (status) 1 - A clone
 *                  (status) 0 - Not a clone
 */
public status
cloned()
{
    string name = file_name(this_object());
    
    if (member_array(name, ({ RACK_COPY, STD_RACK })) > -1)
        return 1;
    
    return 0;
}

/*
 * Function name:   create_room
 * Description:     Basic constructor
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_room()
{
    setuid();
    seteuid(getuid());
 
    set_short("thief rack");
    set_long("The personal rack of a thief.\n");

    if (cloned())
        return;

    set_enable_logging(0);
    set_enable_recovery(1);

    init_database();    
    set_alarm(0.0, 0.0, &recover_objects_from_database());
} /* create_room */

/*
 * Function name:   reset_room
 * Description:     This function has been redefined to make the room reset
 * Arguments:       None
 * Returns:         Nothing
 */
void
reset_room()
{
    if (cloned())
        return;
    
    if (!sizeof(all_inventory(this_object())))
    {
        rm(file_name(this_object()) + "_data.o");
        rm(file_name(this_object()) + ".c");
        remove_object();
    }
} /* reset_room */
 
/* 
 * Function name:   enter_inv
 * Description:     Called when objects enter this container or when an
 *                  object has just changed its weight/volume/light status.
 * Arguments:       (object) ob: The object that just entered this inventory
 *                  (object) from: The object from which it came.
 * Returns:         Nothing
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    // Not actually entering this container, just return
    if (from == this_object())
        return;
    
    add_rack_entry(ob);
} /* enter_inv */

/* 
 * Function name:   leave_inv
 * Description:     Called when objects leave this container or when an
 *                  object is about to change its weight/volume/light status.
 * Arguments:       (object) ob: The object that just left this inventory.
 *                  (object) to: Where it went.
 * Returns:         Nothing
 */
public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    // Not actually leaving this container, just return
    if (to == this_object() || !objectp(to))
        return;
    
    remove_rack_entry(ob);
} /* leave_inv */

/*
 * Function name:   filter_allow_rack
 * Description:     Filter out any items that cannot be dropped, given etc
 * Arguments:       (object) ob - the object to check
 * Returns:         (int) -7: Failed: Living object
 *                  (int) -6: Failed: Rack is full
 *                  (int) -5: Failed: Cannot be dropped or given
 *                  (int) -4: Failed: Cannot be inserted
 *                  (int) -3: Failed: Broken item
 *                  (int) -2: Failed: Worn or wielded
 *                  (int) -1: Failed: Kept item
 *                  (int)  0: Failed: Not an armour or weapon
 *                  (int)  1: Success
 */
public int
filter_allow_rack(object ob)
{
    object  player;
    int     mod;
    
    if (living(ob))
    {
        if (!ob->query_wiz_level())
            return -7;
        
        return 1;
    }
    
    if (!objectp(player = this_player()))
        player = environment(ob);
    
    mod = player->query_stat(SS_LAYMAN) / GSTAT_MOD;
    if (mod <= sizeof(all_inventory(this_object())))
        return -6;

    // Check for the various properties
    if (ob->query_prop(OBJ_M_NO_DROP) ||
        ob->query_prop(OBJ_M_NO_GIVE))
        return -5;
        
    if (ob->query_prop(OBJ_M_NO_INS))
        return -4;
    
    if (ob->query_prop(OBJ_I_BROKEN))
        return -3;
    
    if (ob->query_worn() || ob->query_wielded() || ob->query_held())
        return -2;
    
    if (ob->query_keep())
        return -1;

    if (!IS_WEAPON_OBJECT(ob) && !IS_ARMOUR_OBJECT(ob))
        return 0;
    
    return 1;
} /* filter_allow_rack */

/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     (object) ob - the object that is trying to enter.
 * Returns:       (int) 1 - The object is not allowed to enter
 *                (int) 0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    int value;
    
    if (!objectp(this_player()))
        set_this_player(environment(ob));
    
    switch(value = filter_allow_rack(ob))
    {
        case -7:
        write("A rack is no place for the living.\n");
            break;
        case -6:
        write("There is no more room in the rack.\n");
            break;
        case -5:
        write("The " + ob->short() + " cannot be dropped.\n");
            break;
        case -4:
        write("The " + ob->short() + " does not seem to fit in there.\n");
            break;
        case -3:
        write("The rack is no place for broken items.\n");
            break;
        case -2:
        write("You are using that, maybe you should "
        + (objectp(ob->query_wielded()) ? "unwield" :
        (objectp(ob->query_worn()) ? "remove" : "release"))
        + " it first?\n");
            break;
        case -1:
        write("The " + ob->short() + " has been forcefully kept.\n");
            break;
        case  0:
        write("You may only place weapons and armours in the rack.\n");
            break;
        default:
            break;
    }
    
    return !(value > 0);
} /* prevent_enter */