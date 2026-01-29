/*
   steed_obj.c
   
   Autoloading object for restoring a player when he quit while
   mounted on the steed.
   
   Copyright by Wout de Zeeuw, Fysix@Genesis, Sep 1997

 */

#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

static string M_in = 0, M_out = 0;  // In and out messages of rider

void
create_object()
{
   set_name("steed_rider_restore_object");
   set_long("This objects restores the player after login " +
      "when he quits while being mounted. " +
      "\n");

   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_NO_DROP, 1);
   set_no_show();
}

/* Function name: set_rider_vars
 * Description:   Set the variables of the rider to be restored after
 *                login.
 * Arguments:     string the original arrive message of the rider,
 *                string the original leave message of the rider.
 */
public void
set_rider_vars(string m_in, string m_out)
{
   M_in = m_in;
   M_out = m_out;
}

// Store the variables till next login
public string
query_auto_load()
{
   return MASTER + ":" + M_in + "#" + M_out;
}

// Restore the player and remove this object
public void
init_arg(string arg)
{
   if (sscanf(arg, "%s#%s", M_in, M_out) == 2)
   {
      this_player()->set_m_in(M_in);
      this_player()->set_m_out(M_out);
   }
   remove_object();
}
