/* Name      : /d/Gondor/harondor/room/camp/obj/pebble.c
 * Purpose   : Pebbles to lay on the trail to make players
 *             curious and will perhaps be part of a cleanup
 *             quest. Thus the added name:
 *                _harondor_pebble_chief_quest_part_I
 * Created by: Sir Toby, Gondor Domain, 2005-11-15
 *
 *   Modified: Sir Toby, Gondor Domain, 2006-08-18
 *                       Made it a heap object to support the quest.
 *                       Also allows for ingredient to Heralds.
 */

inherit "/d/Shire/common/obj/rock";

string PSIZE = one_of_list(({"tiny", "small", "small", "medium"}));
string PSHAPE = " " + one_of_list(({"oval shaped", "round", 
                                     "flat oval shaped", 
                                     "oval and hollow"}));


string
pebble_long()
{
   return ((num_heap() == 1) ? "A " + PSIZE + PSHAPE + 
           " pebble. very smooth to the touch.\n" : "The pebbles are very " +
           "smooth to the touch.\n");
}

void
create_pebble()
{
   set_name("pebble");
   add_name("_harondor_pebble_chief_quest_part_I");
   set_adj(PSIZE);

   set_short(PSIZE + " sized pebble");
   set_long(pebble_long);

}


init()
{
    ::init();
    create_pebble();
}

