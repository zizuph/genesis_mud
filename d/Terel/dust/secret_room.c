inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

#define DOOR       (DUSTDIR + "back_door")
#define LOCK_DELAY 8.0
#define MAGIC_GEM  "/d/Terel/zodiac/magic_gem"
#define TP         this_player()
#define TO         this_object()

object door;
object gem, quest_solver=0;

public void
create_room() 
{
    set_short("secret room");
    set_long("Unlike the other rooms of this part " +
        "of the mansion, this room is in perfect state - no dust and " +
        "no dirt. All the walls, including the floor and the " +
        "ceiling, are made of shining silver.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_WIZINFO, "If a player gets trapped here it is his/her " +
                            "own fault. Don't trans 'em outta here!\n");
    
    /* We create the door back */
    door = clone_object(DOOR);
    door->move(TO);
}

public void
set_quest_solver(object who)
{
    quest_solver = who;
    
    if (gem && present(gem, TO)) gem->remove_object();
    
    seteuid(getuid());
    gem = clone_object(MAGIC_GEM);
    gem->add_prop(OBJ_M_NO_GET, VBFC_ME("take_gem"));
    gem->move(TO, 1);
}

public mixed
take_gem()
{
    if (TP == quest_solver) {
        if (gem) set_alarm(1.0, -1.0, "allow_get_gem");
        return 0;
    }
    return "The gem is firmly attached to the floor and cannot be taken!\n";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (ob != quest_solver && living(ob)) {
        ob->catch_msg("You get a sudden feeling of fear!\n");
    }
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if (quest_solver && ob == quest_solver) {
        if (door->query_open() || door->query_locked() == 0) {
            tell_room(TO, "You hear a noice from the door. You better " +
                          "leave at once!\n", quest_solver);
        }
        set_alarm(LOCK_DELAY, -1.0, "lock_door");
    }
}

public void
lock_door()
{
    if (door) door->close_and_lock_door();
}

void
allow_get_gem()
{
    if (gem) gem->remove_prop(OBJ_M_NO_GET);
}
