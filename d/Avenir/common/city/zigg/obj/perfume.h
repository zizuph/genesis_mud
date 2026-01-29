/*
 * - pefume.h
 *
 * File to hold all defines related to perfumes, their bottles,
 * construction, manufacture and scents.
 *
 * Reference for Scents:
 *
 *     http://www.scentit.com/descriptions.html
 *     http://www.aromaweb.com/essentialoils/default.asp
 *     http://www.absolute-aromas.com/R/mainessentialoils.htm
 *
 * Reference for Bottles:
 *
 *     http://www.museudelperfum.com/
 *     http://www.passionforperfume.com/
 *     http://www.perfumebottles.org/home.cfm
 *     http://www.antiquetalk.com/bottles1.htm
 *     http://www.bottlebooks.com/Dating%20Old%20Bottles/determining_the_age_of_cologne_b.htm
 *     http://www.neroliane.eu/neroliane-guide-glossaire.php
 */
#ifndef __PERFUME_H__
#define __PERFUME_H__

#include "zigg.h"

/*
 * Location of the perfume shadow and emote object.
 */
#define PERFUME_BOTTLE  (ZIG_OBJ + "perf_bottle")
#define PERFUME_EMOTES  (ZIG_OBJ + "perf_emotes")
#define PERFUME_SHADOW  (ZIG_OBJ + "perf_shadow")

/*
 * Perfumes:
 *
 * (mixed)Mapping ([
 *  (string)Name : (mixed *)({ (string)Scent,
 *                             (string)Visual,
 *                             (string *)({ (string)Aspects, ... }),
 *                             (string *)({ (string)Components, ... }),
 *                             (int)Cologne as well?,
 *                             (int)Commission only?,
 *                             (int)Cost (in gold),
 *                           }),
 *                 ])
 */
#ifndef NO_PERFUMES
private static mapping perfumes = ([    
    "almond" : ({ "warm, nutty, slightly bitter",
        "light brown liquid",
        ({ "anchoring", "fortifying", "appealing"}),
        ({ "almond" }),
        1, 0, 10 }),
    "amber" : ({ "seductive, resinous yet subtley sweet, masculine",
        "amber oil",
        ({ "sensual", "captivating", "soothing" }),
        ({ "amber" }),
        1, 1, 10 }),         
    "apple" : ({ "sweet, mouthwatering, ripe apple",
        "amber green liquid",
        ({ "enticing", "appetizing" }),
        ({ "apple" }),
        0, 1, 10 }),
    "autumn leaves" : ({ "fresh, earthy and woodsy",
        "amber colored liquid",
        ({ "calming", "relaxing" }),
        ({ "autumn leaves" }),
        1, 0, 10 }),                
    "bay rum" : ({ "spicy, sharp, earthy",
        "grey green liquid",
        ({ "charming"}),
        ({ "bay rum" }),
        1, 0, 10 }),         
    "cedarwood" : ({ "pleasant, masculine, dry woodsy",
        "yellowish orange liquid",
        ({ "grounding", "relaxing", }),
        ({ "white cedar" }),
        1, 1, 10 }),   
    "cinnamon" : ({ "warm, spicy and sweet",
        "red tinged liquid",
        ({ "warming", "exciting", }),
        ({ "cinnamon" }),
        0, 1, 10 }),        
    "cloves" : ({ "peppery, woody",
        "clear liquid",
        ({ "energizing", "invigorating", }),
        ({ "clove" }),
        1, 1, 10 }),         
    "dragonflower" : ({ "subtle but rather foul",
        "deep pink liquid",
        ({ "irritating" }),
        ({ "dragonflower" }),
        1, 0, 10 }),
    "fish" : ({ "salty, stinky fish",
        "green tinged, grey liquid",
        ({ "stomach-turning", "reeking", }),
        ({ "fish" }),
        1, 1, 10 }),        
    "fresh water" : ({ "cool, clean and crisp",
        "faintly blue liquid",
        ({ "mysterious", "purifying", "restoring", "calming"}),
        ({ "fresh water" }),
        1, 0, 10 }),        
    "gardenia" : ({ "delicately fragrant, exotically floral",
        "green tinged, clear liquid",
        ({ "mood-lifting", "sensual", "purifying", }),
        ({ "gardenia" }),
        0, 0, 10 }), 
    "grapefruit" : ({ "fresh, warm yet faintly sweet, citrus",
        "light gold liquid",
        ({ "invigorating", "energizing", "cheering", "refreshing" }),
        ({ "grapefruit" }), 
        1, 0, 10 }),                      
    "honeysuckle" : ({ "potent, sweet nectar",
        "lightweight, colorless liquid",
        ({ "restoring", "mood-lifting" }),
        ({ "honeysuckle" }),
        0, 1, 10 }),
    "honey" : ({ "soft, warm and sweet",
        "pure gold oil",
        ({ "tantalizing", "alluring", "disarming" }),
        ({ "honey" }),
        0, 1, 10 }),        
    "heliotrope" : ({ "distinctive floral and cherry-vanilla",
        "pale purple oil",
        ({ "enticing", "appetizing", "cheering" }),
        ({ "heliotrope" }),
        0, 1, 10 }),
    "jasmine" : ({ "warm, floral and exotic",
        "golden tinged, deep brown liquid",
        ({ "calming", "relaxing", "soothing" }),
        ({ "jasmine" }),
        0, 0, 10 }),
    "leather" : ({ "arid, heady, sharp, leathery",
        "light brown oil",
        ({ "refreshing", "arousing", "sensual", }),
        ({ "leather" }),
        1, 1, 10 }),        
    "lilac" : ({ "heady, sweetly floral",
        "pink tinged, clear liquid",
        ({ "soothing", "calming", "sensual", }),
        ({ "lilac" }),
        0, 1, 10 }),
    "lily" : ({ "fresh, clean, soapy",
        "clear liquid",
        ({ "cleansing", "invigorating", "refreshing", }),
        ({ "lily" }),
        1, 1, 10 }),        
    "lime" : ({ "refreshingly bitter, sharp, citrus",
        "bright green liquid",
        ({ "soothing", "calming", "sensual", }),
        ({ "lime" }),
        1, 1, 10 }),        
    "marjoram" : ({ "rustic, hay-like, aromatic",
        "pale golden liquid",
        ({ "soothing", "fortifying", "relaxing" }),
        ({ "marjoram" }),
        1, 1, 10 }),         
    "marigold" : ({ "pleasingly musky, pungent",
        "dark orange oil",
        ({ "arousing", "warming", "relaxing" }),
        ({ "marigold" }),
        1, 1, 10 }),        
    "myrrh" : ({ "sweet, smokey, spicy and somewhat musky",
        "pale yellow liquid",
        ({ "centering", "warming", "meditative" }),
        ({ "bergamot" }),
        1, 1, 10 }),        
    "oakmoss" : ({ "warm, earthy and masculine",
        "golden tinged, brown liquid",
        ({ "calming", "sensual", "soothing", "relaxing" }),
        ({ "oakmoss" }),
        1, 1, 10 }),
    "ocean breeze" : ({ "fresh, cool, faintly salty",
        "blue tinged, clear liquid",
        ({ "stimulating", "refreshing" }),
        ({ "ocean breeze" }),
        1, 0, 10 }),   
    "passionflower" : ({ "intoxicatingly sweet, tropical",
        "golden liquid",
        ({ "intoxicating", "inspiring", "enticing", "romantic" }),
        ({ "passionflower" }),
        0, 1, 10 }),        
    "patchouli" : ({ "strongly musky and earthy, masculine",
        "dark golden liquid",
        ({ "sensual", "romantic", "soothing" }),
        ({ "patchouli" }),
        1, 0, 10 }),   
    "peach" : ({ "fruity, warm, ripe peach",
        "pink tinged golden liquid",
        ({ "lushous", "delicious", "subtle" }),
        ({ "peach" }),
        0, 1, 10 }),                
    "pine" : ({ "cool, resinous and faintly smokey",
        "green tinged golden liquid",
        ({ "stimulating", "refreshing" }),
        ({ "pine" }),
        1, 0, 10 }),                    
    "rose" : ({ "feminine, sweet, heavy floral",
        "light golden liquid",
        ({ "romantic", "sensual", "uplifting" }),
        ({ "rose" }),
        0, 1, 10 }),   
    "sandalwood" : ({ "sweetly fragrant yet delicate spicy-wood",
        "amber tinged, pale yellow liquid",
        ({ "relaxing", "warming", }),
        ({ "sandalwood" }),
        1, 0, 10 }),
    "skullcap" : ({ "putrid, decaying, death-like",
        "black, syrupy looking liquid",
        ({ "nauseating" }),
        ({ "skullcap" }),
        1, 1, 10 }),
    "spice" : ({ "warm, piquant and vaguely sweet",
        "dark golden liquid",
        ({ "energizing", "enticing", "stimulating", "arousing"}),
        ({ "spice" }),
        1, 0, 10 }),   
    "sweet grass" : ({ "fresh, clean, grassy",
        "green tinged, golden liquid",
        ({ "uplifting", "energizing", "cheering", "refreshing" }),
        ({ "sweet grass" }),
        1, 0, 10 }),             
    "sweetpea" : ({ "extremely sweet, subtley spicy",
        "clear oil",
        ({ "cheering", "energizing", }),
        ({ "sweetpea" }),
        0, 1, 10 }),
    "tiger lily" : ({ "mysterious, sensual floral",
        "deep orange liquid",
        ({ "romantic", "relaxing", "cleansing", }),
        ({ "tiger lily" }),
        0, 1, 10 }),         
    "tuberose" : ({ "wonderfully rich, sultry, floral",
        "lighweight milky liquid",
        ({ "captivating", "refreshing", "bewitching", "romantic"}),
        ({ "tuberose" }),
        0, 1, 10 }),        
    "vanilla" : ({ "soft, rich and creamy, sweet",
        "pale golden liquid",
        ({ "consoling", "soothing", "calming" }),
        ({ "vanilla" }),
        1, 0, 10 }),
    "vetiver" : ({ "complex, woody, earthy and subtley smokey",
        "dark golden liquid",
        ({ "enticing", "captivating", "intriguing" }),
        ({ "vetiver" }),
        1, 0, 10 }),        
    "wintergreen" : ({ "cool, clean and minty sweet",
        "clear liquid",
        ({ "centering", "warming", "meditative" }),
        ({ "wintergreen leaf" }),
        1, 1, 10 }),
]);
#endif

/*
 * Indices for perfumes mapping.
 */
#define SCENT      0
#define PDESC      1
#define AROMA      2
#define COMPONENT  3
#define PCOLOGNE   4
#define PSPECIAL   5
#define PCOST      6

/*
 * Bottles:
 *
 * (mixed)Mapping ([
 *  (string)Name : (mixed *)({ (string)Short,
 *                             (string)Long,
 *                             (string *)({ (string)Names, ... }),
 *                             (string)Material,
 *                             (mapping)([ Designs, ... ]),
 *                             (int)Max uses,
 *                             (int)For colognes?,
 *                             (int)Cost (in gold),
 *                           }),
 *                 ])
 * Notes:
 *
 *   * Bottles always have the name "bottle".
 *   * Bottles have a limit of 4 replaceable elements.
 */
#ifndef NO_BOTTLES
private static mapping bottles = ([
    "delft" : ({ "silver-topped blue and white delft",
        "A silver-topped blue and white decorated bottle.",
        ({ "delft", }),
        ({"blue", "white", "silver-topped",}),
        ([ ]),
        20, 0, 10 }),
    "ivory" : ({ "silver-lidded ivory bottle",
        "An ivory bottle in the shape of an arm and hand with "+
        "florid carvings and crowned with a silver lid.",
        ({ }),
        ({"ivory","silver-lidded",}),
        ([ ]),
        15, 1, 10 }),
    "tear" : ({ "clear crystal tear-shaped bottle",
        "A clear crystal bottle shaped like a tear-drop "+
        "with a long, elegant silver neck and spherical crystal stopper. ",
        ({ }),
        ({"clear","crystal","tear-shaped",}),
        ([ ]),
        20, 1, 10 }),
    "cone" : ({ "beautifully colored conical glass bottle",
        "A tall glass bottle shaped like cone with a wide round "+
        "base tapering to the engraved silver top. The neck of the "+
        "bottle is a %s that fades as the bottle "+
        "flares, becoming a %s.",
        ({ }),
        ({"glass","conical","colored",}),
        ([ "blue"   : ({"deep sapphire blue", "pale blue"}),
       "green"  : ({"dark emerald green", "light green"}),
       "red"    : ({"dark ruby red", "faint pink"}),
       "black"  : ({"abysmal black", "smokey grey"}),
       "purple" : ({"royal purple", "faint lavender"}),
       "orange" : ({"cheerful orange", "sunny yellow"}),
     ]),
        25, 1, 10 }),
    "fruit" : ({ "luminous fruit-shaped bottle",
        "A small bottle made of layered, blown glass and shaped "+
        "like %s. The inside layer of glass is a %s "+
        "while the clear outside layer captures the light making "+
        "the bottle seem to almost have its own luminance. %s and the short, "+
        "green stopper resembles a stem.",
        ({ }),
        ({"luminous","fruit",}),
        ([ "strawberry" : ({"a strawberry", "deep rosy red",
        "Tiny bubbles within the clear glass imitate strawberry seeds"}),
       "orange" : ({"an orange", "warm, bright orange",
        "A delicate glass leaf adorns the top"}),
       "grapes" : ({"a bunch of grapes", "rich, red-violet",
        "Many round chambers form the grapes"}),
         ]),
        20, 1, 10 }),
    "jade" : ({ "gilded rectangular jade bottle",
        "A tall rectagular bottle carved out of green jade with %s "+
        "lightly carved across the front. Tiny gold painted "+
        "%s, matching the elegant gold lid which tops the bottle.",
        ({ }),
        ({"gilded","rectangular","jade",}),
        ([ "tree"   : ({"tree branches", "leaves cling to the branches"}),
       "water"  : ({"a water scene", "reeds poke out of the water"}),
       "flower" : ({ "large, cheerful sunflowers",
        "petals decorate each flower"}),
     ]),
        25, 1, 10 }),
    "oliphant" : ({ "carved ivory bottle",
        "This bottle has been carefully carved from a single piece of "+
        "ivory to resemble an oliphant. The work is exquisite with "+
        "careful attention paid to every detail even the delicate ears "+
        "and tail. The oliphant seems to hold a small cork up to you with "+
        "its long trunk which cleverly disguises the bottle's spout.",
        ({ }),
        ({"carved","ivory","oliphant",}),
        ([ ]),
        10, 1, 10 }),
    "flask" : ({ "small jeweled silver flask",
        "It is a small, flask made of silver and engraved with "+
        "ornate patterns. The centerpiece is an engraving of dragon, "+
        "its tiny scales each carefully set with %s jewel chip that "+
        "sparkles brilliantly in the light.",
        ({"flask",}),
        ({"small","jeweled","silver",}),
        ([ "ruby"     : ({ "a ruby" }),
       "sapphire" : ({ "a sapphire" }),
       "onyx"     : ({ "an onyx" }),
       "emerald"  : ({ "an emerald" }),
       "diamond"  : ({ "a diamond" }),
     ]),
        25, 1, 10 }),
    "cylinder" : ({ "painted cylindrical glass bottle",
        "It is a tall cylindrical bottle made of clear glass with an "+
        "intricate pattern of %s scrolling around the body.",
        ({"cylinder",}),
        ({"painted","cylindrical","glass",}),
        ([ "vines"   : ({ "flowering vines" }),
       "fish"    : ({ "leaping fish" }),
       "leaves"  : ({ "falling leaves" }),
       "dragons" : ({ "soaring dragons" }),
       "birds"   : ({ "flying birds" }),
       "snakes"  : ({ "entwined snakes" }),
       "wraiths" : ({ "flowing wraiths" }),
     ]),
        25, 1, 10 }),
    "prism" : ({ "prismatic crystal bottle",
        "It is a small bottle made of heavy, clear crystal, faceted to "+
        "refract the light and scatter it into rainbow colors.",
        ({"prism",}),
        ({"prismatic","crystal",}),
        ([ ]),
        15, 1, 10 }),
]);
#endif

/*
 * Indices for bottles mapping.
 */
#define SHORT      0
#define LONG       1
#define NAMES      2
#define ADJS       3
#define DESIGN     4
#define USES       5
#define BCOLOGNE   6
#define BCOST      7

/*
 * Locations for dabbing.
 */
#define MALE_LOCS   ({ "neck", "wrist", })
#define FEMALE_LOCS ({ "neck", "wrist", "bosom", "earlobes", })


#endif  __PERFUME_H__
