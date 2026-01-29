
/*   
     A wooden rubbish bin which contains the trash items, some of which
     can be used in the gopheroo catching quest in Gelan.

    coder(s):   Maniac

    history:    12/4/98    rabbit -> gopheroo              Maniac
                19.1.95    only one useful item in bin now Maniac
                21.12.94   modified slightly               Maniac
                28.9.94    created                         Maniac

    purpose:    hold trash items; it gets emptied and refilled 
                periodically and alternately.

    to do:      none
    bug:        none known
*/


inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>
#include "object.h"
#include GOPHEROO_QUEST

#define EMPTY 0
#define FILLED 1

int bin_alarm = 0;
int bin_status = 0;


void
fill_or_empty_bin()
{
    object fish, carrot, net, club, bucket, *ob_list;
    int i;

    remove_alarm(bin_alarm);
    if (bin_status == FILLED)  {
      ob_list = all_inventory(this_object()); 
      if (!sizeof(ob_list)) {
          tell_room(environment(this_object()), "A burly dwarf " +
          "arrives, checks the bin for contents, sighs deeply " +
          "at a wasted journey, and leaves.\n");
          bin_status = EMPTY;
          bin_alarm = set_alarm(400.0, 0.0, fill_or_empty_bin);
          return;
      }
      for (i = 0; i < sizeof(ob_list); i++)
        {
          ob_list[i]->remove_object();
        }
      bin_status = EMPTY;
      tell_room(environment(this_object()), "A burly dwarf " +
                "arrives, empties the contents of the rubbish " +
                "bin into a large sack, then strides off.\n");
      bin_alarm = set_alarm(400.0, 0.0, fill_or_empty_bin);
      return;
    }
    else  {
      seteuid(getuid()); 
      fish = clone_object(GELAN_OBJECTS + "trash_fish");
      fish->move(this_object());
 
      /* Clone one of the useful items and set to good condition so 
         it can be used to catch the rabbit */
      switch (random(4))
      {
        case 0:
          carrot = clone_object(GELAN_OBJECTS + "trash_carrot");
          carrot->move(this_object());
          carrot->set_good_condition();
          break;
        case 1:
          net = clone_object(GELAN_OBJECTS + "trash_net");      
          net->move(this_object());
          net->set_good_condition();
          break;
        case 2:
          bucket = clone_object(GELAN_OBJECTS + "trash_bucket");
          bucket->move(this_object());
          bucket->set_good_condition();
          break;
        default:
          club = clone_object(GELAN_WEAPONS + "trash_club");
          club->move(this_object());
          club->set_good_condition();
          break;
      }
      bin_status = FILLED;  
      tell_room(environment(this_object()),
           "A citizen of Gelan arrives, throws some rubbish " +
           "into the rubbish bin, then wanders off back home.\n");
      bin_alarm = set_alarm(3200.0, 0.0, fill_or_empty_bin);
    }
}



void
r_bin()
{
  if (bin_alarm)
    return;
  bin_alarm = set_alarm(1.0, 0.0, "fill_or_empty_bin"); 
}



void
create_container()
{
    set_name("bin");
    set_pname("bins");
    set_short("large wooden rubbish bin");
    set_pshort("large wooden rubbish bins");
    set_adj(({"large", "wooden", "rubbish"}));
    set_long("This large wooden rubbish bin is here so " +
             "that Gelan can be kept as tidy as possible. " +
             "It is emptied quite frequently for sanitary " + 
             "reasons, so don't expect it to always contain " +
             "stuff, but when it does, a close look at what's " +
             "inside might reveal something useful.\n"); 

    add_prop(CONT_I_WEIGHT, 250000); 	/* grams */
    add_prop(CONT_I_MAX_WEIGHT, 400000); /* grams */
    add_prop(CONT_I_VOLUME, 250000); 	/* ml */
    add_prop(CONT_I_MAX_VOLUME, 400000); /* ml */

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_GET, "This bin is too large and heavy to " + 
                           "actually be picked up.\n");
 
}

