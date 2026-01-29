
/* 
 * Phlogaphulo (Flame Blade) Shadow
 *
 * Used to shadow a weapon's description without too much trouble
 *
 * By Jaacar - November, 1997
 */ 

#pragma save_binary
#pragma strict_types

inherit "/std/shadow";

#include "defs.h"

void
remove_flaming_shadow()
{
    remove_shadow();
}

int
query_pen()
{
    return shadow_who->query_pen() + PHLOGAPHULO_PEN;
}

int
query_hit()
{
    return shadow_who->query_hit() + PHLOGAPHULO_HIT;
}
