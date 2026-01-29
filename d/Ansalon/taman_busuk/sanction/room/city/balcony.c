/* dofficer room with board
 * every item dropped in the room is marked with the colour
 * of officer's branch and moved to proper rank after short delay
 * Modified by Torqual 19.02.2003
 */
/*
 * Louie April 2006 - Added rack.
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/guild/dragonarmy/guild.h"

#include <macros.h>

inherit SANCINROOM;


#define DA_BOARD_ITEM           "_dragonarmy_board_item"
#define DA_RED_ARMOURY          SRED + "armoury"
#define DA_BLUE_ARMOURY         SBLUE + "armoury"


int go_north();
int go_south();
int go_down();
void reset_sanction_room();
object rack_guard;

void
create_sanction_room()
{
    set_short("an opulent room for dragonarmy officers");
    set_long("@@long_descr");

    add_item(({"balcony","large balcony","floor","second floor",
	"area"}),
      "You stand on a balcony that overlooks the ground floor of " +
      "an inn in Sanction. This area has been opulently furnished.\n");
    add_item("furniture",
      "The finest furniture from all over Ansalon, both crafted and " +
      "plundered, has been used to fill this room with comforts fit " +
      "for any king.\n");
    add_item(({"balcony rail","rail"}),
      "A rail runs around the edge of the balcony to stop people " +
      "from falling to the floor below.\n");
    add_item("inn","You stand on a balcony in the finest inn in Sanction.\n");
    add_item("ground floor",
      "Beneath the balcony you stand on is the main room of this inn. A " +
      "haughty innkeeper quietly stands waiting for customers.\n");

    add_exit(SCITY + "inn", "down", go_down);
    add_exit(SCITY + "rda_ho_rack", "north", go_north);
    add_exit(SCITY + "bda_ho_rack", "south", go_south);
    
    clone_object(SOBJ + "officer_board")->move(this_object(), 1);    
    set_alarm(0.0, 0.0, &reset_sanction_room());
    //    clone_object(SOBJ + "rack")->move(TO,1);
}

void
reset_sanction_room()
{
    if (!objectp(rack_guard))
    {
        rack_guard = clone_object(SNPC + "rack_guard");
        rack_guard->move(TO,1);
    }
}


int go_down()
{
    if(present(rack_guard, this_object()) &&
       this_player()->query_prop("_don't_let_this_idiot_leave"))
    {
	rack_guard->command("say There is no way I am letting you leave, betrayer!");
	return 1;
    }
    return 0;
}

int go_north()
{
    
    if(present(rack_guard, this_object()) &&
       this_player()->query_prop("_don't_let_this_idiot_leave"))
    {
	rack_guard->command("say There is no way I am letting you leave, betrayer!");
	return 1;
    }

    if (this_player()->query_dragonarmy_division()=="red")
    {
	if(present(rack_guard, this_object()))
	{
	    rack_guard->command("say You may pass!");
	}
    }
    else
    {
	if(present(rack_guard, this_object()))
	{
	    rack_guard->command("say You have no business going in there!");
	    return 1;
	}
	else
	{
	  this_player()->catch_tell("You realize that your rack room is to " +
                                    "the south, not north.\n");
	  return 1;
	}
    }
    return 0;
}

int go_south()
{
    if(present(rack_guard, this_object()) &&
       this_player()->query_prop("_don't_let_this_idiot_leave"))
    {
	rack_guard->command("say There is no way I am letting you leave, betrayer!");
	return 1;
    }

    if(this_player()->query_dragonarmy_division()=="blue")
    {
	if(present(rack_guard, this_object()))
	{
	    rack_guard->command("say You may pass!");
	}
    }
    else
    {
	if(present(rack_guard, this_object()))
	{
	    rack_guard->command("say You have no business going in there!");
	    return 1;
	}
	else
        {
	  this_player()->catch_tell("You realize your rack room is to " +
                                    "the north, not south.\n");   
	  return 1;
	}
    }
    return 0;
}


string
long_descr()
{
    return "You stand on a large balcony, opulently furnished, " +
    "on the second floor of the finest inn in Sanction. This area " +
    "has been set up by the Dragon Highlord Ariakas as a place for " +
    "officers of the various armies " +
    "to gather in comfort. The balcony extends further to the " +
    "north and further to the south. Looking over the balcony " +
    "rail you can see the ground floor of the inn.\n";
}

void
enter_inv(object what, object from_whom)
{
   string color;

	if (IS_MEMBER(from_whom))
	{
		color = MANAGER->query_division(from_whom);
		if (!query_prop(DA_BOARD_ITEM))
		   what->add_prop(DA_BOARD_ITEM, color); 
	}

//	set_alarm(35.0, 0.0, &move_me_to_rack(what)); //we clean up the room

        ::enter_inv(what, from_whom);
}
