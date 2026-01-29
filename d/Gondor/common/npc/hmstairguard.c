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
  set_short("orc guard");
  set_adj(({"ugly","guarding"}));
  set_long("This orc is standing here on guard duty.\n"+
    "Upon the front of his armour and his helm you spot a little symbol:\n"+
    "A white hand on a black background.\n");
  set_pshort("orc guards");
  set_stats(({ 36, 38, 40, 18, 18, 20 }));
  set_alignment(-250);
  set_hp(10000);
  set_skill(SS_WEP_SWORD, random(5)+40);
  set_skill(SS_WEP_CLUB, random(5)+40);
  set_skill(SS_WEP_POLEARM, random(5)+40);
  set_chat_time(8);
  add_chat("Uruk drepa tuluk! Egur lug en vesall hai krimpatul!");
  add_chat("Onreinn hundur drepa!");
  add_chat("Ash nazg gimba, burz goth thraka!");
  add_chat("Rum marzgitul! Auga bukratul!");
  seq_new("do_things");
  seq_addfirst("do_things",({"@@get_armed","say Grrrmph!"}));
}

get_armed() {
  object wep, arm;
  int w,a;
  seteuid(getuid(this_object()));
  w = random(3);
  a = random(3);
  if (w) wep = clone_object("/d/Gondor/elessar/obj/wep/orcscim");
  else wep = clone_object("/d/Gondor/elessar/obj/wep/orchalberd");
  wep->move(this_object());
  command("wield "+wep->query_name());
  if (a) arm = clone_object("/d/Gondor/elessar/obj/arm/whleather");
  else arm = clone_object("/d/Gondor/elessar/obj/arm/whchain");
  arm->move(this_object());
  command("wear armour");
  arm = clone_object("/d/Gondor/elessar/obj/arm/whhelm");
  arm->move(this_object());
  command("wear helm");
}

init_living()
{
  ::init_living();
  if (check_disguise(this_player())) return;
  this_object()->attack_ob(this_player());
}

check_disguise(object player)
{
  if (present("Orthanc_Clothes",player))
    if (present("Orthanc_Clothes",player)->query_worn() == player) return 1;
  return 0;
}

/* Solemnian prestige */
query_knight_prestige() { return 400; }
