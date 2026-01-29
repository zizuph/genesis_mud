/* Statue of Huma for Vingaard Keep  */
/* Coded by Grace 04/15/94           */
/* modified slightly by Teth 12/03/96 for new VK */
/* Added OotS revelation to statue - Arman 2017 */

inherit "/std/object";

#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include "/d/Krynn/guilds/OotS/defs.h"

create_object()
{
    set_name("statue");
    add_name(({"huma","hero","noble hero"}));
    set_short("statue of a noble hero");
    set_long("\nThe figure of a human male carved out of granite.\n" +
        "He is tall and well-built, with long hair and a traditional " +
        "Solamnian\nmoustache. His face is worn and sorrowful-looking, " +
        "the face of a man\nwho has seen great evil and needless suffering. " +
        "In one hand of the figure\nrests a mythical DragonLance. He wears " +
        "armour of ancient make, the\nbreast-plate of which is carved " +
        "with the markings of the three Solamnic\nOrders. On his arm "+
        "is a shield etched with the symbols of the Knights\nof the Crown.\n" +
        "\nThe statue is renowned for its beauty, and travellers often " +
	"come to pay their respects to it. It would certainly be " +
        "looked upon as a grave insult to mock the statue.\n\n" +
        "At the base of the statue is a plaque which can be read.\n");
    ACI("plaque", "read","@@read_plaque");
    AI("plaque", "It was made with a careful and steady hand. Perhaps you " +
        "should read it?\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_M_NO_GET, "You will get a hernia if you try that again!\n");
    add_prop(OBJ_I_LIGHT, 2);
    add_prop(OBJ_M_NO_STEAL);
}

string
read_plaque()
{
    if(IS_OOTS(TP))
    {
          if(!OOTS_QUERY_REV(TP, "canticle34"))
          {
            TP->catch_msg("\n\nAs you read the plaque at the base of the statue of Huma " +
                     "you are provided with a divine revelation!\n\n\n");
            OOTS_ADD_REV(TP,"canticle34","edification - canticle of the dragon, verse 3 and 4");  
          }
    }

   return "The plaque reads:\n\n" +
        "This carving of Huma Dragonbane was sponsored by a famous Knight " +
        "of the\nSword, in recognition of the tremendous heroism of Huma, "+
        "and in hopes\nthat others might emulate his examples of courage " +
        "and self-sacrifice.\n\n";

}
