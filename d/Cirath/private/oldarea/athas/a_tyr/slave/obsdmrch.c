/* obsdmrch: Obsidian merchant of Tyr. Serpine, 12/25/1996. */
 
inherit "/std/room";
#include "defs.h"
 
#define SELL_CLUBS ({"club","huge obsidian club","obsidian club","huge club",\
            "clubs","huge obsidian clubs","obsidian clubs","huge clubs"})
#define SELL_LEVEL 30
 
void
create_room()
{
    set_short("the Black Stone");
    set_long("Located a bit northwest of the slave pits in Tyr, the "
            +"Black Stone is a shop dedicated to purchasing discarded "
            +"chunks of raw obsidian. Unfortunately though, the owner "
            +"prefers to deal only with the lowest dregs of society, "
            +"since it is easier to cheat such people. The shop itself "
            +"is little more then a box of mud-encased bricks with an "
            +"open roof. The air is filled with obsidian dust, and tiny "
            +"shards lie everywhere.\n");
 
    add_item(({"roof","open roof"}),"There is none.\n");
    add_item(({"dust","shards","shard","obsidian dust"}),
             "A great deal of obsidian has passed this way.\n");
    add_item(({"brick","bricks","mud-encased bricks","mud-encased brick"}),
             "Its a simple wall in a simple building.\n");
    add_item("buyer", "A simple man who refuses to give his name.\n");
 
    OUTSIDE
    ADD_SUN_ITEM
 
    add_exit(TZ_SLAVE+"rd_ds_03.c", "south", 0, 1);
}
 
void init()
{
    ::init();
    add_action("sell_club", "sell");
}
 
int
sell_club(string str)
{
    object seller=this_player();
    object club=present("_oclub_",ENV(seller));
    object cash;
 
    if (member_array(str, SELL_CLUBS)<0)
    {
       seller->catch_msg("The buyer of the Black Stone has a marked "
            +"preference for huge obsidian clubs.\n");
       return 1;
    }
 
    if(!objectp(club))
    {
        seller->catch_msg("You must lay the club at your "
            +"feet for the buyer of the Black Stone to see.\n");
        return 1;
    }
 
    if((seller->query_average())>SELL_LEVEL)
    {
        seller->catch_msg("The buyer prefers not to deal with beings "
            +"as experienced as yourself.\n");
        return 1;
    }
 
    club->remove_object();
    cash=clone_object("/std/coins");
    cash->set_heap_size(1);
    cash->set_coin_type("silver");
    cash->move(seller, 1);
 
    tell_room(ENV(seller), "The buyer takes the club of black stone.\n");
    seller->catch_msg("The buyer hands you a shiny coin for the chunk "
            +"of obsidian.\n");
    say("The buyer hands "+QCTNAME(seller)+" a shiny coin for the chunk "
            +"of obsidian.\n");
    tell_room(ENV(seller), "The buyer says: A pleasure.\n");
    
    return 1;
}
