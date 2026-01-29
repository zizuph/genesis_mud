inherit "/d/Shire/std/clone_handler";
 
#include "/d/Shire/sys/defs.h"
#include "../local.h"
 
void
create_clone_handler()
{
    set_default_area(VALLEY_DIR);
 
    set_excluded_destinations( ({
        VALLEY_DIR + "bank",
        VALLEY_DIR + "forge",
        VALLEY_DIR + "kitchen",
        VALLEY_DIR + "library",
        VALLEY_DIR + "post",   
        VALLEY_DIR + "shop",
        VALLEY_DIR + "store"
            }) );

    add_clone(RNPC_DIR + "citizen", 1, 3, VALLEY_DIR + "u_cor03");
    add_clone(RNPC_DIR + "citizen", 2, 2, VALLEY_DIR + "d_cor07");
    add_clone(RNPC_DIR + "citizen", 3, 1, VALLEY_DIR + "music_rm");
    add_clone(RNPC_DIR + "citizen", 4, 3, VALLEY_DIR + "v_path03");
    add_clone(RNPC_DIR + "citizen", 5, 1, VALLEY_DIR + "t_path01");
    add_clone(RNPC_DIR + "guard",   6, 3, VALLEY_DIR + "t_path01");
    add_clone(RNPC_DIR + "guard",   7, 3, VALLEY_DIR + "w_porch");
    add_clone(RNPC_DIR + "citizen", 8, 2, VALLEY_DIR + "stairs02");
    add_clone(RNPC_DIR + "citizen", 9, 2, VALLEY_DIR + "stairs02");
    add_clone(RNPC_DIR + "citizen",10, 2, VALLEY_DIR + "path02");
    add_clone(RNPC_DIR + "citizen",11, 2, VALLEY_DIR + "t_path08");
    add_clone(RNPC_DIR + "citizen",12, 2, VALLEY_DIR + "v_path09");
    add_clone(RNPC_DIR + "citizen",13, 2, VALLEY_DIR + "v_path06");
    add_clone(RNPC_DIR + "citizen",14, 1, VALLEY_DIR + "stone_seat");
    add_clone(RNPC_DIR + "citizen",15, 1, VALLEY_DIR + "fire");
    add_clone(RNPC_DIR + "citizen",16, 2, VALLEY_DIR + "d_cor05");
    add_clone(RNPC_DIR + "citizen",17, 2, VALLEY_DIR + "u_cor02");
    add_clone(RNPC_DIR + "citizen",18, 2, VALLEY_DIR + "d_cor09");
 
    set_clone_handler_id("Imladris Valley Clone handler");
 
 
} 
