/**********************************************************************
 * - beef.c                                                         - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/2005                             - *
 **********************************************************************/
#pragma strict_types
inherit "/std/food";
#include <stdproperties.h>

public void
create_food()
{
    set_name("beef");
    set_adj(({"seasoned", "plate"}));
    set_short("plate of seasoned beef");
    set_pshort("plates of seasoned beef");
    set_long("This is a plate stacked with specifically seasoned beef. "+
      "The seasoning is a mixture of herbs that are found deep within "+
      "the northern forests then steeped for many hours in a blend of "+
      "pepper, sea salt and dark ale. Then the herbs leaves are draped "+
      "over the beef and marinated for hours. Then it is roasted over "+
      "an open pit until it is cooked to perfection.\n");
    set_amount(200);
    add_prop(HEAP_I_UNIT_VOLUME, 150);
    add_prop(HEAP_I_UNIT_VALUE, 120);
}
