#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Krynn/common/clock/clock.h"

inherit CAVERNS_BASE;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"cave",}));

int webs = 1;
int spider_spawned = 0;
object spider;

void
reset_tharkadan_room()
{
    set_searched(0);
    if(!webs)
    {
        tell_room(TO, "Curtains of thick webs fill the passage here, " +
            "blocking travel to your northwest.\n", ({ }) );
        webs = 1;
        spider_spawned = 0;
    }
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "lava_vent5","northwest","@@pass_webs");
    add_exit(CAVERNS + "lava_vent3","northeast",0);

    add_prop(ROOM_S_DARK_LONG, "An ancient lava vent. Without a light " +
        "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "It is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"volcano","dormant volcano","vent","lava vent","tunnel",
        "passage"}), "You stand within a lava vent of what was once an " +
        "ancient volcano, long dormant. Now it makes a large natural " +
        "tunnel leading deep underground.@@web_short@@\n");
    add_item(({"webs","web-filled tunnel","curtain",
        "curtain of thick webs","thick webs","thick curtains of webs",
        "curtains of webs","curtains"}), "@@webs_desc");

    add_cmd_item(({"webs","through webs","thick webs"}), "cut",
        "@@cut_webs");
    add_cmd_item(({"webs","through webs","thick webs"}), "burn",
        "@@burn_webs");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "vent","ground" }), 3);

    reset_tharkadan_room();
}

void
remove_webs()
{
    webs = 0;
}

string
web_short()
{
    if(webs)
        return " Its passage to the northwest blocked by a curtain " +
            "of thick webs.";
    else
        return "";
}

string
webs_desc()
{
    if(webs)
        return "The passage here is filled with thick curtains of " +
            "sticky webs. You may be able to cut or burn your way " +
            "through them.\n";
    else
        return "You notice traces of web on the walls of the passage " +
            "here.\n";
}


string
short_descr()
{
    if(webs)
        return "a web-filled tunnel, deep within a dormant volcano";
    else
        return "an ancient lava vent, deep within a dormant volcano";
}

string
long_descr()
{
    if(webs)
        return "You stand with an ancient lava vent, its passage down " +
            "to the northwest blocked by thick curtains of webs. The " +
            "vent continues upwards to your northeast.\n";
    else
        return "You stand within an ancient lava vent that leads down " +
            "into the depths of a dormant volcano. To your northeast " +
            "the vent leads upwards while it continues steeply down " +
            "to your northwest.\n";
}

object
query_wielded_weapon(object actor)
{
    object * weapons;
    
    weapons = filter(actor->query_weapon(-1), 
                     &operator(&)(W_SLASH) @ &->query_dt()); 
    if (!sizeof(weapons))
    {
        // Not wielding a slashing weapon
        return 0;
    }
    
    return weapons[random(sizeof(weapons))];
}

string
cut_webs()
{
    if(!webs)
        return "Cut through what?\n";

    if (!objectp(query_wielded_weapon(TP)))
    {
        write("You'll need a slashing weapon to cut through these " +
            "webs!\n");
        return "";
    }

    if(!spider_spawned)
    {
        write("As you begin cutting your way through the thick curtains " +
            "of webs, a creature of nightmares drops from the ceiling " +
            "above you!\n");
        say(QCTNAME(TP) + " begins cutting through the thick curtains " +
            "of webs, but disturbs a creature of nightmares that drops " +
            "from its hiding place above you!\n");

        spider = clone_object(LIVING + "giant_spider");
        spider->move(TO, 1);

        spider_spawned = 1;
        return "";
    }

    if(objectp(spider))
    {
        write("You can't cut through the webs while the spider is " +
            "still here!\n");
        return "";
    }

    write("You cut through the thick curtains of webs, clearing " +
        "a passage to the northwest.\n");
    say(QCTNAME(TP) + " cuts through the thick curtains of webs, " +
        "clearing a passage to the northwest.\n");
    webs = 0;
 
    return "";

}

int
filter_tool(object obj)
{
      if (obj->id("torch"))
        return 1;
      else 
        return 0;
}

string
burn_webs()
{
     if(!webs)
         return "Burn what?\n";

    object *torch;
    torch = filter(all_inventory(TP), filter_tool);
    int i, torch_lit, torch_no = sizeof(torch);

    if(!torch_no)
    {
        write("You need a torch to burn the webs!\n");
        return "";
    }

    for(i = 0; i<torch_no; i++)
    {
       if(torch[i]->query_lit())
           torch_lit = 1;
    }

    if(!torch_lit)
    {
        write("Your torch needs to be lit to burn the webs!\n");
        return "";
    }

    if(objectp(spider))
    {
        write("You can't burn the webs while the spider is here!\n");
        return "";
    }

    write("You raise your burning torch to the nearest curtain of " +
        "webs, and they incinerate with a loud WHOOMP!! You think you " +
        "hear a squeal from within the webs, but you put that down to " +
        "your imagination.\n");
    say(QCTNAME(TP) + " raises " +HIS(TP)+ " burning torch to the " +
        "nearest curtain of webs, and they incinerate with a loud " +
        "WHOOMP!\n");
    webs = 0;
 
    return "";
}


int
pass_webs()
{
    if(webs)
    {
        write("Your passage northwest is blocked by thick curtains of " +
            "webs.\n");
        return 1;
    }

    return 0;
} 

