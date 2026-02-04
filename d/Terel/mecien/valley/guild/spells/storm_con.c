/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <comb_mag.h>

#define TP     this_player()
#define ETP    environment(TP)
#define TO     this_object()
#define ETO    environment(TO)
#define NF(xx) notify_fail(xx);

public void delay_msg(object who, string what);
public void set_cloud(object ob);
public object query_cloud();

static object cloud;

public void
create_object()
{
    set_name("_storm_controller_");
    set_no_show();
    add_prop(OBJ_M_NO_DROP, 1);
}

public void
init()
{
    ::init();
    if (TP == ETO) {
        add_action("do_call", "summon");
    }
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (living(to)) {
        set_alarmv(1.0, -1.0, "delay_msg", ({to,
                   "Through ancient might, the storm is at thy command!"}) );
    }
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if (living(from)) {
        delay_msg(from, "You feel the power of the storm leave you.");
    }
}

public void
delay_msg(object who, string what)
{
    if (!who || !living(who)) return;
    who->catch_msg(what + "\n");
}

public void
set_cloud(object ob)
{
    cloud = ob;
}

public object
query_cloud()
{
    return cloud;
}

public int
do_call(string str)
{
    NF("Summon what?\n");
    if (!str || !cloud) return 0;

    NF("Your call is not heard.\n");
    if (NPMAGIC(TP)) return 0;

    NF("A call to the sky cannot be heard here!\n");
    if (ETP->query_prop(ROOM_I_INSIDE)) return 0;
    say(QCTNAME(TP) + " reaches " + TP->query_possessive() +
        " hands towards the sky.\n");

    if (str == "storm" || str == "storm here") {
        write("You summon the storm to this place.\n");
        if (cloud->move(ETP)) return 0;
        return 1;
    } else if (str == "thunder" || str == "thunder from storm") {
        write("You summon thunder from the mystic storm.\n");
        return (cloud->call_thunder(TP));
    } else if (str == "lightning" || str == "lightning from storm") {
        write("You summon a flash from the mystic storm.\n");
        return (cloud->call_lightning(TP));
    } else if (str == "wind" || str == "wind from storm") {
        write("You summon a gust of wind from the mystic storm.\n");
        return (cloud->call_wind(TP));
    }

    NF("Summon what?\n");
    return 0;
}


