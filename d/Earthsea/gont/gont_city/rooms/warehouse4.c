#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

private object leader;
private int leader_was_alive = 0;

public void
reset_room()
{
    if(!leader)
    {
        if(leader_was_alive)
        {
            leader_was_alive = 0;
            return;
        }

        if(random(5))
        {
            return;
        }

        leader_was_alive = 1;

        leader = clone_object(
            "/d/Earthsea/gont/gont_city/liv/smuggler_leader"
        );
        leader->move(this_object());
        leader->command("hide");
    }
}

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Inside a warehouse");
    set_long("This is a"+
        " large wooden warehouse, busy with"+
        " many harbour workers and sailors carrying heavy"+
        " crates and sacks from one of the ships at the pier"+
        " and stapling them in huge piles. The only light in"+
        " here comes from outside, between gaps in the"+
        " board walls and from the large open door, making"+
        " the clouds of dust in the air clearly visible."+
        " Under your feet is the bare earth, sterile"+
        " and compact from constant use. There are large"+
        " crates and sacks"+
        " everywhere, piled on top of each other all the"+
        " way up to the ceiling.\n");
    add_item(({"sailors","workers"}),"Both sailors dressed"+
        " in exotic clothes and Gontish harbour workers work"+
        " hard with unloading one of the ships anchored by"+
        " the East Pier, carrying the goods inside this"+
        " warehouse.\n");
    add_item("walls","The walls are made by boards,"+
        " crudely fitted together leaving wide gaps between"+
        " them.\n");
    add_item("floor","The floor is the bare earth, made"+
        " compact through the years by hundreds of harbour"+
        " workers walking over it.\n");
    add_item(({"sacks","crates"}),"The sacks and crates"+
        " are full of the goods this particular merchant"+
        " company trades with.\n");
    add_item("dust","Clouds of dust are in the air, clearly"+
        " visible in the light coming in from outside.\n");
    add_item("ceiling","The ceiling is high above your head,"+
        " and the weak light makes it impossible to make out"+
        " anything more.\n");
    add_item("piles","The sacks and crates are piled on top"+
        " of each other, all the way up to the ceiling.\n");
    add_item("workers","Muscular men carrying heavy crates"+
        " and sacks from a newly arrived ship to this warehouse.\n");
    add_item(({"door", "open door", "large door", "large open door"}),
        "A large sliding door has been opened to allow entry into " +
        "the warehouse.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN, "search_crates");
    add_exit("city_street/city_road33", "west");
    reset_room();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(leader && ob->id("smuggler") && !ob->id("leader"))
    {
        leader->greet_smuggler(ob);
    }
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if(leader && living(ob))
    {
        leader->cheer_departure(ob);
    }
}

public string
search_crates(object tp, string str)
{
    if(str != "sacks" && str != "crates")
    {
        return 0;
    }

    if(leader && present(leader, this_object()))
    {
        leader->command("reveal myself");
        leader->command("say Not on my watch!");

        if(tp->query_average_stat() > 90)
        {
            leader->command("kill " + tp->query_real_name());
        }

        return 0;
    }

    if(str == "sacks")
    {
        return "You rummage through the sacks, but come up " +
            "with nothing.\n";
    }

    if(tp->query_prop("__es_gont_wh4_found_hole__"))
    {
        return "You search through the crates and notice " +
            "that the passageway is still there.\n";
    }

    if(tp->query_skill(SS_AWARENESS) < (30 + random(10)) ||
        tp->query_skill(SS_FR_TRAP) < (10+random(10)))
    {
        return "You rummage through the crates, but come up " +
            "with nothing.\n";
    }

    tp->add_prop("__es_gont_wh4_found_hole__", 1);
    return "You rummage through the crates and notice a single " +
        "empty crate. As you push against it to investigate, you " +
        "realize that beneath it lies a hidden passageway! " +
        "You step away from the crate before anyone notices, " +
        "but you could 'push crate' to enter the passage " +
        "provided nobody is watching.\n";
}

public int
push_crate(string str)
{
    object tp = this_player();

    if(!str || str != "crate")
    {
        if(tp->query_prop("__es_gont_wh4_found_hole__"))
        {
            return notify_fail("Push what, the crate?\n");
        }

        return 0;
    }

    if(!tp->query_prop("__es_gont_wh4_found_hole__"))
    {
        return 0;
    }

    if(leader && present(leader, this_object()))
    {
        if(leader->query_prop(OBJ_I_HIDE))
        {
            write("Somebody notices you approaching the crate " +
                "and jumps in your path!\n");
        } else {
            write(QCTNAME(leader) + " notices you approaching " +
                "the crate and jumps in your path!\n");
        }

        leader->command("reveal myself");
        leader->command("say Not on my watch!");

        if(tp->query_average_stat() > 90)
        {
            leader->command("kill " + tp->query_real_name());
        }

        return 1;
    }

    write("You carefully push the crate aside and sneak " +
        "down through the passageway.\n");
    tp->move_living("climbing down the beams",
        "/d/Earthsea/gont/gont_city/rooms/under_wh1", 1);
    return 1;
}

public void
init()
{
    ::init();
    add_action(push_crate, "push");
}
