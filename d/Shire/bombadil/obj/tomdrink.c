/*
 * Withywindle water. This water is used by Tom Bombadill to 
 * heal himself when attacked. It's enchated water from the 
 * Withywindle river, and is based on the orc drink of the orcs 
 * from Moria. Good aligned creatures, except for mebbe gobbos, 
 * will be healed from it whereas evil cratures will be poisoned.
 * Thanks to Rogon for the original code!
 * -- Finwe, January 2001
 */

#include "../local.h"
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <poison_types.h>

inherit "/std/drink";

#define TD_DELAYED_POISON "/d/Shire/bombadil/obj/tomdrink_delayed_poison"

#define MANA_DROP_EVIL 200
#define HEAL_EVIL      30

#define MANA_DROP_GOOD  100
#define HEAL_GOOD       350

create_drink()
{
    set_soft_amount(330);// A small bottle containing 0.33l.
    set_name("bottle");
    add_name(({"_withy_water_", "liquid", "small bottle"}));

    add_adj(({"sparkling", "clear"}));
    set_short("small bottle of sparkling liquid");
    set_pshort("small bottles of sparking liquid");
    set_long("This small bottle is full of sparkling liquid. It is " +
        "crystal clear and has a slight effervescent quality to " +
        "it with a hint of earth and and flowers.\n");
    add_prop(OBJ_I_VALUE,  10+random(10));
    add_prop(OBJ_M_NO_SELL,0);

    set_drink_msg ("The water tickles your nose as you drink it.\n");
}

public void special_effect(int num)
{
  string race;

  race = TP->query_race();

  // if player isn't goblin, and good aligned, and not undead, 
  // then they can drink the water

  if( (race == "goblin") || 
  (TP->query_alignment() <= -150) || 
  (TP->query_prop(LIVE_I_UNDEAD)) )
  {
    object oDelayedPoison;
    FIXEUID;
    oDelayedPoison = clone_object (TD_DELAYED_POISON);
    set_alarm (0.0, 0.0, &oDelayedPoison->do_poison (this_player (), num));
  }
  else
  {
    TP->add_mana(-num*MANA_DROP_GOOD);
    TP->heal_hp(num*HEAL_GOOD);
  };
}
