/*
 * Based on the rodent
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

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"

#define M_STR    (10)
#define M_DEX    (10)
#define M_CON    (10)
#define M_INT    (10)
#define M_WIS    (10)
#define M_DIS    (10)

#define M_HP    (9999)
#define M_MANA  (9999)
#define M_ALIGN (-100)

#define MALE        (0)
#define FEMALE      (1)
#define NEUTER      (2)

void
create_monster()
{
     if (!IS_CLONE) return;


     set_stats(({M_STR, M_DEX, M_CON, M_INT, M_WIS, M_DIS}));
     set_hp(M_HP);
     set_mana(M_MANA);
     set_alignment(M_ALIGN);

     set_skill(SS_UNARM_COMBAT, 30);
     set_skill(SS_WEP_SWORD, 50);


     set_name(({"snake"}));
     set_short("scaly snake");
     set_long("A scaly snake with sharp fangs\n");
     set_adj(({"scaly","snake"}));
     set_race_name("snake");
     set_aggressive(0);
     set_act_time(20);
     add_act(({"stare","sniff"}));
     set_gender(random(2));
     set_skill(SS_DEFENCE,random(5)+5);
     add_prop(OBJ_I_WEIGHT, 500);
     add_prop(OBJ_I_VOLUME, 500);
     set_whimpy(1);
}

#define A_BITE   0

#define H_HEAD 0
#define H_BODY 1

public void
cr_configure()
{
    add_attack(2,1,W_SLASH,40,A_BITE);

    add_hitloc( ({ 2, 2, 2 }), 10, "head", H_HEAD);
    add_hitloc( ({ 1, 1, 1 }), 40, "body", H_BODY);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    }
}
