inherit "/d/Shire/std/clone_handler";
 
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define MINING_DIR  "/d/Shire/moria/mines/mining/"
 
void
create_clone_handler()
{
    set_default_area(MINES_DIR);
/*
    add_excluded_destination(({ MINES_DIR + "stair0",
                                MINES_DIR + "stair1",
                                MINES_DIR + "stair2",
                                MINES_DIR + "shop",
                                MINES_DIR + "shop_store"}));
*/
    add_clone(MORIA_NPC + "test_orc", 1, 100);
//    add_clone(MORIA_NPC + "urukcap",    2, 1);
    add_clone(MORIA_NPC + "cavetroll",   3, 10);
    add_clone(MORIA_NPC + "test_orc", 4, 17, 
        ({MINING_DIR + "mining.1", MINING_DIR + "mining.2", 
          MINING_DIR + "mining.3", MINING_DIR + "mining.4",
          MINING_DIR + "mining.5", MINING_DIR + "mining.6",
          MINING_DIR + "mining.7", MINING_DIR + "mining.8",
          MINING_DIR + "mining.9", MINING_DIR + "mining.10",
          MINING_DIR + "mining.11", MINING_DIR + "mining.12",
          MINING_DIR + "mining.13", MINING_DIR + "mining.14",
          MINING_DIR + "mining.15", MINING_DIR + "mining.16",
          MINING_DIR + "mining.17", MINING_DIR + "mining.18",
          MINING_DIR + "mining.19", MINING_DIR + "mining.20"}) );
//    add_clone(MORIA_NPC + "uruk", 5, 15); 

    set_clone_handler_id("Moria Clone Handler");

} 
