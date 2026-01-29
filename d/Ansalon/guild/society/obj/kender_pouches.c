/* 
 * /d/Ansalon/guild/society/obj/kender_pouches.c
 *
 * Modified from the belt of pouches created
 * by Lilith - ~Avenir/bazaar/Obj/worn/pouch_belt.c
 * on 19 June 1998 by Arman.
 * 
 * Modified by Gwyneth to inherit the standard
 * wearable pack file, and get rid of a bug. 5 Aug, 1999
 * Removed decay routines by Mercade, 21 May 2004
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
    set_long("A set of large voluminous pouches hanging from " +
      "a thick leather belt makes up the kender pouch-belt. " +
      "A necessity for any kender, but especially those under the " +
      "effects of wanderlust. These pouches have been expertly designed "+
      "to hold just about anything, from baubles and herbs, to " +
      "time travelling devices. One may 'fill pack' or 'fill belt' " +
      "to put items into a pouch, and 'empty pack' or 'empty belt' to remove " +
      "all items from your pouches. This pouch-belt is made to " +
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

