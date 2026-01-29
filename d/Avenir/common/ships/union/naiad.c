/* The Naiad that is the captain of the Union Ship
 *    Cirion, April 1997
 */
#pragma strict_types

inherit "/d/Avenir/inherit/npc";

#include "/d/Avenir/common/common.h"


void create_monster()
{
    set_name("anylis");
    add_name("captain");
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

    set_alignment(-800); 

    set_all_attack_unarmed(30, 45);
    set_all_hitloc_unarmed(15);

    add_prop(NPC_I_NO_RUN_AWAY,   1);
    add_prop(MAGIC_I_RES_POISON, 75);
    add_prop(MAGIC_I_RES_ACID,  100);
    add_prop(MAGIC_I_RES_COLD,   85);
    add_prop(MAGIC_I_RES_DEATH,  50);
    add_prop(MAGIC_I_RES_EARTH, 100);
    add_prop(MAGIC_I_RES_WATER, 100);
    add_prop(MAGIC_I_RES_FIRE,  -55); // Will this work?
    add_prop(LIVE_I_SEE_INVIS,    2);
    add_prop(LIVE_I_SEE_DARK,    50);
    add_prop(LIVE_I_QUICKNESS,   82);
    add_prop(LIVE_I_NO_CORPSE,    1);
    add_prop(NPC_I_NO_LOOKS,      1);
    add_prop(MAGIC_I_BREATH_WATER, 1);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    seteuid(getuid());
}

void
tell_summoner(object who)
{
    string str;

    str = ENV(TO)->summon_string(who);

    if(!strlen(str) || !present(who, ENV(TO)))
       return;

    command("whisper " + who->query_real_name() + " Cry out the words '"
       + CAP(str) + "' and you will summon me from here.");
}

void
enter_env(object to, object from)
{
    object summoner;

    ::enter_env(to, from);

    if(!(summoner = ENV(TO)->query_summoner()))
        return;

    if(ENV(TO)->query_ship_summoned() == 1)
        set_alarm(2.0, 0.0, &tell_summoner(summoner));
}

void rem_check()
{
  remove_prop("_tmp_attack_checked");
}

int query_not_attack_me(object attacker, int att_id) 
{
  object weapon;
  string what;

  weapon = attacker->query_weapon(att_id);

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


void do_die(object enemy)
{
  seteuid(getuid(TO));

  tell_room(ENV(TO), "The body of "+QTNAME(TO)+" seems to melt "
    +"and turn to water, soaking into the ground.\n");
  ::do_die(enemy);
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
