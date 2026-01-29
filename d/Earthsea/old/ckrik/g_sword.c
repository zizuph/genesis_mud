inherit "/d/Earthsea/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

#define WEAPON_HIT 40
#define WEAPON_PEN 40

static int damage = 150;

void
create_earthsea_weapon()
{
  set_name("sword");
  set_pname("swords");
  add_name("blade");
  add_pname("blades");

  set_adj("long");
  add_adj("steel");

  set_short("long steel blade");
  set_pshort("long steel blades");
  
  set_long(break_string("A long steel blade. It is extraordinarily " +
	   "long and has a blade wider than any sword you have " +
	   "ever seen. It is very heavy. This sword should be " +
	   "to inflict a lot of damage on its victims.\n", 70));

  set_hit(WEAPON_HIT);
  set_pen(WEAPON_PEN);
  set_wt(W_SWORD);
  set_dt(W_SLASH | W_BLUDGEON);
  set_hands(W_BOTH);
  set_wf(this_object());
  
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN) + 500);
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WEAPON_HIT,WEAPON_PEN) + 
	   5000);
  add_prop(OBJ_M_NO_BUY, 1);
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

mixed
wield()
{
  if (this_player()->query_stat(0) < 60)
    {
      return "You are too weak to wield the " +
	this_object()->query_short() + ".\n";
    }
  
    this_player()->set_skill_extra(0, 40);
    this_player()->set_skill_extra(23, 70);
    this_player()->set_skill_extra(24, 65);

    return 0;
}

mixed
unwield()
{
  this_player()->set_skill_extra(0, 0);
  this_player()->set_skill_extra(23, 0);
  this_player()->set_skill_extra(24, 0);
  return 0;
}


string
query_recover()
{
  return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}

int
did_hit(int aid, string hdesc, int phurt, object enemy,
	int dt, int phit, int dam)
{
  enemy->heal_hp(-1 * damage);
  return 0;
}

void
init()
{
  add_action("dam_set", "damage");
}

int
dam_set(string str)
{
  damage = atoi(str);
  return 1;
}
