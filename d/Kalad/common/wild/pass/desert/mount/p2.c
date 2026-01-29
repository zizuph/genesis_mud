#pragma strict_types
#include "/d/Kalad/defs.h"
inherit "/d/Kalad/room_std";

object ob1;
int genie_appear();

/* by Antharanos */
// Polished by Ibun 2007-05-11

void
create_room()
{
    ::create_room();
    add_prop(ROOM_NO_TIME_DESC,1);
    set_short("On a large, curving ledge on a pinnacle of rock");
    set_long("You are at another ledge on the great pinnacle of rock. " +
       "This flat area seems to curve around the nearly vertical length of " +
       "the pinnacle, but only halfway around it. Ever present in the sky " +
       "above is the Kaladian sun, its heat relentlessly sapping the "+
       "strength from you.\n");
    add_item(({"large ledge","curving ledge","ledge","flat area","area"}),
       "A flat space along the length of the great pinnacle. It is nearly " +
       "fifty feet across as the widest point and twenty feet wide as its " +
       "narrowest.\n");
    add_item(({"great pinnacle of rock","great pinnacle",
        "pinnacle of rock","pinnacle"}), "It appears as if you are " +
        "nearly two thirds of the way up its length.\n");
    add_item(({"sky"}), "It is clear and blue, with not a single " +
        "trace of clouds.\n");
    add_item(({"kaladian sun","sun"}), "A fiery white orb that hangs " +
        "in the sky like a waiting vulture.\n");
    add_item("rock", "It is dark grey in color, similar to " +
        "the ones that compose the rest of this mountain range.\n");
    add_item(({"mountain range","range"}), "A fairly large range " +
        "of mountains that curves in a crescent towards the south.\n");
    add_exit(CPASS(desert/mount/p3),"up","@@genie_block",5);
    add_exit(CPASS(desert/mount/p1),"down","@@check_urn",5);
    reset_room();
}

void
reset_room()
{
    if (!present("efreeti", this_object()))
    {
        set_alarm(2.5, 0.0, "genie_appear");
        set_alarm(1.0,0.0,"msg1");
        set_alarm(2.0,0.0,"msg2");
    }
}

int
genie_block()
{
    object *ob;
    int pres, i;
    ob = FILTER_LIVE(all_inventory(this_room()));
    pres = 0;

    for (i = 0; i < sizeof(ob); i++)
    {
        if(ob[i]->query_name() == "Efreeti")
        {
            write("You begin to climb up further but find that the way is " +
                "blocked by the guardian genie of Fire.\n");
            say(QCTNAME(TP) + " begins to climb up further but finds that " +
                "the way is blocked by the guardian genie of Fire.\n");
            pres++;
        }
}
    return pres;
}

int
msg1()
{
    tell_room(TO,"Without warning, a huge crack appears in the ground "+
        "and fire and brimstone lashes out, as if the fires of hell had just "+
        "reached the world of light.\n");
    return 1;
}

int
msg2()
{
    tell_room(TO,"A figure then steps forth from the unnatural rent in "+
        "the ground and with but a single wave of his hand, closes " +
        "the fissure.\n");
    return 1;
}

void
genie_appear()
{
    object efreeti;

    efreeti = clone_object(CPASS(npc/genie_fire));
    efreeti->move(TO);
}

int
check_urn()
{
    object *ob;
    int i;
    ob = deep_inventory(TP);
    for(i = 0; i < sizeof(ob); i++)
        if(ob[i]->id("urn of rata"))
        {
            write("As you descend down the pinnacle of rock, the urn " +
                "suddenly slips from your grasp and is lost to you.\n");
            say("As " + QTNAME(TP) + " descends down the pinnacle of rock, " +
                "the urn suddenly slips from " + TP->query_possessive() +
               " grasp and is lost.\n");
            ob[i]->remove_object();
            return 0;
        }
    write("You descend down the pinnacle of rock.\n");
    say(QCTNAME(TP) + " descends down the pinnacle of rock.\n");
    return 0;
}
void
init()
{
   ::init();
   AA(banished,banished);
}
int
banished(string str)
{
   if(!str || str != "intotheelementalplaneoffireforever")
      {
      NF("What are you trying to do?\n");
      return 0;
   }
   write("You are banished!\n");
   TP->command("scream");
   TP->command("shout Nooooooooooooooo!!!");
   say(QCTNAME(TP) + " is banished back to the elemental plane of Fire.\n");
   TP->move_living("into the gateway to the elemental plane of Fire",
       "/d/Kalad/common/wild/pass/desert/mount/banished2");
   return 1;
}

/*
void
enter_inv(object ob, object from)
{

    object efreeti;

    ::enter_inv(ob, from);

    if (!present("efreeti", this_object()))
    {
        set_alarm(2.5,0.0,"genie_appear");
        tell_room(TO,"The ground before you suddenly begins to shake and "+
            "thrash about in tortuous movements.\n");
        set_alarm(1.0,0.0,"msg1");
        set_alarm(2.0,0.0,"msg2");

    }
}
*/
