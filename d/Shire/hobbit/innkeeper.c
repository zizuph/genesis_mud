#pragma save_binary

#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "/d/Shire/common/defs.h"

inherit HOBBITMAKER;

void
create_hobbit()
{
    set_type(CITIZEN);
    set_power(40);
    set_name("hamilcar");
    set_title("Burrows, Inn-keeper of the Ploughed Field");
    add_adj(({"bouncy","energetic"}));
    set_long("This hobbit constantly bounces around.\n");
    set_race_name("hobbit");
    set_gender(0);
    disable_all_noise();
    add_act(({"bow","dance","bounce","giggle","panic"}));
    add_chat("Welcome! How are you. Try the brandywine!\n");
    add_chat("I have resently gotten a shipment of pipe-weed from "+
      "Longbottom in south farthing.\n");
    add_chat("Nothing but the finest pipe-weed is sold here to my valued "+
      "customers.\n");

    set_act_time(10);
    set_chat_time(5);
}
