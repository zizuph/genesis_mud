// file name:    marsh_hill
// creator(s):   Cirion, Feb 14, 1996
// last update:  Cirion, Apr 11, 1996 - put in quest functions
// purpose:      This is the area where the bury bones quest
//               can be solved. See /QUESTS/bury_bones.doc
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/dead";
inherit "/d/Avenir/inherit/quest";

#include "/d/Avenir/common/port/bury_bones.h"
#include "../dead.h"

int go_down();
void reset_room();

object   hole,
         naiad;
int      called,
         won;

void create_room()
{
    set_short("small hillock");

    set_long("This is a small hillock within a barren marsh. The ground "
        +"is rather dry here, and the dirt is soft and black."
        +"@@oak_tree@@@@see_hole@@ A "
        +"path circles around the hill to the north, east, and west, and "
        +"falls off into the dismal swamp to the south.\n");

    add_item(({"tree", "oak", "oak tree"}), "@@exa_tree@@");
    add_item(({"ground", "earth", "dirt"}), "The dirt is dark and soft, "
        +"suitable for burying things in.\n");

    add_exit(MARSH+"marsh52", "south", "@@go_down", 1);
    add_exit(PATH+"shore21", "west", "@@go_down", 1);
    add_exit(PATH+"shore22", "north", "@@go_down", 1);
    add_exit(PATH+"shore23", "east", "@@go_down", 1);

    seteuid(getuid(TO));
    reset_room();
}

string 
oak_tree()
{
    if (!won)
        return " A withered oak tree, long dead, rises up from "+
               "the center of the hill.";
    else
        return " In the centre of the hill stands a large oak "+
               "tree in full bloom, the only sign of life that can "+
               "be seen from here.";
}

string 
see_hole()
{
    if (present(HOLE_ID))
        return " A large hole has been dug into the soil beneath "+
               "the tree.";
    else
        return "";
}

string 
exa_tree()
{
    if (!won)
        return "Its arms are long and gnarled, freezing it in "+
               "a tortured pose of anguish.\n";
    else
        return "Inexplicably, it is in the full bloom on "+
               "life, lush foliage forming at its top.\n";
}

void 
sprout()
{
    int    mak, i;
    object *oblist = filter(all_inventory(TO), interactive);

    tell_room(TO, "Suddenly the withered oak tree starts to "
         +"sprout leaves and bloom with life!\n");

    for (mak=0;mak<sizeof(oblist);mak++)
    {
        oblist[mak]->catch_msg("You feel your wounds heal and "
            +"all your fatigue vanishes.\n");
        oblist[mak]->set_hp(oblist[mak]->query_max_hp());
        oblist[mak]->set_mana(oblist[mak]->query_max_mana());
        oblist[mak]->set_fatigue(oblist[mak]->query_max_fatigue());
    }
}

void
reset_room()
{
    object hole = present(HOLE_ID, TO);
    called = 0;

    if (won)
    {
        tell_room(TO, "The oak tree withers and dies.\n");
        won = 0;
    }

    if (hole)
    {
        tell_room(TO, "The hole fills up with moist earth.\n");
        hole->remove_object();
    }

    return;
}

int 
go_down()
{
    write("You descend the small hillock.\n");
    return 0;
}

void
enter_inv(object what, object from)
{
  ::enter_inv(what, from);

    // Most shovels move some sort of 'hole' into the room
    // when they dig...
    if(!living(what) && ( what->id("hole") || what->id("pit") || 
        what->id("trench") ) && !what->id(HOLE_ID))
    {
        what->remove_object();
        if(!present(HOLE_ID))
            clone_object(DEAD+"obj/hole")->move(TO);
    }
    return;
}

void 
init()
{
    ::init();
    add_action("dig", "dig");
    add_action("bury", "bury");
    add_action("bury", "cover");
    add_action("bury", "inter");
    add_action("fill", "fill");
}

int 
dig(string str)
{
    NF("Dig where?\n");
    if(!strlen(str) || !parse_command(str, ({}),
        "'here' / 'ground' / 'down' / 'hole' / 'grave' %s"))
    return 0;

    if(present("hole", TO))
    {
        write("A hole has already been dug here.\n");
        return 1;
    }

    if(!present("shovel", TP))
    {
        write("You would need a shovel to dig in the ground here.\n");
        return 1;
    }

    if(won || TP->test_bit("Avenir", GROUP, BIT) || !present(BONES_ID, TP))
    {
        write("A feeling of peace rests upon this place, you "+
            "cannot disturb it.\n");
        return 1;
    }

    if(naiad)
    {
        if(!present(naiad))
            naiad->move_living("away", TO);

        TP->catch_msg(QCTNAME(naiad)+" stops you.\n");
        say(QCTNAME(naiad)+" stops "+QTNAME(TP)+
            " from digging a hole.\n");
        return 1;
    }

    if(!called)
    {
        write("As you start to dig into the soil, you feel "
            +"the ground begin to shake slightly.\n");
        say("As "+QTNAME(TP)+" starts to dig a hole, you "
            +"start to feel the ground shake slightly.\n");
        called = 1;
        naiad = clone_object(MON+"naiad");
        naiad->move(TO);
        naiad->start_up();
        return 1;
    }

    write("You dig a large hole in the ground.\n");
    say(QCTNAME(TP)+" digs a large hole beneath the oak tree.\n");
    TP->add_fatigue(-50);
    clone_object(OBJ+"hole")->move(TO);
    return 1;
}

void 
reward(object who)
{
    seteuid(getuid(TO));
    if (who->test_bit("Avenir", GROUP, BIT))
    {
        write("You do not feel your actions have had any "
            +"consequences.\n");
        LOG_THIS(TP->query_name()+" buried the bones, but the bit "
            +"had been set.");
        return;
    }

    won = 1;
    called = 0;
    LOG_THIS(TP->query_name()+" completed the quest. "+EXP+" exp.");
    reward_quest("Bury the Shipcaptain", TP, GROUP, BIT, 
               EXP, ALIGNMENT, PRESTIGE);

    set_alarm(2.0, 0.0, sprout);
}

int 
bury(string str)
{
    string  nihil;
    object  ob,
            hole;

    if (!strlen(str))
        return 0;

    NF("You would need to dig a hole to "+QVB+" anything in.\n");
    if(!(hole = present(HOLE_ID)))
        return 0;

    NF(CAP(QVB)+" what?\n");
    if(!parse_command(str, all_inventory(TP) + all_inventory(hole), 
        "[the] / [a] %o %s", ob, nihil) || !ob)
    return 0;

    NF(CAP(QVB)+" "+LANG_THESHORT(ob)+" where?\n");
    if(!parse_command(str, all_inventory(TP) + all_inventory(hole), 
        "[the] / [a] %o 'in' / 'within' / 'with' [the] "+
        "'hole' / 'earth' / 'dirt' / 'grave' / 'ground'", ob) || !ob)
        return 0;

    NF("You cannot "+QVB+" that.\n");
    if(ob->query_prop(OBJ_M_NO_DROP) || !CAN_SEE(TP, ob) || living(ob) ||
        !CAN_SEE_IN_ROOM(TP) || ob->query_no_show() ||
        ob->query_no_show_composite() || (!present(ob, TP) && !present(ob, hole)))
        return 0;

    if(naiad)
    {
        if(!present(naiad))
            naiad->move_living("away", TO);
        TP->catch_msg(QCTNAME(naiad)+" stops you.\n");
        say(QCTNAME(naiad)+" stops "+QTNAME(TP)+" from "+
            "burying something in the hole.\n");
        return 1;
    }

    ob->move(hole, 1);
    TP->catch_msg("You place "+LANG_THESHORT(ob)+" within "
        +"the hole and cover it over with dirt.\n");
    say(QCTNAME(TP)+" places "+LANG_ASHORT(ob)+" within "
        +"the hole and covers it over with dirt.\n");
    if(ob->id(BONES_ID) || present(BONES_ID, hole))
    reward(TP);

    ob->remove_object();
    hole->remove_object();
    return 1;
}

int 
fill(string str)
{
    object   hole;
    string   nihil;

    if(!(hole = present(HOLE_ID)) || !strlen(str))
        return 0;

    if(naiad)
    {
        if(!present(naiad))
        naiad->move_living("away", TO);
        TP->catch_msg(QCTNAME(naiad)+" stops you.\n");
        say(QCTNAME(naiad)+" stops "+QTNAME(TP)+" from "
            +"filling in the hole.\n");
        return 1;
    }

    TP->catch_msg("You fill the hole in with dirt.\n");
    say(QCTNAME(TP)+" fills the hole with dirt.\n");

    if(present(BONES_ID, hole))
        reward(TP);

    hole->remove_object();
    return 1;
}

void 
anyone_here()
{
    if(!sizeof(filter(all_inventory(TO), interactive)))
    {
        called = 0;
        present(HOLE_ID)->remove_object();
        naiad->remove_object();
    }
}

void 
leave_inv(object what, object to)
{
    ::leave_inv(what, to);

    if(interactive(what))
        set_alarm(5.0, 0.0, anyone_here);
}
