inherit "/d/Gondor/minas/houses/citizens/house";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/quest/pw5_defs.h"

void    add_door();
void    reset_room();

int     suspect;
mixed  *door_command = ({}),
       *door_name = ({});
object  citizen;
string  door_id,
        other_room,
        door_desc;

void    set_door_id(string str) { door_id = str; }
void    set_door_command(mixed arr) { door_command = arr; }
void    set_door_name(mixed arr) { door_name = arr; }
void    set_other_room(string str) { other_room = str; }
void    set_door_desc(string str) { door_desc = str; }
void    set_suspect(int i) { suspect = i; }

void
create_suspect_room()
{
    add_exit(MINAS_DIR+"houses/citizens/c2ncrc12","north",0,0);

    set_door_id("MT_c1_n2crc1");
    set_door_command(({"s","south"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(MINAS_DIR + "n2crc1");
    set_door_desc(BSN("The wooden door looks rather old, but it "
      + "obviously has been painted regularly so there is hardly "
      + "any wear noticeable."));

    set_suspect(0); // number of the suspect
}

nomask void
create_room()
{
    set_short("living room");
    set_long(BSN(
        "This is the living room of the house. A door is leading out onto "
      + "the street to the south. A doorway is leading north into the "
      + "kitchen."));

    create_suspect_room();

    add_prop(ROOM_I_INSIDE, 1);

    if (strlen(door_id))
        add_door();

    reset_room();
}

void
add_door()
{
    object  door;

    if (present("door", TO))
        return;

    // clone and configue door
    door = clone_object(MINAS_DIR + "doors/suspect_door");
    door->set_door_id(door_id);
    door->set_pass_command(door_command);
    door->set_door_name(door_name);
    door->set_other_room(other_room);
    door->set_door_desc(door_desc);
    door->set_key(door_id);
    door->move(TO);
}

void
reset_room()
{
    object  key;

    if (objectp(citizen))
        return;

    citizen = clone_object(MT_PW5_SUSPECT);
    if (!(citizen->set_suspect(suspect)))
    {
        citizen->remove_object();
        return;
    }
    citizen->arm_me();
    key = clone_object("/std/key");
    key->set_key(door_id);
    key->set_short("iron key");
    key->set_adj(({"black", "iron", }));
    key->set_long("A black iron key, probably for a door.\n");
    key->move(citizen);
    citizen->move(TO);
}

