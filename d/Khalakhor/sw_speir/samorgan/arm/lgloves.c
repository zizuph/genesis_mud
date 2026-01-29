/* Gloves
 * Created by Damaris 03/2001
 * Tidied up and optimized by Tapakah, 05/2021
 */
#pragma strict_types

#include <stdproperties.h>
#include <wa_types.h>

#include "../defs.h"

inherit KSTDARMOUR;

private string query_gloves();
string gloves_style = query_gloves();

void create_khalakhor_armour ()
{
  set_short("pair of " + gloves_style + " leather gloves");
  set_pshort("pairs of " + gloves_style + " leather gloves");
  set_name("gloves");
  set_adj(gloves_style);
  set_long("A " + short() +" meant to be worn on the hands.\n");
  set_ac(10);
  add_prop(OBJ_I_VALUE, 200);
  set_at(A_HANDS);
  set_am( ({-1,3,-2 }) );
  set_af(this_object());
}

private string
query_gloves ()
{
  string *adjectives = ({
    "grey", "brown",
    "tan", "black"
  });

  return adjectives[random(sizeof(adjectives))];
}
