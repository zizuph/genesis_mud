/*
** Dwarven Mining Company Bank
** Created by Leia
** February 15, 2005
*/

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/room";
inherit "/lib/bank";

#include "/d/Shire/private/shire_admin.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "../defs.h"

#define BANK_RATE_LOG   "/d/Shire/greymount/dwarf_area/bank_rate_log"
/* number of 'days' or room resets. when it reaches day_max,
 * time for a new bank rate. 17 days is approx 1 RL day
 */
int day_count = 0,
    day_max = 17;

void log_bank_rate(string str);

void
create_shire_room()
{

    config_default_trade();

    set_short("Dwarven Mining Company Money Deposit");
    set_long("This is the money deposit for the Dwarven Mining Company. Seeing as dwarves do not fully trust anyone with their gold, they have set up a local branch of the Dwarves of Genesis, an little known affiliated section of the Gnomes of Genesis.\n");
    add_item(({"counter", "large counter"}),
        "The counter has been carved from the room itself, rising out of the floor and running from wall to wall.\n");
    add_item(({"banker"}),
      "A burly greedy-looking dwarf with a long beard. The banker looks at you from behind the counter. He seems ready and able to assist you in any way.\n");
    
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(DT17, "south");

    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

// sets initial bank rate at reboot
    bank_fee=random (35);
    if(bank_fee<5)
        bank_fee=8;

    set_bank_fee(bank_fee);
    log_bank_rate("Game Reboot ");

    config_trade_data();

    room_add_object("/d/Shire/greymount/dwarf_area/dwarf_deposit");
    object deposit = present("deposit", this_object());
    remove_my_desc(deposit);
    add_my_desc("There is a dwarf money deposit here.\n");
	
    reset_shire_room();
}

void
init()
{
    ::init();
    bank_init();

}

void reset_shire_room()
{
    if(day_count<day_max)
    {
        day_count = day_count +1;
    }
    else if(day_count>=day_max)
    {
        bank_fee=random (35);
        if(bank_fee<5)
            bank_fee=8;
        set_bank_fee(bank_fee);
        day_count=0;
 
        log_bank_rate("Normal Cycle");
        
    }
}

void log_bank_rate(string str)
{
    if (file_size(BANK_RATE_LOG) > 50000)
    {
            rename(BANK_RATE_LOG, (BANK_RATE_LOG + ".old"));
    }
    write_file(BANK_RATE_LOG, (ctime(time()) + " "+ str + 
        " - Dwarven Mining Company Bank Rate " + bank_fee+"%\n"));
}