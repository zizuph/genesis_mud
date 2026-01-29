/*
 *  /d/Earthsea/herbs/herb_files/slime_mold.c
 *  
 *  For use in Gont sewers.
 *  Grows in underground and wet places.
 *  
 *  Herb that could be used as a food source.
 *  
 *  Aeg, MAR 2021
 */

#pragma strict_types
#pragma save_binary

inherit "/std/herb";

#include <herb.h>


/*
 * Function name:        create_herb
 * Description  :        the constructor for the herb object
 */

public void
create_herb()
{
    /* By what names is this called? */
    
    set_name("slime mold");
    add_name(({"herb", "mold", "mould", "slime fungus", "fungus"}));
    add_adj(({"yellow-green", "flexible"}));
    add_pname("herbs");
    set_short("yellow-green flexible mold");
    set_pshort("yellow-green flexible molds");
    set_herb_name("slime mold");
    
    /* How is this viewed? */   
    
    set_unid_long("This yellow-green mold is squishy and "
         + "spongelike. It is the size of a small apple and has "
         + "the shape of a flattened egg.\n");

    set_id_long("The slime mold, or slime fungus, spends it's life "
         + "cycle between two distinctive states. It begins it's "
         + "life cycle as a creature might, moving from one place to "
         + "another in search of food. Upon finding something to devour "
         + "it begins it's plant-like stage, where this example currently "
         + "resides. It is often found in dirty water, where sunlight "
         + "does not shine. While it's taste is considered to be horrible, "
         + "it is a decent source of nourishment, and wizards consider it "
         + "to be a staple in the diet of an ascetic.\n");
         

    /* How is this consumed and what does it do? */
        
    set_ingest_verb("eat");
    set_amount(250); /* foodstuffs */
    
    
    /* How rare and how hard to identify? */
    
    set_id_diff(25);
    set_find_diff(2);

    /* Sell value and archaic decay time */
    
    set_herb_value(17);
    set_decay_time(3000);
}
