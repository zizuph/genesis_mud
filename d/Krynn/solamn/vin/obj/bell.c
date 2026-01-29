/* Modified by Percy */
/* further modified by Teth for new vkeep Jan 97 */
    
inherit "/std/object";

#include <ss_types.h>
#include <macros.h>
#include "../knight/guild.h"

private string *areas = ({"VROOM",
        "/d/Krynn/solamn/splains/", });

private int num_areas = sizeof(areas);

int
in_bell_zone(object ob)
{
    string str;
    int i;
    
    /* If the player was removed or is not in a room, 
    he should not be affected */
    if (!ob || !environment(ob) )
        return 0;
    
    /* Get the filename of the room */
    str = file_name(environment(ob));
    
    /*
    * Check to see if the filename matches anything in the areas array
        */
    for (i = 0; i < num_areas; i++)
    /*
    * Only compare the first N characters of the room's filename.
    * N == the length of the string in the AREAS array
    */
    if (areas[i] == str[0..strlen(areas[i])-1])
        return 1;
    
    /* The player should not be affected */
    return 0;
}


void
create_object()
{
    set_name("rope");
    add_name("k_bell");
    set_short("long rope");
    set_long("This is a long hemp rope that appears to be " +
        "attached to something high above, most likely a " +
        "bell. If that's the case, then pulling the rope and " +
        "ringing the bell would be a way to summon Knights to " +
        "defend Vingaard Keep against attack. Misuse of it " +
        "wouldn't be proper.\n");
    add_prop(OBJ_M_NO_GET, "The rope is securely fastened to the bell.\n");
}

init()
{
    ADA("pull");
}

pull(str)
{
    object *players, *ppl;
    int i;
    
    NF("Pull what?\n");
    if (str != "rope" && str != "long rope")
        return 0;
    
    write("You yank hard on the rope.\n");
    SAY(" yanks hard on the rope.");
    
    ppl = filter(users(), in_bell_zone);
    ppl->catch_msg("You hear the tolling of a bell high above "+
        "Vingaard Keep.\n");
    
    if (MEMBER(TP))
        {
        players = users();
        for (i = 0; i < sizeof(players); i++)
        {
            if (players[i]->query_knight_level())
                players[i]->catch_msg("\n\n\n\n\n"+
                "You hear a strange mystical bell sounding in "+
                "your head, warning you of an ATTACK on " +
                "Vingaard Keep. From the sound of it, you'd think " +
                QNAME(TP) + " is ringing the bell.\n\n\n\n\n\n");
        }
    } 
    return 1;
    
}

