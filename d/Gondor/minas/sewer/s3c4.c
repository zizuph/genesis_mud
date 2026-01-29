inherit "/d/Gondor/minas/sewer/sewer";

#include "/d/Gondor/defs.h"

void
create_sewer() 
{
    set_extra_long("The tunnel is running in a straight line down "
      + "from the southwest to the northeast. In the northwest wall "
      + "there is a small opening leading into a smaller tunnel.");
    add_exit(MINAS_DIR + "sewer/s2c4", "northeast", 0, 0);
    add_exit(MINAS_DIR + "sewer/s4c4", "southwest", 0, 0);
    add_exit(MINAS_DIR + "sewer/d8c4", "northwest", 0, 0);

    floor("northeast");
    passage("northeast");
    roof();
}

