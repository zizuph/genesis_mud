/*
 *  /d/Gondor/guilds/rangers/obj/roi_amulet
 *
 *  The emblem carried by the Rangers of Ithilien.
 *
 *  Original ranger tokens coded by Elessar.
 *
 *  Modification log:
 *   Alto, February 2002.
 *   Gwyneth, May 2004
 *  Gwyneth, 12, July 2004: Re-Added ranger subloc code
 *
 */
#include "../rangers.h"
#include "/d/Gondor/defs.h"

inherit RANGERS_OBJ + "ranger_emblem";

#include <wa_types.h>
#include <macros.h>

void
create_emblem()
{
    set_name("amulet");
    add_name(({"ranger_amulet", "Ithilien_Ranger_Amulet", "RoI_emblem"}));
    set_adj("moon-shaped");
    set_slots(A_NECK);
    seteuid(getuid(TO));
}

string
set_emblem_short(object pl)
{
    if (TP == environment(TO))
    {
        return EmblemType + " moon-shaped amulet of the Rangers of Ithilien";
    }

    return EmblemType + " moon-shaped amulet";
}  

string
set_emblem_long(object pl)
{
    if (TP == environment(TO)) 
    {
        if (RANGERS_MEMBER(TP))
            return ("This is an amulet of " + EmblemType + " shaped like " +
                "a rising moon. It is the membership emblem of the Rangers " +
                "of Ithilien. On the backside is enscribed: " + RangerName +
                ", Ranger of Ithilien.\n");
        return ("This is an amulet of " + EmblemType + " shaped like a " +
            "rising moon. On the backside is enscribed: " + RangerName +
            ", Ranger of Ithilien.\n");
    }

    if (RANGERS_MEMBER(TP))
        return ("It is an amulet of " + EmblemType + " shaped like a " +
            "rising moon, the emblem of the Rangers of Ithilien, which " +
            "someone must have dropped.\n");

    return ("It is an amulet of " + EmblemType + " shaped like a " +
        "rising moon.\n");
}

mixed
wear(object ob)
{
    if (RANGERS_MEMBER(TP) || TP->query_npc() || TP->query_wiz_level()) 
    {
        write("You wear the " + EmblemType + " amulet around your neck.\n" +
            "It feels good to be back with the Rangers of Ithilien.\n");
        say(QCTNAME(TP) + " wears the " +
            (stringp(EmblemType) ? EmblemType : "") +
            " moon-shaped amulet around " + POSSESSIVE(TP) + " neck.\n");
        this_player()->add_subloc(RANGER_S_SUBLOC, TO);
        return 1;
    }

    return "You try to wear the amulet, but it just drops off!\n";
}

public mixed
remove(object ob)
{
    this_player()->remove_subloc(RANGER_S_SUBLOC, TO);
    return 0;
}

