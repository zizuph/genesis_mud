/* Street south 4, Vingaard Keep
 * By Teth, Dec. 3 1996
 */


#include "../../local.h"
inherit STREET;

string
tell_message1()
{
    return "The inviting smell of food tantalizes you to go have a bite "+
           "to eat at the Bronze Dragon Inn to your north.\n";
}

string
tell_message2()
{
    return "A few visitors of the Keep enter the Inn to your north.\n";
}

string
tell_message3()
{
    return "The sound of laughter reaches your ears, coming from the Inn "+
           "north of you.\n";
}

public void
create_street()
{
    add_my_desc("There is a cozy building to the north, with a " +
      "sign hanging above the entranceway. The street continues " +
      "west to a courtyard, and east.\n");
    AI(({"building","cozy building"}),"The building appears to be " +
      "an inn, and it is built into the walls of the guildhall, " +
      "allowing the fortress to be more compact where necessary.\n");
    ACI("sign","read","The sign reads:\n\n     The Bronze Dragon " +
      "Inn\n\n");
    AI("sign","The sign reads:\n\n     The Bronze Dragon Inn\n\n");
    AI("entranceway","It would be the logical way to enter the Inn.\n");

    AE(VROOM + "courtyard", "west", 0);
    AE(VROOM + "inn", "north", 0);
    AE(VROOM + "ss5", "east", 0);
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

