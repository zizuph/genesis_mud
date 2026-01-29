/* /d/Faerun/guilds/warlocks/rooms/train.c
 *
 * Warlock training room.
 *
 * Nerull, 2018
 *
 * Increased herbalism from 50 to 60. Tax documentation adjusted
 * to reflect this change - Nerull 2020
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <money.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;
inherit "/lib/skill_raise";
inherit "/lib/guild_support";

void set_up_skills();

//Items for cloning
public string cleaner_str = WARLOCK_GUILDDIR + "obj/c_cleaner.c";
public string tote_str = "/d/Faerun/obj/tote.c";
public string wing_str = WARLOCK_GUILDDIR + "obj/war_wing.c";
public string blood_str = WARLOCK_GUILDDIR + "obj/war_blood.c";
public string dust_str = WARLOCK_GUILDDIR + "obj/war_dust.c";
public string guano_str = WARLOCK_GUILDDIR + "obj/war_guano.c";
public string powder_str = WARLOCK_GUILDDIR + "obj/war_powder.c";
public string spleen_str = WARLOCK_GUILDDIR + "obj/war_spleen.c";
public string sulphur_str = WARLOCK_GUILDDIR + "obj/war_sulphur.c";
public string tear_str = WARLOCK_GUILDDIR + "obj/war_tear.c";


/*
 * Function name: read_buylist
 * Description  : Function to show what's for sale.
 */
int
read_buylist(string str)
{
    write("\n");
    write("+-----------------------------------------------------+\n");
    write("|                 Name                 |  Price       |\n");
    write("+-----------------------------------------------------+\n");
    write("| A round black amulet                 |  8000 Copper |\n");
    write("| A well-used leather tote (open)      |  5000 Copper |\n");
    write("| A bloody fairy wing                  |  4000 Copper |\n");
    write("| A tiny vial of virgin's blood        |  3500 Copper |\n");
    write("| A pinch of vampire dust              |  4500 Copper |\n");
    write("| A pinch of bat guano                 |  2500 Copper |\n");
    write("| A pinch of fine bone powder          |  4000 Copper |\n");
    write("| A tiny bat spleen                    |  3500 Copper |\n");
    write("| A yellow lump of sulphur             |  2500 Copper |\n");
    write("| A solified tear of the innocent      |  3500 Copper |\n");
    write("+-----------------------------------------------------+\n");
    write("\n");

    return 1;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 1);

    set_short("You are inside a narrow humid claystone cavity");

    set_long("You are inside a narrow humid claystone cavity. The "
    +"close proximity of the jagged walls in conjunction with the "
    +"constant torrent of steam emanating from the large iron "
    +"cauldron makes this place very humid and slightly claustrophobic. The "
    +"reek of boiled infant flesh stings in your nostrils, forcing you "
    +"at times to face away from the cauldron and towards the various "
    +"claystone depressions and sharp jagged mold-infested edges that "
    +"are present everywhere. Tiny toes and fingers from various "
    +"humanoid infants hang in hairlike threads anchored to the "
    +"ceiling. Small black candles in several depressions in the "
    +"walls emit some level of illumination to the environment, along "
    +"with flickering shadows. It is possible to <meditate> here. You notice "
    +"plaque on the wall containing a list of components for sale.\n");

    create_skill_raise();
    set_up_skills();

    add_item(({"candle", "candles", "black candles",
    "small black candles", "small candles"}), "These are small sticks of "
    +"black wax. They occupy small depressions in the claystone walls, and "
    +"provide the area with some collective illumination.\n");
    
    add_item(({"wooden fire", "fire"}), "Under the cauldron there is "
    +"a burning wooden fire, consisting of various dried branches "
    +"from dead trees. It emanates a lot of heat, maybe enhanced "
    +"by ancient magic to keep it much more intense.\n");
    
    add_item(({"humidity"}), "When you breathe, it's like breathing "
    +"water. Small pearls of water forms on your forehead simply "
    +"for being in this cavity.\n");
    
     add_item(({"shadows", "flickering shadows"}), "The shadows formed "
     +"by jagged edges and "
     +"formations in the cave dance in unison with the flickering of "
     +"the lit candles. You feel slightly dizzy when focusing on them.\n");
    
    add_item(({"cavity", "cave"}), "This cavity seems to be the result "
    +"of erosion from water gone long ago. It's full of jagged edges "
    +"and small depressions.\n");
    
    add_item(({"hairlike threads", "threads"}), "Hmm...they are thin and "
    +"strikingly resembles hair. Actually, when you think of it, the threads "
    +"seem to be made of humanoid hair!\n");
    
    add_item(({"tiny fingers", "fingers", "humanoid fingers",
    "tiny humanoid fingers"}), "The fingers are from various types "
    +"of humanoids; humans, elves, dwarves, drows, hobbits and "
    +"kenders. Some are new, some are old, but they all are "
    +"from infants. They hang dangling tied together with "
    +"thin hairlike threads hanging from the ceiling.\n");
    
    add_item(({"tiny toes", "toes", "humanoid toes",
    "tiny humanoid toes"}), "The toes are from various types "
    +"of humanoids; humans, elves, dwarves, drows, hobbits and "
    +"kenders. Some are new, some are old, but they all are "
    +"from infants. They hang dangling tied together with "
    +"thin hair-like threads hanging from the ceiling.\n");
    
    add_item(({"ceiling", "roof"}), "The ceiling is jagged and filled "
    +"with black spots of mold. At the west side of the ceiling, thin "
    +"hairlike threads anchored to iron bolts hang from the "
    +"ceiling, carrying the weight of numberous tiny humanoid "
    +"fingers and toes. A few satchels filled with various herbs "
    +"hang from the ceiling too, tied to some jagged edges.\n");
    
    add_item(({"wall", "walls", "jagged walls", "jagged wall"}), "Sharp "
    +"jagged claystone edges decorate the rough walls here along with "
    +"many small depressions. They are "
    +"probably a result of erosion. A plaque of buyable components "
    +"hangs on the west wall.\n");
    
    add_item(({"depression", "depressions", "small depressions"}), "They "
    +"are small natural groves created by erosion, and they are "
    +"everywhere in this cavity. Also, they are put to good use by "
    +"someone as they all have small lit black candles that illuminate "
    +"the room. Cozy.\n");
    
    add_item(({"torrent of steam", "steam", "torrent"}), "The torrent "
    +"is a result of something boiling violently in the large iron "
    +"cauldron. It makes the room steamy and very humid, for not to "
    +"mention adding the reek of boiled infant flesh.\n");
    
    add_item(({"spots", "mold", "black mold"}), "Various black puffy "
    +"spots of poisonous mold pride many of the jagged claystone "
    +"edges. It is probably unhealthy to stay in this environment "
    +"for too long.\n");
    
    add_item(({"plaque"}), "This is an old wooden board serving "
    +"as a plaque. It contains a list of ingredients that the "
    +"Whispess will sell for coin. Read it.\n");
    
    add_item(({"edges", "jagged edges", "mold-infested edges"}), "Every "
    +"surface of the walls and the ceiling consists of sharp natural "
    +"claystone edges. They were probably created long ago by "
    +"erosion. Some of them have spots of black mold that is probably "
    +"sustained by the present humidity.\n");
    
    add_cmd_item(  ({"plaque"}),"read","@@read_buylist");

    add_exit(WARLOCK_ROOMS_DIR + "hall01", "east");
    
    room_add_object(WARLOCK_OBJ_DIR + "iron_cauldron");
    
    add_npc(WARLOCK_GUILD_DIR + "npc/whispess", 1);

    reset_faerun_room();
}


/*
 * Function name: inn_hook_cant_pay()
 * String       : price of the item
 * Description  : What happens when you can't buy an item
 */
int inn_hook_cant_pay(int price)
{
    write("You haven't got enough money to pay for your order.\n");
    return 0;
}


/*
 * Function name: inn_hook_player_buys()
 * String       : price of the item
 * Description  : What happens when you buy an item
 */
int inn_hook_player_buys(int price)
{
    write("You pay "
    + price + " copper for the merchandize.\n");

    say(QCTNAME(this_player()) + " buys something "
    +"from the Whispess.\n");
    return 0;
}


/*
 * Function name: inn_hook_syntax_failure()
 * String       : words
 * Description  : Failure if you type the wrong syntax
 */
int inn_hook_syntax_failure(string str)
{
    write("What would you like to buy?\n");
    return 0;
}

/*
 * Function name: inn_hook_num_failure()
 * String       : number of items
 * Description  : Failure if you try to buy too much
 */
int inn_hook_num_failure(int num)
{
    write("You cannot buy more than one merchandize "
    +"at a time.\n");
    return 0;
}


/*
 * Function name: order()
 * String       : the item to purchase
 * Description  : Function to allowing buying of items.
 */
int order(string str)
{
    string *words;
    int num, tmp, i, price, item;
    object ob;

    if (!str)
    {
        return inn_hook_syntax_failure(str);
    }

    words = explode(str, " ");
    
    num = 1;
    
    if(sizeof(words) > 1)
    {
        
        tmp = LANG_NUMW(words[0]);
        if (!tmp)
            sscanf(words[0], "%d", tmp);
        
        if (tmp > 0)
        {
            num = tmp;
            str = implode(words[1 .. sizeof(words)], " ");
        }
    }

    if (num > 1)
    {
        return inn_hook_num_failure(num);
    }

    switch(str)
    {
        case "amulet":
        case "black amulet":
            ob = clone_object(cleaner_str);
            
            price = num * 8000;
            
            break;
            
        case "tote":
        case "leather tote":
            ob = clone_object(tote_str);
            
            price = num * 5000;
            
            break;
                       
        case "wing":
        case "fairy wing":
            ob = clone_object(wing_str);
            
            price = num * 4000;
            
            break;
                        
        case "blood":
        case "virgin's blood":
            ob = clone_object(blood_str);
            
            price = num * 3500;
            
            break;
            
         case "dust":
         case "vampire dust":
            ob = clone_object(dust_str);
            
            price = num * 4500;
            
            break;
            
        case "guano":
        case "bat guano":
            ob = clone_object(guano_str);
            
            price = num * 2500;
            
            break;
                       
        case "powder":
        case "bone powder":
            ob = clone_object(powder_str);
            
            price = num * 4000;
            
            break;
                        
        case "spleen":
        case "bat spleen":
            ob = clone_object(spleen_str);
            
            price = num * 3500;
            
            break;           
            
        case "sulphur":
        case "lump of sulphur":
            ob = clone_object(sulphur_str);
            
            price = num * 2500;
            
            break;
                        
        case "tear":
        case "tear of the innocent":
            ob = clone_object(tear_str);
            
            price = num * 3500;
            
            break;                      
 
        default:
            return inn_hook_syntax_failure(str);
    }
    
    if(!MONEY_ADD(this_player(),-price))
    {
        inn_hook_cant_pay(price);
        return 1;
    }
    
    inn_hook_player_buys(price);
    
    ob->set_heap_size(num);
    
    ob->move(this_player(), 1);

    return 1;
}


public void
init()
{
    init_skill_raise();
    init_guild_support();
    ::init();
    
    add_action(order, "buy");
}


void
set_up_skills()
{
    string to;

    to = "use air magic";
    sk_add_train(SS_ELEMENT_AIR,        ({ to, to }),  0,0, 50);

    to = "use water magic";
    sk_add_train(SS_ELEMENT_WATER,      ({ to, to }),  0,0, 50);

    to = "use earth magic";
    sk_add_train(SS_ELEMENT_EARTH,      ({ to, to }),  0,0, 50);

    to = "cast abjuration magic";
    sk_add_train(SS_FORM_ABJURATION,    ({ to, to }),  0,0, 50);

    to = "cast enchantment magic";
    sk_add_train(SS_FORM_ENCHANTMENT,    ({ to, to }),  0,0, 50);

     to = "cast conjuration magic";
    sk_add_train(SS_FORM_CONJURATION,    ({ to, to }),  0,0, 50);

     to = "cast transmutation magic";
    sk_add_train(SS_FORM_TRANSMUTATION,  ({ to, to }),  0,0, 50);

    to = "cast illusion magic";
    sk_add_train(SS_FORM_ILLUSION,      ({ to, to }),  0,0, 50);

    to = "cast divination magic";
    sk_add_train(SS_FORM_DIVINATION,    ({ to, to }),  0,0, 50);

    to = "find and locate herbs";
    sk_add_train(SS_HERBALISM,          ({ to, to }),  0,0, 60);

    to = "master spellcraft";
    sk_add_train(SS_SPELLCRAFT,         ({ to, to }), 0, 0, 60);
}


void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    this_player()->catch_msg("The old gruesome hag teaches you to " 
    + sk_tdesc[snum][0] +" better.\n");

    write("You achieve the rank of " + rank + ".\n");

    say("The old gruesome hag teaches "
    +QCTNAME(this_player()) + " to "
    +sk_tdesc[snum][1] + " better!\n");
}


int
sk_improve(string str)
{
    return ::sk_improve(str);
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


/*
 * Function name: gs_hook_start_meditate
 * Description  : This hook is called when player starts to meditate. You can
 *                mask this function to give a different message.
 */
void
gs_hook_start_meditate()
{
    write("You slip into a corner of the mold-infested cavity and "
    +"begins to meditate. While deep in thought, you realize you " 
    +"can <set> your different preferences, and when finished, you can " 
    +"<rise> from the floor.\n");
        
    say(QCTNAME(this_player()) + " slips into a corner of the mold-infested "
    +"cavity and starts meditating.\n");
}


/*
 * Function name: gs_hook_rise
 * Description  : This hook is called when player rises from the meditation.
 *                You can mask this function to give a different message.
 */
void
gs_hook_rise()
{
    write("A feeling of contentment washes over you as you mind returns " 
    +"to reality. You rise from the claystone floor.\n");
        
    say(QCTNAME(this_player()) + " rises from the floor.\n");
}


/*
 * Function name: gs_hook_catch_error
 * Description  : This hook is called when a player tried to do something 
 *                strange while meditating like examining things or leave 
 *                the room. You can mask this function to give a different 
 *                message.
 * Arguments    : string str - Argument the player tried to send to his 
 *                command.
 * Returns      : int 1 - normally.
 */
int
gs_hook_catch_error(string str)
{
    write("You are currently meditating, so it prevents you from "
    +"doing that. However, when you are done, you may <rise> from "
    +"the floor.\n");
    
    return 1;
}
