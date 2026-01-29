/* 
 * /d/Kalad/common/wild/pass/arm/moc_armour.c
 * Purpose    : A full breastplate of obsidian armour
 * Located    : Used by something
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
   ::create_armour();
   set_name("armour");
   set_adj("obsidian");
   add_adj("mail");
   set_long("Incredibly enough, this seems to be a suit of armour, "+
      "fashioned out of obsidian. Although made from stone, it seems "+
      "capable of fending off the strongest of blows.\n");
   set_ac(31);
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE,600);
   add_prop(OBJ_I_WEIGHT,18000);
   add_prop(OBJ_I_VOLUME,18000);
}
