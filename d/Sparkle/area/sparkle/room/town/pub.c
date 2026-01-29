#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/pub";

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

#define LIVE_I_SPARKLE_PUB	"_live_i_sparkle_pub"

public int     do_spit(string str);
public string  read_sign();
public void    reset_room();
public void    create_sailors(int n = 3);
public void    clone_sailor(int i, mixed sarr);
public object  check_monster(string who = "bartender");

/* Name,      Pretitle, Title, Nickname, adj1, adj2, Starting loc.  */
mixed   sail_arr = ({
  ({"tatilar",  "",		"the sailor",  "tatty",  "tall","skinny",
    "square", "e n n w", 3}),
  ({"velomyn",  "",		"the sailor",  "furrface",  "black bearded", "",
    "parrot", "w w n n n w", 4}),
  ({"galgaj",   "",		"the bold",    "",  "big","muscular",
    "jetty2", "n w w w", 9}),
  ({"moguin",   "",		"the experienced adventurer",  "mo", "grim","scarred",
    "square", "e n n w", 6}),
  ({"kantram",  "",		"the utter novice",  "",  "fat","hairy",
    "jetty2", "n w w w", 2}),
  ({"gryej",         "",         "the pirate",  "nimblefoot", "one legged","",
    "parrot", "w w n n n w", 5}),
  ({"lumpar",   "",		"of Liwitch",  "beacon",  "tall","sturdy",
    "vill_gate", "e s e e e n n w", 7}),
  ({"gidorin",  "Captain",  "of the Flunder",  "captain",  "red bearded", "",
    "square", "e n n w", 8}),
  ({"stutch",   "",		"Ironfist",  "pigpen",  "sloppy","unshaved",
    "shop", "n e n n w", 6}),
  ({"vondoj",   "",		"the pirate",  "hawkeye",  "one eyed", "",
    "vill_gate", "e s e e e n n w", 7}),
  ({"aarion",   "",		"of Antraal",  "",  "tall","proud",
    "square", "e n n w", 6}),
  ({"fistus",   "",		"the seasoned adventurer",  "Shorty", "short","encumbered",
    "square", "e n n w", 5}),
  ({"carius",   "",		"the merchant",  "carie",  "well dressed", "",
    "parrot", "w w n n n w", 4}),
  ({"monbier",  "Captain",  "of HMS Exelcior",  "captain",  "decorated", "",
    "jetty2", "n w w w", 8}),
  ({"burun",    "",		"the sailor",  "crow",  "old","bearded",
    "jetty2", "n w w w", 5}),
  ({"munt",     "",		"the storyteller",  "humpey",  "old", "hunchbacked",
    "church", "s e e n n w", 3}),
  ({"sillaric", "",		"of Magonien",  "lilly",  "perfumed", "",
    "vill_gate", "e s e e e n n w", 5}),
  ({"dalid",    "",		"the fierce",  "boner",  "short", "weatherbeaten",
    "vill_gate", "e s e e e n n w", 7}),
  ({"schmerk",  "",		"the gourmet chef",  "parsley",  "dirty", "",
    "square", "e n n w", 4}),
  ({"pintim",   "",		"the experienced novice",  "woggy", "nervous", "",
    "jetty2", "n w w w", 2})
});

static object *sailors = ({}),
keeper;
static int     tmp_rang;

public void    set_tmp_rang(int i) { tmp_rang = i; }

public void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    set_short("the local pub");

    set_long(
      "You are in the local pub.\n"+
      "The atmosphere is thick with tobacco smoke and a murmur can be "+
      "heard from the sailors at the bar. An occasional witty joke "+
      "causes them all to laugh and slam their jars on the counter. "+
      "A sign hangs on the wall behind the counter.\n"+
      "");

    add_exit(S_DOMAIN_PIERS_DIR + "sparkle/pelargir", "east", 0);

    add_item("sign", read_sign());
    add_cmd_item("sign", "read", read_sign());

    add_item(({"sailors" }),"The sailors ignore you.\n");
    add_item(({"counter","bar" }),"It is comfortably high enough to rest your "
      + "elbows on while drinking your beer. That is by human standards of course. "
      + "It is made out of good quality oak. At one corner, there is a bell "
      + "standing on the counter."
      + "\n");
    add_item(({"bell", }), "It is a bell. Made from brass. Probably "
      + "made so one can ring it. Perhaps you should try to do so?\n");
    add_cmd_item("bell", "ring", "@@ring_bell@@");

    reset_room();

    add_drink( ({"water", }), ({"glass", "water", }), 0, 200, 0, 10,
      "glass of water", "glasses of water",
      "A glass of water to quench your thirst.\n");
    add_drink( ({"beer", }), ({"glass", "beer", }), 0, 200, 4, 12,
      "glass of beer", "glasses of beer",
      "A glass of beer. Cheers!\n");
    add_drink( ({"wine", }), ({"glass", "wine", }), 0, 200, 16, 36,
      "glass of wine", "glasses of wine",
      "A glass of white wine. Not exactly a chablis but probably "
      + "a decent vin de pays, judging from the bouquet!\n");
    add_drink( ({"special brew", "special", "brew" }),
      ({"brew", "special", }), ({ "special" }),
      200, 24, 72, "special brew", "special brews",
      "This is a special brew of the pub in Sparkle. It smells a "
      + "little toxic, and you might need a good stomach not to feel "
      + "a little sick after drinking this.\n");
    add_drink( ({"rum", "captain's rum", }),
      ({"rum", }), ({"captain's", }),
      100, 36, 144, "Captain's rum", "Captain's rums",
      "No captain drinking this rum would be able to remain standing "
      + "on his feet on dry land, and not on the planks of a ship, "
      + "either. Drink at your own risk!\n");
    add_drink( ({"firebreather", "fire", }),
      ({"firebreather", "fire", "breather", "rotgut", }), 0,
      100,  50, 288, "firebreather", "firebreathers",
      "It is called firebreather, and if you drink it, this rotgut "
      + "will either kill you by scorching your throat or by cauterizing "
      + "your intestines. Bottoms up!\n");
}

public void
reset_room()
{
    create_sailors(3);

    if (!objectp(keeper))
    {
        setuid (); seteuid (getuid ());
        keeper = clone_object(S_LOCAL_NPC_DIR + "bartender");
        keeper->arm_me();
    }
}

public string
ring_bell()
{
    write("You ring the bell.\n");
    say(QCTNAME(TP) + " rings the bell.\n");

    if (!objectp(keeper))
        return "";

    if (!present(keeper) && !tmp_rang)
    {
        set_alarm(5.0, 0.0, &keeper->move_living("east", TO));
        tmp_rang = 1;
        set_alarm(10.0, 0.0, &set_tmp_rang(0));
    }
    else if (present(keeper))
    {
        keeper->command("glare "+TP->query_real_name());
        keeper->command("say What's the matter? I'm here, aren't I?");
        keeper->command("snarl "+TP->query_real_name());
        keeper->command("say So whaddaya want?");
    }
    return "";
}

public string
read_sign()
{
    return "The sign reads:\n" +
    "\n"+
    "          +----------------------------------------+\n"+
    "          |                                        |\n"+
    "          |   Beer                1 silver coin    |\n"+
    "          |   Wine                3 silver coins   |\n"+
    "          |   Our Special Brew    6 silver coins   |\n"+
    "          |   Captains' Rum       1 gold coin      |\n"+
    "          |   Firebreather        2 gold coins     |\n"+
    "          |                                        |\n"+
    //      "          |   Coffee or Tea        5               |\n"+
    "          |   Water              10 copper coins   |\n"+
    "          |                                        |\n"+
    "          |   PLEASE DON'T SPIT ON THE FLOOR       |\n"+
    "          |                                        |\n"+
    "          +----------------------------------------+\n"+
    "\n";

}

public void
init()
{
    add_action(do_spit, "spit");

    ::init();

    init_pub();
}

public void
create_sailors(int n = 3)
{
    int    *gang = ({}),
    chosen,
    i;
    object  ob;

    // Get n random sailors from the list above.
    while (sizeof(sailors) < n)
        sailors += ({ 0 });

    for (i = 0; i < n; i++)
    {
        if (objectp(sailors[i]))
            break;
        chosen = random(sizeof(sail_arr));
        if (member_array(chosen, gang) < 0)
        {
            gang += ({ chosen });
            set_alarm(1.0 + itof(i) * 5.0, 0.0, &clone_sailor(i, sail_arr[chosen]));
        }
        else
            i--;
    }
}

public void
clone_sailor(int i, mixed sarr)
{
    if (objectp(sailors[i]))
        return;

    setuid (); seteuid (getuid ());

    sailors[i] = clone_object(S_LOCAL_NPC_DIR + "sailor");

    sailors[i]->set_name(sarr[0]);
    if (strlen(sarr[1]))
    {
        sailors[i]->set_name(sarr[1]+" "+ CAP(sarr[0]));
        sailors[i]->add_name(sarr[0]);
    }

    sailors[i]->set_title(sarr[2]);

    if (strlen(sarr[3]))
        sailors[i]->set_nickname(sarr[3]);

    sailors[i]->add_name("sailor");

    sailors[i]->set_adj(sarr[4]);
    if (strlen(sarr[5]))
        sailors[i]->add_adj(sarr[5]);

    sailors[i]->set_path(sarr[7]);

    sailors[i]->set_con(sarr[8]);

    sailors[i]->move_living("down", S_LOCAL_ROOM_DIR + sarr[6]);

    sailors[i]->arm_me();
    sailors[i]->start_walking();
    return;
}

public object
check_monster(string who = "bartender")
{
    object  ob;
    if (objectp(ob = present(who)))
        return ob;

    NFN("The "+who+" is not here right now.");
    return 0;
}

private void
throw_out(object tp, int repeat = 0)
{
    if (!present("bartender") || !present(tp))
        return;

    keeper->command("kick "+tp->query_real_name());

    if (!repeat)
    {
        keeper->command("shout Hey, don't spit on the floor!");
        keeper->command("emote points at the sign.");
        keeper->command("shout Get out of here, you swine!");
    }
    else
    {
        keeper->command("shout I don't want to see you in my pub!");
    }

    tp->catch_msg(QCTNAME(keeper) + " throws you out of the pub.\n");
    tell_room(TO, QCTNAME(keeper) + " throws " + QTNAME(tp)
      + " out of the pub.\n", ({ tp, keeper }) );
    tp->move_living("east", S_DOMAIN_PIERS_DIR + "sparkle/pelargir");
    tell_room(ENV(tp), QTNAME(tp) + " is thrown out of the pub and "
      + "lands with a crash in front of you.\n", tp);
    tp->add_prop(LIVE_I_SPARKLE_PUB, 1);
}

public int
do_spit(string str)
{
    if (!objectp(present("bartender")))
        return 0;

    if (!strlen(str) || (str == "on floor" || str == "on the floor"))
    {
        write("You spit on the floor ... how disgusting!\n");
        say(QCTNAME(TP) + " spits on the floor ... how disgusting!\n");
        set_alarm(2.0, 0.0, &throw_out(TP));
        return 1;
    }
    return 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !living(ob))
        return;

    if (ob->query_prop(LIVE_I_SPARKLE_PUB))
        set_alarm(2.0, 0.0, &throw_out(ob, 1));
}

public int
order(string str)
{
    if (!objectp(check_monster()))
        return 0;
    return ::order(str);
}

