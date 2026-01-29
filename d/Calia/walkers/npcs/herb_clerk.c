
inherit "/std/creature";
inherit "/lib/trade";
inherit "/d/Calia/std/remember";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include <files.h>
#include "defs.h"

#define NUM sizeof(MONEY_TYPES)

#pragma save_binary

void
create_creature()
{
    set_name("Belos");
    add_name("belos");
    set_adj(({"ancient","white-robed"}));
    set_race_name("human");

    set_stats(({100,100,100,100,100,100}));
    set_alignment(0);
    set_skill(SS_DEFENCE,100);
    default_config_trade();
}

void
init_living()
{
    ::init_living();
    add_action("do_buy","buy");
}

int
do_buy(string str)
{
    object item;
    string str2,str3;
    int *arr, price, num,iprice;
    switch(str)
    {
        case "vial":
            item = clone_object(POTION_VIAL_OBJECT);
            iprice = 144;
            break;
        case "gloves":
            item = clone_object("/d/Calia/sea/objects/herb_gloves");
            iprice = 24;
            break;
        case "herbpouch":
            item = clone_object("/d/Calia/sea/objects/herbpouch");
            iprice = 24;
            break;
        case "herbjar":
            item = clone_object("/d/Gondor/common/guild/obj/herbjar");
            iprice = 24;
            break;
        default: 
            NF("I don't have any items named "+str+".\n");
            return 0;
    }
    price = iprice;
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
       return 0;  /* pay() handles notify_fail() call */
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
       write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("You get a "+item->short()+".\n");
    say(QCTNAME(TP)+" gets a "+item->short()+".\n");
    if(item->move(TP))
    {
        write("Its too heavy, and you drop it.\n");
        item->move(environment(TP));
    }
    return 1;
}
