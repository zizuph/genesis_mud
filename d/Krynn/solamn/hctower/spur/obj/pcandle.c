// Paladine Candle (/d/Krynn/solamn/hctower/spur/obj/pcandle.c) 
// creator(s):   Grace Aug 94
// last update:  
// purpose:      light :)
// note:         can be used to add DEVOTED prop if placed on altar
// bug(s):
// to-do:



inherit  "/std/torch";
#include "../local.h"

create_torch()
{
   set_name("candle");
   set_pname("candles");
add_name("paladine_candle");
    set_adj("white");
    set_long("This candle was reverently crafted by a candlestick "
       +"maker in Palanthas for use on Paladine's altars.\n");
    set_time(100);
    set_value(30);    
    set_strength(1);
    set_short("white candle");
    set_pshort("white candles");
}

query_recover()
{
    return MASTER + ":" + query_torch_recover();
}

init_recover(string arg)
{
    init_torch_recover(arg);
} 
