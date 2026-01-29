/*
 *  /d/Gondor/guilds/rangers/obj/ron_brooch.c
 *
 *  The emblem carried by the Rangers of the North.
 *
 *  Original ranger tokens coded by Elessar.
 *
 *  Modification log:
 *  Alto, February 2002.
 *  Gwyneth, 12, July 2004: Re-Added ranger subloc code
 *
 */
#include "../rangers.h"
#include "/d/Gondor/defs.h"

inherit RANGERS_OBJ + "ranger_emblem";

#include <macros.h>
#include <wa_types.h>

void
create_emblem()
{
    set_name("brooch");
    add_name(({"ranger_brooch", "North_Ranger_Brooch", "RoN_emblem"}));
    set_adj("star-shaped");
    set_slots(A_NECK);
    seteuid(getuid(TO));
}

string
set_emblem_short(object pl)
{
    if (TP == environment(TO))
        return EmblemType + " star-shaped brooch of the Rangers of the North";

    return EmblemType + " star-shaped brooch";
}  

string
set_emblem_long(object pl)
{
    if (TP == environment(TO)) 
    {
        if (RANGERS_MEMBER(TP))
            return ("This is a brooch of " + EmblemType + " shaped like " +
                "a rayed star. It is the membership emblem of the Rangers " +
                "of the North. On the backside is enscribed: " + RangerName +
                ", Ranger of the North.\n");
        return ("This is a brooch of " + EmblemType + " shaped like a " +
            "rayed star. On the backside is enscribed: "+ RangerName +
            ", Ranger of the North.\n");
    }

    if (RANGERS_MEMBER(TP))
        return ("It is a brooch of " + EmblemType + " shaped like a rayed " +
            "star, the emblem of the Rangers of the North, which someone " +
            "must have dropped.\n");

    return ("It is a brooch of " + EmblemType + " shaped like a rayed " +
        "star.\n");
}

mixed
wear(object ob)
{
    if (RANGERS_MEMBER(TP) || TP->query_npc() || TP->query_wiz_level()) 
    {
        write("You wear the " + EmblemType + " brooch upon your left " +
            "shoulder.\nIt feels good to be back with the Rangers of the " +
            "North.\n");
        say(QCTNAME(TP) + " wears the " +
            (stringp(EmblemType) ? EmblemType : "") +
            "star-shaped brooch upon " + POSSESSIVE(TP) + " left shoulder.\n");

        this_player()->add_subloc(RANGER_S_SUBLOC, TO);
      return 1;
    }

    return "You try to wear the brooch, but it just drops off!\n";
}

public mixed
remove(object ob)
{
    this_player()->remove_subloc(RANGER_S_SUBLOC, TO);
    return 0;
}

