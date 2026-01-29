/*  Vencar November 2003, Project day (tm)
 *
 *  Original code from id scroll in icewall
*/

inherit "/std/scroll";
inherit "/d/Genesis/newmagic/spellcasting";

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>

void
auto_crumble()
{
    if(living(E(TO)))
        E(TO)->catch_msg("\nYour scroll of teleportation " +
                         "crumbles to dust.\n");

    remove_object();
}


void
create_scroll()
{
    set_name("scroll");
    add_name("icewall_teleport_scroll");
    set_adj("old");
    set_long("Some text is written on the old parchment.\n");

    add_prop(OBJ_I_VALUE, 15000);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 254);

    add_prop(OBJ_S_WIZINFO, "A teleport scroll you can read and recite.\n");
    add_prop(MAGIC_AM_ID_INFO, ({"This is a scroll of teleport.\n", 5,
        "The scroll can be recited to teleport yourself.\n", 10,
        "The scroll seems rather unstable, and may crumble.\n", 20,
        "The spell can only be cast once and will require " +
        "a white pearl.\n", 40 }) );

    add_prop(MAGIC_AM_MAGIC, ({ 35, "enchantment"}) );

    set_file(OBJ + "teleport.txt");

    set_alarm(itof(1800 + random(1800)), 0.0, auto_crumble);
    add_spell(OBJ + "icewall_spell");

}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    add_spell_object(to);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    remove_spell_object(from);
}

