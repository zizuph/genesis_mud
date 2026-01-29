#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <money.h>
#include <stdproperties.h>
#include <const.h>
#include <macros.h>
#include <options.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
inherit "/d/Ansalon/std/monster";
string face();

void
create_krynn_monster()
{ 
    set_name("priest");
    set_adj("tall");
    add_adj(face());
    set_race_name("minotaur"); 
    set_short("tall " +face()+ " minotaur");    set_gender("G_MALE");
    set_long("This is one of the minotaurs on the Island of Mithas. "+
             "It's extremely tall almost seven feet in height, short "+
             "fur covers his massive body and a thin fuzz hides their "+
             "faces and covers their forearms. It's bullish face is "+
             "brutish and ugly, with a broad snout and wide-set eyes. "+
             "It has long, wide hands with thick fingers ending in short "+
             "claws. This minotaur is dressed in a black robed, which "+
             "might endicate that he are one of the priests "+
             "of the temple.\n");
    
    set_stats(({140,110,140,100,50,99}));
    set_alignment(random(50)-25);
    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 65000);
    
    set_act_time(5);
    add_act("emote snorts violently.");
    add_act("emote chants silently.");
 
    // Set skills.
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 50);
    set_skill(SS_AWARENESS, 60);
    MONEY_MAKE(random(5) + 10,"gold")->move(TO,1);
    clone_object(MARM + "silverrobe.c")->move(TO,1);
    command("wear all");

}

string
face()
{
    // Set description.
    string *faces;
    faces = ({"priestly", "robed"});
    return faces[random(sizeof(faces))];
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;

    attacktype = random(5);

    hitloc = ({"left arm","right arm","body","left leg","right leg"});

    if (attacktype == 1)
    {
        pen = 150 + random(200);
        pen -= pen * enemy -> query_prop(MAGIC_I_RES_FIRE) /100;
        hitres = enemy -> hit_me(pen, 40, TO, -1);

        wloc = random(5);
        att  = random(2);

        if (hitres[0] <= 0)
            how = "missing";
        if(hitres[0] > 0)
            how = "slightly burning";
        if(hitres[0] > 10)
            how = "burning";
        if(hitres[0] > 20)
            how = "igniting";
        if (hitres[0] > 30)
            how = "surrounding";
        if (hitres[0] > 45)
            how = "engulfing";

        enemy->catch_msg(QCTNAME(TO) + 
          " mumbles strange words and points"
          + " towards you. A bolt of energy leaps from the "+
            "palm of his hand, " +how+ " your " + hitloc[wloc] + ".\n");

        tell_room(E(TO), QCTNAME(TO) + " points" +
          "at " + QTNAME(enemy) + ". A bolt of energy " +
          "leaps from the palm of his hand, " + how + " " + QTNAME(enemy) +
          "'s " + hitloc[wloc] + ".\n",({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }

        return 1;
    }

    return 0;
}

