/* Vingaard Keep coded by Percy. */
/* Changes by Grace, 04/06/94  */
/* 'Initiating into Orders' by Aridor, 10/94 */

#include "../knight/guild.h"
#include <ss_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#define PLAYER_O_FOR_ROSE     "_player_o_for_rose"
#define PLAYER_O_FOR_SWORD    "_player_o_for_sword"
#define PLAYER_O_FOR_CROWN    "_player_o_for_crown"
#define SKILLOB               "/lib/skill_raise"

inherit IN_BASE;

object knighter, horn, guard, guard2;

int up_stairs();
int check_knight();
string balcony_desc();
int check_align();

void
reset_vin_room()
{
    if (horn)
    return;
    horn = clone_object(VOBJ + "bell");
    horn->move(TO);
    if (!guard)
    (guard = clone_object(VNPC + "gunthar_guard"))->move(TO);
    if (!guard2)
    (guard2 = clone_object(VNPC +"gunthar_guard"))->move(TO);
}

void
create_vin_room()
{
    set_short("Great Hall");
    set_long("You are standing in the Great Hall of Vingaard Keep. " +
      "This is the meeting room of the Knights of Solamnia and their " +
      "allies. In the middle of the room is rectangular wooden " +
      "table, surrounded by many chairs. The northwest corner of " +
      "the room opens upwards, through a hole in the ceiling, " +
      "where a rope dangles. A stairway leads upwards in a " +
      "spiral fashion to the east. An office is north, while the " +
      "main entrance to the guild is south. Near the entranceway " +
      "to the office are posted a sign and a scroll. Two small "+
      "staircases lead northwest and northeast from here, curving "+
      "back inwards as they ascend towards a balcony that overlooks "+
      "the great hall. @@balcony_desc@@\n");

    add_prop(ROOM_I_LIGHT, 3);
    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep " +
      "prevent teleportation in this area... or is it something else?\n");
    AI(({"walls","wall"}),"The walls are made of stone.\n");
    AI("floor","The floor is well tread on. It is made of stone.\n");
    AI("stone","The stone is typical of Vingaard Keep, granite from " +
      "the Vingaard Mountains.\n");
    AI("rope","The rope is made of hemp, and is obviously attached " +
      "to something farther up.\n");
    AI("hole","The hole in the ceiling is where the rope dangles from. " +
      "Looking up, you think you can see a large bell.\n");
    AI(({"bell","large bell"}),"It is too far away to be certain if " +
      "it is indeed a bell.\n");
    AI(({"stairway","spiral stairway"}),"It is carved out of stone, " +
      "and spirals upwards onto the second floor of the Solamnian " +
      "guild hall.\n");
    AI(({"entrance","main entrance"}),"It is just south of here.\n");
    AI("office","It lies to the north.\n");
    AI("sign","The sign has green writing on a light blue background.\n");
    AI("scroll", "This parchment is now yellowed paper.\n");
    AI(({"table","wooden table","rectangular table",
    "rectangular wooden table"}),"This is a massive wooden table, "+
      "with over one hundred chairs surrounding it.\n");
    AI("chairs","The chairs are made of the same wood as the table.\n");
    AI("wood","It is sturdy, stalwart, and heavy oak.\n");
    AI("chair", "No chair is different than any other.\n");
    AI("ceiling", "It is a perhaps six meters high, and supported by " +
      "massive crossbeams.\n");
    AI(({"crossbeams","massive crossbeams"}),"They are made of a " +
      "dark wood.\n");
    AI("dark wood","It is most likely aged elm.\n");

    add_exit(VROOM + "gunth_room", "north", check_align);
    add_exit(VROOM+"joinroom", "south", 0);
    add_exit(VROOM + "startroom", "up", check_knight);
    add_exit(VROOM + "greathall_balcony", "northeast", "@@up_stairs");
    add_exit(VROOM + "greathall_balcony", "northwest", "@@up_stairs");
    seteuid(getuid(TO));
    reset_room();
}

int
check_knight()
{
    if (MEMBER(TP))
    return 0;

   if(TP->query_wiz_level())
      return 0;
    write("As you try to trudge up the stairs, you discover a strong " +
      "feeling of confusion within yourself. Bedazzled, you find " +
      "you have to return to the Great Hall to restore your senses.\n");
    return 1;
}

int up_stairs()
{
    if (TP->query_race_name() == "draconian")
    return 0;

    if ((guard && !CAN_SEE(guard, TP)) || (guard2 && !CAN_SEE(guard2, TP)))
    return 0;

    if ((guard && E(guard) == TO) || (guard2 && E(guard2) == TO))
    {
/*
    if (TP->query_alignment() < 0)
    {
        write("The knight guard blocks your way as you attempt to go up the "+
          "stairway towards the balcony.\n");
        say("The knight guard blocks "+QTNAME(TP)+" as "+PRONOUN(TP)+
          "attempts to go up the stairway towards the balcony.\n");
        return 1;
    }
*/
    write("The knight guard nods slightly at you as you climb the stairway "+
      "towards the balcony above.\n");
    say("The knight guard nods slightly at "+QTNAME(TP)+" as "+PRONOUN(TP)+
      " climbs the stairway towards the balcony above.\n");
    return 0;
    }
    return 0;
}

int
check_align()
{
    if (TP->query_race_name() == "draconian")
    return 0;

    if ((guard && !CAN_SEE(guard, TP)) || (guard2 && !CAN_SEE(guard2, TP)))
    return 0;
    if ((guard && E(guard) == TO) || (guard2 && E(guard2) == TO))
    {
    if (TP->query_alignment() < 0)
    {
        write("The knight guard blocks your way as you attempt to enter the "+
          "office to your north and says: Perhaps when you prove yourself to be "+
          "trustworthy you may pass, but not until then.\n");
        say("The knight guard blocks "+QTNAME(TP)+" as "+PRONOUN(TP)+" attempts "+
          "to enter the office to the north and says: Perhaps when you prove "+
          "yourself to be trustworthy you may pass, but not until then.\n");
        return 1;
    }
    write("The knight guard nods slightly at you as you pass.\n");
    say("The knight guard nods slightly at "+QTNAME(TP)+" as "+PRONOUN(TP)+
      " passes.\n");
    return 0;
    }
    return 0;
}


string
balcony_desc()
{
    object *inv, *live;
    int i;

    (VROOM + "greathall_balcony")->load_me();
    inv = all_inventory(find_object(VROOM + "greathall_balcony"));

    if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    if (sizeof(live) > 0)
        return ("You see " + COMPOSITE_LIVE(live) + " standing on the balcony "+
          "above. ");
    }
    return ("The balcony appears to be empty. ");
}

void
init()
{
    ::init();
    ADA("sit");
    ADA("read");
    ADA("choose");
    ADA("initiate");
    ADD("leave", "leave!");
}


/* Gives info on what commands are available here */
int
read(string str)
{
    NF("Read what?\n");
    if ((str == "sign") || (str == "the sign"))
    {
    write("This is the guildhall of the Solamnian Knights.\n"
      + " Here you can do the following things:\n\n"
      + "initiate <who> - The conclave member (of that order) or grandmaster gives\n"
      + "                 permission to someone to join a new order. This is \n"
      + "                 followed by the choose command of <who>.\n"
      + "choose <order> - Lets you choose the next order to join if you are a\n"
      + "                 squire or knight. You must have the prestige and stats\n"
      + "                 to join the order. <order> can be either crown, sword\n"
      + "                 or rose.\n"
      + "leave! <order> - Lets you leave the knight order you are in at the\n"
      + "                 moment. Of course you must be in one to leave it!\n"
      + "                 Leaving an order will return you to the next lowest\n"
      + "                 order and you will lose all prestige you had gained!\n"
      + "                 It will be as if you had just joined that order.\n"
      + "                 <order> can be sword or rose order.\n"
      + "break! <name> -  This command enables a knight to break sponsorship with\n"
      + "                 an inactive or unacceptable squire. For further\n"
      + "                 information, type 'help guild break!'\n");
    return 1;
    }
    if (str == "scroll")
    {
    write("This scroll is written and signed by Lord Gunthar. It reads: \n\n");
    write(BS("Alas you who read this stand in a land threatened by a most"
        + " terrible evil. It has been brought to my attention that once again"
        + " our ancient enemy Takhisis the dragon queen has found yet another way"
        + " to enter our world. Already she mobilizes her evil dragonarmy against"
        + " us. I fear we can not hold out for much longer......"
        + "  Our only hope lies in the retrieval of certain items of great power"
        + " that have been lost to us for many centuries. Only with these items will"
        + " the power of good stand any hope of defeating her. I have sent out scouts"
        + " and spies to search for these items but few return and those that"
        + " do tell of the horrors that Takhisis commands. And so this is a request"
        + " for help, If you think you can help us defeat her please come and see"
        + " me.", 70));
    write("\nSigned :- Lord Gunthar Uth Wistan.\n");
    return 1;
    }

    return 0;
}


/* Allows a player to leave a knight order */
int
leave(string str)
{
    string squire, knight;
    int lvl;
    object ob;
    NF("Leave which order?\n");
    if (str == "sword order" || str == "rose order")
    {

    lvl = TP->query_knight_level();
    if ((str == "sword order" && lvl != 4) ||
      (str == "rose order" && lvl != 5))
    {
        write("You are not a member of that order!\n");
        return 1;
    }
    if (TP->query_knight_sublevel() == 11)
        TP->clear_high(lvl);
    TP->set_knight_level(lvl - 1);
    TP->set_skill(SS_PRESTIGE_ST, 26);
    TP->set_skill(SS_PRESTIGE_ACC, 18100);
    if (ob = present("pal_med", TP))
        ob->set_knight_sublevel(1);
    TP->change_prestige(1, 0);
    write("You leave the " + C(str) + " and you are now a " +
      KNIGHT_TITLES[lvl - 1] + ".\n");
    say(QCTNAME(TP) + " has left the " + C(str) + ". \n");
    if (lvl < 4)
    {
        knight = TP->query_name();
        (ADMIN)->remove_knight_sponsorlist(knight);
    }
    if (lvl == 4)
        TP->remove_guild_lay();
    return 1;
    }
    return 0;
}

/* the initiate and new choose command together will accept a knight into
* a new order. To enter crown, sword and rose require the initiation of an
* eligible knight (conclave of that order, or someone appointed for this
    * job by the conclave)
*/
int
initiate(string str)
{
    object pro;
    string who, what;
    int lev, subl;
    NF("What?\n");
    if (!MEMBER(TP))
      return 0;

    who = TP->query_real_name();
    NF("What?\n");
    if (!(ADMIN)->is_conclave(who) && !(ADMIN)->is_grandmaster(who) &&
      member_array(C(who), GUILDMASTERS) < 0)
    return 0;
    NF("Initiate who?\n");
    if (!str)
    return 0;
    pro = find_player(str);
    if (!pro || E(pro) != TO)
    {
    write("The Initiate must be present in this room.\n");
    return 1;
    }



    if (pro->query_real_name() == TP->query_real_name())
    {
        if (C(TP->query_real_name()) == C("earth"))
           write("Someone whispers to you: Becarefull... I am watching you!\n");
        write("You can not initiate yourself!\n");
        return 1;
    }

    if (pro->query_knight_level() == 5)
    {
       write(pro->query_name()+" is already a Knight of the Rose, "+
           PRONOUN(pro)+" cannot advance any higher!\n");
        return 1;
    }

    lev = pro->query_knight_level() + 1;
    if (lev == 3)
    what = "Crown";
    else if (lev == 4)
    what = "Sword";
    else
    what = "Rose";
    if (lev == 3)
    pro->add_prop(PLAYER_O_FOR_CROWN, TP);
    else if (lev == 4)
    pro->add_prop(PLAYER_O_FOR_SWORD, TP);
    else
    pro->add_prop(PLAYER_O_FOR_ROSE, TP);
    write("You motion for " + pro->query_name() + " to kneel, so that "+
      PRONOUN(pro)+" may be initiated into the Order of the "+
      what + ".\n");
    pro->catch_msg(TP->query_name()+" motions for you to kneel, so that "+
      PRONOUN(TP)+" may initiate you into the Order of the "+what+".\n"+
      "To do this you must: 'choose <order>'.\n");
    say(QCTNAME(TP)+" motions for "+QTNAME(pro)+" to kneel, so that "+
      PRONOUN(pro)+" may be initiated into the Order of the "+what+".\n", ({TP, pro}));
    knighter = TP;
    return 1;
}

int
choose(string str)
{
    object ob, sh;
    int i;
    mixed tmp;
    string sir_lady;

    NF("Use Choose <new order>.\n");
    if (!str)
    return 0;
    if (!(MEMBER(TP)))
    {
    write("Only solamnian knight members may use this command.\n");
    return 1;
    }

    if (TP->query_knight_level() == 1)
    {
    write("There are no knight orders that want a Black Knight like " +
      "you!\n");
    return 1;
    }

    if (str == "crown")
    {
    if (TP->query_knight_level() == 3)
    {
        write("You are already a Knight of the Crown!\n");
        return 1;
    }
    if (TP->query_knight_level() != 2)
    {
        write("You cannot do that.\n");
        return 1;
    }
    if (TP->query_knight_sublevel() <= 4)
    {
        write("Your prestige isn't high enough to join the Crown " +
          "Order.\n");
        return 1;
    }
    if (TP->query_stat(SS_STR) <= 10 || TP->query_stat(SS_DEX) <= 8 ||
      TP->query_stat(SS_CON) <= 10 || TP->query_stat(SS_INT) <= 7 ||
      TP->query_stat(SS_WIS) <= 10)
    {
        write("You need higher stats than this before the " +
          "Crown Order will accept you.\n");
        return 1;
    }
    tmp = TP->query_prop(PLAYER_O_FOR_CROWN);
    if (!tmp || !P(tmp,TO))
    {
        write("You can only join the crown order if you have " +
          "been initiated and that knight is present here.\n");
        return 1;
    }
    write("You kneel before "+knighter->query_name()+", who performs the "+
      "ceremonial Knighting, touching each of your shoulders with "+
      POSSESSIVE(knighter)+" sword.\n");
    knighter->catch_msg(QCTNAME(TP)+" kneels before you, and you perform "+
      "the ceremonial Knighting, touching each of "+POSSESSIVE(TP)+
      " shoulders with your sword.\n");
    say(QCTNAME(TP)+" kneels before "+QTNAME(knighter)+", who performs "+
      "the ceremonial Knighting, touching each of "+QTNAME(TP)+"'s "+
      "shoulders with "+POSSESSIVE(knighter)+" sword.\n", ({ TP, knighter }));
    if (TP->query_gender() == 1)
        sir_lady = "Lady";
    else
        sir_lady = "Sir";
    knighter->command("$say Arise, "+sir_lady+" "+TP->query_name()+
      ", Knight of the Crown!");
    write("You are now a Knight of the Crown!\n");
    say(QCTNAME(TP) + " is now a Knight of the Crown!\n");
    (ADMIN)->remove_squire_sponsorlist(TP->query_name());
    (ADMIN)->log_action("order", knighter->query_name()+" initiated "+
	TP->query_name()+" into the Crown Order");
    TP->set_knight_level(3);
    if (ob = present("pal_med", TP))
        ob->set_knight_sublevel(1);
    TP->set_bit(1, 5);
    TP->clear_bit(1, 4);
    TP->set_skill(SS_PRESTIGE_ST, 26);
    TP->set_skill(SS_PRESTIGE_ACC, 18100);
    TP->change_prestige(1, 0);
    TP->remove_prop(PLAYER_O_FOR_CROWN);
    return 1;
    }

    if (str == "sword")
    {
    if (TP->query_knight_level() == 4)
    {
        write("You are already a Knight of the Sword!\n");
        return 1;
    }
    if (TP->query_knight_level() != 3)
    {
        write("You cannot do that.\n");
        return 1;
    }
    if (TP->query_knight_sublevel() <= 6)
    {
        write("Your prestige isn't high enough to join the Sword " +
          "Order.\n");
        return 1;
    }
    if (TP->query_stat(SS_STR) <= 30 || TP->query_stat(SS_DEX) <= 20 ||
      TP->query_stat(SS_CON) <= 30 || TP->query_stat(SS_INT) <= 18 ||
      TP->query_stat(SS_WIS) <= 30)
    {
        write("You need higher stats than this before the " +
          "Sword Order will accept you.\n");
        return 1;
    }
    tmp = TP->query_prop(PLAYER_O_FOR_SWORD);
    if (!tmp || !P(tmp,TO))
    {
        write("You can only join the sword order if you have " +
          "been initiated and that knight is present here.\n");
        return 1;
    }
    write("You kneel before "+knighter->query_name()+", who performs the "+
      "ceremonial Knighting, touching each of your shoulders with "+
      POSSESSIVE(knighter)+" sword.\n");
    knighter->catch_msg(QCTNAME(TP)+" kneels before you, and you perform "+
      "the ceremonial Knighting, touching each of "+POSSESSIVE(TP)+
      " shoulders with your sword.\n");
    say(QCTNAME(TP)+" kneels before "+QTNAME(knighter)+", who performs "+
      "the ceremonial Knighting, touching each of "+QTNAME(TP)+"'s "+
      "shoulders with "+POSSESSIVE(knighter)+" sword.\n", ({ TP, knighter }));
    if (TP->query_gender() == 1)
        sir_lady = "Lady";
    else
        sir_lady = "Sir";
    knighter->command("$say Arise, "+sir_lady+" "+TP->query_name()+
      ", Knight of the Sword!");
    write("You are now a Knight of the Sword!\n");
    say(QCTNAME(TP) + " is now a Knight of the Sword!\n");
    (ADMIN)->log_action("order", knighter->query_name()+" initiated "+
	TP->query_name()+" into the Sword Order");
    TP->set_knight_level(4);
    if (ob = present("pal_med", TP))
        ob->set_knight_sublevel(1);
    TP->set_bit(1, 4);
    TP->clear_bit(1, 5);
    TP->set_skill(SS_PRESTIGE_ST, 26);
    TP->set_skill(SS_PRESTIGE_ACC, 18100);
    TP->change_prestige(1, 0);
    TP->remove_prop(PLAYER_O_FOR_SWORD);
    return 1;
    }

    if (str == "rose")
    {
    if (TP->query_knight_level() == 5)
    {
        write("You are already a Knight of the Rose!\n");
        return 1;
    }
    if (TP->query_knight_level() != 4)
    {
        write("You cannot do this.\n");
        return 1;
    }
    if (TP->query_knight_sublevel() <= 8)
    {
        write("Your prestige isn't high enough to join the Rose " +
          "Order.\n");
        return 1;
    }
    if (TP->query_stat(SS_STR) <= 50 || TP->query_stat(SS_DEX) <= 30 ||
      TP->query_stat(SS_CON) <= 50 || TP->query_stat(SS_INT) <= 38 ||
      TP->query_stat(SS_WIS) <= 50)
    {
        write("You need higher stats than this before the Rose " +
          "Order will accept you.\n");
        return 1;
    }
    tmp = TP->query_prop(PLAYER_O_FOR_ROSE);
    if (!tmp || !P(tmp,TO))
    {
        write("You can only join the rose order if you have " +
          "been initiated and that knight is present here.\n");
        return 1;
    }
    write("You kneel before "+knighter->query_name()+", who performs the "+
      "ceremonial Knighting, touching each of your shoulders with "+
      POSSESSIVE(knighter)+" sword.\n");
    knighter->catch_msg(QCTNAME(TP)+" kneels before you, and you perform "+
      "the ceremonial Knighting, touching each of "+POSSESSIVE(TP)+
      " shoulders with your sword.\n");
    say(QCTNAME(TP)+" kneels before "+QTNAME(knighter)+", who performs "+
      "the ceremonial Knighting, touching each of "+QTNAME(TP)+"'s "+
      "shoulders with "+POSSESSIVE(knighter)+" sword.\n", ({ TP, knighter }));
    if (TP->query_gender() == 1)
        sir_lady = "Lady";
    else
        sir_lady = "Sir";
    knighter->command("$say Arise, "+sir_lady+" "+TP->query_name()+
      ", Knight of the Rose!");
    write("You are now a Knight of the Rose!\n");
    say(QCTNAME(TP) + " is now a Knight of the Rose!\n");
    (ADMIN)->remove_squire_sponsorlist(TP->query_name());
    TP->set_knight_level(5);
    (ADMIN)->log_action("order", knighter->query_name()+" initiated "+
	TP->query_name()+" into the Rose Order");

    if (ob = present("pal_med", TP))
        ob->set_knight_sublevel(1);
    TP->set_bit(1, 4);
    TP->set_bit(1, 5);
    TP->set_skill(SS_PRESTIGE_ST, 26);
    TP->set_skill(SS_PRESTIGE_ACC, 18100);
    TP->change_prestige(1, 0);
    TP->remove_prop(PLAYER_O_FOR_ROSE);
    return 1;
    }
    return 0;
}


/* allow player to sit at the table */
int
sit(string str)
{
    NF("Sit where?\n");
    if (!str)
    return 0;

    NF("You can't sit there.\n");
    if (str != "chair");
    return 0;

    write("The chairs at the table are reserved for meetings of great " +
      "import or days of festival or ceremony. Today, neither is " +
      "occurring.\n");
    return 1;
}
