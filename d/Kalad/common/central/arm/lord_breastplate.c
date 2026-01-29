/* 
 * /d/Kalad/common/central/arm/lord_breastplate.c
 * Purpose    : Breastplate worn by the high lord in the citadel (magical)
 * Located    : /d/Kalad/common/central/arm/
 * Created By : Korat 1995
 * Modified By: Zignur buffed the AC and fixed the resists ( so they work )
 * Zignur Jan 2018  Fixed a typo in the MAGIC_AM_ID_INFO
 *
 */ 

/*
High Lords breastplate
Made by korat
feb 14. 1995
*/

inherit "/d/Kalad/std/armour.c";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"

create_armour()
{
   ::create_armour();
   set_name("breastplate");
   set_adj("black");
   add_adj("grand");
   set_long("The breastplate shines in its black light. Even though "+
      "it is made of a single piece of a unknown black metal, it is still "+
      "shaped to reflect the muscles of an athlete, creating small "+
      "shadows to fall from the breast down to an engraved image of "+
      "a clenched fist.\n");
   /* Zignur increased the AC */
   set_ac(55);
   set_at(A_BODY);
   set_af(TO);
   add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
   /* Zignur give it 10 res instead of 10,30,20 */
   add_prop(OBJ_I_RES_MAGIC, 10);
   add_prop(OBJ_I_RES_FIRE, 10);
   /* Zignur changed to death instead of air */
   add_prop(OBJ_I_RES_DEATH, 10);
   add_prop(OBJ_I_VALUE,2500);
   /* Nerfed the weight slightly */
   add_prop(OBJ_I_WEIGHT,11500);
   add_prop(OBJ_I_VOLUME,11000);
   add_prop(OBJ_S_WIZINFO,"This breastplate is enchanted, making "+
      "it have a better protection (ac=55) than normal armours can "+
      "have. It also makes the wearer more protected agains magic. "+
      "To wear this armour, the wearer must have a dis of 70. "+
      "Also, to be able to wear it, the player must "+
      "be sober. To remove it later on s/he must be sober too. The "+
      "reasoning behind this is that the player must be in full "+
      "control of the body to be able to control the magic inherit "+
      "in the armour. Failure to wear it or remove it will give "+
      "the player punishment in less mana, -50.\n");
   add_prop(MAGIC_AM_ID_INFO,({"With your newly gained knowledge "+
      "about this armour, you know that it is enchanted to provide "+
      "excellent protection both against plain weapons and partly "+
      "from the elements it was itself created with. "+
      "You also understand that it is not for anybody to use it. "+
      "The wanting wearer must have a basic understanding of magic "+
      "and be fully concentrated to dare to wear it.\n",30}));
   add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
}

mixed
wear(object what)
{
   if ((TP->query_base_stat(SS_DIS)>60) &&
      (TP->query_intoxicated()<(TP->query_prop(LIVE_I_MAX_INTOX)/10)))
   {
      write("With a chill going through your body, you wear the " +
            "breastplate.\n");
      return 0;
   }
   write ("You strain yourself, but you fail in wearing the "+
      "breastplate. A shiver goes through your body, "+
      "and you feel a small headache drain you somewhat.\n");
   TP->add_mana(-50);
   return -1;
}

mixed
remove(object what)
{
   if (TP->query_intoxicated()<10)
      {
          
          wearer->catch_msg("A chill goes through your body when you "+
          "rip it off yourself.\n");
      return 0;
   }
   wearer->catch_msg("You struggle to remove the breastplate, "+
      "but you fail. You cannot concentrate enough on forcing it off "+
      "your body.\n");
      TP->add_mana(-50);
   return -1;
}

/*
 * Zignur This is needed to make the resists work properly
 *
 */
public mixed
query_magic_protection(string prop, object what)
{
    if ( what == query_worn() )
    {
        switch(prop)
        {
            case MAGIC_I_RES_MAGIC:
            case MAGIC_I_RES_FIRE:
            /* Zignur changed to death instead of air */
            case MAGIC_I_RES_DEATH:
                return ({ 10, 1 });
            default:
                break;

        }
    }
    
    return ::query_magic_protection(prop, what);
}
