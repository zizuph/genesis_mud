
/* 
    /d/Calia/gelan/cadet/hall_of_peace.c 

    The hall of peace, a place to meditate for the cadets, 
    and a place to balance the emphasis of the hall of war. 

    Coded by Maniac@Genesis, May 12 1999 

    Copyright (C) Miguel Leith 1999 

    History: 
    12/5/99         Created                            Maniac 
    30/6/00         Modified timing.                   Maniac 
    Oct, Nov 02     Desc changes re: graduation ring   Maniac 
*/ 

#pragma save_binary

inherit "/std/room";
inherit "/lib/guild_support";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <files.h>
#include <composite.h>
#include "cadet.h"

#pragma strict_types

#define LOCKER_SAVE "/d/Calia/gelan/cadet/locker_save"

public string centre_colour, centre_figure, inner_stone, 
              window_colour, letter_type, marble_colour, 
              light_travel_type, ray_type; 

mapping lockers; 


/* 
 * Function:    gc_query_private_room. 
 * Description: Identify this as a private cadet room. 
 */ 
int 
gc_query_private_room() 
{ 
    return 1; 
} 


/*
 * Function:     query_ring 
 * Description:  Gives back the graduation ring carried 
 *               by this_player() if any. 
 * Returns:      object - graduation ring (if any). 
 */ 
public object 
query_ring() 
{ 
    object tp = this_player(); 

    if (!objectp(tp)) 
        return 0; 

    return present(GC_RING_ID, tp); 
} 


/* 
 * Function:     reset_desc_vars 
 * Description:  Resets the configurable variables in the 
 *               room description to their defaults. 
 */ 
public void 
reset_desc_vars() 
{ 
    centre_colour = "golden"; 
    centre_figure = "falcon"; 
    window_colour = "sky blue"; 
    letter_type = "gold"; 
    ray_type = "gold"; 
    marble_colour = "snow white"; 
    light_travel_type = "radiate"; 
} 


/*
 * Function:     update_centre_colour 
 * Description:  Updates the centre colour in the room description 
 *               for a particular graduate according to the specified 
 *               graduation ring. 
 * Arguments:    object ring - the graduation ring. 
 */ 
private void 
update_centre_colour(object ring) 
{ 
    if ((centre_colour = ring->query_centre_colour()) == "silver") 
    { 
        centre_colour = "silver"; 
    } 
    else if (centre_colour == "crystal") 
    { 
        centre_colour = "crystal"; 
    } 
    else 
    { 
        centre_colour = "golden"; 
    } 
} 


/* 
 * Function:     update_centre_figure 
 * Description:  Updates the centre figure in the room description 
 *               for a particular graduate according to the specified 
 *               graduation ring. 
 * Arguments:    object ring - the graduation ring. 
 */ 
private void 
update_centre_figure(object ring) 
{ 
    if ((centre_figure = ring->query_centre_figure()) == "hawk") 
    { 
        centre_figure = "hawk"; 
    } 
    else if (centre_figure == "kestrel") 
    { 
        centre_figure = "kestrel"; 
    } 
    else 
    { 
        centre_figure = "falcon"; 
    } 
} 


/* 
 * Function:     update_window_colour 
 * Description:  Updates the window colour in the room description 
 *               for a particular graduate according to the specified 
 *               graduation ring. 
 * Arguments:    object ring - the graduation ring. 
 */ 
private void 
update_window_colour(object ring) 
{ 
    if ((inner_stone = ring->query_inner_stone()) == "onyx") 
    { 
        window_colour = "night dark"; 
    } 
    else if (inner_stone == "quartz") 
    { 
        window_colour = "twilight grey"; 
    } 
    else 
    { 
        window_colour = "sky blue"; 
    } 
} 


/* 
 * Function:     update_letter_type  
 * Description:  Updates the letter type in the room description 
 *               for a particular graduate according to the specified 
 *               graduation ring. 
 * Arguments:    object ring - the graduation ring. 
 */ 
private void 
update_letter_type(object ring) 
{ 
    if ((letter_type = ring->query_letter_type()) == "silver") 
    { 
        letter_type = "silver"; 
    } 
    else if (letter_type == "crystal")
    { 
        letter_type = "crystal"; 
    } 
    else 
    { 
        letter_type = "gold"; 
    } 
} 


/* 
 * Function:     update_ray_type 
 * Description:  Updates the ray type (and light travel type) in the 
 *               room description for a particular graduate according 
 *               to the specified graduation ring. 
 * Arguments:    object ring - the graduation ring. 
 */ 
private void 
update_ray_type(object ring) 
{ 
    if ((ray_type = ring->query_ray_type()) == "silver") 
    { 
        ray_type = "silver"; 
        light_travel_type = "emanate"; 
    } 
    else if (ray_type == "crystal") 
    { 
        ray_type = "crystal"; 
        light_travel_type = "refract"; 
    } 
    else 
    { 
        ray_type = "gold"; 
        light_travel_type = "radiate"; 
    } 
} 


/* 
 * Function:     update_marble_colour 
 * Description:  Updates the marble colour in the room description 
 *               for a particular graduate according to the specified 
 *               graduation ring. 
 * Arguments:    object ring - the graduation ring. 
 */ 
private void 
update_marble_colour(object ring) 
{ 
    if ((marble_colour = ring->query_marble_colour()) == "faded red") 
    { 
        marble_colour = "faded red"; 
    } 
    else if (marble_colour == "faded green") 
    { 
        marble_colour = "faded green"; 
    } 
    else 
    { 
        marble_colour = "snow white"; 
    } 
} 



/* 
 * Function:     hall_long 
 * Description:  Gives back the long description, which if 
 *               this_player() is a graduate gets configured 
 *               to match his/her graduation ring. 
 * Returns:      string - long description 
 */ 
public string 
hall_long() 
{ 
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_centre_colour(r); 
        update_centre_figure(r); 
        update_window_colour(r); 
        update_letter_type(r); 
        update_ray_type(r); 
        update_marble_colour(r); 
    } 
    else 
    { 
        reset_desc_vars(); 
    } 

    return 
       ("A circular hall with a cool " + marble_colour + 
        " marble tiled floor, walls and ceiling extends around " + 
        "you, the sheen on their surfaces revealing no obvious " + 
        "flaws. " + 
        "The air here is cool and refreshing with a trace of " + 
        "moisture. Filtered sunlight enters through a " + 
        "hexagonal stained glass window in the domed roof, " + 
        "coloured " + window_colour + " and adorned with the " + 
        "image of " + LANG_ADDART(centre_colour) + " " + 
        centre_figure + ". " + 
        "Six fine lines of " + ray_type + " " + light_travel_type + 
        " from the window to the ceiling's " + 
        "edge, forming a barely perceptible star. Around the " + 
        "chamber wall, in a narrow band half way up, delicate " + 
        letter_type + " tracing weaves an intricate pattern. " + 
        "You may <meditate> here. A hexagonal aperture in the " + 
        "floor provides an exit, via a ladder.\n"); 
} 


/* 
 * Function:     floor_walls_desc 
 * Description:  Gives back the description of the floor/walls, 
 *               which is this_player() is a graduate gets 
 *               configured to match his/her graduation ring. 
 * Returns:      string - floor / walls description. 
 */ 
public string 
floor_walls_desc() 
{ 
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_marble_colour(r); 
    } 
    else 
    { 
        marble_colour = "snow white"; 
    } 

    return ("The floor and walls have " + marble_colour + 
            " marble tiles.\n"); 
} 


/* 
 * Function:     ceiling_desc 
 * Description:  Gives back the description of the ceiling, 
 *               which is this_player() is a graduate gets 
 *               configured to match his/her graduation ring. 
 * Returns:      string - ceiling description. 
 */ 
public string
ceiling_desc()
{
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_marble_colour(r); 
    } 
    else 
    { 
        marble_colour = "snow white"; 
    } 

    return 
        ("It's a domed shaped roof with tiles of " + 
         marble_colour + " marble. A hexagonal window " + 
         "crowns the structure.\n"); 
} 


/* 
 * Function:     image_desc 
 * Description:  Gives back the description of the window image, 
 *               which is this_player() is a graduate gets 
 *               configured to match his/her graduation ring. 
 * Arguments:    string colour - colour of image. 
 *               string figure - description of image figure. 
 * Returns:      string - image description. 
 */ 
public varargs string
image_desc(string colour = 0, string figure = 0)
{
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_centre_colour(r); 
        if (stringp(colour) && centre_colour != colour) 
            return 0; 

        update_centre_figure(r); 
        if (stringp(figure) && centre_figure != figure) 
            return 0; 

        update_window_colour(r); 
    } 
    else 
    { 
        centre_colour = "golden"; 
        centre_figure = "falcon"; 
        window_colour = "sky blue"; 
    } 

    return ("The image of " + LANG_ADDART(centre_colour) + 
            " " + centre_figure + " with its wings " + 
            "outspread, intricately detailed down to its " + 
            "feathers, adorns the hexagonal " + 
            window_colour + " window.\n"); 
} 


/* 
 * Function:     window_desc 
 * Description:  Gives back the description of the window, 
 *               which is this_player() is a graduate gets 
 *               configured to match his/her graduation ring. 
 * Arguments:    string colour - colour of window. 
 * Returns:      string - window description. 
 */ 
public varargs string
window_desc(string colour = 0)
{
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_window_colour(r); 
        if (stringp(colour) && window_colour != colour) 
            return 0; 

        update_centre_colour(r); 
        update_centre_figure(r); 
    } 
    else 
    { 
        window_colour = "sky blue"; 
        centre_colour = "golden"; 
        centre_figure = "falcon"; 
    } 

    return ("The hexagonal window, made of stained glass " + 
            "coloured " + window_colour + " and adorned with " + 
            "the image of " + LANG_ADDART(centre_colour) + " " + 
            centre_figure + ", crowns the domed roof, allowing " + 
            "filtered sunlight to illuminate the chamber.\n"); 
} 


/* 
 * Function:     marble_desc 
 * Description:  Gives back the description of the marble, 
 *               which is this_player() is a graduate gets 
 *               configured to match his/her graduation ring. 
 * Arguments:    string colour - colour of marble. 
 * Returns:      string - marble description. 
 */ 
public varargs string
marble_desc(string colour = 0)
{
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_marble_colour(r); 
        if (stringp(colour) && marble_colour != colour) 
            return 0; 
    } 
    else 
    { 
        marble_colour = "snow white"; 
    } 

    return ("The marble has " + LANG_ADDART(marble_colour) + 
            " surface that shines in the filtered sunlight " + 
            "entering through the skylight. Many such tiles " + 
            "surface the floor, walls and ceiling here.\n"); 
} 


/* 
 * Function:     tracing_desc 
 * Description:  Gives back the description of the tracing, 
 *               which is this_player() is a graduate gets 
 *               configured to match his/her graduation ring. 
 * Arguments:    string colour - colour of tracing. 
 * Returns:      string - tracing description. 
 */ 
public varargs string
tracing_desc(string colour = 0)
{
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_letter_type(r); 
        if (stringp(colour) && letter_type != colour) 
            return 0; 
    } 
    else 
    { 
        letter_type = "gold"; 
    } 

    return ("The " + letter_type + " tracing is extremely " + 
            "fine and only just perceptible. The narrow band " + 
            "around the wall forms an intricate pattern like " + 
            "a somehow ordered tangle of vines.\n"); 
} 


/* 
 * Function:     star_desc 
 * Description:  Gives back the description of the star, 
 *               which is this_player() is a graduate gets 
 *               configured to match his/her graduation ring. 
 * Arguments:    string colour - colour of star. 
 * Returns:      string - star description. 
 */ 
public varargs string 
star_desc(string colour = 0) 
{
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_ray_type(r); 
        if (stringp(colour) && ray_type != colour) 
            return 0; 

        update_window_colour(r); 
    } 
    else 
    { 
        ray_type = "gold"; 
        light_travel_type = "radiate"; 
        window_colour = "sky blue"; 
    } 

    return ("Fine lines of " + ray_type + " " + light_travel_type + 
            " from the " + window_colour + " window to the ceiling's " + 
            "edge, six of them, evenly spaced, creating a barely " + 
            "perceptible star.\n"); 
} 


/* 
 * Function:    create_room 
 * Description: creates the room. 
 */ 
void 
create_room() 
{ 
    reset_desc_vars(); 

    set_short("The hall of peace"); 
    set_long(hall_long); 


    add_item(({"chamber", "hall", "hall of peace"}), 
             "You could always \"look\".\n"); 

    add_item(({ "hexagonal window", "window",  "skylight", "sky light" }), 
             window_desc); 

    add_item(({"floor", "walls", "wall" }), floor_walls_desc); 

    add_item(({"ceiling", "roof", "domed roof" }), ceiling_desc); 


    /* 
     * Marble items. 
     */ 
    add_item(({ "marble", "marble stone", "marble stones", 
               "surface stones", "marble tiles", "marble tile", 
               "tiles", "tile" }), &marble_desc(0)); 


    add_item(({ "white marble", "snow white marble", "white tiles", 
               "snow white tiles", "white tile", "snow white tile", 
               "white stone", "white stones", "snow white stone", 
               "snow white stones" }), &marble_desc("snow white")); 

    add_item(({ "red marble", "faded red marble", "red tiles", 
               "faded red tiles", "red tile", "faded red tile", 
               "red stone", "red stones", "faded red stone", 
               "faded red stones" }), &marble_desc("faded red")); 

    add_item(({ "green marble", "faded green marble", "green tiles", 
               "faded green tiles", "green tile", "faded green tile", 
               "green stone", "green stones", "faded green stone", 
               "faded green stones" }), &marble_desc("faded green")); 

    /* 
     * Tracing items. 
     */ 
    add_item(({ "pattern", "tracing", "band" }), &tracing_desc(0)); 

    add_item(({ "gold", "gold tracing", "gold band", "gold pattern",
                "golden tracing", "golden band", "golden pattern" }), 
             &tracing_desc("gold")); 

    add_item(({ "silver", "silver tracing", "silver band", 
                "silver pattern" }), &tracing_desc("silver")); 

    add_item(({ "crystal", "crystal tracing", "crystal band", 
                "crystal pattern" }), &tracing_desc("crystal")); 


    /* 
     * Star items. 
     */ 
    add_item(({"star", "line", "lines" }), &star_desc(0)); 

    add_item(({ "golden star", "gold star", "gold lines", 
                "golden lines" }), &star_desc("gold")); 

    add_item(({ "silver star", "silver star", "silver lines", 
                "silver lines" }), &star_desc("silver")); 

    add_item(({ "crystal star", "crystal star", "crystal lines", 
                "crystal lines" }), &star_desc("crystal")); 


    /* 
     * Image items. 
     */ 
    add_item(({ "image" }), &image_desc(0, 0)); 

    add_item(({ "falcon" }), &image_desc(0, "falcon")); 

    add_item(({ "kestrel" }), &image_desc(0, "kestrel")); 

    add_item(({ "hawk" }), &image_desc(0, "hawk")); 

    add_item(({ "golden image", "gold image" }), 
             &image_desc("golden", 0)); 

    add_item(({ "silver image" }), &image_desc("silver", 0)); 

    add_item(({ "crystal image" }), &image_desc("crystal", 0)); 

    add_item(({ "gold falcon", "golden falcon" }), 
             &image_desc("golden", "falcon")); 

    add_item(({ "golden kestrel", "gold kestrel" }), 
             &image_desc("golden", "kestrel")); 

    add_item(({ "golden hawk", "gold hawk" }), 
             &image_desc("golden", "hawk")); 

    add_item(({ "silver falcon" }), &image_desc("silver", "falcon")); 

    add_item(({ "silver kestrel" }), &image_desc("silver", "kestrel")); 

    add_item(({ "silver hawk" }), &image_desc("silver", "hawk")); 

    add_item(({ "crystal falcon" }), &image_desc("crystal", "falcon")); 

    add_item(({ "crystal kestrel" }), &image_desc("crystal", "kestrel")); 

    add_item(({ "crystal hawk" }), &image_desc("crystal", "hawk")); 


    add_item(({"ladder", "wooden ladder"}), 
              "A simple wooden ladder leads down to another chamber " + 
              "through a hexagonal aperture in the floor.\n"); 

    add_item(({"aperture", "hole", "hexagonal aperture" }), 
              "The hexagonal aperture is positioned in the floor's " + 
              "centre, amply wide enough for visitors to fit through. " + 
              "The top of a ladder is fixed against it.\n"); 

    add_prop(ROOM_I_INSIDE, 1); 
    add_prop(ROOM_I_HIDE, 75); 
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchantment" })); 
    add_prop(MAGIC_AM_ID_INFO, 
             ({ "The appearance of the hall of peace can vary " + 
                "depending on the onlooker.\n", 10, 
                "The appearance of the hall of peace can vary " + 
                "depending on the attributes of the onlooker's " + 
                "graduation ring.\n", 20 })); 

    restore_object(LOCKER_SAVE); 
    if (!mappingp(lockers))
        lockers = ([ ]); 
    else
        lockers = m_delete(lockers, 0); 
}


/*
 * Function:     remove_object
 * Description:  removes the object, returning 1 if successful, 0 otherwise.  
 *               Here it's masked to save the locker mapping before removing
 *               the room. 
 */ 
int 
remove_object()
{
    save_object(LOCKER_SAVE); 
    ::remove_object(); 
}


void
gs_hook_start_meditate()
{
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_marble_colour(r);
    } 

    write("Slowly you sit down on the " + marble_colour + 
        " marble floor and close your eyes. A " +
        "feeling of great peace and self control falls upon you. You block " +
        "off your senses and concentrate solely upon your own mind. You " +
        "find yourself able to <set> your different preferences at you own " +
        "desire. Just <rise> when you are done meditating. You estimate " +
        "your stats and the progress you make at them.\n\n");
    say(QCTNAME(this_player()) + " sits down on the marble floor and starts " +
        "to meditate.\n");        
}


void
gs_hook_rise()
{
    object r = query_ring(); 

    if (objectp(r)) 
    { 
        update_marble_colour(r);
    } 

    write("As if ascending from a great depth, you rise to the surface of\n" +
          "your consciousness. You exhale and feel very relaxed as you get\n" +
          "up and leave the " + marble_colour + " marble floor.\n");
    say(QCTNAME(this_player()) + " rises from the marble floor.\n");          
}


/*
 * Function:     down_ladder
 * Description:  Action function to move down the ladder into the 
 *               hall of war. 
 */ 
int
down_ladder(string str)
{
    string verb = query_verb();  
    object to = GC_STARTROOM->get_this_object(); 
    object pl = this_player(); 

    if ((verb != "climb" && (!stringp(str) || str == "ladder")) ||
        (verb == "climb" && str == "down ladder")) {
        tell_room(this_object(), QCTNAME(pl) + " leaves descending " +
                  "the ladder.\n", pl); 
        tell_object(pl, "You descend the ladder.\n"); 
        pl->move_living("M", to); 
        tell_room(to, QCTNAME(pl) + " arrives descending the " +
                                    "ladder.\n", pl);
        if (objectp(lockers[pl])) 
            tell_object(pl, "Don't forget to <cclaim> your items.\n"); 
        return 1; 
    }  
    notify_fail("Climb down ladder?\n"); 
    return 0; 
}


/* 
 * Function:      lockable
 * Description:   returns 1 if the object o is a weapon, 0 otherwise. 
 */ 
int
lockable(object o)
{
    return (IS_WEAPON_OBJECT(o) && !o->query_prop(OBJ_M_NO_DROP)); 
}


/* 
 * Function:      can_enter
 * Description:   returns 1 if a player can enter here from the hall
 *                of war, 0 otherwise. No player with a weapon may
 *                enter. 
 */ 
int
can_enter(object player)
{
    return !sizeof(filter(deep_inventory(player), lockable));   
}


/*
 * Function:     down_ladder
 * Description:  Action function to move up the ladder to here from  
 *               the hall of war. Delegated from the cadet startroom. 
 */ 
int
up_ladder(string str, object from)
{
    string verb = query_verb();
    object pl = this_player();  

    if ((verb != "climb" && (!stringp(str) || str == "ladder")) ||
        (verb == "climb" && str == "up ladder")) {
        if (!can_enter(pl)) {
            tell_object(pl, "You are about to ascend but a guard stops " +
                            "you, saying you are carrying weapons. " +
                            "It looks like you will have to <cstore> " +
                            "any weapons you have.\n"); 
            tell_room(from, QCTNAME(pl) + " is about to ascend but " +
                            "a guard stops " + pl->query_objective() + 
                            ", saying " + pl->query_pronoun() + 
                            " is carrying weapons.\n", pl);  
            return 1; 
        } 
        tell_room(from, QCTNAME(pl) + " leaves ascending " +
                  "the ladder.\n", pl); 
        tell_object(pl, "You ascend the ladder.\n"); 
        pl->move_living("M", this_object()); 
        tell_room(this_object(), QCTNAME(pl) + 
                  " arrives ascending the ladder.\n", pl);
        return 1; 
    } 
    notify_fail("Climb up ladder?\n"); 
    return 0;  
}


/* 
 * Function:     move_living_downstairs
 * Description:  Move a living object (ob) downstairs. 
 */ 
void
move_living_downstairs(object ob)
{
    tell_room(this_object(), "Some guards arrive to " +
             "escort " + QTNAME(ob) + " to the hall of war.\n", ob);
    tell_object(ob, "Some guards arrive to escort you to the hall of war.\n");  
    ob->command("$down"); 
} 


/* 
 * Function:     move_inanimate_downstairs
 * Description:  Move an inanimate object (ob) downstairs. 
 */ 
private void
move_inanimate_downstairs(object ob)
{
    object to; 

    if (!ob->move(to = GC_STARTROOM->get_this_object()) && 
        objectp(ob)) { 
        tell_room(this_object(), "A guard arrives and takes " +
                  LANG_THESHORT(ob) + " down to the " +
                  "hall of war.\n"); 
        tell_room(to, "A guard arrives, " +
                      "drops " + LANG_ASHORT(ob) + " and then leaves.\n");  
    }
}


/* 
 * Function:    enter_inv
 * Description: Called when an object enters the inventory of
 *              this room. Here it's masked to move unwanted
 *              objects out. 
 */ 
void
enter_inv(object ob, object from)
{
    if (!living(ob)) 
        set_alarm(0.0, 0.0, &move_inanimate_downstairs(ob));  
    else if (ob->query_npc())
        set_alarm(0.0, 0.0, &move_living_downstairs(ob)); 
    else  
        clone_object(GC_DIR + "peace_shadow")->shadow_me(ob); 
    ::enter_inv(ob, from); 
}


/* 
 * Function:    leave_inv
 * Description: Called when an object leaves the inventory of
 *              this room. Here it's masked to call the guild
 *              support function gs_leave_inv (they might
 *              be meditating!)
 */ 
void
leave_inv(object ob, object to)
{
    if (living(ob) && !ob->query_npc())
        ob->gc_remove_peace_shadow();
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}


/* 
 * Function:     init
 * Description:  Called when an object comes into contact with this one. 
 *               Adds the hall of peace actions.  
 */ 
void
init()
{
    ::init();
    init_guild_support(); 
    add_action(down_ladder, "down"); 
    add_action(down_ladder, "descend"); 
    add_action(down_ladder, "climb"); 
}



/* 
 * Function:      is_container
 * Description:   returns 1 if the object o is a container, 0 otherwise. 
 */ 
int
is_container(object o)
{
    return IS_CONTAINER_OBJECT(o); 
}



/* 
 * Function:     query_locker
 * Description:  returns the locker object for the given player, where
 *               s/he stores weapons
 */
object
query_locker(object player)
{
    object locker; 

    if (!objectp(locker = lockers[player])) {
        locker = clone_object(GC_DIR + "peace_locker"); 
        lockers[player] = locker; 
    } 
    return locker; 
}


/* 
 * Function:      store
 * Description:   Action function delegated from the hall of war. 
 *                Allows a player to store weapons in a locker for
 *                a short while, so they can enter here. 
 */ 
int
store(string str) 
{
    object *moved, *obs, *tmp, locker, player = this_player(); 
    int i, s, something_happened;
    string os; 

    obs = all_inventory(player); 

    something_happened = 0; 

    if (s = sizeof(moved = filter(obs, is_container))) { 
        obs -= moved; 
        /* The lockable contents of unlockable containers should be
           freed up. */ 
        locker = query_locker(player); 
        tmp = ({ }); 
        for (i = 0; i < s; i++)  
            if (!lockable(moved[i]) || moved[i]->move(locker)) {
                if (sizeof(filter(deep_inventory(moved[i]), lockable))) 
                    tmp += ({ moved[i] });
                else
                    moved[i] = 0;  
            } 
        moved -= ({ 0 }); 

        if (sizeof(tmp)) {
            moved -= tmp; 
            player->catch_msg("A guard tells you that you will " +
                              "have to free up the weapons in " + 
                              COMPOSITE_DEAD(tmp) + ".\n");
            something_happened = 1; 
        }  
    }  

    if (s = sizeof(obs = filter(obs, lockable))) {
        tmp = ({ }); 
        locker = query_locker(player); 
        for (i = 0; i < s; i++) 
            if (obs[i]->move(locker))
                tmp += ({ obs[i] }); 

        if (sizeof(tmp)) { 
            obs -= tmp; 
            player->catch_msg("A guard tells you that you will have to " +
                    "free up " + COMPOSITE_DEAD(tmp) + " before you may " +
                    "pass.\n"); 
            something_happened = 1; 
        } 

        if (sizeof(obs)) 
            moved += obs; 
    } 

    if (sizeof(moved)) {
        locker->reset_locker_time(); 
        os = COMPOSITE_DEAD(moved);  
        player->catch_msg("You hand over " + os + " to a guard.\n"); 
        tell_room(environment(player), QCTNAME(player) + 
                  " hands over " + os + " to a guard.\n", player); 

        tell_object(player, 
            "Your storage time will expire in twenty minutes, " + 
            "you must return before then to <cclaim> them, " +
            "or you will lose your weapons.\n"); 
        something_happened = 1; 
    } 

    if (something_happened)
        return 1; 

    notify_fail("You had nothing to store.\n"); 
    return 0; 
}


/* 
 * Function:      claim
 * Description:   Action function delegated from the hall of war. 
 *                Allows a player to claim weapons from a locker that
 *                were stored earlier. 
 */ 
int
claim(string str)
{
    int s, i; 
    object *o, *tmp, locker, player = this_player();  
    string os;

    if (!objectp(locker = lockers[player])) {
        notify_fail("You have nothing stored here.\n"); 
        return 0; 
    } 

    s = sizeof(o = all_inventory(locker)); 

    tmp = ({ }); 
    for (i = 0; i < s; i++) 
       if (o[i]->move(player))
           tmp += ({ o[i] }); 

    o -= tmp;  
    if (sizeof(o)) { 
        os = COMPOSITE_DEAD(o);  
        player->catch_msg("A guard gives you " + os +  " back.\n"); 
        tell_room(environment(player), "A guard gives " +
                  QTNAME(player) + " " + os + " back.\n", player); 
    } 

    if (sizeof(tmp)) { 
        player->catch_msg("You will have to free up some space for " + 
                COMPOSITE_DEAD(tmp) + " and claim again.\n"); 
        return 1;
    } 

    locker->remove_object(); 
    lockers = m_delete(lockers, player); 
    return 1; 
}

