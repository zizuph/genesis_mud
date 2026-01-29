/*
 * RMC - Statue
 * by Conan 1996
 *
 * The prize for the statue is 10 * (size + 1) * (material + 1)^2.
 * i.e. wooden miniature statue costs 10 plats and a
 * gigantic black eog statue 2000 plats.
 */

#pragma save_binary

inherit "/std/object";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <cmdparse.h>

#define RS_MATERIAL ({ "wood", "stone", "iron", "copper", "marble", "gold", "onyx", \
                      "black eog"})
#define RS_SIZE     ({"miniature", "small", "large", "huge", "gigantic"})
#define RS_DESC     ({"This idol must have cost quite much. You don't find these "+\
                      "things in a bazaar, they're made for certain people.", \
                      "The small statue's details are so life-like that it must "+ \
                      "have taken much time and money for artists to create it.", \
                      "The statue must have cost a fortune and it is clear that it is "+\
                          "raised in memory of an extremely rich person."})
string owner;
int material;
int size;
string desc;
string pose;

string *list;

mixed get_statue();

void
create_object()
{
    set_name("statue");
    set_short("very standard statue");
    set_long("This is a standard statue.\n");
    set_adj("standard");
    add_adj("very");

    add_prop(OBJ_M_NO_GET, "@@get_statue");
    add_prop(OBJ_M_NO_SELL, "You can't sell the statue!\n");
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_I_NO_GIVE,1);
    add_prop(OBJ_I_NO_STEAL,1);

    list = ({ });
}

void
init()
{
    ::init();

    add_action("bower",      "bow");
    add_action("polisher",   "polish");
    add_action("groveler",   "grovel");
    add_action("spitter",    "spit");
    add_action("puker",      "puke");
    add_action("kisser",     "kiss");
    add_action("worshipper", "worship");
    add_action("sigher",     "sigh");
    add_action("shower",     "show");
    add_action("rstatue",    "rstatue");
    /*add_action("lister",     "list");*/
}

int
bower(string str)
{
    if (str == "statue")
    {
        write("You bow to the statue, showing it your great admiration.\n");
        say(QCTNAME(TP)+" bows to the statue, showing "+HIS_HER(TP)+" great "+
            "admiration.\n");
        list += ({ TP->query_real_name()+" bowed to me." });
        return 1;
    }
    return 0;
}

int
polisher(string str)
{
    if (str == "statue")
    {
        write("You notice some dirt on the fine statue and decide to polish "+
              "the whole statue.\n");
        say(QCTNAME(TP)+" notices some dirt at the statue and decides to "+
            "polish the whole statue so that it's full beauty can be seen.\n");
        list += ({ TP->query_real_name()+" polished me." });
        return 1;
    }
    return 0;
}

int
groveler(string str)
{
    if (str == "statue")
    {
        write("You are so impressed by the statue that you fall down and "+
              "grovel in front of it.\n");
        say(QCTNAME(TP)+" is so impressed by the statue that "+HE_SHE(TP)+
            "falls down groveling in front of it.\n");
        list += ({ TP->query_real_name()+" groveled before me." });
        return 1;
    }
    return 0;
}

int
kisser(string str)
{
    if (str == "statue")
    {
        write("You kiss the face of the magnificent statue.\n");
        say(QCTNAME(TP)+" kisses the face of the magnificent statue.\n");
        list += ({ TP->query_real_name()+" kissed me." });
        return 1;
    }
    return 0;
}

int
worshipper(string str)
{
    if (str == "statue")
    {
        write("You kneel in front of the statue, showing your respect and "+
              "awe.\n");
        say(QCTNAME(TP)+" kneels in front of the statue, showing "+HIS_HER(TP)+
            " respect and awe.\n");
        list += ({ TP->query_real_name()+" worshipped me." });
        return 1;
    }
    return 0;
}

int
spitter(string str)
{
    write("You find nothing to polish the statue with, so you spit in your "+
          "hands and use them instead.\n");
    say(QCTNAME(TP)+" finds nothing to polish the statue with, so "+
        HE_SHE(TP)+" spits in "+HIS_HER(TP)+" hands and uses them instead.\n");
    list += ({ TP->query_real_name()+" spat at me." });
    return 1;
}

int
puker(string str)
{
    write("You feel you must puke, but the sheer presence of this wonderful "+
          "statue eases your stomach so much that the need completely disappears.\n");
    say(QCTNAME(TP)+" gets the feeling "+HE_SHE(TP)+" must puke, but the sheer "+
        "presence of this wonderful, not to mention magnificent, statue, eases "+
        HIS_HER(TP)+" stomach to such degree that "+HIS_HER(TP)+"need completely "+
        "disappears!\n");
    list += ({ TP->query_real_name()+" puked at me." });
    return 1;
}

int
sigher(string str)
{
    write("You sigh when you look at the statue. What a craftmanship! What "+
          "a magnificent piece of art!\n");
    say(QCTNAME(TP)+" sighs when "+HE_SHE(TP)+" looks at the beautiful "+
        "statue.\n");
    list += ({ TP->query_real_name()+" sighed at me." });
    return 1;
}

int
shower(string str)
{
    NF("Show the statue what? Respect?\n");
    if (str == "statue respect")
    {
        write("Why not bow or grovel in front of the statue? Or maybe polish "+
              "it?\n");
        return 1;
    }
    return 0;
}

int
lister()
{
    int i;
    
    if (TP->query_wiz_level() && sizeof(list))
    {
        write("The statue says: This has happened to me.\n");
        for (i = 0; i < sizeof(list); i++)
            write(" - "+list[i]+"\n");
        return 1;
    }
    return 0;
}

void
help(object ob)
{
    ob->catch_msg("The commands for this statue is: rstatue <help> <show> "+
                  "<force> <brag> <polish> <admire>.\n");
}

void
admire(object ob)
{
    ob->catch_msg("You show your statue great admiration, you're really "+
                  "proud of it!\n");
    tell_room(ENV(ob), QCTNAME(ob) + " shows the statue "+HIS_HER(ob)+
              "greatest admiration, "+HE_SHE(ob)+" has paid plenty for it "+
              "so it would be strange otherwise.\n", ({ob}) );
}

int
rstatue(string str)
{
    string *a, command, who;
    int x;
    
    if(TP->query_real_name() != owner)
        return 0;

    a = explode(str, " ");

    command = a[0];

    if (sizeof(a) > 1)
        who = a[1]; 

    x = 0;

    switch(command)
    {
    case "help":
        help(TP);
        x = 1;
        break;
    case "admire":
        admire(TP);
        x = 1;
        break;
    default:
        break;
    }
    return x;
}


get_statue()
{
    return 1;
}

void
newdesc()
{
    set_short(RS_SIZE[size]+" "+RS_MATERIAL[material]+" statue of " + capitalize(owner));
    set_long(break_string(
        "This is a statue of "+LANG_ADDART(desc)+" showing "+pose+" It's quality proves "+
        "that it is made by very skilled artists, professionals in working "+
        "with "+RS_MATERIAL[material]+". "+RS_DESC[((size)/2)]+" On a small "+
        "plaque on the foot of it, a name has been carved in, saying '"+
        capitalize(owner)+" - "+"Distinguished Member of the Rich Men's Club'. "+
        "You feel an urge of showing the statue your respect and awe.\n",60));
    set_adj(RS_MATERIAL[material]);
    add_adj(RS_SIZE[size]);
}

void
set_owner(string s)
{
    owner = s;
}

void
set_material(int s)
{
    material = s;
}

void
set_size(int s)
{
    size = s;
}

void
set_desc(string s)
{
    desc = s;
}

void
set_pose(string s)
{
    pose = s;
}
