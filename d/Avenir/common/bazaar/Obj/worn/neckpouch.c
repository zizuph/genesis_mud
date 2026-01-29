/* a pouch
 * worn around the neck
 * created by Lilith Oct 1996
 * updated: Lilith Aug 1997: added CONT_I_HOLDS_COMPONENTS prop.
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

    set_name("webpouch");
    set_short("webcloth pouch");
    set_pshort("webcloth pouches");
    add_name(({"pouch", "neckpouch"}));
    add_adj(({"webcloth", "neck"}));
    set_long("A pouch made of the rare, lightweight, and very "+
        "strong silk-like webcloth material. It bears the stamp "+
        "of Havec Sackmaker of Sybarus, and is designed to be "+
        "worn around the neck. It is keepable.\n");

    set_slots(A_NECK);
    set_looseness(20);
    set_layers(1);
    set_mass_storage(1); 
    set_cf(this_object());
    set_keep(1); 

    add_prop(OBJ_I_VALUE,  75);                          
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(OBJ_M_NO_STEAL, "What?\n");
    add_prop(CONT_I_WEIGHT, 250);         /* 0.25 kg */
    add_prop(CONT_I_VOLUME, 500);         /* 0.5 L  */
    add_prop(CONT_I_MAX_WEIGHT, 10000);    /* 10.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 10000);    /* 10.0 L */
    add_prop(CONT_I_REDUCE_WEIGHT, 110); // reduces weight by 10%

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
