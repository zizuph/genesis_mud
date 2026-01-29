/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:     6/4/99     pay bug fixed                   Maniac
                13/4/96     took out reset_room             Maniac
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
                24.12.20    removed wizard requirement to
                            pay                             Arman

    purpose:    get rid of drinks here
    exits:      north and east to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      punishment of people who make the lavatory dirty
                person who empties the box
                cleaner of lavatory
                attendant as real monster
                box as real object
                possibility to wash hands
    bug:        none known
*/


#pragma save_binary

#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include GUARD_INCLUDE

inherit "/std/room";

object * payers = ({0,0,0,0,0,0,0,0,0,0});      /* array of players who have paid
                                                   the fee */

object door_1;                                  /* Pointer to the doors */
object door_2;                                  /* Pointer to the doors */
object door_3;                                  /* Pointer to the doors */


string
poster()
{
   return 
      "Dear Customer:\n\n"
    + "   The town of Gelan is proud of the cleanliness of its lavatory.\n"
    + "   We hope that you leave this building as clean as you found it.\n"
    + "   The Government of Gelan will pursue every traveller who breaks\n"
    + "   this rule.\n"
    + "   Each customer of the lavatory has to pay a fee of \n"
    + "                       1 Gold Coin\n"
    + "   to guarantee the future support of the lavatory.\n"
    + "   When a cabin is occupied, you can knock at the door to tell\n"
    + "   the player to hurry up. To enter a cabin, just type the word\n"
    + "   written on the door.\n"
    + "   The customer is pleased to follow the following rules:\n\n"
    + "       - don't stay too long in the cabinet\n"
    + "       - only one person per cabin\n"
    + "       - use the right cabin\n"
    + "       - leave the cabin as you found it\n"
    + "       - don't write any texts on the walls\n"
    + "                                   Boxy Ballot, Mayor\n\n";
}



public void
create_room()
{
    /* doors */

    door_1 = clone_object(GELAN_DOORS + "lavatory_m");
    door_1->move(this_object());

    door_2 = clone_object(GELAN_DOORS + "lavatory_f");
    door_2->move(this_object());

    door_3 = clone_object(GELAN_DOORS + "lavatory_n");
    door_3->move(this_object());

    /* descriptions */

    set_short("Lavatory");
    set_long("You're inside the public lavatory of Gelan. The walls and "
          + "the floor are white tiled. Everything is well kept and clean "
          + "and there is only a faint smell here.\n"
          + "There is an important looking poster on the wall. Beneath "
          + "the poster is a small metal box.\n"
          + "Beside the box is a toilet attendant sitting on a chair.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 1);		/* this room is inside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_eastend_s","north","@@leave_lavatory");
    add_exit(GELAN_ROOMS + "square_corner_se","west","@@leave_lavatory");
    add_exit(GELAN_ROOMS + "square_fountain_e","northwest","@@leave_lavatory");

    /* items in the room */

    add_item(({"floor","ground","wall"}),"They are white tiled and very clean.\n");
    add_item(({"poster","sign","note"}), "@@poster");
    add_cmd_item(({"poster","sign","note"}), "read", "@@poster"); 
    add_item("box",BS("The box is made of metal and looks very hard to "
          + "break, so don't try it. A sign on the front of the box says: "
          + "'Use <pay fee> to pay the fee to use the lavatory. You "
          + "don't get any money back! All money paid is lost when you leave "
          + "the lavatory !'.\n"));
    add_item("door","You have to be more specific, which door do you mean?\n");
    add_item("lock","You have to be more specific, which lock do you mean?\n");
    add_item(({"attendant","toilet attendant"}),BS("She's responsible for "
          + "this lavatory. She controls if you pay and if you leave the "
          + "lavatory as clean as you found it.\n"));

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
    add_action("pay_fee","pay");
    add_action("knock_door","knock");
    ::init();

}

/*
 * Function name: pay_fee
 * Description:   puts player list of payers
 * Arguments:     none
 * Returns:       1 if OK, 0 for error
 */

int
pay_fee(string arg)
{

    string * argv;
    int i;

    if(!strlen(arg))
    {
        notify_fail("What do you want to pay ?\n");
        return 0;
    }

    argv = explode(arg, " ");

    if(argv[0] != "fee")
    {
        notify_fail("Don't know how to pay " + argv[0] + ".\n");
        return 0;
    }

    if (member_array(this_player(), payers) > -1) {
        notify_fail("You have already paid!\n"); 
        return 0; 
    } 

    /* OK, now the command was correct, now let the player pay */

    /* test if room in array */
    for(i = 0; i < 10; i++)
    {
        if(payers[i] == 0)
        {
            break;
        }
    }

    if(i > 9)
    {
        notify_fail("There are already too many people waiting to use "
       + "the lavatory. You decide to wait a little and try again later.\n");
        return 0;
    }


    if(!MONEY_ADD(this_player(), -144))
    {
        notify_fail("You don't have enough money, sorry.\n");
        return 0;
    }

    payers[i] = this_player(); 

    say(QTNAME(this_player()) + " puts some money in the box.\n");
    tell_object(this_interactive(), "You put the demanded fee in the box. "
          + "You're now allowed to use the lavatory.\n");
    return 1;

}


/*
 * Function name: leave_lavatory
 * Description:   player leaves lavatory, remove him from payers list
 * Arguments:     none
 * Returns:       always 0
 */

int
leave_lavatory()
{
    int i;

    for(i = 0; i < 10; i++)
    {
        if(payers[i] == this_player())
        {
            tell_object(this_player(),"You loose the money you paid in the "
          + "box, sorry.\n");
            payers[i] = 0;
        }
    }

    return 0;
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
 * Function name: query_paid
 * Description:   check if the specified player has pay the fee, remove him then
                  from paid list
 * Arguments:     player object to check
 * Returns:       1 if has paid, 0 if not
 */

int
query_paid(object player)
{

    int i;

    if(player->query_wiz_level())
        return 1;

    for(i = 0; i < 10; i++)
        if(payers[i] == player)
        {
            return 1;
        }

    return 0;
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
        notify_fail("Don't know how to knock " + argv[0] + argv[1] + ".\n");
        return 0;
    }

    if(argv[0] == "blue")
    {
        if(door_1->query_open())
            tell_object(this_player(),BS("Sorry, but the door is already open.\n"));

        tell_room(find_object(GELAN_ROOMS + "lavatory_male"),BS("Someone "
          + "knocks at your door. You'd better hurry a bit, seems that "
          + "someone is waiting.\n"));
        tell_object(this_player(),BS("OK, you knock on the blue door.\n"));
        say(QCNAME(this_player()) + BS(" knocks on the blue door.\n"));
        return 1;
    }

    if(argv[0] == "pink")
    {
        if(door_2->query_open())
            tell_object(this_player(),BS("Sorry, but the door is already open.\n"));

        tell_room(find_object(GELAN_ROOMS + "lavatory_female"),BS("Someone "
          + "knocks at your door. You'd better hurry a bit, seems that "
          + "someone is waiting.\n"));
        tell_object(this_player(),BS("OK, you knock on the pink door.\n"));
        say(QCNAME(this_player()) + BS("knocks on the pink door.\n"));
        return 1;
    }

    if(argv[0] == "green")
    {
        if(door_3->query_open())
            tell_object(this_player(),BS("Sorry, but the door is already open.\n"));

        tell_room(find_object(GELAN_ROOMS + "lavatory_neutral"),BS("Someone "
          + "knocks at your door. You'd better hurry a bit, seems that "
          + "someone is waiting.\n"));
        tell_object(this_player(),BS("OK, you knock on the green door.\n"));
        say(QCNAME(this_player()) + BS("knocks on the green door.\n"));
        return 1;
    }

    notify_fail("Don't know how to knock " + argv[0] + argv[1] + ".\n");
    return 0;

}

/*
 * Function name: remove_paid
 * Description:   remove player from list
 * Arguments:     object of player
 * Returns:       none
 */

void
remove_paid(object player)
{
    int i;

    for(i = 0; i < 10; i++)
        if(payers[i] == player)
            payers[i] = 0;

}

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
