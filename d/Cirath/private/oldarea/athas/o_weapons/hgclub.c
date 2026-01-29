inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
create_weapon()
{
   ::create_weapon();
   set_name("club");
   set_adj("huge");
   add_adj("obsidian");
   set_short("huge obsidian club");
   set_long("This is a massive club. It is basically a large obsidian "
	+"stalagtite that looks to have been torn from the roof of a "
	+"cave. It has some leather wrapped around the handle to "
	+"protect the wielders hands from harm. It must weigh a ton.\n");
   set_hit(10);
   set_pen(40);
   set_hands(W_BOTH);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_wf(TO);
   add_prop(OBJ_I_WEIGHT,50000);
   add_prop(OBJ_I_VOLUME,3000);
   add_prop(OBJ_I_VALUE,1);
}
mixed
wield(object what)
{
   if (this_player()->query_skill(SS_WEP_CLUB) > 30)
   if (TP->query_base_stat(SS_STR) > 85)
   if (TP->query_base_stat(SS_CON) > 85)
      {
	write("You manage to lift the huge club from the ground.\n");
      return 0;
      }
     return "You are too weak and pitiful to handle this weapon!\n";
}
