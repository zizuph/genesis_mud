#pragma strict_types

inherit "/std/container";
inherit "/d/Genesis/std/wearable_pack";
inherit "/d/Genesis/newmagic/spellcasting";
 
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "guild.h"

void
create_container()
{
    if (!IS_CLONE)
    {
        return;
    }

    setuid();
    seteuid(getuid());

    set_name("quiver");
    add_name(GUILD_EMBLEM_ID);
    set_adj("silver-laced");
    add_adj( ({"plain", "leather" }) );
    set_short("plain leather quiver");
    set_long("This is a plain leather quiver, used by elven archers " +
        "for holding arrows. Elven runes have been stitched " +
        "into the side of it that read 'help archers help'.\n");

    set_slots(A_ANY_SHOULDER);

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);

    add_prop(CONT_I_WEIGHT, 200);
    add_prop(CONT_I_VOLUME, 8000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_IS_QUIVER, 1);

    remove_prop(OBJ_I_VALUE);

    add_spell("/d/Ansalon/guild/elven_archers/spells/messenger");
    add_spell("/d/Ansalon/guild/elven_archers/spells/herbgrowth");
    add_spell("/d/Ansalon/guild/elven_archers/spells/darkvision");

}


public int
prevent_enter(object ob)
{
     if(!ob->id("arrow"))
    return 1;
     else     
    return 0;
}


void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}
 
void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}
