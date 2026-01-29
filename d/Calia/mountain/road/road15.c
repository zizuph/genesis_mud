 /* Digit 02 FEB 95 
    Modified Maniac 3/3/95
    added praying for Spirit Circle entrance quest
    An glowing pentagram only appears here if a player is 
    on the Spirit Circle entrance quest AND if they are 
    here. Nobody else can see the pentagram, Jaacar, September 4, 2003
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/mountain/defs.h"

#define LIVE_I_INSERTED_AERIA_STAFF     "_live_i_inserted_aeria_staff"
#define LIVE_I_INSERTED_GU_STAFF        "_live_i_inserted_gu_staff"
#define LIVE_I_INSERTED_DIABRECHO_STAFF "_live_i_inserted_diabrecho_staff"
#define LIVE_I_INSERTED_PYROS_STAFF     "_live_i_inserted_pyros_staff"
#define LIVE_I_INSERTED_PSUCHAE_STAFF   "_live_i_inserted_psuchae_staff"
#define LIVE_I_PURIFIED_SPIRIT_ITEMS    "_live_i_purified_spirit_items"

string scop_quest = "";

void
create_room()
{
    make_the_room("The road leads northwest towards the west docks " +
        "of Calia and its capital Gelan, and southeast further into " +
        "this bleak unpopulated territory. To the west stands the monument " +
        "to the fallen. @@scop_quest@@\n");
    add_exit(ROAD+"road16","northwest");
    add_exit(ROAD+"road14","southeast");
    add_exit(ROAD+"m13", "west");
    add_exit(ROAD+"m14", "east");
    add_exit(ROAD+"m08", "north");
    add_exit(ROAD+"m09", "northeast");
    add_exit(ROAD+"m19", "south");
    add_exit(ROAD+"m18", "southwest");
}

string
scop_quest()
{
    if (TP->query_prop(LIVE_I_INSERTED_AERIA_STAFF) &&
        TP->query_prop(LIVE_I_INSERTED_GU_STAFF) &&
        TP->query_prop(LIVE_I_INSERTED_DIABRECHO_STAFF) &&
        TP->query_prop(LIVE_I_INSERTED_PYROS_STAFF) &&
        TP->query_prop(LIVE_I_INSERTED_PSUCHAE_STAFF))
    {
        scop_quest = "There is a glowing pentagram in the centre of ";
        scop_quest += "the road. You feel a strong urge to pray to ";
        scop_quest += "Psuchae.";
    }
    else
        scop_quest = "";

    return scop_quest;
}

int
do_pray(string str)
{
    if (!str)
        return 0;
    
    if (str != "to Psuchae")
        return 0;

    if (TP->query_prop(LIVE_I_INSERTED_AERIA_STAFF) &&
        TP->query_prop(LIVE_I_INSERTED_GU_STAFF) &&
        TP->query_prop(LIVE_I_INSERTED_DIABRECHO_STAFF) &&
        TP->query_prop(LIVE_I_INSERTED_PYROS_STAFF) &&
        TP->query_prop(LIVE_I_INSERTED_PSUCHAE_STAFF))
    {
        write("You kneel down in the centre of the glowing pentagram "+
            "and close your eyes. You pray with all of your heart to "+
            "Psuchae. You feel a very strange feeling. When you open "+
            "your eyes, you find yourself elsewhere.\n");
        say(QCTNAME(TP)+" kneels down in the centre of the road and "+
            "closes "+TP->query_possessive()+" eyes. "+
            capitalize(TP->query_pronoun())+" begins to pray. There is "+
            "a bright flash of light, causing you to look away for a "+
            "brief second. When you look back, "+TP->query_pronoun()+
            " is gone!\n");
        TP->move_living("M","/d/Calia/guilds/scop/temple/joinroom",1);
        TP->remove_prop(LIVE_I_INSERTED_AERIA_STAFF);
        TP->remove_prop(LIVE_I_INSERTED_GU_STAFF);
        TP->remove_prop(LIVE_I_INSERTED_DIABRECHO_STAFF);
        TP->remove_prop(LIVE_I_INSERTED_PYROS_STAFF);
        TP->remove_prop(LIVE_I_INSERTED_PSUCHAE_STAFF);
        TP->remove_prop(LIVE_I_PURIFIED_SPIRIT_ITEMS);
        return 1;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(do_pray,"pray");
}
