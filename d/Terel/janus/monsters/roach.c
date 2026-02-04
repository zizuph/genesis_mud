 /* warrior bug */
 /* janus 920901 */
 /* Revisions: Lilith Oct 2021: Player notified me that these are way too 
 *                    tough after the white hits change. I've reduced the 
 *                    damage of the attack.
 */

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

create_creature()
{
  int alig;
  if (!IS_CLONE) return;
  alig=(-20);
  set_name(({"cockroach"}));
  set_short("cockroach");
  set_long(break_string("A huge black glistening cockroach. Black carapace "+
  "protects most of its body. Only the eyes and the antennas are unprotected. "+
     ".\n",70));
  set_adj(({"black"}));
  set_race_name("cockroach");
  set_alignment(alig);
  set_stats(({110,70,110,5,5,60}));
  set_aggressive(1);
  set_hp(8100);
  set_gender(random(2));
  set_skill(SS_CLIMB,random(25)+30);
  set_skill(SS_DEFENCE,random(15)+50);
  add_prop(OBJ_I_WEIGHT, 1800000);
  add_prop(OBJ_I_VOLUME, 1800000);
  add_prop(CONT_I_MAX_WEIGHT, 2400000);
  add_prop(CONT_I_MAX_VOLUME, 2400000);
  set_whimpy(1);
}

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_ANTE 3
#define H_EYES 4

public void
cr_configure()
{
// White hits change has made this attack too strong. --Lilith	
//    add_attack(75,45,W_SLASH,100,A_BITE);
    add_attack(35,35,W_SLASH,100,A_BITE);
    add_hitloc( ({ 5, 5, 5 }), 5, "eye", H_EYES);
    add_hitloc( ({ 40, 40, 40 }), 15, "head", H_HEAD);
    add_hitloc( ({ 50, 50, 50 }), 60, "body", H_BODY);
    add_hitloc( ({ 25, 25, 25 }), 15, "legs", H_LEGS);
    add_hitloc( ({ 5, 5, 5 }), 5, "antenna", H_ANTE);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    }
}
