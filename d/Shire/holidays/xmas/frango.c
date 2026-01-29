/*
 * Holiday food from Bree
 * Finwe, December 2002
 */
 
inherit "/std/food";
 
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"


create_food()
{
    setuid();
    seteuid(getuid());

    set_name("frango");
  //  add_name("frangos");
    set_adj("brown");
    set_adj("rich");
//    set_short("rich brown frango");
//    set_pshort("rich brown frangos");
    set_long("This is what the people of Bree call a frango. It is " +
        "a piece of dark chocolate lightly flavored with pepermint. " +
        "It's a treat that is only made during the holidays and is " +
        "often a favorite of those after they try it the first time. @@wrap_status@@\n");
    set_amount(9); 
}


void
init()
{
    ::init();

    add_action("eat_frango", "eat");

}
string eat_frango(string str)
{
    write("You eat a frango mint. Its smooth texture melts in your mouth.\n");
    say(QCTNAME(TP) + " eats a frango mint.\n");
    return "";
}
