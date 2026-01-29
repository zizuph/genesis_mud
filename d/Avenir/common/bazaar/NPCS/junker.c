// file name:	junker.c
// creator(s):	Ilyian
// last update:	Denis, May'97: Regular updates.
// purpose:	Shopkeeper.
// note:	
// bug(s):
// to-do:

# pragma strict_types

# include "/d/Avenir/common/bazaar/bazaar.h"
# include <money.h>
# include <ss_types.h>
# include <stdproperties.h>

inherit "/d/Avenir/inherit/monster";
inherit "/d/Avenir/inherit/intro";

void
create_monster()
{
    ::create_monster();
    set_name("jubert");
    set_title("the old Junker");
    add_name(({"shopkeeper","keeper"}));
    set_race_name("gnome");
    set_gender(0);

    add_adj("hunched old");
    set_long("An old, old gnome. He's not good for much " +
             "anymore, so it seems he makes his living selling " +
             "trifles and trash.\n");

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
    set_knight_prestige(-2);

    set_mm_in("arrives.");
}

public void
arm_me()
{
    seteuid(getuid());
    MONEY_MAKE_SC(random(40))->move(this_object());

    clone_object(BAZAAR + "Obj/worn/pshirt")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
    clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
    command("wear all");
}
