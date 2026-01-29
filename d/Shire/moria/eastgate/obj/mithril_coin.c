/*
 * Mithril Coin
 *
 * Mithril coins, a rare treasure found in Moria
 *
 * Varian, June 2020
 */

#pragma save_binary
#pragma strict_types

inherit "/std/coins";
inherit "/std/heap";

#include <formulas.h>
#include <macros.h>
#include <money.h>
#include <language.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <std.h>

public void
create_coins()
{
    set_name("coin");
    set_pname("coins");
    set_heap_size(1);
    set_coin_type("Mithril");
    set_value(20736);
    set_weight(25);
    set_volume(1);
}
