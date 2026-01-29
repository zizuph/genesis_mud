#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/w/kessie/icewall/local.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit "/std/object";

object player;

void create_object()
{
   seteuid(getuid());
   set_name("protection_from_fire_by_scroll");

   add_prop(OBJ_I_VOLUME, 0);
   add_prop(OBJ_I_WEIGHT, 0);
   add_prop(OBJ_I_NO_DROP, 1);
   add_prop(OBJ_I_NO_GIVE, 1);
   add_prop(OBJ_I_VALUE, 0);

   set_no_show();
}

void
protect_me()
{
   if(player->query_prop("_obj_i_have_fire_prot_by_scroll"))
     {
      player->catch_msg("You are already protected by such an " +
         "enchantment! The scroll is wasted and crumbles to dust.\n");
      remove_object();
     }

   player->add_prop("_obj_i_have_fire_prot_by_scroll");
   player->add_prop(MAGIC_I_RES_FIRE, player->query_prop(MAGIC_I_RES_FIRE) + 55);
   player->catch_msg("\nProtection from fire cast!\n");
   set_alarm(720.0,0.0, &first_hint);
}

void
first_hint()
{
   player->add_prop(MAGIC_I_RES_FIRE, player->query_prop(MAGIC_I_RES_FIRE) - 30);
   set_alarm(120.0,0.0, &second_hint);
   player->catch_msg("\nYour protection from fire enchantment weakens.\n");
}

void
second_hint()
{
   player->add_prop(MAGIC_I_RES_FIRE, player->query_prop(MAGIC_I_RES_FIRE) - 15);
   set_alarm(60.0,0.0, &end_protection);
   player->catch_msg("\nYour protection from fire enchantment is " +
      "on the verge of collapse.\n");
}

void
end_protection()
{
   player->add_prop(MAGIC_I_RES_FIRE, player->query_prop(MAGIC_I_RES_FIRE) - 10);
   set_alarm(120.0,0.0, &second_hint());
   player->catch_msg("\nYour protection from fire enchantment ends.\n");
   player->remove_prop("_obj_i_have_fire_prot_by_scroll");
   remove_object();
}

void enter_env(object to, object from)
{
    object to;

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
    protect_me();
}
