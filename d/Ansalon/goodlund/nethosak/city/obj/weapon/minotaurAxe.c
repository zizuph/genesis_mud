#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    mixed *arr;
    int n;
    
    set_name("battleaxe");

    arr = ({"broad-bladed",35, "double-bladed",37,
            "long-handled",40 });

    set_adj("long");
    n = random(sizeof(arr)/2)*2;
    if (strlen(arr[n])) add_adj(arr[n]);
    set_short("long " +arr[n]+ " battleaxe");
    add_name("axe");
    set_hit(39);
    set_pen(arr[n+1]);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_BOTH);
    add_prop(OBJ_I_VALUE, arr[n+1]*arr[n+1]); 
   
    set_long("The "+ short() +" is a huge and heavy axe, with a large head. "+
             "The blade is a bit rusty, but the edge has been sharpened and "+
             "seems to be able to cause some severe wounds. The axe is "+
             "rather long but a strong and agile warrior might be able "+
             "This weapon has a pointed steel tip which doesn't seem to "+
             "be of any other use then to cause pain at the victim. The "+
             "axe is rather long but a strong and agile warrior might be "+
             "able to use it without getting hurt.\n");

    add_item(("tip"),"The steel tip has been forged out of the head of the "+
                     "axe, making it more durable in battle. The tip itself "+
                     "isn't very big, but it will still cause some agonizing "+
                     "pain to anyone who might get stabbed by it.\n");
}
