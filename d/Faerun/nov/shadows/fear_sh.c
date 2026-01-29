#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/shadow";

void
remove_fear_shadow()
{
    remove_shadow();
}

void flee()
{
        shadow_who->catch_msg("You are fleeing from the unholy terror!\n");
        shadow_who->command("scream");
        shadow_who->run_away();
}

int
query_fear_shadow()
{
    return 1;
}

void
init_fear_shadow(int i)
{
    set_alarm(1.0,1.0, &flee());
    set_alarm(itof(i),0.0,&remove_fear_shadow());
}