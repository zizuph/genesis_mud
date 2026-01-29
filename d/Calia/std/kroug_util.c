
/* 
   Some utility functions for kroug code. 
   
   Coded by Maniac
 
   Separated from kroug room code, 29/1/2000
*/

#pragma save_binary

#include <filter_funs.h>
#include "/d/Genesis/gems/gem.h"

object *
query_krougs(object room)
{
    return filter(all_inventory(room), &->query_smart_kroug());
}

object *
query_players(object room)
{
    return FILTER_PLAYERS(all_inventory(room));
}

int
good_aligned_npc(object ob)
{
    return (ob->query_npc() && (ob->query_alignment() > 0));
}

object *
query_good_npcs(object room)
{
    return filter(all_inventory(room), good_aligned_npc);
}

public void
add_gem_treasure(object npc)
{
    object gem;
    int quality = GEM_EXTREMELY_COMMON;
    
    if (random(5))
    {
        switch (npc->query_average_stat())
        {
        case 0..25:
            quality = GEM_COMMON;
            break;
        
        case 26..50:
            quality = GEM_SOMEWHAT_COMMON;
            break;
        
        case 51..75:
            quality = GEM_SLIGHTLY_COMMON;
            break;
        
        case 76..100:
            quality = GEM_SLIGHTLY_RARE;
            break;
        
        case 101..125:
            quality = GEM_SOMEWHAT_RARE;
            break;
        
        case 126..150:
            quality = GEM_RARE;
            break;
        
        case 151..175:
            quality = GEM_VERY_RARE;
            break;
        
        break;
            quality = GEM_EXTREMELY_RARE;
            break;
        }
        gem = RANDOM_GEM_BY_RARITY(quality);
        gem->move(npc, 1);
    }    
}
