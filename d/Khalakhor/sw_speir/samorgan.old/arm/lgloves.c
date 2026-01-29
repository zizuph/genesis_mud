/* Gloves
 * Created by Damaris 03/2001
 */
#pragma strict_types
#include "arm.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
inherit "/std/armour";

private string query_gloves();
string _ADJ = query_gloves();

void create_armour()
{
  set_short("pair of " + _ADJ + " leather gloves");
  set_pshort("pairs of " + _ADJ + " leather gloves");
  set_name("gloves");
  set_adj( _ADJ  );
  set_long("A " + short() +" meant to be worn on the hands.\n");
  set_ac(10);
  add_prop(OBJ_I_VALUE, 200);
  set_at(A_HANDS);
  set_am( ({-1,3,-2 }) );
  set_af(this_object());
}
private string
query_gloves()
{
  string *adjectives = ({
        "grey", "brown",
        "tan", "black"
                        });

  return adjectives[random(sizeof(adjectives))];
}
