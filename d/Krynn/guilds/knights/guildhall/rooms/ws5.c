/* West street 5, new VK
 * By Teth, Dec. 3 1996
 */


#include "../../local.h"
inherit STREET;

string
tell_message1()
{
    return "The sound of metal on metal rings from the west.\n";
}

string
tell_message2()
{
    return "A sudden gust of heat bellows from the building to your "+
           "west.\n";
}

string
tell_message3()
{
    return "Smoke rises from the chimney above the building to the "+
           "west.\n";
}

public void
create_street()
{
    add_my_desc("A metal smithy is ensconced within the west wall " +
                "of the Keep. The street runs north and south.\n");
    AI(({"metal smithy","smithy"}),"The smithy of Vingaard Keep " +
      "lies to the west. The smithy offers crafted weapons, " +
      "forged from Solamnic steel.\n");

    AE(VROOM + "forge", "west", 0);
    AE(VROOM + "ws4", "north", 0);
    AE(VROOM + "ss1", "south", 0);
    set_tell_time(150);
    add_tell("@@tell_message1");
    add_tell("@@tell_message2");
    add_tell("@@tell_message3");

}

void
enter_inv (object ob, object from)
{
    ::enter_inv(ob, from);
    if (interactive(ob))
	start_room_tells();
}

