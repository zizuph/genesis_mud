#pragma strict_types

inherit "/std/object";
inherit "/lib/holdable_item";

#include "../guild.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define ORB_SHADOW (VAMP_SHADOW_DIR + "orb_sh")

/* This is to prevent the orb from being dropped unintentionally,
 * primarily during logout.  There may now be a better way to handle
 * this.
 */
int
nodrop()
{
    object pobj = previous_object(-2);

    if (pobj && pobj->query_vamp_orb_shadow())
    {
        return 0;
    }

    return (this_interactive() != this_player());
}

void
create_object()
{
    set_name("orb");
    set_adj("mithril");

    set_long("The mithril orb seems quite light for its size, " +
        "approximately twelve centimeters in diameter.  The only detectable " +
        "imperfection in its surface is a small, circular indentation.\n");

    add_item(({ "indentation", "small indentation", "aperture",
                "small circular indentation", "circular indentation", }),
        "The small, circular indentation about one centimeter deep is " +
        "cut into the surface of the orb, forming some sort of aperture.\n");


    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 900);
    add_prop(OBJ_I_VALUE, 80000);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_M_NO_DROP, nodrop);
    add_prop(OBJ_M_NO_STEAL, 1);

    add_prop(MAGIC_AM_MAGIC, ({ 95, "life" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "The orb is a powerful and ancient artifact.\n", 30,
        "It seems to have the power to trap the souls of certain " +
        "beings.\n", 60,
        "A trapped soul can only be released by holding the orb at the " +
        "moment of death.\n", 80 }));

    set_slots(W_ANYH);
}

public mixed
hold()
{
    if (IS_MEMBER(this_player()))
    {
        return 0;
    }

    setuid();
    seteuid(getuid());
    clone_object(ORB_SHADOW)->shadow_me(this_player());

    return 0;
}

public mixed
release()
{
    query_holder()->remove_vamp_orb_shadow();
    return 0;
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

public void
appraise_object(int num)
{
    ::appraise_object(num);
    write(holdable_item_usage_desc());
}

public string
query_auto_load()
{
    return MASTER + ":";
}

