/*
 * /d/Gondor/clubs/storyteller/obj/spectacles.c
 * The guild-object of the Storyteller Club
 * It is an autoloading, non-droppable object that makes sure
 * the Storyteller soul is added to the player.
 *
 * Copyright 1998, Rolf Braun aka Elessar for Gondor.
 * Gwyneth, Oct. 13: Made non-autoloading until the club opens,
 *                   as some players have obtained the item.
 *
 * Morrigan, 10/2002: No longer the guild item, the guild item
 *     is now storybook.c
 */

inherit "/std/object";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/clubs/storyteller/defs.h"

public void
create_object()
{
    setuid();
    seteuid(getuid());

    set_name("spectacles");
    add_name(({ "spectacle", "Storyteller_Spectacles" }));
    set_short("pair of spectacles");
    set_long("This is a pair of spectacles to assist you with your "+
	"reading.\n");
    add_prop(OBJ_I_WEIGHT, 45);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_M_NO_DROP, "You keep your spectacles with you.\n");
    add_prop(OBJ_M_NO_GIVE, "You cannot give your spectacles away.\n");

    config_wearable_item(A_EYES, 1, 1);
}

void
leave_env(object from, object to)
{
     ::leave_env(from, to);
     wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

public int
discard_spectacles(string str)
{
    notify_fail("Discard what? The spectacles?\n");
    if (str != "spectacles")
        return 0;

    notify_fail("You cannot discard spectacles and wear them, too.\n");
    if (this_object()->query_worn())
        return 0;

    write("You discard the spectacles.\n");
    say(QCTNAME(this_player())+" discards "+POSSESSIVE(this_player())+
	" spectacles.\n");
    remove_object();
    
    return 1;
}

string
query_auto_load()
{
    return MASTER_OB(this_object()) + ":";
}

void
init()
{
    ::init();

    if (!IS_STORYTELLER(environment(this_object())))
    {
	remove_object();
        return;
    }

    add_action(discard_spectacles, "discard");
}
