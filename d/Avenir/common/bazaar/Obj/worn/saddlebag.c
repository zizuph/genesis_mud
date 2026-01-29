/* a saddlebag
 *   worn over the shoulder
 * created by Lilith Oct 1996
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
    set_slots(A_R_SHOULDER);
    set_looseness(15);
    set_layers(2);
    set_mass_storage(1); 
    set_cf(this_object());
    set_keep(1); 

    set_name("saddlebag");
    set_pshort("saddlebags");
    set_adj("leather");
    add_name(({"pack", "bag"}));
    set_long("This saddlebag has a good amount of room to carry " +
        "things. It is normally strapped to a horse, but people "+
        "also carry it over the shoulder. This saddlebag is keepable.\n");
    add_item("strap", "It is made of sturdy, padded leather.\n");
    add_item("tag", "A golden trefoil, the symbol of Sybarus, is "+
        "represented on the tag, as are the words:  Havec "+
        "Sackmaker.\n   Use 'fill pack' to put items not worn or "+
        "kept in this pack.  Use 'empty pack' to remove all non-kept "+
        "and non-sellable items from your pack.\n   This pack can "+
        "be used to safely store herbs and magical components.\n");
            
    add_prop(OBJ_I_VALUE,  300);             
    add_prop(CONT_I_WEIGHT, 1500);         /* 1.5 kg */
    add_prop(CONT_I_VOLUME, 1000);         /* 1.0 L  */
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(OBJ_M_NO_STEAL, "What?\n");
    add_prop(CONT_I_MAX_WEIGHT, 100000);  /* 100.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 100000);  /* 100.0 L  */
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



