/* File:          /d/Khalakhor/ship/macdunn/ansalon/sign.c
 * Creator:       Teth
 * Date:          April 20, 1997
 * Modifications:
 * Purpose:       This is the sign for the Khalakhor to Ansalon
 *                pier. It inherits a standard sign.
 * Related Files: /d/Khalakhor/ship/macdunn/
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
    set_adj("sunbeaten");
    set_short("sunbeaten sign");
    set_long("@@sign_text");
    add_cmd_item(({"sign","sunbeaten sign"}),
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
          "    Bonnie Lass now sails to Tabor Sogh.\n" +
          "    The pier is located somewhat to the southeast from here.\n"+
          "    -- Genesis ShipLines Company.\n");
    return "";
}
