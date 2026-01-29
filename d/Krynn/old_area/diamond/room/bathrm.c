/*
   Diamond

    bathrm.c
    --------

    Coded ........: May 1997
    By ...........: Kentari

    Latest update : May 1997
    By ...........: Kentari


 Taken virtually directly from the lavatory in gelan: 
    coder(s):   Merlin

    history:    13/4/96     took out reset_room             Maniac
                31.5.95     Corrections                     Maniac
                16. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 2. 1.93    unable to knock on open door    Merlin
                26.12.92    pink, green door installed      Merlin
                22.12.92    installed door, open door       Merlin
                21.12.92    descs, pay functions            Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin
*/


#pragma save_binary

#include <stdproperties.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit IN_BASE;

object door_1;                                  /* Pointer to the doors */
object door_2;                                  /* Pointer to the doors */
object door_3;                                  /* Pointer to the doors */


string
poster()
{
   return 
      "Dear Customer:\n\n"
    + "   The Diamond City is proud of the cleanliness of its lavatory.\n"
    + "   We hope that you leave this building as clean as you found it.\n"
    + "   The Diamond City will pursue every traveller who breaks this\n"
    + "   rule.\n"
    + "   When a cabin is occupied, you can knock at the door to tell\n"
    + "   the player to hurry up. To enter a cabin, just type the word\n"
    + "   written on the door.\n"
    + "   The customer is pleased to follow the following rules:\n\n"
    + "       - don't stay too long in the cabin\n"
    + "       - only one person per cabin\n"
    + "       - use the right cabin\n"
    + "       - leave the cabin as you found it\n"
    + "       - don't write any texts on the walls\n"
    + "                                -The Janitors of Diamond City\n\n";
}



void
create_dim_room()
{

    /* doors */

    door_1 = clone_object(DIDOORS + "lavatory_m");
    door_1->move(this_object());

    door_2 = clone_object(DIDOORS + "lavatory_f");
    door_2->move(this_object());

    door_3 = clone_object(DIDOORS + "lavatory_n");
    door_3->move(this_object());

    /* descriptions */

    set_short("The Bathroom of Diamond City");
    set_long("You're inside the bathroom of Diamond City. The walls and "
          + "the floor are white tiled. Everything is well kept and clean "
          + "and there is only a faint smell here.\n"
          + "There is an important looking poster on the wall, and plaque "
	  + "thanking the kindly plumbers of Gelan for allowing use of "
	  + "their invention.\n");

    /* exits */

    add_exit(DIROOM + "se1", "northwest", 0);

    /* items in the room */

    add_item(({"floor","ground","wall"}),"They are white tiled and very clean.\n");
    add_item(({"poster","sign","note"}), "@@poster");
    AI("plaque", "It thanks the kindly plumbers of Gelan in Calia for " +
	"allowing use of their invention to the Diamond City.\n");
    add_cmd_item(({"poster","sign","note"}), "read", "@@poster"); 
    add_item("door","You have to be more specific, which door do you mean?\n");
    add_item("lock","You have to be more specific, which lock do you mean?\n");

} /* create_room */

/*
 * Function name: init
 * Description:   add_commands to the player
 * Arguments:     none
 * Returns:       none
 */

void
init()
{
    add_action("knock_door","knock");
    ::init();
}

/*
 * Function name: clean_up
 * Description:   own clean_up routine
 * Arguments:     none
 * Returns:       none
 */

void
clean_up()
{

    door_1->remove_door_info(this_object());
    door_1->remove_object();

    door_2->remove_door_info(this_object());
     door_2->remove_object();

    door_3->remove_door_info(this_object());
    door_3->remove_object();

    ::clean_up();
}

/*
 * Function name: exa_blue_lock
 * Description:   string when looking at door
 * Arguments:     none
 * Returns:       string desc of lock
 */

string
exa_blue_lock()
{

    return door_1->exa_lock();

}

/*
 * Function name: exa_pink_lock
 * Description:   string when looking at door
 * Arguments:     none
 * Returns:       string desc of lock
 */

string
exa_pink_lock()
{
    return door_2->exa_lock();
}

/*
 * Function name: exa_green_lock
 * Description:   string when looking at door
 * Arguments:     none
 * Returns:       string desc of lock
 */

string
exa_green_lock()
{
    return door_3->exa_lock();
}

/*
 * Function name: knock_door
 * Description:   a player wants another player in a cabin to hurry up
 * Arguments:     none
 * Returns:       1 if ok, 0 if not
 */

int
knock_door(string arg)
{

    string * argv;
    int i;

    if(!strlen(arg))
    {
        notify_fail("What do you want to knock ?\n");
        return 0;
    }

    argv = explode(arg, " ");

    if(argv[0] == "door")
    {
        notify_fail("You have to be more precise. Which door do you mean ?\n");
        return 0;
    }

    if(sizeof(argv) < 2)
    {
        notify_fail("Don't know how to knock " + argv[0] + ".\n");
        return 0;
    }

    if(argv[1] != "door")
    {
        notify_fail("Don't know how to knock " + argv[0] + " "
	+ argv[1] + ".\n");
        return 0;
    }

    if(argv[0] == "blue")
    {
        if(door_1->query_open())
            tell_object(this_player(),("Sorry, but the door is already open.\n"));

        tell_room(find_object(DIROOM + "lavatory_male"),("Someone "
          + "knocks at your door. You'd better hurry a bit, seems that "
          + "someone is waiting.\n"));
        tell_object(this_player(),("OK, you knock on the blue door.\n"));
        say(QCNAME(this_player()) + (" knocks on the blue door.\n"));
        return 1;
    }

    if(argv[0] == "pink")
    {
        if(door_2->query_open())
            tell_object(this_player(),("Sorry, but the door is already open.\n"));

        tell_room(find_object(DIROOM + "lavatory_female"), "Someone "
          + "knocks at your door. You'd better hurry a bit, seems that "
          + "someone is waiting.\n");
        tell_object(this_player(), "OK, you knock on the pink door.\n");
        say(QCNAME(this_player()) + "knocks on the pink door.\n");
        return 1;
    }

    if(argv[0] == "green")
    {
        if(door_3->query_open())
            tell_object(this_player(), "Sorry, but the door is already open.\n");

        tell_room(find_object(DIROOM + "lavatory_neutral"), "Someone "
          + "knocks at your door. You'd better hurry a bit, seems that "
          + "someone is waiting.\n");
        tell_object(this_player(),"OK, you knock on the green door.\n");
        say(QCNAME(this_player()) + "knocks on the green door.\n");
        return 1;
    }

    notify_fail("Don't know how to knock " + argv[0] + argv[1] + ".\n");
    return 0;
}
