//crypt = stone chamber or vault used for burial
#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <std.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>

#define ONEOF(x)	x[random(sizeof(x))]

object Statue, Sconce, Chair, Vase;

public void
add_sconces()
{
    Sconce = clone_object(OBJ_DIR +"sconce");
    Sconce->set_direction("north");
    Sconce->move(TO);

    Sconce = clone_object(OBJ_DIR +"sconce");
    Sconce->set_direction("east");
    Sconce->move(TO);

    Sconce = clone_object(OBJ_DIR +"sconce");
    Sconce->set_direction("west");
    Sconce->move(TO);

    Sconce = clone_object(OBJ_DIR +"sconce");
    Sconce->set_direction("south");
    Sconce->move(TO);
}

public void
add_chair()
{
    if (!objectp(Chair))
    {
        Chair = clone_object(OBJ_DIR +"gilt_chair");
        Chair->move(TO);
    }
}

public int check_allowed()
{    
    write("A strange forboding tugs at your senses, but you continue.\n");
    return 0;
}

/*
public int allow(string str)
{
    if (!IS_VAMP(TP))
    {
        return 0;
    }
    notify_fail("Allow whom access to the inner chamber?\n");

    if (!strlen(str))
    {
        string * names=OCC_MANAGER->query_allowed();
        
        if (sizeof(names))
        {
            names=map(names,&capitalize());
            write(COMPOSITE_WORDS(names) + 
            (sizeof(names)==1 ? " is " : " are ") +
            "allowed entry to the inner chamber.\n");
        }
        else
        {
            write("No outsider can enter the inner chamber.\n");
        }
        return 1;
    }    
    object target;
    if (!parse_command(str,users(),"%o",target))
    {
        return 0;
    }
    if (!interactive(target))
    {
        return 0;
    }
    
    OCC_MANAGER->add_allowed(target->query_real_name());
    TP->catch_msg(QCTNAME(target) + " has been granted access "+
    "to the inner chamber.\n");
    return 1;
}

public int deny(string str)
{
    if (!IS_VAMP(TP))
    {
        return 0;
    }
    notify_fail("Allow whom access to the inner chamber?\n");
    if (!strlen(str))
    {
        return 0;
    }    
    
    if (OCC_MANAGER->remove_allowed(str))
    {
        TP->catch_msg(capitalize(str)+ " has been denied access "+
            "to the inner chamber.\n");
        return 1;
    }
    write("'" + capitalize(str) +"' has not been restricted from "+
    "the inner chamber.\n");
    return 1;
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

string
flicker()
{
    object torch = get_torch(), who;

    if(!torch || !living(who = ENV(torch)))
        return 0;

    who->catch_tell("Your " + torch->short(who) + " flickers in the breeze.\n");
    tell_room(ENV(who), QCTNAME(who) + "'s " + QSHORT(torch)
        + " flickers in the breeze.\n", ({ who }));
    return "";
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

    if (!objectp(Sconce))
        add_sconces();
   
    if(!light)
       return "";

    if(ENV(light) == TP)
       whose = "your";
    else if(!living(ENV(light)))
       whose = "the";
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
         light->short(TP)+ " " + ONEOF(({"trembles in the faint "+
         "breeze, illuminating the craggy walls nearby", 
         "casts wavering shadows that form dancing murals on "+
         "the walls", "illuminates the surrounding area"})) + ".  ";
}

/* related to the room long and dark long desc */
public string 
ambiance_test()
{
    string see_long, reg_long, mem_long, wiz_long;
    reg_long = "Despite the freshness of the air flowing into the "+
            "room, there is an ominous, brooding feeling here that "+
            "seems to rob your lungs of their will to breathe.  "+
            "You feel as if a giant hand is pressing down on you "+
            "and you cannot shake it, even knowing it is not there.  "+ 
            "";        
    if (IS_VAMP(TP))
        mem_long = "A feeling of belonging seeps into you as you sense "+
            "the Eldest, whose dreaming presence pervades the very air you "+
            "breathe, imbuing it with latent power.  ";
    if (IS_BG(TP))
        mem_long = "Despite the freshness of the air flowing into the "+
            "room, you sense the brooding presence of the Eldest filling "+
            "the the very air you breathe, making your feel lungs heavy.  "+
            "Awe and no small amount of fear seeps into your bones.  ";
    if (mem_long)
        see_long = mem_long;
    if (!objectp(Statue))
        see_long = reg_long;
    else    
       see_long = reg_long;
    if (IS_WIZ(TP))
       see_long = "This is the main training room for the guild.  "+ see_long;
//  return see_long;
    return ""; /* Changed this for closing the guild. Gorboth */
}

public string
chair_test()
{
    string str;

    if (!objectp(Chair))
        add_chair();    

    str = LANG_ASHORT(Chair);

    return str;
}

public void 
create_vamp_room()
{

    set_short("Sepulchre");

    set_long("@@ambiance_test@@"+
        "This appears to be a combination of sepulchre and temple, "+
        "both a place of eternal rest and a place of offering.  "+
        "Roughly hewn out of the living stone, the corners at each of "+
        "the cardinal points are marked by ornately-wrought torch "+
        "stands.  "+
        "@@light_test@@"+
        "The center of the room is marked by a high dais dominated by "+
        "@@chair_test@@" + ".  "+
        "Near the western corner is a large opening "+
        "in the floor through which cool air flows.  "+
        "\n");

    add_item("dais", "Standing about chest-height on a human, this "+
        "oblong-shaped dais was cut rough-hewn from the same stone "+
        "as the room.  Upon it rests "+
        "@@chair_test@@"+ 
        ".  Four steep steps have been cut into the west-facing side.\n");
    add_cmd_item(({"dais", "steps"}), "climb", 
        "The will to that that suddenly leaves you.\n");
    add_item(({"cardinal points", "corners", "four corners"}),
        "There are four corners, each marking the cardinal points: "+
        "north, east, west, and south.\n");
    add_item(({"wall", "walls", "living stone"}), 
        "The walls of this sepulchral chamber are carved from the "+
        "living stone. They are dark and craggy in most places.\n");
    add_cmd_item(({"wall", "walls", "living stone"}), 
        ({"touch", "feel"}), "The stone of the walls feels cold "+
        "and dry, and mostly rough, rather smooth-finished.\n");
    add_item(({"west corner", "western corner", "hole", "large hole",
        "down","opening","darkness", "floor"}),
        "There is a large opening in the floor along the western "+
        "wall. Fresh air flows through it, carrying the scent of "+
        "water.\n");

    add_exit("chamber","north","@@check_allowed@@");    
    add_exit("cave1","down");

    /* Can't see?  You can still feel the ambiance */
    add_prop(ROOM_S_DARK_LONG, "The darkness here is complete, "+
        "darker than any darkness you have previously experienced.  "+
        VBFC_ME("ambiance_test")+ "\n");
    add_prop(ROOM_S_DARK_MSG, "The darkness enveloping you is much "+
        "too thick to");
    add_prop(ROOM_I_INSIDE,1);

    if (!objectp(Vase))
    {
        Vase = clone_object(OBJ_DIR +"vase");
        Vase->move(TO);
    }

    add_chair();      
    add_sconces();
    reset_room();
}

public void reset_room()
{
    if (!objectp(Statue))
    {
      Statue=clone_object(NPC_DIR+"sleeping_statue");
    }
    Statue->move(TO);
    Statue->command("recline on chair");
/*
    // Remove all training from this room, Petros, Februrary 2010
    
    if (!objectp(Occ_train))
    {
        Occ_train=clone_object(LIB_DIR+"occ_train");
    }
    Occ_train->move(TO);
    if (!objectp(Lay_train))
    {
        Lay_train=clone_object(LIB_DIR+"lay_train");
    }
    Lay_train->move(TO);
    */
}

