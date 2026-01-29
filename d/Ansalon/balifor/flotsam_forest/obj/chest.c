/* Navarre November 10, 2005: Added check to make key break on unlock. */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

object webnet;

void
create_container()
{
    set_name("chest");
    set_adj("grand");
    add_adj("oak");
    set_short("@@short_descr");
    set_pshort("grand oak chests");
    set_long("@@long_descr");
    set_key(CHEST_KEY);
/* I'm assuming the chest lock should be unpickable
 * (since 100 isn't an allowed value for set_pick)
    set_pick(100);
 */
    set_no_pick();
    add_prop(OBJ_I_VALUE,120);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP,0);
    add_prop(CONT_I_WEIGHT, 2500000);
    add_prop(CONT_I_VOLUME,7500);
    add_prop(CONT_I_MAX_WEIGHT, 22500);
    add_prop(CONT_I_MAX_VOLUME,20300);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);

    add_item("lock", "The lock looks so sturdy and thick that all you " +
         "might do it watch and admire. It also looks unpickable to you.\n");
}

/* Added to make the key break when the chest is unlocked.
 * This makes it more fair for people that are solving the
 * quest. Instead of people stock piling the armours with
 * the same key, they now have to solve the quest again
 * like any other player actually working on the quest.
 */
public int
do_default_unlock(string str)
{
  object* items;
  if(::do_default_unlock(str)==1){
    items = all_inventory(this_player());
    for(int i = 0; i<sizeof(items); i++)
    {
//      if(items[i]->query_short()=="elaborate key"){
      if(items[i]->id("_gdragon_lair_key")){

        this_player()->catch_tell("As you try to remove the key from the "+
                                  "lock, the elaborate key breaks!\n");
        tell_room(environment(this_object()), "As "+QTNAME(this_player())+
                  " tries to remove the key from the lock, the elaborate "+
                  "key breaks!\n", this_player());
        items[i]->remove_object();
        break;
      }
    }
    return 1;
  }
return 0;
}

void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the chest.\n");
	return;
    }
    ::enter_inv(obj,from);
}


void
leave_inv(object obj, object to)
{
    ::leave_inv(obj,to);
}


string
short_descr()
{
    return "grand oak chest";
}

string
long_descr()
{
    return "This is a great long chest, made of fine oak " +
    "and bound in iron. Covering the oak chest are grand " +
    "carvings of warriors in battle, although some of the " +
    "detail seems to have begun to rot away in the damp air " +
    "of the cavern.\n";
}
