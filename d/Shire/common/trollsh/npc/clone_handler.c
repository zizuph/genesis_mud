inherit "/d/Shire/std/clone_handler";
 
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/common/trollsh/tunnel/local.h"
 
void
create_clone_handler()
{
    set_default_area("/d/Shire/common/trollsh/tunnel/");
/*
    set_excluded_destinations( ({
        TUN_DIR + "shop",
        TUN_DIR + "store",
        TUN_DIR + "ta16",
        TUN_DIR + "base_tunnel"}) );
*/
    add_clone("/d/Shire/common/trollsh/npc/newtroll", 1, 225);
 
    set_clone_handler_id("Trollshaws Clone handler");
  
} 
