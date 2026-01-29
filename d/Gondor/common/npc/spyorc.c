inherit "/std/monster";
inherit "/std/act/action";
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"

create_monster()
{
  if (!IS_CLONE)
    return;
  set_name("orc");
  set_race_name("orc");
  set_short("spying orc");
  set_adj(({"ugly","spying"}));
  set_long("This orc seems to be out spying on something.\n"+
    "Upon the front of his armour and his helm you spot a little symbol:\n"+
    "A red, lidless eye.\n");
  set_pshort("spying orcs");
  default_config_npc(random(5)+12);
  set_base_stat(SS_CON,random(6)+16);
  set_hp(10000);
  set_alignment(-150);
  set_aggressive(1);
  set_attack_chance(40);
  set_skill(SS_WEP_SWORD, random(5)+9);
  set_chat_time(8);
  add_chat("Uruk drepa tuluk! Egur lug en vesall hai krimpatul!");
  add_chat("Onreinn hundur drepa!");
  add_chat("Ash nazg gimba, burz goth thraka!");
  add_chat("Rum marzgitul! Auga bukratul!");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Drepa tuluk!"}));
}

get_armed() {
  object wep, arm;
  seteuid(getuid(this_object()));
  wep = clone_object("/d/Gondor/elessar/obj/wep/orcscim");
  wep->move(this_object());
  command("wield scimitar");
  arm = clone_object("/d/Gondor/elessar/obj/arm/releather");
  arm->move(this_object());
  command("wear leather");
  arm = clone_object("/d/Gondor/elessar/obj/arm/rethelm");
  arm->move(this_object());
  command("wear helm");
}

/* solemnian prestige */
query_knight_prestige() {return 300; }

