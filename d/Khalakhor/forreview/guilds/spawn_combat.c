#pragma strict_types
#pragma save_binary

#include <filter_funs.h>
#include <cmdparse.h>
#include <composite.h>
#include <wa_types.h>
#include <tasks.h>
#include <formulas.h>
#include <ss_types.h>
#include <language.h>
#include "guild.h"

private static object spawn;

void
setup_spawn_combat(object who)
{
    spawn = who;
}
