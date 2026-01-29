inherit "/std/herb";
#include "/d/Kalad/defs.h"
#include <poison_types.h>
#include <herb.h>

/* When eaten, it will cause the eater's skin to glow, giving them a */
/* light source off their body for random(60) + 120 seconds */

void
create_herb()
{
    set_name("mushroom");
    add_adj("glowing");
    add_adj("yellow");
    set_short("glowing yellow mushroom");

    set_id_long("This is a large, broad-headed mushroom that is "+
    "bright yellow in color. It is glowing with a soft glow. It "+
    "is known as glowshroom, and is said to make a person's skin "+
    "glow if eaten.\n");

    set_unid_long("This is a large, broad-headed mushroom that is "+
    "bright yellow in color, and is glowing with a soft light. You "+
    "have never seen such a thing, it looks fascinating.\n");

    set_herb_name("glowshroom");
    set_amount(10);
    set_decay_time(1000);
    set_id_diff(35);
    set_find_diff(4);
    set_herb_value(700);
    set_ingest_verb("eat");
    set_effect(HERB_SPECIAL,"",0);
}

void
special_effect()
{
    object gob;
    seteuid(getuid());
    gob = clone_object("/d/Kalad/common/herbs/glowob");
    gob->move(TP);
    write("Your skin starts to glow a bright white color!\n");
    say(QCTNAME(TP)+"'s skin starts to glow a bright white color!\n");
    gob->set_remove_time(random(60)+120);
}
