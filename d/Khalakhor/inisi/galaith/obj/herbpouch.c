/*********************************************************************
 * - herbpouch.c                                                   - *
 * - A pouch to carry herbs.                                       - *
 * - Taken from example of herbjar.c                               - *
 * - Special contribrutions/credit found in such code belong to:   - *
 * - Lord Elessar Telcontar, Mercade, Olorin and Khail             - *
 * - Created by Damaris@Genesis 4/27/2003                          - *
 *********************************************************************/

#pragma strict_types

inherit "/std/receptacle.c";
inherit "/lib/keep.c";

#include <files.h>
#include <macros.h>
#include <stdproperties.h>

/* Identify it as herb pouch only when filled. */
string
short_func()
{
    if (sizeof(all_inventory()))
    {
        return "herb pouch";
    }
    return "leather pouch";
}

/* Identify it as herb pouch only when filled. */
string
pshort_func()
{
    if (sizeof(all_inventory()))
    {
        return "herb pouches";
    }
    return "leather pouches";
}

/* Constructor. */
public void
create_container()
{
    set_name("pouch");
    add_name("herbpouch");
    set_adj( ({ "leather", "herb", }) );
    set_short(short_func);
    set_pshort(pshort_func);
    set_long("This is a smooth leather pouch that great care "+
      "has gone into its craftsmanship. Along the side of the "+
      "worked leather is a radiant design of a rainbow that "+
      "arches over an herb leaf. This pouch is specifically "+
      "intended to carry herbs. You can <keep pouch> if you do "+
      "not want to sell it.\n");
    add_prop(CONT_I_IN,            1);
    add_prop(CONT_I_RIGID,         0);
    add_prop(CONT_I_TRANSP,        0);
    add_prop(CONT_I_WEIGHT,      200);
    add_prop(CONT_I_VOLUME,      200);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(OBJ_I_VALUE,         72);

    /* Some herbs are spell components */
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    set_keep(1);
}

/* Only allow herbs to be inserted. */
public int
prevent_enter(object obj)
{
    if (!IS_HERB_OBJECT(obj))
    {
        write("You can only put herbs in the "+query_name()+".\n");
        return 1;
    }
    return 0;
}

/* Necessary for recovering the keep value. */
public string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

/* Necessary for recovering the keep value. */
public void
init_recover(string arg)
{
    init_keep_recover(arg);
}
