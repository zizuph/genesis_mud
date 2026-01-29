/* Seed, by Teth, April 9, 1996 */
inherit "/std/food";
#include "/d/Krynn/common/defs.h"

public void
create_food()
{
    set_name("seed");
    add_name(({"food", "grain"}));
    set_pname("seeds");
    add_pname(({"foods", "grains"}));
    set_short("clefted yellow seed");
    set_pshort("clefted yellow seeds");
    set_adj(({"clefted","yellow"}));
    set_long("This seed is oval in shape, and is coloured yellow. It has "+
      "a cleft that extends the length of the seed on one side. This "+
      "seed appears to belong to some grain plant, perhaps wheat or "+
      "barley.\n"); 
    set_amount(10);

}

