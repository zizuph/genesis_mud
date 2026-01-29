/* A part of the Emerald cave system. Recoded 25/03/97, Tulix III. */
/* This cave provides a handy place to pop up for a breath of air. */

inherit "/std/room";

#include "default.h"

#define AIR_OBJ "/d/Emerald/mountains/mtblack/cave/obj/air_obj.c"

/* We may be debugging the code */
#ifndef DEBUG
#define DEBUG 0
#endif

/* Global variable to track set_alarm */
public int alarm_num;

/* Prototype functions */
public int do_spit(string str);
public void try_hit_lichen(int pc_hit);
public void add_lichen_glow();
public void remove_lichen_glow();
public int do_breath(string str);
public int do_dive(string str);


public void 
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    set_short("A dark cave.\nThere is one obvious exit: dive");    
    set_long("   " +
        "This small cavern is filled with stale, but breathable air.\n" +
        "You'd best take a deep breath before you leave.\n\nThere is one " +
        "obvious exit: dive.\n");

    add_item("lichen", 
        "There is lichen growing on the volcanic rock. It is very fragile, " +
        "and cumbles to dust when you touch it.\n");
    add_item(({"walls","wall"}), 
        "The walls are cold, and damp to touch. It seems to be volcanic " +
        "rock that these caves are made of. Pretty hard stuff it is, too.\n" +
        "There is some lichen growing on the wall.\n");
    add_item(({"roof","ceiling"}), 
        "What little you can see above you suggests that the roof is made " +
        "of the same rock as the walls, volcanic rock. At least you can " +
        "be fairly sure the roof won't be falling down, as volcanic rock " +
        "is pretty tough stuff.\n");
    add_item(({"floor","ground"}),
        "You are currently treading water.\n");
    add_item(({"hole","pool","water"}), 
        "The water around you is quite cold, and rather murky. " +
        "You cannot see the bottom no matter how hard you look. " +
        "You could dive into it if you wanted to.\n");

    setuid();
    seteuid(getuid());
}

/*
 * Function name:   do_dive
 * Description:     move player into the water
 * Arguments:       str: dummy string
 * Returns:         0 if command failed, 1 if command successful
 */
public int
do_dive(string str)
{
    object air_obj;
    
    /* Find the air_obj in the players inventory. */
    air_obj = present("air_obj", TP);
    
    if (!air_obj)    
    {
        if (DEBUG != 0)
        {
            TP -> catch_msg("No air_obj found!\n");
        }
        
        /* Do not allow player to dive if no air_obj is found. */
        write("You decide that you'd rather not get wet just now.\n");
        return 1;
    }    

    TP->catch_msg(
        "As you dive into the water, you suddenly become aware of the "+
        "lack of air.\nLet's hope you took a deep breath before diving in.\n"+
        "Otherwise you might drown, which is such a nasty way to die.....\n"+
        "So make sure you keep an eye on how you feel, and don't stay "+
        "down too long!!\n");

    TP->move_living("into the water", WELL_DIR + "water10e", 0, 0);
    
    /* Start the countdown for the swimmer to drown. */
    air_obj->set_check_air_alarm();

    return 1;
}

/*
 * Function name:   do_breath
 * Description:     give player a bit more air to breathe
 * Arguments:       str: dummy string
 * Returns:         0 if command failed, 1 if command successful
 */
public int
do_breath(string str)
{
    if (( str == "breath" ) || ( str == "deep breath" ))
    {
        TP->add_prop("_live_i_air_remaining", 12);
        write("You take a deep breath of air.\n");
        say(QCTNAME(TP) + " takes a deep breath.\n");
        return 1;
    }
    
    NF("Take what?\n");
    return 0;
}

/*
 * Function name:   init
 * Description:     add commands to players entering the room
 */
public void
init()
{
    object air_obj;
    int air_remaining;

    ::init();
    add_action(do_dive, "dive");
    add_action(do_breath, "take");
    add_action(do_spit, "spit");
    
    /* Put some air in the lungs of the player. */
    air_remaining = TP->query_prop("_live_i_air_remaining");
    if (air_remaining < 6)
    {
        if (DEBUG != 0)
            TP -> catch_msg("air_remaining set to 6.\n");
        
        TP->add_prop("_live_i_air_remaining", 6);
    }

    /* Player may already have the air_obj. */
    air_obj = present("air_obj", TP);
    if (air_obj)
    {
        if (DEBUG != 0)
            TP -> catch_msg("remove_check_air_alarm called by room.\n");
        
        /* Cancel the check_air alarm. */
        air_obj->remove_check_air_alarm();
    }
    else
    {
        if (DEBUG != 0)
            TP -> catch_msg("new air_obj cloned.\n");
        
        air_obj = clone_object(AIR_OBJ);
        air_obj->move(TP);
        return;
    }
}

/* 
 * Function name: do_spit
 * Description:   Decide on the probabilty of the player hitting the lichen.
 * Arguments:     str: the string following the 'spit' command.
 * Returns:       0 = execute spit command, 1 = do not execute spit command.
 */
public int
do_spit(string str)
{
    string dummy;
    
    if (!strlen(str))
    {
        try_hit_lichen(40);
        return 0; /* Continue with the normal spit command. */
    }

    /*  use parse_command to check what player wants to spit onto. */
    if (parse_command(str, this_object(),
        "[towards] [onto] [on] [at] [the] 'lichen' / 'wall' %s", dummy))
    {
        write("You spit towards where you think some lichen is growing.\n");
        tell_room(this_object(), "\n" + QCTNAME(this_player()) +
            " spits towards a place where " + this_player()->query_pronoun() +
            " thinks some lichen is growing.\n", this_player() );
        
        try_hit_lichen(90);
        return 1; /* Do not continue with the normal spit command. */
    }
    else
        return 0; /* Continue normal spit command. */
}

/* 
 * Function name: try_hit_lichen
 * Description:   Determine if the spit hits in lichen.
 * Arguments:     pc_hit: % chance of hit.
 */
public void
try_hit_lichen(int pc_hit)
{
    if (random(100) < pc_hit)
    {
        /* Successful hit on some lichen. */
        if (alarm_num)
        {
            remove_alarm(alarm_num);
            set_alarm( 4.0, 0.0, add_lichen_glow);
        }
        
        alarm_num = set_alarm( 50.0, 0.0, remove_lichen_glow);
    }
}

/* 
 * Function name: add_lichen_glow
 * Description:   Make some lichen in the cave glow.
 */
public void
add_lichen_glow()
{
    tell_room(this_object(), "\nSome lichen in the cave starts to glow.\n");
    add_prop(ROOM_I_LIGHT, 1);
}

/* 
 * Function name: remove_lichen_glow
 * Description:   Remove the glow from the lichen.
 */
public void
remove_lichen_glow()
{
    tell_room(this_object(), "\nThe glow from the lichen fades away.\n");
    add_prop(ROOM_I_LIGHT, 0);
    alarm_num = 0; /* The alarm is no longer active. */
}


