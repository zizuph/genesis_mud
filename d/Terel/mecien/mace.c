inherit "/std/weapon";
#include "/sys/formulas.h"
#include "/sys/stdproperties.h"

create_weapon(){
   set_name("mace");
   set_adj("gilded-silver");
   set_short("gilded silver mace");
   set_long("It is a beautifully crafted mace, gilded with silver " +
      "and gold. The images of angelic spirits adorn its length.\n");
   set_hit(30);
   set_pen(28);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME, 3000);
   add_prop("mystic_weapon", 1);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "conjuration"}));
   add_prop(OBJ_I_IS_MAGIC_WEAPON, 15);
}

did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
   int phit, int dam)
{
   if(phurt > 1){
  if(enemy->query_prop(LIVE_I_UNDEAD)){
            query_wielded()->catch_msg("The mace seems to grow warm in your grasp!\n");
            enemy->catch_msg("Some holy power from the mace weakens you!\n");
            enemy->heal_hp(-10);
         }
      }
}
