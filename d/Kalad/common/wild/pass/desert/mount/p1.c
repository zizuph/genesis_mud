#pragma strict_types
#include "/d/Kalad/defs.h"
inherit "/d/Kalad/room_std";

/* by Antharanos */
// Polished by Ibun 2007-05-11

void
create_room()
{
    ::create_room();
    add_prop(ROOM_NO_TIME_DESC,1);
    set_short("On a ledge along the length of a pinnacle of rock");
    set_long("You are currently on a large, relatively flat ledge along "+
      "the length of a great pinnacle of rock. Above and below you lies "+
      "the unnaturally straight surface of the pinnacle, which is at a near "+
      "ninety degree angle to the ground far below. Here, the searing heat "+
      "of the Kaladian sun pummels you with its fiery presence.\n");
    add_item(({"large flat ledge","relatively flat ledge","flat ledge","ledge"}),
      "The ledge is nearly forty feet across at the widest, but is only a "+
      "scant fifteen feet wide.\n");
    add_item(({"great pinnacle of rock","great pinnacle",
        "pinnacle of rock","pinnacle"}),
      "It appears as if you are a third of the way up its soaring height.\n");
    add_item(({"ground"}),
      "It is hundreds of feet below you.\n");
    add_item(({"kaladian sun","sun"}),
      "The blazing white-hot orb scorches you relentlessly from its vantage "+
      "point on high.\n");
    add_item(({"rock"}),
      "It is colored a deep grey and is cracked in places due to the heat "+
      "of the sun.\n");
    add_exit(CPASS(desert/mount/p2),"up","@@genie_block",5);
    add_exit(CPASS(desert/mount/m15),"down","@@check_feather",5);
    set_alarm(1.0, 0.0, &reset_room());
}

void
reset_room()
{
    object dao;

    if (!present("dao", this_object()))
    {
        dao = clone_object(CPASS(npc/genie_earth));
        tell_room(TO, "The earth beneath you suddenly trembles " +
            "spasmodically, then in an eruption of dirt and " +
            "stones, a mighty figure bursts forth from the " +
            "quaking earth.\n");
        dao->move(TO);
    }
}

void
init()
{
    ::init();
    add_action("banished", "banished");
}

int
genie_block()
{
    object *ob;
    int pres,i;
    ob = FILTER_LIVE(all_inventory(this_room()));
    pres = 0;
    for (i = 0; i < sizeof(ob); i++)
    {
        if(ob[i]->query_name() == "Dao")
            pres = 1;
    }

    if(pres == 1)
    {
        write("You begin to climb up further but are " +
            "instantaneously stopped by the guardian " +
            "genie of Earth.\n");
        say(QCTNAME(TP) + " tries to climb up but is " +
            "instantaneously stopped by the guardian " +
            "genie of Earth.\n");
    }
    return pres;
}

int
check_feather()
{
    object *ob;
    int i;

    if(TP->query_skill(SS_CLIMB) > 60)
        return 0;

    ob = deep_inventory(TP);
    for(i = 0; i < sizeof(ob); i++)
        if(ob[i]->id("sacredfeatherofnathla"))
        {
            write("You start to climb but slip and begin " +
                "to fall, however, just as it seems as if " +
                "you are about to plummet to your death, the "+
                "sacred feather of Nathla suddenly glows " +
                "brightly and you land on the ground safely.\n" +
                "The feather then vanishes from your hand.\n");
            say(QCTNAME(TP) + " starts to climb down but " +
                "slips and falls, however, just as it seems " +
                "as if " + TP->query_pronoun() + " is about to " +
                "plummet to " + TP->query_possessive() + " death, " +
                "the feather that is in " + TP->query_possessive() +
                " hand suddenly glows brightly, and " +
                QCTNAME(TP) + " lands safely on the ground.\n");
            ob[i]->remove_object();
            return 0;
        }
    write("You try to climb down but slip and fall!!!\n");
    say(QCTNAME(TP) + " tried to climb down but slips and falls!!!\n");
    set_alarm(2.0,0.0,"fall");
    return 0;
}

int
fall()
{
    TP->catch_msg("You slam into the ground with horrible force!!!\n");
    TP->heal_hp(-500);
    if(TP->query_hp() <= 0)
        TP->do_die(TO);
    return 1;
}


int
banished(string str)
{
    if(!str || str != "intotheelementalplaneofearthforever")
    {
        NF("What are you trying to do?\n");
        return 0;
    }
    write("You are banished!\n");
    TO->command("scream");
    TO->command("shout Nooooooooooooooo!!!");
    say(QCTNAME(TO) + " is banished back to the elemental plane of Earth.\n");
    TO->move_living("into the gateway to the elemental plane of Earth",
        "/d/Kalad/common/wild/pass/desert/mount/banished1");
    return 1;
}

/*
void
enter_inv(object ob, object from)
{

    object dao;

    ::enter_inv(ob, from);

    if (!present("dao", this_object()))
    {
        dao = clone_object(CPASS(npc/genie_earth));
        dao->move(TO);
        tell_room(TO, "The earth beneath you suddenly trembles " +
            "spasmodically, then in an eruption of dirt and " +
            "stones, a mighty figure bursts forth from the " +
            "quaking earth.\n");
    }
}
*/
