// -*-C++-*-
// file name: 	  /d/Avenir/common/bazaar/Obj/forge/forge_master.c
// creator(s):	  Lilith March 1998
// last update:	  
// purpose:       Keep the mappings and arrays separate.
// note:      
// bug(s):
// to-do:

public mapping lining_type = ([       
        "chamois"  : ({ "chamois", "The chamois is a very "+
                        "soft, pliable leather dressed with exp"+
                        "ensive, scented oils that lend a water-"+
                        "resistent quality.\n" }),
        "linen"    : ({ "linen", "This simple yet elegant fabric "+
                        "is made from spun flax-fiber woven very fine."+
                        " It is a pleasantly cool and comfortable, "+
                        "if easily wrinkled, lining.\n" }),
        "leather"  : ({ "leather", "This leather comes from "+
                        "the tiny deer native to the Sybarus Holm. "+
                        "It has been tanned to bring out the fine "+
                        "grain, texture and suppleness of the skin.\n" }),
        "samite"   : ({ "samite", "This samite cloth is com"+
                        "posed of very heavy silk fibers interwov"+
                        "en with strands of silver.\n" }),
        "satin"    : ({ "satin", "Perfect, glossy satin made "+
                        "with painstakingly-woven silken threads.\n" }),
        "silk"     : ({ "silk", "The luxury of silk is unsurpas"+
                        "sed by any other fabric. This particular "+
                        "cloth is of the highest-quality weave, making "+
                        "it both lustrous and durable.\n" }),
        "suede"    : ({ "suede", "The suede is made from kid "+
                        "leather of the highest quality that has "+
                        "been carefully abraded so as to raise a "+
                        "fine, soft nap on the material.\n" }),
        "velvet"   : ({ "velvet", "This velvet is very plush, "+
                        "and so carefully woven that you are unable "+
                        "to see the individual loops of silk which "+
                        "form the soft, slightly napped surface.\n" }),
        "webcloth" : ({ "webcloth", "The webcloth material has "+
                        "the appearance and lightness of silk, but "+
                        "is very strong and resistant to tearing. "+
                        "It is known to be an extremely rare and "+
                        "thus rather expensive material.\n" }),
        "wool"     : ({ "wool", "This cloth is made of finely "+
                        "spun wool from the sybarun goat, whose "+
                        "fleece is long and silky soft.\n" }),
]);  


public mapping armour_style = ([  
        "scale"          : ({ 20,     ({ 0,0,0 }),       "scale mail", 
                              "small, overlapping plates of polished, high-"+
                              "quality steel riveted into oil-treated "+
                              "leather." }),             
        "chain"          : ({ 25,     ({ -2,3,-1 }),     "chainmail",
                              "intricately interlocking rings of highest "+
                              "quality steel. The rings form a trefoil "+
                              "pattern of three rings linking through a "+
                              "central fourth." }),      
        "augmented"      : ({ 30,     ({ -1,1,0 }),      "augmented mail",  
                              "intricately interlocking rings of highest "+
                              "quality steel, with strips of metal woven "+
                              "through the links. The rings form a trefoil "+
                              "pattern of three rings linking through a "+
                              "central fourth." }),       
        "plate"          : ({ 34,     ({ 0,0,0 }),       "platemail",
                              "large plates of high-quality steel moulded "+
                              "and articulated to provide maximum coverage "+
                              "and protection." }),
]);  

public mapping query_lining_map()   {    return lining_type;    }
public mapping query_style_map()    {    return armour_style;   }

string *linings =  m_indices(lining_type);
string *styles  =  m_indices(armour_style);
string *decora  =  ({ "enameled", "lacquered", "plated"});
string *plating =  ({ "platinum", "gold", "silver", "bronze", "copper"});
string *colours =  ({ "black", "scarlet", "cream", "golden", "green", "yellow",
                      "orange", "ochre", "pink", "purple", "violet",
                      "blood-red", "white", "gray", "blue", "blue-black",
                      "azure", "aquamarine", "silvery", }); 
string *worn    =  ({ "hands", "feet", "head", "arms", "legs", "torso", 
                      "full-body", "shield-arm"});

mixed query_styles()   {    return styles;    }
mixed query_linings()  {    return linings;   }
mixed query_decors()   {    return decora;    }
mixed query_decor()    {    return decora;    }
mixed query_platings() {    return plating;   }
mixed query_plating()  {    return plating;   }
mixed query_colours()  {    return colours;   }
mixed query_where()    {    return worn;      }

public int    *query_armour_am(string str)   {    return armour_style[str][1];    }
public string query_armour_ac(string str)    {    return armour_style[str][0];    }
public string query_armour_style(string str) {    return armour_style[str][2];    }
public string query_armour_long(string str)  {    return armour_style[str][3];    }
public string query_lining_long(string str)  {    return lining_type[str][1];     }

