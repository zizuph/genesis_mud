inherit "/std/object.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void create_object()
{
    set_name("_recital_");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL, 1);

    set_no_show();
}

void init()
{
    ::init();

    add_action("do_recite","recite");
    add_action("do_recite","olorin");
    add_action("do_recite","boromir");
    add_action("do_recite","estel");
    add_action("do_recite","rings");
    add_action("do_recite","ashnazg");
}

string olorin()
{
    return "\n"+
        "    Many are my names in many countries.\n"+
        "      Mithrandir among the Elves; Tharkun to the Dwarves.\n"+
        "        Olorin I was in my youth in the West that is forgotten.\n"+
        "          In the South Incanus; in the North Gandalf;\n"+
        "            To the East I go not.\n\n";
}

string estel()
{
    return "\n"+
        "    All that is gold does not glitter,\n"+
        "      Not all those who wander are lost;\n"+
        "    The old that is strong does not whither,\n"+
        "      Deep roots are not reached by the frost.\n\n"+
        "    From the ashes a fire shall be woken,\n"+
        "      A light from the shadows shall spring;\n"+
        "    Renewed shall be the blade that was broken;\n"+
        "      The crownless shall again be king.\n\n";
}

string boromir()
{
    return "\n"+
        "    Seek for the Sword that was broken:\n"+
        "      In Imladris it dwells;\n"+
        "    There shall be counsels taken\n"+
        "      Stronger than Morgul-spells.\n"+
        "    There shall be shown a token\n"+
        "      That Doom os near at hand,\n"+
        "    For Isildur's Bane shall waken,\n"+
        "      And the Halfling forth shall stand.\n\n";
}

string rings()
{
    return "\n"+
        "    Three Rings for the Elven-kings under the sky,\n"+
        "      Seven for the Dwarf-lords in their halls of stone,\n"+
        "    Nine for the Mortal Men doomed to die,\n"+
        "      One for the Dark Lord on his dark throne\n"+
        "    In the Land of Mordor where the Shadows lie.\n"+
        "      One Ring to rule them all, One Ring to find them,\n"+
        "      One Ring to bring them all and in the darkness bind them\n"+
        "    In the Land of Mordor, where the Shadows lie.\n\n";
}

string ashnazg()
{
    return "\n"+
        "    Ash nazg durbatuluk, ash nazg gimbatul, ash nazg\n"+
        "         thrakatuluk agh burzum-ishi krimpatul.\n\n";
}

int do_recite(string str)
{
    string  vb = query_verb(),
            vers,
            text;

    object  room;

    if(TP != ENV(TO))
        return 0;

    if(vb != "recite")
    {
        if(stringp(str))
           return 0;
        else
            vers = vb;
    }
    else if(!stringp(str))
        return 0;
    else
        vers = str;

    switch(vers)
    {
        case "olorin":  text = olorin();  break;
        case "boromir": text = boromir(); break;
        case "estel":   text = estel();   break;
        case "rings":   text = rings();   break;
        case "ashnazg": text = ashnazg(); break;
        default: return 0; break;
    }

    room = ENV(TO);
    while(!room->query_prop(ROOM_I_IS)) 
        room = ENV(room);

    tell_room(room, text);

    return 1;
}

string query_auto_load()
{
    return MASTER + ":";
}

