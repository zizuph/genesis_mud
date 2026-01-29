/* Entrance door. ~solace/puzzle/doors/ent_door */

inherit "/std/door";

#include "../defs.h"
#include <macros.h>
#include <ss_types.h>

void create_door()
{
    set_name("ent_door");
    set_door_name(({"door", "metal door", "strong door", "strong metal door"}));
    set_door_desc("A very solid looking metal door in the north wall. Upon "+
        "it is the emblem of a tall disturbing human wearing a black hooded "+
        "cloak, hiding his face.\n");

    set_open(1);
    set_locked(0);

    set_door_id("entrance_door");
    set_other_room(LOCATIONS + "start");

    set_open_command("open");
    set_close_command("close");
    set_pass_command(({ "n", "north" }));

    set_open_desc("A strong metal door lies open to the north, above which "+
        "is a small light.\n");

    set_closed_desc("A strong metal door lies closed to the north, above "+
        "which is a small light.\n");

    set_open_mess(({"heaves the strong metal door open.\n", "The strong metal "+
        "door to the south is heaved open by someone in the other room.\n"}));

    set_close_mess(({"heaves the strong metal door shut.\n", "The strong metal"+
        " door to the south is heaved shut by someone in the other room.\n"}));
}

int
let_them_pass(string arg)
{
  int dexh;
  
  if (!other_door)
    load_other_door();
  
  /*
   * The times higher a player can be and still get through
   */
  dexh = 2 + (this_player()->query_stat(SS_DEX) / 25);
  
  if (open_status)
  {
    /* Lets say we arbitrarily can bend as dexh indicates.
     * For something else, inherit and redefine.
     */
    if ((int)this_player()->query_prop(CONT_I_HEIGHT) > 
	query_prop(DOOR_I_HEIGHT) * dexh) 
    {
      write("The " + door_name[0] + " is more than " + 
	    LANG_WNUM(dexh) + " times lower than you.\n" +
	    "You're too tall and " +
	    "not enough dexterous to get through.\n");
      return 1;
    }
    else if ((int)this_player()->query_prop(CONT_I_HEIGHT) > 
	     query_prop(DOOR_I_HEIGHT))
    {
      write("You bend down to pass through the " + short() + ".\n");
      tell_room(environment(this_object()),
		QCTNAME(this_player()) +
		" bends down to pass through the " +
		door_name[0] + ".\n", this_player());
    }
    
    this_player()->move_living(query_verb(), other_room, 1);
    /* Teams shouldn't follow! */
  }
  else
    write(check_call(fail_pass));
  
  return 1;
  
  /*   ::pass_door(arg);*/
}

void let_them_open_door(string arg)
{
    ::open_door(arg);
}

void let_them_close_door(string arg)
{
    ::close_door(arg);
}

int pass_door(string arg)
{
    object door, trapdoor1, trapdoor2;

    door = present("start_door", find_object(LOCATIONS + "start"));

    trapdoor1 = present("start_trapdoor", find_object(LOCATIONS + "start"));
    trapdoor2 = present("azazel_trapdoor", find_object(LOCATIONS + "azazel"));

    if(door->query_open())
    {
        if(objectp(find_object(LOCATIONS + "entrance")->query_occupied()))
        {
            TO->do_close_door();
            door->do_close_door();

            trapdoor1->do_open_door();
            trapdoor2->do_open_door();

            write("As you try to pass through the door, it slams in your "+
                "face!\n");
            say(QCTNAME(TP)+" tries to pass through the door but it slams "+
                 "in "+POSSESSIVE(TP)+" face.\n");

            tell_room(find_object(LOCATIONS + "start"), "The strong metal "+
                "door to the south slams shut and the trapdoor in the floor "+
                "creaks open.\n");

            tell_room(find_object(LOCATIONS + "azazel"), "The trapdoor in "+
                "the ceiling creaks open.\n");
        }
        else
        {
            let_them_pass(arg);

            set_alarm(0.5, 0.0, "say_stuff");

            clone_object(OBJECTS + "hands")->move(TP);

            find_object(LOCATIONS + "entrance")->set_occupied(TP);
            find_object(LOCATIONS + "azazel")->reset_puzzle_room();
        }
    }
    else
    {
        write("You walk into the closed metal door!\n");
        say(QCTNAME(TP)+" walks into the closed metal door.\n");
    }

    return 1;
}

int open_door(string arg)
{
    object trapdoor1, trapdoor2;

    trapdoor1 = present("start_trapdoor", find_object(LOCATIONS + "start"));
    trapdoor2 = present("azazel_trapdoor", find_object(LOCATIONS + "azazel"));

    if(!query_open())
    {
        trapdoor1->do_close_door();
        trapdoor2->do_close_door();

        tell_room(E(trapdoor1), "The trapdoor in the floor slams shut.\n");
        tell_room(E(trapdoor2), "The trapdoor in the ceiling slams shut.\n");
    }

    let_them_open_door(arg);
    return 1;
}

int close_door(string arg)
{
    object trapdoor1, trapdoor2;

    trapdoor1 = present("start_trapdoor", find_object(LOCATIONS + "start"));
    trapdoor2 = present("azazel_trapdoor", find_object(LOCATIONS + "azazel"));

    if(query_open())
    {
        trapdoor1->do_open_door();
        trapdoor2->do_open_door();

        tell_room(E(trapdoor1), "The trapdoor in the floor creaks open.\n");
        tell_room(E(trapdoor2), "The trapdoor in the ceiling creaks open.\n");
    }

    let_them_close_door(arg);
    return 1;
}

int say_stuff()
{
    write("\nYou are suddenly bathed in a soft blue light!\n");
    write("A mysterious voice mumbles: In this area you are only "+
        "allowed to carry one item at a time. Your belongings will "+
        "be stored in a safe place.\n");
    return 1;
}
