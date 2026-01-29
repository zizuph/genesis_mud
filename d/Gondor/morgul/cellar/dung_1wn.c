/*
 * /d/Gondor/morgul/cellar/dung_1nw.c
 * A dungeon on the first floor of dungeons below the Morgul Tower
 *
 * Olorin,  5-nov-1995
 * 
 * Revisions: 8 feb. 2000 Stern: adapted to use Genesis gem system
 */
inherit "/d/Gondor/morgul/cellar/cellar.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/cellar/cellar_defs.h"

#define MIN_AWARE	50
#define GEM_DIR         "/d/Genesis/gems/obj/"
void    reset_room();

int     gem_flag;
object *rats = allocate(2 + random(3)),
        snake;

void
create_morgul_cellar_room()
{
    set_level(1);
    set_room_type("gloomy dungeon");
    set_extra_long("There is only one exit, an archway to the south "
      + "beyond which a dark tunnel is visible. The dungeon is completely "
      + "void of any equipment and your footsteps create an ominous "
      + "echo.");

    add_walls("Set into the west wall are several large iron rings.");
    add_item(({"west wall", "iron rings", "rings", }), BSN(
        "Two pairs of iron rings are set into the wall at an height of "
      + "about 8 feet; two more pairs are about one feet above the "
      + "ground. The rings look perfect to fasten chains to them holding "
      + "a prisoner for interrogation. Actually, one pair of rings does "
      + "still hold an iron chain."));
    add_item(({"chain", "iron chain", "manacles", "manacle", }), "@@exa_chain@@");
    add_floor("Several gullies lead to a drain in the center of "
      + "the dungeon.");
    add_item(({"gully", "gullies", }), BSN(
        "There seems to be little use to have gullies and a drain "
      + "in this dungeon, as it seems unlikely that they are necessary "
      + "to drain the floor from water. But the purpose suddenly becomes "
      + "obvious when closer examination reveals that not water but "
      + "a sticky red liquid was running through those gullies not "
      + "so long ago - blood!"));
    add_item(({"drain", }), "@@exa_drain@@");
    add_archway("south");
    add_ceiling();

    add_exit(CELLAR_DIR + "cellar_1c", "south", 0, 1);

    reset_room();
}

void
clone_rat(int alarm = 1)
{
    int     i,
            s = sizeof(rats);

    for (i = 0; i < s; i++)
    {
        if (!objectp(rats[i]))
        {
            rats[i] = clone_object(NPC_DIR + "rat");
            rats[i]->set_restrain_path(CELLAR_DIR);
            rats[i]->set_random_move(20);
            rats[i]->set_agressive(1);
            rats[i]->move_living("M", TO);
            tell_room(TO, CAP(LANG_ADDART(rats[i]->query_nonmet_name()))
              + " comes running out of the drain in the center of the dungeon.\n");
            if (alarm)
                set_alarm(60.0 + 120.0 * rnd(), 0.0, clone_rat);
            break;
        }
    }
}

void
reset_room()
{
    object  hand;

    gem_flag = 0;
    set_alarm(5.0, 0.0, clone_rat);

    if (!objectp(snake))
    {
        snake = clone_object(NPC_DIR + "snake");
        snake->set_restrain_path(CELLAR_DIR);
        snake->set_random_move(6);
        snake->set_whimpy(70);
        snake->set_base_stat(SS_DEX, 30);
        snake->move_living("down", TO);
    }

    if (!present("hand"))
    {
        hand = clone_object("/std/leftover");
        hand->leftover_init("hand", "human");
        hand->set_no_show_composite(1);
        hand->move(TO);
    }
}

string
exa_drain()
{
    object  gem;
    string  desc =
        "The inside of the drain is clustered with a sticky red "
      + "substance: blood that has not yet completely dried.";

    set_alarm(1.0, 0.0, &clone_rat(0));

    if (!gem_flag &&
        (TP->query_skill(SS_AWARENESS) >= (MIN_AWARE/2 + random(MIN_AWARE))))
    {
        gem_flag = 1;
        gem = clone_object(GEM_DIR + (ONE_OF_LIST(
            ({"jasper", "onyx", "garnet", "jade", "beryl", "opal", }) )));
        desc += " Inside the drain, you find "+gem->short()+"!";
        if (gem->move(TP))
        {
            desc += " As you cannot carry it, you drop it again!";
            if (gem->move(TO))
                gem->move(TO, 1);
        }
    }
    return BSN(desc);
}

string
exa_chain()
{
    object  hand;
    string  desc =
        "The iron chain runs through a pair of iron rings set into the "
      + "wall. At both ends of the chain is a manacle.";

    if (objectp(hand = present("hand")) && hand->query_no_show_composite())
    {
        desc += " One of the manacles still holds the bloody and torn "
          + "hand of the last prisoner to be interrogated here.";
        if (!hand->move(TP))
        {
            desc += " You take the hand to keep it as souvenir of your "
              + "visit to the dungeons of Minas Morgul.";
            say(QCTNAME(TP) + " takes a torn and bloody hand out of "
              + "a manacle hanging from a chain at the wall.\n");
        }
    }

    return BSN(desc);
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob->id("hand") && ob->query_no_show_composite())
        ob->set_no_show_composite(0);
}

