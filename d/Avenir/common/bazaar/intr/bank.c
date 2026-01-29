// file name:
// creator(s):       Avenir Wizards
// purpose:
// note:
// changed:        Lilith  Dec 2004: updated banking fees
//                 Lucius, Jan 2008: Added Bank ID.
//                 Lucius, Jun 2011: Fixed enter_inv code.
//                 Lilith, Oct 2021: updated room props
// bug(s):
// to-do:

inherit "/std/room";
inherit "/lib/bank";

#include <money.h>
#include <cmdparse.h>
#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/include/relation.h"

object banker, bin;

void
reset_room()
{
    if (!banker)
    {
	banker = clone_object("/d/Avenir/common/bazaar/NPCS/banker");
	banker->move_living("xxx", TO);
    }
    if (!bin)
    {
	bin = clone_object("/d/Avenir/common/obj/trash_can");
	bin->move(this_object());
    }
}

void
fee()
{
    if (QRACE(TP) == "hobbit" || QRACE(TP) == "minotaur" || 
      QRACE(TP) == "kender" || QRACE(TP) == "orc" || 
      QRACE(TP) == "ogre" ||  QRACE(TP) == "hobgoblin")
    {
	set_bank_fee(25);
	config_trade_data();
	return;
    }
    else
    {
	set_bank_fee(15);
	config_trade_data();
	return;
    }
}

public void
create_room(void)
{
    set_short("Bank of Sybarus");
    set_long("This is a stately setting worthy of the grand institution "+
      "that is the Bank of Sybarus.  "+
      "From the glass dome high above, the light from the Source "+
      "shines through, casting a soft, misty glow upon the gold-leaf "+
      "ceiling.  The floor is a polished expanse of black marble " +
      "so broad that the green carpet running from the door up to "+
      "the banking counter seems little more than a slender blade of "+
      "grass.  The beautiful workmanship of the counter makes it "+
      "a worthy focal point of the room, rising as it does with "+
      "the striking white purity of alabaster from the dark floor.  "+ 
      "A copper plaque rests upon the pristine surface of the counter, "+
      "and behind it a tapestry hangs.\n");

    add_item("counter", "This counter is made from purest alabaster. " +
      "It has an simple but very elegant design.\n");
    add_item("floor", "The black marble floor has streaks of green in it. \n");
    add_item(({"tapestry", "large tapestry"}), "A work of such quality "+
      "as can be achieved only by master weavers.  It depicts the "+
      "prosperity of the Faithful under the care and guidance of the "+
      "Gods.  Along the bottom border of the tapestry can see words "+
      "picked out in gold thread.\n");
    add_item(({"carpet", "rug", "runner"}), "It is made from the hair "+
      "of the sybarus goat, dyed a vivid green, and finely woven.\n");
    add_item(({"walls", "wall"}), "The walls are made from white limestone.\n");
    add_item("plaque", "It tells you how to exchange your money.\n");
    add_cmd_item("plaque", "read", "@@standard_bank_sign");
    add_cmd_item(({"tapestry", "sign", "words"}), "read", "@@do_banner");
    add_item(({"light", "above", "ceiling", "source", "Source", "dome" }),
      "White light from the source passes through the glass dome.\n");

    config_default_trade();
    config_trade_data();

    object gndep = clone_object("/d/Genesis/obj/deposit");
    gndep->set_short("deposit");
    gndep->set_bank_id(3901, "Sybarus Bazaar");
    gndep->set_no_show_composite(1);
    gndep->move(this_object());

    add_exit(EXTR + "str2.c", "west", 0);
	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.
    add_prop(ROOM_M_NO_ATTACK, "You get a feeling that the god Nitikas "+
	    "disapproves of fighting in this place.");
	add_prop(ROOM_M_NO_MAGIC_ATTACK, "You get a feeling that the god Nitikas "+
	    "disapproves of fighting in this place.");
    reset_room();
}

int
change(string str)
{
    fee();
    return ::change(str);
}

int
test(string str)
{
    fee();
    return ::test(str);
}

int
minimize(string str)
{
    fee();
    return ::minimize(str);
}

int
do_banner()
{
    write("      Sybarus welcomes you.\n\n"+
      "      Surface-dwelling grotesques: Your banking fee is 25%\n\n"+
      "      All others: Your transaction fee is but 15%\n"+
      "\n");
    return 1;
}

string
standard_bank_sign()
{
    fee();
    do_banner();
    return ::standard_bank_sign();
}


void
init()
{
    ::init();
    bank_init();
}

private void
post_enter_inv(object ob, object from)
{
    if (!present(ob, TO) || !present(banker, TO))
	return;

    if (IS_INFIDEL(ob))
    {
	ob->catch_msg(QCTNAME(banker)+ " bustles forward and shoves "+
	    "you out the door.\n");
	tell_room(TO, QCTNAME(banker) +" bustles forward and "+
	  "shoves "+ QTNAME(ob) +" out the door.\n", ob);
	ob->command("$west");
	banker->command("$shout Guards! We have an infidel outside "+
	    "the bank!");
    }
    else
    {
	tell_object(ob, "You glide across the dark marble floor to the "+
	  "counter.\n");
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (living(ob) && (ob != banker))
	set_alarm(0.0, 0.0, &post_enter_inv(ob, from));
}

