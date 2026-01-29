/* Elvish arrows made in Rivendell
 * Finwe, June 2004
 *
 *  Modification log:
 *     
 *     2006.09.05, Toby:
 *     Added set_short to solve the 'A broken broken arrow.' bug
 *     2020 05 18, Mayari
 *     made it a heap of 12 for the hunters club
 *     Changed the desecrption to see if it was the right arrows.
 */

#include "/d/Shire/sys/defs.h"  
#include </stdproperties.h>

inherit "/lib/keep";
inherit "/std/arrow";

public void
setheapsize(int dosen)
{
    set_heap_size(dosen);
}

public void
create_arrow()
{
   // FIXEUID;
    add_prop(HEAP_I_UNIT_WEIGHT, 22);
    add_prop(HEAP_I_UNIT_VOLUME, 26);
    add_prop(HEAP_I_UNIT_VALUE, 20);
    add_prop(OBJ_I_VALUE,60); 
    add_prop(HEAP_I_IS,12);
    add_prop(HEAP_S_UNIQUE_ID,"hunters_club_arrow");

    set_adj(({"long", "wooden", "sleek"}));

    set_short("black feathered arrow");
    set_pshort("black feathered arrows");

    set_keep();
    
    set_projectile_id("hunters_club_arrow");
    set_hit(40);
    set_pen(40);
    setheapsize(12);
      
}

string
get_projectile_long(string str, object for_obj, int num)
{
    if (num == 1)
    {
        return "This is a long, sleek arrow made by warg riders, roaming "          +
        "the Misty Mountains. The shaft is made of smooth blood red wood "          +
         "and the fins are bristling dark black creban feathers. The "              +
        "tip has been hammered from a dirty green piece of bronze, crudely "        +
        "whetted to a rough edge. Even without poison it looks extremely "          +
        "deadly.\n"                                                                 ;

    }
    else
    {
        return "These are long, sleek arrows made by warg riders, roaming "         +
        "the Misty Mountains. The shafts are made of smooth blood red wood "        +
         "and the fins are bristling dark black creban feathers. Each "             +
        "tip has been hammered from a dirty green piece of bronze, crudely "        +
        "whetted to a rough edge. Even without poison these arrows look "           + 
        "extremely deadly.\n"                                                       ;
    }
}