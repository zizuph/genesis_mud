/*
* This is how a bank could look like
*
* Example made by Nick
*/

inherit "/std/room";
inherit "/lib/bank";

#define PATH "/d/Terel/mecien/valley/city/"

#include <stdproperties.h>

/*
* Function name: create_room
* Description:   Set up default trade and cofigure it if wanted.
   */
void
create_room()
{
   config_default_trade();
   
   set_short("Money Handler");
   set_long(break_string(
         "Bright and resonant, this domed hall is made of dark stone and " +
         "rich pine beams. The floor is a polished marble, swirled black " +
         "and gray. A large counter is built in the midst of the hall, made " +
         "of pine and stained gold. A gold sign hangs over the counter. " +
         "", 70) + "\n");
   
   add_item( ({ "sign", "instructions" }),
      "It is made of gold and covered with writing.\n");
   
   add_item("counter", "It is made of stained pine, golden. Behind it\n"
      + "all the transactions take place.\n");
   add_item("floor", "It is swirled marble, back and gray.\n");
   add_item("beams", "They are rich pine and support the dome.\n");
   add_item("dome", "It is a simple gray stone dome.\n");
   add_cmd_item( ({ "sign", "instructions" }), "read", "@@standard_bank_sign");
   
   add_exit(PATH + "street5", "west", 0);
   
   add_prop(ROOM_I_INSIDE, 1);
   
   set_bank_fee(30); /* To set the exchange fee (% of changed amount) */
   
   config_trade_data();
}

init()
{
   ::init();
   
   bank_init(); /* Add the bank commands */
}

/*
* A few hooks to get your own messages.
*
* These are the default texts, redefine them if you think you need. They
   * are only listed here as comments.
*
bank_hook_pay(text)
{
   write("You pay " + text + ".\n");
}

bank_hook_change(text)
{
   write("You get " + text + " back.\n");
}

bank_hook_other_see(test)
{
   if (!test)
      say(QCTNAME(this_player()) + " changes some money.\n");
   else
      say(QCTNAME(this_player()) + " seems to calculate something.\n");
}

bank_hook_already_minimized()
{
   write("Your coins are already minimuzed.\n");
}

bank_hook_no_idea()
{
   write("There is no idea for you to minimize your coins now.\n");
}

bank_hook_minimized()
{
    write("Your coins are now minimized.\n");
    say(QCTNAME(this_player()) + " minimizes" +
	this_player()->query_possessive() + " coins.\n");
}

*/

