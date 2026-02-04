//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    
// note: 
// bug(s):
// to-do:

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>

#define ONEOF(x)	x[random(sizeof(x))]

/*
object Sconce, Icoffin;

public void
clone_decorations()
{
    if (!Sconce)
    {
        Sconce = clone_object(OBJ_DIR +"sconce");
        Sconce->set_direction("north");
        Sconce->move(TO);

        Sconce = clone_object(OBJ_DIR +"sconce");
        Sconce->set_direction("south");
        Sconce->move(TO);
    }
    if (!Icoffin)
    {
        Icoffin=clone_object(ROOM_DIR+"coffin");
        Icoffin->set_owner("isabella");
        Icoffin->move(TO);
    }
}
*/

/* Light-related functions for long desc */
object
get_torch()
{
    object *things;

    things = filter(deep_inventory(TO), &->query_prop(OBJ_I_HAS_FIRE));

    if(!sizeof(things))
        return 0;

    return ONEOF( things );
}

int
emitting_light(object what)
{
    if(function_exists("create_container", what))
        return 0;
    else if(what->query_prop(OBJ_I_LIGHT) > 0)
        return 1;
    else
        return 0;
}

object
find_light()
{
    object *stuff;

    stuff = filter(deep_inventory(TO), emitting_light);

    if(!sizeof(stuff))
        return 0;
    else
        return stuff[0];
}

string
light_test()
{
    object light = find_light();
    string whose, fire, brightness, sdesc;
/*
    if (!objectp(Sconce))
        clone_decorations();
*/   
    if(!light)
       return "";

    if(ENV(light) == TP)
       whose = "your";
    else if(!living(ENV(light)))
       whose = "a";
    else
       whose = ENV(light)->query_the_name(TP) + "'s";

    if(light->query_prop(OBJ_I_HAS_FIRE))
       fire = "fluttering flames";
    else
       fire = ONEOF(({"luminescence","lambent glow"}));

    switch(light->query_prop(OBJ_I_LIGHT))
    {
       case 0:
          brightness = "nonexistent ";
          break;
       case 1..2:
          brightness = "muted ";
          break;
       case 3..5:
          brightness = "bright ";
          break;
       default:
          brightness = "dazzling ";
          break;
    }

    sdesc = light->short(TP);

    /* I don't like the "thick torch (lit)" description */
    if(strlen(sdesc))
       sdesc = implode(explode(sdesc, " (lit)"), "");
    else
       sdesc = "light";

    return "The " + brightness + fire + " of " + whose + " " + 
         light->short(TP)+ " " + ONEOF(({"flickers faintly", 
         "flickers wildly", "wavers momentarily",
         "casts wavering shadows on the tapestries nearby"})) + ". ";
}

public void create_vamp_room()
{

    set_short("Upper tomb");
    set_long("Considerable care was taken to make this a comfortable room. "+
        "The crudely-cut stone walls are almost entirely covered by wall-"+
        "hangings, while large rugs cover most of the floor. Two ornamental "+
        "torchiere stands have been placed in the middle of the north and "+
        "south walls. @@light_test@@"+
        "A single chair with a red-velvet cushion sits opposite the door, "+
        "with a small table standing beside it.\n");

//  add_prop(VAMP_CAN_START_HERE,1);
    add_prop(OBJ_S_SEARCH_FUN, "search_items");
//    clone_decorations();
    
    add_exit("upperchamber","east");
    add_exit("study", "south", "@@south_check@@", 1, 1);

    add_item(({"floor", "ground"}), 
        "The floor is level and unpolished. A thick layer "+
        "of carpets has been scattered over the floor, nearly covering it "+
        "entirely.\n");
    add_item(({"carpet", "carpets", "rug", "rugs"}), 
        "Many carpets line the floor. Beautifully woven with once-vibrant "+
        "colours now muted by time, threadbare and torn in places, their "+
        "condition would be improved by some cleaning and mending.\n");
    add_cmd_item(({ "carpet", "carpets", "rug", "rugs" }), 
        ({ "clean", "beat", "shake" }), 
        "You pick up a carpet and give it a good cleaning.\nYou return "+
        "the carpet to its former place and start to pick up another, "+
        "then stop once you realize that you could do this for hours "+
        "and not really make a dent in cleaning the carpets.\n");    
    add_cmd_item(({ "carpet", "carpets", "rug", "rugs" }), 
        ({ "mend", "repair", "lift" }), 
        "You pick up a carpet and do your best to mend a tear.\nYou return "+
        "the carpet to its former place and start to pick up another, "+
        "then stop once you realize that you could do this for hours "+
        "and not really make a dent in improving the condition of the "+
        "carpets.\n");                    
    add_item(({"ceiling"}), 
        "The ceiling is low and craggy.\n");
    add_item(({"wall", "walls", "stone", "natural stone"}), 
        "The walls are cut from the natural subterranean stone. They are "+
        "almost completely covered in wall-hangings and tapestries.\n");
    add_item(({"wall-hanging", "wall-hangings", "fabric", "fabrics"}),
        "Yards of embroidered and brocaded fabric line the walls.\n");
    add_item(({"embroidery", "embroidered fabric", "brocade", 
        "brocaded fabric", "stitching"}),
        "Ancient, faded by time and neglect, the stitching is no less "+
        "beautiful than it was the day it was created.\n");
    add_item(({"tapestry", "tapestries"}),
        "There are three tapestries, one on each of the north, south, "+
        "and west walls.\n");
    add_item(({ "north tapestry", "north wall", "battle scene" }), 
        "This tapestry depicts an epic battle scene. It appears that "+
        "humans, elves, and dwarves are fighting dragons, trolls, and "+
        "orcs in a snowy and mountainous land with silvery trees.\n");
    add_item(({ "west tapestry", "west wall", "garden", "garden scene" }), 
        "This tapestry shows a garden. There is a golden-haired woman "+
        "sitting under a large tree with a wolfhound laying across "+
        "her lap. Flowering vines loop and twine in complex knots "+
        "around the tapestry's border.\n");
    add_item(({ "south tapestry", "south wall", "study", "small study" }), 
        "This tapestry depicts a small study. It features a desk "+
        "with a bowl of flowers on it and a landscape painting "+
        "above it. There appears to be a small tear in the tapestry, "+
        "near the top drawer.\n");
    add_item(({"tear", "tear in tapestry", "tear in south tapestry" }),
        "You lean closer to the tear in order to examine it.\nYou "+
        "catch a glimpse of something metallic.\n");
    add_item(({"something metallic", "metallic item", "metallic object"}),
        "You can just glimpse something metallic beyond the tear "+
        "in the tapestry.\nPerhaps you should use your hands instead?\n");
    add_item(({"knob"}), "It is a small metallic knob. It appears "+
        "possible to turn it.\n");
    add_item(({ "chair", "wooden chair", "straight-backed chair" }), 
        "It is a straight-backed chair made of wood so old it is "+
        "practically petrified. It has a red velvet cushion on the seat.\n");
    add_item(({ "red-velvet cushion", "velvet cushion", "red cushion", "cushion" }), 
        "It is a flat cushion apparently used to alleviate the hardness "+
        "of the wooden chair.\n");
    add_item(({"table", "small table"}), 
        "It is a small side table made of wood so old, it looks "+
        "like stone.\n");
    add_cmd_item(({ "red-velvet cushion", "velvet cushion", "red cushion", "cushion" }),
        ({ "get", "take" }), "You get the cushion.\nIt is not very interesting, "+
        "so after a cursory examination, you put it back.\n");    
    add_cmd_item(({ "red-velvet cushion", "velvet cushion", "red cushion", "cushion" }),
        ({ "sit", "sit on"}), "You rest for a moment on the chair.\n");
    add_cmd_item(({ "chair", "wooden chair", "straight-backed chair" }), 
        ({ "get", "take" }), "You get the chair.\nAfter a moment, you put it back "+
        "in its place.\n");
    add_cmd_item(({ "chair", "wooden chair", "straight-backed chair" }), 
        ({ "move", "lift"}), "You move the chair a bit.\n");
    add_cmd_item(({ "chair", "wooden chair", "straight-backed chair" }), 
        ({ "sit", "sit on"}), "You rest for a moment on the chair.\n");
    add_cmd_item(({ "table", "small table" }), 
        ({ "get", "take" }), "You get the table.\nAfter a moment, you put it back "+
        "in its place.\n");
    add_cmd_item(({ "table", "small table" }), 
        ({ "move", "lift"}), "You move the table a bit.\n");

}

public string 
search_items(object player, string str)
{      
    switch (str)
    {
        case "south tapestry":    
        case "desk":  
        case "tear":
        case "tear in tapestry":
        case "metallic item":
        case "metallic object":
        case "something metallic":
            player->add_prop("_i_found_knob", 1);
            return "Your fingers find a small knob behind the tear "+
                   "in the tapestry.\n";
            break;
        default:  return "";

    }
     return "";    
}

int
south_check()
{
    if (TP->query_prop("_i_found_knob") < 2)
    {
        TP->catch_msg("There is no obvious exit south.\n");
        return 1;  
    }
    else
    {
        TP->catch_msg("You slip past the tapestry and into "+
            "the room beyond.\n");
        TP->remove_prop("_i_found_knob");
        return 0;
    }
    return 1;
}

int 
do_turn(string str)
{
    if (!TP->query_prop("_i_found_knob"))
    {
        notify_fail("Turn what?\n");
        return 0;
    }

    notify_fail("Are you trying to turn the knob?\n");
    if (!parse_command(str, ({ }), "[the] 'knob'"))
        return 0;    


    write("You turn the knob.\nThere is a clicking sound and "+
        "then a rush of air indicating a void behind the "+
        "south tapestry.\n");
    TP->add_prop("_i_found_knob", 2);
    return 1;
}


void
init() 
{
    ::init();
    add_action(do_turn, "turn");
}
