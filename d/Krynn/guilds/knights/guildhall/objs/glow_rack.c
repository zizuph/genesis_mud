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
  add_name(({"box", "armoury", "weaponry"}));
  set_adj("dark-brown");

  set_short("dark-brown rack");
  set_long("Your eyes behold an awe inspiring rack. The dark-brown structure "
           + "seems to be made of ironwood, and spans both side walls of the "
           + "armoury chamber. Heavy, marred by a thousand scars and blackened "
           + "by untold ages, the wooden rack seems as durable as the mighty "
           + "walls of the Keep itself. Here Armoury Masters store the battle "
           + "equipment of the Solamnian Knighthood. Here rest the blades "
           + "that fought in a thousand victorious battles, here lay the plates "
           + "that averted a thousand mortal blows. For generations, Knights "
           + "brought their, and their fallen comrades' equipment to be used "
           + "by others Knights and Squires.\nA legacy of Honour! A legacy of Faith! "
           + "Use the items wisely. Use them for the Knighthood, and all those who "
           + "call for the aid of Draco Paladin and his Knights. May Kiri-Jolith, "
           + "the god of war, walk beside you.\n\n");

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
prevent_enter(object ob)
{
    if ( !( IS_ARMOUR_OBJECT(ob) || IS_WEAPON_OBJECT(ob) )  )
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
    else if ( !ob->check_recoverable() )
    {
        write("You decide to keep the " + ob->short() + " as "
                        + "it doesn't fit into this honourable rack.\n");
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
