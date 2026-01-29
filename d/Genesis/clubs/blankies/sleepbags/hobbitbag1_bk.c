/*Hobbit sleepingbag --Cozy red and yellow flannel plaid
 *Sewn by Alara
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object.c";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
//#include "/d/Genesis/defs.h"

public int do_roll(string str);
int rolled;

void
create_object()
{
    set_name ("sleepingbag");
    set_pname ("sleepingbags");
    set_adj (({"yellow", "red", "plaid","flannel"}));
    set_short ("@@my_short");
    set_pshort ("@@my_pshort");
    set_long ("@@my_long");
    add_name ("bag");
    add_prop (OBJ_I_WEIGHT, 500);
    add_prop (OBJ_I_VOLUME, 500);
    add_prop (OBJ_M_NO_SELL, "The Sleepingbag is for youngsters.  It "
            + "can not be sold.\n");

    rolled = 0;
}

int
init ()
{
    ::init ();
    add_action ("do_roll", "roll");
    add_action ("do_roll", "roll up");
}

string
my_short ()
{
    if (rolled)
        return "cozy red and yellow plaid flannel sleepingbag all rolled "
                + "up tight\n";
        return "cozy red and yellow plaid flannel sleepingbag\n";
}

string 
my_pshort ()
{
    if (rolled)
        return "cozy red and yellow plaid flannel sleepingbags all rolled "
                + "up tight";
        return "cozy red and yellow plaid flannel sleepingbags";
}

string
my_long ()
{
    if (rolled)
        return "cozy red and yellow flannel sleeping bag all rolled "
                + "up tight.\n Perhaps you can unroll it.\n";
        return break_string ("The sleeping bag  looks warm and "
                + "is made of flannel fabric that is so bright and " 
                + "cheery that is reminds you of the cozy comforts "
                + "of a warm hobbit hole whose inhabitant is rich "
                + "and lives high on the hog-- with full larders, "
                + "warm pies, hot cocoa, and a constantly burning "
                + "fire in the fireplace.  Any traveller would be "
                + "proud to possess such a fine bag. The bag is "
                + "unrolled.  Perhaps you can roll it up.\n", 70);
}

int
do_roll (string str)
{
     if ( (str !="bag") && (str != "sleeping bag") )
    {
        notify_fail ("Roll what? The sleeping bag?\n");
        return 0;
    }
    if  (rolled) 
    {
        notify_fail ("The sleeping bag is already rolled up.\n");
        return 0;
    }
    rolled = 1; 
    {
        write ("You roll up the cozy red and yellow plaid flannel "
                + "sleepingbag.\n");
        say (QCTNAME (this_player ()) + " rolls up "
                +  this_player () ->query_possessive () 
                +  " cozy red and yellow plaid flannel sleeping bag.\n");
       return 1;
    }
}
