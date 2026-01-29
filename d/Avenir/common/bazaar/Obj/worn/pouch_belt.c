/* a pouch-belt
 * created by Lilith August 1996
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
    set_name("belt of pouches");
    set_short("belt of pouches");
    set_pshort("pouch-belts");
    add_name(({"belt", "pouches", "belts", "pouch-belt", "pouch"}));
    set_long("A thick leather belt upon which voluminous pouches "+
        "are strung. The pouches are made of supple, waterproof "+
        "leather and look like they can hold quite a bit. There is "+
        "a small tag sewn to the belt. This pouch-belt is made to "+
        "be worn around the waist. It is keepable.\n");

    set_slots(A_WAIST);
    set_looseness(8);
    set_layers(2);
    set_mass_storage(1); 
    set_cf(this_object());
    set_keep(1); 


    add_prop(OBJ_I_VALUE,  180);                          
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(CONT_I_WEIGHT, 300);        /* 0.3 kg */
    add_prop(CONT_I_VOLUME, 1500);       /* 1.5 L  */
    add_prop(CONT_I_MAX_WEIGHT, 60000);  /* 60.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 60000);  /* 60.0 L  */
    add_prop(CONT_I_REDUCE_WEIGHT, 110); // reduces weight by 10%
    add_item("belt", "It is made of sturdy leather.\n");
    add_item(({"pouch", "pouches"}), "The pouches look like "+
        "they can hold quite a bit.\n"); 
    add_item("tag", "A golden trefoil, the symbol of Sybarus, is "+
        "represented on the tag, as are the words:  Havec "+
        "Sackmaker.\n   Use 'fill pack' to put items not worn or "+
        "kept in this pack.  Use 'empty pack' to remove all non-kept "+
        "and non-sellable items from your pack.\n   This pack can "+
        "be used to safely store herbs and magical components.\n");


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
