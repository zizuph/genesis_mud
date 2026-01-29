/*
 *  /d/Shire/guild/smiths/npc/berim.c
 * 
 *  Berim oversees forging in the Smiths Guild.
 *
 *  General revision.
 *  Glaurung, August 98
 * 
 * Updated for new weapons and armours
 * Finwe, November 2001
 */  

inherit "/d/Shire/std/monster";
inherit "/std/act/chat";

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/smiths/smiths.h"

#define BO_NECKLACE SMITHSDIR_OBJ+"npc_neck"

void
create_shire_monster()
{
    object neck;

    if (!IS_CLONE)
        return;

    set_name(({"berim","guild_assistant"}));
    set_title("Assistant of the Smiths Guild");
    set_living_name("berim");
    set_race_name("human");
    set_adj(({"blue-eyed","long-bearded"}));
    set_long("This man watches over everything that goes on at " +
        "the forge. He is here in order to teach new apprentices " +
        "the art of forging and to assist as needed.\n");
    set_stats(({ 150, 100, 150, 120, 100, 100 })); 
    set_alignment(500);
    set_introduce(1); // function defined in ~Shire/std/monster 

    set_default_answer(QCTNAME(TO)+" tells you: Ehh.. what?\n");
    add_ask(({"bores","Bores"}), QCTNAME(TO)+" tells you: He is my"+
        " brother and the High Master of this guild.\n");
    add_ask(({"blue steel","grey alloy","galvorn","mithril"}), 
        QCTNAME(TO)+" tells you: That metal is very difficult to both"+
        " acquire and to forge items from.\n");
    add_ask(({"iron bar","copper bar","steel bar"}), QCTNAME(TO)+" tells"+
        " you: Yes, useful for forging purposes.\n");
    add_ask(({"forge"}),QCTNAME(TO)+" tells you: The forge is where you may create "+
        "fine weapons and armour. Ask me about either and I will tell you what "+
        "is possible to forge now.\n");
    add_ask(({"mend"}),QCTNAME(TO)+" tells you: Yes, you can mend broken items "+
        "here, as long as they're not magical in nature.\n");
    add_ask(({"melt"}),QCTNAME(TO)+" tells you: Yes, you can melt certain weapons "+
        "and armour here. If you melt enough you will be able to produce an iron "+
        "bar useful for forging new things.\n");
    add_ask(({"set","tools"}),QCTNAME(TO)+" tells you: You need to be holding them "+
        "in order to forge items.\n");
    add_ask(({"weapons","forging weapons"}),QCTNAME(TO)+" tells you: " +
        "Hmm, let me think...\n"+
        "You may attempt to forge a variety of common weapons. Read " +
        "the brass sign for more information. If you are interested " +
        "in finding out what materials you need in order to forge " +
        "each weapon just ask me about the weapon.\n"); 
    add_ask(({"armours","forging armours"}),QCTNAME(TO)+" tells you: " +
        "Hmm, let me think...\n"+
        "You may attempt to forge many common armours. If you are " +
        "interested in finding out what materials you need to forge " +
        "a certain item just ask me about the item.\n");

//General Equipment
    add_ask(({"horsehoes", "horseshoe"}), QCTNAME(TO)+" tells you: To forge a set of four horseshoes you will need an iron bar. When you become skilled enough at making them, horses and ponies won't become as fatigued when fitted with them.\n");

//weapons
    add_ask(({"tower shield", "grand tower shield"}), QCTNAME(TO)+" tells you: To forge a grand tower shield you will need an iron bar and some leather. This is a very fine shield!\n");
    add_ask(({"shield", "heater shield"}), QCTNAME(TO)+" tells you: To forge a shield you will need an iron bar and some leather.\n");
    add_ask("stiletto", QCTNAME(TO)+" tells you: Ah a fine little " +
        "weapon indeed! To forge this you will just need an iron bar.\n");
    add_ask(({"war hammer","warhammer"}),QCTNAME(TO)+" tells you: " +
        "Ah yes a weapon for the strong-armed. To forge this you " +
        "will need an iron bar, a piece of leather, and a piece of wood.\n");
    add_ask(({"battle axe","battleaxe"}),QCTNAME(TO)+" tells you: " +
        "The best idea ever to spring from the minds of dwarves! To " +
        "forge this you will need an iron bar, and a piece of leather.\n");
    add_ask(({"longsword","long sword"}),QCTNAME(TO)+" tells you: " +
        "The weapon of choice by many well respected warriors. To " +
        "forge this you will need an iron bar, and a piece of leather.\n");
    add_ask(({"shortsword","short sword"}),QCTNAME(TP)+" tells you: " +
        "This weapon seems to be getting more popular these days. " +
        "To forge this you will need an iron bar, and a piece of leather.\n");
    add_ask(({"halberd"}),QCTNAME(TO)+" tells you: Ah a good " +
        "long-range weapon, although it takes great skill to use. " +
        "To forge this you will need an iron bar, a piece of wood, " +
        "and a piece of leather.\n");
    add_ask("claymore",QCTNAME(TO)+" tells you: Now this is what " +
        "I call a warrior's weapon! To forge this you will need " +
        "an iron bar and a piece of leather.\n");
    add_ask("bastard sword",QCTNAME(TO)+" tells you: Bastard " +
        "swords are a unusual weapon. They have long handles " +
        "which make them easier to hold. But I've been told they " +
        "require two hands to wield. To forge it, you need iron "+
        "and leather.\n");
    add_ask("dirk",QCTNAME(TO)+" tells you: These nifty knives " +
        "are handy to have. I've been told they are popular with " +
        "cuthroats and thieves as they are easy to hide. If you " +
        "want to forge one, you will need leather and iron.\n");
    add_ask(({"quarterstaff","staffs", "staves", "quarterstaves"}),
        QCTNAME(TO)+" tells you: Oh, quarterstaves are a popular " +
        "weapon. They require special training to be used properly. " +
        "To make one requires only iron.\n");
    add_ask("spiked club",QCTNAME(TO)+" tells you: Spiked clubs " +
        "are a unique weapon. With an iron spiked bar attached to " +
        "the end of a pole, you can do alot of damage to your " +
        "enemies. They require wood, iron, and leather to make " +
        "one properly.\n");
    add_ask("iron  waraxe",QCTNAME(TO)+" tells you: The Iron Waraxe " +
        "axe gets its name from the dwarves who used them in their " +
        "wars. It's a two handed axe, but is powerful when skilled " +
        "Smiths forge them. It requires an iron bar and a piece of " +
        "leather.\n");
    add_ask("short axe",QCTNAME(TO)+" tells you: The short axe is " +
        "just that. An axe on a short handle. Unlike many axes, it " +
        "has a sharp point on the top, which is good for impaling " +
        "your enemies. It is also designed as a one handed axe. " +
        "Some like it because it's quick and efficent. It requires " +
        "iron and wood for the handle.\n");

// armours    
    add_ask(({"platemail","ribbed platemail"}),QCTNAME(TO)+" tells you: " +
        "A very durable armour if you are skilled enough to make " +
        "one. To forge this you will need an iron bar, and a " +
        "piece of leather.\n");
    add_ask(({"bracers","scalemail bracers", "platemail bracers"}),
        QCTNAME(TO)+" tells you: They will provide " +
        "you with adequate protection for your arms. To forge " +
        "this you will need an iron bar, and a piece of leather.\n");
    add_ask(({"greaves","scalemail greaves", "platemail greaves"}),
        QCTNAME(TO)+" tells you: They will provide " +
        "you with decent protection for your legs. To forge this " +
        "you will need an iron bar, and a piece of leather.\n");
    add_ask(({"helm", "great helm", "plate helm"}),QCTNAME(TO)+
        " tells you: Always wear head-gear! " +
        "It just may save your your life. To forge this you will " +
        "need an iron bar, and a piece of leather.\n");
    add_ask(({"chainmail","chainmail"}), QCTNAME(TO)+" tells you: "+
        "Ah a very pratical armour! A chainmail shirt will "+
        "protect your upper body and arms. To forge this you will "+
        "need an iron bar and piece of leather.\n");
    add_ask(({"ringmail","ringmail"}), QCTNAME(TO)+" tells you: "+
        "Hmm. I must say it is a reliable piece of armour and "+
        "very easy to make. It will protect your upper body and "+
        "arms if you make it correctly. To forge this you will "+
        "need an iron bar and piece of leather.\n");
    add_ask(({"boots","pair of boots"}), QCTNAME(TO)+" tells you: "+
        "One pair should last you quite some time. They aren't too "+
        "comfortable but they should protect your feet well enough. "+
        "To forge this you will need an iron bar and piece of leather.\n");
/*
    add_ask(({"gauntlets","pair of gauntlets"}), QCTNAME(TO)+
        " tells you: Oh yes, a tricky piece of armour to make with " +
        "all the fingers and everything...Gauntlets are necessary " +
        "to protect your hands during battle. They require some " +
        "expertise to get them to work just right. To forge a set, " +
        "you will need a piece of leather and an iron bar.\n");
*/
    add_ask("leather",QCTNAME(TO)+" tells you: Leather is used " +
        "for wrapping around the grip of a weapon, or for armour " +
        "straps, or for padding armours with. Leathers may be " +
        "purchased from Tobin.\n");
    add_ask(({"iron","iron bar","iron bars"}),QCTNAME(TO)+" tells " +
        "you: Ah the foundation of all the work we do here. Iron " +
        "bars can be purchased from Bores. You can also supply " +
        "yourself with iron bars by melting down old weapons or armour.\n");
    add_ask("wood",QCTNAME(TO)+" tells you: Wood is useful for " +
        "making the haft of long weapons. Tobin Ironshoe sells them.\n");
    add_ask(({"plating","plating weapons","plating armours"}),
            QCTNAME(TO)+" tells you: "+
        "Plating or edging an item decorates it beautifully. It " +
        "will also increase its value relative to what coin type " +
        "you use.\n");
    add_ask(({"blacken","blackening"}),QCTNAME(TO)+" tells you: " +
        "For a lusterless finish try and blacken your weapon.\n");
    add_ask(({"pump","bellow","pumping bellow"}),QCTNAME(TO)+" tells " +
        "you: Pump the bellow to quickly heat up the Great Forge. " +
        "Your work will proceed faster when the Forge is hotter.\n");
    add_ask(({"sharpening","sharpen","sharpen weapon"}), 
            QCTNAME(TO)+" tells you: Any smith can do that simple " +
            "task here. If you are away from the forge outdoors " +
            "and have a keen eye you should be able to find a stone " +
            "that you can sharpen your weapon with.\n");
    add_ask(({"repair","repairing","repair armour"}), QCTNAME(TO)+
        " tells you: Any smith can do that simple task here.\n");
    add_ask(({"polish","polishing","polish weapon"}), QCTNAME(TO)+
        " tells you: Any smith can do that simple task here.\n");

    set_chat_time(30);
    add_chat("A broken armour can often be mended.");
    add_chat("Melting down useless items is a quick way to get " +
        "raw materials.");
    add_chat("Pump the bellow to heat the Great Forge quickly. " +
        "Your work will go faster.");
    add_chat("All smiths can sharpen and polish weapons here.\n");
    add_chat("All smiths can repair their armour here.\n");
    add_chat("Have you tried to blacken your weapon?");
    add_chat("Have you tried to edge your weapon in silver?");
    add_chat("Have you tried to plate your weapon or armour in gold?");
    add_chat("Forging weapons successfully requires great skill.");
    
   neck = clone_object(BO_NECKLACE);
   neck->set_short("rough iron necklace");
   neck->set_adj("rough");
   neck->set_adj("iron");
   neck->move(this_object());
   command("wear necklace");
   add_prop(LIVE_I_ALWAYSKNOWN, 1);

}
