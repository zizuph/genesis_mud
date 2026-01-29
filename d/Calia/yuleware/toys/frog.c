// OBJECT:  frog

    /* Calia Domain

    HISTORY

    [99-11-22] Created by Uhclem from [D:\CALIA\YULEWARE\TOYS\FROG.DOC].

    PURPOSE

    A toy to be found under the Christmas tree in the domain office in the
    Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_short("big rubber frog");
    set_name("frog");
    add_name("toy");
    add_adj("big");
    add_adj("rubber");

    set_long("The frog is made of soft but strong rubber, and" +
        " it's hollow so that it makes a deep resonating sound" +
        " when you thump it. With the exception of a couple" +
        " of big yellow painted eyes, its skin is deep green" +
        " and bumpy all over. It looks sturdy enough to" +
        " withstand some rough treatment.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_M_NO_SELL, "No merchant has room for something" +
        " this big and useless!\n");

    /*
     *  ITEMS    
     */

    add_item(({"eyes", "painted eyes", "eye", "painted eye"}),
        "The eyes are vivid yellow and quite large, giving the" +
        " frog a startled look as if someone had just stepped on him.\n");

    add_item(({"skin", "rubber"}),
        "The skin is strong but pliable and made of thick rubber" +
        " that resumes its shape no matter how often you squash it.\n");

}

// FUNCTIONS

// Function:  squash_frog

/*

Purpose:  compress the frog to make a rude noise.

Arguments:  string indicating this frog

Returns:  0/1

*/

int
squash_frog(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to squash. */

    {

        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp) + all_inventory(environment(tp)),
        "[on] %o", target))

    {

        if (target != this_object()) return 0;

        if (query_verb() == "squash")

        {

            say("SPPPPPPPLLLLLUUUUUUFPFPFPFPFPTTTTTT!\n" +
                QCTNAME(tp) + " makes a loud rude noise by" +
                " squashing a big rubber frog!\n" +
                "The frog makes an equally loud sucking sound as" +
                " it slowly resumes its normal shape.\n");

            write("SPPPPPPPLLLLLUUUUUUFPFPFPFPFPTTTTTT!\n" +
                "You make a loud rude noise by" +
                " squashing your big rubber frog!\n" +
                "The frog makes an equally loud sucking sound as" +
                " it slowly resumes its normal shape.\n");

        }

        else

            /*
             *  The alternative query_verb() as defined in init() is "step" 
             *  which requires that the frog be on the ground, not in the
             *  player's inventory.  It's also possible to have other values
             *  for query_verb() which use this routine - init() provides a 10%
             *  chance of stepping on the frog when a player enters a room in
             *  which it is lying on the ground.    
             */

        {

            if (environment() == this_player())

            {

                if (query_verb() != "unwrap" &&
                    query_verb() != "take" &&
                    query_verb() != "get")
                    write("You can't do that while you're holding it!\n");

            }

            else

            {

                say("PPPPPPFFPFPFPFPPFUUURRRRRRFFFFPFPFPFFPTTT!\n" +
                    QCTNAME(tp) + " emits - nay, blasts a" +
                    " rude resounding noise that assaults your" +
                    " senses as well as your sensibilities." +
                    " At " + tp->query_possessive() +
                    " feet, a flattened rubber toy makes a" +
                    " loud sucking sound as it returns to a" +
                    " shape resembling a frog.\n");

                write("PPPPPPFFPFPFPFPPFUUURRRRRRFFFFPFPFPFFPTTT!\n" +
                    "Hmmm... seems like there was quite a bit of" +
                    " air in that rubber frog you just stepped" +
                    " on. The air slowly returns to the flattened" +
                    " frog with a loud sucking sound.\n");

            }

        }

        return 1;

    }

    return 0;

}

// Function:  thump_frog

/*

Purpose:  thump the frog to make a little noise.

Arguments:  string indicating this frog

Returns:  0/1

*/

int
thump_frog(string str)

{

    object tp = this_player();
    object target;
    string sound = ({"gorp", "gurp", "barp", "borp"})[random(4)];

    if (!stringp(str)) /* Player did not specify what to thump. */

    {

        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " " + query_verb() + "s a big" +
            " rubber frog which responds by blurting '" + sound + "!'\n");

        write("You " + query_verb() + " the big" +
            " rubber frog which responds by blurting '" + sound + "!'\n");

        return 1;

    }

    return 0;

}

// Function:  init

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(squash_frog, "squash");
    add_action(squash_frog, "step");
    add_action(thump_frog, "thump");
    add_action(thump_frog, "hit");
    add_action(thump_frog, "slap");

    if (query_verb() != "drop"
        && query_verb() != "put"
        && query_verb() != "unwrap"
        && !random(10))
        squash_frog(query_name());

}
