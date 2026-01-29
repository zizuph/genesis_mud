inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>

static int flag;

string inscription();

void create_armour()
{
  set_name(({ "helm", "helmet" }));
  set_adj("visored");

  set_long("A fine visored helm.  There is a short inscription " +
      "on the back of it.\n");

  add_item("inscription", "@@inscription@@");
  add_cmd_item("inscription", "read", "@@inscription@@");

  set_af(this_object());
  set_at(A_HEAD);
  set_ac(30);

  add_prop(OBJ_I_VALUE, 800);
  add_prop(OBJ_I_WEIGHT, 1500);
  add_prop(OBJ_I_VOLUME, 1000);
  add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
  add_prop(MAGIC_AM_MAGIC, ({ 70, "enchantment" }));
  add_prop(MAGIC_AM_ID_INFO, ({ 
      "The helm is enchanted with very powerful magic.\n", 10,
      "It seems that the power of the helm can only be invoked by " +
          "a single individual.\n", 30,
      "To that special individual, it provides powerful magically enhanced " +
          "perception.\n", 80 }));
  add_prop(OBJ_S_WIZINFO, "The special powers of this helm can only be " +
      "used by the Emerald npc, Curan.  It provides him w/ 100 levels of " +
      "LIVE_I_SEE_DARK, up to 100 levels of SS_BLIND_COMBAT.\n");
  
}

string inscription()
{
  if (this_player()->query_race_name() == "elf" ||
      this_player()->query_skill(SS_LANGUAGE) > 50)
  {
    return "It reads, \"For the noble Prince Curan.\"\n";
  }
 
  if (this_player()->query_skill(SS_LANGUAGE) > 20)
  {
      return "You recognize it as elvish but cannot understand " +
        "the words.\n";
  }

  return "You cannot make out the words.\n";
}

int wear(object ob)
{
  flag = 0;
  if (this_player()->id("prince_curan"))
  {
    this_player()->add_prop(LIVE_I_SEE_INVIS,
        this_player()->query_prop(LIVE_I_SEE_INVIS) + 100);
    this_player()->set_skill_extra(SS_BLIND_COMBAT, 
        100 - this_player()->query_skill(SS_BLIND_COMBAT));
    flag = 1;
  }

  return 0;
}

int remove(object ob)
{
  if (flag)
  {
    this_player()->add_prop(LIVE_I_SEE_INVIS,
        this_player()->query_prop(LIVE_I_SEE_INVIS), -100);
    this_player()->set_skill_extra(SS_BLIND_COMBAT, 0);
  }

  return 0;
}    
