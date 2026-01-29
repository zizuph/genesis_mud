inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("The main tunnel is running from the west "
      + "through a bend and continues to the southeast. In "
      + "the northeast wall, there is the entrance into a "
      + "smaller tunnel branch.");
 
    add_exit(MINAS_DIR + "sewer/d6c4",   "northeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/n4c4",   "southeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/dnc4",   "west", 0, 0);

    floor("southeast");
    passage("southeast");
}

