// TEST JOINROOM

#pragma strict_types
#pragma save_binary

#include "/d/Terel/include/Terel.h"
#include "../lib/mages.h"
#include <ss_types.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;




void
create_room()
{
    string book;

    set_short("Joinroom for the mages");
    set_long("test joinroom for the mages.\n");

    book = "Here you can <sign name> to join or <leave guild> the Riders of " +
           "Last guild. " +
           "Members may also use <request sash> to replace their sashes. " +
           "You may also <list> to see what guilds you are already " +
           "a part of. Currently the guild tax is: " + GUILD_TAX  +
           "% however, this is subject to change later on.\n";
add_item("book",book);

    add_item(({"wooden benches","benches","bench"}),
       "The long wooden benches line up along " +
       "the walls.\n");
    add_item(({"large oak table","large table","table",
       "oak table"}),"You notice a large open book resting " +
       "on the table. Next to the book is a writing quill and " +
       "inkwell.\n");

    add_cmd_item("book", "read", book);
    add_cmd_item(({"inkwell","quill", "book"}), 
                 ({"take", "get"}), "Try <sign name> instead.\n");

    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
}


int
sign(string str)
{
    object sh;
    mixed why;

    if (str != "name")
    {
       NF("Sign what, you name maybe?\n");
       return 0;
    }

    /* Clone the shadow */

    setuid();
    seteuid(getuid());

    sh = clone_object(GUILD_SHADOW);

    /* See if this member is acceptable */
    if (stringp(why = sh->acceptable_member(TP)))
    {
        write(why);
    }
    else
    {

        /* Try to add the shadow to the player */
        switch (sh->add_occ_shadow(TP))
      {
            case 1:
                /* We have successfully shadowed the player, so we're set */
                TP->clear_guild_stat(7);
   
                write("you did something now you joined the mages, blah blah.\n");
               write("An imp pops in hands you a book then leaves the same way it came in. blah blah.\n");
                say(QCTNAME(TP) + " joins the mages. Fireworks explode, blah blah..\n");
        /*
                log_file("members", 
                    capitalize(TP->query_real_name()) +
                    " joined " + ctime(time()) + "\n");
        */

                return 1;
    
            case -4:
                /* The player has a race guild already, or one of his existing
                 * guilds has blocked this one.
                 */ 
                write("Your other guilds don't want you in this one!\n");
                break;
    
            default:
                /* Some error in shadowing */
                write("An error has prevented you from joining.\n");
                break;
        }
    }

    /* We couldn't shadow the player, so remove the shadow */
    sh->remove_shadow();
    return 1;
}



void
init()
{
    ::init();
    add_action(sign, "sign");
}
