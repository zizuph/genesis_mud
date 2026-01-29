/* a VERY LARGE bag
 * created by Lilith Oct 1996
 */

inherit "/d/Genesis/std/pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>

void
create_pack()
{
    set_name("bodybag");
    set_short("webcloth sack");
    set_pshort("webcloth sacks");
    add_name(({"bag", "sack"}));
    set_adj("webcloth");
    add_adj(({"silken", "large"}));
    set_long("This is a rather unusual bag. Rather voluminous, it is "+
        "made of a material " +
        "that has the appearance and lightness of silk, but is very "+
        "strong and resistant to tearing. There is a tag of some sort "+
        "sewn onto the sack. This sack is keepable.\n");
    add_item("tag", "A golden trefoil, the symbol of Sybarus, is "+
        "represented on the tag, as are the words:  Havec "+
        "Sackmaker.\n   Use 'fill pack' to put items not worn or "+
        "kept in this sack.  Use 'empty pack' to remove all non-kept "+
        "and non-sellable items from your sack.\n");

    set_mass_storage(1); 
    set_keep(1); 

    add_prop(OBJ_I_VALUE,  450);             
    add_prop(CONT_I_WEIGHT, 200);        /* 0.2 kg */
    add_prop(CONT_I_VOLUME, 2000);        /* 2.0 L  */
    // add_prop(OBJ_M_NO_STEAL, "What?\n");  
    add_prop(CONT_I_MAX_WEIGHT, 190000);  /* 190.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 190000);  /* 190.0 L  */
    add_prop(CONT_I_REDUCE_WEIGHT, 120);  /* reduces weight by 20% */

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
