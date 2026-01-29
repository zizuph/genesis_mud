#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "../defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/object";

int remove_fish();
int remove_hooked;


void
create_object()
{

    set_short("long fishing pole");
    set_long("@@desc_pole");
    add_name("fishing pole");
    add_name("pole");
    add_name("_fish_pole");
    add_item("hook","@@desc_hook");
    add_item("float","@@desc_float");
    add_prop(OBJ_I_VOLUME, 1000);  // Five cubic decimeter
    add_prop(OBJ_I_WEIGHT, 500);    // Pole weights 0,5 Kg
    setuid();
    seteuid(getuid());
}

void
init()
{
    ::init();
        add_action("do_bait", "bait");
        add_action("do_pull", "pull");
}

int
add_fish()
{
    float react_time;

    TO->add_prop("_fish_is_hooked", 1);
    TO->remove_prop("_pole_is_ready");
    react_time = (rnd() * 20.0 + 1.0);
    remove_hooked = set_alarm(react_time, 0.0, &remove_fish());
    return 1;
}

int
query_remove_hooked()
{

    if (remove_hooked)
        return remove_hooked;
}

int
remove_fish()
{
    if (TO->query_prop("_fish_is_hooked"))
        TO->remove_prop("_fish_is_hooked");
    tell_room(ENV(ENV(TO)), "Suddenly the float pops up from below and " +
        "starts bobbing slowly in the water.\nThe fish has escaped!\n");
    return 1;
}

int
do_pull(string str)
{
    object fish;

    if (!(str) || (str == ""))
        return 0;
    if ((str == "pole") || (str == "fishing pole") || (str == "up fish")
        || (str == "up pole") || (str == "up hook")
        || (str == "up fishing pole") || (str == "fish")
        || (str == "hook") || (str == "up"))
    {

 
    if (!(TP->query_prop("_is_fishing")))
    {
        write("You swing the pole in the air with a swishing " +
            "sound.\n");
        say(({METNAME + " swings the fishing pole in the air " +
            "with a swishing sound.\n",
            TART_NONMETNAME + " swings the fishing pole in the air " +
            "with a swishing sound.\n",
            "You hear a swishing sound in the air."}), TP);
        return 1;
    }
 
        if (TO->query_prop("_fish_is_hooked"))
        {
            if (!(random(4)))
                fish = clone_object(THIS_DIR + "obj/trout");
            else
                fish = clone_object(THIS_DIR + "obj/fish");
            fish->move(ENV(TP));
            TO->remove_prop("_fish_is_hooked");
            TP->remove_prop("_is_fishing");
            remove_alarm(remove_hooked);
            write("You pull up the pole with a powerful jerk and drop " +
                "a " + fish->query_short() + " on the " +
                "bottom of the boat. With skill you stick your thumb " +
                "into its mouth and break its neck with a snap.\n");
            say(QCTNAME(TP) + " pulls up a " +fish->query_short()+ " and " +
                "drop it struggling on the bottom of the boat and with " +
                "a snap, break its neck.\n");
            return 1;

        }

        if (!(TO->query_prop("_pole_is_ready")))
        {
            write("You pull up the pole with a jerk but there " +
                "is no bait on the hook.\n");
            say(QCTNAME(TP) + " pulls up the hook in the air and " +
                "realises there is no bait on the hook.\n");
            TP->remove_prop("_is_fishing");
            if (ENV(TP)->query_bite_alarm())
                (ENV(TP)->remove_bite_alarm());
            if (ENV(TP)->query_bob_alarm())
                (ENV(TP)->remove_bob_alarm());
            return 1;

        }
        else
        {
            write("You pull up the pole with a jerk but to " +
                "your disappoinment there is no fish on the " +
                "hook.\n");
            say(QCTNAME(TP) + " pulls up the hook but no fish. " +
                "But the maggot is still struggling on the hook.\n");
            if (ENV(TP)->query_bite_alarm())
                (ENV(TP)->remove_bite_alarm());
            if (ENV(TP)->query_bob_alarm())
                (ENV(TP)->remove_bob_alarm());
            TP->remove_prop("_is_fishing");
            return 1;
        }
    }
    return 0;

}

int
do_bait(string str)
{
    object can, maggot;

    if (!str || str == "")
        return 0;
    if (!(str))
        return 0;
    if ((str == "hook") || (str == "pole") || (str == "maggot"))
    {
       if (TP->query_prop("_is_fishing"))
       {
           write("You cant put a bait on the hook " +
               "when its below water. Better if you " +
               "pull up the hook first.\n");
           return 1;
       }


       if (TO->query_prop("_pole_is_ready"))
       {
           write("There is already a bait on the hook.\n");
           return 1;
       }
       can = (present("_can", TP));
       if (can)
       {
           maggot = (present("_maggot", can));
           if (maggot)
           {
               if (maggot->query_dead())
               {
                   write("This maggot is unfortunately dead and is " +
                       "of no use as bait.\n");
                   return 1;
   }

               maggot->remove_object();
               write("You bait the hook with a struggling maggot " +
                   "from your can. Now you are ready to fish!!\n");
               say(QCTNAME(TP)+ " baits the hook with a " +
                   "struggling maggot. Now the fishing pole is " +
                   "ready to fish with.\n");
               TO->add_prop("_pole_is_ready", 1);
               return 1;
           }
       }
       else
       maggot = (present("_maggot", TP));
       if (maggot)
       {
           if (maggot->query_dead())
   {
       write("This maggot is unfortunately dead and is " +
           "of no use as bait.\n");
       return 1;
   }
           maggot->remove_object();
           write("You bait the hook with a struggling maggot " +
               "from your pocket. Now you are ready to fish!!\n");
           say(QCTNAME(TP)+ " baits the hook with a " +
               "struggling maggot. Now the fishing pole is " +
               "ready to fish with.\n");
           TO->add_prop("_pole_is_ready", 1);
           return 1;
       }
       write("You cant find any bait!\n");
       return 1;
    }
    return 0;


}

string
desc_pole()
{
    string text;

    text = "This is a long fishing pole with a fishing line, " +
        "float and a hook. It is made of " +
        "a bamboo-like material making it very flexible. ";

    if (TO->query_prop("_fish_is_hooked"))
    {
        text += "The fishing line is straight and the float has " +
            "disappeard below the surface. Perhaps its time to " +
            "pull up the pole?\n";
        return text;
    }

    if (TP->query_prop("_is_fishing"))
    {
       text += "\n";
       return text;
    }

    if (TO->query_prop("_pole_is_ready"))
    {
        text += "On the hook you see a struggling maggot.\n";
        return text;
    }
    text += "\n";
    return text;
}

string
desc_hook()
{
    string text;

    if (TP->query_prop("_is_fishing"))
    {
        text = "You cant see it as its below the water.\n";
        return text;
    }

    if (TO->query_prop("_pole_is_ready"))
    {
        text = "On the end you see a struggling little maggot.\n";
        return text;
    }
    text = "Its a small and rusty little hook.\n";
    return text;
}

string
desc_float()
{
    string text;

    if (TO->query_prop("_fish_is_hooked"))
    {
        text = "You cant see the float as it has disappeared below " +
            "the surface.\n";
        return text;
    }

    text = "Its a red and white float made of cork. ";

    if (TP->query_prop("_is_fishing"))
        text += "Right now the float is bobbing on the water.\n";
    else
        text += "\n";

    return text;
}
