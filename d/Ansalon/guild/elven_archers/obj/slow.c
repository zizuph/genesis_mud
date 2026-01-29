#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/object";


#define ICE_ARROW_SLOW "_archers_ice_arrow_slow_obj"
#define SLOW_AMOUNT 25

object player;

void create_object()
{
   seteuid(getuid());
   set_name(ICE_ARROW_SLOW);

   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_NO_DROP, 1);
   add_prop(OBJ_I_NO_GIVE, 1);
   add_prop(OBJ_I_VALUE, 0);

   set_no_show();
}

void
stop_slowness()
{
    int num_slow_objs = sizeof(filter(all_inventory(player),
                               &operator(==) (ICE_ARROW_SLOW) @ &->query_name()));

    if(num_slow_objs == 1)
    {
        player->catch_msg("The warmth returns to your body.\n");
    }
    player->change_prop(LIVE_I_QUICKNESS, player->query_prop(LIVE_I_QUICKNESS) + SLOW_AMOUNT);
    (player->query_combat_object())->cb_update_speed();
    remove_object();
}

void
do_slowness()
{
    player->add_prop(LIVE_I_QUICKNESS, player->query_prop(LIVE_I_QUICKNESS) - SLOW_AMOUNT);
    (player->query_combat_object())->cb_update_speed();
    set_alarm(10.0,0.0, &stop_slowness());
}

void enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
        remove_object();
        return;
    }

    if(!living(to))
    {
        remove_object();
        return;
    }
    player = to;
    do_slowness();
}
