#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"

#include <ss_types.h>
#include <macros.h>
inherit AM_FILE
inherit AUTO_TEAM


object aid;
void
create_krynn_monster()
{
    int wepnum = random(5);
    string weapon;


    set_name("shadow warrior");
    add_name("warrior");
    set_race_name("shadowpeople");
    set_adj("titanic");
    add_adj("amber-eyed");
    add_adj("titanic amber-eyed");
    set_long("Standing about five feet tall, this shadow warrior " +
      "appears to be a large humanoid bat.  Although incapable of " +
      "flight, its wing membrane stretches from wrist to ankle and " +
      "allows the warrior to glide.  Its head is large and hairy " +
      "with long ears, an upturned nose marks the face, and large " +
      "curved fangs protrude from its mouth.  This warrior in " +
      "particular is the most massive you have ever seen.\n");

    set_short("titanic amber-eyed shadow warrior");
    set_stats(({ 200, 200, 200, 150, 150, 200 }));

    set_aggressive(1);
    set_hp(20000);
    set_alignment(300);
     set_knight_prestige(-150);
     set_all_hitloc_unarmed(15);
     set_skill(22,90);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_HIDE, 65);
    set_skill(SS_SNEAK, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(21,100);
    /* We need to make sure the user ids are correct before we
     * attempt to clone anything.
     */
    setuid();
    seteuid(getuid());

    /* Clone the weapon and move it to the monster */
    if (wepnum == 0)
      weapon = "jkknife.c";
    else if (wepnum == 1)
      weapon = "jksword.c";
    else if (wepnum == 2)
      weapon = "jkaxe.c";
    else if (wepnum == 3)
      weapon = "jkhammer.c";
    else
      weapon = "jkpole.c";
    clone_object(SOBJ + weapon)->move(this_object(), 1);
    /* Wield the weapon */
    command("wield all");

    add_prop(LIVE_I_NEVERKNOWN,1);

    /* Clone the armour and move it to the monster */
    /* Wear the armour */
}

int
special_attack(object enemy)
{
  int hitroll = random(7);
  int teststat = enemy->query_stat(5);
  if (teststat > 140)
    teststat = 140;
  else if (teststat < 80)
    teststat = 80;

  if (hitroll == 0)
  {
    if ((TO->query_hp()) > ((TO->query_max_hp())/3))
    {
      enemy->catch_msg(QCTNAME(TO) + " yawns fiercely at you.\n");
      tell_room(E(TO),QCTNAME(TO) + " yawns fiercely at " +
        QCTNAME(enemy) + ".\n", ({enemy,TO}));
      if ((random(100)+70) < teststat)
      {
        enemy->catch_msg("You manage to stifle a yawn of your own.\n");
        tell_room(E(TO),QCTNAME(enemy) + " holds back the urge to yawn.\n",
          ({enemy,TO}));
      }
      else
      {
        enemy->catch_msg("You fail to hold back the urge to yawn.\n" +
          "You feel more tired.\n");
        tell_room(E(TO),QCTNAME(enemy) + " yawns tiredly.\n",
          ({enemy,TO}));
        enemy->set_fatigue((enemy->query_fatigue())-((enemy->query_max_fatigue())/10));
        if (enemy->query_fatigue()<0)
          enemy->set_fatigue(0);
      }
    }
    else
    {
      tell_room(E(TO),QCTNAME(TO) + " hoots loudly to summon assistance.\n",0);
      aid = clone_object(SLIVE + "warrior");
      aid->move(E(TO), 1);
      tell_room(E(TO),QCTNAME(aid) + " glides down from a shaft above.\n",aid);
    }
  return 1;
  }
  return 0;
}
