#pragma save_binary

inherit "/std/poison_effect";
#include <poison_types.h>
#include "potion_defs.h"

void
create_poison_effect()
{
    ::create_poison_effect();
    add_name( MORGUL_S_DOLLOST_POISON_NAME );
	add_name( "dollost_ingr2" );
    set_interval( 60 );
    set_time( query_strength()* 12 );
}

int
use_component()
{
    return 1;
}
