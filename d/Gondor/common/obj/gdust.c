/*
 * /d/Gondor/common/obj/sdust.c
 *
 * A bag of gold dust to be used as a paint additive and
 * a quest object. If tossed into the air, there is a chance
 * that some will get in your eyes. The dust is magic, so
 * will raise one's awareness. It is located on Elfhelm in
 * Edoras.
 * /d/Gondor/rohan/npc/elfhelm.c
 * /d/Gondor/rohan/edoras/rooms/boffice2
 *
 * Coded by Gwyneth on September 11, 2000
 */

inherit "/d/Genesis/gems/gem";

#include <macros.h>

#include "/d/Genesis/gems/gem.h"

#define SHINE "/d/Gondor/common/obj/shine"
#define SHINE_SUBLOC "_shine_subloc"

public void
create_gems()
{
    config_gems("bag of gold dust", "bags of gold dust", "", 5000,
        GEM_VERY_RARE, 52, 64);
    set_long("These are bags of gold dust, packed full " +
        "of beautiful fine gold dust. You imagine that one might " +
        "be able to toss the dust " +
        "into the air and watch it sift down like magic faerie dust.\n");
    add_name(({"dust", "bag", "_gondor_gold_dust"}));
    add_adj(({"gold", "of", "bag"}));
    remove_name("gem");
    remove_adj("bag of gold dust");
    add_prop(MAGIC_AM_MAGIC, ({75, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"A glimmer of enchantment emanates " +
        "from the dust.\n", 20, "A small amount of gold dust in " + 
        "your eyes will make you more aware of your surroundings.\n", 30,
        "Too much in your eyes would be inneffective. The only way " +
        "is to toss it in the air and keep your eyes open.\n", 50}) );
    add_prop(OBJ_M_NO_BUY, "That is reserved for special customers!\n");
    add_prop(OBJ_M_NO_STEAL, 1);
    set_alarm(0.5, 0.0, &remove_name("_gem_ingredient"));
}

public int
toss(string str)
{
    object shine;
    string extra = "";

    if (!strlen(str))
    {
        notify_fail("Toss what into the air?\n");
        return 0;
    }

    if (!parse_command(str, environment(this_object()),
      " %i [into] [the] [air] "))
    {
        notify_fail("Toss what into the air?\n");
        return 0;
    }

    if (this_player() != environment(this_object()))
    {
        notify_fail("You don't hold the dust.\n");
        return 0;
    }

    if (member_array(SHINE_SUBLOC, this_player()->query_sublocs()) == -1)
    {
        setuid();
        seteuid(getuid(this_object()));
        shine = clone_object(SHINE);
        shine->set_colour("gold");
        shine->move(this_player(), 1);
        shine->fun_stuff();

        if (random(100) < 66)
        {
            extra = "Some flecks of gold dust get in your eyes, " +
                "and your surroundings take on a gold glow.";
            shine->add_extras();
        }

        write("You toss the bag of gold dust into the air, where " +
            "its tiny particles float down to the ground. A stray " +
            "current of air sends some gold dust straight into " +
            "your face. " + extra + "\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) +
            " tosses a bag of gold dust into the air, where " +
            "its tiny particles float down to the ground. A stray " +
            "current of air sends some gold dust straight onto " +
            QTPNAME(this_player()) + " face.\n", this_player());
    }
    else
    {
        write("You toss the bag of gold dust into the air, where its " +
            "tiny particles float down to the ground.\n");
        tell_room(environment(this_player()), QCTNAME(this_player()) +
            " tosses a bag of gold dust into the air, where its " +
            "tiny particles float down to the ground.\n", this_player());
    }

    restore_heap();
    set_heap_size(num_heap() - 1);
    return 1;
}

public void
init()
{
    ::init();

    add_action(toss, "toss");
}

public string
query_auto_load()
{
    return 0;
}
