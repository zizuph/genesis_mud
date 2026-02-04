/*  A sign */

/*
    ... indeed, the sign at the entrance to Ribos.

    Modified 3 May 2003, by Bleys
        - added a read action and supporting functions read_sign()
            and sign_text()
        - changed the long of the sign to use sign_text()
        - now includes the Terel defs
*/

#include "/d/Terel/include/Terel.h"

inherit "/std/object";
#include <stdproperties.h>

// Function prototypes.
public int read_sign(string arg);
string sign_text();


void
init()
{
    ::init();

    add_action(read_sign, "read");

}


create_object()
{
   set_name("sign");
   set_adj("welcome");
   set_short("A sign in the middle of the road");
   set_long("The sign reads:\n\n@@sign_text");

   add_prop(OBJ_I_NO_GET, 1);
}


public int
read_sign(string arg)
{

    string text = sign_text();

    if (arg != "sign")
    {
        return 0;
    }

    write(text);
    return 1;
}


string
sign_text()
{
    return "Welcome one and all to the Kingdom of Ribos. I," +
        " King Bor-El, sincerely hope you enjoy your visit." +
        " Please leave our citizens in peace, because I would" +
        " hate to have to send my knights out into the street." +
        " Ribos was founded many years ago, and currently has" +
        " a population of 552.\n";
    // 552? Some "kingdom."
}
