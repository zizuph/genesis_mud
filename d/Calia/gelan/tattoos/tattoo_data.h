#include "/d/Calia/domain.h"

static mapping tattoo_cover = ([
    "forehead":({({TS_HEAD}),"forehead"}),
    "lcheek":({({TS_HEAD}),"left cheek"}),
    "rcheek":({({TS_HEAD}),"right cheek"}),
    "face":({({TS_HEAD}),"face"}),
    "neck":({({TS_NECK}),"neck"}),
    "throat":({({TS_NECK}),"throat"}),
    "rbreast":({({TS_TORSO,TS_ROBE}),"right breast"}),
    "lbreast":({({TS_TORSO,TS_ROBE}),"left breast"}),
    "chest":({({TS_TORSO,TS_ROBE}),"chest"}),
    "stomach":({({TS_TORSO,TS_ROBE}),"stomach"}),
    "back":({({TS_TORSO,TS_ROBE}),"back"}),
    "rshoulder":({({TS_TORSO,TS_ROBE}),"right shoulder"}),
    "lshoulder":({({TS_TORSO,TS_ROBE}),"left shoulder"}),
    "rothigh":({({TS_LEGS,TS_ROBE}),"right outer thigh"}),
    "lothigh":({({TS_LEGS,TS_ROBE}),"left outer thigh"}),
    "rithigh":({({TS_LEGS,TS_TORSO}),"right inner thigh"}),
    "lithigh":({({TS_LEGS,TS_TORSO}),"left inner thigh"}),
    "rshin":({({TS_LEGS}),"right shin"}),
    "lshin":({({TS_LEGS}),"left shin"}),
    "lfoot":({({TS_LFOOT}),"left foot"}),
    "lankle":({({TS_LFOOT}),"left ankle"}),
    "rfoot":({({TS_RFOOT}),"right foot"}),
    "rankle":({({TS_RFOOT}),"right ankle"}),
    "rforearm":({({TS_RARM}),"right forearm"}),
    "rbicep":({({TS_RARM}),"right bicep"}),
    "lforearm":({({TS_RARM}),"left forearm"}),
    "lbicep":({({TS_LARM}),"left bicep"}),
    "lhand":({({TS_LHAND}),"left hand"}),
    "lwrist":({({TS_LHAND}),"left wrist"}),
    "rhand":({({TS_RHAND}),"right hand"}),
    "rwrist":({({TS_RHAND}),"right wrist"}),
    "lbuttock":({({TS_WAIST,TS_ROBE}),"left buttock"}),
    "rbuttock":({({TS_WAIST,TS_ROBE}),"right buttock"}),
    ]);


static string  *tattoo_adj = ({
    "agile", "amazing", "angmar", "ancient",
    "aquamarine", "arcane",
    "artful", "azure",
    "bare-chested", "battered", "beautiful", "black",
    "blazing", "bleeding", "bloody",
    "blue", "botched", "brass", "brave", 
    "bright", "broken",
    "bronze", "burning", "cadet", "calian", 
    "classy", "clever", "comical", "copper",
    "crazy", "crimson", "crooked", "crystal",
    "crystalline", "cute",
    "dainty", "dangerous", "dark",
    "dead", "deadly", "deceptive",
    "delicate", "demented", "demonic",
    "depressed", "detailed", "disintegrating",
    "distinguished", "disturbing", "dragonarmy", 
    "drooling", "drunken", "dunadan",
    "dwarven", "dying",
    "eerie", "elven", "emerald", "etched",
    "eternal", "exquisite",
    "faded", "faint", "female", "feminine", 
    "fiery", "five-headed",
    "flaming", "flattering", "four-headed", 
    "freehand",
    "giant", "gladiator", 
    "gleaming", "glimmering", "glistening", 
    "glowing", "gnome",
    "gnomish", "greedy", "green", 
    "gold", "golden", 
    "grey", "grim", "grinning", "grotesque", 
    "gypsy", "half-elf", "half-elven", "handsome", 
    "happy", "haunted", 
    "haunting", "hobbit", "honest", 
    "horrid", "huge", "human", 
    "illuminated", "impaled", "impressive", 
    "incorrigible", "indigo", "infected", 
    "intense", "intricate", "iron", "jaded", 
    "kahedan", "kender", "knightly", "krougish", 
    "large", "leathery-winged", "lethal", 
    "lonely", "macho",
    "mage", "magical", "male", "masculine",
    "mercenary", 
    "minotaur", "minstrel", "mirror-bright", 
    "mischievious", "misty", "mithril", 
    "monastic", "morbid", 
    "morgul", "multi-coloured", 
    "muscular", "musical", "mysterious", 
    "neidar", 
    "noble", "nude", "old", "onyx", 
    "orange", "orcish", "original", "ornate", 
    "outlined", "outstanding", "overflowing", 
    "partial", "pearl", "perfect", 
    "pink", "pirate", "platinum", 
    "pointy", "powerful", 
    "primitive", "professional", "proud", 
    "purple", "ranger", "red", 
    "rotting", "ruby", "ruined", "runed",
    "sad", "saddened", "sapphire", 
    "scantily-clad", "scarlet", "scarred", 
    "scripted", "seductive", "sexy", 
    "shaded", "shadowy", "sharp", "shattered", 
    "shimmering", "shining", "shiny", 
    "silver", "silvery",   
    "simple", "simplistic", "sleek", 
    "slender", "sly", "skeletal", "small", 
    "solamnic", "sophisticated", "soulless", 
    "steel", 
    "stretched", "subtle", "swirling", "swollen", 
    "tasteful", "tasteless", "terrifying", 
    "thanar", "three-headed", "tiny",
    "traveller", "tribal", "trollish", "twisted", 
    "two-headed", "undead", "unique", 
    "upside-down", "vampyr", "vengeful", 
    "violet", "voluptuous", 
    "vorpal", "wandering", "wealthy", "white",
    "wicked", 
    "wolfish", "worshipper", "yellow", "young",
    });

static string *sensitive_locations = ({
    "rbreast", "lbreast", "rithigh", "lithigh", "lbuttock", "rbuttock",
    });

static string adj1 = "adjective1";
static string adj2 = "adjective2";

/*
 * Because I need to be able to include 2 variables in these design
 * elements, I'm including the following patterns in the string so the
 * code will be able to find them and replace them with the proper 
 * adjectives.
 * ##LADJECTIVE1## -> LANG_ADDART(adj1)
 * ##LADJECTIVE2## -> LANG_ADDART(adj2)
 * ##ADJECTIVE1## -> adj1
 * ##ADJECTIVE2## -> adj2
 */
static string *tattoo_design = ({
/* 0*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## dragon ",
/* 1*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2##, four-pointed star ",
/* 2*/    "a tattoo of ##LADJECTIVE1## gargoyle crouched atop "+
              "##LADJECTIVE2## volcano ",
/* 3*/    "a tattoo of ##LADJECTIVE1## raven with ##ADJECTIVE2## "+
              "wings spread to the wind ",
/* 4*/    "a tattoo of ##LADJECTIVE1## skull with ##LADJECTIVE2##"+
              ", toothy grin ",
/* 5*/    "a tattoo of ##LADJECTIVE1## grim reaper, clutching "+
              "##LADJECTIVE2## scythe in a bony hand ",
/* 6*/    "a tattoo of ##LADJECTIVE1## warrior, surrounded by "+
              "##LADJECTIVE2## mist ",
/* 7*/    "a tattoo of ##LADJECTIVE1## spider spinning "+
              "##LADJECTIVE2## web ",
/* 8*/    "a tattoo of ##LADJECTIVE1## demon unfolding its "+
              "##ADJECTIVE2## wings ",
/* 9*/    "a tattoo of ##LADJECTIVE1## sword enshrouded within "+
              "##LADJECTIVE2## flame ",
/*10*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## eye ",
/*11*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## death's mask ",
/*12*/    "a tattoo of ##LADJECTIVE1## axe cleaving ##LADJECTIVE2##"+
              " skull ",
/*13*/    "a tattoo of ##LADJECTIVE1## axe smeared with "+
              "##ADJECTIVE2## blood ",
/*14*/    "##LADJECTIVE1## tattoo of two crossed ##ADJECTIVE2## axes ",
/*15*/    "a tattoo of ##LADJECTIVE1## dragon guarding ##LADJECTIVE2## arch ",
/*16*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## cross ",
/*17*/    "a tattoo of ##LADJECTIVE1## dragon flashing ##ADJECTIVE2##"+
              " claws ",
/*18*/    "a tattoo of ##LADJECTIVE1## tiger, jaws wide in a vicious "+
              "snarl, revealing ##ADJECTIVE2## fangs ",
/*19*/    "a tattoo of ##LADJECTIVE1## sword with ##LADJECTIVE2##"+
              " crown hung from its crossguard ",
/*20*/    "a tattoo of ##LADJECTIVE1## sword, its blade wrapped in "+
              "##LADJECTIVE2## vine of roses ",
/*21*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## wolf, silhouetted "+
              "howling atop a cliff against a full moon ",
/*22*/    "a tattoo of ##LADJECTIVE1## pack of wolves racing "+
              "through ##LADJECTIVE2## forest ",
/*23*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## wreath "+
              "of athelas ",
/*24*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## crescent moon ",
/*25*/    "a tattoo of ##LADJECTIVE1## satyr merrily playing "+
              "##LADJECTIVE2## lyre ",
/*26*/    "a tattoo of ##LADJECTIVE1## dolphin, leaping gracefully from "+
              "##ADJECTIVE2## waters ",
/*27*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## stein of ale ",
/*28*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## maiden ",
/*29*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## warrior ",
/*30*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## serpent, coiled "+
              "dangerously and ready to strike ",
/*31*/    "a tattoo of ##LADJECTIVE1## dragonlance, wrapped in "+
              "##LADJECTIVE2## vine of roses ",
/*32*/    "##LADJECTIVE1## tattoo of the legendary Huma, riding "+
              "proudly atop ##LADJECTIVE2## dragon, with the motto "+
              "`Est Sularus Oth Mithas' below ",
/*33*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## panther ",
/*34*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## silver haired "+
              "lynx, emerging from shadows ",
/*35*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## club, grasped "+
              "tightly in a boney, skeletal hand ",
/*36*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## sun, hanging "+
              "low above a mountain peak ",
/*37*/    "##LADJECTIVE1## tattoo of two ##ADJECTIVE2## dice, snake "+
              "eyes up ",
/*38*/    "a tattoo of ##LADJECTIVE1## teardrop falling into "+
              "##LADJECTIVE2## pool ",
/*39*/    "a tattoo of ##LADJECTIVE1## dagger piercing ##LADJECTIVE2##"+
              " rose ",
/*40*/    "a tattoo of two ##ADJECTIVE1## halberds, crossed beneath "+
              "a snarling ##ADJECTIVE2## wolf ",
/*41*/    "##LADJECTIVE1## tattoo of two crossed forearms, with fists "+
              "clenched and bearing tattoos of ##ADJECTIVE2## polearms ",
/*42*/    "a tattoo of ##LADJECTIVE1## crescent moon, with "+
              "##LADJECTIVE2## star suspended between the tips ",
/*43*/    "a tattoo of ##LADJECTIVE1##, beneath which is written "+
              "'##ADJECTIVE2##' in brilliant letters ",
/*44*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## rose ",
/*45*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## balance ",
/*46*/    "##LADJECTIVE1## devil with ##LADJECTIVE2## look in his eyes ",
/*47*/    "a tattoo of a savage goblin swinging around " +
              "##LADJECTIVE1## ##ADJECTIVE2## necklace while riding a " +
              "ferocious wolf ",
/*48*/    "a tattoo of two ##ADJECTIVE1## daggers crossed " +
              "under ##LADJECTIVE2## skull ",
/*49*/    "a tattoo of ##LADJECTIVE1## kingfisher flying among " +
              "a flight of ##ADJECTIVE2## dragons ",
/*50*/    "##LADJECTIVE1## tattoo of intricately woven " +
             "##ADJECTIVE2## thorns ",
/*51*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## skull covered " +
              "with spiders and worms ",
/*52*/    "##LADJECTIVE1## tattoo of a pentagram with " +
              "##LADJECTIVE2## skull in its center ",
/*53*/    "a tattoo of ##LADJECTIVE1## warrior holding " +
              "##LADJECTIVE2## skull in its hands ",
/*54*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## skull with two " +
              "swords crossed behind it ",
/*55*/    "##LADJECTIVE1## tattoo of three intertwining circles "+
              "surrounded by ##LADJECTIVE2## circle ", 
/*56*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## dragon ",
/*57*/    "a tattoo of ##LADJECTIVE1## protecing ##LADJECTIVE2## "+
              "elven maiden ",
/*58*/    "a tattoo of ##LADJECTIVE1## moon emanating ##LADJECTIVE2## "+
              "aura ",
/*59*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## Gnomish gizmo ",
/*60*/    "a tattoo of a black-robed human with ##ADJECTIVE1## "+
              "##ADJECTIVE2## eyes before the Black Tower ",
/*61*/    "a tattoo of ##LADJECTIVE1## warrior, slaying "+
              "##LADJECTIVE2## dragon ",
/*62*/    "##LADJECTIVE1## tattoo of ##LADJECTIVE2## phoenix rising "+
              "from the ashes ",
/*63*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## circle ",
/*64*/    "a tattoo of a grease covered ##ADJECTIVE1## with a "+
               "##ADJECTIVE2## hat and a smile ",
/*65*/    "a tattoo of ##LADJECTIVE1## ##ADJECTIVE2## water chalice ",
/*66*/    "##LADJECTIVE1## tattoo of five elemental symbols woven in "+
               "a circle, surrounding ##LADJECTIVE2## crest ",
           });

static mapping guild_tattoos = ([
    // Calians
    "Calians": ({CALIAN_GUILD_BASE_DIR+"specials/calian_cmdsoul",
        "noble", "grey", 21}),
    "Calians2": ({CALIAN_GUILD_BASE_DIR+"specials/calian_cmdsoul",
        "terrifying", "black", 22}),
    "Calians3": ({CALIAN_GUILD_BASE_DIR+"specials/calian_cmdsoul",
        "calian", "grey", 40}),
        
    // Spirit Circle
    "SpiritCircle": ({"/d/Calia/guilds/scop/specials/spiritsoul",
        "faint", "illuminated", 55}),
    "SpiritCircle": ({"/d/Calia/guilds/elementalists/souls/occ_cleric_soul",
        "faint", "illuminated", 55}),
        
    // Worshippers
    "Worshippers1": ({"/d/Calia/guilds/elementalists/souls/lay_worshipper_soul",
        "intricate", "arcane", 66}),
        
    // Knights 
    "Solamnians": ({"/d/Krynn/guilds/knights/souls/solamnian_soul",
        "silver", "delicate", 31}),
    "Solamnians2": ({"/d/Krynn/guilds/knights/souls/solamnian_soul",
        "solamnic", "silver", 32}), 
    "Solamnians3": ({"/d/Krynn/guilds/knights/souls/solamnian_soul",
        "blue", "silver", 49}),
        
    // Redfang
    "Redfang": ({"/d/Kalad/common/guilds/red_fang/commands/fang_soul",
        "bloody", "platinum", 47}),
        
    // ShadowWalkers
    "ShadowWalkers": ({"/d/Kalad/common/guilds/shadow_walkers/shadow_soul",
        "vorpal", "grinning", 48}),
        
    // DeathKnights
    "DeathKnights1": ({"/d/Kalad/common/guilds/khiraa/dk/commands/dk_soul",
        "grotesque", "grim", 54}),
    "DeathKnights2": ({"/d/Kalad/common/guilds/khiraa/dk/commands/dk_soul",
        "grotesque", "grim", 51}),
    "DeathKnights3": ({"/d/Kalad/common/guilds/khiraa/dk/commands/dk_soul",
        "eerie", "grim", 52}),
    "DeathKnights4": ({"/d/Kalad/common/guilds/khiraa/dk/commands/dk_soul",
        "skeletal", "grim", 53}),
        
    // LichPriests
    "LichPriests1": ({"/d/Kalad/common/guilds/khiraa/lp/commands/lp_soul",
        "grotesque", "grim", 54}),
    "LichPriests2": ({"/d/Kalad/common/guilds/khiraa/lp/commands/lp_soul",
        "grotesque", "grim", 51}),
    "LichPriests3": ({"/d/Kalad/common/guilds/khiraa/lp/commands/lp_soul",
        "eerie", "grim", 52}),
    "LichPriests4": ({"/d/Kalad/common/guilds/khiraa/lp/commands/lp_soul",
        "skeletal", "grim", 53}),
        
    // Morgul
    "Morgul1": ({"/d/Gondor/common/guild2/morgul_soul",
        "glowing", "red", 60}),
        
    // Inventors
    "Inventor1": ({"/d/Krynn/gnome/guild/obj/kgnome_soul",
        "gnome", "pointy", 64}),
       
    ]);
