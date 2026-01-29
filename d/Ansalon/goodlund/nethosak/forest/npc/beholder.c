#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit AC_FILE

#define A_MAW  0
#define H_BODY 0
#define H_CEYE 1
#define H_EYES 2
#define H_SEYE 3

void
create_creature()
{
   set_name("beholder");
   set_adj("evil");
   set_race_name("beholder");
   set_short("evil beholder");
   set_long("This creature, also called the sphere of many eyes or "+
    "the eye tyrant, appears as a large orb dominated by a central eye "+
    "and a large toothy maw, has ten smaller eyes on stalks sprouting "+
    "from the top of the orb. Among adventurers, beholders are known "+
    "as deadly adversaries. "+
    "Equally deadly are a number of variant creatures known "+
    "collectively as beholder-kin, including radical and related "+
    "creatures, and an undead variety. These creatures are related "+
    "in manners familial and arcane to the 'traditional' beholders, "+
    "and share a number of features, including the deadly magical "+
    "nature of their eyes. "+
    "The globular body of the beholder and its kin is "+
    "supported by levitation, allowing it to float slowly about as it "+
    "wills.\n");
   
   set_aggressive(1);
   
   set_gender(G_NEUTER);
   set_stats(({ 170, 170, 170, 130, 100, 110}));
   set_skill(SS_DEFENCE, 120);
   set_skill(SS_AWARENESS, 80);
   set_skill(SS_UNARM_COMBAT, 120);
   set_skill(SS_BLIND_COMBAT, 60);
     
   set_attack_unarmed(A_MAW, 50, 50, W_SLASH, 90, "toothy maw");
   add_prop(OBJ_I_RES_MAGIC, 40);
   set_hitloc_unarmed(H_BODY, ({40,35,35,35}), 75,"body");
   set_hitloc_unarmed(H_CEYE, ({40,35,35,35}), 10,"central eye");
   set_hitloc_unarmed(H_EYES, ({40,35,35,35}), 10,"eyestalk");
   set_hitloc_unarmed(H_SEYE, ({ 30, 28, 30, 30}), 5, "one of the smaller eyes");

}

public void
do_die(object killer)
{
    object room = E(TO);

    if ((killer->query_prop("_i_have_the_jilan_quest")==1) &&
        (killer->query_prop("_caught_fish")==1))
    {
        add_leftover(MOBJ + "key.c", "key", 1, 0, 0, 1);
        add_leftover(MOBJ + "beholder_eye.c", "eye", 1, 0, 0, 1);
        update_state();
        killer->add_prop("_i_got_the_hacchak",1);
    }
    tell_room(room, "The beholder suddenly collapses and falls to the ground, dead.\n", ({ TO }));
    ::do_die(killer);   
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

        attacktype = random(10);

        hitloc = ({"left arm","right arm","body","left leg","right leg"});

        // ------------------------ CAST MAGIC MISSILE! ------------------------
        if (attacktype == 1)
        {
            pen = 300 + random(400);
            pen -= pen * enemy->query_prop(MAGIC_I_RES_FIRE) /100;
            hitres = enemy->hit_me(pen, 40, TO, -1);
    
            wloc = random(5);
            att  = random(2);

            if (hitres[0] <= 0)
                how = "missing";
            if(hitres[0] > 0)
                how = "burning";

            enemy->catch_msg(QCTNAME(TO) + 
              " utters the words: Kalith Karan, Tobanis-kar!"+
              " and looks at you. A small missile of magic leaps from one "+
                "of the smaller eyes, " +how+ " your " + hitloc[wloc] + ".\n");

            tell_room(E(TO), QCTNAME(TO) + " utters the words: Kalith Karan, Tobanis-kar!"+
              " and looks at " + QTNAME(enemy) + ". A small missile of magic leaps from one "+
              "of the smaller eyes, " +how+ " " + QTNAME(enemy) +
              "'s " + hitloc[wloc] + ".\n",({enemy, TO}));

            if (enemy->query_hp() <= 0)
            {
                enemy->do_die(TO);
            }
            return 1;
        }
        // ------------------------ CAST BLINDNESS! ------------------------
        if (attacktype == 2)
        {
            enemy->catch_msg(QCTNAME(TO) + 
              " utters the words: Dulak!"+
              " and looks at you with one of its smaller eyes.\n");
            enemy->catch_msg("You have been blinded!\n");

            clone_object("/d/Ansalon/goodlund/nethosak/"+
                "forest/obj/blind_obj")->move(enemy);

            tell_room(E(TO), QCTNAME(TO) + " utters the words: Dulak!"+
              " and looks at " + QTNAME(enemy) +" with one of it's smaller eyes.\n",({enemy, TO}));
            return 1;
        }

    return 0;
}

void
init_living()
{
    ::init_living();
}
