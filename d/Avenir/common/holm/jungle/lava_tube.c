//-*-C++-*-
// file name:    /d/Avenir/common/holm/jungle/lava_tube.c
// creator(s):   Lilith May 31 1997
// revised:
// purpose:      Lava tube to slide down      
// note:         
// bug(s):
// to-do:
#pragma strict_types

/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"
#include <language.h>

#define ENTER  "/d/Avenir/common/holm/jungle/hole"
#define END    "/d/Avenir/common/holm/jungle/lf11"

object *fall_slide = ({ });
string *land = ({"bottom", "head", "right side", "left side", "feet"});
string *tells = ({"You are launched into the air for a moment.\n",
        "You skid over something rough, hurting your bottom.\n",
        "You are going so fast the air seems to scream past "+ 
        "your ears.\n",
        "Something rushes up toward you in the oppressive "+ 
        "darkness.\n",
        "A horrible stench invades your nostrils as you spiral "+
        "downward into darkness.\n",
        "You crash and tumble in the darkness, falling faster "+ 
        "with each passing second.\n"});

void create_domain_room()
{
    set_short("Falling into darkness");
    set_long("Tumbling in darkness down a lava tube.\n");
    add_prop(ROOM_S_DARK_LONG, "Tumbling in darkness down a lava tube.\n");
    add_prop(ROOM_I_LIGHT, -10);
    IN;
}

void falling_down(int pl, object ob, int i)
{
    string where;

    if (!ob) 
    {
        fall_slide -= ({ 0 });
        if (pl)
            ENTER->set_full(0);
        return;
    }
    if (environment(ob) != this_object()) 
    {
        fall_slide -= ({ ob });
        if (pl) 
            ENTER->set_full(0);
        return;
    }
    if (i > 3) 
    {
        if (interactive(ob)) 
        {
            where = (land[random(sizeof(land))]);
            ob->catch_msg("The bottom falls out of the lava tube!\nYou "+
                "land hard on your "+ where +" and slide for another "+
                "meter.\n");
            tell_room(END, QCTNAME(ob)+" falls out of the lava tube and "+
                "lands hard on "+ ob->query_possessive()+ " "+ where +
                ".\n", ob);
            ENTER->set_full(0);
            ob->move_living("M", END);
        }
        else 
        {
            tell_room(END, capitalize(LANG_ASHORT(ob)) +" tumbles from "+
                "the lava tube.\n");        
            ob->move(END);
        }
        fall_slide -= ({ ob }); 
        return;
    }
    if (interactive(ob))
        ob->catch_msg(tells[random(sizeof(tells))] + "\n\n\n\n\n\n"); 
    set_alarmv(2.0, 0.0, "falling_down", ({ pl, ob, i + 1 })); 
}

void enter_inv(object ob, object from)
{
    int pl;
    ::enter_inv(ob, from);

    if (member_array(ob, fall_slide) == -1) 
    {
        pl = interactive(ob);
        set_alarmv(1.5, 0.0, "falling_down", ({ pl, ob, 0 })); 
    }
}

