/* File:          /d/Khalakhor/std/obj/sign.c
 * Creator:       Teth
 * Date:          April 15, 1997
 * Purpose:       This sign is inheritable, and is to be used when
 *                a breakable sign is justified. It is removed when
 *                broken, and clones torches and sticks that
 *                can be used as clubs.
 * Related Files: /d/Khalakhor/common/wep/stick.c
 *                /d/Khalakhor/common/obj/tinder.c
 * Comments:      For an example, see /d/Khalakhor/ship/macdunn/
 *                sign_kalaman.c
 * Modifications:
 *   Cloned objects where left in the void. - Glindor, March 2001
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"

#define NAME   (TO->query_name())
#define ADJ    (TO->query_adj())
#define SHORT  (TO->query_short())

public void
create_object()
{
    set_name("sign");
    set_adj("old");
    set_short("old sign");
    set_long("@@sign_text");
    add_cmd_item(({"sign","old sign"}),
      "read","@@sign_text");

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6000);

    add_prop(OBJ_M_NO_GET, "The sign is lodged securely, " +
      "and it is impossible to remove.\n");
}

public string
sign_text()
{
    write("The sign reads:\n\n" +
      "This is a sign.\n\n");
    return "";
}

public void
init()
{
    add_action("do_break","break");
    ::init();
}

public int
do_break(string str)
{
    object wood1, wood2;

    seteuid(getuid());

    if ((str == NAME) || (str == SHORT))
    {
        write("You square your shoulders relative to the " + SHORT + ", and " +
          "then proceed to demolish the " + NAME + ", leaving some debris.\n");
        say(QCTNAME(TP) + " squares " + HIS + " shoulders " +
          "relative to the " + SHORT + ", and then proceeds to demolish " +
          "the " + NAME + ", leaving some debris.\n");

        if (random(2))
            wood1 = clone_object(COM_WEP + "stick");
	else
	    wood1 = clone_object(COM_OBJ + "tinder");
        if (wood1->move(environment(TP)))
            wood1->remove_object();

        if (random(2))
	    wood2 = clone_object(COM_WEP + "stick");
	else
	    wood2 = clone_object(COM_OBJ + "tinder");
        if (wood2->move(environment(TP)))
            wood2->remove_object();

        TO->remove_object();
        return 1;
    }
    notify_fail("Break what?\n");
    return 0;
}
