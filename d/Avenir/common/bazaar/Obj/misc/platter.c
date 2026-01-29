// A silver platter
// Can be used to carry the head of Nochipa for the
//    Chaor gate quet.
//        -Ilyian, Octiober 1995
inherit "/std/container";

#include <stdproperties.h>
#include "/d/Avenir/common/common.h"

void
create_container()
{
  set_name("platter");
  set_short("silver platter");
  set_adj("silver");
  set_long("This is a beautiful silver platter, with thin "
          +"gilt designes swirling along the bottom.\nThe "
          +"top of the plate is so shiny you can see your "
          +"reflection in it.\n");
  add_prop (CONT_I_WEIGHT, 450);
  add_prop (CONT_I_VOLUME, 500);
  add_prop (OBJ_I_VALUE, 300);
  add_prop (CONT_I_MAX_WEIGHT, 950);
  add_prop (CONT_I_MAX_VOLUME, 1000);
  add_prop (CONT_I_TRANSP, 1);
  add_prop (CONT_I_RIGID, 1);
}

