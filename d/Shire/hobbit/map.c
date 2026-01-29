#pragma save_binary

inherit "/std/object";
#include "/sys/stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "hobbit.h"

/*
 *
 * /d/Shire/hobbit/map- the needed object for the
 * entrance quest of the Adventuresome Hobbits.
 * Dunstable, 3-20-95
 *
 */

int gotten;
int alarm_id;

void
create_object()
{

   set_short("very fine map");
   set_long("This very fine map has been drawn with painstaking "+
   "care and great attention to detail.  At the top the legend is written:\n"+
   "Middle Earth: The lands where hobbits have travelled.\n"+
   "Across the center of the map is written: The Shire.\n"+
   "The scale at the bottom reads 1 foot = 50 leagues.\n"+
   "A rough estimation of the size of the map leads you to "+
   "conclude that the map covers about seventy-five leagues.\n");
   set_adj(({"very","fine"}));
   set_name("map");
   add_name("_hobbit_map_");
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_VALUE, 0);

   gotten = 0;

//   set_alarm(itof(2700 + random(1800)),itof(2700 + random(1800)),"do_decay");
      /* 2700 is 45 mins and 1800 is 30 mins */
       alarm_id = set_alarm(5.0,15.0,"do_decay");  /* Let's test ;) */

}

int
query_gotten()
{
   return gotten;
}


void enter_env(object dest, object old)
{

    object *obs;
    int i, change;

    ::enter_env(dest, old);

    obs = all_inventory(dest);

    change = 0;

    for (i = 0; i < sizeof(obs); i++)
    {
        if (obs[i]->id("_hobbit_map_") && obs[i] != this_object())
        {
            obs[i]->remove_object();
            change++;
        }
    }

    if (change)
        environment()->catch_msg("The maps glue themselves together!\n");

    if(!interactive(dest)) return;
    gotten = gotten + 1;
   if(!gotten < 2)
   {
    dest->add_prop("i_got_the_map",1);
    return;
   }

}
   