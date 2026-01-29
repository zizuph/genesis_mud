
// Shopkeeper
// creator(s): Ilyian
// last update: 
// purpose:    
// note:
// bug(s):
// to-do:       
inherit "/d/Avenir/inherit/monster.c";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include <language.h>
#include <money.h>

void
create_monster()
{
        ::create_monster();
        set_name("shopkeeper");
        add_name(({"shopkeeper","keeper"}));
        set_race_name("gnome");
        set_gender(1);
        add_adj("short");
        set_long("A shopkeeper. Pretty unintersting.\n");

        set_stats(({30,30,30,30,30,30}));
        set_hp(300);
        set_alignment(100);
        set_knight_prestige(-10);

        set_act_time(1);
        add_act("say hi.");

}

arm_me()
{
   seteuid(geteuid(this_object()));
   MONEY_MAKE_CC(random(40))->move(this_object());


   clone_object(BAZAAR + "Obj/worn/ppants")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pshoes")->move(TO, 1);
   clone_object(BAZAAR + "Obj/worn/pbelt")->move(TO, 1);
   command("wear all");
}

