/*
 * Pub for Goblin Caves
 * Based on the Prancing Pony Inn in Bree
 * Boreaulam, July 2014
 */
#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/d/Shire/lib/inn";
inherit L2_BASE_ROOM;
inherit "/d/Sparkle/lib/quest_reward";

#define PRICELIST_ID  ({"pricelist","list","prices", "menu"})
static int * sectors = ({20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 
                  3, 19, 7, 16, 8, 11, 14, 9, 12, 5});
int get_dstat(); 
int set_dstat(int dstat);
void finish_game();
void fail_game();
int return_darts(string str);
int dstat;
void rest_after_match(object player);

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    set_short("Broken Mug tavern");
    set_long("This large cave is the cheery home of the Broken Mug tavern. " +
        "You can see dozens of wooden tables scattered around, each with a " +
        "handful of sturdy chairs huddled around them. A stone counter runs " +
        "along the eastern wall with a large menu clearly attached to the " +
        "wall above it. Several black, iron chandeliers hang from the " +
        "ceiling, each holding many candles and keeping the cave well " +
        "lit. There appears to be a strange, wooden board hanging on the " +
        "southern wall, attracting a lot of attention from the patrons of " +
        "the tavern. An opening in the western wall leads back to the " +
        "underground lake and larger cavern outside.\n\n"); 

    add_item(({"counter", "bar", "countertop"}),
        "Running across the entire length of the eastern wall, this stone " +
        "counter appears to have been carved directly out of the cave " + 
        "itself. Seamlessly attached to both the floor and the northern " + 
        "wall, this counter has been finely worked to produce a smooth and " +
        "charming looking counter.\n");
    add_item(({"tables", "table", "wooden tables", "wooden table",
            "wood tables", "wood table"}),
        "There are dozens of tables here, of all different shapes and sizes. " +
        "There does not seem to be any consistency, almost as if the " +
        "proprietor of the inn simply grabbed any table he could get his " +
        "hands on. Most of the tables appear to be reasonably sturdy " +
        "and well worn with years of use.\n");
    add_item(({"chairs", "wooden chairs", "wooden chairs", "chair"}),
        "There are probably a hundred different chairs here, all collected " +
        "around tables of various shapes and sizes, and every single one " +
        "of them different and mismatched. Yet, for all of that, they " +
        "still appear to be quite solid and sturdy, perfect for a night " +
        "of enthusiastic drinking.\n");
    add_item(({"opening", "irregular opening"}),
        "There is an irregular shaped opening in the wall which leads back " +
        "out into the larger cavern you came from originally.\n");
    add_item(({"lake", "underground lake", "wide lake"}),
        "Barely visible through the opening in the western wall is " +
        "the wide underground lake which fills the middle of the " +
        "cavern outside.\n");
    add_item(({"cavern", "large cavern", "larger cavern"}),
        "When you look through the opening in the west wall, you can " +
        "see a large cavern with a wide lake in the middle of it.\n");
    add_item(({"caves", "caverns"}),
        "You are in a large series of caves and caverns that tunnel " +
        "deep beneath the mountains.\n");
    add_item(({"floor", "ground", "down"}),
        "The ground beneath your feet is the same grey stone as the " +
        "walls and ceiling around you, only it has been worn smooth " +
        "from centuries of traffic.\n");
    add_item(({"wall", "walls"}),
        "The walls here are made of the same grey stone as everything " +
        "else in these caves. On the southern wall, there appears to " +
        "be a wooden board that has attracted the attention of several " +
        "of the tavern's patrons.\n");
    add_item(({"ceiling", "up"}),
        "The dull grey stone of the ceiling has been chiseled here, " +
        "obviously worked by hand to expand what was probably a " +
        "naturally existing cave at first. Several iron chandeliers have " +
        "been hung here, each holding several candles to provide a wealth " +
        "of light across the Broken Mug.\n");
    add_item(({"chandelier", "chandeliers", "iron chandeliers",
            "black chandeliers", "iron chandelier", "black chandelier"}),
        "Several chandeliers, made from black iron and holding several " +
        "candles each, have been hung from the ceiling here to provide " +
        "enough light for the entire tavern.\n");
    add_item(({"stone", "grey stone", "granite"}),
        "This dull grey stone is the very bones of the mountains you are " +
        "currently beneath. This granite is very hard, but in many places " +
        "it appears that several industrious goblins have chiseled away " +
        "at the walls and ceilings to make these caves more habitable.\n");
    add_item(({"board", "dart board", "wooden board", "wooden dart board"}),
        "Hanging on the southern wall is a circular, wooden board. The " +
        "board has been painted in such a manner that it looks as if it " +
        "has been divided into twenty pie-shaped sections, each with a " +
        "small number painted upon it. A small note has been attached " +
        "to the bottom of the board, near a wooden box with several " +
        "metal darts contained inside.\n");
    add_item(({"darts", "dart", "box", "wooden box"}),
        "There are quite a few metal darts sitting inside a wooden box. It " +
        "seems as if people will occassionaly throw these darts into the " +
        "wooden board above it.\n");
    add_item(({"candle", "candles", "wax candle", "wax candles"}),
        "There are dozens of candles, all made of wax, burning brightly " +
        "inside the chandeliers which hang from the ceiling.\n");
    add_item(({"cave", "tavern", "broken mug", "broken mug tavern", "here"}),
        "This large cave is the cheery home of the Broken Mug tavern. " +
        "You can see dozens of wooden tables scattered around, each with a " +
        "handful of sturdy chairs huddled around them. A stone counter runs " +
        "along the eastern wall with a large menu clearly attached to the " +
        "wall above it. Several black, iron chandeliers hang from the " +
        "ceiling, each holding many candles and keeping the cave well " +
        "lit. There appears to be a strange, wooden board hanging on the " +
        "southern wall, attracting a lot of attention from the patrons of " +
        "the tavern. An opening in the western wall leads back to the " +
        "underground lake and larger cavern outside.\n");
    add_item(({"southern wall", "south wall"}),
        "The southern wall appears to be a rather popular part of the " +
        "tavern, with many of the patrons gathered around a circular " +
        "wooden board.\n");
    add_item(({"eastern wall", "east wall"}),
        "This wall has a large menu hanging above the long, stone " +
        "counter which covers the entire eastern end of the tavern.\n");
    add_item(({"northern wall", "north wall"}),
        "The northern wall of the tavern is just bare grey stone, finely " +
        "chiseled, but otherwise unremarkable.\n");
    add_item(({"western wall", "west wall"}),
        "The western wall of the tavern is marked by the opening which " +
        "leads back to the enormous cavern outside.\n");
    add_item(({"sector", "sectors", "section", "sections"}),
        "The sections are numbered from 1 to 20. Starting from the top and " +
        "moving clockwise, the numbers are organized in the following " + 
        "order:\n\t" +
        "20, 1, 18, 4, 13, 6, 10, 15, 2, 17, 3, " +
        "19, 7, 16, 8, 11, 14, 9, 12, 5\n" +
        "In the very center of the board, there are two small circles, the " +
        "smaller one in the center of the larger one.\n");
    add_item(({"circles", "small circles"}),
        "There are two small circles in the middle of the wooden board, one " +
        "within the other. The smaller one is painted red, and the ring " +
        "around it is painted green.\n");
    
    add_exit("roomf3", "west", "@@can_leave");

    add_item(PRICELIST_ID, "@@pricelist_desc");
    add_item("note", "@@get_darts_rules");
    
    add_npc(NPCS_DIR + "l2_bartender", 1, &->arm_me());
    
    configure_shire_inn();
} /* create_room */

/*
 * Function name:        init
 * Description  :        inits inn and adds commands for darts
 */
void
init()
{
    ::init();
    init_shire_inn();
    add_action("do_read", "read", 0);
    add_action("play_game", "play", 0);
    add_action("aim_dart", "aim", 0);
    add_action("return_darts", "return", 0);
    add_action("check_score", "check", 0);
} /*initXX */


/*
 * Function name:        pricelist_desc
 * Description  :        pricelist for drinks
 */
string
pricelist_desc()
{
    return "\n" +
    "\t+--------------------------------------------+\n" +
    "\t|                                            |\n" +
    "\t|   Drinks                                   |\n" +
    "\t|   ======================================   |\n" +
    "\t|   Dark Beer . . . . . . . . . . .  12 cc   |\n" +
    "\t|   Red Wine. . . . . . . . . . . .  24 cc   |\n" +
    "\t|   Strong Whiskey. . . . . . . . .  60 cc   |\n" +
    "\t|                                            |\n" +
    "\t+--------------------------------------------+\n" +
"\n\n";
} /* pricelist_desc */

/*
 * Function name:        get_darts_rules
 * Description  :        rules for darts game
 */
string
get_darts_rules()
{
    return "\n" +
    "\t+-----------------------------------------------------------------+\n" +
    "\t|                                                                 |\n" +
    "\t|                            DARTS                                |\n" +
    "\t|                                                                 |\n" +
    "\t| The goal of darts is to reduce your score to zero. Starting at  |\n" +
    "\t| 501, every dart you throw which hits the board will reduce your |\n" +
    "\t| score by that amount. The board is divided into twenty          |\n" +
    "\t| sections, worth points from 1-20. Each section has bonus        |\n" +
    "\t| 'double' and 'treble' sectors which are worth two and three     |\n" +
    "\t| times the value of the section respectively. There are two      |\n" +
    "\t| circles in the middle, one inside the other, called the         |\n" +
    "\t| 'bullseye'. The inner circle is worth 50 points and the ring    |\n" +
    "\t| around it is worth 25 points. The only catch is that your       |\n" +
    "\t| final throw to reach zero must hit a double sector.             |\n" +
    "\t|                                                                 |\n" +
    "\t| You can perform the following commands here:                    |\n" +
    "\t|                                                                 |\n" +
    "\t| <play game>            - start the game                         |\n" +
    "\t| <return darts>         - cancel the current game                |\n" +
    "\t| <check score>          - check the current score                |\n" +
    "\t| <aim X>                - try to hit section X                   |\n" +
    "\t| <aim X double/treble>  - aim for the bonus sector of X          |\n" +
    "\t| <aim center>           - aim for the bullseye                   |\n" +
    "\t|                                                                 |\n" +
    "\t| Note: Remember, the more you practice,                          |\n" +
    "\t|                 the better you will play!                       |\n" +
    "\t|                                                                 |\n" +
    "\t+-----------------------------------------------------------------+\n" +
"\n\n";
} /* get_darts_rules */

/*
 * Function name:        get_order
 * Description  :        create drinks
 */
mixed *
get_order(string item_name)
{
    object order;
    int price;

    setuid(); seteuid(getuid());
    switch (item_name)
    {
    case "beer":
    case "beers":
    case "dark beer":
    case "dark beers":
        order = clone_object(FOOD_DIR + "l2_beer");
        price = 12;
        break;
    case "wine":
    case "wines":
    case "red wine":
    case "red wines":
        order = clone_object(FOOD_DIR + "l2_wine");
        price = 24;
        break;
    case "whiskey":
    case "whiskeys":
    case "strong whiskey":
    case "strong whiskeys":
        order = clone_object(FOOD_DIR + "l2_whiskey");
        price = 60;
        break;
    }
    return (({order}) + ({price}));
} /* get_order */

/*
 * Function name:        is_playing
 * Description  :        check status
 */
int
is_playing()
{
    return this_player()->query_prop("GC_L2_dart_playing") == 1;
} /* is_playing */

/*
 * Function name:        is_resting
 * Description  :        check status
 */
int
is_resting()
{
    return this_player()->query_prop("GC_L2_dart_playing") == 2;
} /* is_resting */

/*
 * Function name:        can_leave
 * Description  :        player cannot leave while playing darts
 */
int
can_leave()
{
    if(!is_playing())
        return 0;
    write("You cannot leave while playing. <return darts> to stop playing.\n");
    return 1;
} /* can_leave */

/*
 * Function name:        do_read
 * Description  :        process read command
 */
int
do_read(string str)
{
    if (!str)
        return 0;
    if (member_array(str, PRICELIST_ID) != -1)
    {
        write(pricelist_desc());
        return 1;
    }
    if(str == "note")
    {
        write(get_darts_rules());
        return 1;
    }
    return 0;
} /* do_read */

/*
 * Function name:        play_game
 * Description  :        start game
 */
int
play_game(string str)
{
    if (!str)
        return 0;
    
    if(is_playing())
    {
        write("You are playing already.\n");
        return 1;
    }
        
    if(is_resting())
    {
        write("You are not focused enough to start another game. Perhaps you " +
            "should have a beer while you wait and gather yourself.\n");
        return 1;
    }
        
    this_player()->add_prop("GC_L2_dart_playing", 1);
    this_player()->add_prop("GC_L2_dart_score", 501);
    this_player()->add_prop("GC_L2_dart_attempts", 0);
    write("You take some darts and move closer to the dart board.\n");
    return 1;
} /* play_game */

/*
 * Function name:        aim_dart
 * Description  :        throwing a dart
 */
int
aim_dart(string str)
{
    if(!is_playing())
    {
        write("You are not playing. <Play game> to start.\n");
        return 1;
    }

    notify_fail("Please <read note> for rules.\n");
    int factor = 1;
    int scored = 0;
    if (!str)
        return 0;
        
    int sector = 0;
    string factor_str = "";
    if (!parse_command(str, all_inventory(this_player()),
        "[the] [sector] %d %w", sector, factor_str))
    {
        if (!parse_command(str, all_inventory(this_player()),
            "[the] [sector] %d", sector))
        if (!parse_command(str, all_inventory(this_player()),
            "[the] [sector] %w", factor_str))
        return 0;
    }
    
    int is_bull_eye = 0;
    if(factor_str == "double")
        factor = 2;
    else if(factor_str == "treble")
        factor = 3;
    else if((factor_str == "") || (factor_str == "single"))
        factor = 1;
    else if(factor_str == "center")
        is_bull_eye = 1;
    else
        return 0;
    
    int dstat = get_dstat();
    // calculate hit
    // Players with 200 DEX, 200 STR, 0 darts thrown 
    //              will have 99% chance to hit
    // Players with 100 DEX, 100 STR, 2000 darts thrown 
    //              will have 99% chance to hit
    // Players with 100 DEX, 100 STR, 1000 darts thrown 
    //              will have 74% chance to hit
    // Players with 100 DEX, 100 STR, 0 darts thrown 
    //              will have 49% chance to hit
    float tohit = itof((this_player()->query_stat(SS_DEX)
        + this_player()->query_stat(SS_STR))*10 + 
        dstat)/40.0;
    tohit = min(99.0, tohit - 1.0);
    
    if(itof(random(100)) >= tohit)
    {
        write ("You throw a dart, but it hits the board awkwardly " +
            "and falls on the floor.\n");
        set_dstat(dstat + 1);
        int attempts = this_player()->query_prop("GC_L2_dart_attempts");
        // update game attempts
        if((attempts + 1 >= LEVEL2_DARTS_LIMIT) && is_playing())
            fail_game();
        else
            this_player()->add_prop("GC_L2_dart_attempts", attempts + 1);

        return 1;
    }

    // calculate accuracy
    // Players with 200 WIS, 200 INT, 0 darts thrown 
    //              will have 99% chance to hit exact sector
    // Players with 100 WIS, 100 INT, 2000 darts thrown 
    //              will have 99% chance to hit exact sector
    // Players with 100 WIS, 100 INT, 1000 darts thrown 
    //              will have 74% chance to hit exact sector
    // Players with 100 WIS, 100 INT, 0 darts thrown 
    //              will have 49% chance to hit exact sector
    float acc = itof((this_player()->query_stat(SS_WIS)
        + this_player()->query_stat(SS_INT))*10 + 
        dstat)/40.0;
    acc = min(99.0, acc - 1.0);

    if(is_bull_eye)
    {
        if(itof(random(100)) >= acc)
        {
            scored = sectors[random(20)];        
            write ("You throw a dart, but it misses the bullseye and " +
                "hits sector " + scored + ".\n");
        }
        else
        {
            if(random(3)) // 66% to hit near bull eye
            {
                scored = 25;
                write ("You throw a dart, but it just misses the bullseye " +
                    "and instead hits the round sector around the bullseye.\n");
            }
            else
            {
                scored = 50;        
                write ("You hit the center of the dart board. Bullseye!\n");
            }
        }
    }
    else
    {
        if((sector < 1) || (sector > 20))
        {
            write("Try to aim for a sector from 1 to 20.\n");
            return 1;
        }
        
        int sector_index = -1;
        for(int i = 0; i < 20; i++)
            if(sectors[i] == sector)
                sector_index = i;

        if(itof(random(100)) >= acc)
        {
            if(random(2))
                scored = sectors[(sector_index + 19) % 20];
            else
                scored = sectors[(sector_index + 21) % 20];        
            write ("You throw a dart but it misses the sector you were " +
                "aiming for and hits sector " + scored + " instead.\n");
        }
        else
        {
            if(factor == 1)
            {
                scored = sector;        
                write("You hit sector " + scored + " with precision.\n");    
            }
            else 
            {
                // calculate factor accuracy
                // Players with 200 WIS, 200 INT, 0 darts thrown 
                //              will have 74% chance to hit exact sector
                // Players with 200 WIS, 200 INT, 1000 darts thrown 
                //              will have 99% chance to hit exact sector
                // Players with 100 WIS, 100 INT, 2000 darts thrown 
                //              will have 74% chance to hit exact sector
                // Players with 100 WIS, 100 INT, 1000 darts thrown 
                //              will have 49% chance to hit exact sector
                // Players with 100 WIS, 100 INT, 0 darts thrown 
                //              will have 25% chance to hit exact sector
                float factor_acc = acc - 25.0 + itof(dstat)/40.0;
                factor_acc = min(99.0, factor_acc);
                if(itof(random(100)) < factor_acc)
                {
                    scored = sector * factor;
                    if(factor == 2)
                        write("You hit the outer circle of sector " + 
                        sector + " with precision.\n");    
                    else
                        write("You hit the inner circle of sector " + 
                        sector + " with precision.\n");    
                }
                else
                {
                    scored = sector;
                    write("You miss the bonus area, but still hit sector " + 
                    scored + ".\n");    
                }
            }
        }
    }
    // check win condition
    int new_score = this_player()->query_prop("GC_L2_dart_score") - scored;
    int attempts = this_player()->query_prop("GC_L2_dart_attempts");

    if(new_score > 1)
        this_player()->add_prop("GC_L2_dart_score", new_score);
    else if(new_score == 1)
        write("You got more points than you needed. That throw does not " +
            "count, you will have to try again.\n");
    else if(new_score < 0)
        write("You got more points than you needed. Try again.\n");
    else // new_score is zero
        if(factor != 2)
            write("To finish a game, you need to hit a double. That " +
                "throw does not count, you will have to try again.\n");
        else
            finish_game();
    // update dart stat        
    set_dstat(dstat + 1);
    // update game attempts
    if((attempts + 1 >= LEVEL2_DARTS_LIMIT) && is_playing())
        fail_game();
    else
        this_player()->add_prop("GC_L2_dart_attempts", attempts + 1);
        
    return 1;
} /* aim_dart */

/*
 * Function name:        finish_game
 * Description  :        player finished a game
 */
void
finish_game()
{
    write("HOORAY!!! You won.\n");
    int attempts = this_player()->query_prop("GC_L2_dart_attempts");
    if(!this_player()->test_bit("Sparkle",
    GOBLIN_DARTS_GROUP,
    GOBLIN_DARTS_BIT1)) {
        // give first bit reward
        write("Your last dart hits the board and you feel satisfied with " +
            "the score..\n");
        give_reward(TP,
            GOBLIN_DARTS_GROUP,
            GOBLIN_DARTS_BIT1,
            GOBLIN_DARTS_EXP1,
            "darts_game1");
        if(attempts == 8)
            if(!this_player()->test_bit("Sparkle",
            GOBLIN_DARTS_GROUP,
            GOBLIN_DARTS_BIT2)) {
                // give second bit reward
                write("Reward 2");
                give_reward(TP,
                    GOBLIN_DARTS_GROUP,
                    GOBLIN_DARTS_BIT2,
                    GOBLIN_DARTS_EXP2,
                    "darts_game2");
            }
    } else {
        if(attempts == 8)
            if(!this_player()->test_bit("Sparkle",
            GOBLIN_DARTS_GROUP,
            GOBLIN_DARTS_BIT2)) {
                // give second bit reward
                write("People around you start screaming and cheering as " +
                    "you manage to reach zero in the minimum number of " + 
                    "throws!\n");
                give_reward(TP,
                    GOBLIN_DARTS_GROUP,
                    GOBLIN_DARTS_BIT2,
                    GOBLIN_DARTS_EXP2,
                    "darts_game2");
            }
    }

    return_darts("return darts");
} /* finish_game */

/*
 * Function name:        fail_game
 * Description  :        player failed to finish
 */
void
fail_game()
{
    write("ARGH!!! You failed to finish the game within " + LEVEL2_DARTS_LIMIT 
    + " attempts. Maybe you will have better luck next time.\n");
    return_darts("return darts");
} /* fail_game */

/*
 * Function name:        return_darts
 * Description  :        return darts
 */
int
return_darts(string str)
{
    if (!str)
        return 0;
        
    if(!is_playing())
    {
        write("You are not playing, so you have no darts to return.\n");
        return 1;
    }
        
    this_player()->add_prop("GC_L2_dart_playing", 2);
    set_alarm(20.0, 0.0, &rest_after_match(this_player()));

    this_player()->add_prop("GC_L2_dart_score", 0);
    this_player()->add_prop("GC_L2_dart_attempts", 0);
    write("You put the darts back inside the wooden box.\n");

    return 1;
} /* return_darts */

/*
 * Function name:        rest_after_match
 * Description  :        rest player after match
 */
void
rest_after_match(object player)
{
    player->add_prop("GC_L2_dart_playing", 0);
} /* rest_after_match */


/*
 * Function name:        check_score
 * Description  :        check score command
 */
int
check_score(string str)
{
	if(!str || ((str != "score") && (str != "the score")))
	{
		write("Check what?\n");
		return 1;
	}
		
    if(!is_playing())
    {
        write("You are not playing. <Play game> to start.\n");
        return 1;
    }
    write("Your score is: " + this_player()->query_prop("GC_L2_dart_score") + 
          " after " + this_player()->query_prop("GC_L2_dart_attempts") +
          " attempts.\n");
    return 1;
} /* check_score */

/*
 * Function name:        get_dstat
 * Description  :        get number of thrown darts by this player
 */
int
get_dstat() 
{
    string name = this_player()->query_name();
    dstat = 0;
    if (file_size(L2_DSTAT_DIR + name + ".o") > 0)
    {
        restore_object(L2_DSTAT_DIR + name);
    }
    return dstat;
} /* get_dstat */

/*
 * Function name:        set_dstat
 * Description  :        set number of thrown darts by this player
 */
int set_dstat(int arg)
{
    string name = this_player()->query_name();
    dstat = arg;
    save_object(L2_DSTAT_DIR + name);
} /* set_dstat */
