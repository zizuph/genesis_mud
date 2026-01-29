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
    add_action ("do_unroll", "unroll");
    add_action ("do_fluff", "fluff");
}

string
my_short ()
{
    if (rolled)
        return "cozy red and yellow plaid flannel sleepingbag all rolled "
                + "up tight";
        return "cozy red and yellow plaid flannel sleepingbag";
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
        return "The cozy red and yellow flannel sleepingbag is rolled "
                + "up tight.\n Perhaps you can unroll it.\n";
        return break_string ("The sleepingbag  looks warm and "
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
    if (!strlen(str) ||
        !parse_command(str, ({ }),
             "[up] [the] [sleeping] 'bag' / 'sleeping-bag'/ 'sleepingbag'"))
    {
        notify_fail ("Roll what? The sleepingbag?\n");
        return 0;
    }
    if  (rolled) 
    {
        notify_fail ("The sleepingbag is already rolled up.\n");
        return 0;
    }
    rolled = 1; 
    {
        write ("You roll the cozy red and yellow plaid flannel "
                + "sleepingbag.\n");
        say (QCTNAME (this_player ()) + " rolls up "
                +  this_player () ->query_possessive () 
                +  " cozy red and yellow plaid flannel sleepingbag.\n");
       return 1;
    }
}

int
do_unroll (string str)
{
     if ( (str !="bag") && (str != "sleepingbag") )
    {
        notify_fail ("Unroll what? The sleepingbag?\n");
        return 0;
    }
    if  (rolled !=1) 
    {
        notify_fail ("The sleepingbag is not rolled up.\n");
        return 0;
    }
    rolled = 0; 
    {
        write ("You unroll the cozy red and yellow plaid flannel "
                + "sleepingbag, and give it a little shake to "
                + "make it fluffy again.\n");
        say (QCTNAME (this_player ()) + " unrolls "
                +  this_player () ->query_possessive () 
                +  " cozy red and yellow plaid flannel sleepingbag.\n");
        say (QCTNAME (this_player ()) + " shakes out "
                +  this_player () ->query_possessive () 
                +  " sleepingbag and fluffs it.\n");
       return 1;
    }
}
int
do_fluff (string str)
{
     if ( (str !="bag") && (str != "sleepingbag") )
    {
        notify_fail ("Fluff what? The sleepingbag?\n");
        return 0;
    }
    if  (rolled =1) 
    {
        notify_fail ("Uh, Perhaps you want to unroll it first?.\n");
        return 0;
    }
    rolled = 0; 
    {
        write ("You give the cozy red and yellow plaid flannel "
                + "sleepingbag, a gentle shake to fluff it up a "
                +"little.\n");
        say (QCTNAME (this_player ()) + " fluffs and plumps "
                +  this_player () ->query_possessive () 
                +  " cozy red and yellow plaid flannel sleepingbag.\n");
        
       return 0;
    }
}