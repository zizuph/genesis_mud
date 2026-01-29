inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"

void
create_container()
{
    set_name("strongbox");
    set_adj("invisible");
    set_short("@@short_descr");
    set_long("@@long_descr");
    set_key(OGRE_MAGI_KEY);

    set_pick(70);

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
    add_prop(OBJ_I_INVIS, 1);

    add_item("lock", "The lock looks of dwarven make and quite " +
        "sophisticated. It would be very difficult to pick.\n");
}

/* Added to make the key break when the chest is unlocked.
 * This makes it more fair for people that are solving the
 * quest. Instead of people stock piling the equipment with
 * the same key, they now have to obtain the key from the magi.
 */
public int
do_default_unlock(string str)
{
  object* items;
  if(::do_default_unlock(str)==1){
    items = all_inventory(this_player());
    for(int i = 0; i<sizeof(items); i++)
    {
      if(items[i]->id("_ogre_magi_lair_key")){

        this_player()->catch_tell("As you try to remove the key from the "+
                                  "lock, the key breaks!\n");
        tell_room(environment(this_object()), "As "+QTNAME(this_player())+
                  " tries to remove the key from the lock, the "+
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
	write("You cannot put that into the strongbox.\n");
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
    return "invisible strongbox";
}

string
long_descr()
{
    return "This large chest is the strongbox of an ogre magi. Runes " +
       "of invisibility cover it, making it impossible to see without " +
       "magical assistance.\n";
}
