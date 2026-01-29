/* A hammer. ~solace/puzzle/weapons/hammer */

inherit "/std/weapon";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/language.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"

#define HIT_OBJ ({ ({ "clock",   "You strike the clock an almighty blow, "+   \
                                 "but it resists your attack unscathed." }),  \
                   ({ "torch",   "You strike the torch a glancing blow "+     \
                                 "with a dull THUD." }),                      \
                   ({ "stone",   "You hit the stone with THUMP, but "+        \
                                 "nothing seems to happen" }),                \
                   ({ "chair",   "The hammer bounces off the armchair!" }),   \
                   ({ "doorway", "You hit the doorway with the hammer, "+     \
                                 "making a slight dent in the stonework." }), \
                   ({ "lamps",   "Your hammer crumples the lamps slightly "+  \
                                 "but does not do any permanent damage." }),  \
                   ({ "sign",    "You smash the hammer into the sign, but "+  \
                                 "it makes little impression." }),            \
                   ({ "panel",   "The control panel CLANGs noisily as you "+  \
                                 "hit it, but no mark is made." }),           \
                   ({ "tube",    "You hit the tube really hard and are "+     \
                                 "surprised when nothing happens." })        })

void create_weapon()
{
    set_name("hammer");
    set_adj("large");
    add_adj("heavy");
    set_long("This hammer is quite large. It has a wooden handle and a metal "+
        "head.\n");
    add_prop("mystic_weapon", 1);

    set_hit(15);
    set_pen(8);

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);

    set_hands(W_ANYH);
}

void init()
{
    ::init();

    add_action("try_smash", "hit");
    add_action("try_smash", "smash");
}

int try_smash(string what)
{
    int i;
    mixed raw_items;
    string *tmp, *items = ({ });
    object player, room, window, *obj;

    if(!strlen(what))
    {
        notify_fail(C(query_verb())+" what?\n");
        return 0;
    }

    if(LIVING(E(TO)))
        player = E(TO);
    else
    {
        notify_fail("You have to be holding the hammer first.\n");
        return 0;
    }

    if(!objectp(query_wielded()) || query_wielded() != player)
    {
        notify_fail("You must be wielding the hammer first.\n");
        return 0;
    }

    if(E(player)->query_prop(ROOM_I_IS))
        room = E(player);
    else
        return 0;

    if(!sizeof(obj = FIND_STR_IN_OBJECT(what, room)))
    {
        raw_items = room->query_item();

        for(i = 0; i < sizeof(raw_items); i++)
            items += raw_items[i][0];

        if(member_array(what, items) == -1)
        {
            notify_fail("There isn't "+LANG_ADDART(what)+" here for you to "+
                query_verb()+".\n");
            return 0;
        }
    }
    else
        what = obj[0]->query_name();

    if(what == "window" || what == "glass window")
    {
        window = present("window", room);

        if(!objectp(window))
        {
            write("Bizarre error that shouldn't have happened.\n");
            return 1;
        }

        if(window->query_broken())
            player->catch_msg("You strike the window again for good luck, "+
                "but it seems already to be in quite a bad state.\n");
        else
        {
            window->set_broken(1);

            seteuid(getuid(TO));
            clone_object(WEAPONS + "glass")->move(room);

            player->catch_msg("You "+query_verb()+" the "+what+" with your "+
                "hammer and with a CRASH it explodes in a shower of glass.\n");
        }

        tell_room(E(player), QCTNAME(player)+" "+(random(2) ? "hit" : "smashe")+
            "s the "+what+" with "+POSSESSIVE(player)+" hammer.\n", player);
    }
    else
    {
        for(i = 0; i < sizeof(HIT_OBJ); i++)
        {
            if(what == HIT_OBJ[i][0])
            {
                player->catch_msg(HIT_OBJ[i][1]+"\n");

                tell_room(E(player), QCTNAME(player)+" hits the "+what+" "+
                    "with "+POSSESSIVE(player)+" hammer.\n", player);
                return 1;
            }
        }

        write("Your blows don't seem to have effect.\n");
    }
    return 1;
}
