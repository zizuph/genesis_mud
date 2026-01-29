/**
* This room is a simple control object that returns various quest
* information about a player and domain quests.
* Feel free to modify for your domain use in any way you wish.
*
* Basically all you have to do is:
* - Put this file into your domain
* - Replace all the add_quest_track_bits(group, bit) lines in the
*      create_room() with the values for your domain.
* - Change the return message in query_completed_quests_string
* - Call this object's quest_completed_quests_string function, 
*      passing in the player you want the string description for.
* - Write the string to the player somehow.
*
*
* I wrote it quick and dirty, if you have questions let me know.
* Louie  2006
*/

#pragma strict_types

inherit "/std/room.c";

//prototypes
int query_completed_quests();
string query_completed_quests_string(object ob);
mixed *quest_bits = ({});
void add_quest_track_bit(int group, int bit);

/*
 * Create the room.  Mortals shouldn't actually go into this
 * room, just use add_quest_track_bit(group, bit) to add
 * the quest group/bit combos for your domain.
 */
void
create_room()
{
    set_short("quest tracking room");

    set_long("This room is just a quest tracking room.  "+
        "Type 'quests' to see your quest count for DOMAIN.  "+
        "\n");

    //These are the Emerald quests group/bit combinations.
    //You would obviously use the combos from your domain.
    //add_quest_track_bit(group, bit)
    add_quest_track_bit(0, 0);
    add_quest_track_bit(3, 0);
    add_quest_track_bit(1, 0);
    add_quest_track_bit(2, 2);
    add_quest_track_bit(2, 6);
    add_quest_track_bit(2, 1);
    add_quest_track_bit(2, 7);
    add_quest_track_bit(2, 4);
    add_quest_track_bit(0, 6);
    add_quest_track_bit(2, 8);
    add_quest_track_bit(2, 0);
    add_quest_track_bit(0, 5);
    add_quest_track_bit(2, 5);
    add_quest_track_bit(0, 7);
    
}

/*
 * Adds group/bit combos to the class variable
 */
void
add_quest_track_bit(int group, int bit)
{
    quest_bits += ({ ({ group, bit }) });
}

/*
 * Standard init
 */
void
init()
{
    ::init();
    add_action(query_completed_quests, "quests");
}

/*
 * This method would be called from whatever room you are
 * actually displaying the information to the mortals in.
 * Inside that room, to get the string message this returns
 * you would use:
 *
 * "/d/Domain/path/quest_tracker_room"->query_completed_quests_string(this_player());
 *
 * And get back a string description of the quests the player has
 * completed to display to the mortal.
 *
 */
string 
query_completed_quests_string(object ob) {
    
    if (!ob || !interactive(ob))
        return "";

    int i = sizeof(quest_bits),
        completed = 0,
        total = i;
    
    while (i--)
    {
        if (ob->test_bit(domain(this_object()), 
                quest_bits[i][0], quest_bits[i][1]))
        {
            completed++;
        }
    }

    //Change this description to whatever you like.
    // 'completed' is the count of quests the mortal has
    // completed, while 'total' is the total
    // amount of quests for your domain (that you registered
    // here).
    return "You have completed "+
            completed+
            " of "+
            total+
            " DOMAIN quests.";
}

/*
 * This is just for testing in this room.
 * Have your jr use the 'quests' command here to test your stuff.
 */
int 
query_completed_quests()
{
    write(query_completed_quests_string(this_player())+"\n");
    return 1;
}