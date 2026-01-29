/* A knife for the newbie area
 *   Cirion 050296
 */
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";
#include <wa_types.h>
#include <stdproperties.h>

string *randadj = ({ "short","small","thick" });

void create_weapon()
{
  int hit = 14 + random(3); // hit from 14 - 16
  int pen = 18 + random(3); // pen from 18 - 20

  string myadj = randadj[random(sizeof(randadj))];

  set_name("axe");
  add_name("hand axe");
  set_adj(myadj);
  add_adj("hand");
  set_short(myadj + " hand axe");
  set_long("It is a smallish hand axe, designed to slash "
    +"down on the enemy. The quality is poor, though, and "
    +"it looks like it would not hold up too long.\n");

  set_default_weapon(hit, pen, W_AXE, W_SLASH, W_NONE);

  set_likely_dull(6);
  set_likely_corr(8);
  set_likely_break(20);
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 3000);
  add_prop(OBJ_I_VALUE, 285);
}
