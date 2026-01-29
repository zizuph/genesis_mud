inherit "/std/object";

#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include <macros.h>

static int burning;

void
create_object()
{
    set_name(({ "bomb", "smoke_bomb" }));
    set_adj("smoke");

    set_long("A small smoke bomb.  It has a very short fuse " +
        "protruding from the top.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, 2 * 12 * 12 * 12);

    add_item("fuse", "A short fuse protrudes from the top of the " +
        "smoke bomb.  If you were to light the bomb, you had better " +
        "drop it quickly!\n");
}

void
add_smoke(object env)
{
    object ob;

    setuid();
    seteuid(getuid());

    ob = clone_object(THIEF_LAIR_DIR + "obj/smoke_bomb_effect");
    ob->move(env, 1);
    ob->start();
}

void
explode_bomb()
{
    object *envs;
    int i;

    burning = -1;

    set_long("A small smoke bomb.  A small, blackened stub of a burnt " +
        "fuse protrudes from the top.\n");
    remove_item("fuse");
    add_item("fuse", "The fuse is burnt out.\n");

    envs = all_environment(this_object());

    for (i = 0; i < sizeof(envs); i++)
    {
        tell_room(envs[i], "There is a brief flash of light, and suddenly " +
            "the area is filled with dense smoke!\n", envs);
        
        if (envs[i]->query_prop(ROOM_I_IS))
	{
            add_smoke(envs[i]);
            return;
	}

        if (!envs[i]->query_prop(CONT_I_ATTACH) && envs[i]->query_prop(CONT_I_CLOSED))
	{
            return;
	}
    }

    add_smoke(envs[i - 1]);
}

mixed
command_light()
{
    if (burning > 0)
    {
        return "The fuse is already lit!\n";
    }

    if (burning < 0)
    {
        return "The fuse is burnt out; the smoke bomb " +
            "has already been used.\n";
    }

    burning = set_alarm(5.0, 0.0, explode_bomb);
    return 1;
}

/*
 * A hook to allow npcs to use the smoke bomb.
 */
void
use_bomb(object npc = previous_object())
{
    if (burning != 0)
    {
        npc->command("drop " + OB_NAME(this_object()));
        return;
    }

    burning = set_alarm(5.0, 0.0, explode_bomb);
    set_alarm(3.0, 0.0, &npc->command("drop " + OB_NAME(this_object())));
}
    
