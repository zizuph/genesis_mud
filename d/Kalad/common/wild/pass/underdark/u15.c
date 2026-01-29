/* 
 * /d/Kalad/common/wild/pass/underdark/u15
 * Purpose    : It shall be revealed to you in time...
 * Located    : Under Hespyre Mts.
 * Created By : Antharanos
 * Modified By: Nikklaus, Oct'97: adapated to dark_dom
 */

# pragma strict_types
# include "dark_dom.h"

inherit DARK_DOM;

void
create_dark_dom()
{
    create_tunnel();
    set_long(long()+
      "Dark passages lead to the northeast, southeast, and west.\n");
    add_exit(DARK(u16), "northeast");
    add_exit(DARK(u17), "southeast");
    add_exit(DARK(u14), "west");
}

