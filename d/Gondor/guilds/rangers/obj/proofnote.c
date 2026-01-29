/*  /d/Gondor/guilds/rangers/obj/proofnote.c
 *
 *  Modified by Tigerlily on 11/01/2003--language for new joining procedure.
 */
inherit "/std/object";

#include <cmdparse.h>
#include <macros.h>
#include <stdproperties.h>

string Playername;

void destruct_me();

string
describe()
{
    return "Dear " + Playername + "!\n\n" + "We, Arador and Damrod, " +
        "Rangers of the Westlands, give you this note of introduction " +
        "to Amaron, Master Ranger of the Westlands. We recommend you to " +
        "him based on your ability to find your way through this forest " +
        "and because you have proven yourself by avoiding the traps we " +
        "had set out.\n\nWhen you find Amaron, present this note to him. " +
        "Beware if your attentions are not worthy, however! For you will " +
        "surely be tested for your character and stoutness of heart.\n\n" +
        "  Signed:   Arador, Ranger of the North, and\n"+
        "            Damrod, Ranger of Ithilien.\n";
}

int
do_destruct()
{
    set_alarm(2.0, 0.0, destruct_me);
    return 0;
}

void
create_object()
{
    set_short("note of recommendation");
    set_pshort("notes of recommendation");
    set_long(&describe());
    set_name("note");
    add_name("Ranger_Test_Proof");
    add_prop(OBJ_M_NO_DROP, &do_destruct());
    add_prop(OBJ_I_WEIGHT,  0);
    add_prop(OBJ_I_VOLUME,  0);
}

void
set_playername(string name)
{
    Playername = capitalize(lower_case(name));
}

string
query_playername()
{
    return Playername;
}


int
read_note(string str)
{
    mixed *message;

    notify_fail("Read what?\n");

    if (!strlen(str))
        return 0;

    message = FIND_STR_IN_OBJECT(str, this_player());

    if (!sizeof(message))
    {
        message = FIND_STR_IN_OBJECT(str, environment(this_player()));
        if (!sizeof(message))
        {
            notify_fail(capitalize(query_verb()) + " what?\n");
            return 0;
        }

        write("The message is too far away to read.\n");
        return 1;
    }

    if (message[0] == this_object())
        write(describe());
    else
        return 0;

    return 1;
}

void
destruct_me()
{
    object room;
    room = environment();
    while(!room->query_prop(ROOM_I_IS))
        room = environment(room);
    tell_room(room, "A white pigeon comes flying, picks up " +
        "the note, and flies away!\n");
    remove_object();
}

void
init()
{
    add_action(read_note,"read");
}

