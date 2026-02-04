/*
 * Cotillion 2015-02-14: LIVE_I_QUICKNESS 100 -> 50
                         Removed the clone logging
 */

#pragma strict_types

#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;
// inherit "/d/Terel/include/cloned_armours.c";

#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Terel/include/quest_bits.h"
#include <files.h>
#include <macros.h>

int     given_away;
string  dropped_by_wiz,
        cloned_by_wiz;

#define SPEED 50

void
create_terel_armour()
{
    set_name("boots");
    set_short("pair of black boots");
    set_pshort("pairs of black boots");
    set_long("It's a black boots with grey linings.\n");
    set_adj(({"black"}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({55,"enchantment"}));
    add_prop(OBJ_S_WIZINFO,"The boots are of elven make made for "+
                   "the taller people. Only beneficial to elves, half-elves, "+
                   "and humans. They recieve 100 quickness from the "+
                   "boots. The boots are found on Trevin, the assassin "+
                   "in Last. /d/Terel/last/npc/assassin.c.\n");

    add_prop(MAGIC_AM_ID_INFO,({
             "The boots will endow members of the taller races with "+
             "a degree of speed.\n",70}));
    add_prop(OBJ_I_WEIGHT, 500);
    set_armour_size(ANY_SIZE);

    set_default_armour(20, A_FEET, 0, this_object());
}

mixed 
wear_terel_armour(object obj) 
{
     if(!TP->test_bit("Terel", QUEST_HAQ_GROUP, QUEST_HAQ_BIT))
         return 0;

     wearer->add_prop(LIVE_I_QUICKNESS, 
     wearer->query_prop(LIVE_I_QUICKNESS)+ SPEED);
    write("The "+short()+" pulse as you wear them.\n");
     return 0;
}

mixed 
remove(object obj)
{
   if(!TP->test_bit("Terel", QUEST_HAQ_GROUP, QUEST_HAQ_BIT))
       return 0;  
        
   wearer->add_prop(LIVE_I_QUICKNESS, wearer->query_prop(LIVE_I_QUICKNESS) - SPEED);
   return 0;
  /* If you want special remove messages put them here */
  /* and return 1 instead of 0.                         */ 
}

