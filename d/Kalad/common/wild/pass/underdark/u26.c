/* 
 * /d/Kalad/common/wild/pass/underdark/u26.c
 * Purpose    : Does there have to be one?
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: Adapted to dark_dom inherit
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the northeast and southeast.\n");
    add_exit(DARK(u21), "northeast");
    add_exit(DARK(u27), "southeast");
}
