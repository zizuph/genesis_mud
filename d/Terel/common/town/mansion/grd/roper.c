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
  alig=(-100);
  set_name(({"koekkenmoddig"}));
  set_short("koekkenmoddig");
  set_long(break_string("A huge lumbering shape of living refuse. It has "+
     "eight long "+
     "long slithering, barbed, dark green tentacles radiating out from the "+
     "central body. Three of them are severely damaged. That must have been "+
     "those vines that you have been cuting. The body seems to be a putrid "+
     "brown amorphous mass. "+
     "There is no distictive features except for a huge mouth, "+
     "filled with sharp teeth and sinous cilia. \n",70));
  set_adj(({"living","huge"}));
  set_race_name("plant");
  set_alignment(alig);
  set_stats(({75,65,90,40,35,70}));
  set_aggressive(0);
  set_hp(9999);
   set_mana(9999);
   set_fatigue(9999);
  set_gender(2);
  set_skill(SS_DEFENCE,30+random(20));
  set_skill(SS_UNARM_COMBAT,50);
  set_skill(SS_BLIND_COMBAT,100);
   add_prop(LIVE_I_QUICKNESS,80);
  set_skill(SS_AWARENESS,65+random(20));
  add_prop(OBJ_I_WEIGHT, 1000000);
   add_prop("_ranger_i_not_brawl",1);
  add_prop(OBJ_I_VOLUME, 1000000);
   add_prop(CONT_I_MAX_VOLUME, 70001);
       add_prop(LIVE_I_SEE_DARK,3);
       add_prop(LIVE_I_SEE_INVIS,2);
  set_whimpy(0);
}

#define A_TANG  0
#define A_BITE 1

#define H_BODY 0
#define H_TENT 1
public void
cr_configure()
{
    object ob3;
    add_attack(79,45,W_BLUDGEON,95,A_TANG);
    add_hitloc( ({ 40, 20, 52 }), 80, "body", H_BODY);
    add_attack(77,75,W_IMPALE,5,A_BITE);
    add_hitloc( ({ 25, 18, 25 }), 20, "tentacle", H_TENT);
}

public string

cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_TANG:return "lashing tentacle";
    case A_BITE:return "gruesome diseased bite";
    }
}

