
/* 	
    This is the bank in the town Gelan

    coder(s):   Glykron & Maniac

    history:    16-02-08    added bank ID,                  Mercade
                  6/6/97    if you attacked gelan you can't bank, Maniac     
                20.12.94    leave_inv for number quest      Maniac
                    8.94    mobile handler code added       Maniac
                12. 2.93    path/guard object installed     Merlin
	        12. 2.93    last modified		    Glykron
                 5.12.92    created                         Glykron
                 6.11.92    installed help system           Merlin

    purpose:	change money here
    exits:      east to square, south to lockers
*/

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include GUARD_INCLUDE
#include NUMBER_QUEST

inherit GELAN_BASE_ROOM;
inherit "/lib/bank";

object keeper;


void
fix_keeper()
{
  keeper = clone_object(GELAN_MONSTERS + "ska");
  keeper->move(this_object());
  tell_room(this_object(), QCTNAME(keeper) + " arrives.\n");
}


void
reset_room()
{
  if (!keeper) fix_keeper();
}

int
south()
{
    if(TP->query_wiz_level())
    {
	write("You walk through the bars.\n");
	say(QCTNAME(TP) + " walks through the bars!\n");
	return 0;
    }
    write("Bars prevent you from proceeding south.\n");
    return 1;
}


public void
create_gelan_room()
{
    object bank;
    /* descriptions */

    set_short("Bank");
    set_long(
	"This is a rectangular room with sandstone walls that goes half as " +
	"far back as it is across and high.  The windows of this building " +
	"are barred, and the scent of money lingers in the air.  A plaque " +
        "hangs by the long well-protected counter.  " +
	"There is also an iron barred doorway to the south, leading " +
        "to the bank lockers.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 1);			/* this room is inside */

    /* exits */

    add_exit(GELAN_ROOMS + "banklockers", "south", "@@south");
    add_exit(GELAN_ROOMS + "square_westend_s", "east", 0);

    /* items in the room */


    add_item( ({"window", "windows"}), "The windows are guarded by thick " +
              "iron bars, adding to the fortified appearance of this place." +
              "\n");
               
    add_item( ({"wall", "walls"}), "The walls are made of thick " + 
              "sandstone.\n");

    add_item("plaque", "@@standard_bank_sign");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");

    add_item( ({ "counter", "iron-barred counter" }), BS(
	"You see no way to get behind the counter, since it is totally " +
	"enclosed by thick iron bars.  " +
	"\n"));

    config_default_trade();

    set_bank_fee(22); /* To set the exchange fee (% of changed amount) */

    config_trade_data();

    bank = clone_object("/d/Genesis/obj/deposit");
    bank->set_bank_id(1401, "Gelan");
    bank->move(THIS, 1);
    set_alarm(1.0, 0.0, "reset_room");
}


/* End the number game if the leaving player is playing it */
void
leave_inv(object ob, object to)
{
    int i;
    ::leave_inv(ob, to);
    if (keeper && (keeper->query_testing() == ob)) {
        keeper->reset_test();
        keeper->another_try(ob);
    }
}


int
check_keeper()
{

  if (keeper && present(keeper,this_object()))
    return 1;
  else
    return 0; 
}



/* Called when player pays some money */
void
bank_hook_pay(string text)
{
    TP->catch_msg("You pay " + text + " to " + QTNAME(keeper) + ".\n");
}


/* Called when a change text is supposed to be written */
void
bank_hook_change(string text)
{
    TP->catch_msg(QCTNAME(keeper)+ " gives you " + text + " back.\n");
}


/*
 * This function writes what the other players sees.
 */
void
bank_hook_other_see(int test)
{
    if (!test)
	say(QCTNAME(keeper) + " changes some of " + QTNAME(TP) + 
            "'s money.\n");
    else
	say(QCTNAME(this_player()) + " seems to calculate something.\n");
}


/*
 * Function name: bank_hook_already_minimized
 * Description:   Write this when your coins already are minimized
 */
void
bank_hook_already_minimized()
{
    keeper->command("say Your coins are already minimized, " + 
                    TP->query_nonmet_name());
}

/*
 * Function name: bank_hook_no_idea
 * Description:   When there is no idea to minimize since it will all be
 *   		  eaten up by the tax
 */
void
bank_hook_no_idea()
{
    keeper->command("say There is no point in minimizing " +
                    "your coins now, " + TP->query_nonmet_name());
}


/*
 * Function name: bank_hook_minimized
 * Description:   Player minimized his coins
 */
void
bank_hook_minimized(string pay_text, string got_text)
{
    TP->catch_msg(QCTNAME(keeper) + " minimized your coins.\n");
    say(QCTNAME(keeper) + " minimized " + QTNAME(TP) + "'s coins.\n");
}

int
attacked_town_check()
{
    if (this_player()->query_prop(ATTACKED_GELAN))  { 
        if (!keeper->command("say to " + this_player()->query_real_name() + 
                " No service for people who make trouble here!"))
            keeper->command("confused");  
        return 1;
    } 
    return 0;
}

/* Called for action to change some coins */
int
change(string str)
{
  if (!check_keeper())
    {
      NF("The banker is not here!\n");
      return 0;
    }
  else if (attacked_town_check())  
      return 1;
  else return ::change(str);
}


/* Called for minimize action */
int
minimize(string str)
{
  if (!check_keeper())
    {
      NF("The banker is not here!\n");
      return 0;
    }
  else if (attacked_town_check()) 
      return 1;
  else return ::minimize(str);
}


/*
 * Function name: init
 * Description:   adds actions
 * Arguments:     none
 * Returns:       nothing
 */
void
init()
{
    ::init();
    bank_init();
}
