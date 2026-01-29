/*
 *  /d/Shire/guild/smiths/rooms/forge_room.c
 *  
 *  The forge room of the Blacksmiths 
 *
 *  Code standards updated and general revision.
 *  Glaurung, August 98
 *
 *  9-Sep-99  Added windows and breeze, Kesor
 *  
 *  Added a large barrel that apprentices use to fill forging 
 *  barrels full of water with. Players may also drink from this 
 *  large barrel. Not taxed since it's available to all players.
 *  -- Finwe, November 2001
 */  

#pragma strict_types;


inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "/d/Shire/guild/smiths/smiths.h"
#include <formulas.h>
#include <money.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#define LIVE_I_BLACKENING "_live_i_blackening"
#define LEFT_FORGE "_Shire_live_i_left_forge"
#define IS_WEAPON(x) (function_exists("create_object", x) == "/std/weapon")
#define IS_ARMOUR(x) (function_exists("create_object", x) == "/std/armour")
#define FORGING "_live_o_forge_"
#define FORGE_NE          SMITHSDIR_ROOMS + "forge_ne"
#define FORGE_E           SMITHSDIR_ROOMS + "forge_e"
#define FORGE_FAR_E       SMITHSDIR_ROOMS + "forge_far_e"
#define FORGE_SE          SMITHSDIR_ROOMS + "forge_se"
#define FORGE_S           SMITHSDIR_ROOMS + "forge_s"



//** Global Variables **//
int breeze_time;

//** Prototypes **//
private int do_polish(string s);
private int do_melt(string str);
private void add_blackness(object o, int i);
private int do_blacken(string s);
private int do_enhance(string s);
private int do_bellow(string s);
private int do_mend(string s);
private int do_repair(string s);
private int do_sharpen(string s);
string do_check();

void do_breeze();
void remove_forge_alarms();

public void create_forge_room(){}

void 
create_well_room() 
{
}

public void
create_room() 
{
    set_short("The forge room of the Blacksmiths");
    set_long("This room is the pride of the Blacksmiths. This is where "+
        "the forges are placed and where the members of the guild most often "+
        "can be found. The room is very hot and a layer of soot covers "+
        "all items that have been here for more than a couple of days. "+
        "There are two new windows on the eastern wall. Most of "+
        "the time this room is very noisy, hammering sounds and loud "+ 
        "discussions being the most frequent cause. A large bellow "+
        "is located by the forge next to which tools can usually be "+
        "found. The tools can be used by all who have a mind to make "+
        "something useful, but be warned: an hour's work at the forges makes "+
        "you thirsty, hungry and tired.\n"+
        "A brass sign.\n");

    add_item(({"bellow"}), "It provides air for the forge. "+
        "You think you can make the forge hotter by pumping it.\n");
    add_item(({"fires"}),"They are used to melt metals in.\n");
    add_item(({"soot"}),"Black soot coming from the fires.\n");
    add_item(({"window","windows"}),"Two new windows are located on the eastern"+
        " wall to enable circulation of air in the room. A breeze comes through"+
        " them from time to time.\n");
    add_item(({"breeze"}),"A breeze sometimes comes from the windows.\n");
    add_item("sign", "It is a piece of brass, hammered thing " +
        "with some writing engraved on its surface. At the top " +
        "of the sign, it reads 'The Forge of Bree'.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    if (!objectp("set of forging tools")) 
        room_add_object("/d/Shire/guild/smiths/obj/tools", 1);

    if (!objectp("great forge")) 
        room_add_object(SMITHSDIR_OBJ+"forge_i", 1);

    // adds drinking
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    set_drink_from( ({ "large barrel", "water"}) );
    create_well_room();
    add_item(({"barrels", "many barrels"}),
        "The barrels are made of wood and used for forging. They " +
        "are all different sizes and all look well used. Most of " +
        "the barrels have dirty water in them from when smiths " +
        "plunge their items in to cool the metal. One large "+
        "barrel is full of clean water is used to replenish the " +
        "other barrels.\n");
    add_item("large barrel",
        "The large barrel is full of rainwater. It is used to " +
        "refresh and replenish the other barrels spread about " +
        "the forge that are used to cool hot metals. The water " +
        "in this barrel is so clean, it looks good enough to " +
        "drink.\n");
    add_item("barrel",
        "Which barrel did you want to look at?\n");

    set_room_tell_time(300);
    add_room_tell("Dark steam rises from the forge.");
    add_room_tell("Unbearable heat rolls off the forge.");

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_TELEPORT, 1);

    create_forge_room();
}

public void
init()
{
   ::init();
    init_drink();

    add_action(do_polish,  "smpolish");
    add_action(do_repair,  "smrepair");
    add_action(do_sharpen, "smsharpen");
    add_action(do_melt,    "smmelt");
    add_action(do_mend,    "smmend");
    add_action(do_blacken, "smblacken");
    add_action(do_enhance, "smedge");
    add_action(do_enhance, "smplate");
    add_action(do_bellow,  "smpump");
    add_action(do_check,   "smcheck");
}

private int
do_bellow(string s)
{
    object forge;

    if (!strlen(s))
        return 0;

    if (s != "bellow")
    {
        NF("Pump what? The bellow perhaps?\n");
        return 0;
    }

    if (TP->query_stat(SS_STR) < 100)
    {
        NF("You are too weak to do that.\n");
        return 0;
    }

    if (!objectp(forge = present("_great_smith_forge",TO)))
    {
        NF("Please contact a Shire wizard. The Smith's "+
            "forge seems to be missing.\n");
        return 0;
    }

    if (forge->query_prop(OBJ_I_BELLOW_USED))
    {
        NF("The forge is already blazing!\n");
        return 0;
    }

    forge->start_fire();
    return 1;
}

private int
do_enhance(string s)
{
    int     coinsNeeded,  // coins needed for the job
            index;        // which cointype in MONEY_TYPES
    string  metalType,    // type of coin being used
            verb = query_verb();  // are we 'edging' or 'plating'
    object  item,         // the item we wil work on
            shadow,       // shadow that will modify items appearance
           *obAr1,        // return array for parse_command
           *obAr2;        // return array for FIND_STR_IN_OBJECT

    if (!strlen(s))
        return 0;

    // what are we using? Find out both the item and the metal type 
    if (!parse_command(s, TP, "%i 'with' / 'in' %s", obAr1, metalType))
    {
        NF(CAP(verb)+" what with what type of metal?\n");
        return 0;
    }

    obAr1 = NORMAL_ACCESS(obAr1, 0, 0);
    if (sizeof(obAr1) > 1)
    {
        NF("You may only "+verb+" one item at a time.\n");
        return 0;
    }

    // ok we have the item we want   
    item = obAr1[0];
    if (!IS_WEAPON(item) && !IS_ARMOUR(item))
    {
        NF("You may only "+verb+" weapons and armour.\n");
        return 0;
    }

    // check if we forged this item
    if (item->query_forger() != TP->query_real_name())
    {
        NF("You can only modify things you forge.\n");
        return 0;
    }

    // has this item been modified already?
    if (strlen(item->query_prop(OBJ_S_MODIFIED_BY_SMITH)))
    {
        NF("You feel that altering the "+item->short()+
            " anymore may damage it beyond repair.\n");
        return 0;
    }

    // make sure we are using a legal metal type
    if ((index = member_array(metalType, MONEY_TYPES)) == -1)
    {
        NF("You must use a valid type of coin.\n");
        return 0;
    }

    // coin amount needed? plating something costs more than edging
    coinsNeeded = (item->query_prop(OBJ_I_VOLUME) /
        ((verb == "smedge") ? 200 : 50));

    // set a minimum amount needed no matter what we are doing
    coinsNeeded = MAX(10, coinsNeeded);

    // make sure we actually have the correct coins with us
    if (!sizeof(obAr2 = FIND_STR_IN_OBJECT(metalType+" coins", TP)))
    {
        NF("You have no " + metalType + " with you to use.\n");
        return 0;
    }

    // do we have enough of the proper coins?
    if (obAr2[0]->num_heap() < coinsNeeded)
    {
        NF("You feel you will need more " + metalType + " to do the job.\n"); 
        return 0;
    }

    // remove coins from player and shadow item with proper adjective
    obAr2[0]->set_heap_size(obAr2[0]->num_heap() - coinsNeeded);
    write("You enhance your "+item->short()+" with "+metalType+".\n");
    say(QCTNAME(TP)+" enhances "+HIS_HER(TP)+" "+item->short()+
        " with "+metalType+".\n");
    // increase the value of the item
    item->add_prop(OBJ_I_VALUE, item->query_prop(OBJ_I_VALUE) +
        coinsNeeded * ftoi(pow(12.0,itof(index))));
    MANAGER->modify_smith_item_desc(item, metalType+"-plated");  
    return 1;
}

public void
leave_inv(object obj, object to)
{
    object tools;


    if (tools = present("smiths_forging_tools", obj))
    {
        write("You drop the forging tools on the way out.\n");
        tell_room(TO, QCTNAME(obj)+" drops a "+tools->short()+".\n",obj);
        tools->move(TO);

    }

    if (TP->query_prop(LIVE_I_BLACKENING))
    {
        write("You remove your weapon from the forge.\n");
        TP->remove_prop(LIVE_I_BLACKENING);
    }
    ::leave_inv(obj, to);
}


private int
do_polish(string str) 
{
    object item,
          *to_polish;
    int    condition,
           repair;

    if (!strlen(str))
    {
        NF("Polish what?\n");
        return 0;
    }

    if (!IS_MEMBER(TP)) 
    {
        NF("Only a Smith may do that.\n");
        return 0;
    }


    if ((!parse_command(str, ENV(TP), "[the] %i", to_polish)) ||
        (!sizeof(to_polish = NORMAL_ACCESS(to_polish, 0, 0))))
    {
        NF("Polish what?\n");
        return 0;
    }

    if (sizeof(to_polish) != 1) 
    {
        NF("You may only polish one item at a time.\n");
        return 0;
    }

    item = to_polish[0];
    if (!IS_WEAPON(item))
    {
        NF("You may only polish weapons.\n");
        return 0;
    }    

    condition = item->query_corroded();
    repair = item->query_repair_corr();
    if (!(condition - repair)) 
    {
        NF("Luckily the item doesn't need polishing.\n");
        return 0;
    }

    if (!F_LEGAL_WEAPON_REPAIR_CORR(repair + 1, condition))
    {
        NF("Polishing can't help your "+item->short()+" anymore.\n");
        return 0;
    }

    while (F_LEGAL_WEAPON_REPAIR_CORR(repair + 1, condition))
        item->set_repair_corr(++repair);

    write("You carefully polish your "+item->short()+".\n");
    say(QCTNAME(TP)+" carefully polishes "+HIS_HER(TP)+" "+item->short()+".\n");
    return 1;
}

private int
do_repair(string str) 
{
    object item,
          *objArr;
    int    fatigue,
           repair,
           condition;

    if (!strlen(str))
    {
        NF("Repair what?\n");
        return 0;
    }

    if (!IS_MEMBER(TP)) 
    {
        NF("Only a member of the Blacksmiths may do that here.\n");
        return 0;
    }

    fatigue = TP->query_max_fatigue() / 4;
    if (TP->query_fatigue() < fatigue) 
    {
        NF("You are too tired to do that right now.\n");
        return 0;
    }

    TP->set_fatigue(TP->query_fatigue() - fatigue);
    if ((!parse_command(str, ENV(TP), "[the] %i", objArr)) ||
        (!sizeof(objArr = NORMAL_ACCESS(objArr, 0, 0))))
    {
        NF("Repair what?\n");
        return 0;
    }

    if (sizeof(objArr) != 1) 
    {
        NF("You may only repair one item at a time.\n");
        return 0;
    }

    item = objArr[0];
    if (!IS_ARMOUR(item))
    {
        NF("You may only repair armours.\n");
        return 0;
    }

    condition = item->query_condition();
    repair = item->query_repair();
    if (!(condition - repair))
    {
        NF("That does not need to be repaired.\n");
        return 0;
    }

    // with maxed forging failure rate is 10%
    if ((random(TP->query_skill(SS_FORGING))) < 5) //  
    {
        item->set_condition(condition + 1);        
        NF("Somehow you manage to make things worse! Go get some training.\n");
        return 0;
    }

    if (!F_LEGAL_ARMOUR_REPAIR(repair + 1, condition))
    {
        NF("You can't seem to repair your "+item->short()+" anymore.\n");
        return 0;
    }

    while (F_LEGAL_ARMOUR_REPAIR(repair + 1, condition))
        item->set_repair(++repair);

    write("You repair your "+item->short()+" as best you can.\n");
    say(QCTNAME(TP)+" repairs "+HIS_HER(TP)+" "+item->short()+".\n");
    TP->set_fatigue(TP->query_fatigue() - (TP->query_fatigue() / 3));
    return 1;
}

private int
do_sharpen(string str) 
{
    object item,
          *objArr;
   int condition,
           repair;

    if (!strlen(str))
    {
        NF("Sharpen what?\n");
        return 0;
    }

    if (!IS_MEMBER(TP)) 
    {
        NF("Only a member of the Blacksmiths may do that here.\n");
        return 0;
    }

    if ((!parse_command(str, ENV(TP), "[the] %i", objArr)) ||
        (!sizeof(objArr = NORMAL_ACCESS(objArr, 0, 0))))
    {
        NF("Sharpen what?\n");
        return 0;
    }

    if (sizeof(objArr) != 1) 
    {
        NF("You may only sharpen one item at a time.\n");
        return 0;
    }

    item = objArr[0];
    if (!IS_WEAPON(item))
    {
        NF("You may only sharpen weapons.\n");
        return 0;
    }

    condition = item->query_dull();
    repair = item->query_repair_dull();
    if (!(condition - repair))
    {
        NF("That does not need to be sharpened.\n");
        return 0;
    }

    // with maxed forging failure rate is 10%
    if ((random(TP->query_skill(SS_FORGING))) < 5) //  
    {
        item->set_dull(condition + 1);        
        NF("Somehow you manage to make things worse!\n");
        return 0;
    }

    if (!F_LEGAL_WEAPON_REPAIR_DULL(repair + 1, condition))
    {
        NF("You can't seem to sharpen your "+item->short()+" anymore.\n");
        return 0; 
    }

    while (F_LEGAL_WEAPON_REPAIR_DULL(repair + 1, condition))
        item->set_repair_dull(++repair);

    write("You sharpen your "+item->short()+" as best you can.\n");
    say(QCTNAME(TP)+" sharpens "+HIS_HER(TP)+" "+item->short()+".\n");
    return 1;
}

private int
do_mend(string str) 
{
    object item,
          *to_mend;
    int    fatigue;

    if (!strlen(str))
    {
        NF("Mend what?\n");
        return 0;
    }

    if (!IS_MEMBER(TP))
    {
        NF("Only a Smith may do that.\n");
        return 0;
    }

    fatigue=TP->query_max_fatigue()/4;
    if (TP->query_fatigue() < fatigue)
    {
        NF("You are too tired to mend anything right now.\n");
        return 0;
    }

    TP->set_fatigue(TP->query_fatigue() - fatigue);
    if ((!parse_command(str, ENV(TP), "[the] %i", to_mend)) ||
        (!sizeof(to_mend = NORMAL_ACCESS(to_mend, 0, 0)))) 
    {
        NF("Mend what?\n");    
        return 0;
    }

    if (sizeof(to_mend) != 1) 
    {
        NF("You may only mend one item at a time.\n");
        return 0;
    }

    item = to_mend[0];
    if (!IS_ARMOUR(item) && !IS_WEAPON(item))
    {
        NF("You can only mend weapons and armour.\n");
        return 0;
    }

    if (!item->query_prop(OBJ_I_BROKEN)) 
    {
        NF("Luckily this item isn't broken.\n");
        return 0;
    }

    if ((item->query_prop(OBJ_I_IS_MAGIC_WEAPON)) ||
        (item->query_prop(OBJ_I_IS_MAGIC_ARMOUR))) 
    {
        NF("You can't figure out how to mend this item.\n");
        return 0;
    }

    if (IS_WEAPON(item))
    {
        if (random(TP->query_skill(SS_MENDING_WEAPONS)) < 20)
        {
            write("After a while you determine you will "+
                "not be able to mend this weapon. You "+
                "decide to throw the useless item into "+
                "the forge.\n");
            tell_room(TO, QCTNAME(TP)+" throws something "+
                "into the forge.\n", TP);
            item->remove_object();
            return 1;
        }

        write("You manage to mend your broken weapon although "+
            "you doubt you could ever mend it again.\n");
    }

    else if (IS_ARMOUR(item))
    {
        if (random(TP->query_skill(SS_MENDING_ARMOURS)) < 20)
        {
            write("After a while you determine you will not be "+
                "able to mend this armour. You decide to throw "+
                "the useless item into the forge.\n");
            tell_room(TO, QCTNAME(TP)+" throws something into "+
                "the forge.\n", TP);
            item->remove_object();
            return 1;
        }

        write("You manage to mend your armour although you doubt "+
            "you could ever mend it again.\n");
    }

    else
    {
        NF("You can only mend weapons and armours.\n");
        return 0;
    }

    tell_room(TO, QCTNAME(TP)+" does some work at the forge.\n",TP);
    item->remove_prop(OBJ_I_BROKEN);
    TP->set_fatigue(TP->query_fatigue()-(TP->query_fatigue()/3));
    return 1;
}

private int
do_melt(string str) 
{
    object item,
          *to_melt;

    if (!strlen(str))
    {
        NF("Melt what?\n");
        return 0;
    }

    if (!IS_MEMBER(TP)) 
    {
        NF("You have no idea how to do that!\n");
        return 0;
    }

    if ((!parse_command(str, ENV(TP), "[the] %i", to_melt)) ||
        (!sizeof(to_melt = NORMAL_ACCESS(to_melt, 0, 0)))) 
    {
        NF("Melt what?\n");
        return 0;
    }

    if (sizeof(to_melt) != 1) 
    {
        NF("Please select only one item to melt.\n");
        return 0;
    }

    item = to_melt[0];

    if (!IS_ARMOUR(item) && !IS_WEAPON(item))
    {
        NF("You cannot really figure out how to melt down this item.\n");
        return 0;
    }

    if ((item->query_prop(OBJ_I_IS_MAGIC_WEAPON)) ||
        (item->query_prop(OBJ_I_IS_MAGIC_ARMOUR))) 
    {
        NF("You quickly realize you can't melt that.\n");
        return 0;
    }

    if (((item->query_hit() < 15) || (item->query_pen() < 15)) &&
        (IS_WEAPON(item))) 
    {
        write("You were unable to produce anything useful.\n");
        item->remove_object();
        return 1;
    }

    if (((item->query_ac()<15)) && (IS_ARMOUR(item))) 
    {
        write("You were unable to produce anything useful.\n");
        item->remove_object();
        return 1;
    }

    if (item->query_prop(OBJ_I_WEIGHT)<2000) 
    {
        write("There was not enough original material to produce anything useful.\n");
        item->remove_object();
        return 1;
    }

    write("You melt down the "+item->short()+".\n");
    say(QCTNAME(TP)+" melts down the "+item->short()+".\n");
    item->remove_object();
    item =  clone_object(SMITHSDIR_OBJ+"ir_bar");
    if (item->move(TP)) 
    {
        write("Since you cannot carry the iron bar you drop it on the floor.\n");
        item->move(ENV(TP));
    }

    return 1;
}

private int
do_blacken(string str)
{
    object obj, *obAr;
    string mod;

    if (!strlen(str) || !sizeof(obAr = FIND_STR_IN_OBJECT(str,TP)))
    {
        NF("Blacken what?\n");
        return 0;
    }

    if (sizeof(obAr) > 1)
    {
        NF("You may only blacken one thing.\n");
        return 0;
    }

    obj = obAr[0];  // this should be the only element anyway
    if (!IS_WEAPON(obj))
    {
        NF("You may only blacken weapons.\n");
        return 0;
    }

    if (strlen(mod = obj->query_prop(OBJ_S_MODIFIED_BY_SMITH)))
    {
        if (mod == "blackened")
        {
            NF("That has already been blackened!\n");
            return 0;
        }
         
        NF("You feel that altering this item anymore may damage it "+
            "beyond repair.\n");
        return 0;
    }

    if (ENV(obj)->query_real_name() != obj->query_forger())
    {
        NF("You can only blacken items you create.\n");
        return 0;
    }

    TP->add_prop(LIVE_I_BLACKENING, 1);
    write("You place your "+obj->short()+" into the hot forge.\n");
    tell_room(TO, QCTNAME(TP)+" places "+HIS_HER(TP)+
        " "+obj->short()+" into the hot furnace.\n", TP);
    set_alarm(itof(random(10)),0.0,&add_blackness(obj,0));
    return 1;
}

private void
add_blackness(object obj, int stage)
{
    object shadow;

    if (!TP->query_prop(LIVE_I_BLACKENING))
        return;

    if (TO != ENV(ENV(obj)))
    {
        if (TP->query_prop(LIVE_I_BLACKENING))
            TP->remove_prop(LIVE_I_BLACKENING);

        write("You must be holding the "+obj->short()+
            " if you want to do anything with it.\n");
        return;
    }

    switch (stage)
    {
        case 0:
            write("Your "+obj->short()+" starts to darken "+
                "as the flames of the furnace dance over it.\n");
            tell_room(TO, QCTNAME(TP)+"'s "+obj->short()+
                " darkens as the flames of the furnace dance "+
                "about it.\n", TP);
            set_alarm(itof(random(15)),0.0,&add_blackness(obj,++stage));
            break;

        case 1:
            write("You remove your "+obj->short()+
                " from the furnace.\n");
            tell_room(TO, QCTNAME(TP)+" removes "+HIS_HER(TP)+
                " "+obj->short()+" from the furnace.\n", TP);
            if ((TO == ENV(ENV(obj))) && (TP->query_prop(LIVE_I_BLACKENING)))
            {
                MANAGER->modify_smith_item_desc(obj, "blackened");
            }

            TP->remove_prop(LIVE_I_BLACKENING);
            break;

       default:
            write("Illegal index of "+stage+".\n");
            break;
    }
}

void
do_breeze()
{
    switch (random(3))
    {
    case 0:
        tell_room(TO,"You can feel a small breeze coming from the windows.\n");
        break;
    case 1:
        tell_room(TO,"A breeze washes your face and dries the sweat.\n");
        break;
    case 2:
        tell_room(TO,"You can hear a breeze enters through the windows, "+
        "it touches your face as it comes in to cool the environment.\n");
        break;
    }
}



string read_sign()
{
return "On the brass sign you see enscribed:\n\n" +

"      +--------------------------------------------------------------+\n"+
"      |  o   o                                                o   o  |\n"+
"      |    o                                                    o    |\n"+
"      |                                                              |\n"+
"      |                       The Forge of Bree                      |\n"+
"      |                     --======= 0 ========--                   |\n"+
"      |                                                              |\n"+
"      |   Forging weapons and armours successfully requires great    |\n"+
"      |   skill. It is also tiring work and takes much out of the    |\n"+
"      |   strongest person. Remember this as you will become quite   |\n"+
"      |   thirsty, hungry, and tired.                                |\n"+
"      |                                                              |\n"+
"      |   Skilled smiths may forge the following items.              |\n"+
"      |                                                              |\n"+
"      |                                                              |\n"+
"      |     General Equipment                                        |\n"+
"      |   =========================================================  |\n"+
"      |     - Horsehoes (set of four)                                |\n"+
"      |     - Megaphone                                              |\n"+
"      |                                                              |\n"+
"      |     Armours                  Weapons                         |\n"+
"      |   =========================================================  |\n"+
"      |     - Boots                  - Bastard Sword                 |\n"+
"      |     - Bracers                - Battle Axe                    |\n"+
"      |     - Platemail Bracers      - Claymore                      |\n"+
"      |     - Scalemail Bracers      - Dirk                          |\n"+
"      |     - Breastplate            - Halberd                       |\n"+
"      |     - Chainmail              - Iron Waraxe                   |\n"+
"      |     - Greaves                - Knife                         |\n"+
"      |     - Platemail Greaves      - Longsword                     |\n"+
"      |     - Scalemail Greaves      - Quarterstaff                  |\n"+
"      |     - Helm                   - Short Axe                     |\n"+
"      |     - Great Helm             - Shortsword                    |\n"+
"      |     - Plate Helm             - Spiked Club                   |\n"+
"      |     - Platemail              - Stiletto                      |\n"+
"      |     - Ribbed Platemail       - Warhammer                     |\n"+
"      |     - Ringmail                                               |\n"+
"      |     - Shield                                                 |\n"+
"      |     - Grand Tower Shield                                     |\n"+
"      |                                                              |\n"+
"      |   Visitors may assist Blacksmiths by pumping the bellows.    |\n"+
"      |   This is done by 'smpump bellow'.                           |\n"+
"      |                                                              |\n"+
"      |    o                                                   o     |\n"+
"      |  o   o                                               o   o   |\n"+
"      +--------------------------------------------------------------+\n\n";
}

void remove_forge_alarms()
{
    mixed *alarms = get_all_alarms();
    int    i, 
           alarm_id = 0,
           sz = sizeof(alarms);

    for (i = 0; i < sz; i++)
    {
        alarm_id = alarms[i][0];
        remove_alarm(alarm_id);
    }

    if (TP->query_prop(FORGING))
        TP->remove_prop(FORGING);
}



int check_forging()
{
    
    if(TP->query_prop(FORGING))
    {
	//remove_forge_alarms();
        write("You are in the middle of forging, and decide to wait until you're finished.\n");
        return 1;
    }
    return 0;
}

/*
 * Routine to check who is in forges
 */

string
do_check()
{
    object other_room;
    mixed opeople;

    // Only allow 'smcheck' in Shire forge rooms
    if (environment(TP)->query_prop("_forge_i_shire") != 1) {
         write("What?\n");
         return "";
    }

    write("                                Forge Occupants\n");
    write("======================================================"+
            "========================\n\n");

    // check forge_ne
    if (!LOAD_ERR(FORGE_NE))
        other_room = find_object(FORGE_NE);
    else
        write("\tNortheast Forge: The forge is hazy. There could be a problem with it. " +
            "Please contact a shire wizard or mail them.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\tNortheast Forge: Deserted and quiet.\n");
    else
        write("\tNortheast Forge: "+COMPOSITE_LIVE(opeople)+"\n");

 
 // check forge_e
    if (!LOAD_ERR(FORGE_E))
        other_room = find_object(FORGE_E);
    else
        write("\t     East Forge: The forge is hazy. There could be a problem with it. " +
            "Please contact a shire wizard or mail them.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\t     East Forge: Deserted and quiet.\n");
    else
        write("\t     East Forge: "+COMPOSITE_LIVE(opeople)+"\n");
 
 // check forge_far_e
    if (!LOAD_ERR(FORGE_FAR_E))
        other_room = find_object(FORGE_FAR_E);
    else
        write("     Further East Forge: The forge is hazy. There could be a problem with it. " +
            "Please contact a shire wizard or mail them.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("     Further East Forge: Deserted and quiet.\n");
    else
        write("     Further East Forge: "+COMPOSITE_LIVE(opeople)+"\n");

 // check forge_se
    if (!LOAD_ERR(FORGE_SE))
        other_room = find_object(FORGE_SE);
    else
        write("\tSoutheast Forge: The forge is hazy. There could be a problem with it. " +
            "Please contact a shire wizard or mail them.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\tSoutheast Forge: Deserted and quiet.\n");
    else
        write("\tSoutheast Forge: "+COMPOSITE_LIVE(opeople)+"\n");
 
 // check forge_s
    if (!LOAD_ERR(FORGE_S))
        other_room = find_object(FORGE_S);
    else
        write("\t    South Forge: The forge is hazy. There could be a problem with it. " +
            "Please contact a shire wizard or mail them.\n");
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        write("\t    South Forge: Deserted and quiet.\n");
    else
        write("\t    South Forge: "+COMPOSITE_LIVE(opeople)+"\n");

    write("\n======================================================"+
            "========================\n\n");

return "";
}


