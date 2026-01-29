inherit "/d/Gondor/ithilien/sforest/on_tree.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define HARD_TO_CLIMB  20  /* how hard is it to climb up the oak? - x + random(x) */

string on_road();

static int     alert_alarm;

object  haradrim1,
        haradrim2;

void
create_on_tree()
{
    set_short("a branch close to the top of a giant oak");
    set_description("You are standing on a branch of a giant oak "
      + "in a forest somewhere in southern Ithilien.");
    set_extraline("You are close to the top of the tree. Someone has "
      + "cut away several branches and twigs so that you have a "
      + "terrific view from here. You might manage to climb down the "
      + "tree.");

    add_item(({"view", }), BSN(
        "To the north, you can look over a wide forest covering "
      + "gentle slopes and vales that extend to the Anduin in the "
      + "west. The foothills of the Ephel Duath are rising to the "
      + "east, the dark shadow of the mountains themselves receding "
      + "eastward in a long curve. Where the forest meets the "
      + "foothills, a road can be seen, running from the north to the "
      + "south in a straight line. From here, every movement on that "
      + "road can be observed."));
    add_item(({"river","anduin"}), BSN(
        "Far away to the west, you can see a shimmering blue band. "
      + "This is the mighty river Anduin, running from the Falls of "
      + "Rauros south towards Osgiliath and finally to its mouth at "
      + "the sea. You estimate that it is about twenty leagues from "
      + "here to its eastern bank."));
    add_item(({"oak","oak tree","tree"}), BSN(
        "This is a giant tree with an enourmous trunk. You are close "
      + "to the top, perhaps thirty or forty yards above the ground."));
    add_item(({"mountains","mountain-range","mountain","ephel duath"}),
        BSN("The mountains named Ephel Duath appear to be dark grey "
      + "from here. You judge the mountains to be between 5000 to 7000 "
      + "feet tall, and you guess they are several miles away now."));
    add_item("road", on_road);
    add_item(({"branch","branches","bough","boughs"}), BSN(
        "All the branches of the oak tree are densely covered with "
      + "thick green leaves. The branch you are standing on is close "
      + "to the top of the oak. It is thicker than a man's thigh and "
      + "probably could hold several people."));
    add_item(({"forest","thickets","bushes"}), BSN(
        "As far as you can see the gentle slopes of Southern Ithilien "
      + "are covered by a forest made up of small clusters of trees "
      + "and wide glades of bushes and thorns in between."));

    set_down_room(ITH_DIR + "sforest/mbranch");
}

void
reset_room()
{
    if (!objectp(haradrim1))
    {
        haradrim1 = clone_object(ITH_DIR + "npc/haradrim1");
        haradrim1->arm_me();
        haradrim1->move_living("down", TO);
    }

    if (!objectp(haradrim2))
    {
        haradrim2 = clone_object(ITH_DIR + "npc/haradrim2");
        haradrim2->arm_me();
        haradrim2->move_living("down", TO);
        if (objectp(haradrim1))
            haradrim1->team_join(haradrim2);
    }
}

void
climb_down()
{
    if (TP->query_prop("_arrested") &&
        objectp(haradrim1) && present(haradrim1)) 
    {
        if (!haradrim1->stop_fleeing(TP))
        {
            write(QCTNAME(haradrim1) + " tries to stop you, but you "
              + "manage to climb down.\n");
            tell_room(TO, QCTNAME(haradrim1) + " tries to stop "
              + QTNAME(TP)+", but "+TP->query_pronoun()+" manages to "
              + "climb down.\n", TP);
            fall_down(HARD_TO_CLIMB + 2*random(HARD_TO_CLIMB) - TP->query_stat(SS_DEX)/3);
        }
    }
    else if (TP->query_prop("_arrested") &&
        objectp(haradrim2) && present(haradrim2)) 
    {
        haradrim2->command("kill " + TP->query_real_name());
        fall_down(HARD_TO_CLIMB + 2*random(HARD_TO_CLIMB) - TP->query_stat(SS_DEX)/3);
    }
    else if(objectp(TP->query_attack()))
        fall_down(HARD_TO_CLIMB + 2*random(HARD_TO_CLIMB) - TP->query_stat(SS_DEX)/3);
    else
    {
        write("You climb down.\n");
        tell_room(TO,QCTNAME(TP) + " climbs down.\n",TP);
        TP->move_living("M", down_room);
        tell_room(ENV(TP),QCTNAME(TP) + " arrives climbing down from above.\n",TP);
    }
}

string
on_road()
{
    int     i,
            size,
            flag = 0;
    object  road,
           *lnames = ({ });
    string  desc = 
        "The long straight road runs south through Southern Ithilien "
      + "towards the land of Harad, while in the other direction it "
      + "goes to the crossroads where it meets the road from Osgiliath "
      + "to Minas Morgul. From there, it then continues north towards "
      + "the Morannon, the Black Gate of Mordor. The road and everyone "
      + "travelling on it is visible for many miles.";

    FIX_EUID

    (ITH_DIR + "road/sr2")->teledingska();
    road = find_object(ITH_DIR + "road/sr2");
    lnames = FILTER_LIVE(all_inventory(road));
    if (sizeof(lnames))
    {
        desc += " Far north, just south of the Morgulduin, you can see "
             +  COMPOSITE_LIVE(lnames) + " on the road.";
        flag = 1;
    }

    (ITH_DIR + "road/sr3")->teledingska();
    road = find_object(ITH_DIR + "road/sr3");
    lnames = FILTER_LIVE(all_inventory(road));
    if (sizeof(lnames))
    {
        desc += " East of the small rising on which the oak grows, you can see "
             +  COMPOSITE_LIVE(lnames) + " on the road.";
        flag = 1;
    }

    (ITH_DIR + "road/sr4")->teledingska();
    road = find_object(ITH_DIR + "road/sr4");
    lnames = FILTER_LIVE(all_inventory(road));
    if (sizeof(lnames))
    {
        desc += " Far south, you can see "+COMPOSITE_LIVE(lnames)+" on the road.";
        flag = 1;
    }

    if (!flag)
        desc += " There is nobody on the road.";

    return BSN(desc);
}

void
alert_msg(object ob)
{
    alert_alarm = 0;
    haradrim2->command("say Look out!");
    if (!IS_EVIL(ob))
        haradrim2->command("say There are enemies on the road!");
    else
        haradrim2->command("say There is something on the road.");
}

void
enter_road(object ob, object from)
{
    if (!objectp(haradrim2) || !present(haradrim2))
        return;
    if (!alert_alarm || !sizeof(get_alarm(alert_alarm)))
        alert_alarm = set_alarm(2.0, 0.0, &alert_msg(ob));
}

void
make_smoke(object fire)
{
    ::make_smoke(fire);
    if (!objectp(haradrim1) || !present(haradrim1))
        return;
    haradrim1->fire_alarm();
    return;
}

/*
 * Function:    query_range_targets
 *
 * Description: Returns information about adjacent rooms
 *              that you can reach with missile weapons
 *              from this room.
 *
 * Arguments:   (object) The person that wishes to fire
 *              into an adjacent room.
 *
 * Returns:     An array with the following content. If
 *              there is more then one room accessible
 *              from this room, each room pads their
 *              values to the array.
 *
 * ({ path to remote room, 
 *    matching pattern with parse_command syntax, 
 *    description of remote room,
 *    description of this room as seen from remote room 
 *  })
 *
 * Note that upon making it possible to shoot across
 * rooms, you better make your npc:s able to respond
 * to it so they won't be sitting ducks.
 *
 */

mixed 
query_range_targets(object archer)
{
   seteuid(getuid(this_object()));
   (ITH_DIR + "road/sr2")->load_me();
   return ({    (ITH_DIR + "road/sr2"),
                "[at] [on] [the] 'road'",
		"on the road",
		"from a giant oak"
		    });
}
