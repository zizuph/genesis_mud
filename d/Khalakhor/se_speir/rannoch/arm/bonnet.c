/* File         : /d/Khalakhor/se_speir/rannoch/arm/bonnet.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-13      
 * Purpose      : Object file of the Loch Rannoch area.
 * Related Files: 
 * Comments     : Borrowed Zima's bonnet description
 * Modifications: 
 */

inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>

#define TP        this_player()
#define TO        this_object()
#define HIS(x)    x->query_possessive()

void create_armour()
{
    set_short("white bonnet");
    set_name("bonnet");
    set_long("It is a plain white bonnet, a headdress of a lady with a "+
             "narrow brim and long straps which tie neatly beneath the "+
             "chin.\n");

    set_ac(0);
    add_prop(OBJ_I_VALUE, 200);
    set_at(A_HEAD);
    set_am(({0,0,0 }));
    set_af(this_object());
}

string query_recover() { return 0; }

mixed wear()
{
    if (TP->query_gender() == G_MALE)
    return "Not exactly something a male should wear, both men " +
           "and women would laugh at you.\n";

    else write("You wear the "+TO->short()+" on your head, and tie " +
               "the straps together under your chin.\n");

    say(QCTNAME(TP)+" wears the "+TO->short()+" on "+HIS(TP)+" head, " +
          "and ties the straps together under "+HIS(TP)+" chin.\n");
    return 1;
}

mixed remove()
{
    if (TP->query_gender() == G_MALE)
    return "With a sigh of relief, you untie the straps and remove the bonnet.\n";

    write("You untie the straps of the "+TO->short()+" and remove " +
          "it from your head.\n");
    say(QCTNAME(TP)+" unties the straps and removes the "+TO->short()+" " +
                    "from "+HIS(TP)+" head.\n");

    return 1;
}

