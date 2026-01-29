/* This file is /d/Gondor/common/npc/teamorc.c         */
/*                                                     */
/* This orc will attack anyone attacking a member      */
/* of his team                                         */
/* copied in parts from /doc/examples/mobiles/troll.c  */

inherit "/d/Gondor/common/npc/std_orc";

#define BS(message)	break_string(message, 75)

create_monster()
{
    ::create_monster();

    set_long(BS("A most evil creature. He is big and strong, and he "
        + "looks at you with death in his eyes..\n"));

    add_chat("It's dangerous on the plains!");
    add_chat("When the rohirrim find us, we're finished!");
    add_chat("Home to Isengard, Saruman's awaiting our report!");
    add_cchat("You'll be dead soon!");
    add_cchat("Too bad that we don't have the time to put it to death properly!");  

}
