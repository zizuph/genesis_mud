#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#pragma save_binary

inherit "/d/Kalad/room_std";

void
create_room()
{
    set_short("In a dark hall");
    
    set_long("\n   You are walking along a short, cold hallway. The "+
    "walls and ceiling are made of smooth black stone, while the "+
    "floor is formed of polished black marble. Small red runes "+
    "decorate the sides of the walls.\n"+
    "   The air is think with the stench of death and decay. The "+
    "hallway continues further into darkness in both directions. "+
    "Here there stands a small statue in the center of the room.\n\n");
    
    add_item(({"statue","small statue"}),"It is made out of solid "+
    "onyx and stands on a silver platform. It is shaped like a "+
    "hand thrust up into the air, and in its palm it holds a "+
    "grim looking skull. The eyes of the skull are made of sparkling "+
    "emeralds. At the base of the statue, there burns a small "+
    "purple-black flame out of the ground, casting an eerie glow "+
    "on the statue, and reflecting malevolent looking sparkles off "+ 
    "the eyes. There are words written at the base.\n");

    add_cmd_item("words","read","@@read_words@@");
    add_item("words","@@read_words@@");

    INSIDE;
    add_item(({"runes","symbols"}),"@@query_k_rune@@");
    add_item("ceiling","The ceiling is made of solid black stone.\n");
    add_item("walls","The walls are made of dark black stone, with "+
    "a few runes inscribed on them.\n");
    add_item("floor","The floor is of solid polished black marble.\n");
   

    add_exit(KHIRAA_DIR(temple/rooms/t15),"west",0,-1);
    add_exit(KHIRAA_DIR(temple/rooms/t17),"east",0,-1);
    clone_object(KHIRAA_DIR(temple/doors/traindoor1))->move(TO);
    clone_object(KHIRAA_DIR(temple/doors/dkcoffindoor1))->move(TO);
}

string
query_k_rune()
{
    if(IS_LP(TP) || IS_DK(TP))
        return "They are praises to the Nameless one. All hail "+
        "unto Him, Lord of Eternity.\n";
    return "You do not know what they mean, but "+
    "they look very ancient.\n";
}

string
read_words()
{
    return
    "The blood of the sacrifices, "+
    "Do feed our Lord well, "+
    "Power of the Necromancers, "+
    "Stem from the Dark Hell, "+
    "Entry is only thus allowed, "+
    "To those who kneel down, "+
    "Before the incarnation of Him, "+
    "Such ways to be found.\n";
}

void
down_to_hell(object ob)
{
    tell_object(ob,"You slowly dissolve from away, and reappear in "+
    "another room....\n");
    tell_room(E(TO),QCTNAME(ob)+" slowly dissolves away and is gone.\n",
    ob);
    ob->move_living("M",KHIRAA_DIR(temple/rooms/sacrifice_chamber));
    tell_room(E(TO),QCTNAME(ob)+" slowly fades into view.\n");
}

int
do_kneel(string str)
{
    NF("Kneel before what?\n");
    if(str == "before statue" || str == "before Him" || 
       str == "before skull")
    {
        write("You kneel before the statue.\n");
        say(QCTNAME(TP)+" kneels before the statue.\n");
        tell_room(TO,"The eyes on the skull of the statue begin to "+
        "glow red.\n");
        set_alarm(4.5,0.0,&down_to_hell(TP));
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    AA(do_kneel,kneel);
}

