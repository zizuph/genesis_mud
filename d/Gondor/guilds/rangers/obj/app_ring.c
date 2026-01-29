/*
 *  /d/Gondor/guilds/rangers/obj/app_ring.c
 *
 *  The emblem carried by the Apprentice Rangers.
 *
 *  Original ranger tokens coded by Elessar.
 *
 *  Alto, February 2002.
 *
 *  Modification log:
 *  Gwyneth, 2 April 2002: Cleaned up
 *  Gwyneth, 12, July 2004: Re-Added ranger subloc code
 */
#include "../rangers.h"

inherit RANGERS_OBJ + "ranger_emblem";
#include <wa_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

public void
create_emblem()
{
    set_name("ring");
    add_name(({"ranger_ring", "Apprentice_Ranger_Ring"}));
    set_slots(A_ANY_FINGER);
    seteuid(getuid(TO));
}

public string 
set_emblem_short(object pl)
{
    if (TP == environment(TO))
    {
        return EmblemType + " ring";
    }

    return EmblemType + " ring";
}  

public string 
set_emblem_long(object pl)
{
    if (TP == environment(TO)) 
    {
        if (RANGERS_MEMBER(TP))
            return ("This is a ring of " + EmblemType + ". It is the " +
                "membership emblem of the Apprentice Rangers. On the " +
                "backside is enscribed: " + RangerName + ", Apprentice " +
                "Ranger of the Westlands.\n");
        else
            return ("This is a ring of " + EmblemType + ". On the " +
                "backside is enscribed: " + RangerName + ", Apprentice " +
                "Ranger of the Westlands.\n");
    }

    if (RANGERS_MEMBER(TP))
        return ("It is a ring of " + EmblemType + ", the emblem of the " +
            "Apprentice Rangers.\n");
    else
        return ("It is a ring of " + EmblemType + ".\n");
}

public mixed
wear(object ob)
{
    if (RANGERS_MEMBER(TP) || TP->query_npc() || TP->query_wiz_level()) 
    {
        write("You wear the " + EmblemType + " ring on your finger.\n" +
            "It feels good to be back with the Apprentice Rangers of the " +
            "Westlands.\n");
        say(QCTNAME(TP) + " wears the " + 
            (stringp(EmblemType) ? (EmblemType + " ") : "") + "ring on " +
            POSSESSIVE(TP) + " finger.\n", TP);
        this_player()->add_subloc(RANGER_S_SUBLOC, TO);
        return 1;
    }
    else
        return "You try to wear the ring, but it just won't fit!\n";
}

public mixed
remove(object ob)
{
    this_player()->remove_subloc(RANGER_S_SUBLOC, TO);
    return 0;
}

