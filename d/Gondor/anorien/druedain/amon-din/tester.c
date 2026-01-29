inherit "/d/Gondor/anorien/druedain/amon-din/din_master";

#include "/d/Gondor/defs.h"

void
create_room()
{

    set_short("this is a test room for din_master");
    set_long("This is a test room for din_master.\n");

    add_view("Nowhere else in Gondor besides from the top of the "
      + "Mindolluin can one see as large a part of the realm.");
}
