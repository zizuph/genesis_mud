inherit "/std/shadow";

#include "/d/Avenir/common/bazaar/bazaar.h"

#define STOCKADE_ROOM   (EXTR + "hill")

/* Don't autoload this shadow! */

public void
autoload_shadow(mixed arg)
{
    remove_shadow();
}

/* Let's shadow do_die, and call for guards if in bazaar */

public void
do_die(object killer)
{
    string foo;
    
    if (query_shadow_who()->query_hp() > 0 ||
        query_shadow_who()->query_wiz_level() ||
        query_shadow_who()->query_ghost()) return;
    
    if (killer && living(killer) &&
        sscanf(file_name(environment(killer)), BAZAAR + "%s", foo) == 1)
        STOCKADE_ROOM->call_for_guards(killer, environment(killer));
    
    query_shadow_who()->do_die(killer);
}
