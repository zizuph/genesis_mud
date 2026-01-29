/*
 * An illusionary weapon created as part of the Test of High Sorcery
 * It will vanish shortly after leaving the Test, and cannot be sold.
 */
 
inherit "/std/weapon";

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

create_weapon()
{
    set_name("shortsword");
    set_adj("thin");
    add_adj("steel");
    add_name("sword");
    set_short("thin steel shortsword");
    set_long("This is a two-foot length of sharpened cold steel, bladed " +
        "along one edge. Its blade is thin and designed for thrusting, but " +
        "it is so sharp that even the slightest touch with the edge could " +
        "sever a finger.\n");        

    set_hit(34);
    set_pen(28);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_ANYH);

    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(34, 33));
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