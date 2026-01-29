/*
 * /d/Gondor/ithilien/nforest/mbranch.c
 * Cleaned up and reformatted code
 * Finwe, October 2017
 */

inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include <macros.h>

#define HARD_TO_CLIMB  20  /* how hard is it to climb up the cedar? - x + random(x) */
#define HARD_TO_EVADE  50  /* how hard is it to evade the arrows? - x + random(x) */

string extraline;
int num_arrow;

string describe();
void   reset_room();

void
create_room()
{

    extraline = "Thick branches covered with green needles block the " +
        "view in all directions. You might manage to climb up or down. ";

    set_short("A branch halfway up a giant cedar");
    set_long("@@describe");

    add_item(({"cedar","cedar tree","closer cedar","nearer cedar", 
            "second cedar","next cedar","smaller cedar"}),
        "This is a giant tree with an enourmous trunk. You guess that " +
        "your halfway between the ground and the top of the cedar. \n");
    add_item(({"branch","branches","bough","boughs","needles"}),
        "All the branches of the cedar tree are densely covered with " +
        "thick green needles. The branch you are standing on is somewhere " +
        "about halfway up the cedar. It is thicker than a man's thigh " +
        "and probably could hold several people. The other branches " +
        "are similar. Growing closely together, they block the view in " +
        "all directions, but you might manage to climb further up or " +
        "down.\n");

  set_noshow_obvious(1);

  reset_room();
}

void
reset_room()
{
    num_arrow = 60;
}

string
describe()
{
    object clock;
    string time,long_descf;
    clock = find_object("/d/Gondor/elessar/lib/clock");
    time = clock->query_time_of_day();
    long_descf = "You are standing on a branch of a giant cedar in a " +
        "forest somewhere in northern Ithilien. It looks like you are " +
        "about halfway up on the way to the top of the tree. ";

    if (!clock->query_war())
    {
        switch(time)
        {
            case "night":
                long_descf = long_descf + "Darkness rules the fields of " +
                    "Ithilien now in the nightime. ";
                if (clock->query_moon()==2)
                {
                    long_descf = long_descf + "A full moon gives some light. ";
                }
                else if (clock->query_moon()==1)
                {
                    long_descf = long_descf + "The moon gives a little light. ";
                }
                else
                {
                    long_descf = long_descf + "The sky is covered with dark " +
                        "clouds, and not even the moon shines through. ";
                }
                break;
            case "afternoon":
                long_descf = long_descf + "The light of day shines across " +
                    "Ithilien. It is afternoon. ";
                break;
            case "morning":
                long_descf = long_descf + "The sun is on its way up on " +
                    "the morning sky to the east. ";
                break;
            case "noon":
                long_descf = long_descf + "The sun is almost at its peak " +
                "on its way across the sky. It is the middle of the day in " +
                "Middle-Earth. ";
                break;
            case "evening":
                long_descf = long_descf + "The sun is setting in the west, " +
                    "coloring the sky golden red. ";
                break;
            case "early morning":
                long_descf = long_descf + "The sun is rising in the east, " +
                    "casting long shadows across Ithilien. ";
                break;
        }
    } /* !clock->query_war() */
    else
    {
        switch(time)
        {
            case "evening":
            case "night":
            case "early morning":
                long_descf = long_descf + "Massive dark clouds cover the " +
                    "sky, making it difficult to distinguish night and day. " +
                    "The clouds seem to be coming from the east, where " +
                    "Mordor lies. You suspect it is night now, as it is " +
                    "as dark as it can get. ";
                break;
            case "morning":
                long_descf = long_descf + "A thick cover of clouds prevent " +
                    "the sun from shining on the lands of Ithilien, and " +
                    "it is almost as dark as at night. However you gather " +
                    "that it is probably morning, as it is getting a " +
                    "bit lighter than earlier. ";
                break;
            case "noon":
                long_descf = long_descf + "A dark mass of clouds seems " +
                    "to be rolling in from the east, covering the sky " +
                    "above Ithilien. It is not much lighter now than " +
                    "it usually is at night, but still you suspect it " +
                    "is the middle of the day. ";
                break;
            case "afternoon":
                long_descf = long_descf + "A thick mass of clouds cover " +
                "the sky, making it difficult to see far. You suspect " +
                "that it is afternoon, as it is getting a bit darker " +
                "than earlier. ";
                break;
        }
    }

    if (extraline) 
    {
        long_descf = long_descf + extraline + "\n";
    }
    else 
    {
        long_descf = long_descf + "\n";
    }
  
    return (break_string(long_descf,75));
}

void
fall_up(int hit)
{
    write("You try to climb higher.\n");
    write("Suddenly you slip ...\n");
    tell_room(TO,QCTNAME(TP) + " tries to climb higher into the tree, but " +
        "slips.\n",TP);
    TP->reduce_hit_point(hit);
    write("You lose your last hold on the branch you were trying to climb.\n");
    write("You fall down again, but you manage to stop your fall on " +
        "a branch halfway up the tree.\n");
    tell_room(TO,capitalize(TP->query_pronoun()) + " loses his hold and " +
        "falls down again.\n",TP);
}

void
climb_up()
{
    write("Stepping from branch to branch, you manage to climb higher. \n");
    tell_room(TO,"Stepping from branch to branch, " + QTNAME(TP) + 
        " manages to climb higher.\n",TP);
    TP->move_living("M",ITH_DIR + "nforest/lookout");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing up from below.\n",TP);
}

void
climb_down()
{
    write("You climb down to the lowest branch of the tree.\n");
    tell_room(TO,QCTNAME(TP) + " climbs down from the branch.\n",TP);
    TP->move_living("M",ITH_DIR + "nforest/lbranch");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing down from above.\n",TP);
    return;
}

void
fall_down(int hit)
{
    write("You try to climb down from the branch.\n");
    write("Suddenly you slip ...\n");
    tell_room(TO,QCTNAME(TP) + " tries to climb down from the branch, but " +
        "slips.\n",TP);
    TP->reduce_hit_point(hit);
    write("You fall down from the branch, but manage to stop your fall " +
        "on the lowest branch of the tree.\n");
    tell_room(TO,capitalize(TP->query_pronoun()) + " falls down from " +
        "the branch, but manages to stop" + TP->query_possessive() + 
        " fall on the lowest branch of the tree.\n",TP);
    TP->move_living("M",ITH_DIR + "nforest/lbranch");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives falling down from above.\n",TP);
    return;
}

int
do_climb(string str)
{
    int climb_skill, dex_stat, risk, hurt, cap;

    if(!str)
    {
        write("Climb what? \n");
        return 1;
    }

    climb_skill = TP->query_skill(SS_CLIMB);
    dex_stat = TP->query_stat(SS_DEX);
    risk = HARD_TO_CLIMB + random(HARD_TO_CLIMB);
    cap = climb_skill + dex_stat/2;

    if (str == "cedar" || str == "branch" || str == "bough" || str == "tree")
    {
        write("Climb up or down?\n");
        return 1;
    }

    if (str == "up")
    {
        if(cap > risk) 
        {
            climb_up();
        }
        else
        {
            fall_up(5*(risk-cap));
        }
    }
    else if(str == "down")
    {
        risk = risk + random(HARD_TO_CLIMB);
        if(cap > risk) 
        {
            climb_down();
        }        
        else 
        {
            fall_down(5*(risk-cap));
        }
    }
    else 
    {
        write("Climb what? \n");
    }
    
    return 1;
}

void
arrow_hit(object tp)
{
    int dex_stat, risk, hurt;

    if(!present(tp->query_real_name(),TO)) 
    {
        return;
    }

    if(tp->query_hp() < 50)
    {
        set_alarm(30.0, 0.0, &arrow_hit(tp));
        return;
    }

    if(!present("ranger",find_object(ITH_DIR + "nforest/lookout")))
    {
        set_alarm(30.0, 0.0, &arrow_hit(tp));
        return;
    }

    if(num_arrow == 0) 
    {
        return;
    }

    if(IS_EVIL(tp))
    {
        dex_stat = tp->query_stat(SS_DEX);
        risk = HARD_TO_EVADE + random(HARD_TO_EVADE) + 
            random(HARD_TO_EVADE);
        if(dex_stat > risk)
        {
            write("An arrow narrowly misses you.\n");
            tell_room(TO,"An arrow narrowly misses " + QTNAME(tp) + ".\n",TP);
        }
        else
        {
            write("You are hit by an arrow fired from above.\n");
            tell_room(TO,QCTNAME(tp) + " is hit by an arrow fired from " +
                "above.\n",TP);
            tp->reduce_hit_point(50);
        }
        num_arrow--;
        set_alarm(itof(random(150 - 2*num_arrow)), 0.0, &arrow_hit(tp));
    }
    return;
}

void
drop_item(object ob)
{
    string down_room;

    down_room = ITH_DIR + "nforest/lbranch";

    if (ob && present(ob))
    {
        tell_room(TO, "The " + ob->query_name() + " falls down.\n");
        ob->move(down_room);
        tell_room(down_room, CAP(LANG_ADDART(ob->query_name())) + 
            " falls down from above.\n");
        down_room->drop_item(ob);
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!living(ob))
    {
        set_alarm(1.0, 0.0, &drop_item(ob));
    }
    else if(IS_EVIL(ob))
    {
        set_alarm(itof(random(10)), 0.0, &arrow_hit(TP));
    }
}

void
make_smoke(object fire)
{
    tell_room(TO,"Smoke from " + LANG_ADDART(fire->short()) + " is rising " +
        "from below into the sky.\n");
    return;
}

void
init()
{
    ::init();
    add_action("do_climb","climb");
}
