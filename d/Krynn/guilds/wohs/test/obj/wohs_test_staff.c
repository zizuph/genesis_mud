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
    set_name("staff");
    add_adj("archmage");
    set_short("staff of the archmage");
    set_long("This staff is made of the rare magical wood known " +
        "as ironwood, and is engraved with powerful runes of magic - " +
        "one of five powerful artifacts held by the Archmages who are " +
        "Masters of the Towers of High Sorcery.\n");       

    set_hit(40);
    set_pen(40);
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON);
    set_hands(W_BOTH);
    set_wf(TO);

    add_prop(OBJ_I_WEIGHT, 5500);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(60, 60));

  add_prop(MAGIC_AM_MAGIC,({60, "enchantment"}));
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_ID_INFO,({
    "The " + TO->query_short() + " appears to be magical in some way. ",1,
    "This staff is an ancient relic of the Age of Dreams, rivalled "+
    "only by the greater Dragonlances in magical power! It can "+
    "enhance the spellcasting ability of the wielder.\n", 45 }));
  add_prop(OBJ_S_WIZINFO,"This is an illusionary weapon held in the "+
    "Tower in the WoHS Test. When it leaves the Test environment "+
    "it vanishes. It doesn't provide any magical benefits, contrary "+
    "to its magic id description.\n");

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

void
wield_message()
{
    if(E(TO) != wielder)
	return;
    wielder->catch_msg("The staff of the archmage hums with magical power " +
      "as you wield it.\n");

}

mixed
wield(object what)
{
    wielder = TP;
    set_alarm(1.0, 0.0, "wield_message");
}
