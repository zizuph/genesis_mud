/* The creature that tries to prevent you from
 * burying the ship captain's bones. She can probably
 * only be defeated using some sort of fire.
 * Update: Lilith, May 1997 removed bit setting for quest failure.
 *    Cirion 100496
 */
#pragma strict_types

inherit "/d/Avenir/inherit/npc";
inherit "/d/Avenir/inherit/quest";

#include "../dead.h"
#include "/d/Avenir/smis/sys/statserv.h"
#include "/d/Avenir/common/port/bury_bones.h"

#include "/d/Genesis/gems/gem.h"

object  arm;
int     started,
        k,
        alarm_id;

void create_monster()
{
    set_name("alinatisa");
    add_name("naiad");
    set_title("the Child of Hizarbin");
    set_race_name("naiad");
    set_short("pale naiad");
    set_adj("pale");
    add_adj("sea");

    set_gender(G_FEMALE);
    set_appearance(98);

    set_long("Her skin is tinged faintly green, and "
       +"her hair is the consistancy of seaweed, but her "
       +"pale face is young and lovely.\nShe regards you "
       +"with sad and intense eyes, pale aquamarine blue.\n"
       +"She looks beautiful.\n");

    set_stats(({ 80, 100, 80, 110, 120, 120}));
    set_exp_factor(150);

    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT,  85);
    set_skill(SS_DEFENCE,       80);
    set_skill(SS_AWARENESS,     75);
    set_skill(SS_LANGUAGE,      80);
    set_skill(SS_SPELLCRAFT,    77);
    set_skill(SS_HERBALISM,      8);

    set_alignment(0); 

    set_all_attack_unarmed(30, 45);
    set_all_hitloc_unarmed(15);

    add_prop(NPC_I_NO_RUN_AWAY,   1);
    add_prop(OBJ_I_RES_POISON, 75);
    add_prop(OBJ_I_RES_ACID,  100);
    add_prop(OBJ_I_RES_COLD,   85);
    add_prop(OBJ_I_RES_DEATH,  50);
    add_prop(OBJ_I_RES_EARTH, 100);
    add_prop(OBJ_I_RES_WATER, 100);
    add_prop(OBJ_I_RES_FIRE,  -55); // Will this work?
    add_prop(LIVE_I_SEE_INVIS,    2);
    add_prop(LIVE_I_SEE_DARK,    50);
    add_prop(LIVE_I_QUICKNESS,   82);
    add_prop(LIVE_I_NO_CORPSE,    1);
    add_prop(NPC_I_NO_LOOKS,      1);
    add_prop(MAGIC_I_BREATH_WATER, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_cact_time(10);
     add_cact("@@health_act@@");

    set_act_time(2);
     add_act("@@ask_bones@@");

    seteuid(getuid());
    arm = clone_object(GEM_OBJ_DIR + "sapphire");
     arm->move(TO);
    arm = clone_object(GEM_OBJ_DIR + "diamond");
     arm->move(TO);
    arm = clone_object(OBJ+"necklace");
     arm->move(TO);
    command("wear all");
}

object find_bones()
{
  object   *oblist;
  int       m;

    if (!objectp(this_object()) || !objectp(environment()))
        return 0;

  oblist = filter(all_inventory(ENV(TO)), interactive);

  if(!sizeof(oblist))
   return 0;

  for(m=0;m<sizeof(oblist);m++)
  {
    if(present(BONES_ID, ({ oblist[m] }) + deep_inventory(oblist[m]) ))
     return oblist[m];
  }

  return 0;
}

void check_die(object who)
{
  if(!query_hp())
   do_die(who);

  attack_object(who);
  attack_object(find_bones());
}

string ask_bones()
{
  object   who = find_bones();

  if(!who)
   return "peer .";

  switch(random(6))
  {
   case 0:
    return "say Return what is mine, "+who->query_name()+".";
    break;
   case 1:
    return "say I know you have them, "+who->query_name()+".";
    break;
   case 2:
    return "say The remains of Braston shall lie with "
          +"me forever.";
    break;
   case 3:
    return "peer expect "+who->query_real_name();
    break;
   case 4:
    return "say Do not keep me waiting "+who->query_name()
         +". My patience is limited.";
    break;
   default:
    command("say I have waited long enough.");
    command("say Now you will die for your foolishness.");
    special_attack(who);
    return "";
    break;
   }
}

int query_knight_prestige() 
{
  return(1300); 
}

string do_heal()
{
  heal_hp(random(1000) + 50);
  return "emote seems to be surrounded by a faint greenish glow.";
}

void rem_check()
{
  remove_prop("_tmp_attack_checked");
}

int query_not_attack_me(object attacker, int att_id) 
{
  object weapon;
  string what;

  if (att_id != -1) // some special attacks use -1
  {
    weapon = attacker->query_weapon(att_id);
  }

  add_prop("_tmp_attack_checked", 1);
  set_alarm(0.1, 0.0, rem_check);

  if(weapon->query_prop(OBJ_I_IS_MAGIC_WEAPON)) 
  {
    if(member_array("water", weapon->query_prop(MAGIC_AM_MAGIC)) != -1)
    {
      tell_room(ENV(TO), QCTNAME(attacker)+"'s "+QSHORT(weapon)+
           " seems to be absorbed right into the body of " 
          + QCTNAME(TO)+"!\n",
           attacker);
      attacker->catch_msg("Your " + weapon->short() +
         " is absorbed into the body of "+ QTNAME(TO)+"!\n");
      weapon->remove_object();
      return 1;
    }

    if(member_array("fire", weapon->query_prop(MAGIC_AM_MAGIC)) != -1)
    {
      if(!random(3))
       command("emote screams in agony as "+LANG_THESHORT(weapon)
           +" burns her flesh.");
      return 0;
    }
   
    if(!random(3))
      return 0;
  }

  if(weapon)
   {
     tell_room(ENV(TO), QCTNAME(attacker)+"'s "+QSHORT(weapon)+
           " passes right through " + QCTNAME(TO)+".\n",
           attacker);
     attacker->catch_msg("Your " + weapon->short() +
         " passes right through "+ QTNAME(TO)+".\n");
     return 1;
   }

  switch(att_id) 
   {
    case TS_LWEAPON:
      what = "left arm";
      break;
    case TS_RWEAPON:
      what = "right arm";
      break;
    case TS_RFOOT:
      what = "right foot";
      break;
    case TS_LFOOT:
      what = "left foot";
      break;
    default:
      what = "something";  // Hmmm....
      break;
    }

  attacker->catch_msg("Your "+what+" seems to pass right through "
       +QTNAME(TO)+"'s watery body.\n");
  say(QCTNAME(attacker) +
      "'s "+what+" seems to pass right through "+QTNAME(TO)
     +"'s watery body.\n");
  return 1;
}

/* This should stop most special attacks */
public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
  if(dt != MAGIC_DT && !query_prop("_tmp_attack_checked"))
   wcpen = 0;

  return ::hit_me(wcpen, dt, attacker, attack_id);
}

int special_attack(object enemy)
{
  object   who = find_bones();

  if(query_attack() != who)
  {
   who->catch_msg(QCTNAME(TO)+" glares at you with rage.\n");
   say(QCTNAME(TO)+" glares at "+QTNAME(who)+" with rage.\n", ({ TO, who}));
   attack_object(who);
  }

  if(random(4))
   return 0;

  switch(random(2))
  {
    case 0:
     enemy->catch_msg(QCTNAME(TO)+" looks straight into "
       +"your eyes.\n");
     say(QCTNAME(TO)+" looks straight into the eyes of "
       +QTNAME(enemy)+".\n", enemy);
     if(enemy->query_magic_res(MAGIC_I_RES_DEATH) > random(10))
      enemy->catch_msg("You feel that you are resisting some "
          +"deathly magic.\n");
     else
     {
      enemy->catch_msg("You feel the life draining from you.\n");
      enemy->add_fatigue(-(random(80)));
     }
     break;

    case 1:
     command("emote holds her hand in a tight fist.");
     if(enemy->query_magic_res(MAGIC_I_RES_WATER) > random(10))
       enemy->catch_msg("You feel you throat constricting, "
           +"but some other force saves you.\n");
     else
     {
       enemy->catch_msg("You feel your throat filling with "
         +"water!\n");
       say(QCTNAME(enemy)+" clutches "+POSSESS(enemy)
         +" throat.\n", enemy);
       enemy->command("$choke");
       enemy->heal_hp(-(random(400) + 100));
       if(!enemy->query_hp()) enemy->do_die(TO);
     }
     break;

    default: return 0; break;
    }

  return 1;
}

void punish(object who)
{
  command("give gems to "+who->query_real_name());
  command("emote seems to melt into a mass of water, which "
        +"flows away down the hill.");

  who->catch_msg("You feel a profound sense of loss and "
        +"failure.\n");

  setuid();
  seteuid(getuid(TO));
  LOG_THIS(who->query_name()+" gave the bones to Alinatisa "
          +"instead of burying them.");
  STATSERV_LOG_EVENT("necronisi", "Gave bones to Naiad");
  ENV(TO)->reset_room();
  set_alarm(0.0, 0.0, remove_object);
}

void enter_inv(object to, object from)
{
  object what = to;

  ::enter_inv(to, from);

  if(!living(from))
   return;

  if(what->id(RING_ID))
  {
    set_alarm(1.0, 0.0, &command("say I do not want this trifle! "
               +"Give me his remains!"));
    set_alarm(2.0, 0.0, &command("drop "+RING_ID));
    return;
  }

  if(what->id(BONES_ID))
  {
    set_alarm(1.0, 0.0, &command("laugh joy"));
    set_alarm(2.0, 0.0, &command("say Now he will lie with "
             +"me for all eternity!"));
    set_alarm(3.0, 0.0, &punish(from));
    return;
  }

  if(what->query_prop(OBJ_I_HAS_FIRE))
  {
    set_alarm(0.05, 0.0, &command("emote screams in pain from "
            +"the fire of "+LANG_THESHORT(what)+"!"));
    heal_hp(-200);
    set_alarm(0.1, 0.0, &check_die(from));
    what->remove_object();
    return;
  }

  if(member_array("fire", what->query_prop(MAGIC_AM_MAGIC)) != -1)
  {
    set_alarm(1.0, 0.0, &command("emote howls in agony as her "
              +"pale skin burns!"));
    heal_hp(-400);
    set_alarm(1.1, 0.0, &check_die(from));
    set_alarm(1.3, 0.0, &command("drop "+what->query_name()));
    return;
  }

  if(what->id("paralyze") || what->id("poison"))
    what->remove_object();

  set_alarm(1.0, 0.0, &command("drop "+what->query_name()));
  return;
}

void do_die(object enemy)
{
  seteuid(getuid(TO));
  LOG_THIS(enemy->query_name()+" killed the Naiad.");
  STATSERV_LOG_EVENT("necronisi", "Killed Naiad");
  tell_room(ENV(TO), "The body of "+QTNAME(TO)+" seems to melt "
    +"and turn to water, soaking into the ground.\n");
  ::do_die(enemy);
}

int notify_you_killed_me(object killed)
{
  seteuid(getuid(TO));
  LOG_THIS(killed->query_name()+" was killed by the naiad.");
  set_alarm(1.0, 0.0, &command("get all from corpse"));
}

void start_acts()
{
  object who;

  k++;

  switch(k)
  {
    case 0: case 1:
     say("The moisture in the earth starts to gather and "
        +"begins to form a strange shape.\n");
     break;
    case 2:
     say("The water coalesces into "+LANG_ADDART(QSHORT(TO))+".\n");
     break;
    case 3:
     if(!(who = find_bones())) break;
     command("say "+who->query_name()+"! Those remains belong "
         +"to me!");
     break;
    case 4:
     if(!(who = find_bones())) break;
     command("say Return them to me at once, for I have taken "
         +"him to the sea. There he will remain!");
     break;
    case 5:
     if(!(who = find_bones())) break;
     command("glare . "+who->query_real_name());
     break;
   default:
     remove_alarm(alarm_id);
     k = 0;
     break;
   }
}

void start_up()
{
  if(started) return;
  started = 1;

  alarm_id = set_alarm(1.0, 3.0, start_acts);
}

void init_living()
{
  ::init_living();
  
  add_action("try_burn", "burn");
  add_action("try_burn", "swing");
  add_action("try_burn", "thrust");
}

int try_burn(string str)
{
  object    liv,
            ob;

  if(!strlen(str)) return 0;

  NF(CAP(QVB)+" what?\n");
  if((!parse_command(str, ENV(TP), "%l [with] %o", liv, ob) &&
     !parse_command(str, ENV(TP), "[the] / [a] %o [at] / [to] [the] %l", ob, liv))
     && liv != TO || !present(ob, TP))
    return 0;
  
  NF("That seems to have no effect on her.\n");
  if(!ob->query_prop(OBJ_I_HAS_FIRE) &&
     member_array("fire", ob->query_prop(MAGIC_AM_MAGIC)) == -1)
    return 0;

  NF("You are too tired to try that.\n");
  if(TP->query_fatigue() < 7)
    return 0;

  set_alarm(0.01, 0.0, &check_die(TP));

  if(!query_attack())
    attack_object(TP);

  if(random(TP->query_stat(SS_DEX)) < random(query_stat(SS_DEX)))
  {
    TP->catch_msg("You try to burn "+QTNAME(TO)+" with "
         +LANG_THESHORT(ob)+", but she dodges you.\nYou "
         +"stumble slightly.\n");
    say(QCTNAME(TP)+" tries to burn "+QTNAME(TO)+" with "
         +LANG_ASHORT(ob)+", but she dodges "+TP->query_objective()
         +".\n");
    TP->add_attack_delay(random(10));
    TP->add_fatigue(-7 - random(7));
    return 1;
   }

  TP->catch_msg("You swing "+LANG_THESHORT(ob)+" at "
      +QTNAME(TO)+", burning her badly!\n");
  say(QCTNAME(TP)+" swings "+LANG_THESHORT(ob)+" at "
      +QTNAME(TO)+", burning her badly!\n");
  TP->add_fatigue(7);
  command("emote screams in anguish as her flesh sizzles and burns.");
  heal_hp(-(100 + random(200)));
  return 1;
}
