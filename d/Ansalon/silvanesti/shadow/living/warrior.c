#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"

#include <ss_types.h>
#include <macros.h>
inherit AM_FILE
inherit AUTO_TEAM


void
create_krynn_monster()
{
    int num = random(5), wepnum = random(6);
    string first,second,weapon;

    if (num == 1)
      second = "black-furred";
    else if (num == 2)
      second = "gray-furred";
    else if (num == 3)
      second = "brown-furred";
    else if (num == 4)
      second = "green-eyed";
    else
      second = "amber-eyed";

    num = random(5);
    if (num == 0)
      num = 5;

    if (num == 1)
      first = "large";
    else if (num == 2)
      first = "burly";
    else if (num == 3)
      first = "towering";
    else if (num == 4)
      first = "immense";
    else
      first = "enormous";

    set_name("shadow warrior");
    add_name("warrior");
    set_race_name("shadowpeople");
    set_adj(first);
    add_adj(second);
    add_adj(first + " " + second);
    set_long("Standing about five feet tall, this shadow warrior " +
      "appears to be a large humanoid bat.  Although incapable of " +
      "flight, its wing membrane stretches from wrist to ankle and " +
      "allows the warrior to glide.  Its head is large and hairy " +
      "with long ears, an upturned nose marks the face, and large " +
      "curved fangs protrude from its mouth.\n");

    set_short(first + " " + second + " shadow warrior");
    num-=1;
    set_stats(({ num*20+110,
                 num*20+110,
                 num*10+120,
                 num*10+100,
                 num*10+100,
                 num*10+120 }));
    set_aggressive(1);

    set_hp(num*1000+12000);
    set_alignment(200);
    set_knight_prestige(-100);
    set_all_hitloc_unarmed(10);
    set_random_move(15);
    set_skill(22,70);
    set_skill(SS_WEP_CLUB, 90);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 95);
    set_skill(SS_HIDE, 55);
    set_skill(SS_SNEAK, 100);
    set_skill(SS_AWARENESS, 100);
    /* We need to make sure the user ids are correct before we
     * attempt to clone anything.
     */
    setuid();
    seteuid(getuid());

    /* Clone the weapon and move it to the monster */
    if (wepnum == 0)
      weapon = "siflail.c";
    else if (wepnum == 1)
      weapon = "blwhip.c";
    else if (wepnum == 2)
      weapon = "sicklecord.c";
    else if (wepnum == 3)
      weapon = "spikecord.c";
    else if (wepnum == 4)
      weapon = "chainblade.c";
    else
      weapon = "shadowstaff.c";
    clone_object(SOBJ + weapon)->move(this_object(), 1);
    /* Wield the weapon */
    command("wield all");

    add_prop(LIVE_I_NEVERKNOWN,1);
    set_cact_time(10);

    add_cact("twirl cord");
    /* Clone the armour and move it to the monster */
    /* Wear the armour */
}

int
special_attack(object enemy)
{
  int hitroll = random(15);
  int teststat = enemy->query_stat(5);
  if (teststat > 130)
    teststat = 130;
  else if (teststat < 80)
    teststat = 80;

  if (hitroll == 0)
  {
    enemy->catch_msg(QCTNAME(TO)+" yawns fiercly at you.\n");
    tell_room(E(TO),QCTNAME(TO) +" yawns fiercly at " +
      QCTNAME(enemy) + ".\n",({enemy,TO}));
    if ((random(100) + 50) < teststat)
    {
      enemy->catch_msg("You manage to stifle a yawn of your own.\n");
      tell_room(E(TO),QCTNAME(enemy) + " holds back the urge to yawn.\n",
        ({enemy,TO}));
    }
    else
    {
      enemy->catch_msg("You fail to hold back the urge to yawn.\n" +
        "You feel more tired.\n");
       tell_room(E(TO),QCTNAME(enemy) + " yawns tiredly.\n", ({enemy,TO}));
      enemy->set_fatigue((enemy->query_fatigue())-((enemy->query_max_fatigue())/15));
      if (enemy->query_fatigue() < 0)
        enemy->set_fatigue(0);
    }
    return 1;
  }
  return 0;
}
