#include "../guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include <filter_funs.h>
#include <macros.h>
#include <tasks.h>
#include <cmdparse.h>

static int fabric_exposed = 0;
int black_fabric_present = 0;
int red_fabric_present = 0;

int do_push();
int open_door();
int close_door();
void set_black_fabric_present(int i);
void set_red_fabric_present(int i);
object *items = ({});

object
config_shelf(string where)
{
    object shelf;

    shelf = clone_object(VAMP_OBJ_DIR + "shelf");
    shelf->set_wall(where);
    shelf->move(this_object(), 1);
    return shelf;
}

void create_vamp_room()
{
    set_short("Storage room");

    set_long("   This is the temple's storage area.  It appears that it " +
        "has been recently restored, the shelves cleaned and repaired.\n");

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "search_shelves");

    /* Keep this around so that the searching routines don't have to be
     * moved
     */
    add_item(({ "shelf", "shelves" }), "Several sets of heavy, wooden " +
        "shelves are placed against the walls.\n");

    add_exit("hall4", "south");

    setuid();
    seteuid(getuid());

    restore_object(file_name(this_object()));

    if (!black_fabric_present)
    {
        set_black_fabric_present(!random(7));
    }
    
    if (!red_fabric_present)
    {
        set_red_fabric_present(!random(15));
    }

    setuid();
    seteuid(getuid());
    items = map(({ "north", "east", "west", "south" }), config_shelf);
}

void reset_room()
{
    items -= ({ 0 });

    if (!sizeof(filter(all_inventory(this_object()), living)))
    {
        close_door();
    }
}

void set_black_fabric_present(int i)
{
    black_fabric_present = i;
    setuid();
    seteuid(getuid()); 
    save_object(file_name(this_object()));
}

void set_red_fabric_present(int i)
{
    red_fabric_present = i;
    setuid();
    seteuid(getuid()); 
    save_object(file_name(this_object()));
}

string search_shelves(object who, string str)
{
    if (str != "shelves")
    {
        return "";
    }

    if ((this_player()->resolve_task(TASK_DIFFICULT,
        ({ TS_INT, TS_WIS, SS_AWARENESS })) > 0))
    {
        return "Hidden behind the shelves, you notice a panel on " +
            "the wall that is slightly inset.\n";
    }

    return "";
}

int press(string str)
{
    if (str != "panel")
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    do_push();
    return 1;
}

int open(string str)
{
    if (member_array(str, ({ "door", "small door", "hidden door",
        "small hidden door" })) < 0)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!do_push())
    {
        write("The door is already open.\n");
        return 1;
    }

    return 1;
}

int do_push()
{
    say(({ this_player()->query_Met_name() + " reaches behind a shelf.\n",
           capitalize(this_player()->query_nonmet_name()) + 
           " reaches behind a shelf.\n",
           "" }));

    write("You press the panel.\n");

    if (open_door())
    {
        FILTER_CAN_SEE_IN_ROOM(all_inventory(this_object()))->catch_msg(
            "A small, well hidden door in the north wall swings open, " +
            "revealing a tiny chamber.\n");

        return 1;
    }

    return 0;
}

void
update_bolts()
{
    string bolt_str;

    if (black_fabric_present)
    {
        if (red_fabric_present)
        {
            bolt_str = "one holds a striking, blood-red cloth, " +
                "and the other holding a beautiful, jet-black cloth.\n";
        }
        else
        {
            bolt_str = "one holds a beautiful, jet-black cloth, " +
                "while the other is empty.\n";
        }
    }
    else
    {
        if (red_fabric_present)
        {
            bolt_str = "one holds s striking, blood-red cloth, " +
                "while the other is empty.\n";
        }
        else
        {
            bolt_str = "they are both empty, however.\n";
        }
    }

    add_item("panel", "A small, square panel set into the north wall.\n");

    remove_item("bolt");
    add_item(({ "bolt", "bolts", "bolts of fabric",
                "bolt of fabric", "fabric bolt", "fabric bolts"}),
                "There are two fabric bolts firmly attached to " +
                "the bottom of the chamber; " + bolt_str + 
                "The bolts themselves seem to have a strange aura " +
                "about them, as if they were magical in nature.\n");
}

int open_door()
{
    object fabric;

    if (!fabric_exposed)
    {
        set_long("   This is the temple's storage area.  It appears that it " +
            "has been ransacked, though, as all that remains on the shelves " +
            "are dust and a few scraps of wood.\nA small door in the north " +
            "wall is open, revealing a tiny chamber.\n");

        add_item(({ "door", "small door" }), "A small door approximately " +
            "one and one-half meters high, and slightly set off of the " +
            "ground.\n");

        add_item(({ "chamber", "tiny chamber", }), "The chamber contains " +
            "just two fabric bolts.\n");

        update_bolts();

        if (black_fabric_present)
        {
            fabric = clone_object(VAMP_OBJ_DIR + "black_fabric");
            items += ({ fabric });
            fabric->move(this_object(), 1);
        }

        if (red_fabric_present)
        {
            fabric = clone_object(VAMP_OBJ_DIR + "red_fabric");
            items += ({ fabric });
            fabric->move(this_object(), 1);
        }

        fabric_exposed = 1;

        return 1;
    }    

    return 0;
}

int close(string str)
{
    if (member_array(str, ({ "door", "small door", "chamber door" })) < 0)
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (close_door())
    {
        write("You close the door.\n");
        say(({ this_player()->query_Met_name() + " closes the chamber door.\n",
               capitalize(this_player()->query_nonmet_name()) + " closes the " +
               "chamber door.\n",
               "" }));
    }
    else
    {
        write("The door is closed already.\n");
    }

    return 1;
}

int close_door()
{
    if (fabric_exposed)
    {
        fabric_exposed = 0;

        filter(all_inventory(), &->fabric_is_on_bolt())->remove_object();

        set_long("   This is the temple's storage area.  It appears that it " +
            "has been ransacked, though, as all that remains on the shelves " +
            "are dust and a few scraps of wood.\n");

        remove_item("panel");
        remove_item("chamber");
        remove_item("door");
        remove_item("bolt");

        return 1;
    }

    return 0;
}

int
list(string str)
{
    mixed *oblist;

    if (!strlen(str))
    {
        str = "all";
    }

    if (!parse_command(str, all_inventory(this_object()),
        "[the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!sizeof(filter(oblist, &->list_shelf_contents())))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    return 1;
}
     
void init()
{
    ::init();

    add_action(press, "press");
    add_action(press, "push");
    add_action(open,  "open");
    add_action(close, "close");
    add_action(list,  "list");
}

void leave_inv(object ob, object to)
{
    if (to)
    {
        if (ob->id("_vamp_fabric_black"))
        {
            if (black_fabric_present)
            {
                set_black_fabric_present(0);
            }
        }
        else if (ob->id("_vamp_fabric_red") && red_fabric_present)
        {
            set_red_fabric_present(0);
        }

        update_bolts();
    }

    ::leave_inv(ob, to);
}

/*
 * Too often I thoughtlessly update the room and cause the
 * contents to be lost.  This should prevent that.
 */
void
remove_object()
{
    if (sizeof(FILTER_DEAD(deep_inventory(this_object()) - items)))
    {
        throw("Cannot destruct while items are present.\n");
    }

    destruct();
}
