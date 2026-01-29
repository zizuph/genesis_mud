inherit "/std/object";
inherit "/d/Gondor/common/lib/tell_funcs";
#include "/sys/stdproperties.h";
#include "/d/Gondor/defs.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"

create_object() {
  set_name("horn");
  set_adj("ivory");
  set_adj("silver-clad");
  set_short("silver-clad ivory horn");
  set_long("This ivory horn is from the great Kine of Araw. Silver is clad\n"+
    "around it in intricate patterns, and the horn has been hollowed out\n"+
    "to make it possible to blow in it, and produce a strong sound.\n");
  add_prop(OBJ_I_WEIGHT,250);
  add_prop(OBJ_I_VOLUME,200);
  add_prop(OBJ_I_VALUE,600);
  add_prop(OBJ_M_NO_BUY,1);
  seteuid(getuid());
}

init()
{
  ::init();
  add_action("blow_horn","blow");
  add_action("play_horn","play");
}

blow_horn(string str)
{
  if (!str) { write(capitalize(query_verb())+" what?\n"); return 1; }
  if (str != "horn") return 0;
  write("You breathe deeply, and blow the horn.\n");
  write("You produce a deep and mighty, bellowing sound!\n");
  say(QCTNAME(TP)+" blows in the horn, and produces a mighty sound!\n",TP);
  tell_players_in_domain_out(query_domain(this_player()),
    "The sound of a mighty horn echoes through the land.\n");
  tell_next_room_with_dir(environment(this_player()),
    "You hear the sound of a mighty horn from");
  return 1;
}

