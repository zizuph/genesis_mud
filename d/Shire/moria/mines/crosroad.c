#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

#define HEAL_AMOUNT 1000
int heal;

CONSTRUCT_ROOM {
    heal += HEAL_AMOUNT;
    add_prop(ROOM_I_LIGHT, 1);
    set_short("Cross-roads");
    set_long("Cross-roads. The air is filled with an odour of thurible and "+
	     "mirra, and a tallow candle standing high upon a niche spreads "+
	     "warm light in the room. A wide passage from east continues to "+
	     "the west here. To the north a smaller exit opens in the "+
	     "floor.\n");
    add_item(({"light","candle"}),
	     "It is far to high for you to reach, and anyway, you wouldn't "+
	     "like to ruin the aura of this cosy room.");
    add_item("niche","It is situated high above you.");
    add_item(({"air","mirra","thurible","odour","aura"}),
	     "It smells strange, but somehow nice! Wonder if this is a holy "+
	     "place?");
    EXIT("goldroom","north");
    EXIT("bat_cave","east");
    EXIT("durhall","west");
}

RESET_ROOM {
    heal += 100; 
}   

init() {
  ::init();
    add_action("my_pray","pray");
    add_action("heal_fun","kneel");
}

my_pray() {
  write("You fold your hands and prays.\n"+
	"Nothing happens. Perhaps kneel?\n");
  tell_room(TO,
    QCTNAME(TP)+" folds his hands and prays.\n", TP);
  return notify_fail("Ok.\n");
}

heal_fun() {
  int avail,needs;
  write("You kneel down.\n");
  say(QCTNAME(TP)+" kneels down.\n");
  write("A beam of smoke hits right through your heart!\n");
  say("A beam of smoke hits right through "+QTNAME(TP)+
      "'s heart!\n");
  if (heal > 2000)
    avail = 1000;
  else if (heal > 700)
    avail = 500;
  else if (heal > 200)
    avail = 200;
  else avail = 0;
  if (!avail) {
    write("You get an ugly feeling that there is something fishy going on.\n");
    say(QCTNAME(TP)+" gets a fishy look in "
	+this_player()->query_possessive()+" eyes.\n");
  } 
  else {
    write("Your stomack revolts, but you feel a lot better!!\n");
    say("Strangely enough, "+QTNAME(TP)+" smiles!\n");
    needs = this_player()->query_max_hp() - this_player()->query_hp();
    if (avail > needs)
      avail = needs;
    this_player()->heal_self(avail);
    heal -= avail;
  }
  return 1;
}    
