/* created by Aridor 10/12/93 
 *
 * Modified by Blizzard, 20.02.2004, Added some hooks so boars assist
 *                                   their teammembers.
 */


#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/estwilde/local.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>

inherit   AC_FILE
inherit   "/std/act/attack";

#define   WARBOAR_WOUND    "_neidar_warboar_wound_"

void
create_creature()
{
    int i;

    set_name("boar");
    set_race_name("pig");
    set_adj("massive");
    add_adj("war");
    set_short("massive war boar");

    set_gender(0);
    set_long("This is a massive angry war boar, trained by " +
      "the Neidar as mighty fighting machines. Huge tusks protrude " +
      "from its mouth, tipped with steel, making it a lethal opponent.\n");

    set_stats(({119, 70, 130, 90, 90, 101}));

    set_hp(5000);
    set_alignment(0);
    set_knight_prestige(0);

    NEVERKNOWN;
    set_skill(SS_UNARM_COMBAT, 75);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_AWARENESS, 90);
    
    add_prop(LIVE_I_SEE_DARK, 3);

    set_attack_unarmed(1, 70, 60, W_IMPALE, 90, "steel-tipped tusks");
    set_attack_unarmed(2,30,25,W_IMPALE,10,"bite");

    set_hitloc_unarmed(1, 40, 90, "body");
    set_hitloc_unarmed(2, 20, 10, "head");


}

void
initial_attack(object enemy)
{
    object boar_stun;
    
    if ( enemy->query_prop(WARBOAR_WOUND) &&
        (time() < (enemy->query_prop(WARBOAR_WOUND) + 10)) )
    {
        return;
    }

    enemy->catch_msg(QCTNAME(TO)+ " charges into your right leg, " +
      "gouging it nastily with its iron-tipped tusks!\n");
    tell_room(E(TO), QCTNAME(TO)+ " charges into " +
      QTNAME(enemy)+ "'s right leg, gouging it nastily with " +
      "its iron-tipped tusks!\n", ({enemy, TO}));

 /* Modified so we remove old stun object from the target, and clone
  * new one into him to prevent multiple stun objects in one person.
  * Also added a property, so we avoid spamming this function in case
  * player reattacks teammember of this boar. (In old version they
  * kept charging and cloning new wounds.)
  * Blizzard, 20.02.2004
  */
    boar_stun = present("neidar_boar_stun", enemy);
    
    if ( boar_stun )
    {
        boar_stun->remove_object();
    }
    
    boar_stun = clone_object(EOBJ + "boar_stun");
    boar_stun->move(enemy, 1);
    
    enemy->add_prop(WARBOAR_WOUND, time());
}

void
attacked_by(object ob)
{
    command("emote squeaks loudly in annoyance, and charges towards you!");
    command("kill " + ob->query_real_name());

    initial_attack(ob);
}

public void
hook_friend_attacked(object friend, object enemy)
{
    command("assist " + OB_NAME(friend));
    
    initial_attack(enemy);
}

public void
hook_friend_attack(object friend, object enemy)
{
    command("assist " + OB_NAME(friend));
    
    if ( !present("neidar_boar_stun", enemy) )
        initial_attack(enemy);
}

public void
hook_friend_killed(object friend, object killer)
{
    command("kill " + OB_NAME(killer));
    
    initial_attack(killer);
}

void
init_living()
{
    ::init_living();
}
