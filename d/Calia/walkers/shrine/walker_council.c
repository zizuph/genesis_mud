


#pragma save_binary

inherit "/std/room";
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include <language.h>
#include "defs.h"
#include COUNCIL_HEADER

void
load_board()
{
    clone_object(COUNCIL_OBJECTS+"council_board")->move(THIS);
}

void
load_book()
{
    clone_object(COUNCIL_OBJECTS+"log_book")->move(THIS);
}

int
query_prevent_snoop()
{
    return 1;
}

void 
create_room()
{
    set_short("The Walkers Councilroom.\n");
    set_long("You are standing in the council chambers of the "+
        "Walkers of Thalassia.  This chamber is lit "+
        "by glowing rocks set into the walls.  There is a large "+
        "banner hanging on the western wall, and a scroll hanging "+
        "below it.  In one corner you see a small table.\n");

    add_item(({"rocks","glowing rocks"}),"The rocks are all different "+
        "sizes, and seem to be magical in nature.  They must be a gift "+
        "from the Elementals to light this chamber.\n");
    add_item(({"table","small table"}),"In the corner of the room "+
        "there is a small wooden table.  On top of the table is "+
            "a brown book which the council records its actions in.\n");
    add_item("scroll","There is writing on the scroll that you can read.\n");

    add_item("banner","On the banner you see:\n"+
            "council            - list council members.\n" +
            "assistants         - list council assistants.\n"+
            "mentors            - list all mentor/apprentice pairs.\n"+
            "trainban <player>  - ban <player> from training.\n" +
            "spellban <player>  - ban <player> from using spells.\n"+
            "expel <player>     - expel <player> from the Walkers guild.\n" +
            "rempunish <player> - remove current punishment from <player>.\n" +
            "addmem <player>    - add <player> to the Walkers Council.\n" +
            "remmem <player>    - remove <player> from the Walkers Council.\n"+
            "addass <player>    - add <player> as an assistant.\n"+
            "remass <player>    - remove <player> as an assistant.\n"+
            "fire apprentices   - list all Pyros Apprentices.\n"+
            "fire granted       - list all Firewalker Granted Members.\n"+
            "fire elders        - list all Firewalker Elder Members.\n"+
            "wind apprentices   - list all Aeria Apprentices.\n"+
            "wind granted       - list all Windwalker Granted Members.\n"+
            "wind elders        - list all Windwalker Elder Members.\n"+
            "wave apprentices   - list all Diabrecho Apprentices.\n"+
            "wave granted       - list all Wavewalker Granted Members.\n"+
            "wave elders        - list all Wavewalker Elder Members.\n"+
            "stone apprentices  - list all Gu Apprentices.\n"+
            "stone granted      - list all Stonewalker Granted Members.\n"+
            "stone elders       - list all Stonewalker Elder Members.\n"+
            "spirit apprentices - list all Psuchae Apprentices.\n"+
            "spirit granted     - list all Spiritwalker Granted Members.\n"+
            "spirit elders      - list all Spiritwalker Elder Members.\n"+            
            "\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    add_exit(SHRINE+"upper","east",0,1);
   
    load_book();
    load_board();   

    seteuid(getuid());
    COUNCIL_CODE->load_me();
}


/*
 * Function: enter_inv
 * Description: block unwanted people from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!living(ob)) return;

    if (!(COUNCIL_CODE->is_council_member(ob->query_name()) ||
        COUNCIL_CODE->is_calian_wiz(ob)) &&
        (SECURITY->query_wiz_level(ob->query_real_name()) < 39))
    {
        ob->move(from);
        ob->catch_msg("You are not permitted into the Walkers Council " +
            "chambers.\n");
        return;
    }

}

int
see_council(string str)
{
    return COUNCIL_CODE->see_council(str);
}

int
see_mentors(string str)
{
    return COUNCIL_CODE->see_mentors(str);
}

int
see_assistants(string str)
{
    return COUNCIL_CODE->see_assistants(str);
}

int
record_stop_spells(string str)
{
    return COUNCIL_CODE->record_stop_spells(str);
}

int
record_stop_train(string str)
{
    return COUNCIL_CODE->record_stop_train(str);
}

int
record_expel_player(string str)
{
    return COUNCIL_CODE->record_expel_player(str);
}

int
record_remove_punish(string str)
{
    return COUNCIL_CODE->record_remove_punish(str);
}

int
add_council_member(string str)
{
    return COUNCIL_CODE->add_council_member(str);
}

int
remove_council_member(string str)
{

    return COUNCIL_CODE->remove_council_member(str);
}

int
add_assistant(string str)
{
    return COUNCIL_CODE->add_assistant(str);
}

int
remove_assistant(string str)
{
    return COUNCIL_CODE->remove_assistant(str);
}

int
read_scroll(string str)
{
    if (str != "scroll")
        return 0;

    seteuid(getuid());
    tail(SPELL_LOG);
    return 1;
}

int
determine_fire(string str)
{
    if (str == "apprentices")
       return COUNCIL_CODE->see_fire_apprentices(str);
      
    if (str == "granted")
        return COUNCIL_CODE->see_fire_granted(str);

    if (str == "elders")
        return COUNCIL_CODE->see_fire_elders(str);

    NF("What do you want to list?\n");
    return 0;
}

int
determine_wind(string str)
{
    if (str == "apprentices")
       return COUNCIL_CODE->see_wind_apprentices(str);
      
    if (str == "granted")
        return COUNCIL_CODE->see_wind_granted(str);

    if (str == "elders")
        return COUNCIL_CODE->see_wind_elders(str);

    NF("What do you want to list?\n");
    return 0;
}

int
determine_wave(string str)
{
    if (str == "apprentices")
       return COUNCIL_CODE->see_wave_apprentices(str);
      
    if (str == "granted")
        return COUNCIL_CODE->see_wave_granted(str);

    if (str == "elders")
        return COUNCIL_CODE->see_wave_elders(str);

    NF("What do you want to list?\n");
    return 0;
}

int
determine_stone(string str)
{
    if (str == "apprentices")
       return COUNCIL_CODE->see_stone_apprentices(str);
      
    if (str == "granted")
        return COUNCIL_CODE->see_stone_granted(str);

    if (str == "elders")
        return COUNCIL_CODE->see_stone_elders(str);

    NF("What do you want to list?\n");
    return 0;
}

int
determine_spirit(string str)
{
    if (str == "apprentices")
       return COUNCIL_CODE->see_spirit_apprentices(str);
      
    if (str == "granted")
        return COUNCIL_CODE->see_spirit_granted(str);

    if (str == "elders")
        return COUNCIL_CODE->see_spirit_elders(str);

    NF("What do you want to list?\n");
    return 0;
}

void 
init()
{
    ::init();
    add_action(determine_fire, "fire");
    add_action(determine_wind, "wind");
    add_action(determine_wave, "wave");
    add_action(determine_stone, "stone");
    add_action(determine_spirit, "spirit");
    add_action(see_assistants, "assistants");
    add_action(see_mentors, "mentors");
    add_action(see_council, "council");
    add_action(record_stop_train, "trainban");
    add_action(record_expel_player, "expel");
    add_action(record_stop_spells, "spellban");
    add_action(record_remove_punish, "rempunish");
    add_action(add_council_member, "addmem");
    add_action(remove_council_member, "remmem");
    add_action(add_assistant, "addass");
    add_action(remove_assistant, "remass");
    add_action(read_scroll,"read");
}
