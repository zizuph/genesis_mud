/* 
 * Creator:       Zima (copied from Teth and puzit)
 * Date:          April 20, 1997
 * Modifications:
 * Purpose:       This is the sign for the MacDunn to Baile Ashlagh
 *                pier. It inherits a standard sign.
 * Comments:
 * Adapted by Tapakah for the new ship system
 */
 
#pragma save_binary
#pragma strict_types
 
#include <stdproperties.h>
#include "/d/Genesis/ship_new/ships.h"
#include "../ship.h"

#define COMPANY "Genesis ShipLines Company"

inherit STDSIGN;

public void
create_object ()
{
  ::create_sign;
  set_name("sign");
  set_adj("wood-framed");
  set_short("wood-framed sign");
  set_long("@@sign_text");
 
  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 6000);
 
  add_prop(OBJ_M_NO_GET, "The sign is lodged securely, " +
           "and it is impossible to remove.\n");
}
 
public string
get_label (string *lines)
{
  int max_width;
  string label;

  max_width = applyv(max, map(lines, strlen)) + 10;
  if(max_width > 70)
		max_width = 70;
  label = "";
  label += sprintf("%'-'-*s", max_width+4,"-") + "\n";
  label += sprintf("|%*|s|",max_width+2, " ") + "\n";
  label += sprintf("|%*|s|",max_width+2, COMPANY) + "\n";
  label += sprintf("|%*|s|",max_width+2, "Welcomes you to " + SHIP_NAME) + "\n";
  label += sprintf("|%*|s|",max_width+2, " ") + "\n";
  foreach(string line: lines) {
		label += sprintf("|%*|s|",max_width+2, line) + "\n";
  }
  label += sprintf("|%*s|",max_width+2, " ") + "\n";
  label += sprintf("%'-'-*s", max_width+4,"-") + "\n";

  return label;
}
