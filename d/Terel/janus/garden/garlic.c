 /*
  * garlic.c
  *
  * will make vampyrs go wimpy
  * Olorin, April 1993
  * Last mod: check for query_guild_name_occ() too, Olorin 10-jun-1993
  */
inherit "/std/herb";

#include "/sys/herb.h"
#include <macros.h>
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <ss_types.h>

int aid = 0;

public void
create_herb()
{
  set_name("bulb");
  add_name("cloves");
  add_name("spice");
  add_name("_spice");
  set_adj("white");
  set_adj("rose-tinged");
  set_adj("smelly");
  set_herb_name("garlic");
  set_short("smelly white rose-tinged bulb");
  set_pshort("smelly white rose-tinged bulbs");
  set_ingest_verb("eat");
  set_unid_long("This is a smelly white rose-tinged bulb. It seems to have " +
                "been dug out of the earth recently and gives off a sharp " +
                "pungent smell.\n");
  set_id_long("This is a garlic bulb. Garlic (Allium sativum) is a hardy, " +
              "perennial bulb plant of the lily family growing in warm and " +
              "moderate climate. It can reach a height of two feet and has " +
              "very narrow, keeled leaves with dense spherical heads of " +
              "pinkish flowers. The white rose-tinged bulbs of strong odour " +
              "are thinly covered and break into separate parts, or cloves. " +
              "Since ancient times, garlic cloves have been used to flavour " +
              "dishes. Some rhymes of old days claim that garlic has the " +
              "magical property of protecting against some kindreds of " +
              "undead, but for centuries no one in Gondor has been able to " +
              "verify this claim.\n");
  set_herb_value(50 + random(50));
  set_id_diff(20);
  set_find_diff(5);
  set_effect(HERB_HEALING, "hp", 2);
  set_decay_time(5000);
}

public string
query_recover()
{
    return MASTER + ":" + query_herb_recover();
}

public void
init_recover(string arg)
{
    init_herb_recover(arg);
}

public int
vamp_check(object ob)
{
    if (ob->test_bit("Emerald", 0, 4) || ob->query_guild_name_occ() ==
        "Vampyr guild") return 1;
    return 0;
}

public int
vamp_filter(object ob)
{
    if (!ob || !living(ob)) return 0;
    if (!interactive(ob)) return 0;
    if (vamp_check(ob)) return 1;
    return 0;
}

public void
smell()
{
    object room, *people, me;
    int i, rnd, strength;

    room = ENV(TO);
    if (!room->query_prop(ROOM_I_IS)) room = ENV(room);
  
    if (!room->query_prop(ROOM_I_IS)) return;
  
    tell_room(room, "A sharp pungent smell pervades the surroundings.\n");

    people = filter(all_inventory(room), vamp_filter);
  
    for (i=0; i<sizeof(people); i++)
    {
         rnd = 195 - random(61) - random(61);
         strength = people[i]->query_stat(SS_DIS) + 
                    people[i]->query_stat(SS_OCCUP);
         if (rnd > strength)
         {
              people[i]->catch_msg("The terrible stench makes you sick. " +
                                   "You run away head over heels.\n");
              tell_room(room, QCTNAME(people[i]) + " flees from the " +
                        "stench.\n", people[i]);
              people[i]->run_away();
         }
         else
         {
              people[i]->catch_msg("The terrible stench makes you sick. " +
                                   "You want to run away, but you barely " +
                                   "manage to overcome your fright.\n");
              tell_room(room, QCTNAME(people[i]) + " shrinks away from " +
                              "the stench. " + CAP(people[i]->query_pronoun()) +
                              " looks terribly frightened.\n", people[i]);
              people[i]->add_panic(rnd/10);
         }
    }
}

public void
init()
{
  ::init();
  
  if (!aid)
      aid = set_alarm(2.0, itof(20 + random(20)), smell);
}

public void
enter_env(object dest, object old)
{
    if (dest && living(dest) && vamp_check(dest))
    {
        clear_effect();
        set_poison_file(HERB_DIR + "garlic_vamp_effect");
        set_effect(HERB_POISONING, "garlic", 10);
    }
    else if (old && living(old) && vamp_check(old))
    {
        clear_effect();
        set_effect(HERB_HEALING, "hp", 2);
    }
    else
    {
        clear_effect();
        set_effect(HERB_HEALING, "hp", 2);
    }
    
    ::enter_env(dest, old);
}
