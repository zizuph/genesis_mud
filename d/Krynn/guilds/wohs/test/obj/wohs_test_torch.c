/*
 * An illusionary object created as part of the Test of High Sorcery
 * It will vanish shortly after leaving the Test, and cannot be sold.
 */
 
inherit "/std/torch";

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"


void
check_if_in_test()
{
    set_alarm(180.0, 0.0, "do_i_dispel");
}

void
remove_illusionary_sword()
{
   remove_object();
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
         set_alarm(0.3, 0.0, "remove_illusionary_sword");
      }
      else
	set_alarm(180.0, 0.0, "do_i_dispel");

    return;
}

create_torch()
{
    set_name("torch");
    set_short("wooden torch");
    set_long("A standard torch of some wood that you don't recognise. "+
         "it creates an impressive amount of light.\n");       
    set_strength(5);

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
