/* Xak Tsorath coded by Percy 
 *
 * Added a cure for the plague here based on /d/Avenir/common/ships/bazaar/deck.c
 * Arman - 2017
 */

#include "xlocal.h"

inherit  XAKINROOM
inherit "/d/Krynn/solamn/guild/spells/chapel_base.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/OotS/defs.h"

void
create_xak_room()
{
    object door;
    
    set_short("The main chamber");
    set_long("You are standing in an huge circular chamber that stretches"
	     + " some 80 feet in diameter. The chamber walls are made of smooth"
	     + " white stone that soars up 80 feet to a domed ceiling. The"
	     + " chamber is given an extra appearance of size by its"
	     + " emptiness, the only thing of note in the chamber being"
	     + " a statue of Mishakal in the centre of the room. Various"
	     + " exits lead off from the chamber.\n");
    
    add_exit(TDIR + "tempstairs.c", "east", 0);
    add_exit(TDIR + "tempnorth.c", "north", 0);
    add_exit(TDIR + "tempsouth.c", "south", 0);
    add_exit(TDIR + "tempnwr.c", "northwest", 0);
    add_exit(TDIR + "tempswr.c", "southwest", 0);
    
    INSIDE;
    DARK;
    add_item(({"metal door", "door", "doors", "double door", "double doors", "metal doors"}), "@@doors");
    add_item(({"statue", "mishakal", "beautiful statue"}), "@@statue");
    
    door = clone_object(OBJ + "t_hall_doorb.c");
    door->move(TO);
    door->set_key(K_TEMPLE);
}

void
init()
{
    ::init();
   init_chapel();
      ADA("pick");
      ADA("knock");
}

int
pick(string str)
{
    NF("Pick what?\n");
    if ((str == "lock") || (str == "the lock") || (str == "door lock"))
      {
	  write("You try to pick the lock, but it is too complex for you.\n");
	  SAY(" is messing with the door lock.");
	  return 1;
      }
    return 0;
}

int
knock(string str)
{
    NF("Knock where?\n");
    if ((str == "on the door") || (str == "on the doors")
	|| (str == " on the double doors") || (str == "door"))
      {
	  write("You knock on the doors, the sound of your knocking " +
		"is swallowed up by the deathly silence of the city.....\n");
	  SAY(" knocks on the door very loudly.");
	  return 1;
      }
    return 0;
}

string
doors()
{
    write("These double doors are made of a strange silvery blue metal, they"
	  + " look very old and very very solid.\n");
    SAY(" studies the doors carefully.");
    return "";
}

string
statue()
{
    write("The statue is made of the same strange silvery blue metal"
	  + " that was used to create the doors. It is a beautiful work"
	  + " of art that seems almost lifelike, you can see why so many"
	  + " people chose to worship this goddess.\n");
    SAY(" examines the statue.");
    return "";
}


int
hilt_transformed(object ob)
{

      object blessing;

      if(ob->query_alignment() < 100)
      {
       ob->catch_tell("The blue-steel hilt crumbles to dust.\n");
       return 1;
      }


      if(random(4) == 1)
      {
       tell_room(TO, "\n\nSuddenly, the statue glows with a holy light! A voice as soft " +
       "as the wind whispers 'You have returned what was once lost and broken, " +
       "now let me restore it to its former glory!'\n\nThe statue ceases to glow... "+
       "you wonder if you imagined everything that has just transpired?\n");

       ob->catch_tell("The blue-steel hilt has been transformed into a holy blade!\n");
       clone_object("/d/Ansalon/dargaard/obj/weapon/mishakal_blade")->move(ob);
      }
      else
      {
       tell_room(TO, "\n\nSuddenly, the statue glows with a holy light! A voice as soft " +
       "as the wind whispers 'In return for this holy relic, I give you my blessings...' " +
       "\n\nThe statue ceases to glow... you wonder if you imagined everything that has " +
       "just transpired?\n");

       if (P("ansalon_bless_object",ob))
       {
         ob->catch_tell("The blue-steel hilt vanishes, however you notice no difference "+
         "to your blue aura.\n");
       }
       else
       {       
       ob->catch_tell("The blue-steel hilt vanishes.\n");
       blessing = clone_object("/d/Ansalon/dargaard/obj/mishakal_blessing");
       blessing->move(ob);
       blessing->remove_mish_obj();
       }
      }

       return 1;
}

int
cure_plague(object carrier, int inc)
{
    object ob;
	
    while(ob = present("nasty_sickness", carrier)) 
    { 
	ob->cure_poison( ({"all"}), 999 );   

	tell_room(TO, "\nSuddenly, the statue glows with a holy light!\nA voice as soft " +
       "as the wind whispers: 'With the return of the scourge of Chemosh, so too does the blessings " +
       "of Mishakal return...'\n\nThe statue ceases to glow... you wonder if you imagined " +
       "everything that has just transpired?\n");
	carrier->catch_tell("You feel as if you have been cleansed of the foul plague.\n");
	break;
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob))
    {
        if (P("_mishakal_blade_hilt",ob))
        {
            object hilt = P("_mishakal_blade_hilt",ob);
            hilt->remove_object();
            set_alarm(3.0, 0.0, &hilt_transformed(ob));
        }
    }

    if (living(ob))
    {
        if (P("nasty_sickness", ob))
        {
            set_alarm(3.0, 0.0, &cure_plague(ob, 0));
        }
    }

    if (living(ob))
    {
       if(IS_OOTS(ob))
       {
          if(!OOTS_QUERY_REV(TP, "mishakal"))
          {
            TP->catch_msg("\n\nYou find your mind suddenly filled with divine clarity as a " +
                            "revelation on the aspect of Mishakal manifests to you!\n\n\n");
            OOTS_ADD_REV(TP,"mishakal","the aspect of mishakal");  
          }
       }
    }

}

