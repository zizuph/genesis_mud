/*
 * Princess Lover, Wesley
 *
 * Quest NPC
 *
 * This is the NPC you shall rescue/free or rescue/assassin in the 
 * love or hate me quest in Kalaman.
 *
 * 20110628 Lunatari : Created
 * 20110927 Lunatari : Code review by Navarre, I made the changes. 
 */
#include "local.h"

inherit AM_FILE

string ask_to_follow();

#define SHORT_DESC "young curly-haired man"
#define CHAIN_DESC "chained to the wall"

int is_chained;
object trust_ob;

void chain_me();

void
create_krynn_monster()
{
    set_name("wesley");
    add_name("man");
    set_title("the Common Trader's Son of Kalaman");
    set_race_name("human");
    set_adj(({"young","curly-haired"}));
    set_short("young curly-haired man");
    set_long("He looks very well for a prisoner, in fact nothing " +
      "about this young curly-haired man gives you the impression " +
      "that he would be a hardened criminal. His eyes are tear-filled " +
      "but yet hopeful. His hair is still well kept and his clothes " +
      "does not at all resemble the other prisoners outfits. He seems " +
      "to have been placed in this cell recently, or he would be in the " +
      "same awful state as the others.\n");

    set_stats(({45, 65, 45, 45, 45}));
    set_hp(query_max_hp());

    set_alignment(900);
    set_knight_prestige(-3);

    set_act_time(10);
    add_act("moan");
    add_act("sob silent");
    add_act("grin badly");
    add_act("sigh");
    add_act("say My sweet Kirsten! Look what they have done to us!");

    set_default_answer("say I am not sure about that, I just want to get "+
      "back to my sweet Kirsten!\n"); 

    add_ask("prison", "say Yes, Prison, Just because the princess should " +
      "not be with the son of a simple trader, specially not a poor one, " +
      "so sir Calof, hmpf, put me in here to get rid of me.\n");
    add_ask("kirsten", "say Yes! My love, My sweet Kirsten! You know it " +
      "is quite amazing that the princess of Kalaman is actually such a " +
      "sweet; and so in love with me! I wish I could get back to her!\n");
    add_ask("escape", "say You would help me escape? That is just so " +
      "very kind of you. When you are ready to go just ask me and I " +
      "shall follow!\n");
    add_ask("follow", ask_to_follow, 1);
    
    add_prop(LIVE_I_NEVERKNOWN, 0);

    seteuid(getuid());

    equip(({ KOBJ + "armour/shirt" }));

    set_alarm(1.0, 0.0, &chain_me());
}

void
return_intro(string who)
{
  who = L(who);
  if (P(who,E(TO)))
  {
    command("say Oh, Hello there!");
    command("introduce myself");
  }
}

void
add_introduced(string who)
{
  set_alarm(2.0, 0.0, &return_intro(who));
}

string
ask_to_follow()
{
   if (is_chained)
   {
     return "say I would love to! Sadly I am chained to the wall!";
   }

   if (trust_ob->query_real_name() == TP->query_real_name())
   {
     TO->set_follow(TP);
     return "say Ok " + QCTNAME(TP) + "! I will follow you!";
   }
   else
   {
     return "say I am sorry, I do not trust you!";
   }
} 

void
unchain_me(object player)
{
  if (ENV(TO)->query_chains())
  {  
     ENV(TO)->remove_prisoner();
     trust_ob = player;
     is_chained = 0;
     command("say Thank you " + QNAME(player) + ", now I will " +
       "follow you, if you ask me!");
  }
}

void
chain_me()
{
  if (!ENV(TO)->query_chains())
  {  
     ENV(TO)->add_prisoner(TO);  
     is_chained = 1;
  }
} 
