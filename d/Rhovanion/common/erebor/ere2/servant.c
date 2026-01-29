inherit "/std/monster";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <living_desc.h>
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere2/"

int     seq_c = 0,
        seq_alarm;
 
object servant;
object key;
 
void close_door_seq();

void
create_monster() 
{
  set_living_name("gundor");
  set_name(({"gundor","servant","schoolclerk"}));
  set_title("schoolclerk");
  set_race_name("dwarf");
  set_adj(({"weak","gray-haired"}));
  default_config_npc(52);
  set_base_stat(SS_CON,100);
  set_base_stat(SS_STR,60);
  set_alignment(100+random(200));
  add_act("rsay Who are you?");
  add_cchat("Get out of here, you thieving scoundrel!");
  add_cchat("Guards! Help!");
  seq_new("do_things");
  seq_addfirst("do_things",({"present me","@@close_door"}));
}


/* solemnian prestige */
query_knight_prestige() {return (-5);}

void
close_door()
{
    if (objectp(query_attack()))
        return;

    key = clone_object(CAVE_DIR + "small_key");
    key->move(TO);
    seq_c = 0;
    seq_alarm = set_alarm(1.0, 1.0, close_door_seq);
}

void
close_door_seq()
{
 switch(seq_c++)
  {
  case 1:
    command("yawn");
    break;
  case 2:
    command("close door");
    command("emote closes the door.");
    break;
  case 3:
    command("lock door with key");
    command("emote locks the door.");
    break;
  case 4:
    command("smile friendly");
    break;
  case 5:
    remove_alarm(seq_alarm);
    write("The servant disapers behind a curtain, and is gone!\n");
     remove_object();
    break;
  }
}

