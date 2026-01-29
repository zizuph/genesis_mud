#pragma strict_types

#include "defs.h"

#define AC 20

inherit "/std/armour"; 

int wear_alarm; 

public void 
create_armour() 
{
    set_name("chainmail"); 
    add_name("mail"); 
    set_adj("dark"); 
    add_adj("chilling"); 
    set_short("dark chilling chainmail"); 
    set_pshort("dark chilling chainmails"); 
    set_long("This chainmail shirt appears to be of excellent " + 
        "workmanship and very ancient origins, the steel rings " + 
        "themselves still gleam brightly beneath their dark finish, " + 
        "shining a deep blue. It does, however, have a strange " + 
        "sensation of wrath seeming to emanate from it, and " + 
        "you can feel a chill coming off it almost like waves " + 
        "washing over a shore.\n"); 
    set_ac(AC);
    set_am(({-2, 5, -3}));
    set_at(A_BODY | A_ARMS);
    set_af(TO);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, A_BODY));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 5);
}

public void
chill_me(object who)
{
    tell_object(who, "As you pull the dark chainmail, you feel a " +
        "bone-numbing chill permeate your body.\n");
    command("shiver");
}

public mixed
remove(object obj)
{
    if (!obj || obj != TO)
        return 0;

    else
        if (get_alarm(wear_alarm))
            remove_alarm(wear_alarm);
    return 0;
}

public mixed
wear(object obj)
{
    if (!obj || obj != TO)
        return 0;
    else if (obj == TO && !TP->query_prop(LIVE_I_UNDEAD))
    {
        wear_alarm = set_alarm(0.5, 0.0, &chill_me(TP));
    }
    return 0;
}
