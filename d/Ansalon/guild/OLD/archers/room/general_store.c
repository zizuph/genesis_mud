
/* File name :  general_store.c
 *
 * The general store tent.
 *
 * Blizzard, 05.11.2003
 */
 
#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <macros.h>

inherit  "/lib/shop";
inherit  R_FILE

#define  STORE_ROOM            (GUILD_ROOM + "store_base")

void
reset_archer_room()
{

}

public int
wiz_check()
{
    if (TP->query_wiz_level() || TP->query_npc() )
        return 0;
    
    write("Because of some magic force, you cannot enter there.\n");
    say(QCTNAME(TP) + " tries to enter the store room.\n");
    return 1;
}

public void
create_krynn_room()
{
    config_default_trade();
    set_money_greed_buy(102);
    set_money_greed_sell(102);
    
    set_short("inside the storage tent");
    set_long("You are standing inside a large tent.\n");
    
    INSIDE;
    NO_TIME;
    
    add_exit(GUILD_ROOM + "archer_camp3.c", "out", 0, 1);
    add_invis_exit(STORE_ROOM, "enter", wiz_check);
        
    set_store_room(STORE_ROOM);
    reset_archer_room();
    
}

void
init()
{
    ::init();
    init_shop();
    
}

