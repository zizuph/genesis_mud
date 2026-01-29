inherit "/std/room";
inherit "/lib/pub";
inherit "/d/Cirath/ak_wela/inherit/room_tell";
#include "/d/Cirath/common/defs.h"


void
init()
{
    ::init();
    init_pub();
    add_action("sit_down", "sit");
}

void
create_room()
{
    set_short("The Sea Serpent Saloon");
    set_long("The dark saloon has several booths and tables, with a long " +
             "bar opposite the doorway.  The balcony on the upper level " +
             "currently holds many fair damsels who would love to spend " +
             "some time with a big handsome man.  A burly bouncer stands " +
             "before the stairway leading up to them, though, and another " +
             "one stands at the main door.  The bartender also appears to " +
             "be no slouch at being able to keep the peace in her " +
             "establishment.\n");
    add_item("sign", "Welcome, mateys!  ");
    add_cmd_item("sign","read",
                 "Welcome, mateys!  ");

    add_item("menu","This is a menu, it contains a list of drinks!\n");
    add_cmd_item("menu", ({ "read", "peruse" }),
"                    Sea Serpent Saloon Specials\n\n" +
"                    Beer    :     8 copper coins\n" +
"                    Ale     :    12 copper coins\n" +
"                    Mead    :    55 copper coins\n" +
"                    Whiskey :    76 copper coins\n" +
"                    Rum     :   260 copper coins\n" +
"\n\n Be careful not to upset the bouncers!\n");

    set_tell_time(20);
    add_tell("One of the fair young damsels on the balcony above you " +
             "waves coyly.  You feel certain her smile was aimed directly " +
             "at you.\n");
    add_tell("A beautiful redhead calls out from upstairs, \"Hey, big " +
             "fella!  Did you bring me back anything?\"\n");

    add_exit(AK_WELA_DIR + "brdwlk1", "east");

   
    add_drink(({ "beer", "small beer" }), "beer", "small",
               70, 4, 8, 0, 0,
               "A small but refreshing beer.\n", 0);
    add_drink(({ "ale", "tiny ale" }), "ale", "tiny",
               100, 6, 12, 0, 0,
               "A very dark and pleasant-tasting bitters.\n", 0);
    add_drink(({ "mead", "honey mead" }), "mead", "honey",
               50, 35, 55, 0, 0,
               "A rich honey mead, well aged.\n" , 0);
    add_drink(({ "whiskey", "malt whiskey" }), "whiskey", "malt",
               62, 25, 76, 0, 0,
               "A fine malt whiskey.\n", 0);
    add_drink(({"rum", "dark rum"}), "rum", "dark",
               84, 50, 260, 0, 0,
               "The finest rum anywhere, for the discriminating sailor.\n", 0);

    clone_object(AK_WELA_DIR + "npc/doorman")->move(TO);
    clone_object(AK_WELA_DIR + "npc/bouncer")->move(TO);
    clone_object(AK_WELA_DIR + "npc/barkeep")->move(TO);
}


