// filename:     c_blessing.c
// creator(s):   Zielia 2006
// last update:
// purpose:      Blessing object for cahor altar
// note:
// bug(s):
// to-do:
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "zigg.h"

#define LD_PATH_CHECK       "/d/Genesis/obj/statue"
#define BONUS_INVIS 1

inherit "/std/object";

private static float time = itof(1800 + random(3600));

public void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_no_show();
    set_name(({"Cahor::Blessing"}));
    add_prop(OBJ_S_WIZINFO, "This is a blessing that makes the bearer "+
	"able to see invisible items for a time.\n");

    add_prop(OBJ_I_NO_DROP, 1);
}

public void
remove_object(void)
{
    if (IS_CLONE)
    {
	object ob = present(EYES_NAME, ENV());
	ob->rem_ref("cateyes");

	ALTER_PROP(ENV(), LIVE_I_SEE_INVIS, -BONUS_INVIS);
	ENV()->catch_tell("Your eyes feel fatigued and the world looks "+
	    "normal again.\n");
    }

    ::remove_object();
}

private void
check_near_avenir(void)
{
    string room_filename = file_name(ENV());

    // Lasts longering in Avenir.
    if (wildmatch("/d/Avenir/*", room_filename ) ||
	room_filename == LD_PATH_CHECK)
    {
        // still in range of Avenir.
	if (!random(4))
	{
	    set_alarm(0.0, 0.0 , &remove_object());
	    return;
	}
	else
	{
	    set_alarm(1800.0, 0.0 , &check_near_avenir());
            return;
	}
    }

    set_alarm(0.0, 0.0 , &remove_object());
}

public void
enter_env(object to, object from)
{
    object ob = present(EYES_NAME, to);

    ::enter_env(to, from);

    to->catch_tell("You feel a brief, sharp pain in your eyes and the "+
	"world starts to look hazy, as though it were a thin veil covering "+
	"something more vibrant.\n");

    if (!objectp(ob))
    {
        ob = clone_object(EYES_OBJ);
        ob->move( to );
    }

    ob->add_ref("cateyes");

    ALTER_PROP(to, LIVE_I_SEE_INVIS, BONUS_INVIS);

    set_alarm(time, 0.0 , &check_near_avenir());
}
