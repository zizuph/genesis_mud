#pragma save_binary

inherit "/std/room";
#include "../gnome.h"

create_room() {
  set_short("Gnomehome entrance");
  set_long(BS(" This is the entrance to Gnomehome, the ancient dwelling of " +
              "the gnome race. The gate, to the northwest, is framed by two " +
              "massive pillars with a connecting walkway on top. Trying to " +
              "take this place by force would be futile. Beyond the gate, " +
              "you see the dimly lit tunnel sloping downwards, inwards.\n"));

  add_item(({ "gnomehome", "Gnomehome", "dwelling", "town" }),
           BS(" The town is strategically placed where the plains, to your " +
              "south, meet the sheer rock cliff wall to the north. The wall " +
              "has a bay here, so rock surrounds the town on three of eight " +
              "sides. The western part of the mound is covered by trees.\n"));

  add_item(({ "gate", "pillar", "pillars", "walkway" }),
           BS(" The gate is massive, short though the gnomes may be. It's " +
              "clearly designed to stand almost any assault. Guards walk " +
              "back and forth on top of it.\n"));

  add_exit(ROOM_DIR + "corr1", "northwest");
  /*
   * Well, here there should be some sort of exits out on the plain,
   * I suppose? Is there a mechanism for connecting domains on the map?
   * Time to find out.
   */
}