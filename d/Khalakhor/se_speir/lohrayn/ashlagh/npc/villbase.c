// Complete/Partial Random villager in Baile Ashlagh
//
// Zima, June 10, 1998
//
// Refactored, Tapakah, 08/2021

#pragma no_clone
#pragma strict_types
 
#include <ss_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include "adj.h"
#include "defs.h"

inherit BASE_NPC;

#define  SEPT (({"Gilvary", "Neese", "Stuart", "Larsech", "Ogden"}))
int      has_servername=0;
string   adj1, adj2;
 
//
// arm_me
//
void
arm_me ()
{
  if (! sizeof(armours))
    armours = query_gender() == G_MALE
      ? ({ COM_ARM+"shirt_cloth",
           COM_ARM+"belt",
           random(3) ? COM_ARM+"breeches" : COM_KILTS+"kilt_lohrayn" })
      : ({ COM_ARM+"dress",
           COM_ARM+"bonnet",
           COM_ARM+"apron" });
  
  ::arm_me();
}
 
//
// do_add_acts
//
void do_add_acts () {
  set_cact_time(30);
  add_cact("shout Guards! I'm being attacked!");
  add_cact("shout The naoimh curse ye, ye dirty dog!");
  add_cact("shout The guards'll make dog food of ye!");
  add_cact("shout Hit me in the face will ye! Why I'll...");
  add_cact("shout May the next boat ye ride sink like a rock!");
  set_act_time(60);
  add_act("emote breaths in the fresh air deeply.");
  add_act("say 'Tis a beautiful day, truly tis!");
  add_act("emote greets you saying, Deagh Madainn!");
  add_act("emote smiles hospitably.");
  add_act("emote eyes you suspiciously.");
  add_act("say The naoimh preserve ye, stranger.");
  add_act("say There's no fear of the goblins, I say.");
  add_act("say Things will pick up again once the gates are reopened.");
  add_act("say The goblins be gone for good now, I say.");
  add_act("say Top 'o the mornin' to ya, stranger.");
  if (query_gender()==G_FEMALE) {
    add_act("emote reties her bonnet beneath her chin.");
    add_act("emote wipes her hands on her apron.");
    add_act("emote nods her head to you politely.");
    add_act("emote smooths the wrinkles of her dress.");
    add_act("emote mumbles something to herself.");
    add_act("emote stumps her toe and curses abruptly.");
    add_cact("shout Fightin' a defenseless woman! A brave one ye are!");
    add_cact("shout If I had me rollin' pin, I'd bash yer brains in!");
    add_cact("shout Me pader'll dice ye into pieces!");
    add_cact("shout Me husband'll chop yer head off!");
  }
  else {
    add_act("emote pulls his kilt up higher above his hips.");
    add_act("emote rubs his chin thoughtfully.");
    add_act("emote adjusts his vest vainly.");
    add_act("emote smooths the wrinkles of his kilt.");
    add_act("emote admires your arms covetously");
    add_act("emote mumbles something to himself.");
    add_act("emote stumps his toe and curses abruptly.");
    add_cact("shout If I had me sword, I'd stick ye like a pig!");
    add_cact("shout If I had me mace, I'd bash yer head like a melon!");
    add_cact("shout If I had me dirk, I'd skin ye alive!");
    add_cact("shout I curse yer ancestors, ye wicked curr!");
  }
}
 
//
// set_servername
//
void set_servername ()
{
  if (query_gender())
    set_name(SERVERFILE->get_name(G_FEMALE));
  else
    set_name(SERVERFILE->get_name(G_MALE));
  log_me("GOT " + query_name(), "info", "servername");
  has_servername=1;
}
 
//
// set_std_desc
//
void set_std_desc ()
{
  adj1=ADJ1[(random(sizeof(ADJ1)))];
  if (query_gender()) {
    add_name(({"lass","woman"}));
    adj2=FEMALE_ADJ[(random(sizeof(FEMALE_ADJ)))];
    set_long("She is a "+adj1+" "+adj2+" human, one of the villagers of "+
             "Baile Ashlagh. She is dressed modestly with an apron and "+
             "bonnet, the traditional garb of the local women.\n");
    add_adj(({adj1,adj2,"bonnie"}));
  }
  else  {
    add_name(({"man","gent"}));
    adj2=MALE_ADJ[(random(sizeof(MALE_ADJ)))];
    set_long("He is a "+adj1+" "+adj2+" human, dressed in the "+
             "garb of Clan Lohrayn, a purple and white on gold kilt. "+
             "He is one of the villagers of Baile Ashlagh.\n");
    add_adj(({adj1,adj2,"handsome"}));
  }
}
 
//
// add_asks
//
string defans ()
{
  tell_room(ENV(TO),QCTNAME(TO)+" says: I don't know. Ye ought to ask "+
            "Maighstir Konner 'bout that.\n");
  return "";
}
void add_asks ()
{
  set_default_answer(defans);
  add_ask(({"konner","maighstir","maighstir konner","mayor"}),
          "say Konner be the maighster, the villager mayor. He's usually in "+
          "the town hall.",1);
}
 
//
// set_base_villager
//
void
set_base_villager ()
{
  int     level=10+random(50);
  string  sept=SEPT[(random(sizeof(SEPT)))];

  ::create_khalakhor_human();
  // set standard names/titles
  add_name("villager");
  add_prop(ATTACK_TEAM,ATEAM);
  if (not_configured) {
    set_race_name("human");
    set_living_name(lower_case(query_name()));
    cs_set_sept(sept);
    cs_set_clan("Lohrayn");
    set_title(sept+" of Clan Lohrayn");
  }
 
  // set standard descriptions/actions
  set_std_desc();
  do_add_acts();
  add_asks();
  set_height_desc("of normal length");
  set_width_desc("of normal width");
    
  //configure NPC level
  default_config_npc(level);
  set_skill(SS_UNARM_COMBAT, level);
  set_skill(SS_DEFENCE, level);
  set_alignment(100+random(300));
  set_exp_factor(50);
}
 
//
// create_villager
//
varargs void
create_villager (int gender=-2, string name="")
{
  // set gender of villager
  setuid();
  seteuid(getuid());
  object env = previous_object();
  string in_pub = 0;
  if (objectp(env))
    in_pub = function_exists("init_pub", env);

  string loc = env ? file_name(env) : "xx";
  log_me(loc + " " + in_pub + "!", "error", "villager");
  
  if (in_pub)
    set_gender(G_MALE);
  else if (gender > -2)
    set_gender(gender);
  else
    if (random(2))
      set_gender(G_MALE);
    else
      set_gender(G_FEMALE);
  
  set_base_villager();
  if (strlen(name)<=1) {
    log_me("Calling name ", "info", "villager");
    set_servername();
  }
}

//
// remove_object - return name to nameserver.
//
void
remove_object ()
{
  if (has_servername)
    SERVERFILE->return_name(query_gender(),lower_case(query_name()));
  ::remove_object();
}
 
void
hook_return_intro_new (string str)
{
  if (query_gender()==G_MALE) {
    command("say Top 'o the mornin' to ya, "+capitalize(str)+"!");
    command("say I'm "+query_name()+" "+query_title()+", and welcome to "+
            "Baile Ashlagh!");
    command("bow deeply");
  }
  else {
    command("say Goo' day to ya, "+capitalize(str)+"!");
    command("say I'm "+query_name()+" "+query_title()+", and pleased to "+
            "make yer acquaintance.");
    command("curtsey politely");
  }
  (find_player(lower_case(str)))->add_introduced(lower_case(query_name()));
}

void
attacked_by (object enemy)
{
  string  my_team_id = (TO->query_prop(ATTACK_TEAM));
  object  TR         = ENV(TO);
  object *inv        = (FILTER_PRESENT_LIVE(all_inventory(TR))) - ({TO});
  int     i;
 
  // if enemy gone or i'm not on a team, nothing to do
  if (! objectp(enemy) && stringp(my_team_id))
    return;
 
  // do normal attacked_by
  ::attacked_by(enemy);
 
  // check living in room. If on our team, call attacker
  for (i=0; i<sizeof(inv); i++) {
    if ((inv[i]->query_prop(ATTACK_TEAM) == my_team_id) /* same team */
        && ! inv[i]->query_prop(ATTACK_PASSIVE)
        && ! inv[i]->query_attack())                     /* !fighting */
      inv[i]->command("$kill " + OB_NAME(enemy));
  }
}

