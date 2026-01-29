inherit "/std/object";
#include "/d/Kalad/defs.h"

create_object()
{
    set_name("clock");
    set_adj("grandfather");

    set_short("grandfather clock");
    set_long("@@clock_desc@@");

    add_prop(OBJ_I_NO_GET,1);
}

clock_desc()
{
    int hour;

    hour = HOUR;

    return BS("This ornate grandfather clock is made of solid " +
      "redwood from the Hespyre mountains near Kabal. " +
      "It stands proudly by the wall keeping time and " +
      "you can watch as the swing of its pendulum ticks off " +
      "the seconds. The small hand is resting near the " +
      hour + " on the dial.\n");
}
