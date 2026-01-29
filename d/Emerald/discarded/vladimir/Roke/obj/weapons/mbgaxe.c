inherit "/d/Kalad/std/weapon.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
/* by Antharanos */
void
create_weapon()
{
   ::create_weapon();
   set_name("blood-stained axe");
   add_name("axe");
   set_long("A large steel axe with brown stains all over its surface. "+
      "The axe has a particularly keen-looking edge, leading you to believe "+
      "that the stains are not rust marks, but dried blood.\n");
   set_hit(40);
   set_pen(40);
   set_hands(W_BOTH);
   set_wt(W_AXE);
   set_dt(W_SLASH);
   add_prop(OBJ_I_VALUE, 1200);
   add_prop(OBJ_I_WEIGHT, 15000);
   add_prop(OBJ_I_VOLUME, 10000);
}
int
try_hit(object ob)
{
   if (random(1))
      {
      query_wielded()->catch_msg("You try but aren't able to swing the "+
         "blood-stained axe.\n");
      tell_room(environment(query_wielded()), QCTNAME(query_wielded()) +
         " strains visibly but doesn't manage to swing the blood-stained axe.\n",
         query_wielded());
      return -1;
   }
   return 1;
}
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
   if (phurt == -1)
      {
      query_wielded()->catch_msg("You manage to slice through empty air "+
         "with the blood-stained axe.\n");
      enemy->catch_msg("The blood-stained axe whistles through the air just "+
         "inches from your head.\n");
   }
   else if (phurt == 0)
      {
      query_wielded()->catch_msg("You gasp in astonishment when the "+
         "blood-stained axe just tickles the "+ enemy->query_nonmet_name()+ ".\n");
      enemy->catch_msg("To your surprise the blood-stained axe just nicks "+
         "your head instead of slicing it to ribbons.\n");
   }
   else
      {
      query_wielded()->catch_msg("The blood-stained axe slices into your "+
         "enemy leaving behind tattered flesh.\n");
      enemy->catch_msg("You feel the blood-stained axe slice into you, "+
         "leaving behind tattered flesh.\n");
   }
   return 1;
}
