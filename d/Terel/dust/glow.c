inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

#define DUSTDIR "/d/Terel/dust/"
#define TP      this_player()
#define TO      this_object()
#define ETO     environment(TO)

public void
cool_down()
{
    object ash;

    seteuid(getuid());
    ash = clone_object(DUSTDIR + "ash");
    ash->move(ETO);
    tell_room(ETO, "The glowing fire cools down.\n");
    remove_object();
}

public void
create_object()
{
    set_name("fire");
    add_name("glow");
    set_adj("glowing");
    set_short("glowing fire");
    set_long("Those are the glowing remains of an extinguished fire.\n");
    add_item("light",
        "The glowing fire doesn't emit much light anymore.\n");
    add_prop(OBJ_I_NO_GET, "@@try_get");
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_WEIGHT, 100000);
    add_prop(OBJ_I_VOLUME, 1000000);
    add_prop(OBJ_I_VALUE,0);
    set_alarm(65.0, -1.0, cool_down);
}

public void
burn(object who)
{
    if (!who) return;
    
    who->reduce_hit_point(who->query_max_hp() / 20);
    who->do_die(TO);
}

public string
try_get()
{
    say(QCTNAME(TP) + " tries to get the glowing fire, but is burnt.\n");
    set_alarm(1.0, -1.0, &burn(TP));
    return "You try to touch the glowing fire, " +
           "but it is hot.. OUCH that hurt!!\n";
}

public int
do_touch(string str)
{
    notify_fail("Touch what?\n");
    if (str == "fire" || str == "glow")
    {
        write(try_get());
        return 1;
    }
    return 0;
}

public void
init()
{
    ::init();
    add_action(do_touch, "touch");
    add_action(do_touch, "feel");
}
