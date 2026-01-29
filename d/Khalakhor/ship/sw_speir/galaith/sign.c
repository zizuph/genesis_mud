/* ********************************************************************
 * - sign.c                                                         - *
 * - Sign for dock on Galaith Isle                                  - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Undated by Damaris@Genesis 05/2005                             - *
 **********************************************************************/
#pragma save_binary
#pragma strict_types
 
inherit "/d/Khalakhor/std/obj/sign.c";
#include <stdproperties.h>
 
public void create_object()
{
    set_name("sign");
    set_adj("redwood");
    set_short("redwood sign");
    set_long("@@sign_text");
    add_cmd_item(({"sign","redwood sign"}), "read","@@sign_text");
 
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6000);
 
    add_prop(OBJ_M_NO_GET, "The sign is lodged securely, " +
      "and it is impossible to remove.\n");
}
 
public string sign_text()
{
    write(
      "          $--------------------------------$\n"+
      "          |                                |\n"+
      "          |            Galaith             |\n"+
      "          |                                |\n"+
      "          |--------------------------------|\n"+
      "          |                                |\n"+
      "          |      Captain Kelien Silith     |\n"+
      "          |                                |\n"+
      "          |     Sails to the village of    |\n"+
      "          |           SaMorgan             |\n"+
      "          |                                |\n"+
      "          |         passage 20 cc          |\n"+
      "          |                                |\n"+
      "          $--------------------------------$\n");
    return "";
}
