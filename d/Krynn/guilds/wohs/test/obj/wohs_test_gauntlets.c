/* WoHS gauntlets for npcs in the WoHS Test, Arman Dec 2017 */

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

public void
create_armour()
{
    set_name("gauntlets");
    set_pname("gauntlets");
    add_name(({"armour"}));
    set_ac(35); 
    set_am( ({ -2, 3, -1 }) );
    set_at(A_ARMS);
    add_adj( ({ "imperial", "engraved" }) );
    set_short("pair of imperial gauntlets");
    set_pshort("pairs of imperial gauntlets");
    set_long("This fine pair of gauntlets appears to be have once " +
        "belonged to an imperial cavalier of the Ergothian army. It " +
        "is constructed of high-quality steel and offers good " +
        "protection.\n");
    add_prop(OBJ_I_VOLUME, 4000); 
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(40, A_ARMS));
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(40));

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
