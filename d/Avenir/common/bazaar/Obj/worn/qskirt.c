// file name:    ~Avenir/common/bazaar/Obj/worn/qbelt
// creator(s):    Grace  May  1995
// last update:   Lilith 28 July 1997: added some emotes.         
// purpose:       ornamentation for the lovely dancer
// note:          It is a belt of veils.         
// bug(s):                 
// to-do:  

inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/keep";

#include "/d/Avenir/common/bazaar/bazaar.h"
#include "/d/Avenir/common/clubs/dance/dance_club.h"
#include <wa_types.h>

void
create_armour()
{
    set_name("skirt");
    add_name("belt");
    add_pname(({"clothes", "clothing"}));
    set_short("skirt of multi-colored veils");
    add_adj(({"multi-colored", "multicolored", "colored"}));
    set_long ("A silk belt to which several veils are attached,"+
            " forming a skirt.\n"+
            "When worn properly, the veils swirl about the legs "+
            "with every step, giving provocative glimpses of "+
            "bare flesh.\n");
    add_item("veils", "There are seven of them. They are rather "+
	"sheer and vibrant in colour.\n");
    add_cmd_item(({"veil", "veils"}), ({"pull","pull off belt"}),
        "You try to pull the veils off of the belt, but stop "+
        "when you realize that you will tear the fabric.\n");

    set_ac (5);
    set_am(({ 0, 0, 0}));
    set_at (A_WAIST);

    add_prop(OBJ_I_VALUE,  120);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 500);
}

static int
dtwirl(string str)
{
    string cqv;
    cqv = capitalize(query_verb());

    if (str) 
    {
        notify_fail(cqv +" "+ str +" cannot be done.\n");
        return 0;
    }

    if (!query_worn()) 
    {
        write("You need to be wearing the "+ short() +", first.\n");
        return 1;
    }

    if (TP->query_gender() == G_MALE)
    {
        write("Wouldn't you look silly doing that?!\n");
        return 1;
    }
    /* Dancers do it right */
    if (TP->query_prop(DANCE_PROP))
    {
        write("You twirl gracefully around, setting the multi-coloured "+
            "veils of your skirt aflutter.\n");
        say(QCTNAME(TP) +" twirls gracefully around, setting her multi-"+
            "coloured veils aflutter.\n");
        return 1;
    }

    /* Non-dancers don't quite succeed */    
    write("You twirl around, trying to set the multi-coloured veils "+
        "aflutter, but they just swish a bit and then settle.\n");
    say(QCTNAME(TP) +" twirls around. Her "+ short() +" makes a "+
        "slight swishing sound, then settles.\n");
    return 1;
}

static int
dexpose(string str)
{
    string cqv;
    cqv = capitalize(query_verb());

    if (!query_worn()) 
    {
        write("You need to be wearing the "+ short() +", first.\n");
        return 1;
    }

    if (TP->query_gender() == G_MALE)
    {
        write("Wouldn't you look silly doing that?!\n");
        return 1;
    }

    if (!str) 
        str = "thigh";
    if (str == "thigh" || str == "leg" || str == "ankle")
    {
        /* Dancers do it right */
        if (TP->query_prop(DANCE_PROP))
        {
            write("With a slight twist of your hips you cause a veil "+
                "to rustle, briefly exposing a slender, shapely "+ 
                str +".\n");
            say(QCTNAME(TP) +" rustles a veil, briefly exposing a "+
                "slender, shapely "+str +".\n");
            return 1;
        }
        /* Non-dancers don't quite succeed */    
        write("You twist your hips awkwardly, trying to expose your "+
            str +" by making the veils rustle.\n");
        say(QCTNAME(TP) +" does something that makes her "+ short() +
            " rustle.\n");
        return 1;
    }
    else
    {
        notify_fail(cqv +" "+ str +" cannot be done.\n");
        return 0;
    }
}

void
init()
{
    ::init();
    add_action(dtwirl,  "dtwirl");
    add_action(dexpose, "dexpose");
    add_action(dtwirl,  "twirl");
    add_action(dexpose, "expose");
}
   
