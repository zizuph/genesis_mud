/* cat */
/* janus 920901 */
/*
    Modified: 29 Apr 2003, by Bleys
        - fixed a typo in do_pet()
*/
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

#define TO this_object()
#define TP this_player()

public void
init_living()
{
    ::init_living();
    add_action("do_pet", "capture");
    add_action("do_pet", "catch");
    add_action("do_pet", "pet");
    add_action("do_pet", "grab");
    add_action("do_pet", "crush");
}

public void
create_creature()
{
  set_name("cat");
  set_short("black cat");
  set_long("A cute black cat. It has a small necklace " +
           "around it's neck.\n");
  add_item("necklace", "A silver necklace. " +
                "Hanging from the necklace is a small plaque.\n");
  add_item(({"plaque", "small plaque"}), "The plaque reads: " +
           "Reward for returning of this cat to Joe Gardener.\n");
  set_adj("black");
  set_race_name("cat");
  set_alignment(45);
  set_stats(({10, 20, 10, 10, 10, 10}));
  set_aggressive(0);
  set_hp(100);
  set_gender(1);
  set_skill(SS_CLIMB, random(35) + 5);
  set_skill(SS_DEFENCE, random(15) + 30);
  add_prop(CONT_I_WEIGHT, 1500);
  add_prop(CONT_I_VOLUME, 1500);
  add_prop(CONT_I_MAX_WEIGHT, 2000);
  add_prop(CONT_I_MAX_VOLUME, 2000);
}

#define A_BITE  0
#define A_CLAW  1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3
#define H_EYES 4

public void
cr_configure()
{
  add_attack(20,6,W_SLASH,40,A_BITE);
  add_attack(15,5,W_SLASH,60,A_CLAW);

  add_hitloc( ({ 2, 2, 2 }), 15, "head", H_HEAD);
  add_hitloc( ({ 1, 1, 1 }), 5, "eye", H_EYES);
  add_hitloc( ({ 5, 5, 5 }), 10, "tail", H_TAIL);
  add_hitloc( ({ 3, 3, 3 }), 55, "body", H_BODY);
  add_hitloc( ({ 2, 2, 2 }), 15, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
  switch (aid)
  {
    case A_BITE:return "bite";
    case A_CLAW:return "claw";
  }
}

public int
do_pet(string what)
{
  object catnip;

  seteuid(getuid());
  if (what != "cat" && what != "black cat") return 0;

  if (TP->test_bit("Terel", QUEST_JJ1_GROUP, QUEST_JJ1_BIT)) {
      write("The cat seems to be wary of you since you have "+
            "tricked the cat to get to his owner once before.\n");
      return 1;
  }
  catnip = present("flowers", TP);
  if (catnip && "catnip" == catnip->query_herb_name()) {
      write("When you try to get closer to the cat you notice " +
            "that the cat is very interested in the catnip " +
            "you carry. It seems that the cat will follow you " +
            "anywhere, as long as you carry the catnip.\n");
      add_prop("_cat_finder", TP->query_name());
      set_follow(TP->query_real_name());
      return 1;
  }
  write("When you try to pet the cat, you notice "+
        "that the cat is afraid of you and avoids you elegantly. " +
        "Maybe if you had something that would make the cat interested " +
        "in you, then you would succeed to catch the " + what + ".\n");
  return 1;
}
