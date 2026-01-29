/* File:          /d/Khalakhor/common/herbs/honeysuckle.c
 * Creator:       Teth
 * Date:          January 26, 1998
 * Modifications:  
 * Added consistent singular and plural names - Tapakah, 04/2021
 * Purpose:       This herb is a generic herb for the domain.
 * Related Files: 
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <composite.h>
#include <herb.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

public void
create_herb()
{
    set_name("flower");
    add_name(({"herb", "honeysuckle"}));
    set_adj("twinned");
    add_adj("pink");
    set_herb_name("honeysuckle");
    set_short("pink twinned flower");
    set_pshort("pink twinned flowers");
    set_pname("flowers");
    add_pname(({"herbs", "honeysuckles"}));
    set_ingest_verb("eat");
    set_unid_long("This is a pink twinned flower. It was probably " +
      "picked from a shrub with vine-like branches in an open area. " +
      "It has a strong scent.\n");
    set_id_long("This pink twinned flower is the blossom of a " +
      "honeysuckle shrub. Honeysuckle is known to those with herb " +
      "lore as Lonicera. The shrub is two metres tall, with twisting " +
      "branches. When blooming, the honeysuckle is almost peerless " +
      "for its intoxicating scent. As the fruit of the honeysuckle " +
      "starts to decay, it ferments on the tree and causes birds which " +
      "ingest the fruit to become inebriated. Honeysuckle is most often " +
      "found in open sunny places.\n");
    set_herb_value(58);
    set_id_diff(13);
    set_find_diff(4);
    set_decay_time(600); /* 10 minutes */
    set_amount(1);
    set_effect(HERB_HEALING, "fatigue", 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_cmd_item(({"flowers","flower","scent","the flowers",
      "the pink flowers","the pink flower","the scent",
      "the pink twinned flower","the pink twinned flowers","strong scent",
      "the strong scent","intoxicating scent", "the intoxicating scent"}),
      ({"smell","inhale"}),"The overwhelming smell of the " +
      "pink flowers is like the rich odor of fresh honey, mixed with " +
      "the delicate fragrance of an entire floral bouquet.\n");
}

public string
query_recover() 
{
    return MASTER+":"+query_herb_recover();
}

public void
init_recover(string arg) 
{ 
    init_herb_recover(arg); 
}


