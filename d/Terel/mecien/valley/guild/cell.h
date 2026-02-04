/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
#define PATH               "/d/Terel/mecien/valley/guild/"
#define TO                 this_object()
#define TP                 this_player()
#define NO_MANA            10
#define MIN_INC_MANA       10
#define DELAY              30

int no_mana, resting, aid=0;
object last_user;
int query_no_mana();
int leave();
int do_rest();
int do_rise();
string my_bed();
void inc_mana(object who);
object query_last_user();

void
init()
{
    ::init();
    add_action("do_rest", "rest");
    add_action("do_rest", "meditate");
    add_action("do_rise", "rise");
    add_action("do_rise", "leave");
}

void
reset_room()
{
    if (!resting) no_mana = NO_MANA;
}


int
leave()
{
    if (!resting) return 0;
    write( "You cannot do that while resting! You must rise first.\n");
    return 1;
}

int
do_rest()
{
    int i;
    object room;

    if (resting) return 0;

    for (i=0; i<sizeof(OTHER_CELLS); i++) {
        room = find_object(PATH + OTHER_CELLS[i]);
        if (room && room->query_last_user() == TP) {
            write(
                "You aren't allowed to use this bed!\n"
            );
            if (room->query_no_mana() >= 1) {
                write("Use your old cell instead.\n");
            }
            return 1;
        }
    }
    if (no_mana < 1) {
        write(
            "The bed isn't in order. Please, come back later when " +
            "the staff have prepared it for you.\n"
        );
        return 1;
    }
    if (TP->query_mana() == TP->query_max_mana()) {
        write("There is no need for you to rest.\n");
        return 1;
    }
    write("You lay down on the soft bed.\n");
    write("The light goes out and you feel calm.\n");
    add_prop(ROOM_I_LIGHT, 0);
    resting = 1;

    last_user = TP;
    aid = set_alarm(itof(DELAY), -1.0, &inc_mana(TP));
    return 1;
}

int
do_rise()
{
    if (!resting) return 0;

    write("As you rise from the bed the light comes on.\n");
    if (aid) {
        remove_alarm(aid);
        aid = 0;
    }
    resting = 0;
    add_prop(ROOM_I_LIGHT, 1);

    return 1;
}

void
inc_mana(object who)
{
    int tp_mana, tp_max_mana, tp_inc_mana, inc;

    aid = 0;
    
    if (!resting || !who || environment(who) != TO) return;

    tp_mana = who->query_mana();
    tp_max_mana = who->query_max_mana();
    tp_inc_mana = tp_max_mana/45;
    if (tp_inc_mana < MIN_INC_MANA) tp_inc_mana = MIN_INC_MANA;

    if (tp_mana == tp_max_mana) {
        who->catch_msg("There is no need for you to rest here any longer.\n");
        who->catch_msg("You better rise.\n");
        return;
    }
    if (no_mana < 1) {
        who->catch_msg("You are not allowed to rest here any longer.\n");
        who->catch_msg("You better rise.\n");
        return;
    }
    inc = tp_inc_mana;
    if (tp_max_mana-tp_mana < inc) inc = tp_max_mana-tp_mana;

    who->catch_msg("Some of your lost powers are restored.\n");
    no_mana--;
    who->add_mana(inc);

    aid = set_alarm(itof(DELAY), -1.0, &inc_mana(who));
}

string
my_bed()
{
    if (resting)
        return "You are lying in it right now.\n";
    if (no_mana < 1 )
        return "It looks very soft. However, it doesn't look " +
               "particularily inviting since someone has recently " +
               "used it.\n";
    return "It looks very soft. Maybe you should rest " +
           "in it for a while?\n";
}

object
query_last_user()
{
    return last_user;
}

int
query_no_mana()
{
    return no_mana;
}
