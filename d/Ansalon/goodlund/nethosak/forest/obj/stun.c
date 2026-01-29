#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit "/std/object";

int time;
object player;

void create_object()
{
   seteuid(getuid());
   set_name(TROLL_STUN_OBJ);

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
    player->catch_msg("The pain in your limbs disappears.\n");
     
    player->change_prop(LIVE_I_QUICKNESS, player->query_prop(LIVE_I_QUICKNESS) + 200);
    (player->query_combat_object())->cb_update_speed();
    player->remove_prop(I_AM_SLOWED_FROM_TROLLS);
    remove_object();
}

void
do_slowness()
{
   player->change_prop(LIVE_I_QUICKNESS, player->query_prop(LIVE_I_QUICKNESS) - 200);
    (player->query_combat_object())->cb_update_speed();
   set_alarm(90.0,0.0, &stop_slowness());
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
