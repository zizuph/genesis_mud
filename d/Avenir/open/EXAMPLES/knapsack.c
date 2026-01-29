/* a scrip
 *   worn over the shoulder
 * created by Lilith Oct 1996
 * Lilith Aug 1997: added magical components prop
 *
 * revisions: 07/08/98 - Lilith - updated to new wearable pack.
 * Mercade, 21 May 2004; removed decay routines.
 */

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

void
create_wearable_pack()
{
    set_slots(A_BACK);
    set_looseness(15);
    set_layers(2);
    set_mass_storage(1); 
    set_cf(this_object());
    set_keep(1); 

    set_name("knapsack");
    set_short("sturdy leather knapsack");
    set_pshort("sturdy leather knapsack");
    add_adj(({"sturdy", "leather"}));
    add_name("pack");
    set_long("This knapsack is made to be comfortable when carried for " +
        "long distances. It is favored by those who carry heavy loads "+
        "for long distances because it is worn across the back and "+
        "held in place by two study straps over each shoulder. "+
        "There is a small tag sewn into one of the straps. "+
        "This knapsack is keepable.\n");
    add_item("strap", "It is made of sturdy, padded leather.\n");
    add_item("tag", "A golden trefoil, the symbol of Sybarus, is "+
        "represented on the tag, as are the words:  Havec "+
        "Sackmaker.\n   Use 'fill pack' to put items not worn or "+
        "kept in this pack.  Use 'empty pack' to remove all non-kept "+
        "and non-sellable items from your pack.\n   This pack can "+
        "be used to safely store herbs and magical components.\n");
            
    add_prop(OBJ_I_VALUE,  240);             
    add_prop(CONT_I_WEIGHT, 500);        /* 0.5 kg */
    add_prop(CONT_I_VOLUME, 500);        /* 0.5 L  */
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(OBJ_M_NO_STEAL, "What?\n");
    add_prop(CONT_I_MAX_WEIGHT, 130000);  /* 80.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 130000);  /* 80.0 L  */
    add_prop(CONT_I_REDUCE_WEIGHT, 110); // reduces weight by 10%

}

string
query_recover()
{
     return MASTER + ":" + query_keep_recover() + 
     query_container_recover();
}

void
init_recover(string arg)
{
     init_keep_recover(arg);
     init_container_recover(arg);
}

