inherit "/std/monster";
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>

string occ;

string
random_color()
{
    int i;
  i = random(4);
  switch(i) {
    case 0:
      occ = "rower";
      return "rowing";
      break;
    case 1:
      occ = "slave";
      return "slave";
      break;
    case 2:
      occ = "slave";
      return "slave";
      break;
    case 3:
      occ = "convict";
      return "convict";
      break;
    }
	
}

void
create_monster()
{
    string color;

    color = random_color();
    
    set_name(occ);
    add_adj("strong");
    add_adj(color);
    set_race_name("minotaur");

    default_config_npc(50);

    set_base_stat(SS_STR, 70);
    set_base_stat(SS_CON, 60);
    set_hp(1000);

    seq_new("do_stuff");
    seq_addfirst("do_stuff",
	({ "@@get_oar", "say Let's get this ship moving, shall we?" }) );
    add_prop(OBJ_M_NO_ATTACK, "You feel the minotaur is under protection.\n");
}

void
get_oar()
{
    object oar;

    seteuid(getuid());
    oar = clone_object(OBJ + "oar");
    if (oar)
    {
	oar->move(this_object());
	command("wield oar");
    }
}
