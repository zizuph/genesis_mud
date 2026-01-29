/*
 *	/d/Gondor/anorien/nimrais/cave/tunnel2.c
 *
 *	January 1996, Olorin
 */
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <filter_funs.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MIN_AWARE	 20
#define FATIGUE		 50

public void    cavein();

static int     heap_state = 0,
               pulled,
               alarm_id,
               stage;

public void
create_room()
{
    set_short("a narrow tunnel");
    set_long("@@long_desc@@");

    add_item(({"ground", "floor", "water", }), "The thin stream of "
      + "water is trickling downwards on the tunnel floor.\n");
    add_item(({"tunnel", "walls", }), BSN("The smooth walls are proof that "
      + "the tunnel was not created by mining, but probably by the steady flow "
      + "of water through a softer layer of rock."));
    add_item(({"rock"}), "@@exa_rock@@");
    add_item("oblong rock", "@@exa_rock|oblong@@");
    add_item("large rock",  "@@exa_rock|large@@");
    add_item(({"heap", "rocks", "stones", }), "@@exa_heap@@");
    add_cmd_item(({"rock", "oblong rock", "large rock", }), "pull", "@@pull_rock@@");

    add_exit(ANO_DIR + "nimrais/cave/tunnel1", "southeast", 0, 2);
    add_exit(ANO_DIR + "nimrais/cave/tunnel3", "northeast", "@@block_msg@@", 3);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT,  0);
}

public int
block_msg()
{
    if (!heap_state)
    {
        write("The passage upwards is blocked by the heap of rocks "
          + "and stones.\n");
        return 1;
    }

    write("You climb over the low heap of rocks.\n");
    return 0;
}

public string
long_desc()
{
    string  desc = "The tunnel makes a turn here, bending from "
                 + "southeast to northeast.";

    if (!heap_state)
        desc += " In the bend a large heap of rocks and stones has "
             +  "gathered and is blocking the passage further upwards.";

    desc += " To the southeast, the tunnel is leading downwards in a "
         +  "slope almost as steep as the one leading upwards. A thin "
         +  "stream of water is trickling down the slope on the ground.";

    return BSN(desc);
}

public void
reset_room()
{
    heap_state = 0;
    pulled = 0;
}

public string
exa_heap()
{
    string  desc;

    if (!heap_state)
    {
        desc = "The heap of rocks and stones is blocking the passage "
             + "upwards completely. The rocks and stones probably once "
             + "came sliding down from further upwards, and were stopped "
             + "by the bend that the tunnel makes here.";
        if (TP->query_skill(SS_AWARENESS) > MIN_AWARE)
            desc += " Looking closely, you notice that there is one "
                 +  "large oblong rock lying close to the ground in the "
                 +  "heap that might hold more than its fair share of "
                 +  "the heap back in place.";
    }
    else
        desc = "The ground is covered with many rocks and stones. "
             + "They form a low heap right in the bend of the tunnel, "
             + "but there should be no problem climbing over them.";

    return BSN(desc);
}

public int
query_heap_state()
{
    return heap_state;
}

varargs public string
exa_rock(string shape)
{
    string  desc;

    if (!heap_state)
    {
        desc = "The large oblong rock is lying close to ground, half "
             + "buried under other rocks and stones of the heap. It "
             + "might be dangerous to pull on it, as this might start "
             + "the heap sliding further down the tunnel.";
    }
    else
    {
        if (strlen(shape) && (shape == "oblong" || shape == "large"))
            desc = "You find no "+shape+" rock.";
        
        desc = "The rock of the walls, floor, and roof of the "
             + "tunnel is black, and hard and cold to the touch.";
    }

    return BSN(desc);
}

public void
slide_heap()
{
    object  rock;

    switch (stage++) 
    {
    case 0:
        tell_room(TO, "The heap of rocks and stones seems to flow down "
          + "the tunnel like a glacier made from rock.\n"
          + "It is impossible to stop it again now, and the only hope lies "
          + "in a quick escape.\n");
        tell_room(ANO_DIR + "nimrais/cave/tunnel1",
            "Some stones come tumbling down the tunnel from above.\n"
          + "It might be dangerous to stay here.\n");
        rock = clone_object(OBJ_DIR + "random_rock");
        rock->move(ANO_DIR + "nimrais/cave/tunnel1");
        tell_room(ANO_DIR + "nimrais/cave/back",
            "Some stones come falling down from above.\n"
          + "It might be dangerous to stay here.\n");
        rock = clone_object(OBJ_DIR + "random_rock");
        rock->move(ANO_DIR + "nimrais/cave/back");
        break;
    case 1:
        tell_room(TO, "The heap of rocks and stones comes sliding down "
          + "the tunnel, gathering speed, burying or tearing down everything "
          + "in its path.\n"
          + "Save yourself, as long as you still can!\n");
        tell_room(ANO_DIR + "nimrais/cave/tunnel1",
            "Some stones come wildly tumbling down the tunnel from above.\n"
          + "It is probably dangerous to stay here.\n");
        rock = clone_object(OBJ_DIR + "random_rock");
        rock->move(ANO_DIR + "nimrais/cave/tunnel1");
        tell_room(ANO_DIR + "nimrais/cave/back",
            "Some stones come falling down from above.\n"
          + "It is dangerous to stay here.\n");
        rock = clone_object(OBJ_DIR + "random_rock");
        rock->move(ANO_DIR + "nimrais/cave/back");
        break;
    case 2:
        tell_room(TO, "The heap of rocks and stones comes sliding down "
          + "the tunnel now with great speed, and nothing can withstand "
          + "it.\n");
        tell_room(ANO_DIR + "nimrais/cave/tunnel1",
            "Several stones come shooting down the tunnel from above.\n"
          + "It is lethally dangerous to stay here!\n");
        rock = clone_object(OBJ_DIR + "random_rock");
        rock->move(ANO_DIR + "nimrais/cave/tunnel1");
        tell_room(ANO_DIR + "nimrais/cave/back",
            "Some stones come falling down from above.\n"
          + "It is lethally dangerous to stay here.\n");
        rock = clone_object(OBJ_DIR + "random_rock");
        rock->move(ANO_DIR + "nimrais/cave/back");
        break;
    case 3:
        tell_room(TO, "You are buried under the avalanche of rocks.\n");
        heap_state = 1;
        cavein();
        tell_room(ANO_DIR + "nimrais/cave/tunnel1",
            "Several stones and rocks come shooting down the tunnel from above.\n"
          + "You can hear the low grumble and crunching of a rock avalanche coming down in the tunnel.\n"
          + "Run while you still can!\n");
        rock = clone_object(OBJ_DIR + "random_rock");
        rock->move(ANO_DIR + "nimrais/cave/tunnel1");
        tell_room(ANO_DIR + "nimrais/cave/back",
            "Several rocks and stones come falling down from above.\n"
          + "You can hear a low grumble and a crunching sound from above.\n"
          + "Leave while you still can!\n");
        rock = clone_object(OBJ_DIR + "random_rock");
        rock->move(ANO_DIR + "nimrais/cave/back");
        break;
    case 4:
        heap_state = 2;
        (ANO_DIR + "nimrais/cave/tunnel1")->cavein();
        tell_room(ANO_DIR + "nimrais/cave/back",
            "Rocks and stones come raining down from above.\n"
          + "You can hear the sounds of a rock avalanche advancing above.\n"
          + "Run and save your life!\n");
        rock = clone_object(OBJ_DIR + "random_rock");
        rock->move(ANO_DIR + "nimrais/cave/back");
        break;
    case 5:
        heap_state = 3;
        (ANO_DIR + "nimrais/cave/back")->cavein();
        break;
    case 999:
    default:
        heap_state = 4;
        remove_alarm(alarm_id);
        alarm_id = 0;
        break;
    }
}

public string
pull_rock()
{
    object  rock;

    if (heap_state || (alarm_id && sizeof(get_alarm(alarm_id))))
        return 0;

    if (TP->query_fatigue() < FATIGUE)
    {
        write("You are too tired!\n");
        return "";
    }

    write("You pull on the oblong rock with all your force.\n");
    say(QCTNAME(TP)+" pulls on something at the foot of the heap.\n");

    pulled += random(TP->query_stat(SS_STR));
    TP->add_fatigue(- FATIGUE);

    switch (pulled)
    {
        case 0..20:
            write("You hardly managed to move the rock.\n");
            break;
        case 21..50:
            write("You managed to move the rock a little.\n");
            break;
        case 51..80:
            write("The rock moved a little, and some rocks in the "
              + "heap seemed to move, too.\n");
            say("Some of the rocks in the heap seemed to move.\n");
            break;
        case 81..120:
            write("You succeeded in pulling the rock a litte out "
              + "from under the heap. Not much, but enough to notice "
              + "the all of the heap will slide down the tunnel if "
              + "you manage to pull out the rock completely.\n");
            say("Some small rocks and stones from the heap come tumbling "
              + "down and disappear downwards into the tunnel, and "
              + "some large rocks shifted their position dangerously.");
            tell_room(ANO_DIR + "nimrais/cave/tunnel1",
                "A few stones come tumbling down the tunnel from above.\n");
            rock = clone_object(OBJ_DIR + "random_rock");
            rock->move(ANO_DIR + "nimrais/cave/tunnel1");
            break;
        case 121..160:
            write("You manage to pull out the rock by quite a bit. "
              + "It is still holding the rest of the heap in place, "
              + "but some of the rocks in the heap already shifted "
              + "their position. The heap might start sliding down "
              + "any moment now.\n");
            say("A slight tremor is running through the heap, and "
              + "some rocks shift their position. The heap looks like "
              + "it might start sliding down any moment.\n");
            tell_room(ANO_DIR + "nimrais/cave/tunnel1",
                "A few stones and small rocks come tumbling down the tunnel "
              + "from above.\n");
            rock = clone_object(OBJ_DIR + "random_rock");
            rock->move(ANO_DIR + "nimrais/cave/tunnel1");
            tell_room(ANO_DIR + "nimrais/cave/back",
                "A stone comes tumbling down from above.\n");
            rock = clone_object(OBJ_DIR + "random_rock");
            rock->move(ANO_DIR + "nimrais/cave/back");
            break;
        case 161..200:
            write("You manage to pull the rock almost free. The heap "
              + "almost starts sliding down, and several small and some "
              + "large rocks roll down and disappear into the tunnel "
              + "leading down.\n");
            say("A tremor runs through the heap, and several small "
              + "and some larger rocks roll down and disappear into "
              + "the tunnel leading down. The heap might start to "
              + "slide down any moment now.\n");
            tell_room(ANO_DIR + "nimrais/cave/tunnel1",
                "A few stones and small rocks come tumbling down the tunnel "
              + "from above.\n");
            rock = clone_object(OBJ_DIR + "random_rock");
            rock->move(ANO_DIR + "nimrais/cave/tunnel1");
            tell_room(ANO_DIR + "nimrais/cave/back",
                "A stone comes tumbling down from above.\n");
            rock = clone_object(OBJ_DIR + "random_rock");
            rock->move(ANO_DIR + "nimrais/cave/back");
            break;
        case 201..1000:
            write("You pull the rock free. A tremor runs through the "
              + "heap, and slowly it begins to slide down, threatening "
              + "to bury everything in the tunnel under it.\n");
            say("A tremor runs through the heap, and slowly it begins "
              + "to slide down the tunnel, threatening to bury everything "
              + "in the tunnel beneath it.\n");
            tell_room(ANO_DIR + "nimrais/cave/tunnel1",
                "A few stones and small rocks come tumbling down the tunnel "
              + "from above.\n");
            rock = clone_object(OBJ_DIR + "random_rock");
            rock->move(ANO_DIR + "nimrais/cave/tunnel1");
            tell_room(ANO_DIR + "nimrais/cave/back",
                "A stone comes tumbling down from above.\n");
            rock = clone_object(OBJ_DIR + "random_rock");
            rock->move(ANO_DIR + "nimrais/cave/back");
            if (!alarm_id || !sizeof(get_alarm(alarm_id)))
            {
                stage = 0;
                alarm_id = set_alarm(5.0, 5.0, slide_heap);
            }
            break;
    }

    return "";
}

public void
clean_up()
{
    FILTER_DEAD(all_inventory(TO))->remove_object();
}

public void
cavein()
{
    int     sl,
            i;
    object *liv;

    liv = FILTER_LIVE(all_inventory(TO));

    for (i = 0, sl = sizeof(liv); i < sl; i++)
    {
        liv[i]->heal_hp(- (liv[i]->query_max_hp() + 1));
        liv[i]->do_die(TO);
        log_file("traps", liv[i]->query_name() + " killed by rock "
          + "avalanche in "+file_name(TO)+" at "+ctime(time())+".\n");
    }

    tell_room(ANO_DIR + "nimrais/cave/niche", "A loud roar is coming from "
      + "the tunnel to the northwest.\n"
      + "It sounds as if an avalanche of rocks and stones is coming down "
      + "the tunnel, burying everything under it.\n");
    tell_room(ANO_DIR + "nimrais/cave/entrance",
        "A loud scraping noise and small puffs of dust are coming from the back of the cave.\n");

    set_alarm(1.0, 0.0, clean_up);
}

