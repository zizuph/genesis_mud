inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"

void
create_object()
{
    set_short("basket of rotten fruit");
    set_name("fruit");
    set_adj("rotten");
}


int
throw_item(string who)
{
    int i;
    string thrower_name;
    object whob;

    if (!who)
    {
	write ("Donut who?\n");
	return 1;
    }

    if( this_player()->notmet_me(whob) )
    {
        thrower_name = "A " + C(this_player()->query_nonmet_name());
    }
    else
    {
        thrower_name = this_player()->query_Met_name();
    }

    if (find_player(who) && present(find_player(who),environment(this_player()))) {
        whob = find_player(lower_case(who));


        tell_object(whob, thrower_name + " throws a piece of rotten fruit at you, "+
            "which hits you in the face, splattering all over you!\n");

        write ("You throw a piece of rotten fruit at " + C(who) + ".\n");
        return 1;
    }

}


void
init()
{
    ::init();
    add_action(throw_item, "throw");
}
