/*
  This is a mana restoring potion. It restores MANA mana points.
  The code is mostly stolen from Yodah.
*/

inherit "/d/Shire/open/potion";

#include "macros.h"
#include <stdproperties.h>

#define MANA 30

create_potion() {
  ::create_potion();
  seteuid(getuid());
  set_duration(0);
  set_color("grey");
  set_effectshort("mana");
  set_effectlong("This potion looks dangerous.\n");
  set_smell("nice");
  set_taste("vile");
  set_identified(0);
  /*set_identvalue(600); */
  add_prop(OBJ_I_VALUE, 350);

}

int start_effect() {
  write(
	"Ugh! This potion tasted BAD! You feel like your mouth\n" +
	"is full of garlic.\n" +
	"Then you suddenly feel a tingling sensation.\n");
  say(QCTNAME(this_player()) + " looks like he swallowed a lemon " +
      "as " + this_player()->query_pronoun() + " quaffs the potion.\n" +
      "Then " + this_player()->query_pronoun() + " suddenly looks much better!\n");
  this_player()->add_mana(MANA);
  delay_destruct();       /* kill ourselves */
}

  
