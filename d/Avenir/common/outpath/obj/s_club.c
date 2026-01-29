/* A spiked club for the newbie area
 *   Cirion 050296
 */
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";
#include <wa_types.h>
#include <stdproperties.h>

string *randadj = ({ "wooden","hefty","large" });

void create_weapon()
{
  int hit = 19 + random(3); // Hit from 19 - 21
  int pen = 16 + random(3); // Pen from 16 - 18

  string myadj = randadj[random(sizeof(randadj))];

  set_name("club");
  set_adj(myadj);
  add_adj("spiked");
  set_short(myadj + " spiked club");
  set_long("It is a hefty wooden club, made of oak. Scattered "
     +"along the head of the club are long metal spikes placed "
     +"at random intervals.\n");
  add_item(({"spike","spikes"}),"They look nasty!\n");

  set_default_weapon(hit, pen, W_CLUB, (W_BLUDGEON | W_IMPALE), W_NONE);

  set_likely_dull(6);
  set_likely_corr(8);
  set_likely_break(0);
  set_hands(W_ANYH);

  add_prop(OBJ_I_WEIGHT, 4275);
  add_prop(OBJ_I_VOLUME, 7305);
  add_prop(OBJ_I_VALUE, 209);
}
