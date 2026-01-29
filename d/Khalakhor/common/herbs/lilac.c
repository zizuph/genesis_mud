/* File:          /d/Khalakhor/common/herbs/lilac.c
 * Creator:       Teth
 * Date:          February 10, 1998
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
    set_name("flowers");
    add_name(({"herb", "bunch", "lilac", "flower"}));
    set_adj("aromatic");
    add_adj(({"purple","bunch","of","bunches"}));
    set_herb_name("lilac");
    set_short("bunch of purple aromatic flowers");
    set_pshort("bunches of purple aromatic flowers");
    set_pname("flowers");
    add_pname(({"herbs", "bunches", "lilacs" }));
    set_ingest_verb("eat");
    set_unid_long("This is a bunch of purple aromatic flowers. " +
      "It was picked from a shrub, and its perfume wafts up " +
      "overwhelmingly. It seems to be a cultivated plant.\n");
    set_id_long("This bunch of purple aromatic flowers is a set " +
      "of blossoms from the lilac shrub. Lilac, known to herbalists " +
      "as Syringa, is a domesticated shrub that grows to four " +
      "meters in height. It flowers in springtime, its smell " +
      "discernable from one hundred meters away. It has no known " +
      "use other than its appeal to gardeners and perfume-makers.\n");
    set_herb_value(44);
    set_id_diff(9);
    set_find_diff(3);
    set_decay_time(1200); /* 20 minutes */
    set_amount(1);
    set_effect(HERB_HEALING, "fatigue", 1);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 5);
    add_cmd_item(({"flowers","perfume","the flowers",
      "the purple flowers","the aromatic flowers","the perfume",
      "the purple aromatic flowers","the bunch of flowers",
      "the bunch of purple aromatic flowers"}),
      ({"smell","inhale"}),"The perfume of the bunch of purple " +
      "flowers is heady and aromatic. It is cloyingly sweet.\n");
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


