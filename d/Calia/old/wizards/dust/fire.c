inherit "/std/object";
#define DUSTDIR "/d/Terel/dust/"
#include <stdproperties.h>
#include <macros.h>

#define BSN(s) break_string((s) + "\n",70)
#define BSNN(s) break_string((s) + "\n\n",70)

#define TP this_player()

create_object() {

    set_name("fire");
    set_adj("orange");
    set_short("orange fire");
    set_long("This fire emits orange light.\n");
    add_item("light",
	"The light seems to dip everything in this room " +
	"in an orange color.\n");
    add_prop(OBJ_I_NO_GET,"@@try_get");
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_WEIGHT,100000);
    add_prop(OBJ_I_VOLUME,1000000);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_I_LIGHT,1);
}

void
init()
{
    ::init();
    add_action("do_touch","touch");
    add_action("do_touch","feel");
    add_action("do_touch","enter");
}

remove_flag(object tp)
{
    tp->add_prop("_fire_burnt_already",0);
}

try_get()
{
    if (TP->query_prop("_fire_burnt_already"))
    {
	write("You don't dare to touch the fire after you burnt yourself...\n");
	return 1;
    }
    TP->add_prop("_fire_burnt_already",1);
    call_out("remove_flag",4,TP);
    TP->reduce_hit_point(TP->query_max_hp() / 4);
    TP->do_die(0);
    say(QCTNAME(TP) + " tries to get the fire, but is burnt.\n");
    write("You try to touch the fire, but it is hot.. OUCH that hurt!!\n");
    return 1;
}

do_touch(string str)
{
    notify_fail("Touch what?\n");
    if (str == "fire")
    {
	write(try_get());
	return 1;
    }
    else return 0;
}

void
extinguish()
{
    object glow;

    seteuid(getuid());
    glow = clone_object(DUSTDIR + "glow");
    glow->move(environment(this_object()));
    say("The fire goes out.\n");
    write("The fire goes out.\n");
    remove_object();
}
