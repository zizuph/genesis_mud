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
    set_slots(A_L_SHOULDER);
    set_looseness(15);
    set_layers(2);
    set_mass_storage(1); 
    set_cf(this_object());
    set_keep(1); 

    set_name("scrip");
    set_short("suede leather scrip");
    set_pshort("suede leather scrips");
    add_adj(({"suede", "leather"}));
    add_name("pack");
    set_long("This scrip is made to be comfortable when carried for " +
        "long distances. It is favored by pilgrims and explorers "+
        "alike because its strap is worn on one shoulder so that "+
        "it crosses the chest, causing the scrip itself to be carried "+
        "at waist-height and easily accessible. There is a small tag "+
        "sewn to the strap. This scrip is keepable.\n");
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
    add_prop(CONT_I_MAX_WEIGHT, 80000);  /* 80.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 80000);  /* 80.0 L  */
    add_prop(CONT_I_REDUCE_WEIGHT, 110); // reduces weight by 10%

}

string
query_recover()
{
     return MASTER + ":" + query_keep_recover() + 
     query_container_recover();
}

void reject(void)
{
     tell_object(environment(), "\n ** The "+ short() +" falls apart.\n"+
	 " ** You should visit Havec in the Bazaar for an improved one!\n\n");
     remove_object();
}

void
init_recover(string arg)
{
     init_keep_recover(arg);
     init_container_recover(arg);

     set_alarm(0.5, 0.0, reject);
}
