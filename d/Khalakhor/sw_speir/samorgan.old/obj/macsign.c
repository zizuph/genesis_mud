/* sign for Port MacDunn
 * MacDunn/SaMorgan
 * Damaris 03/2001
 */
 
#pragma save_binary
#pragma strict_types
 
inherit "/d/Khalakhor/std/obj/sign.c";
#include <stdproperties.h>
 
public void create_object()
{
    set_name("sign");
    set_adj("wooden");
    set_short("wooden sign");
    set_long("@@sign_text");
    add_cmd_item(({"sign","wood-framed sign"}), "read","@@sign_text");
 
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6000);
 
    add_prop(OBJ_M_NO_GET, "The sign is lodged securely, " +
      "and it is impossible to remove.\n");
}
 
public string sign_text()
{
    write(
      "+---------------------------------+\n"+
      "|     Dock of the Bella Diaz      |\n"+
      "+---------------------------------+\n"+
      "|     Kristo MacDuff, Captain     |\n"+
      "|                                 |\n"+
      "|            Sails to             |\n"+
      "|          Port MacDunn           |\n"+
      "|          passage 40 cc          |\n"+
      "+---------------------------------+\n");
    return "";
}
