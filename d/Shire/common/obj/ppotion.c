/*
  This is a poisonous potion. It takes half of your hp's away.
  The code is mostly stolen from Yodah.
*/

inherit "/d/Shire/open/potion";

#include "macros.h"
#include <stdproperties.h>


create_potion() {
  ::create_potion();
  seteuid(getuid());
  set_duration(0);
  set_color("pink");
  set_effectshort("poison");
  set_effectlong("This potion looks rather tasty.\n");
  set_smell("exciting");
  set_taste("good");
  set_identified(0);
  /*set_identvalue(600); */
  add_prop(OBJ_I_VALUE, 50);

}

int start_effect() {
  int hp;
  write(
	"This potion tasted like the finest wine.\n" +
	"But! you suddenly feel a wrenching sensation.\n");
  say(QCTNAME(this_player()) + " looks like he is about to puke " +
      "as " + this_player()->query_pronoun() + " quaffs the potion.\n");

  hp = this_player()->query_hp();
  hp = hp/2;
  this_player()->set_hp(hp);

  write("You suddenly feel alot weaker. Maybe time to see a doctor?\n");
  delay_destruct();       /* kill ourselves */
}

  
