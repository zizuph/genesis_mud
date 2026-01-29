/*
 * Base room for Duneldings Camp
 *
 * --Raymundo, March 2020
 */
#pragma strict_types 
 
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";
inherit "/d/Shire/std/room/room_tell";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <language.h>
#include <tasks.h>
#include <composite.h>
#include "/d/Gondor/defs.h"
#include "defs.h"
#include "/d/Gondor/common/lib/clock.h"
#include "/d/Gondor/common/lib/herb_list.h"

#define UP  CAMP_ROOM_DIR + up_tree
#define TENT    "_a_tent_sits_here"
#define KILLER "i_kill_dunlendings"
//prototypes

void forest_herbs_1();
void forest_herbs_2();
void forest_herbs_3();
void forest_adds();
void forest_tells();
string sniper_shoot(); //so players get shot if they've been attacking//

//Controls which room the climb command goes to.
//Also controls whether or not the sniper_shoot function works properly
string up_tree;

void forest_adds_up();
string forest_up_long();
string forest_up_short();

void meadow_adds();
void meadow_tells();
string in_tent; //Controls entering tents in the meadows.
string extra_line(); //A clue that the tent is here.
void create_dunlending() {}

string tent_long();
string tent_short();

void path_adds();

void
create_gondor()
{
    set_short("to be filled in");   
    set_long("to bef illed in");
    
    
    set_room_tell_time(90);
    
    
    
    
    
    create_dunlending();
}

/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */
void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}

//Incase we want an animal in the room. Sounds fun for a forest.
void
add_random_animal()
{
    if(!random(4))
    {
        add_npc(ONE_OF_LIST(RANDOM_ANIMAL));
    }
}

//inside the tents
void
add_tent()
{
    add_prop(ROOM_I_INSIDE, 1);

    try_item( ({"pinecone", "pinecones", "needles", "needle", "pine needles", "pine needle"}),
        "The pine needles look like they blew into the room when the "
        + "tent flap was opened. The pinecones are about the size of "
        + "your fist and likely just got kicked through the tent "
        + "flap when a weary Dunlending was heading to bed, or perhaps "
        + "in the midst of a struggle.\n");
    try_item( ({"litter", "trash"}), "There are pinecones and pine needles "
        + "everywhere. But there are also discarded bones from meals "
        + "and scraps of cloth on the floor.\n");
    try_item( ({"scraps", "cloth", "scraps of cloth"}), "The scraps of cloth "
        + "seem to be pieces of old dresses or shirts, likely pillaged "
        + "from farms in the area. They look as if someone wiped their "
        + "dagger on them after slicing a hunk of meat from a bone.\n");
    try_item( ({"bone", "bones"}), "The bones have human teeth marks on "
        + "them. It seems the meat was gnawed off of them, and then the "
        + "bones discarded.\n");
    try_item("tent", "The tent is a quiet place to sleep out of the "
        + "weather. It's a bit dark, having no windows, but it's also "
        + "warm and dry.\n");
    try_item( "dust", "Dust lingers in the air. Sunlight sparkles as "
        + "it shines through the dust.\n");
    try_item( ({"door", "flap"}), "The exit to the tent is a flap of "
        + "canvas, pulled back to allow both light and fresh air to "
        + "enter the tent. You could call it a door if you were being "
        + "generous.\n");
    try_item( "bed", "The bed looks like a few crates of similar "
        + "sizes pushed together in a rectangle and covered with some "
        + "blankets.\n");
    try_item( ({"blanket", "blankets"}), "The blankets look like the "
        + "type of thing a farm wife would make out of her husband's "
        + "old trousers. You see red splotches of blood here and "
        + "there, indicating these blankets were taken, not made "
        + "especially for this occupant.\n");
    try_item(  ({"chair", "chairs", "table", "tables", "chest", "chests"}),
        "It looks like a crate, repurposed for another use.\n");
    try_item( ({"floor"}), "The floor is just dirt. While the walls of "
        + "tent are canvas, the floor is only dirt. You see pinecones "
        + "and pine needles and scraps of bones and other trash "
        + "strewn about. Even goblins don't make a mess this bad where "
        + "they sleep!\n");
    try_item( ({"wall", "walls", "ceiling", "roof"}),
        "Made of thick heavy canvas, it will definitely keep you dry.\n");
    try_item("canvas", "The tent is made of canvas.\n");
    
}

string 
tent_long()
{
    string *long_tent = ({
        "You stand inside a tent. Pinecones and pine needles litter "
            + "the floor. ",
        "Inside this cramped tent, things look dim, but not dark. ",
        "Looking around the tent, you see dust sparkle in the sunlight "
            + "streaming in from the door. ",
        "The inside of the tent looks cluttered and, frankly, a bit "
            + "dirty. "});
            
    string *crates_tent = ({
        "Wooden crates line the north wall of the tent, with no apparent "
            + "reason for which crate is stacked on another. ",
        "Hapazardly strewn about are wooden crates of various sizes. ",
        "You don't see any furniture here, except for a bed, "
            + "but there are several wooden crates that seem to "
            + "function as storage chests, chairs, and tables "
            + "all at the same time. ",
        "A heap of wooden crates is roughly stacked in a corner of "
            + "the tent. "});
    
    string *trash_tent = ({
        "Scattered across the floor, you notice discarded bones from "
            + "dinner, meat still clinging to them.\n",
        "Half-eaten pieces of meat have been thrown to the sides of the "
            + "tent.\n",
        "Remnants of last night's dinner can be seen strewn about "
            + "the tent, as if the occupants respects neither nature, "
    + "nor the efforts of the camp cook.\n"});
    return( ONE_OF_LIST(long_tent) + ONE_OF_LIST(crates_tent)
        + ONE_OF_LIST(trash_tent));
    
}

string
tent_short()
{
    string *short_tent = ({
        "Inside a Dunlending's tent", 
        "In a hidden tent",
        "In a tent in a meadow",
    "Inside a tent in a meadow"});
    return(ONE_OF_LIST(short_tent));   
}

//platform adds and room tells.
void
add_forest_up()
{
    forest_adds_up();
    
}

//downstairs forest rooms.
void add_forest()
{
    add_random_animal();
    forest_adds();
    forest_tells();
}


//forest_herbs_* which herb are in the room.
void
forest_herbs_1()
{
    set_up_herbs( ({HERB_DIR + "blueberry",
                    HERB_DIR + "strawberry",
                    HERB_DIR + "suranie",
                    KRYNN_HERB_DIR + "hawthorn"}));
}

void
forest_herbs_2()
{
    set_up_herbs( ({ HERB_DIR + "handasse",
                     HERB_DIR + "raspberry",
                     KRYNN_HERB_DIR + "bkd_sedge",
                     KRYNN_HERB_DIR + "lady_slipper"}));
}

void
forest_herbs_3()
{
    set_up_herbs ( ({ HERB_DIR + "curugwath",
                      HERB_DIR + "sumac",
                      HERB_DIR + "tuo",
                      KRYNN_HERB_DIR + "hazelnut"}) );
}

//basic adds. included in add_forest()
void
forest_adds()
{
    try_item( ({"forest"}), "Tall old-growth pine trees grow here. "
        + "They are far enough apart that it's easy to walk through "
        + "them, and there are no branches until further up the "
        + "trunk than even an ogre could reach.\n");
    try_item( ({"ground", "floor", "forest floor"}), "Pine needles "
        + "cover the floor. They are brown and crunch as you walk "
        + "over them. They smell strongly of pine.\n");
    add_cmd_item( ({"needles", "floor", "forest", "pine needles"}), ({"smell"}),
        "You bend down and put your nose close to the pine needles. As you "
        + "breathe in through your nose, you notice a very strong scent of "
        + "pine.\n");
    try_item( ({"needles", "pine needles"}), "The pine needles cover the "
        + "forest floor. They smell strongly of pine.\n");
    try_item( ({"sky", "clouds"}), "Through the trees, you see a few clouds "
        + "in the sky.\n");
    try_item( ({"branch", "branches"}), "There are branches far above your "
        + "head. They sway gently in the wind.\n");
    try_item( ({"wind", "breeze"}), "You stick out your hand and feel the "
        + "wind blowing.\n");
    try_item( ({"herb", "herbs", "plants"}), "Without taking a closer look, "
        + "you can't be sure what types of herbs these are, but you do "
        + "realize herbs grow here.\n");
    try_item( ({"tree", "trees"}), "These are pine trees. Their trunks are "
        + "straight and tall, and the branches way above your head. These trees "
        + "look old, and there is ample room between them for you to walk, or "
        + "even ride a horse!\n");
    try_item( ({"mountain", "mountains", "white mountain", "white mountains"}), 
        "Far to the southeast, rugged "
        + "mountains rise above the trees. You can barely see their peaks "
        + "from here.\n");
}

//pinecones are fun. let's have a pinecone.
void
add_pinecone()
{
    try_item(({"pinecone", "cone", "pine cone", "pinecones", "cones", "pine cones"}),
        "The pinecones are about the size of your hand. They're closed tight and "
        + "and feel sharp to the touch.\n");
    add_cmd_item(({"pinecone", "cone", "pine cone", "pinecones", "cones", "pine cones"}),
        ({"touch", "feel"}), "The pinecone feels sharp. Ouch!\n");
}

void
add_cliff()
{
    add_cmd_item( ({"cliff", "down cliff", "cliffs", "down"}), "climb",
        "The cliff is too steep! You'd fall and hurt yourself!\n");
    try_item( ({"cliff", "cliffs"}), "The forest ends abruptly here, "
        + "and a steep cliff leads down several hundred meters to a "
        + "ravine below.\n");
    try_item("ravine", "The ravine seems deep and narrow at the bottom. "
        + "It looks like it was carved or many thousands of years by spring "
        + "snowmelt from the White Mountains.\n");
}

//room tells for forests.
//Strangely, I'm running this all through the sniper_shoot() function
//To control whether or not people get shot while in the room.
void
forest_tells()
{

    add_room_tell("@@sniper_shoot@@");

}

//does your room have a platform?
int
do_climb()
{
    /*Must kill the dunlendings before you can climb*/
    object ob;
    if(objectp(ob = present("_dunlending_warrior_")))
    {
        write(ob->query_The_name(TP) + " blocks you from climbing up "
            + "the tree.\n");
            return 1;
    }
    /*I don't want climb skill to be a barrier, but I do want occasional fails*/
    if(TP->query_skill(SS_CLIMB) >= (20 + random(32)))
    {
    say(QCTNAME(TP) + " leaves climbing up the tree.\n");
    write("You climb up the tree.\n");
    TP->move_living("M", (CAMP_ROOM_DIR + up_tree));
    tell_room(CAMP_ROOM_DIR + up_tree, QCTNAME(TP) + " arrives climbing from "
        + "below.\n", TP);

    return 1;
    }
    else
    {
        notify_fail("You try to climb the tree but end up falling!\n");
        say(QCTNAME(TP) + " tries to climb the tree but falls instead!\n");
        return 0;
    }
}
//Does your room have a platform (cont)?
void
forest_climb(string str) //The str here sets the prototype up_tree for use in do_climb()
{
    up_tree = str;
    add_cmd_item( ({"tree", "up tree", "the tree", "up the tree", "up"}), 
        "climb", "@@do_climb@@");
    add_item( ({"tree", "trees"}), "Looking closely, you notice some wooden "
        + "pegs pounded into the trunk of one of the trees. You could likely "
        + "climb up it! The pegs lead toward a platform far above your head.\n");
    add_item( ({"peg", "pegs", "ladder"}), "The pegs are pounded into the "
        + "trunk of the tree as a kind of makeshift ladder. You could likely "
        + "climb the tree.\n"); 
    add_item( "platform", "The platform is made of wood and tied to branches "
        + "with ropes. It looks pretty sturdy from here.\n");
    add_item( ({"branch", "branches"}), "The branches far above your head hold "
        + "a wooden platform.\n");
    add_item( ({"rope", "ropes"}), "The ropes hold the platform to the branches.\n");
}

/* Function: add-forest_meadow()
 * Arguments: a string for the direction the meadow is from you.
 */
void
add_forest_meadow(string str)
{
    int med = random(3);
    switch(med)
    {
        case 0:
    try_item("meadow", "To the " + str + " the forest thins, exposing a "
        + "meadow. The grass in the meadow looks like it's nearly knee "
        + "high, and it is open to the sky.\n");
    try_item("grass", "In the meadow, you see grass, which is quite a "
        + "substantial change from all the pine needles you stand on "
        + "in the forest.\n");
        return;
        break;
        
        case 1:
    try_item("meadow", CAP(str) + " of here is a wide-open meadow. It has lush "
        + "grass growing in it, and looks to be the kind of place where a deer "
        + "would graze, abeit carefully for fear of the wolves that still "
        + "roam the area.\n");
    try_item("grass", "The grass looks very green, and like the kind of thing "
        + "a deer would eat.\n");
        return;
        break;
        
        case 2:
    try_item("meadow", "There are no trees " + str + " of here, just a wide-"
        + "open grassy meadow.\n");
    try_item("grass", "The grass is quite lush in the meadow.\n");
        return;
        break;
        
        default:
    try_item("meadow", "To the " + str + " the forest thins, exposing a "
        + "meadow. The grass in the meadow looks like it's nearly knee "
        + "high, and it is open to the sky.\n");
    try_item("grass", "In the meadow, you see grass, which is quite a "
        + "substantial change from all the pine needles you stand on "
        + "in the forest.\n");
        return;
        break;
    }

}

//Platform add_items.
void
forest_adds_up()
{
    try_item( ({"platform", "wooden plantform"}), "Made of rough-hewn "
        + "wooden boards, the platform is tied onto a few sturdy-looking "
        + "branches with ropes. It's large enough for a few people to "
        + "stand up here and keep watch.\n");
    try_item( ({"branch", "branches"}), "This high above the ground, "
        + "the branches are thick. You notice the platform is tied mainly "
        + "to branches that are as thick as your leg or so.\n");
    try_item( ({"rope", "ropes"}), "The ropes are made of braided hemp. "
        + "They keep the platform tightly held to the branches.\n");
    try_item( ({"forest", "trees", "pine trees"}), "The forest actually "
        + "seems much thicker up here among the branches than it did "
        + "down below. You see trees in every direction, and some "
        + "mountains in the distance.\n");
    try_item( ({"mountain", "mountains", "distance"}), "The mountains "
        + "are jagged and tough-looking. They seem to be the kind of "
        + "place trolls would live. You see an eagle circling above "
        + "them.\n");
    try_item("eagle", "The eagle circles above the mountains.\n");
    try_item( ({"sky", "clouds"}), "The sky looks expansive from here. "
        + "You feel like you could reach out and grab a cloud you're so "
        + "high.\n");
    try_item( ({"ground", "floor", "forest floor"}), "The forest floor "
        + "is a long ways down. Don't fall!\n");
    try_item("tree", "The tree is thick and sturdy. Pegs form a make-shift"
        + "ladder leading down toward the ground.\n");
    try_item( ({"peg", "pegs"}), "The pegs have been hammered into the "
        + "tree and can be used as a ladder to get down from up here.\n");
    try_item( ({"crate", "crates"}), "You see old crates piled up as make-shift "
        + "chairs.\n");
    try_item( ({"scraps", "food", "scraps of food"}), "The scraps of food look "
        + "like bones, and bread crumbs, and even some leaves. Clearly tidiness "
        + "is not a priority here.\n");
    try_item( ({"arrow", "arrows", "broken arrow", "broken arrows"}),
        "Broken arrows clutter the platform, demonstrating a lack of care in even "
        + "the most basic maintenance of equipment.\n");
}

/* Function Name:   forest_up_long()
 * Arguments:       None.
 * Description:     Creates a random long description for a platform room.
 *                  NOTE: Each string in the array ends with a space (except 
 *                        the final one which has a \n). You must include the 
 *                        space or the sentences will run together.
 */
string
forest_up_long()
{
    string *platform =
        ({"You stand on a large wooden platform. ", "Made of thick pine boards, the platform you stand on will support several people's weight. ", "Far above the forest floor, you stand on a wooden platform. ", "You find yourself on a flat wooden platform that is attached to a large pine tree with ropes. "});
    string *detail1 = 
        ({"Some crates are piled along the edges of the platform, creating make-shift chairs. ", "Scraps of food litter the platform. ", "Broken and crooked arrows have been tossed willy-nilly onto the platform, without any thought to how it looks. "});
        
    string *detail2 =
        ({"Nevertheless, this platform maintains a clear line of sight to the forest below, making it an effective vantage point for archers.\n", "Still, you find yourself able to clearly see what's happening below. This is a good place for archers to set up an ambush.\n", "From here, an archer is able to survey the whole forest and see danger as it approaches.\n", "Nearly invisible from below, this platform is the perfect place to lay in wait for a fat deer--or a careless enemy.\n"});

    return((ONE_OF_LIST(platform)) + (ONE_OF_LIST(detail1)) + (ONE_OF_LIST(detail2)) );
}

/* Function Name:   forest_up_short()
 * Arguments:       none.
 * Description:     Creates random short descriptions for platform rooms.
 */
 
string
forest_up_short()
{
    string *short =
    ({"On a platform above the forest floor", "A wooden platform tied to a tree", "On a wooden platform", "An archers' platform hidden in the tree branches", "On a platform attached to tree branches"});
    
    return(ONE_OF_LIST(short));
}

//If there is no <climb tree> room here, then these room tells will load.
void
no_sniper_adds()
{
   
    add_room_tell("A pinecone drops from above your head and lands with a "
        + "thud in some pine needles.");
    add_room_tell("Far above your head, branches sway.");
    add_room_tell("You see a flash of movement out of the corner of your "
        + "eye--only to realize it's a rabbit.");
    add_room_tell("Blackbirds perch high in the branches.");
    add_room_tell("From somewhere up high in the trees, you hear people "
        + "talking.");
    add_room_tell("You hear a wolf howl.");
    add_room_tell("You see a human quickly hide behind a tree.");
    
}

//part of archer_attack()
int filter_enemy(object enemy)
{
  if(!interactive(enemy))
    return 0;
  if(enemy->query_prop(KILLER))
    return 1;
  else
  return 0;
}

//part of archer_attack()
object *check_enemies()
{
  return filter(all_inventory(this_object()),"filter_enemy",this_object());
}

/* Function:    archer_attack()
 * Arguments:   none
 * Description: This function uses the room tell to launch arrows down from 
 *                  the platform above IF 1) there is a platform above 
 *                  (i.e. you can <climb tree> in this room, and 2) the 
 *                  the player has killed a dunlending. It was stolen from:
 *                  /d/Gondor/minas/lib/archery.c .
 */ 
void
archer_attack()
{
    object *enemy,
           *victims = ({}),
            armour,
            co;
    int     n, i, j,
            dam,
           *hloc_id,
            hloc,
            hit,
            hurt,
            phurt,
            hp,
            tmp;
  int old_prop, cur_pan;
    mixed  *hloc_ac,
            ac;
    string  mstr;

   

    enemy = check_enemies();

    n = sizeof(enemy);
    if (!n)
        return;

    string *arrow_notice = ({
        "Arrows rain down from the trees.\n",
        "Archers begin to shoot from above.\n",
        "Arrows come flying from somewhere up in the trees.\n",
    "Arrows fire in rapid succession from the platform in the trees.\n"});
    tell_room(TO, ONE_OF_LIST(arrow_notice), 0);
    
    for (i = 0; i < n; i++)
    {
        if ((hit = enemy[i]->resolve_task(TASK_DIFFICULT, ({SS_DEX, 
            SS_AWARENESS, SS_ACROBAT, SS_PARRY}))) < 0)
        {
            co = enemy[i]->query_combat_object();
            hloc_id = co->query_hitloc_id();
            tmp = random(100);
            for (j = 0, hloc = 0; hloc < sizeof(hloc_id); hloc++)
            {
                hloc_ac = co->query_hitloc(hloc_id[hloc]);
                if (!sizeof(hloc_ac))
                    break;
                j += hloc_ac[1];
                if (j >= tmp)
                    break;
            }
            if (hloc >= sizeof(hloc_id))
            hloc = sizeof(hloc_id) - 1;

            ac = hloc_ac[3];
    
        if (sizeof(ac))
            ac = ac[0];
        if (floatp(ac))
            ac = ftoi(ac);
        if (!intp(ac))
            ac = 0;

        dam = random(200);
        ac = random(ac);
        dam = F_DAMAGE(dam, ac);

            if (dam < 1)
                dam = 0;

            hp = enemy[i]->query_hp();

    /*
     * Wizards are immortal. (immorale ??)
     */
            if ((int)enemy[i]->query_wiz_level() && dam >= hp)
            {
            tell_object(enemy[i], "Your wizardhood protects you from death.\n");
                tell_room(environment(enemy[i]),
                    QCTNAME(enemy[i]) + " is immortal and fails to die!\n", enemy[i]);
            }
    
            if (dam > 0 && hp)
            {
                phurt = (100 * dam) / hp;
                if (dam && !phurt)
                    phurt = 1;     /* Less than 1% damage */
            }
            else if (dam > 0)
                phurt = 100;
            else
                phurt = -1;   /* Enemy missed */

            if (dam > 0)
                enemy[i]->heal_hp(-dam);
    
   
    
            if (phurt == 0)
                mstr = "Several arrows strike the ground near your feet.\n";
            else if (phurt == 1)
                mstr = "An arrow grazes you.\n";
            else if (phurt < 5)
                mstr = "A couple of arrows lightly wound you.\n";
            else if (phurt < 10)
                mstr = "You are struck by a couple of arrows.\n";
            else if (phurt < 20)
                mstr = "You are sliced by a few arrows.\n";
             else if (phurt < 30)
                 mstr = "Several arrows pierce you.\n";
             else if (phurt < 50)
                 mstr = "You are wounded badly by a volley arrows.\n";
            else if (phurt < 70)
                mstr = "You are seriously wounded by several well-aimed arrows.\n";
            else if (phurt < 90)
                mstr = "An arrow sinks deep into your body, inflicting a dangerous wound!\n";
             else
                 mstr = "Several arrows strike you, some sinking deep into your body.\n"+
                   "You are mortally wounded!\n";
            enemy[i]->catch_msg(mstr);
         
            victims += ({enemy[i]});
        }
    }
    switch(sizeof(victims))
    {
        case 0:
            tell_room(TO, "The arrows miss.\n");
            break;
        case 1:
            tell_room(TO,QCTNAME(victims[0]) + " is hit by an arrow.\n", victims[0]);
            break;
        default:
            tell_room(TO,CAP(COMPOSITE_LIVE(victims)) + " are hit by arrows.\n", victims);
            break;
    }
    for (i = 0; i < sizeof(victims); i++)
    {
        if (victims[i]->query_hp() <= 0)
        {
            victims[i]->do_die(TO);
           
        }
    }
  
}  


/* Function Name:   sniper_shoot()
 * Arguments:       none
 * Description:     Checks to see if a <climb tree> room has loaded. (If
 *                  a <climb tree> room exists here, the string up_tree
 *                  will have a value.) If there IS a <climb tree> room, 
 *                  then it will adjust room tells based on whether or
 *                  not anything lives in the <climb tree> room. Eventually,
 *                  this will include the possibility for players getting shot
 *                  by archers from above.
 */
 
string
sniper_shoot()
{
    string desc;
    object entr_room, *people;
    
    if(!up_tree)
    {
        no_sniper_adds();
        return("You notice sudden movement in the branches above your head, "
            + "but it was only an owl.");
    }

    if (objectp( entr_room = find_object( CAMP_ROOM_DIR + up_tree ) ))
    {
        if (sizeof( people = FILTER_LIVE( all_inventory( entr_room ) ) ))
        {
            //These are the room tells if we have something living on the platform
            string *adds =
            ({"The platform overhead creaks, as if archers shifted their weight.", "You see an archer look down at you from the platform overhead.", "You hear a soft rattling sound, as if an archer were getting an arrow from a quiver.", "From up above, you hear: If anyone tries anything, shoot to kill.", "You hear footsteps from overhead."});
            archer_attack();
            return(ONE_OF_LIST(adds));
        }
        //Room tells for NOTHING living on the platform 
        string *dead_adds =
        ({"The platform is eerily silent overhead.", "You hear the cakaaw, cakaaw of a crow.", "The wind blows, shifting the platform overhead.", "A drop of blood drips down on you from the platform overhead.", "For a moment, the forest canopy is silent."});
        return(ONE_OF_LIST(dead_adds));
    }
    else
    {
        //This tends to happen when the <climb tree> room hasn't loaded yet, 
        //So in practical terms, right after Armageddon.
        return("The wind blows, making you shiver.");
    }
}

//added to all outdoor meadow rooms.
void add_meadow()
{
    meadow_adds();
    meadow_tells();
    
}

//add items for meadows.
void
meadow_adds()
{
    try_item( ({"grass", "grasses", "meadow", "meadows"}), 
        "The grass in this meadow is quite tall, about up to a human's "
        + "knee in most places. In addition to grass, you see many herbs "
        + "and even the occasional patch of skunk cabbage.\n");
    try_item( ({"cabbage", "skunk cabbage", "patch"}),
        "An early blooming plant, skunk cabbage likes wet areas in forests, "
        + "such as this meadow.\n");
    try_item( ({"herb", "herbs"}), "There are many herbs here in the meadow, "
        + "but you'd need to take a closer look to see which ones are which.\n");
    try_item( ({"tree", "trees"}), "Large, tall pine trees create a forest on the "
        + "edge of the meadow. The trees are so large you could probably build "
        + "a small house in their branches!\n");
    try_item( ({"flower", "flowers"}), "Various wildflowers grow in the "
        + "meadow. Some are pink, others purple, and others still are yellow.\n");
    try_item( ({"sky", "cloud", "clouds"}), "You have a wide-open view of the "
        + "sky from here, since there are no trees in the meadow. You could easily "
        + "check the time.\n");
    try_item( ({"ground", "dirt", "soil"}), "The ground is, for the most part, "
        + "covered in grass.\n");
    try_item( ({"campfire", "smoke", "campfire smoke", "camp fire", "camp fire smoke"}),
        "Smoke rises here and there throughout the meadow. In each "
        + "instance, the smoke looks well-contained, leading you "
        + "to believe it's campfires or cooking fires, not an out-of-"
        + "control wildfire.\n");
    try_item( ({"tent", "tents"}), "You don't see any tents here. They must "
        + "be well camoflauged, if they are around at all.\n");
    
}
//room tells for meadows.
void
meadow_tells()
{
    add_room_tell("On the edge of the meadow, you see movement in a tree.");
    add_room_tell("A deer, wary of predators, sneaks into the meadow looking "
        + "for something to eat.");
    add_room_tell("A fox sneaks through the grass, stalking its prey.");
    add_room_tell("You hear the harsh tones of humans talking somewhere in "
        + "the distance.");
    add_room_tell("Clouds float across the open sky.");
    add_room_tell("A murder of crows circles the meadow, looking for carrion.");
    add_room_tell("Campfire smoke rises in the distance.");
    
    
    
}

//works with enter_tent()
int
do_enter()
{
   /*Must kill the dunlendings before you can enter the tent*/
    object ob;
    if(objectp(ob = present("_dunlending_warrior_")))
    {
        write(ob->query_The_name(TP) + " blocks you from entering the "
            + "tent.\n");
            return 1;
    }
    say(QCTNAME(TP) + " lifts the flap and enters the tent.\n");
    write("You lift the flap and enter the tent.\n");
    TP->move_living("M", (CAMP_ROOM_DIR + in_tent));
    tell_room(CAMP_ROOM_DIR + in_tent, QCTNAME(TP) + " arrives from "
        + "outside.\n", TP);

    return 1;
     
    
}

/*
 * Function Name: extra_line()
 * Arguments:     none
 * Description:   For the outdoor meadow rooms, this will add a description
 *                    of a camoflauged tent into the long description of the 
 *                    room so that players know there is a tent here.
 */
string
extra_line()
{
    if(TO->query_prop(TENT))
    {
        string *tent_desc =
            ({"An odd mound sits, almost invisible, in the grass. ", 
            "You see a strange mound here, covered in sticks and grass. ",
            "At first, you thought the large mound here was a bush, but "
                + "now you have your doubts. ", 
            "A carefully hidden mound "
                + "sits amongst the grass, making it difficult to spot at "
                + "first. "});
        return(ONE_OF_LIST(tent_desc));
    }
    else
        return("");
}

/*
 * Function name:   enter_tent()
 * Arguments:       str -- the name of the tent room 
 *                      eg m1 would have the tent room m1t.
 *                      m2 would be m2t, etc.
 * Description:     This function includes the add_items and
 *                      add_cmd_item necessary to include the 
 *                      tent rooms.
 */
void
enter_tent(string str)
{
    in_tent = str;
    add_cmd_item( ({"tent", "in tent", "the tent", "mound", "the mound"}), 
        "enter", "@@do_enter@@");
    try_item("flap", "A heavy piece of canvas, the flap can be used to keep "
        + "night air or rain out of the inside of the tent. When you enter the "
        + "tent, you'll likely lift the flap out of your way so it doesn't "
        + "hit you in the face.\n");
    try_item( ({"mound", "large mound"}), "Looking closely, you notice the "
        + "mound is a tent!\n");
    add_item("tent", "Made of waxed canvas, the tent has been expertly "
        + "camouflaged using grass and things available in the meadow. It "
        + "looks just like the surrounding meadow, and if you weren't looking "
        + "for it, you'd miss it. You could probably enter the tent.\n");
    try_item( ({"camouflaged", "camouflage"}), "You know, the art of making "
        + "things appear like their surroundings.\n");
    add_item( ({"ground", "grass", "meadow", "grasses"}),
        "The grass has been trampled here, and the ground packed down, by "
        + "people wearing heavy military style boots. These are not the "
        + "type of boots you wear to be stealthy through the woods; these are "
        + "the kind of boots you wear when you plan on invading a city.\n");
    add_room_tell("A campfire smoulders near the entrance to the tent.");
    add_item("entrance", "The entrance to the tent is covered with a flap, "
        + "but you would likely just move the flap as you enter the tent.\n");
    add_cmd_item("flap", "move", "You poke at the flap with your hand. It "
        + "moves. You could probably enter the tent.\n");
    add_item( ({"fire", "campfire", "camp fire"}), "In the center of a ring "
        + "of stones, you see a smoldering fire. It's still hot, and so "
        + "it could be stoked back up with some firewood and a few pine "
        + "needles.\n");
    try_item( ({"ring", "stones", "ring of stones"}), "The stones are placed "
        + "in a circle and stacked about claf-high. They are soot-stained "
        + "on the inside from the campfire.\n");
        
}

//possible herbs. 3 variations. random(ish) but mapable.   
void
meadow_herbs_1()
{
    set_up_herbs( ({
            KRYNN_HERB_DIR + "tiger_lily",
            SHIRE_HERB_DIR + "huckleberry",
            HERB_DIR + "chervil",
            SHIRE_HERB_DIR + "bilberry"}));
}

void
meadow_herbs_2()
{
    set_up_herbs( ({
            KRYNN_HERB_DIR + "dandelion",
            KRYNN_HERB_DIR + "locoweed",
            HERB_DIR + "rpotato",
            KRYNN_HERB_DIR + "chicory"}));
}

void
meadow_herbs_3()
{
    set_up_herbs( ({
            SHIRE_HERB_DIR + "grass",
            KRYNN_HERB_DIR + "sm_camas",
            KRYNN_HERB_DIR + "tiger_lily",
            HERB_DIR + "ungolestel"}));
}

/* Function:    add_meadow_forest()
 * Arguments:   A string for the direction the forest is from the
 *              current room.
 * Description: add_item for a visible forest.
 */
 void
add_meadow_forest(string str)
{
    string *forest = ({ (CAP(str) + " of the meadow you see a forest of tall "
        + "pine trees.\n"), ("There is a pine forest to the " + str + ".\n"),
        ("Tall pine trees, bigger around than an Ogre's outstreached arms, "
        + "cast shadows from the " + str + ".\n"), ("You see a forest " +
        str + " of you. The trees are tall, and the forest floor covered in "
    + "pine needles.\n") });
    
    add_item( ({"forest", "forests"}), ONE_OF_LIST(forest));
}
 
void 
 add_guard_down()   
 {
    if(!random(3))
    {
        add_npc(CAMP_NPC_DIR + "guard");
        add_npc(CAMP_NPC_DIR + "scout");
        if(!random(10))
        {
            add_npc(CAMP_NPC_DIR + "captain");
        }
    }
 }
 
void
path_adds()
{
    try_item( ({"farm", "farmhouse", "house"}),
        "Far to the northwest, you see a farm, complete with a farmhouse. "
        + "From here it's hard to be certain, but it looks as if it's been "
        + "recently pillaged. Quite a lot of smoke rises up from the farm.\n");
    try_item("smoke", "Where there's smoke, there's fire--and this looks "
        + "like more than an average amount of smoke.\n");
    try_item( ({"field", "fields"}), "There are fields on each side of the "
        + "path. They seem to be planted with wheat, but weeds have grown up "
        + "so high that the fields look compeltely untended.\n");
    try_item( ({"weed", "weeds"}), "The weeds are nearly as tall as the wheat, "
        + "but not being a farmer, it is difficult for you to determine "
        + "exactly which type of weeds they are.\n");
    try_item( ({"path", "road", "trail"}), "The path is little more than "
        + "a dirt trail between the fields. It leads from the farm to the "
        + "forest.\n");
    try_item( ({"forest", "tree", "trees", "meadow"}),
        "Southeast of here is a forest full of ancient tall pine trees. You "
        + "notice a large, open meadow as well.\n");    
    try_item("wheat", "The wheat is tall and golden. Unfortunately, weeds "
        + "are growing wildly in the fields. It seems the farmer isn't doing "
        + "his job!\n");
    try_item("farmer", "You see no farmer. That's part of the problem!\n");
    try_item("ground", "You look down. There are fields on both sides of the "
        + "path.\n");
    
}
