inherit "/std/object.c";
#include "/d/Emerald/defs.h"

public void
create_object()
{
    set_name("fumble_ob");
    set_no_show();
    add_prop(OBJ_I_NO_DROP, 1);
}

void
init()
{    
    ::init();
    EO->add_prop(LIVE_AS_ATTACK_FUMBLE, ({ "foobar" , "barfoo" }) );
    set_alarm( 20.0, 0.0, "end_fumble");
    return;
}

public void
end_fumble()
{
    EO->remove_prop(LIVE_AS_ATTACK_FUMBLE);
    tell_room( ENV(EO), "foobar, zuchini end_fumble.\n" );
    return;
}

public void
end_fumble_quickly()
{
    EO->remove_prop(LIVE_AS_ATTACK_FUMBLE);
    tell_room( ENV(EO), "foobar, zuchini, end_fumble, but quickly.\n" );
    return;
}

