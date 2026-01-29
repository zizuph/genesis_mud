inherit "/d/Kalad/std/armour";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_armour()
{
    ::create_armour();
    set_name("watch");
    set_adj("gold");

    set_short("gold watch");
    set_long("@@clock_desc@@");
    set_ac(1);
    set_at(A_NECK);

    add_prop(OBJ_I_VALUE,720);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,250);
}

clock_desc()
{
    int hour;

    hour = HOUR;

    return ("An exquisitely crafted gold neck watch. Tiny engravings "+
      "of lions decorate it and accentuate its priceless beauty. A "+
      "delicate cover of shiny glass covers the watch face. The small "+
      "hand is resting near the " + hour + " on the dial.\n");
}
