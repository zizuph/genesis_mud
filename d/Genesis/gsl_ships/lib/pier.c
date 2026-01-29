/*
 * Standard pier - library form
 * TAPAKAH, 2007
 */

#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <options.h>
#include "../ships.h"

static object       sign;

object
query_sign ()
{
  return sign;
}

/*
 * Function:    initialize_pier
 * Description: This function clones the default Genesis ShipLines sign
 *              If you wish to make a custom sign, make sure you mask
 *              this function and clone your own.
 */
public void
initialize_pier()
{
    this_object()->add_prop(ROOM_I_HAS_PIER, 1);
    
    if (!objectp(query_sign()))
    {
        setuid();
        seteuid(getuid());

        mapping row = PIER_DATABASE->query_row_by_filename(MASTER_OB(this_object()));
        if (mappingp(row) && strlen(row["sign"]))
        {
            sign = clone_object(row["sign"]);
        }
        else
        {
            sign = clone_object(STDSIGN);
        }
        sign->move(this_object());
    }
    
    SHIP_MANAGER->configure_all_signs();
}

varargs string
get_pier_description (object observer = TP, int precision = 0)
{
    string description;
    object *items;

    description = this_object()->long();
    items = FILTER_CAN_SEE(all_inventory(this_object()), observer);
    items -= ({ observer });

    if (items)
    {
        if (sizeof(FILTER_DEAD(items)))
        {
            description += capitalize(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
        }
        if (sizeof(FILTER_LIVE(items)))
        {
            description += capitalize(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
        }
    }
    return description;
}

public int
add_pier_entry(string filename, string port, string description)
{
    setuid();
    seteuid(getuid());
    
    PIER_DATABASE->add_pier_entry(filename, port, description);
}

public int
is_in_service ()
{
  object ship;
  ship = present("ship", this_object());

  if(ship->query_deck())
    return 1;
  return 0;
}

object *
want_silence ()
{
  object *listeners, *quiet, *all_present;
  
  all_present = FILTER_LIVE(all_inventory(this_object()));
  quiet = filter(all_present, &->query_option(OPT_SILENT_SHIPS));
  listeners = all_present - quiet;

  return quiet;
}
