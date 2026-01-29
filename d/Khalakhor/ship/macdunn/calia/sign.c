/* File:          /d/Khalakhor/ship/macdunn/calia/sign.c
 * Creator:       Teth and puzit
 * Date:          April 20, 1997
 * Modifications:
 * Purpose:       This is the sign for the Khalakhor to Gelan
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
    set_adj("oily");
    set_short("oily sign");
    set_long("@@sign_text");
    add_cmd_item(({"sign","oily sign"}),
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
      "    The line to Gelan has been discontinued.\n" +
      "    This pier now serves the Mariners of Genesis and other\n" +    
      "    independent navigators.\n"+
          "-- Mariners of Genesis Guild\n");
    return "";
}
