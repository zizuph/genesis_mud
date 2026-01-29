/*
 * Filename:        glow_rack.c
 * Description:     A box which only allows glowing items to enter.
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
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

void
create_container()
{
  set_name("rack");
  add_name( ({"box", "armoury", "weaponry"}) );
  set_adj("dark-brown");
  add_adj( ({"solid", "oak", "newer", "steel"}) );

  set_short("solid oak rack");
  set_long("This is the newer rack of solid oak binded with steel "
            + "bracers still smells of fresh wood, and the bindings "
            + "shine in torchlight. Constructed several years after "
            + "the Cataclysm, this rack proved indispensable...\n"
            + "For the main one could no longer hold the blessed armours "
            + "and swords of Knights who fell in desperate struggles at "
            + "a time when Gods abandoned us. Now, however, its role has "
            + "changed. The Knighthood blooms again, and many a fine young "
            + "man seek the elder Knights out in an attempt to become knights "
            + "themselves. Here you may place equipment of lesser quality, "
            + "or one you presume will not last long. Knights and Squires "
            + "alike serve with these weapons.\n\n");

  add_prop(CONT_I_MAX_WEIGHT,  3000000); /* 2000 kilos */
  add_prop(CONT_I_MAX_VOLUME,  2000000); /* 2000 liters */
  add_prop(CONT_I_WEIGHT, 20000);
  add_prop(CONT_I_VOLUME, 160000);
  add_prop(CONT_I_RIGID, 1);
  add_prop(OBJ_M_NO_GET, "The rack is bolted to the wall.\n");

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
prevent_enter(object ob)
{
    if ( !( (IS_ARMOUR_OBJECT(ob)) || (IS_WEAPON_OBJECT(ob)) )  )
    {
        write("As " + ob->short() + " isn't an armour "
                        + "or a weapon you decide to keep it.\n");
        return 1;
    }
    else if ( (IS_ARMOUR_OBJECT(ob)) && (ob->query_worn()) )
    {
        write("Remove the " + ob->short() + " if you wish to rack it.\n");
        return 1;
    }
    else if ( IS_WEAPON_OBJECT(ob) && ob->query_wielded() )
    {
        write("Unwield the " + ob->short() + " if you wish to rack it.\n");
        return 1;
    }
    else if ( ob->check_recoverable() )
    {
        write("You throw a quick glance at the " + ob->short()
                        + " and decide it wouldn't fit into this rack.\n");
        return 1;
    }

    return 0;
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
