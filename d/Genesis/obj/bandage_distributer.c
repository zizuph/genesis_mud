#define COMMON_BOARD_MASTER "/d/Genesis/obj/common_master"
#define DISPENSER_OBJECT    "/d/Genesis/obj/bandage_dispenser"
#define DISPENSER_ID        "_bandage_dispenser"

void
create()
{
    setuid();
    seteuid(getuid());
}

/*
 * Function name: distribute_dispenser
 * Description  : Create a dispenser and add it to the common board.
 * Arguments    : object room - the room to add the dispenser to.
 */
void
create_dispenser(object room)
{
    if (!present(DISPENSER_ID, room))
    {
        // clone_object(DISPENSER_OBJECT)->move(room, 1);
    }
}

/*
 * Function name: distribute_dispensers
 * Description  : Ditribution of dispensers to the common board rooms.
 */
void
distribute_dispensers()
{
    object *rooms;

    /* Get all rooms with a common board. */
    rooms = filter(COMMON_BOARD_MASTER->query_all_cloned_boards(), objectp);
    rooms = filter(map(rooms, environment), objectp);

    /* Add the bandage dispensers to the rooms. */
    map(rooms, create_dispenser);
}
