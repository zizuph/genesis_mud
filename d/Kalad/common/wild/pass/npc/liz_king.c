/* 
 * /d/Kalad/common/wild/pass/npc/liz_king.c
 * Purpose    : The lizard man king
 * Located    : /d/Kalad/common/wild/pass/desert/salt/l11
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/lib/unique";
#include "/d/Kalad/defs.h"

void
create_monster()
{
   int i;
   set_name("lizard man king");
   add_name("man");
   add_name("king");
   set_race_name("lizard man");
   set_adj("bestial");
   set_short("bestial lizard man king");
   set_pshort("bestial lizard man kings");
   set_long("A gargantuan specimen of the lizard man species. This incredibly "+
      "muscular, and devious creature looks like a nightmarish cross "+
      "between a man and an alligator. The result is a being that possesses "+
      "the intelligence of humankind and the utter savagery and bestial "+
      "ferocity of the reptiles.\n");
   set_gender(G_NEUTER);
   for(i = 0; i < 3; i++)
      set_base_stat(i,150 + random(25));
   set_base_stat(3, 70);
   set_base_stat(4, 70);
   set_base_stat(5, 100);
   set_all_hitloc_unarmed(50);
   set_alignment(-250);
   set_knight_prestige(750);
   set_skill(SS_WEP_POLEARM,100);
   set_skill(SS_BLIND_COMBAT,50);
   set_skill(SS_DEFENCE,100);
   set_skill(SS_PARRY,100);
   add_prop(LIVE_I_QUICKNESS,200);
   set_skill(SS_AWARENESS,75);
   set_act_time(6);
   add_act("emote hisses.");
   add_act("grin men");
   add_act("snarl all");
   add_act("emote snaps up a passing fly.");
   add_act("emote licks the tip of it's trident.");
   add_act("peer");
   add_act("scratch chin");
   add_act("spit all");
   add_act("emote grins maliciously.");
   add_act("emote places a long thin feather among its scales.");
   set_cact_time(3);
   add_cact("snarl all");
   add_cact("growl all");
   add_cact("scream");
   add_cact("emote grins savagely.");
   add_cact("cackle");
   add_cact("startle all");
   add_cact("kick all");
   add_cact("spit all");
   add_cact("emote places a long thin feather among its scales.");
   add_prop(LIVE_I_SEE_DARK,5);
/*
   trig_new("%w 'drops' %s","react_drop");
   trig_new("%w 'wears' %s","react_wear");
   trig_new("%w 'wields' %s","react_wear");
   trig_new("%w 'gives' %s","react_wear");
*/
}

void
my_stuff()
{
   object it;
   seteuid(getuid(TO));
   it = clone_unique("/d/Kalad/common/wild/pass/wep/lmk_trident", 5, 
            "/d/Kalad/common/wild/pass/wep/lmk_spear");
   it -> move(TO);
   command("wield all");
   it = clone_object("/d/Kalad/common/wild/pass/obj/lmk_feather");
   it -> move(TO);
   MONEY_MAKE_GC(random(5))->move(TO,1);
}

int
react_drop(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_drop",who);
      return 1;
   }
}

void
return_drop(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("get all");
      command("grin greed");
   }
}
int
react_wear(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_wear",who);
      return 1;
   }
}
void
return_wear(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("laugh " + (obj->query_real_name()));
      command("emote hisses something incomprehensible.");
      command("kill " + (obj->query_real_name()));
   }
}

int
special_attack(object enemy)
{
    object arm;
    mixed hr;
    string str;
    if(random(10))
        return 0;
    hr = enemy->hit_me(random(100) + 500, W_BLUDGEON, TO, -1);
    switch(hr[0])
    {
        case 0:
            str = "no effect";
        break;
        case 1..10:
            str = "little effect";
        break;
        case 11..30:
            str = "a solid thud";
        break;
        case 31..50:
            str = "a loud crack";
        break;
        case 51..70:
            str = "a bone crushing sound";
        break;
        default: 
            str = "a massive life-crushing blow";
    }
    tell_object(enemy,"The "+short()+" mauls its massive shoulder "+
    "into your body with "+str+"!\n");
    tell_watcher("The "+short()+" mauls its massive shoulder into "+
    QTNAME(enemy)+"'s body with "+str+"!\n",enemy);
    if(objectp(enemy->query_armour(A_TORSO)))
    {
        arm = enemy->query_armour(A_TORSO);
        arm->set_condition( arm->query_condition() + 1 );
    }
    if(enemy->query_hp() <= 0)
        enemy->do_die(TO);
    return 1;
}

