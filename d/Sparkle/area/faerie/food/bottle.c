/*
 * bottle of wine for sale for Green Oaks
 * -- Finwem March 2005
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "std/object";

int max_drinks   = 24,
    max_sips     = 80,
    alco_amt     = 12,
    soft_amt     = 102;

string wine_name = "TESTER",
    wine_long    = "flat and black looking. This wine looks like it " +
        "would kill a pirate if drunk and give you bad BO, so this is " +
        "obviously a test long description.";

int do_drink(string str);

void create_object() 
{
    setuid(); 
    seteuid(getuid()); 
    set_name("bottle");
    add_name("wine bottle");
    set_short("bottle of " + wine_name + " wine");
    set_long("This is a bottle of " + wine_name + ". It comes from the " +
        "winery of Green Oaks. The bottle is made of glass and opaque, and is " +
        "is @@check_full@@. The wine is " + wine_long + "\n");
}

string check_full()
{
    if((max_drinks == 24) || max_sips == 72)
        return "full";
    else if(max_drinks >= 20 || max_sips >= 68)
        return "almost full";
    else if(max_drinks >= 18 || max_sips >= 60)
        return "three quarters of the way";
    else if(max_drinks >= 12 || max_sips >= 36)
        return "half full";
    else if(max_drinks >= 6 || max_sips >= 18)
        return "a quarter of the way full";
    else if(max_drinks >= 3 || max_sips >= 7)
        return "almost empty";
    else if(max_drinks <= 0 || max_sips <= 0)
        return "empty";
}
    
int do_drink(string str)
{

    if( (str=="wine") || (str==wine_name + " wine") ||         
        (str=="wine from bottle") ||
        (str==wine_name + " wine from bottle") ||
        (str=="bottle") )
    {
        if(max_drinks > 0)
        {
            TP->drink_alco(alco_amt);
            TP->drink_soft(soft_amt);
            max_drinks = max_drinks - 1;
            write("You take a drink from the " + short() + ".\n");
            say(CAP(QTNAME(TP)) + " takes a drink from the " + short() + ".\n");
write(max_drinks + " " + TP->query_prop(LIVE_I_MAX_DRINK) + "\n");
            return 1;
        }
    }
    return 0;    
}
    


void init() {
   add_action("do_drink", "drink");
//   add_action("do_taste", "taste");
//   add_action("do_taste", "sip");
}
