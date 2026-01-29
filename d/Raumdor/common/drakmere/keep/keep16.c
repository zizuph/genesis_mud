/* Sarr */
#include "defs.h"
inherit KEEP_ROOM;

object lord, cguard, guard1, guard2;

void
create_room()
{
    ::create_room();
    set_short("Near a throne in a grand chamber");
    set_long(
      "You are in the northern part of a grand chamber. The throne sits " +
      "resplendant upon a dais, a glory to behold. All along the walls are " +
      "paintings, statues, weapons, tapestries and many other decorative " +
      "artifacts. A short distance in front of the throne stands a pristine " +
      "font, flanked by two large braziers.\n");
    add_item("paintings",
      "They are pictures of many wonderes and nightmarish things. They are " +
      "very beautiful.\n");
    add_item("statues", "Beautiful sculptures of men and women.\n");
    add_item("weapons", "They hang off the wall as treasures.\n");
    add_item("tapestries",
      "They are beautifully woven, depciting many wonderous scenes.\n");
    add_item(({"artifacts", "treasures"}),
      "Many assorted treasures adorn the walls.\n");
    add_item("dais", "A short, five-step dais that holds the throne.\n");
    add_item(({"brazier", "braziers"}),
      "Large iron pots that burn to make heat and light.\n");
    add_item("throne",
      "It must be the throne of the keep. It is made of gold and encrusted " +
      "with many valuable jewels and metals.\n");
    add_item(({"font", "pristine font"}),
      "It is made of white marble and immaculately clean. Its prominence in " +
      "the chamber and ornamental pedestal suggest it might be used holy " +
      "ceremonies and rituals. Its basin contains water.\n");
    add_item(({"basin", "water"}), "Clean water sits still in the font's " +
       "basin.\n");
    add_item(({"pedestal", "elaborate pedestal", "ornamental pedestal"}),
      "It is made of solid white marble, like the font it bears, and is " +
      "carved with beautiful artistry.\n");
    
    add_exit(KEEP_DIR + "keep21", "south", "@@block@@");
    reset_room();
}

int
block()
{
    if (TP->query_attack())
    {
        lord->command(
          "shout Run in fear, fiend! The power of the Creator shall strike " +
          "fear into your evil heart!");
        lord->set_hp(10000);
        write("You feel a stricken with fear!\n");
    }
    return 0;
}

void
reset_room()
{
    if (!lord)
    {
        lord = clone_object(KEEP_NPC_DIR + "drakin");

        lord->move_living("xxx", TO);
    }

    if (!cguard)
    {
        cguard = clone_object(DRAKMERE_NPC_DIR + "dguard_chief");

        cguard->move_living("xxx", TO);
    }
    lord->team_join(cguard);

    if (!guard1)
    {
        guard1 = clone_object(DRAKMERE_NPC_DIR + "eg_guard_s");

        guard1->move_living("xxx", TO);
    }
    lord->team_join(guard1);

    if (!guard2)
    {
        guard2 = clone_object(DRAKMERE_NPC_DIR + "eg_guard_s");

        guard2->move_living("xxx", TO);
    }
    lord->team_join(guard2);
}
