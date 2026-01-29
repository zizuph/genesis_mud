inherit "/std/armour";
inherit "/d/Genesis/specials/examples/std_magic_lib";

#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
/*#include "/d/Gondor/defs.h"*/
#include "/d/Krynn/common/defs.h"

int twisted;

#define MAGES(ob) ob->query_guild_member("Morgul Mages")

void
create_armour()
{
    set_name("ring");
    add_name("lesser_ring");
    set_adj("simple");
    add_adj("golden");
    set_short("simple golden ring");
    set_long("This looks like a simple golden ring, but you feel a " +
    	"powerful warmth eminating from it, almost as if it wants " +
        "to twist itself around your finger.\n");

    set_at(A_ANY_FINGER);
    set_ac(1);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO,"This is one of the lesser rings of " +
        "Middle Earth. For reference, Gandalf originally thought " +
        "that Bilbo's ring was one of the lesser rings. There is a " +
        "potential plan that a building of the One Ring quest " +
        "could include using lesser rings to potentially be " +
        "discovered as the One Ring, thus initiating the quest. " +
        "This would be one example of those rings. In the meantime, " +
        "this ring will be designed to also attract the attention " +
        "of the most dedicated servants of Sauron, allowing it " +
        "to perhaps be role-played with as a potential One Ring.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({"This appears to be a magic ring from the lands of " +
        "Middle Earth. You get the strong feeling that this " +
        "ring could help conceal you from magically prying " +
        "eyes.\n", 30}));

}


init()
{
    add_action("twist");
}

void
twisting()
{
    twisted = 0;
}


twist(str)
{
    object *players;

    int i;

    notify_fail("Twist what?\n");
    if(str != "ring" && str != "lesser_ring")
	return 0;

    if(twisted == 1)
    {
	write("You feel too exhausted and drained to twist the ring.\n");
	return 1;
    }

    write("You play around with the simple golden ring, " +
    	"slipping it on and off your finger.\n");
    SAY(" plays with a simple golden ring");
    twisted = 1;
    set_alarm(5.0, 0.0, "twisting");

    if(MAGES(this_player()) || environment(ob)(this_object()))
    {
	players = users();
	for (i = 0; i < sizeof(players); i++)
	{
	    if(MAGES(players[i]))
		players[i]->catch_msg("You feel a strange itch.\n");
	}
    } 
    return 1;

}