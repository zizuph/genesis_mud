inherit "/d/Krynn/std/furl_scroll";
inherit "/lib/keep";
#include "/d/Ansalon/goodlund/nethosak/chislev_temple/local.h"
#include <macros.h>
#include <cmdparse.h>

#define SCROLLFILE      TDIR + "map/flotsam.txt"
#define SCROLL_I_FURLED "_scroll_i_furled"

void
create_scroll()
{
    set_name("map");
    add_name("scroll");
    set_pname("maps");
    add_pname("scrolls");
    set_adj("aged");
    set_short("furled aged map");
    add_adj("furled");
    set_pshort("aged maps");
    set_long("This aged map is currently furled.\n");
    set_keep(1);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 50 + (random(50)));
    add_prop(SCROLL_I_FURLED, 1);

    set_file(SCROLLFILE);
}