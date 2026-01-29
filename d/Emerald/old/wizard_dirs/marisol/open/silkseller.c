// Silkseller	silkseller.c
// creator(s):	Grace
// last update:	Denis, May'97: Regular updates: triggers and such.
// purpose:
// note:
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/common/bazaar/bazaar.h"
# include <language.h>
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";

void
create_monster()
{
    set_name("laurent");
    set_title("the silk seller");
    add_name(({"shopkeeper","keeper", "silkseller"}));
    set_race_name("gnome");
    set_gender(0);

    add_adj(({"smiling", "well-dressed"}));
    set_long("A young and healthy gnome. He seems to be quite "+
             "successful at what he does.\n");

    set_all_hitloc_unarmed(50);

    set_stats(({70,70,70,70,70}));

    set_skill(SS_UNARM_COMBAT,50);
    set_skill(SS_BLIND_COMBAT,100);
    set_skill(SS_PARRY,50);
    set_skill(SS_DEFENCE,65);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_WEP_POLEARM,50);
    set_skill(SS_WEP_CLUB,50);
    set_skill(SS_WEP_KNIFE,50);
    add_prop(NPC_I_NO_RUN_AWAY,1);

    set_alignment(100);
    set_knight_prestige(-1);

    set_mm_in("arrives.");
}

public void
arm_me()
{
   seteuid(geteuid(this_object()));
   MONEY_MAKE_SC(random(40))->move(this_object());

   clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
}
