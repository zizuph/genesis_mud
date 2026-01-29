#include <macros.h>
#include "../guild.h"

inherit "/std/arrow";

public void
verify_location()
{
    object gBow = calling_object();
    
    if (objectp(gBow) && environment() != gBow->query_magic_quiver())
    {
        object stack;
        stack = gBow->query_projectile_stack();
        stack->set_heap_size(12);
        set_alarm(0.1, 0.0, &remove_object());
    }
}

public status
query_loaded()
{
    return loaded;
}

public void
create_arrow()
{
    set_adj("unearthly");
    add_adj("mistral");
    set_projectile_id("unearthly_mistral_arrow");
    set_hit(58);
    set_pen(58);
    
    add_prop(MAGIC_AM_ID_INFO, ({
        "This is a wind arrow, constructed from purely solidified mana.", 60
    }));
        
    add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
    
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_S_WIZINFO, "A magical arrow cloned by the archer guru "
    + "bow, it is unlimited in supply and vanish when fired.\n");
}

/*
 * Function name: set_broken
 * Description  : This functions sets the broken status of this projectile.
 * Arguments    : int b - The new broken status. 1 - Broken. 0 - Whole.
 */
public void
set_broken(int b)
{
} /* set_broken */

/*
 * Function name: query_broken
 * Description  : Gives information of the broken status of this projectile.
 * Returns      : 1 - Projectile broken. 0 - Projectile whole.
 */
public int
query_broken()
{
    return 0;
} /* query_broken */

/*
 * Function name: query_recover
 * Description  : Called to make this projectile is recoverable, and
 *                to make sure the keep status is kept.
 */
string
query_recover()
{
    return 0;
} /* query_recover */

/*
 * Function name:   add_prop
 * Description:     This has been masked to keep the arrow from being collected.
 * Arguments:       (string) prop - The property string to be added.
 *                  (int) val: The value of the property
 * Returns:         Nothing
 */
public void
add_prop(string prop, mixed val)
{
    if (prop != OBJ_O_BELONGS_TO_ARCHER)
        ::add_prop(prop, val);
} /* add_prop */


/*
 * Function name:   enter_env
 * Description:     Remove the object when entering a non-living environment.
 * Arguments:       (object) from - the object we come from.
 *                  (object) to - the object we are entering.
 *
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (objectp(from) && objectp(to) && from->query_magic_quiver()
        && !living(to))
        set_alarm(0.0, 0.0, &remove_object());
} /* enter_env */