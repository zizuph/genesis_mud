/*
 * Filename:        smith_rack.c
 * Description:     A box for storing herbs
 *
 * Coded by Daniel W. Mathiasen aka Boron
 *
 * Revision history:
 *
 * October 20, 2010 - Added auto-save functionality, Petros
 */
inherit "/std/container";
// Step 1. Inherit the Recovery Library
inherit "/d/Genesis/specials/lib/item_recovery_lib"; 

#include "/d/Krynn/common/defs.h"
#include "../../guild.h"
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

void
create_container()
{
  set_name("rack");
  add_name(({"box", "armoury"}));
  set_adj(({"light", "green"}));

  set_short("light green rack");
  set_long("Your eyes behold an well used rack. The wooden structure "
           + "is as clear as on a newly cut tree. Here Knights store the "
           + "herbs which have been supplied to them by allies.\n\n");

  add_prop(CONT_I_MAX_WEIGHT,  3000000); /* 2000 kilos */
  add_prop(CONT_I_MAX_VOLUME,  2000000); /* 2000 liters */
  add_prop(CONT_I_WEIGHT, 20000);
  add_prop(CONT_I_VOLUME, 160000);
  add_prop(CONT_I_RIGID, 1);
  add_prop(OBJ_M_NO_GET, "The rack is bolted to the wall..\n");

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

int
prevent_leave(object ob)
{
    if (MEMBER(TP))
    return 0;

   if(TP->query_wiz_level())
      return 0;
   write("A squire arrives and informs you not to remove the " +
      "items from the rack.\n");
   return 1;
}

static mixed
check_insert()
{
    int     i = 1;
    object  obj;

    while (objectp(obj = previous_object(--i)))
    {
        if (obj == TO)
        {
            if (IS_HERB_OBJECT(TO))
                return 0;
            else
                return "You can only put herbs in the "+query_name()+".\n";
        }
    }
    return "You can only put herbs in the "+query_name()+".\n";
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
