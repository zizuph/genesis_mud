/*  
    Flying carpet, helps you get the lava tanks.
    Alternative to having throw skill to hit the lava tank.
    for pickaxe quest

    Made by: Maelstrom, 2016/05


*/

inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include "../defs.h"

create_object()
{
    set_name(({"carpet","old_carpet_quest"}));
    set_short("carpet");
    set_pshort("carpets");
    set_adj("old");
    set_long("A really really old carpet. Why would anyone keep this?\n");

	add_prop(OBJ_I_VOLUME, 1);
	add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_M_NO_DROP, "You'd better hang on to this. Your sixth sense tells you you're going to need it.\n");
    add_prop(OBJ_M_NO_GIVE, "You'd better hang on to this. Your sixth sense tells you you're going to need it.\n");
    add_prop(OBJ_M_NO_SELL, "You'd better hang on to this. Your sixth sense tells you you're going to need it.\n");   
}

int
player_solved_quest(object tp)
{
    int questIsDone = 0;
    if (tp->test_bit("Krynn", PICKAXE_GROUP, PICKAXE_BIT))
    {
        questIsDone = 1;
    }
    return questIsDone;
}

int
player_has_lava_tank()
{
    object *obSearch = FIND_STR_IN_OBJECT("lava_tank_quest", this_player());
    obSearch += FIND_STR_IN_OBJECT("miner_pickaxe", this_player());
    return sizeof(obSearch) > 0 || player_solved_quest(tp);
}

int
do_wish(string str)
{
    int found = 0;
    object c_item;
    object tp = this_player();
    string *data;
    string item;
    string place;    

string      *roof_inventions = ({
                "green tube",
                "saw contraption",
                "grey dagger",
                "purple shield",
                "blue lance",
                "flask launcher",
                "green pike",
                "white mace",
                "stars",
                "long bar"
            });

    if (!str)
    {
        return 0;
    }

    data = explode(str, " fly to ");
    if (sizeof(data) > 1)
    {
        item = data[0];
        place = data[1];
    }
    else
    {
        item = data[0];
        place = "";
    }

    if (item == "carpet") {
        
        if (place == "lava tank" || place == "red sword" || place == "red tank" || place == "tank")
        {
            found = 1;

            if (player_has_lava_tank())
            {
                tp->catch_msg("There's nothing to be gained anymore, you already have the lava tank. " +
                    "The carpet crumbles and fades away.\n");                
            }
            else
            {
                c_item = clone_object(OBJ_DIR + "lava_tank_quest");
                c_item->move(tp);
                tp->catch_msg("You wish this old carpet would fly to the lava tank, and so it does; " +
                    "you are surprised for a while, but you quickly overcome it, you dont know how much time you have. " +
                    "Being up close, it's an easy task to remove the tank from the sword; afterwards, " +
                    "you wish to be back on the ground, and so you are, but then the carpet crumbles and fades away, " +
                    "it would seem it only had one trip left on it.\n");
                tell_room(environment(tp), QCTNAME(tp) + " suddenly flies up in a carpet, grabs something and flies down.\n", tp);
            }
            remove_object();
        }
        else if (IN_ARRAY(place, roof_inventions))
        {
            found = 1;
            tp->catch_msg("You wish this old carpet would fly to the "+place+", and so it does; " +
                "you are surprised for a while, but you quickly overcome it, you dont know how much time you have. " +
                "Being up close, you check the "+place+" closely, but dont find anything of interest; afterwards, " +
                "you wish to be back on the ground, and so you are, but then the carpet crumbles and fades away, " +
                "it would seem it only had one trip left on it.\n");
            tell_room(environment(tp), QCTNAME(tp) + " suddenly flies up in a carpet, looks at something and flies down.\n", tp);
            remove_object();
        }
    }

    if (found > 0)
    {
        return 1;
    }

    notify_fail("wish carpet fly to where?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(do_wish, "wish");
    add_action(do_wish, "command");
    add_action(do_wish, "order");
    add_action(do_wish, "fly");
    add_action(do_wish, "sit"); 
}