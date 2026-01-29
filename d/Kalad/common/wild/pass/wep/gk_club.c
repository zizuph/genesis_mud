/* 
 * /d/Kalad/common/wild/pass/wep/gk_club.c
 * Purpose    : This is the Goblin King's, Nomog, Club. It is magical, in which you need less than 100 intelience, greater than 50 club skill, and less than 500 align. If you fail you loose fatigue. It also has a few cool emote with it.
 * Located    : Located on the goblin king, Nomog.
 * Created By : Antharanos  ??.??.??
 * Modified By: Damaris 07/2007
 * First Modif: Changed crush to smash, due to Ogres (AoD) have a crush 
 *              command.
 */ 

inherit "/d/Kalad/std/weapon";
#include "/d/Kalad/defs.h"
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"
/* by Antharanos */
create_weapon()
{
   ::create_weapon();
   set_name("club");
   set_adj("two-handed");
   add_adj("mithril");
   set_wf(TO);
   set_long("An immense club made entirely out of pure mithril, one "+
      "of the hardest substances known to the civilized races. The club "+
      "itself is flawless in its shape and contour, not the slightest "+
      "marring of its surface, save for the image of a blood-red hand "+
      "clutching a severed eyeball that adorns its handle. It looks "+
      "like it would 'smash' anything quite well.\n");
   set_hit(44);
   set_pen(44);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   set_hands(W_BOTH);
   add_prop(OBJ_M_NO_BUY,1);
   add_prop(OBJ_I_VALUE,2592);
   add_prop(OBJ_I_WEIGHT,30000);
   add_prop(OBJ_I_VOLUME,30000);
   add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
   add_prop(MAGIC_AM_MAGIC, ({ 50, "enchantment" }));
   add_prop(OBJ_S_WIZINFO,"This magically endowed club, which belongs "+
      "to the goblin king (/d/Kalad/common/wild/pass/npc/gob_king) has "+
      "been magically enhanced to hit harder and penetrate through defences "+
      "with greater ease than normal weapons. Due to its special properties, "+
      "the wielder must be skilled in its use (50 club skill), cannot be "+
      "entirely dedicated to good (align < 500) and must not have an "+
      "intelligence over 100. Failure to wield the club causes a severe "+
      "draining of one's strength, making that person very fatigued.\n");
   add_prop(MAGIC_AM_ID_INFO,({"This club has been enchanted\n", 5,
            "The enchantment on the club makes it more powerful than standard "+
            "weapons.\n", 25,
            "This enchanted club, more powerful than normal weapons, can only "+
            "be wielded by persons of low intellect, even lower principles, and "+
            "skilled wielders of clubs. Those that try to use the weapon and "+
            "fail will lose their energy.\n", 51}));
}
mixed
wield(object what)
{
   if(TP->query_stat(SS_INT) < 101)
      if(TP->query_alignment() < 500)
      if(TP->query_skill(SS_WEP_CLUB) > 49)
      {
      write("As your hands grasp the two-handed mithril club's handle, "+
         "a blood red hand appears in your mind's eye...\n"+
         "Then...\n"+
         "The bloody hand starts going through your memories!\n"+
         "The blood red hand withdraws from your mind and seems to allow you "+
         "to wield the two-handed mithril club.\n");
      say(QCTNAME(TP) + " suddenly stands stock still.\n");
      say(QCTNAME(TP) + " begins to move once more.\n");
      return 0;
   }
   TP->add_fatigue(-500);
   say(QCTNAME(TP) + " appears pale and quite shaken.\n");
   return "As your hands wrap around the handle of the two-handed "+
   "mithril club...an image of a blood red hand appears in your mind's "+
   "eye! The bloody hand rips and tears your energy away!!! The blood red "+
   "hand withdraws from your mind.\n";
}
mixed
unwield(object what)
{
   write("An image of a bloody hand clutching a severed eyeball appears "+
      "in your mind...then just as quickly...disappears.\n");
   say(QCTNAME(TP) + " looks somewhat relieved.\n");
   return 0;
}
init()
{
   ::init();
   add_action("club","club");
   add_action("smash","smash");
}
club()
{
   if(!query_wielded(TO))
      {
      write("You must wield the club first.\n");
      return 1;
   }
   write("You start clubbing everything within your reach into paste!\n");
   say(QCTNAME(TP) + " starts clubbing everything within " + TP->query_possessive() + " reach into paste!!\n");
   set_alarm(2.0,0.0,"club_effect");
   return 1;
}
club_effect()
{
   write("Everything in your vicinity is now flat as can be.\n");
   say("Everything in " + QCTNAME(TP) + "'s vicinity is now flat as can be.\n");
}
smash()
{
   if(!query_wielded(TO))
      {
      write("You must wield the club first.\n");
      return 1;
   }
   write("You whip out your two-handed mithril club and smash the "+
      "nearest convenient object.\n");
   say(QCTNAME(TP) + " whips out " + TP->query_possessive() + " two-handed mithril club and smashes the nearest convenient object.\n");
   return 1;
}
