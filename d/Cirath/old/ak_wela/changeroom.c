inherit "/lib/bank";
inherit "/std/room";
inherit "/d/Cirath/ak_wela/inherit/room_tell";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_room()
{
    config_default_trade();
    set_short("Yinaga's room of Exchange");
    set_long("You have just entered Yinaga's bank back office. This is "+
             "where you can change money into other, more valueable coinage. " +
             "All for a small fee of 17 %. Two gnomes sit in fortress-like, " +
             "little rooms, changing money for those who wants it.\n");
    add_exit(AK_WELA_DIR + "bank", "south", 0, 2);

    add_item(({"gnome","gnomes"}),"Theese gnomes looks even more heavily "+
             "fortified than the other one back south.\n");

    add_item("sign","@@standard_bank_sign");
    set_tell_time(90);
    add_tell("A greedy looking man with beady eyes hurries past you to the "+
             "south, carrying two small pouches clenched in his fists.\n");
    add_tell("The gnome screams WHAT ?! A loan ?? "+
             "Are you out of your mind ? We do NOT do charity!" +
             "\nA man hurries away from the counter with an embarrased smile "+
             " upon his lips.\n");
    add_tell("The gnome shouts: There you are sir , 250 platinum, as agreed!"+
             "\nA man hurries away from the counter with a panicky look in his eyes.\n");
    add_tell("You feel something bump into you and with horror you check "+
             "your purse. Luckily all is there.\n");

    set_bank_fee(17);
    
    config_trade_data();
}


void enter_inv(object what , object from)
{
	start_room_tells(what);
	::enter_inv(what,from);
}

void init()
{
        ::init();
	bank_init();

}
