/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 *  A mystic serpent. Mortricia 930310
 *                    Modified to inherit immuto_animal 960110
 */

inherit "/d/Terel/mecien/valley/guild/spells/immuto/immuto_animal";

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

#define TO     this_object()
#define ETO    environment(TO)

#define A_BITE  0

#define H_BODY  0
#define H_HEAD  1

public void
create_creature()
{
    ::create_creature();
    
    set_name("serpent");
    set_long(
        "Arcane and majestic, an enormous serpentine creature of " +
        "emerald hue. Its scales shimmer like a coat of jewels. Its " +
        "mouth filled with long fangs, its eyes burning bright like " +
        "radiant stars.\n"
    );
    set_adj(({"giant", "emerald"}));
    set_race_name("serpent");

    set_stats( ({100,145,125,30,80,90}) );
    set_learn_pref( ({10,10,10,10,10,10}) );
    set_hp(9999);
    set_mana(9999);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(CONT_I_WEIGHT, 200000);
    add_prop(CONT_I_VOLUME,  200000);
    add_prop(CONT_I_MAX_WEIGHT, 280000);
    add_prop(CONT_I_MAX_VOLUME, 280000);
    add_prop(LIVE_I_QUICKNESS, 80);
    set_skill(SS_DEFENCE,      90);
    set_skill(SS_PARRY,        55);
    set_skill(SS_AWARENESS,    90);
    set_skill(SS_CLIMB,        70);
    set_skill(SS_LOC_SENSE,    50);
    set_skill(SS_HUNTING,      60);

    add_item(({"fangs"}),  "They are long and filled with venom.\n");
    add_item(({"scales"}), "They shine like brilliant jewels.\n");
    add_item(({"eyes"}),   "They possess an unworldy power.\n");
}

public void
cr_configure()
{
    add_attack(70, 60, W_IMPALE, 100, A_BITE);

    add_hitloc( ({ 50, 50, 50 }), 25, "body",  H_BODY);
    add_hitloc( ({ 70, 70, 70 }), 75, "head",  H_HEAD);
}

public string
cr_attack_desc(int aid)
{
    switch (aid) {
      case A_BITE:return "deadly fangs";
    }
}

public void
remove_object()
{
    tell_room(ETO, QCTNAME(TO) + " fades away with a eerie green " +
              "glow.\n", TO);
    ::remove_object();
}

special_attack(object enemy)
{
   object me;
   mixed *hitresult;
   string how;

   me = this_object();
   if (random(5)) return 0;

   hitresult = enemy->hit_me(60+random(40), W_BLUDGEON, me, -1);
   how = " fails to grasp";
   if (hitresult[0] >  0) how = " grasps";
   if (hitresult[0] > 25) how = " grips";
   if (hitresult[0] > 40) how = " crushes";

   me->catch_msg("You encircle your victim with your coils.\n");
   enemy->catch_msg(QCTNAME(me) + how + " you in " +
          me->query_possessive() + " serpentine coils.\n");
   tell_watcher(QCTNAME(me) + how + " " +QTNAME(enemy) +
        " in " + me->query_possessive() +  " serpentine coils.\n", enemy);

   if (enemy->query_hp() <= 0) enemy->do_die(me);
   return 1;
}
