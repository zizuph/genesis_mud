//-*-C++-*-
// Female Infidel
// creator(s): Ilyian, October 1995
// purpose:
// note: Modelled after Boriska's random npcs
// updates:  Lilith June 2004 - added archers
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/monster.c";
inherit "/d/Avenir/inherit/helper";

#include "../infidel.h"
#include <ss_types.h>

string *g_names = ({ "solia", "matri", "aliso", "entrea",
    "antasish", "marika", "lausine", "praesi",
    "lesina", "terrias", "rilia", "nasai" });
string *given_names = g_names;

int do_this_check();
void do_slay(object victim);
void do_greet(object who);

string
get_name()
{
    string str;

    if(!sizeof(given_names))
       given_names = g_names;

    str = ONEOF(given_names);

    given_names -= ({ str });
    return str;
}

void create_monster()
{

  string *randadjl = ({"tall", "blue-eyed",
		       "short", "long-haired", "slender",
		       "long-legged", "blonde-haired",
		       "wide-eyed"});

  string *randadjs = ({"gentle","anxious","good-looking",
		       "happy","sad","frightened","graceful"});
  
  string *title1 = ({ "Trusted", "Strong", "Wise",
      "Glorious", "Graceful" });
  string *title2 = ({ "Warrior", "Handmaiden",
      "Ally" });

  if(!IS_CLONE)
    return;

  ::create_monster();

  set_name(MASTER->get_name());
  set_living_name(query_name());

  add_name("infidel");
  add_name("avenir_infidel_id"); 
  set_race_name("human");
  set_gender(G_FEMALE);
  set_adj(randadjl[random(sizeof(randadjl))]);
  add_adj(randadjs[random(sizeof(randadjs))]);

  set_title("the " + ONEOF(title1) + " " + ONEOF(title2)
     + " of the Infidels");

  set_long("This slender woman is graceful and good-"
           +"looking, with wide blue eyes and a "
           +"gentle bearing.\n");
  set_stats(({ 40+random(20), 50+random(20), 90+random(30),
	       90+random(20), 80+random(10), 70+random(30) }));

  set_aggressive(1);  // Using my aggressive formula

  remove_leftover("scalp");
  add_leftover(OBJ +"scalp", "scalp", 1, 0, 0, 1);

  set_skill(SS_WEP_KNIFE, 50 + random (30));
  set_skill(SS_DEFENCE, 40 + random (30));
  set_skill(SS_AWARENESS, 50);
  set_skill(SS_BLIND_COMBAT, 40);
  set_skill(SS_UNARM_COMBAT, 50);
  set_skill(SS_WEP_MISSILE, 60);


  set_act_time(5);
  add_act("say I wish we could leave this place.");
  add_act("say I left my husband and my son behind.");
  add_act("whisper infidel Who is that?");
  add_act("Yes, I feel the same.");
  add_act("smile warm infidel");
  add_act("peer at hobbit");
  add_act("peer at goblin");
  add_act("peer at elf");
  add_act("say Some days I wish I'd never met Nochipa.");
  add_act("say If we worship Alphum improperly, why has he not "+
      "abandoned us?");
  add_act("say The Inquisitors managed to borrow a dej-minha "+
      "from the Hegemon. What are we going to do?");
  add_act(({"say I heard that she is a Mistress of the Black Flower.",
            "shudder"}));

  set_cact_time(9);
  add_cact("emote clutches her arm in pain."); 
  add_cact("shout Somebody help me!");
  add_cact("shout Please! I don't want to die!");
  add_cact("shout They are trying to kill me!");

  seteuid(getuid());
  set_helper_friends( ({}) );
  set_helper_actions(({"shout Help! They are trying to kill me!",
		       "scream",
		       "say I'll kill you myself!"}));

  MAKE_INFIDEL;
}

void
arm_me()
{
  clone_object(OBJ+"yark_bow")->move(TO);
  clone_object(OBJ+"bronze_arrow")->move(TO);
  clone_object(OBJ+"f_armour")->move(TO);
  clone_object(OBJ+"f_boots")->move(TO);
 
  clone_object("/std/bowstring")->move(TO);

  if(!random(3))
    clone_object(OBJ + "ring")->move(TO);
  else 
    clone_object(OBJ + "bracelet")->move(TO);

  command("wear all");
  command("wimpy terribly hurt");

}

/* Should I attack this guy? */
int
do_this_check()
{
  if(query_attack())
    { return 0; }  // always concentrate on fighting

  if (TP->query_npc())
    { return 0; } // don't kill each other

  if (TP->query_prop("_live_i_killed_infidel_guard"))
    {        
      set_alarm(itof(random(8)), 0.0,
		&command("shout The murderer is here!"));
      return 1; 
    }
  
  if (TP->query_prop("_live_i_attacked_infidel_guard"))
    { 
      set_alarm(itof(random(8)), 0.0,
		&command("shout I found the intruder!"));
      return 1; 
    }

  set_alarm(itof(random(5) + 3), 0.0, &do_greet(TP));
  return 0;
}

/*
 * Function name: init_attack
 * Description:   Called from init_living() i monster.c
 */
public void
init_attack()
{
  int i = check_call(monster_aggressive);
  if ((!i) || (this_player()->query_npc()))
    return;
  if (do_this_check() &&
      (monster_attack_chance == 0) || (random(100) < monster_attack_chance))
    set_alarm(itof(random(4)), 0.0, &do_slay(TP));
}

/*
 * Ok, I'll attack, but only if I'm not busy killing
 * someone else right now.
 */
void
do_slay(object victim)
{
  if(query_attack())
    { return; }  // always concentrate on fighting

  command("kill "+victim->query_real_name());
}

/*
 * Greet strangers
 */
void
do_greet(object who)
{
  string *ways = ({"nerv","corag","caut","dubiou","inquir",
                   "thought","warm","curious"});
  string *emots = ({"smile","peer","eyebrow","glare","nod"});
  string *says = ({"Is there something I can help you with?",
                   "You really shouln't have come here. It is "
		     +"dangerous.", "There is nothing for you "
		       +"here. You had better go."});  
  if(random(2))
    command(emots[random(sizeof(emots))]+" "
	    +ways[random(sizeof(ways))]+" "+TP->query_real_name());
  if(random(3))
    command("say "+says[random(sizeof(says))]);
  return;
}

void
attacked_by(object who)
{
  who->add_prop("_live_i_attacked_infidel_guard",1);
  if(random(2) && !query_attack())  
    set_alarm(3.0, 0.0, &command("shout Help! They "
				 +"are trying to kill me!"));
  command("wield bow");
  ::attacked_by(who);
}

void
do_die(object killer)
{
  command("emote slumps to the floor in a lifeless heap.");
  killer->add_prop("_live_i_killed_infidel_guard",1);
  ::do_die(killer);
}

string
race_sound()
{
    return ONEOF(({"cries","sings","says","whispers","lilts"}));
}

public void
add_introduced(string s_who)
{
    object o_who = find_player(s_who);
 
    if(o_who && interactive(o_who)
       && !query_attack() && CAN_SEE(TO, o_who)
       && CAN_SEE_IN_ROOM(TO) 
       && !o_who->query_prop("_live_i_attacked_infidel_guard")
       && !o_who->query_met(this_object()))
        set_alarm(itof(random(5) + 1), 0.0, "command",
                  "introduce myself to " + s_who);
}


public int
special_attack(object enemy)
{
    string how;
    int damage, swing_type;
    mixed hitres;
    object me;
  
    command("shoot "+ enemy->query_real_name());
    return 0;
}

