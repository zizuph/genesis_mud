 /* worker tangler */
 /* janus 920901 */
 
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define TO this_object()
#define TP this_player()
int plantstr;
object ob;
create_creature()
{
  int alig;
  if (!IS_CLONE) return;
  alig=(-40);
  set_name(({"vine"}));
  set_short("strangler vine");
  set_long(break_string("A long slithering, thorny, dark green vine. "+
     "Thick bark protects the whole length of the vine.\n",70));
  set_adj(({"strangler","thorny"}));
  set_race_name("plant");
  set_alignment(alig);
  set_stats(({55,35,60,5,5,50}));
  set_aggressive(0);
  set_hp(2900);
  set_gender(2);
  set_skill(SS_DEFENCE,random(25)+10);
  set_skill(SS_BLIND_COMBAT, 100);
   set_skill(SS_UNARM_COMBAT,40);
  set_skill(SS_AWARENESS, 80);
  add_prop(OBJ_I_WEIGHT, 100000);
  add_prop(OBJ_I_VOLUME, 100000);
  add_prop(CONT_I_MAX_VOLUME, 70001);
   add_prop("_ranger_i_not_brawl",1);
      add_prop(LIVE_I_SEE_DARK,3);
      add_prop(LIVE_I_SEE_INVIS,2);
  set_whimpy(0);
}

#define A_TANG  0

#define H_BODY 0

public void
cr_configure()
{
    object ob3;
    add_attack(66,25,W_BLUDGEON,100,A_TANG);
    add_hitloc( ({ 18, 15, 22 }), 100, "central stem", H_BODY);
}

public string

cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_TANG:return "tangle attempt";
    }
}

