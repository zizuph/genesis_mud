inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";

#include "/d/Emerald/defs.h";
#include <wa_types.h>;

int pregnant = 0;

void create_creature() {
    if (sizeof(object_clones(this_object())) > 25)
      remove_object();
    set_name("rabbit");
    set_race_name("rabbit"); 
    set_adj("white");
    set_long("It is a really CUTE white rabbit.\n");
    set_stats(({ 5,   4,   3,   2,   3,   4}));
    set_hp(10);
    set_gender(random(2));
    if (query_gender() == 1) {
      add_adj("female");
      add_name("_female_rabbit");
      set_alarm(120.0, 120.0, "procreate");
    }
    if (!query_gender()) {
      add_adj("male");
      set_alarm(30.0, 30.0, "procreate");
    }
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(CONT_I_HEIGHT, 300);
    add_prop(CONT_I_VOLUME, 1500);
    add_prop(CONT_I_IN, 0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_attack_unarmed(0,  6,  7, W_IMPALE, 80, "teeth");
    set_attack_unarmed(1, 12, 12, W_SLASH,  10, "left paw");
    set_attack_unarmed(2, 12, 12, W_SLASH,  10, "right paw");
    set_hitloc_unarmed(0, ({ 5, 7, 3, 2 }), 20, "head");
    set_hitloc_unarmed(1, ({ 5, 4, 8, 0 }), 80, "body");
}

void procreate() {
    int num_babies, x;
    object female_rabbit, new_rabbit, baby_rabbit;
      if (!query_gender()) {
        female_rabbit = present("_female_rabbit", environment());
        if (female_rabbit) {
          female_rabbit->impregnate();
          tell_room(MASTER_OB(environment()), QCTNAME(this_object()) +
                    " demonstrates its ability to procreate wildly " +
                    "as he jumps " + QTNAME(female_rabbit) + "!\n",
                    this_object());
          tell_object(this_object(), "You demonstrate your ability " +
                      "to procreate wildly as you jump " +
                      QTNAME(female_rabbit) + "!\n");
        }
      }
      baby_rabbit = find_object(MBLACK_DIR + "npc/baby_rabbit");
      if (baby_rabbit && pregnant)
      if ((query_gender() == 1) &&
          (sizeof(object_clones(baby_rabbit)) < 25)) {
        tell_room(MASTER_OB(environment()), QCTNAME(this_object()) +
                  " demonstrates its ability to procreate "+
      "wildly as it gives birth to some baby rabbits. " +
                  "Some baby rabbits are born!\n", this_object());
        tell_object(this_object(), "You demonstrate your ability "+
                    "to procreate as you give birth to some baby "+
                    "rabbits!\n");
        num_babies = random(5) + 1;
        for (x=0; x < num_babies; x++) {
          new_rabbit = clone_object(MBLACK_DIR + "npc/baby_rabbit");
          new_rabbit->move(environment());
          team_join(new_rabbit);
        }
        pregnant = 0;
      }
}

void impregnate() {
    pregnant = 1;
}
