/* This container "fakes" the inside of the tower, allowing players
 * to drop things into the tower from the roof.
 */

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>

string
hole_long()
{
    object room;

//    if (this_player()->query_wiz_level() || this_player()->query_vampire() ||
    if (this_player()->query_wiz_level() ||
        this_player()->query_prop(LIVE_I_SEE_DARK) ||
        (query_room() && (query_room()->query_prop(OBJ_I_LIGHT) > 0)))
    {
        return "You manage to make out a staircase in the darkness " +
               "directly below the hole in the roof.  Jumping down " +
               "would be treacherous.\n";
    }

    return "You can't make anything out in the darkness of the tower. " +
        "Jumping down inside would be treacherous.\n";
}

void
create_container()
{
    set_no_show_composite(1);
    set_name(({ "hole", "tower" }));
    set_long(hole_long);
    add_prop(CONT_I_MAX_WEIGHT, 10000000);
    add_prop(CONT_I_MAX_VOLUME, 10000000);
    remove_prop(CONT_I_WEIGHT);
    remove_prop(CONT_I_VOLUME);
    add_prop(OBJ_M_NO_GET, 1);
    LOAD_ERR("/d/Terel/common/town/street/tower2");

    /* This won't get updated if tower2 is updated, but it doesn't
     * seem like a major problem.
     */
    set_room(find_object("/d/Terel/common/town/street/tower2"));
}

void
show_visible_contents(object for_obj)
{
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (query_room())
    {
        tell_room(query_room(), capitalize(LANG_ASHORT(ob)) +
            " falls in from the hole in the roof.\n");
    }
}

/* This used to be used by the old Emerald Vampires as a 
 *  secondary 'lair'. Recycling for use by players.
 *      Lilith, Mar 2022  
int
jump(string str)
{
    if (!strlen(str))
    {
        return 0;
    }

    if (!parse_command(str, ({}),
        "[down] 'through' / 'in' / 'into' 'hole' / 'tower'"))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    say(({ METNAME + " jumps down through the hole in the roof.\n",
           ART_NONMETNAME + " jumps down through the hole in the roof.\n",
           "" }));

    if (this_player()->query_wiz_level() ||
        this_player()->query_vampire())
    {
        write("You leap down into the hole, landing securely on a " +
            "staircase.\n");

        this_player()->move_living("M",
            "/d/Terel/common/town/street/tower2", 1);

        say(({ METNAME + " jumps down through the hole in the roof.\n",
               ART_NONMETNAME + " jumps down through the hole in the roof.\n",
               "" }));
        return 1;
    }

    write("You leap down into the hole.\n");
    this_player()->move_living("M",
        "/d/Terel/common/town/street/tower2", 1);

    write("You make a bad landing and fall off the edge of the staircase!\n");
    say(({ METNAME + " jumps down through the hole in the roof and falls " +
           "off the edge of the staircase!\n",
           ART_NONMETNAME + " jumps down through the hole in the roof and falls " +
           "off the edge of the staircase!\n",
           "" }));

    this_player()->move_living("M",
        "/d/Terel/common/town/street/tower1", 1);

    say(({ METNAME + " falls in from above, crashing to the ground in " +
           "a heap.\n",
           ART_NONMETNAME + " falls in from above, crashing to the ground " +
           "in a heap.\n",
           "" }));

    this_player()->heal_hp(-(this_player()->query_hp()));
    this_player()->do_die(this_object());
    return 1;
}        
*/


int
jump(string str)
{
    int rnd;
	
    if (!strlen(str))
    {
        return 0;
    }

    if (!parse_command(str, ({}),
        "[down] 'through' / 'in' / 'into' 'hole' / 'tower'"))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    say(({ METNAME + " jumps down through the hole in the roof.\n",
           ART_NONMETNAME + " jumps down through the hole in the roof.\n",
           "" }));

    rnd = random(10);	
	if (rnd >= 8)
    {
        write("You leap down into the hole, landing securely on a " +
            "staircase.\n");

        this_player()->move_living("M",
            "/d/Terel/common/town/street/tower2", 1);

        say(({ METNAME + " jumps down through the hole in the roof.\n",
               ART_NONMETNAME + " jumps down through the hole in the roof.\n",
               "" }));
        return 1;
    }

    
    write("You leap down into the hole.\n");
    this_player()->move_living("M",
        "/d/Terel/common/town/street/tower2", 1);

    write("You make a bad landing and fall off the edge of the staircase!\n");
    say(({ METNAME + " jumps down through the hole in the roof and falls " +
           "off the edge of the staircase!\n",
           ART_NONMETNAME + " jumps down through the hole in the roof and falls " +
           "off the edge of the staircase!\n",
           "" }));

    this_player()->move_living("M",
        "/d/Terel/common/town/street/tower1", 1);

    say(({ METNAME + " falls in from above, crashing to the ground in " +
           "a heap.\n",
           ART_NONMETNAME + " falls in from above, crashing to the ground " +
           "in a heap.\n",
           "" }));
    /* This hurts, but doesn't kill */
    this_player()->heal_hp(-(this_player()->query_hp() /5));
    return 1;
}        



void
init()
{
    ::init();
    add_action(jump, "jump");
    add_action(jump, "climb");
}
