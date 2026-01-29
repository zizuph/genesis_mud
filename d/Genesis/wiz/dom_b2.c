#pragma save_binary

inherit "/std/room";
#include "default.h"


create_room(){

set_short("Tower of Domains");
set_long(

);

add_exit(THIS_DIR + "dom_b1", "up", "@@check");

}

check(){

if(this_player()->query_wiz_level()) return 0;

write("A brillant blue light repels you!\n");
return 1;

}
