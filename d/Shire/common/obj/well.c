/*
 * A well. Just a gadget to fill your bucket with. ;-)
 *					Tricky, 28-2-92
 */
inherit "/std/object";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

//   Prototypes
void echo1();
void echo2();
void echo3();

int echo1_id, echo2_id, echo3_id;
void
create_object()
{
    set_name("well");
    set_adj("deep");
    set_short("deep well");
    set_long("@@my_long");
    add_prop(OBJ_I_WEIGHT, 7000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_prop(OBJ_I_NO_GET, 1);
}

string
my_long()
{
    say(QCTNAME(this_player()) + " peers quizzically into the well.\n"
      + capitalize(this_player()->query_pronoun()) + " cannot resist shouting 'echo!' "
      + "into it.\n");
    echo1_id = set_alarm(5.0,0.0,&echo1());
    return
	"You peer quizzically into the well.\n"
      + "It is deep, moist, and far below you see the reflection of water.\n"
      + "You cannot resist shouting 'echo!' into the hole.\n";
}

void
echo1()
{
    remove_alarm(echo1_id);
    tell_room(environment(this_object()), "From the well you hear clearly: echo!\n");
    echo2_id = set_alarm(5.0,0.0,&echo2());
}

void
echo2()
{
    remove_alarm(echo2_id);
    tell_room(environment(this_object()), "From within the well sounds: ...cho!\n");
    echo3_id = set_alarm(5.0,0.0,&echo3());
}

void
echo3()
{
    remove_alarm(echo3_id);
    tell_room(environment(this_object()), "From the well you faintly hear: ...o!\n");
}
