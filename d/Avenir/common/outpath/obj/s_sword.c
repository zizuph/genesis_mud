/* A knife for the newbie area
 *   Cirion 050296
 */
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";
#include <wa_types.h>
#include <stdproperties.h>

string *randadj = ({ "hefty", "unwieldly", "long", "rusted" });

void create_weapon()
{
  int hit = 12 + random(2);
  int pen = 12 + random(2);
  string myadj = randadj[random(sizeof(randadj))];

  set_name("sword");
  set_adj(myadj);
  set_short(myadj + " sword");
  set_long("A poorly made sword, there are specks of "
    +"rust all along the blade.\n");

  set_default_weapon(hit, pen, W_SWORD, W_SLASH, W_NONE);

  set_likely_dull(6);
  set_likely_corr(8);
  set_likely_break(10);
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 600);
  add_prop(OBJ_I_VOLUME, 700);
  add_prop(OBJ_I_VALUE, 290);
}
