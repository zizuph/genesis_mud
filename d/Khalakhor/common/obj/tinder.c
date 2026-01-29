/* File:          /d/Khalakhor/common/obj/tinder.c
 * Creator:       Teth
 * Date:          April 14, 1997
 * Modifications:
 * Purpose:       This torch is cloned when a sign is broken.
 * Related Files: /d/Khalakhor/std/obj/sign.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit  "/std/torch";
#include <macros.h>

public void
create_torch()
{
    set_name("tinder");
    add_name(({"torch","stick","wood"}));
    set_pname("tinders");
    add_pname(({"torches","sticks"}));
    set_adj("jagged");
    set_short("jagged tinder");
    set_pshort("jagged tinders");
    set_long("This piece of wood is usable as a torch, although it " +
      "does not appear that it would last very long. It seems " +
      "to be a broken piece of some wooden construction.\n");

    set_strength(1);
    set_value(55);
}

public string
query_recover()
{
    return MASTER + ":" + query_torch_recover();
}

public void
init_recover(string arg)
{
    init_torch_recover(arg);
}
