/* The fish hooked by the fishingrod */
inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

#define TP      this_player()
#define TO      this_object()
#define ETO     environment(TO)

int aid;

public void
tell_env(string msg)
{
    if (!ETO) return;
    
    if (living(ETO)) {
        ETO->catch_msg(msg);
    } else if (ETO->query_prop(ROOM_I_IS)) {
        tell_room(ETO, msg);
    }
}

public void
wriggle()
{
    tell_env("The " + short() + " wriggles back and forth " +
             "as it slowly suffocates.\n");
}

public void
die()
{
    if (aid) {
        remove_alarm(aid);
        aid = 0;
    }
    tell_env("The " + short() + " dies. You realize that it has been in " +
             "the air for too long.\n");
    remove_adj("raw");
    add_adj("dead");
    set_short("dead fish");
    set_long("A dead fish.\n");
    change_prop(OBJ_I_VALUE, 6);
}

public
create_food()
{
    set_name("fish");
    set_adj("raw");
    set_short("raw fish");
    set_long("The fish is wriggling about as it " +
             "attempts to get back in to water. " +
             "You feel very mean as the fish slowly suffocates!\n");

    add_prop(OBJ_I_WEIGHT, 180);
    add_prop(OBJ_I_VOLUME, 184);

    set_amount(65);
    aid = set_alarm(10.0, 15.0, wriggle);
    set_alarm(127.0, -1.0, die);
    add_prop(OBJ_I_VALUE,12);
}
