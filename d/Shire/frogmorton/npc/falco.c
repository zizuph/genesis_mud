/*
 * The chief bounder in Frogmorton
 * Finwe, November 2000
 */

#include "/d/Shire/sys/defs.h"
#include HOBBIT_FILE

inherit HOBBITMAKER;

void
create_hobbit()
{
    set_family_name("Took");
    set_type(SHIRRIFFE);
    set_name("falco");
    set_title("Took, Chief Bounder of the East Farthing Troop " +
        "of the Watch");
    set_long("This is Falco Took, chief Bounder in the East " +
        "Farthing Troup of the Watch and seems to be busy with " +
        "some seemingly important business. He's responsible for " +
        "keeping the peace and making sure there no one causes " +
        "any mischief.\n");

    set_gender(0);
    add_act("smile");
    add_chat("Welcome to Frogmorton.");
    add_chat("Is there something I can help you with?");
    add_chat("If you see any shady characters, report them to me.");
    add_chat("We don't like strangers hanging around, so please " +
        "leave or I may call bounder to take you away.");
    add_chat("There are strange things happening in the Shire.");
    add_chat("Mungo sure knows how to have a good party.");
    add_chat("If you need to send a message, you can hire messengers here.");

    add_act(" shuffles some papers about his desk.");
    add_act(" looks over some documents.");
    add_act(" signs something and sets it aside.");
    add_act(" looks up at you.");
    add_act(" reads some new orders.");
    add_act(" chuckles happily.");

   
    set_act_time(2);
    set_chat_time(2);
   
    MAKE_MONEY;
    trig_new("%w 'introduces' %s", "react_introduce");
}
 
