/* File:          /d/Khalakhor/ship/macdunn/shire/sign.c
 * Creator:       Teth & puzit
 * Date:          April 20, 1997
 * Modifications:
 * Purpose:       This the sign for the Khalakhor to Greyhavens
 *                pier. It inherits a standard sign.
 * Related Files: /d/Khalakhor/ship/macdunn/shire/
 *                /d/Khalakhor/std/obj/sign.c
 *                /d/Khalakhor/common/obj/tinder.c
 *                /d/Khalakhor/common/wep/stick.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/obj/sign.c";
#include <stdproperties.h>

public void
create_object()
{
    set_name("sign");
    set_adj("faded");
    set_short("faded sign");
    set_long("@@sign_text");
    add_cmd_item(({"sign","faded sign"}),
      "read","@@sign_text");

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6000);

    add_prop(OBJ_M_NO_GET, "The sign is lodged securely, " +
      "and it is impossible to remove.\n");
}

public string
sign_text()
{
    write("The text reads:\n\n" +
      "    Ship passage to Greyhavens.\n" +
      "    45 copper coins!\n" +
      "    No charge for youth.\n\n");
    return "";
}
