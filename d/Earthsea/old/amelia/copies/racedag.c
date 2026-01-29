/* created by Aridor 11/30/93 */
/* modified to adjust to a dagger Vladimir 8-18-94 */
   inherit "/std/weapon";

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Roke/common/defs.h"




create_weapon()
{
   set_name("peace maker");
   set_pname("daggers");
   add_name("dagger");
   set_adj("viscious");
   add_adj("midnight-black");
   set_long("@@my_long");  
   set_default_weapon(33, 35, W_KNIFE, W_SLASH | W_IMPALE, W_RIGHT);

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
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(33,35) + 1000); /* it is magical! */
}
int
try_hit(object ob)
{
   if (random(1))
       {
      query_wielded()->catch_msg("You attempt to strike your enemy "+
         "with the dagger, but you fail miserably and almost drop it "+
         "on the ground.\n");
      tell_room(environment(query_wielded()), QCTNAME(query_wielded()) +
         " stumbles forward and almost drops his dagger.\n",
         query_wielded());
      return -1;
   }
   return 1;
}
varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int
dam)
{
   if (enemy->query_race_name("human"))
    dam *= 2;
write("The human is in extreme pain.\n");
TP->catch_msg("The dagger has a hit of: " + TO->query_hit() + ".\n");
   if (phurt == -1)
      {
      query_wielded()->catch_msg("You deftly swing the dagger, just missing "+
        "your opponent's throat.\n");
      enemy->catch_msg("You can faintly hear the sound of humming as the "+
         "viscious midnight-black dagger narrowly glides by your throat.\n");
   }
   else if (phurt == 0)
      {
      query_wielded()->catch_msg("You dart forward and slice into the"+
         " "+ enemy->query_nonmet_name()+" he does not seem harmed, "+
         "just surprised.\n");
      enemy->catch_msg("You are astonished by the velocity at which the "+
         "viscious midnight-black dagger just barely slices you in the ribs.\n");
   }
   else
      {
      query_wielded()->catch_msg("The viscious midnight-black dagger "+
          "seems to aim and savagely cut your enemy by itself.\n");
      enemy->catch_msg("You stagger from the pain as the viscious midnight-black "+
         "dagger plunges deep into your stomache, blood begins to spurt forth from "+
         "your deep and jagged wound.\n");
   }
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


my_long()
{
   return "This dagger is long and viscious. The blade is midnight black. "+
    "The hilt is made from soft leather that is dyed green, wrapped "+
   "around metal. On the very bottom of the weapon is a symbol of two "+
   "crossed axes over a map of the world.\n";


}




mixed
wield(object what)
{
   if (TP->query_base_stat(SS_DIS) > 70)
      {
      write("You feel a slight tinge of fear as you grip this magnificent "+
        "weapon. You manage to overcome it and take hold of its power.\n");
      return 0;
   }
   TP->add_mana(-random(50)-10);
   return "As you try to take hold of the dagger, an overpowering feel " +
   "of terror rips through your mind and body. You are unable to wield "+
   "the dagger.\n";
}

mixed
unwield(object what)
{
   return 0;
}


