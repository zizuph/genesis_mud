/* Silver door with the coloured buttons */
inherit "/std/door";

#define DUSTDIR    "/d/Terel/dust/"
#define OTHER_ROOM (DUSTDIR + "secret_room")

void
create_door()
{
    ::create_door();
    
    set_door_id("testdoor");
    set_door_desc("This door doesn't seem to have a " +
                  "normal lock. You wonder how it can be unlocked...\n");
    set_pass_command(({"w","west"}));
    set_door_name(({"silver door","door"}));
    set_other_room(OTHER_ROOM);
    set_lock_name("lock");
    set_lock_desc("You don't see any lock. However, " +
        "if you look closely, you can make out the twelve zodiac " +
        "signs, namely Aries, Taurus, Gemini, Cancer, Leo, Virgo, " +
        "Libra, Scorpio, Sagittarius, Capricorn, Aquarius " +
        "and Pisces, building a circle, engraved in the silver door.\n");
   add_item(({"lock","zodiac","sign","signs"}),
      "You don't see any lock. However, " +
      "if you look closely, you can make out the twelve zodiac " +
      "signs, namely Aries, Taurus, Gemini, Cancer, Leo, Virgo, " +
      "Libra, Scorpio, Sagittarius, Capricorn, Aquarius " +
      "and Pisces, building a circle, engraved in the silver door.\n");
    set_no_pick();

    set_open(0);
    set_locked(1);
}

/*
 * The following function unlocks the door
 * + tells secret_room who is allowed to get the gem
 * + loads the gem in the other room. Mortricia added this. April 94
 */

public int
door_solved()
{
    if (!other_door) load_other_door();
    
    if (lock_status && other_room && other_door)
    {
        do_unlock_door("You hear a soft 'clic' from the silver door.\n");
        other_door->do_unlock_door("You hear a soft 'clic' from the silver door.\n");
        other_room->set_quest_solver(this_player());
        return 1;
    }
    return 0;
}
