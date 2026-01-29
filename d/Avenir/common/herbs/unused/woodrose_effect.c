// Woodrose effect. It makes people behave joyful
// and silly. Cirion, July 1997
inherit "/std/poison_effect";

#include <poison_types.h>
#include "/d/Avenir/common/common.h"

string *emotes = ({ "hiccup", "laugh", "cackle", "dance", "twitch", "wiggle", "sing", "yodel" });
string *emotes_adv = ({ "smile", "bounce", "giggle", "squirm",
            "grin" });
string *emotes_others = ({ "hug", "cuddle", "dance", "flirt", 
            "nuzzle", "pounce", "tackle" });
string *adv = ({ "joyful", "drunken", "happ", "insan", "amazedly", "coquett",
            "cute", "glee", "fanat", "misch", "naught", "quixot", "randomly",
            "sentiment", "vacant" });

void
create_poison_effect()
{
    set_name("woodrose_effect");
    set_short("Woodrose Happiness");

    set_interval(20);
    set_time(5000);


    set_silent(2); // use my own messages, no coughing, etc.

    set_strength(20);
    set_poison_type("happiness");

    set_damage(({ POISON_USER_DEF }));
}

object
get_valid_other(object who)
{
    object *people;

    if(!ENV(who))
       return 0;

    people = FILTER_LIVE(all_inventory(ENV(who))) - ({ who });

    if(!sizeof(people))
        return 0;

    people -= ({ 0 });

    if(!sizeof(people))
        return 0;


    people = FILTER_CAN_SEE(people, who);

    if(!sizeof(people))
        return 0;

    return ONEOF(people);
}

void
special_damage(int damage)
{
    object who, me;

    if(!(me = ENV(TO)))
        return;

    who = get_valid_other(me);

    if(who && random(3))
        me->command(ONEOF(emotes_others) + " " + who->query_real_name());
    else if(!random(2))
        me->command(ONEOF(emotes_adv) + " " + ONEOF(adv));
    else
        me->command(ONEOF(emotes));
}
