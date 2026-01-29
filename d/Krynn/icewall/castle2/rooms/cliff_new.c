#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>
inherit ICEOUTROOM;

int avalanche_done = 0;

public void
reset_icewall_room()
{
    set_searched(random(2));

    if(sizeof(FILTER_LIVE(all_inventory(TO))))
	return;

    avalanche_done = 0;
}

void
create_icewall_room()
{

    set_short("Under a high, snowy cliff");
    set_long("@@long_descr@@");


    add_exit("west_path1","south");
    add_exit("dark_cave","east","@@noenter_cave",1,1);

    add_cmd_item("cave","enter","With the mound of fresh snow " +
        "blocking the entrance, its not as simple as one might think.\n");
    add_item("canyon","The canyon is nothing but a deep fissure " +
        "in the snow, further limited by the high cliffs on the east " +
        "and west sides. You ponder why snow doesnt cover this place, and " +
        "reach a conclusion that avalanches on a regular bases must " +
        "bear the snow away, further into the south flatlands.\n");
    add_item(({"mound","fresh mound","fresh snow","mounds"}),"A" +
        " thick mound of fresh snow blocks the entrance to the cave. " +
        "You could, however, try to push your way in.\n");
    add_item(({"cliff","snowy cliff","high cliff"}),"Heavy with " +
        "snow, it looks quite dangerous. You hush, realizing that " +
        "any louder shout might bring down an avalanche!\n");
    add_item(({"cave","dark cave"}), "Dark, and partially blocked " +
        "by mounds of fresh snow fallen from the cliff, this natural " +
        "looking cave opens at the base of the cliff, leading east. " +
        "You think it might be possible to push through the snow " +
        "and enter the cave.\n");
    add_item(({"spot", "darker spot"}), "It appears to be an " +
        "entrance to a dark cave... but it is well blocked with mounds " +
        "of fresh snow fallen from the cliff.\n");
    add_item(({"castle","dark castle","icewall castle"}),"All you " +
        "can see is the high western wall of the castle. No battlements " +
        "are visible in the open, but narrow archers' slit cut the upper " +
        "part of the wall.\n");
    add_item("mountains","High and heavy with snow, they appear devoid " +
        "of any living inhabitants. Most of them are covered with the great " +
        "Icewall glacier.\n");
    add_item(({"glacier","icewall glacier"}),"The glacier starts high in " +
        "mountains to the north, but over the ages the twinkling icy " +
        "carpet flowed south, into the flatlands.\n");

    set_tell_time(800);

    add_tell("It is snowing hard... And white flakes begin to " +
        "cover you from head to toe.\n");
    add_tell("With a rustle, more snow slides down the cliff to "+
        "rest at its base!\n");
    add_tell("Wind picks up quite suddenly, scattering " +
        "snow and chilling you to the bone. You can " +
        "feel the first jabs of frostbite on your face. " +
        "This is definitely not a friendly land.\n");
    add_tell("You think you have just heard a strange shriek " +
        "carried here by the everpresent freezing wind.\n");
    add_tell("Snow whirls about you, creating myriad of patterns... " +
        "There is a strange beauty in them...\n\n\n" +
        "You shiver and slap your face. It must be the cold.\n");

    seteuid(getuid(TO));

    enable_reset(200);
    reset_icewall_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
        start_room_tells();
}

string
long_descr()
{
    return ("" +
	"Walking the arctic canyon around the base of the glacier, " +
	"you have entered an " +
	"U-shaped valley. High, snow-capped mountains block your way " +
	"to the north and west. To the east the glacier, pouring over "+
	"a rock outcropping, has created a steep, snowy " +
	"cliff that hangs over the canyon. Above it, you can see the " +
	"dark icewall castle. At the base of the cliff, against " +
	"the white of the snow, you notice a darker spot.\n");
}


int
noenter_cave()
{
    write("You attempt to walk into the cave, but there is too " +
        "much snow blocking your path! You could try to push through, " +
        "though.\n");
    say(QCTNAME(TP) + " tries to walk east, into the cave, but mounds " +
        "of fresh snow block the way effectively.\n");
    return 1;
}

int
push(string str)
{
    if(str != "through snow")
    {
        notify_fail("Push through what?\n");
        return 0;
    }

    if((TP->query_stat(SS_STR)) < 100)
    {
        say(QCTNAME(TP) + " tried to make " + HIS(TP) + " way " +
            "through the snow but is too weak to do it.\n");
        write("You try to push through the mound of snow but " +
            "are too weak to continue.\n");
        TP->add_fatigue(-50);
        return 1;
    }

    if((TP->query_fatigue()) < 50)
    {
        say(QCTNAME(TP) + " tried to make " + HIS(TP) + " way " +
            "through the snow but is too tired to do it.\n");
        write("You try to push through the mound of snow but " +
            "are too tired continue.\n");
        TP->add_fatigue(-50);
        return 1;
    }

    write("Grudging your way through the mounds of snow, you " +
        "force your way into the cave. Behind you, more snow " +
        "slides down from the cliff, obliterating your tracks.\n");
    say("With an effort, " + QTNAME(TP) + " pushes through " +
        "the mounds of snow at the base of the cliff " +
        "and enters the dark cave. Behind " + HIM(TP) + ", more " +
        "snow slides down from the cliff, blocking the path again.\n");
    tell_room(ROOMSK + "dark_cave", "Grudging " + HIS(TP) + 
        " way through the mound " +
        "of snow, " + QTNAME(TP) + " arrives from the outside.\n");
    
    TP->move_living("into the dark cave", ROOMSK + "dark_cave", 1, 0);
    TP->add_fatigue(-50);
    
    return 1;
}

// this function is called via alarm => no TP!!!
// also there is no need for this function to return anything
// (no way to check results anyway so better cast it void
void
no_avalanche(object tp)
{
    /* Player might have run off */
    if (environment(tp) != TO)
        return;

    tp->catch_tell("\nAs you shout, snow showers from above you in a rain " +
        "of flakes! It looks beautiful, a true example of Nature's " +
        "mastery of the art.\n");
    tell_room(TO, "\nAs " + QTNAME(tp) + " shouts, snow showers from above " +
        "you in a rain of flakes! It looks beautiful, a true example " +
        "of Nature's mastery of art.\n", tp); 
}

void
do_post_avalanche(object tp)
{

    tell_room(TO, "Fearing for your life, you thrash desperately and " +
        "manage to dig yourself out of the loose snow.\n\n" +
        "The deadly curtain of snow has got a solid hit on " +
        "you, bruising you badly.\n");
}

// this function is called via alarm => no TP!!!
void
do_avalanche(object tp)
{
    // here I will temporary set TP
    object old_tp = TP;
    set_this_player(tp);
    write("\nAs you shout, the cliffs above you shake and rumble! " +
        "Frozen, you catch your breath as tons of snow and ice " +
        "cascade down on you!\nYou have just the time to panic, " +
        "before a mighty avalanche barrels over you! A heavy " +
        "blanket of snow covers you completely!\n\n\n");
 
    say("As " + QTNAME(TP) + " shouts, the cliffs above you " +
        "shake and rumble! Frozen, you catch your breath as " +
        "tons of snow and ice cascade down on you!\nYou have " +
        "just the time to panic, before a mighty avalanche " +
        "barrels over you! A heavy blanket of snow covers you " +
        "completely!\n\n\n");
    // reset TP back to original value
    set_this_player(old_tp);

    tell_room(ROOMSK + "west_path1", "Tons of snow and ice " +
        "slide down from the cliffs to the north! Thankfully, " +
        "the avalanche did not rush through the whole canyon.\n");
    tell_room(ROOMSK + "west_path2", "Tons of snow and ice " +
        "slide down from the cliffs to the north! Thankfully, " +
        "the avalanche did not rush through the whole canyon.\n");

    set_alarm(1.5, 0.0, &do_post_avalanche(tp));
    FILTER_LIVE(all_inventory(TO))->heal_hp(-random(800));
}

/* int
died_in_avalanche()
{ 
      
       if (FILTER_LIVE(all_inventory(TO))->query_hp() <= 0)
          {
             player->catch_msg("Crushed under the snow and ice, " +
               "you attempt to breathe, but the punctured lungs " +
               "do not respond...\n");
             player->do_die(TO);
          }

return 0;
} */

int
do_shout(string str)
{
    if (!strlen(str))
	return 0;

    if (!avalanche_done)
    {
	set_alarm(1.5, 0.0, &do_avalanche(TP));
	avalanche_done = 1;
	return 0;
    }

    set_alarm(1.5,0.0, &no_avalanche(TP));
    return 0;
}

void
init()
{
    ::init();

    add_action(do_shout, "shout");
    add_action(push, "push");
}                   
