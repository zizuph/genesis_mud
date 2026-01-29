#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit AUTO_TEAM

void
create_krynn_monster()
{
    set_pick_up_team(({"_kalen_guard"}));
    set_max_team_size_auto_join(3);

    set_name("hobgoblin");
    add_name("goblin");
    add_name("_kalen_guard1");
    add_name("_kalen_guard");
    add_adj("tall");
    add_adj("dirty");
    set_short("tall dirty hobgoblin");
    set_race_name("hobgoblin");
    set_gender("G_MALE");
    set_long("This is one burly hobgoblin standing 6 feel tall and his stance " +
             "and alertness reveals that he is obviously a formidable soldier. " +
             "Looking closer you can see that he is more equiped for stealth " +
             "than for heavy combat.\n");
    
    set_stats(({140+random(50),
                120+random(40),
                80+random(40),
                140+random(20),
                140+random(20),
                140+random(20)}));
    set_hp(query_max_hp());

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    add_prop(CONT_I_WEIGHT, 120000);
    add_prop(CONT_I_HEIGHT, 185);
    add_prop(LIVE_I_QUICKNESS, 100);

    set_all_hitloc_unarmed(40);

    set_alignment(-450);
    set_knight_prestige(40);

    set_cact_time(8);
    add_cact("shout Block the door! There shall be no escape!");
    add_cact("say Coming here was your last mistake.");
    add_cact("say Of all the places you could die, you had to pick our hideout. We should feel honoured.");
    add_cact("emote raises an eyebrow.");
    add_cact("say You thought you could come here and force us to abandon our plans? Hah! You and what army?!");
    add_cact("say Stick out your head and I will make it fast and painless.");
    add_cact("say How nice of you to come and entertain us before our long journey.");

    set_default_answer("If only you could move as fast as your mouth, you might stand a chance.");
}

int
special_attack(object enemy)
{
    int attacktype,
        pen,
        att,
        wloc;
    
    mixed hitres;
    
    string *hitloc,
            how,
            weapon;
    

    if (!sizeof(query_weapon(-1)))
        return 0;

    attacktype = random(5);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});
    
    weapon = query_weapon(-1)[0]->query_short();

    if (attacktype == 1)
    {
        pen = 500+random(400);
        hitres = enemy->hit_me(pen, W_IMPALE, TO, -1);

        wloc = random(5);
        att  = random(2);

        switch(hitres[0])
        {
            case -4..0:
                how = "his " + weapon + " barely missing";
                break;
            case 1..10:
                how = "his " + weapon + " lightly scratching";
                break;
            case 11..20:
                how = "his " + weapon + " piercing";
                break;
            case 21..40:
                how = "his " +weapon+ " impaling";
                break;
            default:
                how = "his " + weapon + " cutting through to the bone of";
        }
        enemy->catch_msg(QCTNAME(TO) + 
                         " makes a quick stab"
                         + " at you, " + how + " your " + hitloc[wloc] + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " makes a quick stab"+ 
                  " at " +QTNAME(enemy) + ", " +how+ " " +POSSESSIVE(enemy)
                  + " " + hitloc[wloc] + ".\n", ({ enemy, TO }));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }
        return 1;
    }
    return 0;
}

void
arm_me()
{
    seteuid(getuid(this_object()));

    clone_object(SOBJ+"poison_dagger")->move(this_object(), 1);
    clone_object(SOBJ+"sharp_dagger")->move(this_object(), 1);
    clone_object("/d/Krynn/pax/armour/leather_arm")->move(this_object(), 1);
    command("wear all");
    command("wield all");
}
