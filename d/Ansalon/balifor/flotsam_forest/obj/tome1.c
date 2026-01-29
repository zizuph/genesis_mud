#pragma save_binary

inherit "/std/scroll";
#include <stdproperties.h>
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

create_scroll()
{
    seteuid(getuid(this_object()));
    set_name("tome");
    set_short("thin tome");
    set_long("This thin blue-binded tome " +
      "has the title 'Manual of the Magi. Volume 436ii'. A " +
      "small insert on the front page states that it is " +
      "copy number 26, being printed and bound at the Tower " +
      "of Istar during the Age of Might.\n");
    set_file(TOME_FILE_ONE);
}
