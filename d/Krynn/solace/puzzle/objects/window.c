/* The window in the wall to break. ~solace/puzzle/objects/window */

inherit "/std/container";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/composite.h"
#include "/sys/filter_funs.h"
#include "/sys/stdproperties.h"

int fail_al;
int broken; /* Defines whether the window is broken or not. */

void add_object_to_me()
{
    seteuid(getuid(TO));
    clone_object(OBJECTS + "banana")->move(TO);
    clone_object(OBJECTS + "mouse_trap")->move(TO);
}

void set_broken(int i)
{
    broken = i;
}

int query_broken()
{
    return broken;
}

void create_container()
{
    set_no_show();

    set_name("window");
    add_name("compartment");
    set_adj("glass");
    set_long("No long description 'cos you can't see it!");

    add_prop(OBJ_M_NO_GET, 1);

    add_prop(CONT_I_VOLUME,     0);
    add_prop(CONT_I_WEIGHT,     0);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);

    add_prop(CONT_I_NO_REM, "@@can_get_object@@");

    add_object_to_me();
}

int can_get_object()
{
    object *players, gloves, hands, obj;

    if(query_broken())
    {
        players = FILTER_LIVE(I(E(TO)));

        if(!sizeof(players))
            return 1;

        else if(sizeof(players) > 1)
        {
            seteuid(getuid(TO));
            write_file(LOG + "errors", "More than one player in the "+
                "puzzle area.\n");
        }

        else
        {
            obj = players[0];

            hands = present("hands", obj);
            gloves = present("gloves", obj);

            if(!objectp(gloves) || (objectp(gloves) &&
               !call_other(hands, "is_worn_on_hands", gloves)))
            {
                obj->heal_hp(-(5 + random(6)));

                obj->catch_msg("You reach into the window but only succeed "+
                    "in cutting your wrist on the broken glass.\n");

                tell_room(E(TO), QCTNAME(obj)+" reaches in to get something "+
                    "from the window but only succeeds in cutting "+
                    POSSESSIVE(obj)+" wrist on the broken glass.\n", obj);

                if(obj->query_hp() <= 0)
                {
                    obj->catch_msg("You sever a major artery in your wrist "+
                        "and die writhing in agony.\n");

                    tell_room(E(TO), QCTNAME(obj)+" dies from loss of blood "+
                        "as "+PRONOUN(obj)+" severs a major artery in "+
                        POSSESSIVE(obj)+" wrist.\n", obj);

                    obj->do_die(TO);
                }
            }
            else
                return 0;
        }
    }
    return 1;
}
