/**********************************************************************
 * - egsign.c                                                       - *
 * - Dock sign for Galaith Isle                                     - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Undated by Damaris@Genesis 05/2005                             - *
 * - Ported by Tapakah to new ship system 04/2009                   - *
 **********************************************************************/
#pragma save_binary
#pragma strict_types
 
inherit "/d/Khalakhor/std/obj/sign.c";
#include <stdproperties.h>
 
public void create_object()
{
    set_name("sign");
    set_adj("small wooden");
    set_short("small wooden sign");
    set_long("@@sign_text");
    add_cmd_item(({"sign","small wooden sign"}), "read","@@sign_text");
 
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
      "          |            SaMorgan            |\n"+
      "          |                                |\n"+
      "          |--------------------------------|\n"+
      "          |                                |\n"+
      "          |      Captain Kelien Silith     |\n"+
      "          |                                |\n"+
      "          |       Sails to the isle of     |\n"+
      "          |             Galaith            |\n"+
      "          |                                |\n"+
      "          |     The line to Galaith has    |\n"+
      "          |       been moved to Cadu       |\n"+
      "          |    Genesis ShipLines Company   |\n"+
      "          |                                |\n"+
      "          $--------------------------------$\n");
    return "";
}
