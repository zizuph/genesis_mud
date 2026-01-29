/* Garg for the newbie caverns.
 *  Cirion 050296
 */

inherit "/std/monster";
#include "../outpath.h"
#include <money.h>

void create_monster()
{
   string adj = ({ "wretched", "degenerate", "savage",
             "hostile", "aggressive", "mean", "smelly",
             "vile", "sickly", "nasty", "hopeless",
             "unhappy" })[random(12)];

   set_name("quarl");
   set_race_name("quarl");
   set_adj(adj);
   set_short(adj + " quarl");
   set_pname("quarlle");
   set_pshort(adj + " quarlle");

   set_long("This wretched creature may have once been human, "
     +"but the decades spent living like a savage have gnarled "
     +"its skin and made it hostile and aggressive.\n"
     +"He looks hideous.\n");

   set_stats(({ 30 + random(20),
                20 + random(20),
                30 + random(20),
                10 + random(20),
                10 + random(20),
                30 + random(20) }));

   set_gender(G_MALE);
   add_prop(NPC_I_NO_LOOKS, 1);
   add_prop(LIVE_I_NEVERKNOWN, 1);

   set_skill(SS_WEP_KNIFE, 10 + random(30));
   set_skill(SS_WEP_CLUB, 10 + random(30));
   set_skill(SS_WEP_SWORD, 10 + random(30));
   set_skill(SS_WEP_AXE, 10 + random(30));

   set_skill(SS_PARRY, 10 + random(30));
   set_skill(SS_AWARENESS,     15);
   set_skill(SS_DEFENCE, 10 + random(30));
   set_skill(SS_UNARM_COMBAT, 10 + random(30));
   set_skill(SS_SWIM,          30);
   set_skill(SS_CLIMB,         61);
   set_skill(SS_LOC_SENSE,     80);
   set_skill(SS_LOC_SENSE,     54);

   set_alignment( - random(30) );

   set_act_time(15);
    add_act("emote mutters to himself.");
    add_act("poke quarl in eye");
    add_act("kick second quarl");
    add_act("bounce .");
    add_act("jump angr quarl");
    add_act("cry");

  set_cact_time(3);
    add_cact("scream");
    add_cact("shout Die now! Now!");
    add_cact("spit enemy");
    add_cact("snarl enemy");
    add_cact("poke enemy eye");

}

void arm_me()
{
  string   wep;

  seteuid(getuid(TO));

  MONEY_MAKE_SC(random(20) + 1)->move(TO);

  switch(random(4))
  {
    case 0: wep = "s_sword"; break;
    case 1: wep = "s_knife"; break;
    case 2: wep = "s_axe"; break;
    default: wep = "s_club"; break;
  }

  clone_object(OBJ+wep)->move(TO, 1);
  if(!random(3))
     clone_object(OBJ+"s_knife")->move(TO, 1);


  command("wear all");
  command("wield all");

}

void aggro(object who)
{
  if(query_attack() || !present(TP, ENV(TO)) || random(8))
   return;

  switch(random(4))
  {
    case 0:
      command("say Kill you "+TP->query_race_name()+"!");
      break;
    case 1:
      command("shout Food!");
      break;
    case 2:
      command("emote screams in rage!");
      break;
    default:
      command("say Come! I rip you apart, "+TP->query_race_name()+"!");
      break;
   }

  command("kill "+TP->query_real_name());
}  

void init_living()
{
  ::init_living();

  if(CAN_SEE(TO, TP) && CAN_SEE_IN_ROOM(TO) && interactive(TP) )
   set_alarm(itof(random(10) + 1), 0.0, &aggro(TP));
}
