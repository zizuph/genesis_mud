/* A knife for the newbie area
 *   Cirion 050296
 */
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";
#include <wa_types.h>
#include <stdproperties.h>

string *randadj = ({ "rusty","short-handled","short","nasty","rusty" });

void create_weapon()
{
  int hit = 13 + random(3); // hit from 13 - 15
  int pen = 13 + random(3); // pen from 13 - 15
  string myadj = randadj[random(sizeof(randadj))];

  set_name("dagger");
  add_name(({"knife","blade"}));
  set_adj(myadj);
  set_short(myadj + " dagger");
  set_long("It is a small dagger with a sharp point. The hand "
    +"guard is round and quite large.\n");

  set_default_weapon(hit, pen, W_KNIFE, W_IMPALE, W_NONE);

  set_likely_dull(6);
  set_likely_corr(8);
  set_likely_break(10);
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 3000);
  add_prop(OBJ_I_VOLUME, 2000);
  add_prop(OBJ_I_VALUE, 183);
}
