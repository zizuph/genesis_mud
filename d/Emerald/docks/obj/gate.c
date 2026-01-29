inherit "/d/Emerald/std/door";

#include "../defs.h"

void
create_emerald_door()
{
    object l;
    set_name("gate");
    set_adj(({ "heavy", "ornate", "iron" }));
    set_open(PAVILION_OPEN);
    l = add_default_lock();
    l->set_key("NONE");

#if PAVILION_OPEN
    l->unlock();
#else
    l->lock();
#endif

    set_long("A heavy, ornate, iron gate.\n");
}
