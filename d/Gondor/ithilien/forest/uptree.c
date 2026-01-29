/*
 * /d/Gondor/ithilien/forest/uptree.c
 *
 * NOT USED
 */


inherit "/d/Gondor/std/room";
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#define GROUND_ROOM "/d/Gondor/ithilien/forest/haradcamp4"

create_gondor()
{
    set_short("Among the branches of a giant oak");
    set_long("@@long_func");
    add_item(({"tree","oak"}),"@@exa_tree");
    add_item(({"branches","branch"}),"@@exa_branches");
    add_item("rope","@@exa_rope");
    seteuid(getuid(TO));
}

init()
{
    add_action("climb","climb");
    add_action("cut_rope","cut");
    add_action("untie","untie");
    add_action("free","free");
}

long_func()
{
    seteuid(getuid(TO));
    GROUND_ROOM->short();
    if (GROUND_ROOM->query_prisoned()) return "You are sitting on a branch in the great and majestic oak tree.\n"+
    "The green crown of the tree is all around you, rustling in the breeze.\n"+
    "A rope is tied to a branch here, and looking down along it, you see\n"+
    "that a human is hanging from it, his hands all tied up. You guess it\n"+
    "possible to climb down from the tree here.\n";
    return "You are sitting on a branch in the crown of the great and majestic\n"+
    "oak tree in the Ithilien forest. Green leaves rustle in the wind all\n"+
    "around you, but you find it impossible to climb further up because\n"+
    "the branches are likely to break by your weight. Climbing down seems\n"+
    "possible though.\n";
}

exa_tree()
{
    return "The oak tree looks old, almost ancient, judging by the size of\n"+
    "its green crown and the wide trunk. Down below you see a green clearing,\n"+
    "the branches of the oak reaching out over most of it.\n";
}

exa_branches()
{
    if (GROUND_ROOM->query_prisoned()) return "A rope is tied to one of the stout branches of the tree. Looking\n"+
    "down along the rope, you see a man hanging in it, his hands strung up\n"+
    "by the rope, stretched by the weight of his own body.\n";
    return "The branches are thick right here, but you notice that further up\n"+
    "they seem thinner, and will probably not hold your weight.\n";
}
climb(string str)
{
    if (!str || str != "down") {
    write("Climb where? Down?\n");
    return 1;
    }
    write("You climb down from the great oak tree.\n");
    TP->move_living("climbing down from the great oak tree",ITH_DIR+"forest/haradcamp4");
    return 1;
}

cut_rope(string str)
{
    string s1,s2,wep;
    if (sscanf(str,"%s with %s",s1,s2)==2) {
    if (s1 != "rope") {
      write("Cut what?\n");
      return 1; }
    wep = s2;
    if (present(wep,TP)) {
      if (is_weapon(present(wep,TP))) {
        do_cut_rope(TP);
        return 1;
        }
      write("That isn't sharp enough to cut the rope!\n");
      return 1;
      }
    write("You don't have that!\n");
    return 1;
    }
    if (str == "rope") {
    if (!got_weapon(TP)) {
      write("You don't have any sharp weapon to cut with!\n");
      return 1;
      }
    do_cut_rope(TP);
    return 1;
    }
    return 0;
}

is_weapon(object wep)
{
    if (!wep) return 0;
    if (function_exists("create_object",wep) != "/std/weapon") 
    return 0;
    if (wep->query_dt() == 2) return 1;
    return 0;
}

got_weapon(object pl)
{
    object *items;
    int n;
    if (!pl) return 0;
    items = all_inventory(pl);
    while (n < sizeof(items)) {
    if (is_weapon(items[n])) return 1;
    n++;
    }
    return 0;
}

do_cut_rope(object pl)
{
    write("You cut the rope, and the human slumps to the ground far below.\n");
    say(QCTNAME(pl)+" cuts the rope, and the human slumps to the ground far below.\n",pl);
    GROUND_ROOM->short();
    GROUND_ROOM->do_cut_rope();
    return 1;
}

