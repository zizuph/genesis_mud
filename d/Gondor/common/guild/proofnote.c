#pragma save_binary

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

string playername;

void
create_object()
{
    set_short("note of recommendation");
    set_pshort("notes of recommendation");
    set_long("@@describe");
    set_name("note");
    add_name("Ranger_Test_Proof");
    add_prop(OBJ_M_NO_DROP,"@@do_destruct");
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
}

void
set_playername(string name)
{
    playername = capitalize(lower_case(name));
}

string
query_playername()
{
    return playername;
}

string
describe()
{
  return "Dear "+playername+"!\n\n"+
    "We, Arador and Damrod, Rangers of Gondor, hereby recommend\n"+
    "the Council of the Gondorian Rangers to accept you, and allow you\n"+
    "to join the Gondorian Rangers Guild.\n"+
    "We recommend this on the basis of seeing you find your way through\n"+
    "this forest, and also avoid the traps we had set out.\n\n"+
    "The decision is not ours to make, however. Seek out an Officer,\n"+
    "Recruiter or Mentor of the Rangers, and discuss the possibility\n"+
    "with them.\n\n"+
    "  Signed: Arador, Ranger of Gondor, and\n"+
      "          Damrod, Ranger of Ithilien.\n";
}

void
init()
{
    add_action("read_note","read");
}

int
read_note(string str)
{
    if (!str) return 0;
    if (str != "note" && str != "note of recommendation") return 0;
    write(describe());
    return 1;
}

void
destruct_me()
{
    object room;
    room = environment();
    while(!room->query_prop(ROOM_I_IS))
        room = environment(room);
    tell_room(room, "A white pigeon comes flying, picks up the note, and flies away!\n");
    remove_object();
}

int
do_destruct()
{
    set_alarm(2.0, 0.0, destruct_me);
    return 0;
}


