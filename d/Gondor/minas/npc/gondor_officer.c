/* This file is /d/Gondor/minas/npc/gondor_officer.c   */
/*                                                     */
/* Olorin, July 1993                                   */
/* Redefined for Minas Tirith guards by Elessar, May 1994   */
/* Increased size and skills, Eowul, April 11th, 2009 */

inherit "/d/Gondor/minas/npc/std_gondor_guard.c";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define WEP_ARRAY1 ({WEP_DIR + "dlongsword", WEP_DIR + "hhalberd", WEP_DIR + "gbattleaxe"})
#define WEP_ARRAY2 ({ARM_DIR + "gshield" })
#define ARM_ARRAY1 ({ARM_DIR + "ghelmet"})
#define ARM_ARRAY2 ({ARM_DIR + "schainmail"})

string gate;

create_monster()
{
  int rnd;
  if (!IS_CLONE) return;
  seteuid(getuid());
  ::create_monster();

  set_short("stern officer");
  set_pshort("officers");
  set_name("officer");
  set_pname("officers");
  set_long(BSN(CAP(LANG_ADDART(implode(query_adjs()," "))) + 
    " officer of the Gondorian Army. He is probably from Anorien or Lossarnach, " +
    "the provinces closest to Minas Tirith. His proud stance makes him look "+
    "like he his the veteran of many battles. Experienced and skilled as he is, he " +
    "is a terrifying opponent in combat. "));
    
  rnd = random(60);
  default_config_npc(160+rnd/2);
  set_base_stat(SS_DIS, 180 + rnd);
  set_alignment(350+rnd*10);
  set_skill(SS_WEP_SWORD, MIN(100, 75 + rnd));
  set_skill(SS_WEP_POLEARM, MIN(100, 75 + rnd));
  set_skill(SS_WEP_CLUB, MIN(100, 75 + rnd));
  set_skill(SS_WEP_AXE, MIN(100, 75 + rnd));
  set_skill(SS_WEP_KNIFE, MIN(100, 75 + rnd));
  set_skill(SS_PARRY, MIN(100, 75 + rnd));
  set_skill(SS_DEFENCE, MIN(100, 75 + rnd));
  add_prop(CONT_I_HEIGHT,170+rnd);
  add_prop(CONT_I_WEIGHT,85000+rnd*500);
  add_prop(CONT_I_VOLUME,80000+rnd*500);    
  refresh_mobile();
}

void set_arm_arrays()
{
  ::set_arm_arrays();
  wep1 = WEP_ARRAY1;
  wep2 = WEP_ARRAY2;
  arm1 = ARM_ARRAY1;
  arm2 = ARM_ARRAY2;
}

void
set_gate(string str)
{
    gate = str;
}

string
query_gate()
{
    return gate;
}

query_knight_prestige() { return -8; }

