#include <macros.h>
inherit "/std/armour";

/*
 * shire_armour.c
 *
 *  If you inherit this file and use create_shire_armour() and
 *  reset_shire_armour() instead of create/reset_armour() you
 *  will automatically get recoverable armours.
 *  In addition, further changes may be made in this file later
 *  to add special things for our armours.
 *
 * Sir Rogon, Sep 29, 1993.
 *
 *  Useful macros is in defs.h, so you can write:
 *
 *    #include "defs.h"
 *    inherit ShireArmour;
 *
 *    CreateArmour()
 *    {
 *	 set_ ...
 *    }
 *
 *    ResetArmour()
 *    {
 *	 do special things at resets.
 *    }
 *
 */

create_armour()
{
    this_object()->create_shire_armour();
}

reset_armour()
{
    this_object()->reset_shire_armour();
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
