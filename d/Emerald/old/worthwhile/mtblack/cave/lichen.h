/* /d/Emerald/cave/lichen.h - this file is to be included in most of the  */
/* caves, so that you light up the cave by spitting on lichen.            */
/* This feature was added while the game was closed for a mudlib upgrade. */
/* Coded 05/06/96 by Tulix III.                                           */

/* Global variable to track set_alarm */
public int alarm_num;

/* Prototype functions */
public int do_spit(string str);
public void try_hit_lichen(int pc_hit);
public void add_lichen_glow();
public void remove_lichen_glow();

/* 
 * Function name: init
 * Description:   Call the do_spit fuction when a player uses 'spit' command.
 */
public void
init()
{
    ::init();
    add_action(do_spit, "spit");
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
        tell_room(this_object(), QCTNAME(this_player()) +
            " spits towards a place where " + this_player()->query_pronoun() +
            " thinks some lichen is growing.\n", this_player() );
        
        try_hit_lichen(95);
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
            remove_alarm(alarm_num);

        set_alarm( 4.0, 0.0, add_lichen_glow);
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
    add_prop(ROOM_I_LIGHT, 1);
    tell_room(this_object(), "Some lichen in the cave starts to glow.\n");
}

/* 
 * Function name: remove_lichen_glow
 * Description:   Remove the glow from the lichen.
 */
public void
remove_lichen_glow()
{
    tell_room(this_object(), "The glow from the lichen fades away.\n");
    add_prop(ROOM_I_LIGHT, 0);
    alarm_num = 0; /* The alarm is no longer active. */
}

