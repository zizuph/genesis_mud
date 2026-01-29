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
    set_name("greatsword");
    set_adj("heavy");
    add_adj("runed");
    add_name("sword");
    set_short("heavy runed greatsword");
    set_long("An incredible blade! This greatsword has a blade over a " +
        "meter in length, covered in runes glowing a furious red. So " +
        "sharp it looks it could carve though thick steel like " +
        "parchment - a sword rivalled by nothing you have seen before. " +
        "Wicked parrying hooks protrude just above its large guard, " +
        "with a heavy steel pommel balancing the weight of the blade " +
        "at the end of comfortably long two-handed handle.\n");       

    set_hit(60);
    set_pen(60);
    set_wt(W_SWORD);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 12500);
    add_prop(OBJ_I_VOLUME, 14000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(60, 60));

  add_prop(MAGIC_AM_MAGIC,({60, "enchantment"}));
  add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
  add_prop(MAGIC_AM_ID_INFO,({
    "The " + TO->query_short() + " appears to be magical in some way. ", 1,
    "This greatsword is an ancient relic of the Age of Dreams, rivalled " +
    "only by the greater Dragonlances!\n", 45 }));
  add_prop(OBJ_S_WIZINFO,"This is an illusionary sword wielded by the " +
    "the Duke in the WoHS Test. When it leaves the Test environment " +
    "it vanishes.\n");

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
