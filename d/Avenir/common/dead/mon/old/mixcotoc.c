

// file name: mixcotoc
// creator(s): Ilyian (16 October, 1995)
// last update:
// purpose: Incubbus that is the gatekeeper to the Sanctuary
//          of Cahor on the bottom level of the crypts. He
//          is unkillable.
// note:
// bug(s):
// to-do:

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/action";
inherit "/std/act/asking";
inherit "/d/Avenir/inherit/quest";

#include "../dead.h"

/* Function prototypes */
string query_gate_quest();
void open_gate();
void close_gate();
void give_gate_quest(object player);
void give_quest_actions();
void test_gate_quest(object player);
void reward_gate_quest(object player);

int alarm_id, quest_act;

void
arm_me()
{
   object   key;

   seteuid(getuid());
   key = clone_object(OBJ+"gate_key");
     key->move(TO);
     key->add_prop(OBJ_I_NO_STEAL, 1);
}

void
create_creature()
{
  set_name(({"mixcotoc","creature","humanoid","efreet"}));
  set_race_name("efreet");
  set_adj(({"massive","black-winged"}));
  set_short("massive black-winged efreet");
  set_title("the Guardian of Cahor");
  set_gender(G_NEUTER);

  set_long("This creature is truly enormous, dwarfing you "
          +"beneath its great height. Wide black wings "
          +"sprout from its back, ending in razor sharp "
          +"talons. Its long arms end in malformed hands, "
          +"from which long claws protrude.\n");

  set_alignment(0);

  set_stats(({200,200,200,200,200,200}));
  set_hp(query_max_hp());
 
  set_skill(SS_AWARENESS, 95);
  set_skill(SS_DEFENCE, 95);

  set_attack_unarmed(0,60,60,W_SLASH,50,"right claw");
  set_attack_unarmed(1,60,60,W_SLASH,50,"left claw");

  set_hitloc_unarmed(0, 70 ,25,"head");
  set_hitloc_unarmed(1, 70, 50,"body");
  set_hitloc_unarmed(2, 70, 25,"legs");

  add_prop(LIVE_I_NO_CORPSE, 1);
  add_prop(LIVE_I_SEE_DARK, 90);
  add_prop(LIVE_I_NEVERKNOWN, 1);
  add_prop(LIVE_I_QUICKNESS, 100);
  add_prop(CONT_I_HEIGHT, 700);
  add_prop(CONT_I_WEIGHT, 100000);
  add_prop(NPC_I_NO_RUN_AWAY,1);
  remove_prop(NPC_M_NO_ACCEPT_GIVE);

  set_cact_time(10);
   add_cact("say Fool. I am Immortal.");
   add_cact("say Flee while you still have a chance.");
   add_cact("emote opens its arms wide, as if to embrace you.");

  set_act_time(20);
   add_act("ponder");
   add_act("peer strang human");
   add_act("peer strang elf");
   
  add_ask(({"cahor", "about cahor", "Cahor", "about Cahor"}),
      "say If you do not know of the Mistress of Deception, "
     +"then you have no business being here.",1);
  add_ask(({"nochipa","Nochipa","about nochipa"}),"say Nochipa "
     +"is a heretic priestess of those miserable Infidels.",1);
  add_ask(({"infidel","infidels","hideout"}),"say You will have "
     +"to find the hideout on your own.",1);
  add_ask(({"door","open door","to open door","gate","open gate",
            "pass","to pass","pass gate","south","about the gate",
            "to open gate","task"}),VBFC_ME("query_gate_quest"));

  trig_new ("%s 'introduces' %s", "intro_me");

}

int intro_me (string s1, string s2)
{
  string *foo;
  object who;

  if (sizeof (foo = explode (s2, " as:\n")) != 2)
    return 0;
  foo = explode (foo[1], " ");

  if (!(who = find_player(lower_case(foo[0]))))
    who = find_player(lower_case(foo[1]));

  if (!who)
    return 0;

  if (who->query_met(this_object()))
    return 1;

  foo[0] = (random(5) ? "say So?" : "introduce myself");
  set_alarm(2.0, 0.0, &command(foo[0]));

  return 1;

}

heal_hp(int hp)
{
    // He is unkillable...
    return;
}

do_die(object killer)
{
   command("grin "+killer->query_real_name());
   set_hp(query_max_hp());
   command("say I said I was Immortal, Fool!");
}

int check_pass()
{
  if(TP->test_bit("Avenir", Q_GROUP,GATEBIT))
      return 0;
  else
    {
      close_gate();
      command("snarl "+TP->query_real_name());
      return 0;
    }
}

init_living()
{
   add_action("check_pass","south");
   add_action("check_pass","s");
   add_action("check_pass","enter gate");
   add_action("check_pass","pass gate");
   ::init_living();
}



void open_gate()
{
    set_alarm(2.0, 0.0, &command("unlock gate with key"));
    set_alarm(4.0, 0.0, &command("open gate"));
    set_alarm(16.0, 0.0, close_gate);
    return;
}


void close_gate()
{
    command("close gate");
    command("lock gate with key");
    return;
}

string query_gate_quest()
{
  if (TP->test_bit("Avenir", Q_GROUP,GATEBIT))
    {
     command("bow deep "+TP->query_name());
     open_gate();
     return "";
    }
  if(TP->query_prop("_live_i_got_avenir_gate_quest"))
    {
     command("say I have already told you what you need to do.");
     command("say Now Begone!");
     return "";
    }
  else
    {
     give_gate_quest(TP);
     return "";
    }
}

void give_gate_quest(object player)
{
   if(query_attack() || sizeof(get_alarm(alarm_id)))
        return;
   else
     {
       player->add_prop("_live_i_got_avenir_gate_quest",1);
       alarm_id = set_alarm(1.0, 2.0, give_quest_actions);
       return;
     }
}

void give_quest_actions()
{
    switch(quest_act++)
        {
          case 0: command("emote narrows its eyes intently.");
                  break;       
          case 1: command("say Hmmm... waht to get past, eh?");
                  break;
          case 2: command("ponder");
                  break;
          case 3: command("say Cahor does not like the weak ... "
                         +"you'll have to prove yourself first.");
                  break;
          case 4: command("say Bring me the head of that bitch "
                         +"Nochipa on a silver platter.");
                  break;
          default: 
            {
               remove_alarm(alarm_id);
               alarm_id = 0;
               quest_act = 0;
            }
         }
     return;
}     

public void enter_inv(object obj, object from)
{
  ::enter_inv(obj, from);
  if(!interactive(from))
        return;

  if(obj->id("silver platter") || obj->id("silver plate"))
  {
    if(!present("_head_of_nochipa",obj) ) 
     {
        set_alarm(2.0, 0.0, &command("say So where's her head?"));
        set_alarm(4.0, 0.0, &command("drop "+obj->query_name()));
        return;
     }
     set_alarm(2.0, 0.0, &test_gate_quest(from));
     return;
  }

  if(obj->query_prop("_is_head_of_nochipa"))
     {
        set_alarm(2.0, 0.0, &command("snarl"));
        set_alarm(3.0, 0.0, &command("say I said "
               +"to bring it on a silver platter!"));
        set_alarm(5.0, 0.0, &command("drop "+obj->query_name()));
        return;
     }
  else
      {
        set_alarm(2.0, 0.0, &command("eyebrow"));
        set_alarm(3.0, 0.0, &command("drop "+obj->query_name()));
        return;
      }
}



void test_gate_quest(object player)
{
  if(player->test_bit("Avenir", Q_GROUP,GATEBIT))
    {
      set_alarm(2.0, 0.0, &command("say Why did you bring me "
              +"this again?"));
      set_alarm(4.0, 0.0, &command("shrug"));
      set_alarm(5.0, 0.0, &command("get all from platter"));
      set_alarm(6.0, 0.0, &command("eat all"));
      return;
    }

  set_alarm(1.0, 0.0, &command("say Ahhhhh!"));
  set_alarm(3.0, 0.0, &command("get all from platter"));
  set_alarm(5.0, 0.0, &command("eat all"));
   set_alarm(8.0, 0.0, &reward_gate_quest(player));
}

void reward_gate_quest(object player)
{
/*                  Quest name, who, group, bit, xp, align, prestige */
   reward_quest("Dead Isle Gate Quest", player,  Q_GROUP, GATEBIT, GATEEXP, -400, -4);

   seteuid(getuid(TO));

   WRITE_THIS_LOG(QUEST_FILE, "gave the head of Nochipa to "
        +"Mixcotoc. Reward: "+GATEEXP+" exp.\n" );
   command("whisper "+player->query_real_name()+" You may pass now and "
        +"forevermore. All you need to is ask.");
   open_gate();
}
