/*The Dwarven Mining Company Gem Shop
** Created by Leia
** 1/30/2006
** Last updated: 1/30/2006
** Gem Shop Code Borrowed From Bree Gem Shop
*/

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";
inherit "/lib/shop";
inherit "/d/Shire/bree/gem_list";


inherit "/d/Genesis/gems/gem_shop";

#include "/d/Shire/sys/defs.h"
#include "../defs.h"

#define STORE_ROOM	GEM_STOR


void reset_shire_room();

void
create_shire_room()
{
    set_short("Dwarven Mining Company Gem Shop");
    set_long("This is the Dwarven Mining Company Gem Shop. Like all of the other 'buildings' in this town, it is set deep within the rock. This is where miners from the Company come to sell their gems and make their day's wages. Those not from the Company are also welcome to sell their findings at this location, or purchase gems as they see fit. Behind the counter, piles of gems are stacked up, awaiting transport or purchase.\n");
    create_gem_shop();
    set_money_greed_sell(130);
    set_money_give_out(   ({ 100, 700, 4000, 0 })); /* Max_pay   */
    set_store_room(GEM_STOR);
    add_item(({"counter", "desk"}), "This counter is crafted out of the purest marble. There are no imperfections that you can find, a testament to the handiwork of the craftsman. It runs from stone wall to stone wall at the back of the shop.\n");
    add_item(({"wall", "walls", "stone wall", "stone", "rock"}), "The stone walls are massive, creating a rounded dome-shaped room that houses the shop. From the center of the dome hangs an enormous chandelier.\n");
    add_item("chandelier", "This is an enormous chandelier, crafted out of the finest gold. It must have one hundred tiny flickering candles, that seem to magically burn without ever burning out.\n");
    add_item(({"candle", "candles"}), "There are around one hundred candles burning brightly in the chandelier. The flames flicker with the slightest of air currents, but miraculously never go out, and never burn out the candle.\n");
    add_item(({"flame", "flames"}), "There is something mysterious about the flame that lights these candles. While you cannot put your finger on just what it is, the flame is enticing and easy to stare at.\n");
    add_item(({"gems", "gem"}), "Gems of all sorts lay in piles behind the counter. Some of them may be for sale.\n");

    add_exit(DT01, "east");
    
}

void
init()
{
    ::init();
    init_gem_shop();
}

void
reset_shire_room()
{
}