/*
*    Key for the Heartroom of the crimson tower
*/
inherit "/std/key";
#include <formulas.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
check_if_in_test()
{
    set_alarm(180.0, 0.0, "do_i_dispel");
}

void
do_i_dispel()
{
    object room = TO;
    object person = TO;

    while(E(room))
      room = E(room);

    if(E(TO) != room)
      while(person && !(interactive(person)))
	person = E(person);

    if(room && file_name(room))
      if(file_name(room)[0..30] != "/d/Krynn/guilds/wohs/test/room/")
      {
         person->catch_msg("The " +TO->short()+ " dissipates! It was " +
             "nothing but an illusion!\n");
         set_alarm(0.3, 0.0, "remove_illusionary_item");
      }
      else
	set_alarm(180.0, 0.0, "do_i_dispel");

    return;
}

void
remove_illusionary_item()
{
   remove_object();
}


void
create_key() 
{
    ::create_key();
    set_name("key");
    add_name("_wohs_test_heartroom_key");
    set_short("shadowy key");
    set_adj("shadowy");
    set_long("This key doesn't feel to be of any real substance, like " +
        "a string of shadowy smoke swirling curiously in your hand.\n");

    set_key(8874654);
    add_prop("_key_i_no_keyring",1);
    add_prop(OBJ_M_NO_SELL, "@@no_sell_message"); 

    check_if_in_test();
}

string
no_sell_message()
{
    set_alarm(0.3, 0.0, "remove_illusionary_sword");
    return "As you attempt to sell the " +TO->short()+ " it dissipates! " +
        "It was nothing but an illusion!\n";
}
