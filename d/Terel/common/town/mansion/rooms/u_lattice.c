/* Under the lattice, standing in water. Mortricia 930501 */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include "/d/Terel/common/terel_defs.h"

#define TP             this_player()
#define TO             this_object()
#define SCEPTRE        MORTRICIADIR+"camp/house/sceptre"
#define WHERE          MANSION+"rooms/in_water"
#define OCTO           MANSION+"mon/octo"

object octo;

public void
create_room()
{
    set_short("standing in water");
    set_long(
        "You are standing in knee-deep water, at least where you are. " +
        "Above you, there is a lattice work.\n");
    add_item("water",
        "The water is dark and dirty. You cannot see how deep it is, so " +
        "you shouldn't walk around to much.\n");
    add_item(({"lattice", "lattice work"}), "It's outside your reach.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_CONTAIN_WATER, 1);

    seteuid(getuid(TO));
    octo = clone_object(OCTO);
    octo->move(WHERE);

    add_exit(MANSION + "rooms/b_wall", "up", "@@go_up");
}

public int
go_up()
{
    if (TP->query_ghost()) return 0;
    write("You cannot go there.\n");
    return 1;
}

public void
move_item(object ob)
{
    if (!ob) return;
    
    tell_room(TO, "The " + ob->short() + " disappears into the water.\n");
    ob->move(WHERE);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (living(ob)) return;
    
    set_alarm(1.0, -1.0, &move_item(ob));
}

public void
res_of_search(object who)
{
    object *obs;
    int i, n;

    if (!who || environment(who) != TO) return;
    if (octo && environment(octo) != TO) {
        octo->move_living("M", TO);
        who->catch_msg("Oops! Your search revealed " +
                       LANG_ADDART(octo->short()) + ".\n");
        return;
    } else if (octo && environment(octo) == TO) {
        who->catch_msg("The " + octo->short() + " is in the way.\n");
        return;
    } else if (!octo) {
        obs = all_inventory(find_object(WHERE));
        n = sizeof(obs);
        i = random(2*n + 3);
        if (i < n) {
            if (!living(obs[i])) {
                who->catch_msg("You found " +
                               LANG_ADDART(obs[i]->short()) + ".\n");
                if (obs[i]->move(who)) {
                    who->catch_msg("You cannot hold it.\n");
                    obs[i]->move(TO);
                }
                return;
            }
        }
    }
    who->catch_msg("Your search revealed nothing special.\n");
    return;
}

public int
do_search(string str)
{
    if (str != "water" && str != "the water") return 0;
    write("You start to search the water.\n");
    say(QCTNAME(TP) + " starts to search the water.\n");
    set_alarm(6.0, -1.0, &res_of_search(TP));
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_search, "search");
}
