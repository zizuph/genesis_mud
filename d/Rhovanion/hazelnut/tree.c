inherit "/std/object";

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Rhovanion/defs.h"

static string uptree_file = "/d/Rhovanion/common/objects/uptree";
static string stump_file = "/d/Rhovanion/common/objects/stump";
static string fallen_file = "/d/Rhovanion/common/objects/fallen_tree";
static object room;
static int tree_hurt = 0;

void set_fallen_file(string arg)
{
    fallen_file = arg;
}

string query_fallen_file()
{
    return fallen_file;
}

void set_uptree_file(string arg)
{
    uptree_file = arg;
}

string query_uptree_file()
{
    return uptree_file;
}

void set_stump_file(string arg)
{
    stump_file = arg;
}

string query_stump_file()
{
    return stump_file;
}

mixed is_item_there(string item)
{
    string *stuff, *newadjs;
    object *everth;
    int i, j, k;

    if (!item)
        return 0;
    stuff = explode(item, " ");
    if (sizeof(stuff) == 1)
        return present(item, TP);

    everth = all_inventory(TP);
    for (i=0; i<sizeof(everth); i++)
    {
        if (everth[i]->query_name() != stuff[sizeof(stuff)-1])
            continue;

        newadjs = everth[i]->query_adjs();
        for (j=0, k=0; j<sizeof(stuff)-1; j++)
        {
            if (member_array(stuff[j], newadjs) != -1)
            {
                k++;
                newadjs -= ({ stuff[j] });
            }

            if (k == sizeof(stuff)-1)
                return everth[i];
        }
    }
    return 0;
}

string longdes()
{
    string text;
    text = "This massive tree looks like it has stood here for a long " +
        "time.  Compared to the trees of Mirkwood forest though it is only a " +
        "baby.  Its roots lie half exposed to the air, and its branches " +
        "are large and close together.  You could probably climb this tree " +
        "pretty easily.  ";

    switch(tree_hurt)
    {
        case 0: text += "\n"; break;
        case 3:
        case 2:
        case 1: text += "It has been slightly damaged by an axe.\n"; break;
        case 6:
        case 5:
        case 4: text += "It has been damaged by an axe.\n"; break;
        case 9:
        case 8:
        case 7: text += "It has been so badly scarred by an axe that it " +
                 "looks ready to fall over at any minute.\n"; break;
        default: text += "It is falling over.\n";
    }

    return text;

}

create_object()
{
    set_name("tree");
    set_short("massive tree");
    set_adj("massive");
    set_long("@@longdes@@");

    add_item(({ "roots", "root", "tree roots", "tree root" }),
        "The massive roots of the tree have grown partly out of the ground, " +
        "and have been weathered with exposure to the sun and wind.\n");

    add_item(({ "branches", "branch", "tree branches", "tree branch" }),
        "The branches hang low to the ground here, and continue all the way " +
        "up the tree where they seem to form some kind of natural platform.\n");

    add_item(({ "leaf", "leaves" }),
        "These leaves are broad and soft.\n");

    add_item(({ "bark", "trunk" }),
        "The bark of this tree is rough, and has numerous places that could " +
        "be used for handholds.\n");

    add_prop(OBJ_I_WEIGHT, 500000 + random(10000));
    add_prop(OBJ_I_VOLUME, 500000 + random(10000));
    add_prop(OBJ_I_NO_GET, 1);
}

init()
{
    ::init();
    add_action("climb", "climb");
    add_action("chop", "chop");
    add_action("burn", "burn");
}

int climb(string what)
{
    string file;

    NF("Climb what?\n");
    if ((what != "tree")  && (what != "the tree"))
        return 0;

    NF("You can't seem to get up it for no apparent reason, it probably " +
        "doesn't belong here.\n");
    if (sscanf(MASTER_OB(ENV(TO)), "%s", file) != 1)
        return 0;

    file = sprintf("%s-uptree", file);
    room = find_object(file);

    if (!room)
    {
      setuid();
      seteuid(getuid());
      if (file_size(file + ".c") >= 0)
      {
          file->teledningsanka();
          room = find_object(file);
      }
      else
      {
          write_file(file + ".c",  
              "inherit \"" + uptree_file + "\";\n");
          file->teledningsanka();
          rm(file + ".c");
          room = find_object(file);
          room->add_exit(ENV(TO), "down");
      }
    }

    if ((TP->query_skill(SS_CLIMB)) < (10 + random(15)))
    {
        TP->command("drop all");
        write("You slip and fall to the ground, which causes you to drop all " +
            "of your possessions.\n");
        say(QCTNAME(TP) + " tries to climb up the tree, but slips and lands " +
            "in a heap on the ground, dropping all of " + HIS(TP) + 
            " possessions.\n");
        return 1;
    }

    write("You scramble easily up the tree.\n");
    say (QCTNAME(TP) + " climbs up the tree.\n");
    TP->move_living("M", room);
    return 1;
}

void stump_me()
{
    object ob;
    setuid();
    seteuid(getuid());

    ob = clone_object(stump_file);
    ob->set_tree_file(MASTER);
    ob->move(ENV(TO));
    ob = clone_object(fallen_file);
    ob->move(ENV(TO));
    remove_object();
}

int chop(string str)
{
    object axe, *roominv;
    string axer;
    int i;

    NF("Chop down what with what?\n");
    if (!parse_command(str, TP,  "[down] [the] 'tree' 'with' [the] %s", axer))
        return 0;
    axe = is_item_there(axer);
    if (!axe)
        return 0;

    if (member_array("/std/weapon.c", inherit_list(axe)) == -1)
        return 0;

    NF("You can't chop down a tree with that!\n");
    if (axe->query_wt() != W_AXE)
        return 0;

    NF("It might work better if you wielded it!\n");
    if (axe->query_wielded() != TP)
        return 0;

    NF("You are too tired to do that.\n");
    if (TP->query_fatigue() < 10)
        return 0;

    if (!random(MAX(1,10-axe->query_likely_dull())))
        axe->set_dull(axe->query_dull() + 1);
    TP->set_fatigue(TP->query_fatigue() - 10);

    if(30000 < 
  random(axe->query_pen()*TP->query_skill(SS_WEP_AXE)*TP->query_stat(SS_STR))
      )
      tree_hurt++;

    tell_room(room, "The tree shakes as someone hits it from below " +
        "with an axe.\n");
    TP->catch_msg("You chop at the tree with your " + axe->query_short() +
        ".\n");
    tell_room(ENV(TP), QCTNAME(TP)+" chops at the tree with "+HIS(TP)+" "+
        axe->query_short() + ".\n", ({ TP }));
    if (tree_hurt < 10)
        return 1;

    write("You give it one final blow.  The wood begins to creak, and then " +
          "the tree topples over.\n");
    tell_room(ENV(TP), QCTNAME(TP)+" gives the tree one last mighty blow, "+
                      "and the tree creaks and falls over.\n");

    if (!room)
    {
        set_alarm(1.0, 0.0, "stump_me");
            return 1;
    }

    roominv = all_inventory(room);
    for (i=0; i<sizeof(roominv); i++)
    {
        if (living(roominv[i]))
        {
            roominv[i]->catch_msg("The tree tips and starts to fall swiftly " +
                "through the air!  You are thrown from the tree and land " +
                "hard on the ground.\n");
            roominv[i]->set_hp(roominv[i]->query_hp() -
                (100 - roominv[i]->query_skill(SS_ACROBAT)));
            tell_room(ENV(TO), QCTNAME(roominv[i]) + " comes flying " +
                "out of the tree!\n");
            roominv[i]->move_living("M", ENV(TO));
            roominv[i]->command("drop all");
            roominv[i]->command("cry");
            if (roominv[i]->query_hp() <= 0)
                roominv[i]->do_die(TO);
        }

        else
        {
            tell_room(ENV(TO), "Something comes flying out of the tree!\n");
                roominv[i]->move(ENV(TO));
        }
    }

    set_alarm(1.0, 0.0, "stump_me");
        return 1;
}

int burn(string sr)
{
    string dum;
    NF("Burn what?\n");
    if (!strlen(sr))
        return 0;
    if (sr != "tree")
        return 0;

    write("If you burned down the tree, the surrounding area would almost " +
        "certainly catch on fire, and you and all those around you would be " +
        "irrevocably killed.  It would probably be best not to do it.\n");
    return 1;
}
