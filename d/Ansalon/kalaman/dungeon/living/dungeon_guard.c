/*
 * Dungeon Guards
 * 
 * Basically a Kalaman guard but changed for the Dungeon
 *
 * 20110927 Lunatari : looked it over after Navarre's review.
 */
#include "local.h"

inherit (KNPC + "guard_base");

#define WEP3 KOBJ + "weapon/halberd"
#define WEP2 KOBJ + "weapon/claymore"
#define ARM1 KOBJ + "armour/platemail"
#define ARM2 KOBJ + "armour/winged_helmet"
#define ARM3 KOBJ + "armour/gauntlets"
#define ARM4 KOBJ + "armour/g_robe"
#define ARM5 KOBJ + "armour/leggings"

string *gAdj1 = ({"tired","worn-down","wary","casual","smelly",
                  "careless","muttering","black-bearded","old",
                  "scarred","skinny","fat","one-eyed","red-bearded"});

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

string query_guard_desc();
string query_guard_act();

int gSleeping = 0;

#define ACT_SLEEP ({ "emote snores loudly.", \
  "emote turns in his sleep.", \
  "emote sighs deeply in his sleep" })

#define ACT_AWAKE ({ "emote looks around confidently.", \
  "say Lord Calof might be a wise leader but I do not see the logic in guarding these rats, we should just kill them.", \
  "say Oh if I could just be stationed outside again!" })

void
create_guard()
{
    set_name("guard");
    set_adj(ONE_OF(gAdj1));
    add_adj("dungeon");
    set_short(implode(query_adjs()," ") + " guard");
    set_race_name("human");
    set_gender(G_MALE);

    set_long(query_guard_desc);

    set_stats(({150 + random(20),
                160 + random(25),
                180 + random(25),
                70, 70, 130 }));

    set_alignment(600);
    set_knight_prestige(-3);
    
    add_prop(CONT_I_HEIGHT, 180 + random(40));
    add_prop(CONT_I_WEIGHT,70000 + random(10000));
    set_skill(SS_WEP_POLEARM, 75 + random(25));
    set_skill(SS_WEP_SWORD, 75 + random(25));
    set_skill(SS_PARRY, 50 + random(40));
    set_skill(SS_DEFENCE, 70 + random(15));
    set_skill(SS_BLIND_COMBAT, 80 + random(20));
    set_skill(SS_AWARENESS, 80 + random(15));
    add_prop(LIVE_I_NEVERKNOWN, 1);

    set_act_time(5);
    add_act(query_guard_act);
    
    equip(({
        ({ WEP2, WEP3 })[random(2)],
            ARM1, ARM2, ARM3, ARM4, ARM5 }));
}

void
init_living()
{
  ::init_living();

  if (!random(5)) 
  {
    command("nod " + TP->query_name());
  }
}

string
query_guard_act()
{
  if (gSleeping)
  {
    return ONE_OF(ACT_SLEEP);
  }

  return ONE_OF(ACT_AWAKE);
}

void
surrender_attack(object player)
{
  command("shout Hey there " + player->short() + "! You should "+
   "not be in here! Surrender or die!");
  clone_object(SURRENDER_OBJECT)->move(TP);
  command("kill " + player->query_name());
}

int
query_dungeon_guard()
{
  return 1;
}

int
set_sleeping()
{
  gSleeping = 1;
  TO->command("unwield all");
  tell_room(ENV(TO), QCTNAME(TO) + " lays down on a bed and sleeps.\n", TO);
  TO->add_adj("sleeping");
  TO->set_short("sleeping " + TO->short());
}

int
set_awake()
{
  gSleeping = 0;
  TO->remove_adj("sleeping");
  TO->set_short(implode(query_adjs()," ") + " guard");
  tell_room(ENV(TO), QCTNAME(TO) + " wakes up and stands tall.\n", TO);
  TO->command("wield all");
}

int
query_sleeping()
{
  return gSleeping;
}

string
query_guard_desc()
{
    string text;

    text = "This " + TO->short() + " has been assigned "+ 
           "by the ruler of Kalaman, Lord Calof to the demeaning " +
           "dungeon duty, most likely as a punishment for not " +
           "performing too great with the normal duties as a " +
           "wall or elite guard.";

    if (gSleeping) 
    {
      text += TO->query_pronoun() + " is sleeping deeply.";
    }

    return text + "\n";
}
