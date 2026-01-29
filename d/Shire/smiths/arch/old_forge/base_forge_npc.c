/*
 *  Smiths Guild NPC in Rivendell.
 *  Based on /d/Shire/smiths/npc/berim.c
 * 
 *  Finwe, January 2001
 */  

inherit "/d/Shire/std/monster";
inherit "/std/act/chat";

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/smiths/smiths.h"
#include "forge.h"

//string tanner_name = FORGE_TANNER_NAME;

void
create_shire_monster()
{
    if (!IS_CLONE)
        return;


    set_name(FORGE_NPC_NAME);
//    add_name(({"butterbur","innkeeper"}));
    add_name(FORGE_NPC_RACE);
    set_living_name(FORGE_NPC_NAME);
//    set_title(FORGE_NPC_TITLE);
    set_race_name(FORGE_NPC_RACE); 
    set_adj(FORGE_NPC_ADJ1);
    add_adj(FORGE_NPC_ADJ2);
    set_long("This is the long descr of the Forge npc\n");
    set_introduce(1); // function defined in ~Shire/std/monster 

    set_default_answer(QCTNAME(TO)+" tells you: I do not understand you.\n");
    add_ask(({"necklace", "iron necklace"}), 
        QCTNAME(TO)+" tells you: The iron necklace is the guild " +
        "item of the Smiths Guild. One can be obtained in Bree " +
        "at the Smiths guildhouse.");
    add_ask(({"smiths guild", "smith's guid"}), 
        QCTNAME(TO)+" tells you: The Smiths Guild is\n");
    add_ask(({"berim"}), 
        QCTNAME(TO)+" tells you: He is the High Master of the " +
        "Smiths Guild in Bree.\n");
    add_ask(({"joining"}),
        QCTNAME(TO)+" tells you: To join the Smiths Guild, you " +
        "will need to travel to the guildhouse in Bree.\n");
    add_ask(({"blue steel","grey alloy","galvorn","mithril"}), 
        QCTNAME(TO)+" tells you: That metal is very difficult to both"+
        " acquire and to forge items from.\n");
    add_ask(({"iron bar","copper bar","steel bar"}), 
        QCTNAME(TO)+" tells you: They are needed if you wish f" +
        "forge items.\n");
    add_ask(({"forge"}),
        QCTNAME(TO)+" tells you: Here, if you are skilled in " +
        "the craft of smithing, you may create fine weapons and " +
        "armour. Ask me about either and I will tell you what " +
        "is possible to forge now.\n");
    add_ask(({"mend"}),
        QCTNAME(TO)+" tells you: Skilled smiths may mend broken " +
        "items here, as long as they're not magical in nature.\n");
    add_ask(({"melt"}),
        QCTNAME(TO)+" tells you: You may melt certain weapons " +
        "and armour here. If you melt enough you will be able " +
        "to produce an iron bar useful for forging new things.\n");
    add_ask(({"set","tools"}),
        QCTNAME(TO)+" tells you: You need to be holding them "+
        "in order to forge items.\n");
    add_ask(({"weapons","forging weapons"}),
        QCTNAME(TO)+" tells you: Hmm, let me think...\n"+
        "You may attempt to forge a stiletto, a warhammer, a " +
        "battle axe, a longsword, a shortsword, a halberd, or a " +
        "claymore. If you are interested in finding out what " +
        "materials you need inorder to forge each weapon just " +
        "ask me about the weapon.\n"); 
    add_ask(({"armours","forging armours"}),
        QCTNAME(TO)+" tells you: Hmm, let me think...\n"+
        "You may attempt to forge platemail, chainmail, ringmail, "+
        "bracers, greaves, a helm, or boots. If you are interested in "+
        "finding out what materials you need to forge a certain "+
        "item just ask me about the item.\n");
// weapons 
    add_ask("stiletto", 
        QCTNAME(TO)+" tells you: Ah, a fine little weapon " +
        "indeed! To forge this you will just need an iron bar.\n");
    add_ask(({"war hammer","warhammer"}),
        QCTNAME(TO)+" tells you: Ah yes,  a weapon for the " +
        "strong-armed. To forge this you will need an iron bar, " +
        "a piece of leather, and a piece of wood.\n");
    add_ask(({"battle axe","battleaxe"}),
        QCTNAME(TO)+" tells you: The weapon of choice among " +
        "dwarves! To forge this you will need an iron bar and " +
        "a piece of leather.\n");
    add_ask(({"longsword","long sword"}),
        QCTNAME(TO)+" tells you: The weapon of choice by many " +
        "warriors. To forge this you will need an iron bar, and "+
        "a piece of leather.\n");
    add_ask(({"shortsword","short sword"}),
        QCTNAME(TP)+" tells you: This weapon seems to " +
        "be getting more popular these days. To forge this you " +
        "will need an iron bar and a piece of leather.\n");
    add_ask(({"halberd"}),
        QCTNAME(TO)+" tells you: Ah, a good long-range weapon, " +
        "although it takes great skill to use. To forge this " +
        "you will need an iron bar, a piece of wood, and a " +
        "piece of leather.\n");
    add_ask("claymore",
        QCTNAME(TO)+" tells you: Now this is what I call a " +
        "warrior's weapon! To forge this you will need an iron " +
        "bar and a piece of leather.\n");

// armours
    add_ask(({"platemail","plate mail"}),
        QCTNAME(TO)+" tells you: A very durable armour "+
        "if you are skilled enough to make one. To forge this " +
        "you will need an iron bar and a piece of leather.\n");
    add_ask("bracers",
        QCTNAME(TO)+" tells you: They will provide you with " +
        "adequate protection for your arms. To forge this you " +
        "will need an iron bar.\n");
    add_ask("greaves",
        QCTNAME(TO)+" tells you: They will provide you with " +
        "decent protection for your legs. To forge this you " +
        "will need an iron bar, and a piece of leather.\n");
    add_ask("helm",
        QCTNAME(TO)+" tells you: Always wear head-gear! It just " +
        "may save your your life. To forge this you will need " +
        "an iron bar and a piece of leather.\n");
    add_ask(({"chainmail","chain mail"}),
        QCTNAME(TO)+" tells you: Ah a very pratical armour! A " +
        "chainmail shirt will protect your upper body and arms. " +
        "To forge this you will need an iron bar and piece of " +
        "leather.\n");
    add_ask(({"ringmail","ring mail"}),
        QCTNAME(TO)+" tells you: This is a reliable piece of " +
        "armour and very easy to make. It will protect your " +
        "upper body and arms if you make it correctly. To forge " +
        "this you will need an iron bar and piece of leather.\n");
    add_ask(({"boots","pair of boots"}), 
        QCTNAME(TO)+" tells you: One pair should last you quite " +
        "some time. They aren't too comfortable but they should " +
        "protect your feet well enough. To forge this you will " +
        "need an iron bar and piece of leather.\n");

// Items and misc commands
    add_ask("leather",
        QCTNAME(TO)+" tells you: Leather is used for wrapping " +
        "around the grip of a weapon, for armour straps, or for " +
        "padding armours with. You can make leather from the " +
        "hide or skin of certain animals.\n");
    add_ask(({"iron","iron bar","iron bars"}),
        QCTNAME(TO)+" tells you: Ah the foundation of all the " +
        "work we do here. Iron bars can be purchased or you can " +
        "supply yourself with iron bars by melting down old " +
        "weapons or armour.\n");
    add_ask("wood",
        QCTNAME(TO)+" tells you: Wood is useful for making the " +
        "haft of long weapons.\n");
    add_ask(({"plating","plating weapons","plating armours"}),
        QCTNAME(TO)+" tells you: Plating or edging an item " +
        "decorates it beautifully. It will also increase its " +
        "value relative to what coin type you use.\n");
    add_ask(({"blacken","blackening"}),
        QCTNAME(TO)+" tells you: For a lusterless finish try " +
        "and blacken your weapon.\n");
    add_ask(({"pump","bellow","pumping bellow"}),
        QCTNAME(TO)+" tells you: Pump the bellow to quickly " +
        "heat up the Great Forge. Your work will proceed faster "+
        "when the Forge is hotter.\n");
    add_ask(({"sharpening","sharpen","sharpen weapon"}), 
        QCTNAME(TO)+" tells you: Any smith can do that simple " +
        "task here. If you are away from the forge outdoors and " +
        "have a keen eye you should be able to find a stone " +
        "that you can sharpen your weapon with.\n");
    add_ask(({"repair","repairing","repair armour"}), 
        QCTNAME(TO)+" tells you: Any smith can do that simple " +
        "task here.\n");
    add_ask(({"polish","polishing","polish weapon"}), 
        QCTNAME(TO)+" tells you: Any smith can do that simple " +
        "task here.\n");

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
    
    // function defined in ~Shire/std/monster
    add_equipment("/d/Shire/smiths/necklace"); 
}
