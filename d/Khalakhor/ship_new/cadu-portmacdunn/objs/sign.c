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
 * Ported to the new ship system by Tapakah, 03/2009
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "/d/Genesis/ship_new/ships.h"

inherit STDSIGN;

public void
create_object()
{
  ::create_sign();
  set_name("sign");
  set_adj("brand");
  add_adj("new");
  set_short("brand new sign");
  set_long("@@sign_text");
  add_cmd_item(({"sign","brand new sign"}),
               "read","@@get_label");
  
  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 6000);
  
  add_prop(OBJ_M_NO_GET, "The sign is lodged securely, " +
           "and it is impossible to remove.\n");
}
