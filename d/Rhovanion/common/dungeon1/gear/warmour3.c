inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("mail");
   set_short("suit of full high steel scale mail");
   set_pshort("suits of full high steel scale mail");
   set_adj(({"full","high steel","scale"}));
   set_long("This suit of armour is comprised of many " +
      "small scales of high steel each etched with a " +
      "gold plated picture of a coiled and horned wyrm. " +
      "The scales cover the chest, arms, and legs of its " +
      "wearer quite well especially considering how light " +
      "the suit is and how little it constricts movement.\n" +
      "     Strange horns from an unknown animal, though " +
      "most likely reptilian, protrude from the edges of " +
      "the sleeves and leggings and the shoulders as well. " +
      "It looks very formidable.\n");
   set_ac(45);
   set_am(({ -2, 3, -1 }));
   set_at(A_BODY | A_LEGS | A_ARMS );
}
