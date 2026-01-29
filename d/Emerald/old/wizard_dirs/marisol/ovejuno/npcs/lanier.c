/* Coded by Ckrik June 1998
 * Modified by Marisol (08/31/98) to be used in the village of
 * Ovejuno in Emerald.
 */

inherit "/d/Emerald/std/elf";
inherit "/d/Genesis/lib/intro.c";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include <wa_types.h>

/* The combat special parameters.
 * SPA_DELAY = delay between specials
 * counter = the counter used in the special
 */

#define SPA_DELAY 5
static int counter = 3;
#define SPECIAL_FORMULA (200 + random(200))

#define WEP "/d/Emerald/marisol/ovejuno/weapons/silver_sword.c"
#define BARMOUR "/d/Emerald/marisol/ovejuno/weapons/silver_plated.c"
#define HELMET "/d/Emerald/marisol/ovejuno/weapons/silver_helmet.c"
#define LEG "/d/Emerald/marisol/ovejuno/weapons/silver_guards.c"

void
create_elf()
{
    ::create_elf();
    set_name("lanier");
    set_living_name("lanier");
    set_title("Guard of the Telbarion's palace");
    set_adj("aloof");
    set_adj("tall");
    set_race_name("elf");
    set_gender(G_MALE);
    set_appearance_offset(-25);
    set_long("An aloof tall male elf guard. He seems bore of drinking "+
        "his glass of wine here in the pub. You better don't mess up "+
        "with him if you value your health.\n");

    set_stats(({90, 90, 100, 60, 60, 95}));

    add_prop(OBJ_M_HAS_MONEY, 700);

    set_hp(query_max_hp());

    set_skill(SS_DEFENSE, 100);
    set_skill(SS_PARRY, 90);
    set_skill(SS_WEP_SWORD, 95);
    set_skill(SS_AWARENESS, 35);
    set_skill(SS_BLIND_COMBAT, 80);

    set_act_time(50);
    add_act("emote scans the room with an air of indiference.");
    add_act("emote mumbles to himself: I wish I can go back soon to "+
        "Telberin.");  
    add_act("emote asks for another drink to the bartender.");

    set_cact_time(45);
    add_cact("emote prepares himself for combat.");
    add_cact("say You will regret this impertinence stranger.");
    add_cact("say Prepare to die!");

    set_alignment(200);
    add_equipment(({WEP, BARMOUR, HELMET, LEG}));
    add_prop(OBJ_M_HAS_MONEY, 600);
}

                                         
int
special_attack(object enemy)
{
    string damage_lvl;
    mixed damage;
    int num = SPA_DELAY;

    if (++counter >= SPA_DELAY + random(3) &&
      this_object()->query_weapon(-1) != 0)
    {
      counter = 0;

      damage = enemy->hit_me(SPECIAL_FORMULA,
                             W_SLASH, this_object(), -1);

      if (damage[0] > 0)
        damage_lvl = "slightly cuts";
      if (damage[0] > 15)
        damage_lvl = "cuts a small wound on";
      if (damage[0] > 25)
        damage_lvl = "slices a deep wound on";
      if (damage[0] > 50)
        damage_lvl = "inflicts great damage on";
      if (damage[0] > 75)
        damage_lvl = "hacks off a chunk of flesh of";
      if (damage[0] >= 0)
        {
          switch(random(2))
            {
            case 0:
              enemy->catch_msg(QCTNAME(this_object()) + " swings his " +  
                               "sword around and " + damage_lvl +
                               " your " + damage[1] + ".\n");

              tell_watcher(QCTNAME(this_object()) + " swings his " +
                           "sword around and " + damage_lvl +
                           " " + QTNAME(enemy) + "'s " +
                           damage[1] + ".\n", enemy);

              break;
            default:
            enemy->catch_msg(QCTNAME(this_object()) + " suddenly " +
                  "whips up his " +
                  this_object()->query_weapon(-1)[0]->query_short() +
                  " and " + damage_lvl + " your " + damage[1] +
                  ".\n");
            tell_watcher(QCTNAME(this_object()) + " suddenly " +
                         "whips up his " +
                         this_object()->query_weapon(-1)[0]->query_short() +
                         " and " + damage_lvl + " " +
                         QTNAME(enemy) + "'s " + damage[1] +
                           ".\n", enemy);
              break;
            }
        }
      else
        {
           enemy->catch_msg(QCTNAME(this_object()) + " swings his " +
                           this_object()->query_weapon(-1)[0]->query_short() +
                           " and narrowly misses you.\n");
           tell_watcher(QCTNAME(this_object()) + " swings his " +
                       this_object()->query_weapon(-1)[0]->query_short() +    
                       " and narrowly misses " + QTNAME(enemy) + ".\n",
                       enemy);
          this_object()->command("fume");
          this_object()->command("say Lucky dodge, you won't " +
                                 "be so lucky next time.");
        }
      if (enemy->query_hp() <= 0)
        {
          enemy->catch_msg("You yell in agony as " +
                           QTNAME(this_object()) + " slices " +
                           "open your guts.\n");
          tell_watcher(QCTNAME(enemy) + " yells in agony" +
                       " as " + QTNAME(this_object()) + " slices " +
                       "open " + enemy->query_pronoun() + " guts.\n",
                       enemy);
          enemy->do_die(this_object());
        }
      return 1;
    }
  return 0;
}                                                                        
