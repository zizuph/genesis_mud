inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <living_desc.h>
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere3/"

int     seq_c = 0,
        seq_alarm;
 
void open_tomb_seq();

void
create_monster() 
{
  set_living_name("thain");
  set_name(({"thain","guard","tombguard"}));
  set_title("of Erebor, guardian of Thorins tomb");
  set_race_name("dwarf");
  set_adj(({"muscular","red-haired"}));
  set_long("This is Thain the faithful, who guards the tomb "
        + "of Thorin.\n");
  default_config_npc(52);
  set_base_stat(SS_CON,200);
  set_base_stat(SS_STR,180);
  set_skill(SS_WEP_AXE, random(10)+90);
  set_skill(SS_DEFENCE, random(10)+90);
  set_skill(SS_PARRY, random(10)+90);
  set_alignment(100+random(200));
  set_chat_time(300);
  add_chat("Can I help you?");
  add_chat("Welcome to the tomb of Thorin II!");
  add_chat("My name is Thain.");
  add_chat("Have you got anything to ask me about?");
  add_cchat("Get out of here, you thieving scoundrel!");
  add_cchat("You won't get away with this, you know!");
  add_cchat("Guards! Help!");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Well, I'm back in "
             + "business.","present me"}));  
}

void
get_armed()
{
  clone_object(WEAPON_DIR + "axe_sup")->move(TO);
  command("wield axe");
  clone_object(ARMOUR_DIR + "goblin/mail_sup")->move(TO);
  clone_object(ARMOUR_DIR + "goblin/helm_sup")->move(TO);
  command("wear all");
  clone_object(CAVE_DIR + "gold_key")->move(TO);
}

/* solemnian prestige */
query_knight_prestige() {return (-5);}

void
open_tomb()
{
    if (objectp(query_attack()))
        return;

    seq_c = 0;
    seq_alarm = set_alarm(5.0, 1.0, open_tomb_seq);
    set_alarm(5.0, 1.0, open_tomb_seq);
}

void
open_tomb_seq()
{
 switch(seq_c++)
  {
  case 1:
    command("unlock gate with gold key");
    break;
  case 2:
    command("open gate");
    break;
  case 3:
    command("fart");
    break;
  case 4:
    command("laugh rude");
    break;
  case 5:
    remove_alarm(seq_alarm);
    break;
  case 6:
    command("burp");
    break;
  }
}

