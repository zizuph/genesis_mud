inherit "/std/object";
inherit "/lib/holdable_item";
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit "/lib/keep";

#define QUERY_THIEF ob->query_guild_style_occ() == "thief" || ob->query_guild_style_lay() == "thief" || ob->query_race_name() == "kender"

object wearer;

void
create_object()
{
    set_name("picks");
    add_adj("lock");
    add_adj("set");
    add_adj("of");
    set_short("set of lock picks");
    set_long("This set of small picks and wires is a standard set of " +
      "lock picks, most often used by thieves, assasins, and kender. " +
      "When held, no lock is safe from these rogues!\n");

    set_slots(W_ANYH);

    add_prop(OBJ_S_WIZINFO,
      "This is a set of tools that raises ones open locks skill " +
      "by 10 points when held in either hand.\n");
    add_prop(OBJ_I_VALUE, 30);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 800);
}

public mixed
hold()
{
    TP->set_skill_extra(SS_OPEN_LOCK,
      TP->query_skill_extra(SS_OPEN_LOCK) + 10);

    wearer = TP;
    return 0;
}

public mixed
release()
{
    wearer->set_skill_extra(SS_OPEN_LOCK,
      wearer->query_skill_extra(SS_OPEN_LOCK) - 10);

    wearer = 0;
    return 0;
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    holdable_item_leave_env(env, to);
}
