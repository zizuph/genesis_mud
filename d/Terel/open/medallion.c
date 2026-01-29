/*
 *  /d/Terel/open/medallion.c
 *
 *  Enables wizards of Terel to do the following:
 *  1 - Check Terel quest bits in players
 *  2 - Check the status of all Zodiac gems in the game
 *  3 - add/remove/query race sizes from race size tracker
 *
 *  Obsolete code removed. General revision done.
 *  Torm, Oct 98    
 */

#pragma strict_types
#pragma no_inherit

inherit "/std/object";

#include "/d/Terel/include/Terel.h"
#include <stdproperties.h>
#include <macros.h>
#include <files.h>

//** Prototypes **//
private int do_delete_race(string s);
private int do_help(string s);
private int do_list_races();
private int do_set_race_size(string s);
private int gem_info();
private int list_quests(string s);
private string q_info(int grp, int bit);
private void remove_terel_medallion();


public void
create_object()
{
    set_name(({"medallion","_terel_wizard_medallion"}));
    set_short("medallion");
    set_long("A priceless medallion set with a big shiny "+
        "diamond.\n");
    add_prop(OBJ_M_NO_DROP,1);
}

public void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);

    if (!living(inv))
        set_alarm(0.1, 0.0, remove_terel_medallion);

    else if (SECURITY->query_wiz_dom(TP->query_name()) != "Terel") 
        set_alarm(0.1, 0.0, remove_terel_medallion); 
}

public void
init() 
{
    ::init();

    add_action(do_set_race_size, "addrace");
    add_action(do_delete_race,   "deleterace");
    add_action(do_list_races,    "listraces");
    add_action(do_help,          "help");
    add_action(list_quests,      "tquests");
    add_action(gem_info,         "tgem");
}

private int
do_set_race_size(string s)
{
    int size;
    string race;

    if (sscanf(s, "%s %d", race, size) != 2)
        return 0;

    RACE_SIZE_TRACKER->set_race_size(race, size);
    return 1;
}

private int
do_delete_race(string s)
{
    if (!strlen(s))
        return 0;

    if (!objectp(RACE_SIZE_TRACKER))
        RACE_SIZE_TRACKER->load_object();

    RACE_SIZE_TRACKER->delete_race(s);
    return 1;
}

private int
do_list_races()
{
    if (!objectp(RACE_SIZE_TRACKER))
        RACE_SIZE_TRACKER->load_object();

    RACE_SIZE_TRACKER->query_races_tracked();
    return 1;
}

private int
do_help(string arg) 
{
    if (!strlen(arg) || arg != "medallion") 
        return 0;

    write("Available commands:\n"+
        "tquests [<who>]        Display the Terel quests "+
            "<who> has solved.\n"+
        "tgem                   Show status of Zodiac "+
            "gems in the game.\n"+
        "addrace <race> <size>  List <race> as <size> "+
            "in race size tracker.\n"+
        "deleterace <race>      Remove <race> from race size "+
            "tracker.\n"+
        "listraces              Display all races tracked.\n"+
        "help medallion         Display this message.\n");
    return 1;
}

private int
list_quests(string str)
{
    int i, grp, bit;
    object ob;
  
    if (!strlen(str)) 
        ob = this_player();
    else 
        ob = find_player(str);
  
    if (!objectp(ob))
    { 
        notify_fail("Couldn't locate '"+str+"'.\n");
        return 0;
    }

    write("Object: " + file_name(ob) + " (interactive)\n");     
    write("Player: " + ob->query_name() + " has solved:\n"+
        "-----------------------------------------------------------\n");
    for (grp=0; grp<=4; grp++) 
    {
        for (bit=0; bit<=19; bit++) 
        {
            if (ob->test_bit("Terel", grp, bit)) 
            {
                write("Group: "+grp+"   Bit: "+
                    sprintf("%2d", bit)+"  "+q_info(grp, bit)+"\n");
            }
        }
    }
    write("-----------------------------------------------------------\n\n");
    return 1;
}

private string
q_info(int grp, int bit)
{
    if (grp == 0) 
    {
        switch(bit) 
        {
            case 0 : return "Orc Fire             (Zodiac - Orange)";
            case 1 : return "Green Balance        (Zodiac - Green)";
            case 2 : return "Red Death            (Zodiac - Red)";
            case 3 : return "Maze and Box         (Zodiac - Violet)";
            case 4 : return "Lost Child           (Ribos/Calathin)";
            case 5 : return "Jester's Hat         (Gypsy 1)";
            case 6 : return "Shave Beardy Woman   (Gypsy 2)";
            case 7 : return "Wrestler's Belt      (Gypsy 3)";
            case 8 : return "Go Juggling          (Gypsy 4)";
            case 9 : return "Walk Tight Rope      (Gypsy 5)";
            case 10 : return "Magician's Treasure  (Gypsy 6)";
            case 11 : return "Release Spectre      (Gypsy 7)";
            case 12 : return "Rescue Virgin        (Mansion)";
            case 13 : return "Porcia Riddle        (Zodiac - Yellow)";
            case 14 : return "Tear Tapestry        (Thane)";
            case 15 : return "Dead DarkOne         (Thane)";
            case 16 : return "Mystic Entrance      (Mumon)";
            case 17 : return "Final Zodiac         (Mansion)";
            case 18 : return "Mine Blue Gem        (Zodiac - Blue)";
            case 19 : return "Witch's Ring         (Garden/Mansion)";
        }
    } 

    else if (grp == 1) 
    {
        switch(bit) 
        {
            case 0 : return "Lost cat             (Enchanted garden)";
            case 1 : return "Lost bracelet        (Enchanted garden)";
            case 2 : return "Kill the bug queen   (Enchanted garden)";
            case 3 : return "Kill the evil dragon (Ribos)";
            case 4 : return "Rescue the prisoner  (Mansion/dungeons)";
            case 5 : return "Dungeon 2            (Dungeons)";
            case 6 : return "Vote room puzzle     (Tomb)";
            case 7 : return "Missing sandal       (Tomb/Road_s)";
            case 8 : return "Musician's torment I (Janus/Calathin)";
            case 9 : return "Batshit              (cottage/orc_cave)";
            case 10: return "Tune Harpsichord     (Minstrel/mansion)";
            case 11: return "Ribos Crime          (Ribos)";
            case 12: return "Gardener's Gloves    (Calathin)";
            case 13: return "Bandit Treasure      (Silver Forest)";
            case 14: return "Caravan Raid         (Silver Forest)";
            case 15: return "Hunt Assassin         (North/South Ports)";
        }
    }
    else if (grp == 2) 
    {
        switch(bit) 
        {
            case 0 : return "Calathin Enemy        (Calathin)";

        }
    }

    return "*** That quest isn't stored in the medallion ***";
}

private int
gem_info()
{
    int i;
    object *ul, gem;
    
    ul = users();
    
    for (i=0; i<sizeof(ul); i++) 
    {
        gem = present("Terel_ZODIAC_gem", ul[i]);
        if (!objectp(gem)) 
            continue;
        if (ul[i]->test_bit("Terel", 0, 17))
            write(sprintf("%-12s 1 %s\n", ul[i]->query_name(), gem->query_auto_load()));
        else
            write(sprintf("%-12s 0 %s\n", ul[i]->query_name(), gem->query_auto_load()));
    }
    return 1;
}

private void remove_terel_medallion() { remove_object(); }

public string query_auto_load() { return MASTER; }
