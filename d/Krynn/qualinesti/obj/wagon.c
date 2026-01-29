/* wagon.c
 * Kragh's wagon.
 *
 * Blizzard, 31/05/2003
 */
 
inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>


int      remove_canvas(string str);

void
create_object()
{
    set_name("wagon");
    set_adj("sturdy");
    add_adj("wooden");
    set_long("This is a sturdy wooden vehicle with four wheels, used " +
        "for transporting things. It looks to be fully loaded, but " +
        "you can not see what is inside, because it is tightly covered by " +
        "strong canvas.\n");
    add_item(({"wheel", "wheels"}),
        "The wagon has four wooden wheels. Each of them is reinforced by " +
        "steel bars.\n");
    add_item("canvas",
        "The strong canvas has been put on the wagon, covering its load.\n");
        
    add_prop(OBJ_I_WEIGHT, 800000);
    add_prop(OBJ_I_VOLUME, 700000);
    add_prop(OBJ_M_NO_GET, 1);        
}

void
init()
{
    ::init();
    add_action(remove_canvas, "remove");
    add_action(remove_canvas, "lift");
}

int
remove_canvas(string str)
{
    object dwarf;
    
    if ( !stringp(str) )
    {
        notify_fail("Remove what?\n");
        return 0;
    }
    
    if ( str == "canvas" )
    {
        if ( (dwarf = present("kragh", E(TO))) )
        {
            dwarf->command("emote thunders: Leave that be lad, its mine, " +
                "and i'll have none of ye messin' with'em.");
            return 1;
        }
        else
        {
            write("You remove the canvas but there is nothing " +
                "interesting for you to get from the wagon so you " +
                "decide to leave it.\n");
            tell_room(E(TO), QCTNAME(TP) + " removes the canvas, but " +
                "he does not find anything interesting in the wagon.\n", TP);
                
            return 1;
        }
    }
    else
        return 0;
        
      
}
