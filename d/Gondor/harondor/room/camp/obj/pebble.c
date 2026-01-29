/* Name      : /d/Gondor/harondor/room/camp/obj/pebble.c
 * Purpose   : Pebbles to lay on the trail to make players
 *             curious and will be part of a cleanup
 *             quest. Thus the added name:
 *                _harondor_pebble_chief_quest_part_I
 * Created by: Sir Toby, Gondor Domain, 2005-11-15
 *
 *   Modified: Sir Toby, Gondor Domain, 2006-08-18
 *                 Now allows for ingredient to Heralds.
 */

inherit "/std/object";

#include "/sys/stdproperties.h"

//string PSIZE = [("tiny", "small", "medium")random(3)];
string PSIZE = one_of_list(({"tiny", "small", "small", "medium"}));
string PSHAPE = " " + one_of_list(({"oval shaped", "round", 
                                     "flat oval shaped", 
                                     "oval and hollow"}));

void
create_object()
{
   set_name("pebble");
   add_name("stone");
   add_name("_harondor_pebble_chief_quest_part_I");
   add_name("_prot_spell_ingr1_");
   set_adj(PSIZE);

   set_short(PSIZE + " sized pebble");
   set_pshort(PSIZE + " sized pebbles");
   set_long("A " + PSIZE + PSHAPE + " pebble very " +
            "smooth to the touch.\n");

   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT,5);
   add_prop(OBJ_I_VOLUME,1);
}
