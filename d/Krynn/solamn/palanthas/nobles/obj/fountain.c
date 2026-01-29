/* stone.c: The thing that causes the tell effect. 
   This is the new stone. */

#include <options.h>
#include <macros.h>
#include <composite.h>
#include "../../local.h";

inherit "/std/container";

#define HEDGE           NOBLE + "hedge"

static string *relay_rooms = ({ HEDGE });

public void
create_container()
{
 set_name("fountain");
 add_adj(({"tall", "marble", "tower"}));
 set_short("tall marble tower fountain");
 set_long("The fountain is a small scale replica of the Tower of "
	+ "Arms in the Merchants district.  Rising from a white, marble pool, "
	+ "it stands nearly eight feet.  Streams of water arc high into the "
	+ "air from the tops of its four corners before falling with tinkling "
	+ "bloops into the stone pool below.\n");

 add_prop(OBJ_I_NO_GET, 1);
 add_prop(OBJ_M_NO_ATTACK, 1);

 enable_commands();

 setuid();
 seteuid(getuid());
}

void
relay_message(mixed str, object from)
{
    if (stringp(str))
        str = "In the park you observe:  " + str;
    
    if (pointerp(str))
        str = map(str, &operator(+)("In the park you observe:  ", ));
    
    foreach (string room: relay_rooms)
    {
        object ob, *people;

        ob = find_object(room);
        if (!objectp(ob))
            continue;
        
        people = filter(all_inventory(ob), living);
        foreach (object player: people)
        {
            /* This leads to double messages in things like shout */
            if (objectp(from) &&
                environment(player) == environment(from))
                continue;
            
            if (player->query_option(OPT_NO_FIGHTS) ||
                !CAN_SEE_IN_ROOM(player))
                continue;
            player->catch_msg(str, from);
        }
    }
}

void
catch_msg(mixed str, object obj)
{
    relay_message(str, obj);
}

int
query_option(int opt)
{
    if(opt == OPT_GAG_MISSES)
        return 0;
}

void
remove_item(object ob)
{
    ob->remove_object();
}

/*
 * This object can't be paralyzed poisoned etc.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_alarm(0.0, 0.0, &remove_item(ob));
}
