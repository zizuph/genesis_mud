/* ctower/obj/wand.c is cloned by ctower/maze23.c  */
inherit "/std/object";
inherit "/d/Emerald/ctower/obj/ctower_obj_base";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <cmdparse.h>
#include <ss_types.h>

void get_it(object player);

void
reset_object()
{
    reset_ctower_object();
}

void
create_object()
{
    set_name("wand");
    add_name("ctower_wand");
    set_long( "This is a clear, crystal wand that is about "+
	"two centimeters thick and twelve centimeters long.\n");
    add_adj("crystal");
    add_adj("for");              // cheap way to allow 'search for wand'
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_VALUE, 108);
    add_prop(OBJ_M_NO_GET, "You reach for the wand, but your hand passes " +
	"right through it!\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_it");
  
    create_ctower_object();
}
 
string
search_it(object player, string str)
{
    if (!strlen(str) || 
        !parse_command(str, ({}), "[for] [the] [crystal] 'wand'"))
    {
        notify_fail("Feel what?\n");
        return 0;
    }
  
    if (player->resolve_task(TASK_DIFFICULT, ({ TS_INT, SS_AWARENESS })) > 0)
    {
        get_it(player);
        return "\n";
    }
  
    return 0;  
}
 
int
feel(string str)
{
    if (!strlen(str) || 
        !parse_command(str, ({}), "[for] [the] [crystal] 'wand'"))
    {
        notify_fail("Feel what?\n");
        return 0;
    }
  
    if (this_player()->resolve_task(TASK_ROUTINE + 100, ({ TS_INT, 
	SS_AWARENESS })) > 0)
    {
        get_it(this_player());
    }
    else
    {
        write("You don't feel anything.\n");
    }
  
    return 1;
}

void
get_it(object player)
{
    string str = " grabs at empty space and gets something!\n";

    player->catch_tell("You feel a wand and quickly pick it up!\n");
    tell_room(environment(this_object()), ({
        player->query_met_name() + str,
        player->query_nonmet_name() + str,
        "" }), player);

    remove_prop(OBJ_M_NO_GET);
    move(player, 1);
}

int
touch(string str)
{
    string touch_str;
    mixed *oblist;
    object wand;

    if (!parse_command(str, all_inventory(this_player()),
        "%s 'with' [the] %i", touch_str, oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Touch with what?  Be more specific!\n");
        return 0;
    }

    if (oblist[0] != this_object())
    {
        return 0;
    }

    wand = oblist[0];

    if (!parse_command(touch_str, all_inventory(environment(this_object())),
        "[the] %i", oblist) ||
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        notify_fail("Touch what with the wand?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Touch what with the wand?  Be more specific!\n");
        return 0;
    }

    if (living(oblist[0]))
    {
        write("You poke " + oblist[0]->query_the_name(this_player()) + 
            "with the wand.\n");
        oblist[0]->catch_tell(this_player()->query_The_name(oblist[0]) + 
            " pokes you with a crystal wand.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) +
            " pokes " + QTNAME(oblist[0]) + " with a crystal wand.\n",
            ({ oblist[0], this_player() }));
        
        return 1;
    }

    write("You touch the " + oblist[0]->short() + " with the wand.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) +
        " touches the " + QSHORT(oblist[0]) + " with a crystal wand.\n",
        this_player());

    oblist->touch_with_ctower_wand();

    return 1;
}

void
init()
{
    ::init();

    if (this_player() != environment())
    {
        add_action(feel, "feel");
    }
    else
    {
        add_action(touch, "touch");
    }
}
