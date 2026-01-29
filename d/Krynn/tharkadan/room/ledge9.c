#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit THARK_OUT;
inherit HERBSEARCHNEW

string *herbs = HERB_MASTER->query_herbs(({"mountains",}));

void
reset_tharkadan_room()
{
    set_searched(0);
}

string
check_acrobatics()
{
    int acro_skill = TP->query_skill(SS_ACROBAT);
    string str, str2;

    // Success chance is (Acrobatic skill + 60) vs random(100);

    switch(acro_skill)
    {
       case 0:
         str = "Having no acrobatic skill, you would be rolling the " +
               "dice with the odds stacked against you to make it " +
               "across to the other side.";
         break;
       case 1..15:
         str = "Having minimal acrobatic skill, you would be rolling " +
               "the dice with even odds to make it across to the other " +
               "side.";
         break;
       case 16..25:
         str = "Having reasonable acrobatic skill, you would have a " +
               "decent chance of making it to the other side around " +
               "four out of five times.";
         break;
       case 26..40:
         str = "Having good acrobatic skill, you would have a decent " +
               "chance of making it to the other side around nine out " +
               "of ten times.";
         break;
       default:
         str = "Being a skilled acrobat, you feel confident in being " +
               "able to make it to the other side without fail.";
         break;
    }

    if(TP->query_prop("_suitable_for_kirijolith"))
     str2 = " You wonder if this is where you demonstrate your courage " +
            "as part of your Test of Faith?";
    else
     str2 = "";

    return str + str2;
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(ROOM + "ledge10","northwest",0);

    add_item(({"valley","vale","wide vale","protected vale",
         "isolated valley", "floor","centre","forested valley"}),
         "You stand on the side of a towering peak overlooking a wide " +
         "vale rimmed by mountains. Aspens and firs grow in abundance, " +
         "although the most notable feature of this valley is the " +
         "towering peak you currently stand on.\n");
    add_item(({"mountains"}),"Mountains rim the valley beneath you.\n");
    add_item(({"aspen","aspen trees","aspens"}), "You see aspen trees " +
         "growing in large numbers in the valley below.\n");
    add_item(({"fir","fir trees","firs"}), "You see large fir trees " +
         "growing in the valley below.\n");
    add_item(({"trees","tree"}), "Aspens and firs grow in abundance " +
         "below in the valley.\n");
    add_item(({"snow","snow-covered","snow-covered ground",
	 "white","snow-covered land","winters snow","winter's snow"}),
         "@@add_item_snow");
    add_item(({"towering peak","peak","ancient volcano","volcano",
         "mountain","ledge"}), "You are standing on the edge of a ledge " +
         "on the side of a towering peak. Across from you approximately " +
         "ten meters to your east another ledge continues up the peak. " +
         "There is nothing on that ledge for a grapple to secure itself " +
         "to, and it looks like the only way to get there is if a " +
         "skilled and daring acrobat ran at speed across the wall of " +
         "the peak, stepping only on a handful of footholds!\n");
    add_item(({"footholds","wall","wall of the peak","shelves"}),
         "Along the wall of the peak are a handful of small shelves of " +
         "stone. These shelves are all that is left of the ledge that " +
         "once ran from where you currently stand to the ledge that " +
         "starts ten meters to your west. A skilled acrobat may be able " +
         "to run across the wall to the other side, however a fall from " +
         "here risks death to all but the most hardy of mortals. " +
         "@@check_acrobatics@@ \n");
    add_item(({"summit"}),"You look up towards the summit, and estimate " +
         "you are getting close to the top.\n");

    add_cmd_item(({"across the wall","across wall","across the footholds",
         "across footholds","across shelves","across the shelves"}),
         "run","@@run_across_wall");

    seteuid(getuid(TO));

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs), ONE_OF(herbs) }), ({ "canyon","ground" }), 3);

    reset_tharkadan_room();
}

string
short_descr()
{
    return "a ledge high on the side of a towering peak in the " +
        "Tharkadan mountain range";
}

string
mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
	str = "The ledge starts here, running steeply upwards to your " +
            "northwest. ";
	break;
    case AUTUMN:
    case WINTER:
	str = "The snow-covered ledge starts here, running steeply " +
            "upwards to your northwest. ";
	break;
    }
    return str;
}

string
long_descr()
{
    return "You stand high on a ledge running along the side of a " +
        "towering peak that sits in the centre of a forested valley. " +
        mountain_desc()+ "Approximately ten meters to your east you see " +
        "another ledge continue down the mountain.\n";
}

void
fourth_jump(object player, int jump)
{
    if(E(player) != TO)
       return;

    write("You grab the edge of the eastern ledge and skillfully pull " +
        "yourself up, successfully making it across!\n");
    say(QCTNAME(player) + " grabs the edge of the eastern ledge and " +
        "skillfully pulls " +HIM(player)+ "self up and over!\n");
    player->move_living("M", ROOM + "ledge8", 1, 0);
    tell_room(E(player), QCTNAME(player)+ " pulls " +HIM(player)+ " " +
        "self up fromthe edge and on to the ledge.\n", ({ player }) ); 
    return;       
}

void
third_jump(object player, int jump)
{
    if(E(player) != TO)
       return;

    if(jump == 3)
    {
        write("You land awkwardly on the last foothold and slide off " +
            "it, falling down the side of the peak!\n");
        say(QCTNAME(player)+ " lands awkwardly on the last thin " +
            "foothold on the side of the peak and slips, falling down " +
            "the side of the peak!\n");
        player->command("$scream");
        write("\n\n\n\n\n\nYou plummet down the side of the peak to the " +
            "valley far below!\n\n\n\n\n\n\n\n");
        say(QCTNAME(player)+ " plummets down the side of the peak to " +
            "the valley far below.\n");
        player->move_living("M", ROOM + "vale7", 1, 0);
        tell_room(E(player), "You hear a scream from high up on the " +
             "towering peak before seeing " + QTNAME(player)+ " free " +
             "falling to the ground before you!\n", ({ player }) );
        player->heal_hp((-2500 - random(1000)));

/*
        if(player->query_hp() == 0)
        {
             write("You fatally free fall into the ground.\n");
             player->do_die();
        }
        else
*/
             write("You are seriously injured from your fall, but " +
                 "survived!\n");
        return;
     }

    write("You reach the last narrow shelf, and with your momentum push " +
        "off with both feet towards the edge of the eastern ledge!\n");
    say(QCTNAME(player) + " reaches the last of the narrow shelves with " +
        "quite a bit of momentum, then pushes off it powerfully with " +
        "both feet towards the edge of the eastern ledge!\n");

    set_alarm(2.5, 0.0, &fourth_jump(player, jump)); 
    return;       
}

void
second_jump(object player, int jump)
{
    if(E(player) != TO)
       return;

    if(jump == 2)
    {
        write("You land awkwardly on the second foothold and slide off " +
            "it, falling down the side of the peak!\n");
        say(QCTNAME(player)+ " lands awkwardly on the second thin " +
            "foothold on the side of the peak and slips, falling down " +
            "the side of the peak!\n");
        player->command("$scream");
        write("\n\n\n\n\n\nYou plummet down the side of the peak to the " +
            "valley far below!\n\n\n\n\n\n\n\n");
        say(QCTNAME(player)+ " plummets down the side of the peak to " +
            "the valley far below.\n");
        player->move_living("M", ROOM + "vale7", 1, 0);
        tell_room(E(player), "You hear a scream from high up on the " +
             "towering peak before seeing " + QTNAME(player)+ " free " +
             "falling to the ground before you!\n", ({ player }) );
        player->heal_hp((-2500 - random(1000)));

        if(player->query_hp() == 0)
        {
             write("You fatally free fall into the ground.\n");
             player->do_die();
        }
        else
             write("You are seriously injured from your fall, but " +
                 "survived!\n");
        return;
     }

    write("You land on the second narrow shelf with your right foot and " +
        "begin nimbly sprinting along the wall face towards the next " +
        "shelf!\n");
    say(QCTNAME(player) + " lands on the second narrow shelf with " +
        HIS(player)+ " right foot and begins sprinting along the wall " +
        "face - defying gravity! - towards another narrow shelf along " +
        "the wall of the peak!\n");

    set_alarm(2.5, 0.0, &third_jump(player, jump)); 
    return;       
}

void
first_jump(object player, int jump)
{
    if(E(player) != TO)
       return;

    if(jump == 1)
    {
        write("You land awkwardly on the first foothold and slide off " +
            "it, falling down the side of the peak!\n");
        say(QCTNAME(player)+ " lands awkwardly on the first thin " +
            "foothold on the side of the peak and slips, falling down " +
            "the side of the peak!\n");
        player->command("$scream");
        write("\n\n\n\n\n\nYou plummet down the side of the peak to " +
            "the valley far below!\n\n\n\n\n\n\n\n");
        say(QCTNAME(player)+ " plummets down the side of the peak to " +
            "the valley far below.\n");
        player->move_living("M", ROOM + "vale7", 1, 0);
        tell_room(E(player), "You hear a scream from high up on the " +
             "towering peak before seeing " + QTNAME(player)+ " free " +
             "falling to the ground before you!\n", ({ player }) );
        player->heal_hp((-2500 - random(1000)));

        if(player->query_hp() == 0)
        {
            write("You fatally free fall into the ground.\n");
            player->do_die();
        }
        else
            write("You are seriously injured from your fall, but " +
                "survived!\n");
        return;
    }

    write("You land on the first narrow shelf with your left foot and " +
        "launch yourself towards the next foothold!\n");
    say(QCTNAME(player) + " lands on the first narrow shelf with " +
        HIS(player)+ " left foot and then launches " +HIM(player)+ 
        "self towards another narrow shelf along the wall of the peak!\n");

    set_alarm(2.5, 0.0, &second_jump(player, jump)); 
    return;       
}

string
run_across_wall()
{
    int success_chance = TP->query_skill(SS_ACROBAT) + 60;
    int jump_roll = random(100) - success_chance;
    int jump_no;

    // Players doing the Test of Faith don't fall.
    if(TP->query_prop("_suitable_for_kirijolith"))
        jump_roll = 0;

    switch(jump_roll)
    {
        case 1..10:
            jump_no = 3;
            break;
        case 11..20:
            jump_no = 2;
            break;
        case 21..40:
            jump_no = 1;
            break;
        default:
            jump_no = 4;
            break;
    }

    write("You take a handful of steps back and then run towards the " +
        "ledge, jumping towards the first foothold jagging out from " +
        "the side of the steep peak wall.\n");
    say(QCTNAME(TP) + " takes a handful of steps backwards before " +
        "running towards the edge of the ledge, leaping off towards a " +
        "thin shelf of stone jagging out from the side of the steep " +
        "peak wall.\n");

    set_alarm(2.5, 0.0, &first_jump(TP, jump_no));
    return "";
} 
