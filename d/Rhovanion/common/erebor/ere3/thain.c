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
void close_tomb_seq();

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
  set_act_time(300);
  add_act("rsay Welcome to the tomb of Thorin II!");
  add_act("rsay Have you got anything to ask me about?");
  add_cchat("Get out of here, you thieving scoundrel!");
  add_cchat("You won't get away with this, you know!");
  add_cchat("Guards! Help!");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Hello there! "
             + "","present me"}));  
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
    seq_alarm = set_alarm(1.0, 4.0, open_tomb_seq);
}

void
open_tomb_seq()
{
 switch(seq_c++)
  {
  case 1:
    command("say Time to open up!");
    break;
  case 2:
    command("unlock door with key");
    break;
  case 3:
    command("open door");
    break;
  case 4:
    command("smile friendly");
    break;
  case 5:
    command("e");
    break;
  case 6:
    remove_alarm(seq_alarm);
    break;
  }
}

void
close_tomb()
{
    if (objectp(query_attack()))
        return;

    seq_c = 0;
    seq_alarm = set_alarm(1.0, 4.0, close_tomb_seq);
}

void
close_tomb_seq()
{
 switch(seq_c++)
  {
  case 1:
    command("shout Time to close everybody!");
    break;
  case 2:
    command("emote Pushes everybody out from the tomb.");
    break;
  case 3:
    command("w");
    break;
  case 4:
    command("close door");
    break;
  case 5:
    command("lock door with gold key");
    break;
  case 6:
    remove_alarm(seq_alarm);
    break;
  }
}
