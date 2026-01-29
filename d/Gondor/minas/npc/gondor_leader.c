/* This file is /d/Gondor/minas/npc/gondor_officer.c   */
/*                                                     */
/* Olorin, July 1993                                   */
/* Increased size and skills, Eowul, April 11th, 2009 */

inherit "/d/Gondor/minas/npc/std_gondor_guard.c";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "dlongsword", WEP_DIR + "gspear", WEP_DIR + "gbattleaxe"})
#define WEP_ARRAY2 ({ARM_DIR + "gshield" })
#define ARM_ARRAY1 ({ARM_DIR + "ghelmet"})
#define ARM_ARRAY2 ({ARM_DIR + "schainmail"})

int patrol_size;
int add_patrol();
int add_3_soldiers(int o);

create_monster()
{
  int rnd;
  if (!IS_CLONE) return;
  seteuid(getuid());
  ::create_monster();

  set_short("gondorian officer");
  set_pshort("officers");
  set_name("officer");
  add_adj("gondorian");
  set_pname("officers");
  set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," "))) + 
    " officer of the Gondorian Army. He is probably from Anorien or Lossarnach, " +
    "the provinces closest to Minas Tirith. His proud stance makes him look "+
    "like he his the veteran of many battles. Experienced and skilled as he is, he " +
    "is a terrifying opponent in combat. He is currently leading a patrol."));
    
  rnd = random(40);
  default_config_npc(105+rnd/2);
  set_base_stat(SS_DIS, 140 + rnd);
  set_alignment(250+rnd*10);
  set_random_move(5);
  set_skill(SS_WEP_SWORD,75+rnd/2);
  set_skill(SS_WEP_POLEARM,75+rnd/2);
  set_skill(SS_WEP_CLUB, 75+rnd/2);
  set_skill(SS_WEP_AXE,  75+rnd/2);
  set_skill(SS_WEP_KNIFE,75+rnd/2);
  set_skill(SS_PARRY,    75+rnd/2);
  set_skill(SS_DEFENCE,  75+rnd/2);
  add_prop(CONT_I_HEIGHT,170+rnd);
  add_prop(CONT_I_WEIGHT,85000+rnd*500);
  add_prop(CONT_I_VOLUME,80000+rnd*500);    
  refresh_mobile();
    set_alarm(3.0, 0.0, add_patrol);
}

void set_arm_arrays()
{
  ::set_arm_arrays();
  wep1 = WEP_ARRAY1;
  wep2 = WEP_ARRAY2;
  arm1 = ARM_ARRAY1;
  arm2 = ARM_ARRAY2;
}

int
add_patrol()
{
  int n, p, o;
  this_object()->set_leader();
  p = patrol_size + random(2);
  while (n <= p/2)
    {
      o = p - n*3;
      if (o > 3) o = 3;
      set_alarm(1.0, 0.0, &add_3_soldiers(o));
      n++;
    }
  return 1;
}

int
add_3_soldiers(int o)
{
  int n;
  object soldier;
  if (o<1) return 0;
  if (o>3) o = 3;
  while (n < o)
    {
      soldier = clone_object(MINAS_DIR+"npc/gondor_soldier");
      soldier->arm_me();
      soldier->move(ENV(TO));
      tell_room(ENV(TO),CAP(LANG_ADDART(soldier->query_nonmet_name()))+" arrives.\n");
      TO->team_join(soldier);
      n++;
    }
  return 1;
}

set_patrol_size(int i)
{
  patrol_size = i;
}

query_knight_prestige() { return -8; }

