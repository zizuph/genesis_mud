inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
void
create_armour() {
   set_name("bucklers");
   set_short("pair of gold etched steel bucklers");
   set_pshort("pairs of gold etched steel bucklers");
   set_adj(({"gold etched","steel"}));
   set_long("This is a pair of oval shaped, small, " +
      "steel shields meant to be worn along the length " +
      "of the back of the forearm, strapped to your wrist " +
      "and just below your elbow.  Around the edges " +
      "they are trimmed with ornately set gold, and " +
      "in the center of the shields is etched in gold " +
      "a picture of a long, coiled and horned wyrm.\n");
   set_ac(25);
   set_am(({ 0, 5, -5 }));
   set_at(A_HANDS);
}
