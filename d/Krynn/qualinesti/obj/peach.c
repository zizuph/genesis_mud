/* The peach picked from the tree in Qualinesti. */

inherit  "/std/food";
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

int      bite(string str);
//int      size = 2;

create_food()
{
    set_name("peach");
    add_name( ({ "peach fruit", "fruit" }) );
    set_adj("soft");
    add_adj("orange-red");
    set_short("soft orange-red fruit");
    set_pshort("soft orange-red fruits");
    set_long("This is a soft round fruit with a orange-red skin and it " +
        "looks for juicy.\n");  
    set_amount(20);
}

void
init()
{
    ::init();
    add_action(bite, "bite");
    add_action(bite, "consume");
}

int
bite(string str)
{
    notify_fail("Bite what?\n");
    
    if ( (str == "peach") || (str == "soft fruit") || 
        (str == "orange-red fruit") || (str == "soft orange-red fruit") )
    { 
        write("As you bite down the soft skin, sweet juice starts " + 
            "to drain out the fruit, down your chin. You lick your lips " +
            "quickly.\n");
        say("As " + QCNAME(TP) + " bites down the soft skin, sweet juice " +
            "starts to drain out of the fruit, down " + POSSESSIVE(TP) +
            " chin. " + QCTNAME(TP) + " quickly licks " + POSSESSIVE(TP) +
            " lips.\n");
        
//        seteuid(getuid());
//        set_heap_size(num_heap() - 1);     
        TP->command("eat peach");      
        return 1;     
    }

    return 0;
}

