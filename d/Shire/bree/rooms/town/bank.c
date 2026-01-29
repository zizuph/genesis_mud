/*
 * Based on the Dwarfheim bank. The bank fee randomly changes. 
 * If the fee is less than 5%, then the fee is set to 10%. 
 * The max fee is 35%.
 * -- Finwe, May 2001
 *
 * Bank rate changes periodically instead of when game reboots
 * -- Finwe March 2005
 *
 * Palmer 18 June 2006 - Changed 'out' exit to 'west' 
 *
 * Updated bank to handle gems, bank num is 1201
 * -- Finwe January 6 2008
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/room";
inherit "/lib/bank";

#include "/d/Shire/private/shire_admin.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "defs.h"

#define BANK_RATE_LOG   "/d/Shire/bree/bank_rate_log"
/* number of 'days' or room resets. when it reaches day_max,
 * time for a new bank rate. 17 days is approx 1 RL day
 */
int day_count = 0,
    day_max = 40;

void log_bank_rate(string str);

void
create_shire_room()
{
    object deposit = clone_object("/d/Genesis/obj/deposit");
    
    deposit->set_bank_id(1201, "Bree");
    deposit->move(this_object(), 1);

    config_default_trade();

    set_short("Bank of Bree");
    set_long("This is the Bank of Bree. The building is solid " +
        "looking with bars on the windows. The people of Bree " +
        "come here to keep their money safe from thieves. Everyone " +
        "in the town agrees it is the safest place to store their " +
        "extra money, and have recently opened it to travellers to " +
        "use. Behind the counter is the banker, a trustworthy " +
        "looking human. There is a plaque and a sign on the wall.\n");

    add_item(({"counter", "large counter"}),
        "The counter is made from a single piece of wood. It is " +
        "a deep honey color and gleams from constant polishing.\n");
    add_item(({"banker"}),
      "The banker looks busy as he looks over his books. He " +
      "looks well preserved and ready to assist you.\n");
    add_item(({"bars", "grates", "window bars", "bars on the windows"}),
        "The bars on the windows are made of steel and look solid. " +
        "They run horizontally, and protect the bank from robbers.\n");
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(ROAD_DIR + "broad03","west",0,1);

    add_item("plaque","@@standard_bank_sign");
    add_cmd_item("plaque","read", "@@standard_bank_sign");

// sets initial bank rate at reboot
    bank_fee=random (35);
    if(bank_fee<5)
        bank_fee=11;

    set_bank_fee(bank_fee);
    log_bank_rate("Game Reboot ");

    config_trade_data();

//    room_add_object("/d/Genesis/obj/deposit");

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
            bank_fee=11;
        set_bank_fee(bank_fee);
        day_count=0;

        log_bank_rate("Normal Cycle");
//    TELL_ADMIN(ctime(time()) + " Bree Bank rate at " + bank_fee);
        
    }
}

void log_bank_rate(string str)
{
    if (file_size(BANK_RATE_LOG) > 1000)
    {
	    rename(BANK_RATE_LOG, (BANK_RATE_LOG + ".old"));
    }
    write_file(BANK_RATE_LOG, (ctime(time()) + " "+ str + 
        " - Bree bank rate " + bank_fee+"%\n"));
}
