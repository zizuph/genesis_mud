/*********************************************************************
 * - sign.c                                                        - *
 * - shipline Gont-Kabal                                           - *
 * - Recoded by Damaris 5/2003                                     - *
 *********************************************************************/
 
#pragma save_binary
#pragma strict_types
 
inherit "/std/object";
#include <stdproperties.h>
 
public void create_object()
{
    set_name("sign");
    set_adj("thick-wooden");
    set_short("thick-wooden sign");
    set_long("@@sign_text");
    add_cmd_item(({"sign","thick-wooden sign"}), "read","@@sign_text");
 
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 6000);
 
    add_prop(OBJ_M_NO_GET, "The sign is lodged securely, " +
      "and it is impossible to remove.\n");
}
 
public string sign_text()
{
    write(
      "+---------------------------------+\n"+
      "|      Dock of the Candelis       |\n"+
      "+---------------------------------+\n"+
      "|     Logaan Leneer, Captain      |\n"+
      "|   Now sails the Newbie Line     |\n"+
      "|   Via Gont, Kabal, Sparkle and  |\n"+
      "|   Gelan. The new pier is in the |\n"+
      "|   southeast of the district     |\n"+
      "|                                 |\n"+
      "|   -- Genesis ShipLines          |\n"+
      "|         Company                 |\n"+
      "+---------------------------------+\n");
    return "";
}
