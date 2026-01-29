inherit "/std/weapon";
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <wa_types.h>




create_weapon()
{
   set_name("peace maker");
   add_name("maker");
   set_pname("peace makers");
    add_pname(({"daggers","weapons"}));
   add_name("dagger");
   set_adj("vicious");
   add_adj("midnight-black");
   set_long("@@my_long");
   set_default_weapon(36, 38, W_KNIFE, W_SLASH | W_IMPALE, W_RIGHT);

   set_wf(TO);
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
   add_prop(OBJ_S_WIZINFO,"This is a very potent dagger. It is very light "+
      "and strong. It has magic in that allows it a high hit and "+
      "penetration. It was made especially for the town marshal to "+
      "keep the town in order.\n");

   add_prop(MAGIC_AM_ID_INFO,({"This weapon is magical and potent\n", 5,
            "You feel a strong will emanating from " +
            "the dagger that you must overcome.\n", 25,
            "The weapon's balance is subject to the magic, "+
            "allowing better wieldability and very high hit rate.\n", 51}));
   add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
   add_prop(OBJ_I_VOLUME, 2500);
   add_prop(OBJ_I_WEIGHT, 3900);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(36,38) + 1200);
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


my_long()
{
   return "This dagger is long and vicious. The blade is midnight black. "+
   "The hilt is made from soft leather that is died green wrapped "+
   "around metal. On the very bottom of the weapon is a symbol of two "+
   "crossed axes over a map of the world.\n";


}


mixed
wield(object what)
{
      if (this_player()->query_skill(SS_WEP_KNIFE) > 65)
   if (TP->query_base_stat(SS_DIS) > 80)
   if (TP->query_base_stat(SS_DEX) > 80)
      {
      write("You feel a slight tinge of fear as you grip this magnificent "+
         "weapon. You manage to overcome it and take hold of it's power.\n");
      return 0;
   }
   TP->add_panic(random(100)-5);
   return "As you try to take hold of the dagger, an overpowering feel " +
   "of terror rips through your mind and body. You are unable to wield "+
   "the dagger.\n";
   TP->command("panic");

}

mixed
unwield(object what)
{
   write("You hear a chilling howl in the distance.\n");
   say(QCTNAME(TP)+" seems to struggle for a moment.\n");
   TP->command("sigh");
   return 0;

}


