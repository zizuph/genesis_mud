/* WoHS helm for npcs in the WoHS Test, Arman Dec 2017 */

inherit "/std/armour";
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

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
create_armour()
{
    set_name("helmet");
    add_name(({"armour","helm"}));
    set_pname("helmets");
    add_pname(({"armours","helms"}));
    set_ac(35);
    set_am( ({ 0, 1, -1 }) );
    set_at(A_HEAD);
    add_adj( ({ "hard", "steel" }) );
    set_short("hard steel helmet");
    set_pshort("hard steel helmets");
    set_long("This helmet is of imperial design, made from rigid steel. " +
             "It offers good protection for your head.\n");
    add_prop(OBJ_I_VOLUME, 2150);
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(35, A_HEAD));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35));

    add_prop(OBJ_M_NO_SELL, "@@no_sell_message"); 

    check_if_in_test();
}

string
no_sell_message()
{
    set_alarm(0.3, 0.0, "remove_illusionary_item");
    return "As you attempt to sell the " +TO->short()+ " it dissipates! " +
        "It was nothing but an illusion!\n";
}