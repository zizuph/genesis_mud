/* The black-dragon's cave. ~mucalytic/hills/locations/cave1 */

inherit "/std/room";

#include "../defs.h"
#include "/sys/money.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

void reset_room()
{
    int i;

    if(!present("black-dragon"))
    {
        clone_object(CREATURES + "black_dragon")->move(TO);

        clone_object(WEAPONS + "blue_sword")->move(TO);

        for(i = 0; i < (1 + random(5)); i++)
            clone_object(OBJECTS + "gem")->move(TO);

        for(i = 0; i < (1 + random(5)); i++)
            MONEY_MAKE(5 + random(11), (random(2) ? "copper" : "silver"))->move(TO);

        for(i = 0; i < (1 + random(3)); i++)
            MONEY_MAKE(1 + random(5), (random(2) ? "gold" : "platinum"))->move(TO);
    }
}

void create_room()
{
    set_short("Inside a large cave in the foot-hills");
    set_long("You find yourself in a large cave in the side of a hill. "+
        "Above you, softly glowing stalagtites hang from the ceiling, "+
        "illuminating your surroundings with enough light to see clearly. "+
        "The walls of the cave have huge gash marks ripped into them and "+
        "the surroundings are also quite sooty, as if there had been a "+
        "fire here recently. The only exit is a hole in the cave wall "+
        "leading east.\n");

    add_exit(LOCATIONS + "path14", "east", 0, 3);

    add_prop(ROOM_I_LIGHT, 50 + random(50));
    add_prop(ROOM_I_HIDE, 50 + random(50));
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);

    add_item(({"cave", "large cave"}), "You're standing in it!\n");

    add_item(({"hole", "hole in the cave wall"}), "It leads east.\n");

    add_item(({"ceiling", "surroundings"}), "You notice nothing of "+
        "immediate interest.\n");

    add_item(({"marks", "gash marks", "huge gash marks"}), break_string(
        "The gash marks in the walls look as if they had been made by a "+
        "giant troll wieilding the world's largest battle-axe.\n", 75));

    add_item(({"wall", "walls", "cave walls", "walls of the cave"}),
        break_string("The cave walls bear huge deep gash marks, even though "+
        "they seem to be made from solid hill rock. A hole in the east wall "+
        "provides an exit from this place.\n", 75));

    add_item(({"stalagtites", "glowing stalagtites", "softly glowing "+
       "stalagtites"}), break_string("The stalagtites hang down like huge "+
        "lances from the ceiling. They seem to be covered with a strange "+
        "luminous moss that glows with a bizarre green-tinged light.\n", 75));

    reset_room();
}

void init()
{
    ::init();

    add_action("stop_get", "get");
    add_action("stop_get", "take");
}

int stop_get(string what)
{
    object dragon;

    if(strlen(what))
    {
        dragon = present("black-dragon");

        if(objectp(dragon))
        {
            if(dragon->query_awake())
            {
                switch(random(3))
                {
                    case 0:
                        dragon->command("emote roars: THAT'S ENOUGHT MORTAL. "+
                            "YOU HAVE BREATHED YOUR LAST.");
                        break;
                    case 1:
                        dragon->command("emote roars: THIEVING MORTAL. NOW "+
                            "YOU DIE!!!");
                        break;
                    case 2:
                        dragon->command("emote roars: I WILL KILL YOU NOW, "+
                            "MORTAL.");
                }

                TP->catch_msg(QCTNAME(dragon)+" attacks you!\n");
                dragon->catch_msg("You attack "+QTNAME(TP)+"!\n");
                tell_room(QCTNAME(dragon)+" attacks "+QTNAME(TP)+"!\n", ({ TP, dragon }));

                dragon->attack_object(TP);
            }
            else
                dragon->wake_dragon();
            return 1;
        }
    }
    return 0;
}

void leave_inv(object ob, object to)
{
    set_alarm(1.0, 0.0, "check_players");

    ::leave_inv(ob, to);
}

void check_players()
{
    object *players, dragon;

    players = filter(all_inventory(TO), "filter_living", TO);

    if(!sizeof(players))
    {

        dragon = present("black-dragon");

        if(objectp(dragon))
            if(dragon->query_awake())
                dragon->sleep_dragon();
    }
}
    
int filter_living(object obj)
{
    return(obj->query_prop(LIVE_I_IS) & !obj->query_npc());
}
